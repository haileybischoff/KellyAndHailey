/*
 * draw.c
 *
 *  Created on: Oct 5, 2017
 *      Author: superman
 */

#include <stdbool.h>
#include "draw.h"
#include "images.h"
#include "draw_tank.h"
#include "draw_aliens.h"
#include "draw_bunker.h"
#include "score_keeping.h"

#define FRAME_BUFFER_0_ADDR_BASE 0xC1000000  // Starting location in DDR where we will store the images that we display.

#define TWO_LIVES 2
#define ONE_LIFE 1
#define NO_LIVES 0
#define TOP_CLEAR_SCREEN_Y 29
#define BOTTOM_CLEAR_SCREEN_Y 444
#define SCREEN_HEIGHT 480 //Height of screen

unsigned int * frame_pointer = (unsigned int *) FRAME_BUFFER_0_ADDR_BASE;

void eraseLives(uint8_t lives){ //Erase the lives
	point_t life;
	life.y = LIFE_Y_POSITION;
	if(lives == TWO_LIVES){ //If we now have two lives erase the one on right
		life.x = LIFE_3_X_POSITION;
	}
	else if(lives == ONE_LIFE){ // We have one life erase the middle
		life.x = LIFE_2_X_POSITION;
	}
	else if(lives == NO_LIVES){ //No lives  erase the left
		life.x = LIFE_1_X_POSITION;
	}
	uint8_t line, pixel;
	for(line = 0; line < TANK_HEIGHT; line++){ //For height
		for(pixel = 0; pixel < TANK_WORD_WIDTH; pixel++){ //For width
			if((tank_symbol[line] & (SHIFT<<(TANK_WORD_WIDTH-SHIFT-pixel)))){ //If pixel is a 1
				frame_pointer[(line + life.y)*SCREEN_WIDTH + (pixel + life.x)] = BLACK; //Set to black
			}
		}
	}
	//drawLife(LIFE_1_X_POSITION, LIFE_Y_POSITION); //Draw life 1
}

void clearScreen(){
	uint16_t pixel, line;
	for(line = TOP_CLEAR_SCREEN_Y; line < BOTTOM_CLEAR_SCREEN_Y; line++){ //height
		for(pixel = 0; pixel < SCREEN_WIDTH; pixel++){ //width
			if(frame_pointer[(line)*SCREEN_WIDTH + (pixel)] != BLACK){ //Set to black
				frame_pointer[(line)*SCREEN_WIDTH + (pixel)] = BLACK; //Set to black
			}
		}
	}
}

unsigned int * draw_start_screen(){
	setTankPosition(TANK_INITIAL_X_POSITION); //Set tank position
	uint16_t row, col;
	for(row = 0; row < SCREEN_HEIGHT; row++) {//row
		for(col = 0; col < SCREEN_WIDTH; col++) { //col
			if(row == GROUND_LEVEL || row == (GROUND_LEVEL - INCREMENT_OR_DECREMENT)){ //This is to draw the bottom line of the game
				frame_pointer[row*SCREEN_WIDTH + col] = GREEN;
			}
			else{
				frame_pointer[row*SCREEN_WIDTH + col] = BLACK;
			}
		}
	}
	uint16_t tank_position;
	tank_position = TANK_INITIAL_X_POSITION;
	setTankPosition(tank_position); //Set tank
	drawLife(TANK_INITIAL_X_POSITION, TANK_Y_POSITION); //Draw tank
	drawLife(LIFE_1_X_POSITION, LIFE_Y_POSITION); //Draw life 1
	drawLife(LIFE_2_X_POSITION, LIFE_Y_POSITION); //Draw life 2
	drawLife(LIFE_3_X_POSITION, LIFE_Y_POSITION); //Draw life 3
	drawLifeMessage(LIVES_MESSAGE_X, LIVES_MESSAGE_Y); // Draw the Lives message
	drawScoreMessage(SCORE_MESSAGE_X, SCORE_MESSAGE_Y); // Draw the score message

	point_t score_position;
	score_position.x = SCORE_X;
	score_position.y = SCORE_Y;

	drawNumber(score_position, zero);
	drawBunker(BUNKER_1_X_POSITION, BUNKER_Y_POSITION); //Draw bunker 1
	drawBunker(BUNKER_2_X_POSITION, BUNKER_Y_POSITION); //Draw bunker 2
	drawBunker(BUNKER_3_X_POSITION, BUNKER_Y_POSITION); //Draw bunker 3
	drawBunker(BUNKER_4_X_POSITION, BUNKER_Y_POSITION); //Draw bunker 4
	initializeAlienBlock();
	drawAlienBlock(); //Draw the alien block
	return frame_pointer; //Return the fram pointer
}
