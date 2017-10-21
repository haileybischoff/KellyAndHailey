/*
 * draw_saucer.c
 *
 *  Created on: Oct 20, 2017
 *      Author: superman
 */

#include "draw_saucer.h"
#include "images.h"

#define SAUCER_Y_POSITION 29 // This is the Y position for when we draw the saucer.
#define SAUCER_MIN_X_POSITION -32 // The minimum X position for our saucer
#define SAUCER_MAX_X_POSITION 640 // The maximum X position for our saucer
#define SAUCER_MOVE 4 // How many pixels our saucer moves when it moves
#define SAUCER_ERASE_HEIGHT_OFFSET 6 // The amount down we need to know in order to erase.

static uint16_t saucerPosition; //Variable to keep track of saucer position
static bool saucer_move_right = true; // A bool for moving the saucer right or left
static bool tank_killed_saucer = false;

static point_t saucer_shot;

extern unsigned int * frame_pointer;

uint16_t getSaucerPosition(){
	return saucerPosition;
}

void setDeadSaucerPosition(point_t deadSaucer){
	saucer_shot.x = deadSaucer.x;
	saucer_shot.y = deadSaucer.y;
}

point_t getDeadSaucerPosition(){
	return saucer_shot;
}

void setDidTankKillSaucertoFalse(){
	tank_killed_saucer = false;
}

bool didTankKillSaucer(){
	return tank_killed_saucer;
}

void setSaucerPosition(uint16_t val){
	saucerPosition = val;
}

point_t setUpdatedTopLeftSaucer(point_t some_point){
	uint16_t leftSaucerX = getSaucerPosition();
	uint16_t rightSacuerX = leftSaucerX + SAUCER_WIDTH;
	uint16_t saucerTopY = SAUCER_Y_POSITION;
	uint16_t saucerBottomY = saucerTopY + SAUCER_HEIGHT;
	point_t mine;
	if(((some_point.x >= leftSaucerX) && (some_point.x <= rightSacuerX)) && ((some_point.y >= saucerTopY) && (some_point.y <= saucerBottomY))){
		mine.x = leftSaucerX;
		mine.y = saucerTopY;
		return mine;
	}

	return mine;
}

bool calculateHitSaucer(point_t some_point){
	uint16_t leftSaucerX = getSaucerPosition();
	uint16_t rightSacuerX = leftSaucerX + SAUCER_WIDTH;
	uint16_t saucerTopY = SAUCER_Y_POSITION;
	uint16_t saucerBottomY = saucerTopY + SAUCER_HEIGHT;
	if(((some_point.x >= leftSaucerX) && (some_point.x <= rightSacuerX)) && ((some_point.y >= saucerTopY) && (some_point.y <= saucerBottomY))){
		tank_killed_saucer = true;
		return true;
	}
	return false;
}

// This function will erase the extra bits on the side of the saucer that will get missed by the automatic update.
void eraseExtraSaucerBits(int16_t x_position){
	uint8_t line, pixel;

	for(line = 0; line < SAUCER_MOVE; line++){ // We only need to overwrite a few pixels within a 4x4 area
		for(pixel = 0; pixel < SAUCER_MOVE; pixel++){
			if(saucer_move_right){ // This is what we need to erase if we are moving right.
				if(frame_pointer[(line + SAUCER_Y_POSITION + SAUCER_ERASE_HEIGHT_OFFSET)*SCREEN_WIDTH + (pixel + x_position - SAUCER_MOVE)] == RED){
					frame_pointer[(line + SAUCER_Y_POSITION + SAUCER_ERASE_HEIGHT_OFFSET)*SCREEN_WIDTH + (pixel + x_position - SAUCER_MOVE)] = BLACK; //Set to black
				}
			}
			else{ // This is what we need to erase if we are moving left.
				if(frame_pointer[(line + SAUCER_Y_POSITION + SAUCER_ERASE_HEIGHT_OFFSET)*SCREEN_WIDTH + (pixel + x_position + SAUCER_WIDTH)] == RED){
					frame_pointer[(line + SAUCER_Y_POSITION + SAUCER_ERASE_HEIGHT_OFFSET)*SCREEN_WIDTH + (pixel + x_position + SAUCER_WIDTH)] = BLACK; //Set to black
				}
			}
		}
	}
}

// This calculates the new x position for the saucer.
uint16_t update_saucer_x_position(){
	static int16_t x_position = RESET; // A static variable to to hold the x position

	if(saucer_move_right){
		x_position += SAUCER_MOVE; // If we are moving right increment our position.
	}
	else{
		x_position -= SAUCER_MOVE; // If we are moving left decrement our position.
	}

	if(x_position == SAUCER_MAX_X_POSITION){ // If we reach the max saucer position
		eraseExtraSaucerBits(x_position); // We need to erase the final bits of saucer
		saucer_move_right = false; // We need to go left for next time.
	}
	else if(x_position == SAUCER_MIN_X_POSITION){ // If we reach the min saucer position
		eraseExtraSaucerBits(x_position); // We need to erase the final bits of saucer.
		saucer_move_right = true; // We need to go right for next time.
	}
	return x_position;
}

void eraseSaucer(point_t position){
	//xil_printf("Did we erase the saucer??\n\r");
	uint8_t line, pixel;
	//int16_t x_position = update_saucer_x_position();
	//xil_printf("start erasing at x is : %d and y is : %d \n\r", position.x, position.y);
	for(line = 0; line < SAUCER_HEIGHT; line++){ // We only need to overwrite a few pixels within a 4x4 area
		for(pixel = 0; pixel < SAUCER_WIDTH; pixel++){
			//if(frame_pointer[(line + position.y)*SCREEN_WIDTH + (pixel + position.x)] == RED){
			frame_pointer[(line + position.y)*SCREEN_WIDTH + (pixel + position.x)] = BLACK; //Set to black
			//}
			//if(frame_pointer[(line + position.y + SAUCER_ERASE_HEIGHT_OFFSET)*SCREEN_WIDTH + (pixel + position.x - SAUCER_MOVE)] == RED){
			//	frame_pointer[(line + position.y + SAUCER_ERASE_HEIGHT_OFFSET)*SCREEN_WIDTH + (pixel + position.x - SAUCER_MOVE)] = BLACK; //Set to black
			//}
		}
	}
}

bool drawSaucer(){
	uint8_t line, pixel;

	int16_t x_position = update_saucer_x_position();
	//xil_printf("Draw saucer at x is : %d and y is : %d \n\r", x_position, SAUCER_Y_POSITION);
	setSaucerPosition(x_position);
	if((x_position == SAUCER_MAX_X_POSITION) || (x_position == SAUCER_MIN_X_POSITION)){
		return false; // We need to stop the draw saucer functionality now that we have gone off the board.
	}

	if(x_position < LEFT_BORDER){ // We have some partial drawing to do when it gets to the left border.
		for(line = 0; line < SAUCER_HEIGHT; line++){ //For height
			for(pixel = 0; pixel < SAUCER_WIDTH; pixel++){ // So we need to do a smaller width because we are only drawing some of the saucer.
				if((pixel + x_position) >= RESET){
					if((saucer_symbol[line] & (SHIFT<<(SAUCER_WIDTH-SHIFT-pixel)))){
						if(frame_pointer[(line + SAUCER_Y_POSITION)*SCREEN_WIDTH + (pixel + x_position)] == BLACK){
							frame_pointer[(line + SAUCER_Y_POSITION)*SCREEN_WIDTH + (pixel + x_position)] = RED; //Set to red
						}
					}
					else{
						if(frame_pointer[(line + SAUCER_Y_POSITION)*SCREEN_WIDTH + (pixel + x_position)] == RED){
							frame_pointer[(line + SAUCER_Y_POSITION)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
						}
					}
				}
			}
		}
		if(!saucer_move_right){
			eraseExtraSaucerBits(x_position);
		}

	}
	else if(x_position > (RIGHT_BORDER - SAUCER_WIDTH)){ // We have some partial drawing to do when it gets to the right border.
		for(line = 0; line < SAUCER_HEIGHT; line++){ //For height
			for(pixel = 0; pixel < (SCREEN_WIDTH - x_position); pixel++){ //
				if((saucer_symbol[line] & (SHIFT<<(SAUCER_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + SAUCER_Y_POSITION)*SCREEN_WIDTH + (pixel + x_position)] == BLACK){
						frame_pointer[(line + SAUCER_Y_POSITION)*SCREEN_WIDTH + (pixel + x_position)] = RED; //Set to red
					}
				}
				else{
					if(frame_pointer[(line + SAUCER_Y_POSITION)*SCREEN_WIDTH + (pixel + x_position)] == RED){
						frame_pointer[(line + SAUCER_Y_POSITION)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
					}
				}
			}
		}
		if(saucer_move_right){
			eraseExtraSaucerBits(x_position);
		}
	}
	else{ // Erasing and drawing for normal operation.
		for(line = 0; line < SAUCER_HEIGHT; line++){ //For height
			for(pixel = 0; pixel < SAUCER_WIDTH; pixel++){ //For width
				if((saucer_symbol[line] & (SHIFT<<(SAUCER_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + SAUCER_Y_POSITION)*SCREEN_WIDTH + (pixel + x_position)] == BLACK){
						frame_pointer[(line + SAUCER_Y_POSITION)*SCREEN_WIDTH + (pixel + x_position)] = RED; //Set to red
					}
				}
				else{
					if(frame_pointer[(line + SAUCER_Y_POSITION)*SCREEN_WIDTH + (pixel + x_position)] == RED){
						frame_pointer[(line + SAUCER_Y_POSITION)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
					}
				}
			}
		}
		eraseExtraSaucerBits(x_position);
	}
	return true;
}
