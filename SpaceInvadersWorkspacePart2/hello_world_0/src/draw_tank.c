/*
 * draw_tank.c
 *
 *  Created on: Oct 20, 2017
 *      Author: superman
 */

#include "draw_tank.h"
#include "draw.h"
#include "images.h"

#define TANK_RIGHT_BORDER SCREEN_WIDTH - 32 //The right border is the screen width - 32
#define TANK_LEFT_BORDER 0 //The tank left border is 0
#define TANK_MOVE_LEFT 4 //move left by 4
#define TANK_MOVE_RIGHT 26 //move right by 26
#define TANK_MOVE 4 //Move is 4

extern unsigned int * frame_pointer;

static uint16_t tankPosition; //Variable to keep track of tank position

void setTankPosition(uint16_t val){ //Set the position of the tank
	tankPosition = val;
}

uint16_t getTankPosition(){ //get the position of the tank
	return tankPosition;
}

void drawTank(uint8_t direction){
	if(direction == TANK_LEFT){
		// Move the tank left.
		if(getTankPosition() != TANK_LEFT_BORDER){ //This is to make sure that it doesn't go over to the left of the screen when it is at the edge;
			setTankPosition(getTankPosition() - TANK_MOVE);
		}
	}
	else if(direction == TANK_RIGHT){
		// Move the tank left.
		if(getTankPosition() < (TANK_RIGHT_BORDER)){ //This should make sure that the tank doesn't go off the edge of the screen might make it (640-32) instead of (640-30)
			setTankPosition(getTankPosition() + TANK_MOVE);
		}
	}
	uint8_t line, pixel;
	for(line = 0; line < TANK_HEIGHT; line++){
		for(pixel = 0; pixel < TANK_WORD_WIDTH; pixel++){
			// Stuff to do to move the tank left
			if(direction == TANK_LEFT){
				// Draw the left side of the moving tank
				if((tank_symbol[line] & (SHIFT<<(TANK_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] == BLACK){
						frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] = GREEN; //Set to green
					}
				}
				else{
					if(frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] == GREEN){
						frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] = BLACK; //Set to black
					}
				}
				// Erase the right side of the moving tank
				if(pixel >= (TANK_WORD_WIDTH - TANK_MOVE_LEFT)){
					frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + TANK_MOVE + getTankPosition())] = BLACK; //Set to black
				}
			}
			// Stuff to do to move the tank right
			else if(direction == TANK_RIGHT){
				// Draw the Right side of the moving tank
				if((tank_symbol[line] & (SHIFT<<(TANK_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] == BLACK){
						frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] = GREEN; //Set to green
					}
				}
				else{
					if(frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] == GREEN){
						frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] = BLACK; //Set to black
					}
				}
				// Erase the left side of the moving tank
				if(pixel < (TANK_WORD_WIDTH - TANK_MOVE_RIGHT)){
					frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel - TANK_MOVE + getTankPosition())] = BLACK; //Set to black
				}
			}
		}
	}
}
