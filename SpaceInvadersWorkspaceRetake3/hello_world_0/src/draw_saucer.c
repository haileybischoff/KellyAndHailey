/*
 * draw_saucer.c
 *
 *  Created on: Oct 20, 2017
 *      Author: superman
 */

#include "draw_saucer.h"
#include "images.h"
#include "sound.h"

#define SAUCER_MIN_X_POSITION -32 // The minimum X position for our saucer
#define SAUCER_MAX_X_POSITION 640 // The maximum X position for our saucer
#define SAUCER_MOVE 4 // How many pixels our saucer moves when it moves
#define SAUCER_ERASE_HEIGHT_OFFSET 6 // The amount down we need to know in order to erase.

static uint16_t saucerPosition = RESET; //Variable to keep track of saucer position
static uint16_t saucerDeathPosition = RESET;
static bool saucer_move_right = true; // A bool for moving the saucer right or left
static bool tank_killed_saucer = false;
static bool getNewPosition = false;

extern unsigned int * frame_pointer;

uint16_t getSaucerPosition(){ //Get the saucer position
	return saucerPosition;
}

uint16_t getSaucerDeathPosition(){ //Get the desath position for saucer
	return saucerDeathPosition;
}

void setSaucerDeathPosition(uint16_t deathPosition){ //Set the death position for saucer
	saucerDeathPosition = deathPosition;
}

void setDidTankKillSaucerFlag(bool saucerFlag){ //Set the flag for tank killed saucer
	tank_killed_saucer = saucerFlag;
}

bool didTankKillSaucer(){ //Did tank kill saucer
	return tank_killed_saucer;
}

void setSaucerPosition(uint16_t val){ //Set saucer position
	saucerPosition = val;
}

bool calculateHitSaucer(point_t some_point){ //Calculate if a saucer was hit
	uint16_t leftSaucerX = getSaucerPosition(); //left position
	uint16_t rightSacuerX = leftSaucerX + SAUCER_WIDTH; //Right position
	uint16_t saucerTopY = SAUCER_Y_POSITION; //Top position
	uint16_t saucerBottomY = saucerTopY + SAUCER_HEIGHT;
	if(((some_point.x >= leftSaucerX) && (some_point.x <= rightSacuerX)) && ((some_point.y >= saucerTopY) && (some_point.y <= saucerBottomY))){
		tank_killed_saucer = true; //Tank killed saucer
		setDidTankKillSaucerFlag(true);
		getNewPosition = true; //get new position
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
	if(getNewPosition){
		x_position = getSaucerPosition(); //Get the saucer position
		getNewPosition = false;
	}
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

void eraseSaucer(){
	sound_saucer_stop();
	sound_init_saucer_hit();
	uint16_t x_position = getSaucerPosition();
	setSaucerDeathPosition(x_position); //Set the saucer death position
	uint8_t line, pixel;
	for(line = 0; line < SAUCER_HEIGHT; line++){ // We only need to overwrite a few pixels within a 4x4 area
		for(pixel = 0; pixel < SAUCER_WIDTH; pixel++){ //For width
			if(frame_pointer[(line + SAUCER_Y_POSITION)*SCREEN_WIDTH + (pixel + x_position)] == RED){
				frame_pointer[(line + SAUCER_Y_POSITION)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
			}
		}
	}
	if(saucer_move_right){
		saucer_move_right = false; //Turn move right off
		setSaucerPosition(SAUCER_MAX_X_POSITION);
	}
	else{
		saucer_move_right = true; //Turn move right on
		setSaucerPosition(SAUCER_MIN_X_POSITION); //Set the position of the saucer
	}
}

bool drawSaucer(){
	sound_init_saucer_move();
	uint8_t line, pixel;
	int16_t x_position = update_saucer_x_position();
	//xil_printf("Draw saucer at x is : %d and y is : %d \n\r", x_position, SAUCER_Y_POSITION);
	setSaucerPosition(x_position);
	if((x_position == SAUCER_MAX_X_POSITION) || (x_position == SAUCER_MIN_X_POSITION)){
		return false; // We need to stop the draw saucer functionality now that we have gone off the board.
	}
	if(x_position < LEFT_BORDER){ // We have some partial drawing to do when it gets to the left border.
		sound_saucer_stop();
		for(line = 0; line < SAUCER_HEIGHT; line++){ //For height
			for(pixel = 0; pixel < SAUCER_WIDTH; pixel++){ // So we need to do a smaller width because we are only drawing some of the saucer.
				if((pixel + x_position) >= RESET){
					if((saucer_symbol[line] & (SHIFT<<(SAUCER_WIDTH-SHIFT-pixel)))){ //If pixel is a 1
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
			//sound_saucer_stop();
			eraseExtraSaucerBits(x_position); //Erase extra bits of the saucer
		}
	}
	else if(x_position > (RIGHT_BORDER - SAUCER_WIDTH)){ // We have some partial drawing to do when it gets to the right border.
		sound_saucer_stop();
		for(line = 0; line < SAUCER_HEIGHT; line++){ //For height
			for(pixel = 0; pixel < (SCREEN_WIDTH - x_position); pixel++){ //For width
				if((saucer_symbol[line] & (SHIFT<<(SAUCER_WIDTH-SHIFT-pixel)))){ //If pixel is a 1
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
			//sound_saucer_stop();
			eraseExtraSaucerBits(x_position); //Erase extra bits of the saucer
		}
	}
	else{ // Erasing and drawing for normal operation.
		for(line = 0; line < SAUCER_HEIGHT; line++){ //For height
			for(pixel = 0; pixel < SAUCER_WIDTH; pixel++){ //For width
				if((saucer_symbol[line] & (SHIFT<<(SAUCER_WIDTH-SHIFT-pixel)))){ //Pixel is a 1
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
		eraseExtraSaucerBits(x_position); //Erase the extra bits of saucer
	}
	return true;
}
