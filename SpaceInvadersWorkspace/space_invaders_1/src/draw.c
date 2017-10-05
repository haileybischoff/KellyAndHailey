/*
 * draw.c
 *
 *  Created on: Oct 5, 2017
 *      Author: superman
 */

#include "draw.h"
#include "images.h"

#define FRAME_BUFFER_0_ADDR 0xC0000000  // Starting location in DDR where we will store the images that we display.

#define RED 0x00FF0000 // Hexadecimal color value for Red
#define GREEN 0x0000FF00 // Hexadecimal color value for Green
#define WHITE 0x00FFFFFF // Hexadecimal color value for White
#define BLACK 0x00000000 // Hexadecimal color value for Black

#define GROUND_LEVEL 459
#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640
#define TANK_Y_POSITION 423
#define TANK_INITIAL_X_POSITION 314
#define LIFE_1_X_POSITION 449
#define LIFE_2_X_POSITION 489
#define LIFE_3_X_POSITION 529
#define LIFE_Y_POSITION 5
#define BUNKER_X_OFFSET BUNKER_WORD_WIDTH
#define BUNKER_Y_OFFSET BUNKER_BLOCK_HEIGHT
#define NUMBER_BUNKER_BLOCKS_X 4
#define NUMBER_BUNKER_BLOCKS_Y 3
#define BUNKER_1_X_POSITION 104
#define BUNKER_2_X_POSITION	232
#define BUNKER_3_X_POSITION 360
#define BUNKER_4_X_POSITION	488
#define BUNKER_Y_POSITION 367

unsigned int * start_frame_pointer = (unsigned int *) FRAME_BUFFER_0_ADDR;

static uint16_t tankPosition;
static point_t tankBulletPosition;
static point_t alienBlockPosition;

void setTankPosition(uint16_t val){
	tankPosition = val;
}

uint16_t getTankPosition(){
	return tankPosition;
}

void setTankBulletPosition(point_t val){
	tankBulletPosition.x = val.x;
	tankBulletPosition.y = val.y;
}

point_t getTankBulletPosition(){
	return tankBulletPosition;
}

void setAlienBlockPosition(point_t val){
	alienBlockPosition.x = val.x;
	alienBlockPosition.y = val.y;
}

point_t getAlienBlockPosition(){
	return alienBlockPosition;
}

void drawBunker(uint32_t x_position, uint16_t y_position){
    uint32_t line, pixel;
    for(line = 0; line < BUNKER_HEIGHT; line++){
    	for(pixel = 0; pixel < BUNKER_WORD_WIDTH; pixel++){
    		if((bunker_left_half[line] & (1<<(BUNKER_WORD_WIDTH-1-pixel)))){
    			start_frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = GREEN;
    		}
    		if((bunker_right_half[line] & (1<<(BUNKER_WORD_WIDTH-1-pixel)))){
    			start_frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + BUNKER_WORD_WIDTH + x_position)] = GREEN;
    		}
    	}
    }
}

void drawTank(uint32_t x_position, uint16_t y_position){
    uint32_t line, pixel;
    for(line = 0; line < TANK_HEIGHT; line++){
    	for(pixel = 0; pixel < TANK_WORD_WIDTH; pixel++){
    		if((tank_symbol[line] & (1<<(TANK_WORD_WIDTH-1-pixel)))){
    			start_frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = GREEN;
    		}
    	}
    }
}

unsigned int * draw_start_screen(){

	unsigned int * start_frame_pointer = (unsigned int *) FRAME_BUFFER_0_ADDR;

	setTankPosition(TANK_INITIAL_X_POSITION);

    int row=0, col=0;
    for( row=0; row<480; row++) {
    	for(col=0; col<640; col++) {
    		if(row == GROUND_LEVEL || row == (GROUND_LEVEL + 1)){
    			start_frame_pointer[row*SCREEN_WIDTH + col] = GREEN;
    		}
    		else{
    			start_frame_pointer[row*SCREEN_WIDTH + col] = BLACK;
    		}
    	}
    }

    drawTank(TANK_INITIAL_X_POSITION, TANK_Y_POSITION);
    drawTank(LIFE_1_X_POSITION, LIFE_Y_POSITION);
    drawTank(LIFE_2_X_POSITION, LIFE_Y_POSITION);
    drawTank(LIFE_3_X_POSITION, LIFE_Y_POSITION);
    drawBunker(BUNKER_1_X_POSITION, BUNKER_Y_POSITION);
    drawBunker(BUNKER_2_X_POSITION, BUNKER_Y_POSITION);
    drawBunker(BUNKER_3_X_POSITION, BUNKER_Y_POSITION);
    drawBunker(BUNKER_4_X_POSITION, BUNKER_Y_POSITION);

    return start_frame_pointer;
}
