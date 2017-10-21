/*
 * score_keeping.c
 *
 *  Created on: Oct 21, 2017
 *      Author: superman
 */

#include "score_keeping.h"
#include "draw_aliens.h"
#include "images.h"

#define SQUID_POINTS 40
#define BUG_POINTS 20
#define JELLYFISH_POINTS 10
#define SAUCER_POINTS 200 //Hard coded in should be random between 50 and 350

static uint32_t totalScore = RESET;

extern unsigned int * frame_pointer;

void computeScore(uint8_t alien_number){
	uint8_t alien_Score;
	if(alien_number < ALIEN_ROW_1){
		alien_Score = SQUID_POINTS; //Set to squid in
	}
	else if((alien_number >= ALIEN_ROW_1) && (alien_number < ALIEN_ROW_3)){

		alien_Score = BUG_POINTS; //Set to bug in
	}
	else if((alien_number >= ALIEN_ROW_3) && (alien_number < ALIEN_ROW_5)){

		alien_Score = JELLYFISH_POINTS; //Set to jellyfish in
	}
	else{
		alien_Score = SAUCER_POINTS;
	}
	setScore(alien_Score);
	xil_printf("Score is: %d\n\r", getScore());

}

uint32_t getScore(){
	return totalScore;
}
void setScore(uint32_t score){
	totalScore += score;
}

void drawLife(uint16_t x_position, uint16_t y_position){ //Draw life function
	uint8_t line, pixel;
	for(line = 0; line < TANK_HEIGHT; line++){ //For height
		for(pixel = 0; pixel < TANK_WORD_WIDTH; pixel++){ //For width
			if((tank_symbol[line] & (SHIFT<<(TANK_WORD_WIDTH-SHIFT-pixel)))){
				frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = GREEN; //Set to green
			}
		}
	}
}