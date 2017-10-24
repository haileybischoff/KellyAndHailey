/*
 * draw_bunker.c
 *
 *  Created on: Oct 21, 2017
 *      Author: superman
 */

#include <stdbool.h>
#include "draw_bunker.h"
#include "images.h"

#define BUNKER_X_OFFSET BUNKER_BLOCK_WORD_WIDTH //Bunker x offset
#define BUNKER_Y_OFFSET BUNKER_BLOCK_HEIGHT //Bunker y offset
#define BUNKER_NUMBER_BLOCKS_X 4 //Number of x bunker blocks
#define BUNKER_NUMBER_BLOCKS_Y 3 //Number of y bunker blocks
#define BUNKER_NUMBER_TOTAL_BLOCKS 12 //Total number of bunker blocks
#define BUNKER_ROW_1 4 //The first row of bunker blocks
#define BUNKER_ROW_2 8 //The second row of bunker blocks
#define BUNKER_ROW_3 12 //The third row of bunker blocks
#define BUNKER_1_X_MAX_POSITION BUNKER_1_X_POSITION + FULL_BUNKER_WORD_WIDTH //First bunker x position
#define BUNKER_2_X_MAX_POSITION	BUNKER_2_X_POSITION + FULL_BUNKER_WORD_WIDTH//Second bunker x position
#define BUNKER_3_X_MAX_POSITION BUNKER_3_X_POSITION + FULL_BUNKER_WORD_WIDTH//Third bunker x position
#define BUNKER_4_X_MAX_POSITION	BUNKER_4_X_POSITION + FULL_BUNKER_WORD_WIDTH//Fourth bunker x position
#define BUNKER_Y_BOTTOM_POSITION BUNKER_Y_POSITION + BUNKER_HEIGHT //Y position for bunkers
#define BUNKER_DEAD_BLOCK 4 //Dead bunker block
#define BUNKER_DAMAGE_1 0 //Bunker damage 1
#define BUNKER_DAMAGE_2 1 //Bunker damage 2
#define BUNKER_DAMAGE_3 2 //Bunker damage 3
#define BUNKER_DAMAGE_4 3 //Bunker damage 4

static uint8_t bunker_1_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,3,3,0};
static uint8_t bunker_2_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,3,3,0};
static uint8_t bunker_3_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,3,3,0};
static uint8_t bunker_4_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,3,3,0};

static point_t bunker_shot;

static bool tank_killed_bunker = false;
static bool alien_killed_bunker = false;

extern unsigned int * frame_pointer;

void setShotBunkerPosition(point_t bunkerPosition){
	bunker_shot.x = bunkerPosition.x;
	bunker_shot.y = bunkerPosition.y;
}

point_t getShotBunkerPosition(){
	return bunker_shot;
}

uint8_t getErosionStage(uint8_t bunkerNum, uint8_t blockNumber){
	if(bunkerNum == BUNKER1){
		return bunker_1_block_erosion[blockNumber];
	}
	else if(bunkerNum  == BUNKER2){
		return bunker_2_block_erosion[blockNumber];
	}
	else if(bunkerNum == BUNKER3){
		return bunker_3_block_erosion[blockNumber];
	}
	else{
		return bunker_4_block_erosion[blockNumber];
	}
}

uint8_t calculateBlockNumber(uint8_t bunkerNum, point_t bunkerPosition){
	uint8_t answer = WRONG_BUNKER; //
	uint16_t left_edge;
	if(bunkerNum == 0){
		left_edge = BUNKER_1_X_POSITION;
	}
	else if(bunkerNum == 1){
		left_edge = BUNKER_2_X_POSITION;
	}
	else if(bunkerNum == 2){
		left_edge = BUNKER_3_X_POSITION;
	}
	else if(bunkerNum == 3){
		left_edge = BUNKER_4_X_POSITION;
	}
	uint8_t row, col;
	for(row = 0; row < 3; row++){
		uint16_t topOfBunkerBlock = BUNKER_Y_POSITION + (BUNKER_BLOCK_HEIGHT * row);
		uint16_t bottomOfBunkerBlock = BUNKER_Y_POSITION + (BUNKER_BLOCK_HEIGHT * (row + 1));
		if((bunkerPosition.y >= topOfBunkerBlock) && (bunkerPosition.y < bottomOfBunkerBlock)){
			for(col = 0; col < 4; col++){
				uint16_t left_of_block = left_edge + (col * BUNKER_BLOCK_WORD_WIDTH);
				uint16_t right_of_block = left_edge + ((col + 1) * BUNKER_BLOCK_WORD_WIDTH);
				if((bunkerPosition.x >= left_of_block) && (bunkerPosition.x < right_of_block)){
					return ((row*4) + col);
				}
			}
		}
	}
	return answer;
}

uint8_t calculateBunkerNumber(point_t bunkerPosition){
	uint8_t answer = WRONG_BUNKER; //
	if(((bunkerPosition.x >= BUNKER_1_X_POSITION) && (bunkerPosition.x <= BUNKER_1_X_MAX_POSITION)) && ((bunkerPosition.y >= BUNKER_Y_POSITION) &&(bunkerPosition.y <= BUNKER_Y_BOTTOM_POSITION))){
		return BUNKER1;
	}
	else if(((bunkerPosition.x >= BUNKER_2_X_POSITION) && (bunkerPosition.x <= BUNKER_2_X_MAX_POSITION)) &&((bunkerPosition.y >= BUNKER_Y_POSITION) && (bunkerPosition.y <= BUNKER_Y_BOTTOM_POSITION))){
		return BUNKER2;
	}
	else if(((bunkerPosition.x >= BUNKER_3_X_POSITION) && (bunkerPosition.x <= BUNKER_3_X_MAX_POSITION)) && ((bunkerPosition.y >= BUNKER_Y_POSITION) && (bunkerPosition.y <= BUNKER_Y_BOTTOM_POSITION))){
		return BUNKER3;
	}
	else if(((bunkerPosition.x >= BUNKER_4_X_POSITION) && (bunkerPosition.x <= BUNKER_4_X_MAX_POSITION)) && ((bunkerPosition.y >= BUNKER_Y_POSITION) && (bunkerPosition.y <= BUNKER_Y_BOTTOM_POSITION))){
		return BUNKER4;
	}
	else{
		return answer;//TODO random number
	}
}

uint8_t didTankKillBunker(){
	return tank_killed_bunker;
}

uint8_t didAlienKillBunker(){
	return alien_killed_bunker;
}

void setDidTankKillBunkerFlag(bool tankKilledBunkerFlag){
	tank_killed_bunker = tankKilledBunkerFlag;
}

void setDidAlienKillBunkerFlag(bool alienKilledBunkerFlag){
	alien_killed_bunker = alienKilledBunkerFlag;
}

void drawBunker(uint16_t x_position, uint16_t y_position){
	uint8_t line, pixel;
	for(line = 0; line < BUNKER_HEIGHT; line++){ //Height
		for(pixel = 0; pixel < BUNKER_WORD_WIDTH; pixel++){ //Width
			if((bunker_left_half[line] & (SHIFT<<(BUNKER_WORD_WIDTH-SHIFT-pixel)))){
				frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = GREEN; //Set to green
			}
			if((bunker_right_half[line] & (SHIFT<<(BUNKER_WORD_WIDTH-SHIFT-pixel)))){
				frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + BUNKER_WORD_WIDTH + x_position)] = GREEN; //Set to green
			}
		}
	}
}

void eraseBunkers(){
	uint8_t number;
	for(number = 0; number < 4; number++){
		point_t bunker;
		bunker.y = BUNKER_Y_POSITION;
		if(number == 0){
			bunker.x = BUNKER_1_X_POSITION;
		}
		else if(number == 1){
			bunker.x = BUNKER_2_X_POSITION;
		}
		else if(number == 2){
			bunker.x = BUNKER_3_X_POSITION;
		}
		else {
			bunker.x = BUNKER_4_X_POSITION;
		}
		uint8_t line, pixel;
		for(line = 0; line < BUNKER_HEIGHT; line++){ //Height
			for(pixel = 0; pixel < BUNKER_WORD_WIDTH; pixel++){ //Width
				if((bunker_left_half[line] & (SHIFT<<(BUNKER_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + bunker.y)*SCREEN_WIDTH + (pixel + bunker.x)] != BLACK){ //Set to green
						frame_pointer[(line + bunker.y)*SCREEN_WIDTH + (pixel + bunker.x)] = BLACK; //Set to green
					}
				}
				if((bunker_right_half[line] & (SHIFT<<(BUNKER_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + bunker.y)*SCREEN_WIDTH + (pixel + BUNKER_WORD_WIDTH + bunker.x)] != BLACK){
						frame_pointer[(line + bunker.y)*SCREEN_WIDTH + (pixel + BUNKER_WORD_WIDTH + bunker.x)] = BLACK; //Set to green
					}
				}
			}
		}
	}
}

void erodeBunker(uint8_t bunker_number, uint8_t block_number){
	uint16_t x_position, y_position;
	uint8_t erosion_number;
	// Set the initial y_position
	y_position = BUNKER_Y_POSITION;
	// Set the initial x_position and increment the appropriate damage for the bunker
	if(bunker_number == BUNKER_1){ //Bunker 1
		if(bunker_1_block_erosion[block_number] < BUNKER_DEAD_BLOCK){
			erosion_number = bunker_1_block_erosion[block_number];
			bunker_1_block_erosion[block_number] = ++erosion_number; //Increment erosion
		}
		x_position = BUNKER_1_X_POSITION;
	}
	else if(bunker_number == BUNKER_2){ //Bunker 2
		if(bunker_2_block_erosion[block_number] < BUNKER_DEAD_BLOCK){
			erosion_number = bunker_2_block_erosion[block_number];
			bunker_2_block_erosion[block_number] = ++erosion_number; //Increment erosion
		}
		x_position = BUNKER_2_X_POSITION;
	}
	else if(bunker_number == BUNKER_3){ //Bunker 3
		if(bunker_3_block_erosion[block_number] < BUNKER_DEAD_BLOCK){
			erosion_number = bunker_3_block_erosion[block_number];
			bunker_3_block_erosion[block_number] = ++erosion_number; //Increment erosion
		}
		x_position = BUNKER_3_X_POSITION;
	}
	else if(bunker_number == BUNKER_4){ //Bunker 4
		if(bunker_4_block_erosion[block_number] < BUNKER_DEAD_BLOCK){
			erosion_number = bunker_4_block_erosion[block_number];
			bunker_4_block_erosion[block_number] = ++erosion_number; //Increment erosion
		}
		x_position = BUNKER_4_X_POSITION;
	}
	// Calculate the x offset.
	x_position += (block_number % BUNKER_NUMBER_BLOCKS_X) * BUNKER_X_OFFSET;
	// Calculate the y offset
	if((block_number >= BUNKER_ROW_1) && (block_number < BUNKER_ROW_2)){
		y_position += BUNKER_Y_OFFSET; //Set y position
	}
	else if((block_number >= BUNKER_ROW_2) && (block_number < BUNKER_ROW_3)){
		y_position += BUNKER_Y_OFFSET + BUNKER_Y_OFFSET; //Set y position
	}
	// Actually erode the appropriate bunker.
	uint8_t line, pixel;
	for(line = 0; line < BUNKER_BLOCK_HEIGHT; line++){ //Height
		for(pixel = 0; pixel < BUNKER_BLOCK_WORD_WIDTH; pixel++){ //Width
			if(erosion_number == BUNKER_DAMAGE_1){ //Bunker damage 1
				if(!(bunker_damage_1[line] & (SHIFT<<(BUNKER_BLOCK_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == GREEN){
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
					}
				}
			}
			else if(erosion_number == BUNKER_DAMAGE_2){ //Bunker damage 2
				if(!(bunker_damage_2[line] & (SHIFT<<(BUNKER_BLOCK_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == GREEN){
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
					}
				}
			}
			else if(erosion_number == BUNKER_DAMAGE_3){ //Bunker damage 3
				if(!(bunker_damage_3[line] & (SHIFT<<(BUNKER_BLOCK_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == GREEN){
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
					}
				}
			}
			else if(erosion_number == BUNKER_DAMAGE_4){ //Bunker damage 4
				if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == GREEN){
					frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
				}
			}
		}
	}
}
