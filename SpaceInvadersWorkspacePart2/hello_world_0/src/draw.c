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

#define SCREEN_HEIGHT 480 //Height of screen

unsigned int * frame_pointer = (unsigned int *) FRAME_BUFFER_0_ADDR_BASE;

unsigned int * draw_start_screen(){
	setTankPosition(TANK_INITIAL_X_POSITION); //Set tank position
	uint16_t row, col;
	for(row=0; row < SCREEN_HEIGHT; row++) {
		for(col=0; col < SCREEN_WIDTH; col++) {
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
	drawLifeMessage(LIVES_MESSAGE_X, LIVES_MESSAGE_Y);
	drawBunker(BUNKER_1_X_POSITION, BUNKER_Y_POSITION); //Draw bunker 1
	drawBunker(BUNKER_2_X_POSITION, BUNKER_Y_POSITION); //Draw bunker 2
	drawBunker(BUNKER_3_X_POSITION, BUNKER_Y_POSITION); //Draw bunker 3
	drawBunker(BUNKER_4_X_POSITION, BUNKER_Y_POSITION); //Draw bunker 4
	initializeAlienBlock();
	drawAlienBlock(); //Draw the alien block
	return frame_pointer; //Return the fram pointer
}
