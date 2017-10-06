/*
 * draw.c
 *
 *  Created on: Oct 5, 2017
 *      Author: superman
 */

#include "draw.h"
#include "images.h"

#define FRAME_BUFFER_0_ADDR_BASE 0xC1000000  // Starting location in DDR where we will store the images that we display.

#define RED 0x00FF0000 // Hexadecimal color value for Red
#define GREEN 0x0000FF00 // Hexadecimal color value for Green
#define WHITE 0x00FFFFFF // Hexadecimal color value for White
#define BLACK 0x00000000 // Hexadecimal color value for Black

#define GROUND_LEVEL 459

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

#define TANK_Y_POSITION 423
#define TANK_INITIAL_X_POSITION 304
#define MOVE_LEFT 4
#define MOVE_RIGHT 26
#define MOVE 4

#define LIFE_1_X_POSITION 449
#define LIFE_2_X_POSITION 489
#define LIFE_3_X_POSITION 529
#define LIFE_Y_POSITION 5

#define BUNKER_X_OFFSET BUNKER_BLOCK_WORD_WIDTH
#define BUNKER_Y_OFFSET BUNKER_BLOCK_HEIGHT
#define BUNKER_NUMBER_BLOCKS_X 4
#define BUNKER_NUMBER_BLOCKS_Y 3
#define BUNKER_NUMBER_TOTAL_BLOCKS 12
#define BUNKER_ROW_1 4
#define BUNKER_ROW_2 8
#define BUNKER_ROW_3 12
#define BUNKER_1_X_POSITION 104
#define BUNKER_2_X_POSITION	232
#define BUNKER_3_X_POSITION 360
#define BUNKER_4_X_POSITION	488
#define BUNKER_Y_POSITION 367
#define BUNKER_DEAD_BLOCK 4
#define BUNKER_DAMAGE_1 1
#define BUNKER_DAMAGE_2 2
#define BUNKER_DAMAGE_3 3
#define BUNKER_DAMAGE_4 4

#define ALIEN_INITIAL_X_POSITION 144
#define ALIEN_INITIAL_Y_POSITION 51
#define ALIEN_X_OFFSET ALIEN_WORD_WIDTH
#define ALIEN_Y_OFFSET (ALIEN_HEIGHT + 8)
#define ALIEN_AMOUNT 55
#define SQUID_IN 1
#define SQUID_OUT 2
#define BUG_IN 3
#define BUG_OUT 4
#define JELLYFISH_IN 5
#define JELLYFISH_OUT 6
#define ALIEN_MAX_COL 11
#define ALIEN_ROW_1 11
#define ALIEN_ROW_2 22
#define ALIEN_ROW_3 33
#define ALIEN_ROW_4 44
#define ALIEN_ROW_5 55
#define ALIEN_ROW_2_OFFSET 1
#define ALIEN_ROW_3_OFFSET 2
#define ALIEN_ROW_4_OFFSET 3
#define ALIEN_ROW_5_OFFSET 4
#define ALIEN_ERASE 0
#define ALIEN_MOVE_HORIZONTAL 2
#define ALIEN_MOVE_VERTICAL 20


unsigned int * frame_pointer = (unsigned int *) FRAME_BUFFER_0_ADDR_BASE;

static uint8_t alien_block[ALIEN_AMOUNT] = {1,1,1,1,1,1,1,1,1,1,1, \
		                                    1,1,1,1,1,1,1,1,1,1,1, \
		                                    1,1,1,1,1,1,1,1,1,1,1, \
		                                    1,1,1,1,1,1,1,1,1,1,1, \
		                                    1,1,1,1,1,1,1,1,1,1,1};

static uint8_t bunker_1_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,4,4,0};
static uint8_t bunker_2_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,4,4,0};
static uint8_t bunker_3_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,4,4,0};
static uint8_t bunker_4_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,4,4,0};

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

void setAlienBulletPosition(point_t val){

}

point_t getAlienBulletPosition(){

}

point_t calculateAlienPosition(uint8_t alien_number){

	point_t position = getAlienBlockPosition();

	// Get the y_position for all the aliens.
    if((alien_number >= ALIEN_ROW_1) && (alien_number < ALIEN_ROW_2)){
		position.y += (ALIEN_Y_OFFSET * ALIEN_ROW_2_OFFSET);
	}
	else if((alien_number >= ALIEN_ROW_2) && (alien_number < ALIEN_ROW_3)){
		position.y += (ALIEN_Y_OFFSET * ALIEN_ROW_3_OFFSET);
	}
	else if((alien_number >= ALIEN_ROW_3) && (alien_number < ALIEN_ROW_4)){
		position.y += (ALIEN_Y_OFFSET * ALIEN_ROW_4_OFFSET);
	}
	else if((alien_number >= ALIEN_ROW_4) && (alien_number < ALIEN_ROW_5)){
		position.y += (ALIEN_Y_OFFSET * ALIEN_ROW_5_OFFSET);
	}

	// Get the x_position for all the aliens.
	position.x += (alien_number % ALIEN_MAX_COL)*ALIEN_X_OFFSET;

	return position;
}

void killAlien(uint8_t alien_number){

	point_t position = calculateAlienPosition(alien_number);
	uint16_t x_position = position.x;
	uint16_t y_position = position.y;

	alien_block[alien_number] = ALIEN_ERASE;
	uint8_t line, pixel;
    for(line = 0; line < ALIEN_HEIGHT; line++){
    	for(pixel = 0; pixel < ALIEN_WORD_WIDTH; pixel++){
    		if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] != BLACK){
    			frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK;
    		}
    	}
    }
}

void drawAlien(uint16_t x_position, uint16_t y_position, uint8_t alien_type){
    uint8_t line, pixel;
    for(line = 0; line < ALIEN_HEIGHT; line++){
    	for(pixel = 0; pixel < ALIEN_WORD_WIDTH; pixel++){
    		if(alien_type == SQUID_IN){
    			if((squid_step_in_symbol[line] & (1<<(ALIEN_WORD_WIDTH-1-pixel)))){
    				if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] != WHITE){
    					frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = WHITE;
    				}
    			}
    			else{
    				if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == WHITE){
    					frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK;
    				}
    			}
    		}
    		else if(alien_type == SQUID_OUT){
    			if((squid_step_out_symbol[line] & (1<<(ALIEN_WORD_WIDTH-1-pixel)))){
    				if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] != WHITE){
    					frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = WHITE;
    				}
    			}
    			else{
    				if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == WHITE){
    					frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK;
    				}
    			}
    		}
    		else if(alien_type == BUG_IN){
    			if((bug_step_in_symbol[line] & (1<<(ALIEN_WORD_WIDTH-1-pixel)))){
    				if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] != WHITE){
    					frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = WHITE;
    				}
    			}
    			else{
    				if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == WHITE){
    					frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK;
    				}
    			}
    		}
    		else if(alien_type == BUG_OUT){
    			if((bug_step_out_symbol[line] & (1<<(ALIEN_WORD_WIDTH-1-pixel)))){
    				if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] != WHITE){
    					frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = WHITE;
    				}
    			}
    			else{
    				if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == WHITE){
    					frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK;
    				}
    			}
    		}
    		else if(alien_type == JELLYFISH_IN){
    			if((jellyfish_step_in_symbol[line] & (1<<(ALIEN_WORD_WIDTH-1-pixel)))){
    				if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] != WHITE){
    					frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = WHITE;
    				}
    			}
    			else{
    				if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == WHITE){
    					frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK;
    				}
    			}
    		}
    		else if(alien_type == JELLYFISH_OUT){
    			if((jellyfish_step_out_symbol[line] & (1<<(ALIEN_WORD_WIDTH-1-pixel)))){
    				if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] != WHITE){
    					frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = WHITE;
    				}
    			}
    			else{
    				if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == WHITE){
    					frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK;
    				}
    			}
    		}
    	}
    }
}

void updateAlienPosition(){
	point_t alien_position = getAlienBlockPosition();
	alien_position.x += ALIEN_MOVE_HORIZONTAL;
	setAlienBlockPosition(alien_position);
}

void drawAlienBlock(){
	static uint8_t alien_step_out = 0;
	if(alien_step_out){
		alien_step_out = 0;
	}
	else{
		alien_step_out = 1;
	}

	uint8_t alien_number;
	uint8_t alien_type;
	for(alien_number = 0; alien_number < ALIEN_AMOUNT; alien_number++){
		// Get which type of alien we are drawing.
		if(alien_step_out){
			if(alien_number < ALIEN_ROW_1){
				alien_type = SQUID_OUT;
			}
			else if((alien_number >= ALIEN_ROW_1) && (alien_number < ALIEN_ROW_3)){

				alien_type = BUG_OUT;
			}
			else if((alien_number >= ALIEN_ROW_3) && (alien_number < ALIEN_ROW_5)){

				alien_type = JELLYFISH_OUT;
			}
		}
		else{
			if(alien_number < ALIEN_ROW_1){
				alien_type = SQUID_IN;
			}
			else if((alien_number >= ALIEN_ROW_1) && (alien_number < ALIEN_ROW_3)){

				alien_type = BUG_IN;
			}
			else if((alien_number >= ALIEN_ROW_3) && (alien_number < ALIEN_ROW_5)){

				alien_type = JELLYFISH_IN;
			}
		}

		point_t position = calculateAlienPosition(alien_number);
		uint16_t alien_x_position = position.x;
		uint16_t alien_y_position = position.y;
		// Draw the alien.
		if(alien_block[alien_number]){
			drawAlien(alien_x_position, alien_y_position, alien_type);
		}
	}

	updateAlienPosition();
}

void erodeBunker(uint8_t bunker_number, uint8_t block_number){
	uint16_t x_position, y_position;

	uint8_t erosion_number;

	// Set the initial y_position
	y_position = BUNKER_Y_POSITION;

	// Set the initial x_position and increment the appropriate damage for the bunker
	if(bunker_number == BUNKER_1){
		if(bunker_1_block_erosion[block_number] < BUNKER_DEAD_BLOCK){
			erosion_number = bunker_1_block_erosion[block_number];
			bunker_1_block_erosion[block_number] = ++erosion_number;
		}
		x_position = BUNKER_1_X_POSITION;
	}
	else if(bunker_number == BUNKER_2){
		if(bunker_2_block_erosion[block_number] < BUNKER_DEAD_BLOCK){
			erosion_number = bunker_2_block_erosion[block_number];
			bunker_2_block_erosion[block_number] = ++erosion_number;
		}
		x_position = BUNKER_2_X_POSITION;
	}
	else if(bunker_number == BUNKER_3){
		if(bunker_3_block_erosion[block_number] < BUNKER_DEAD_BLOCK){
			erosion_number = bunker_3_block_erosion[block_number];
			bunker_3_block_erosion[block_number] = ++erosion_number;
		}
		x_position = BUNKER_3_X_POSITION;
	}
	else if(bunker_number == BUNKER_4){
		if(bunker_4_block_erosion[block_number] < BUNKER_DEAD_BLOCK){
			erosion_number = bunker_4_block_erosion[block_number];
			bunker_4_block_erosion[block_number] = ++erosion_number;
		}
		x_position = BUNKER_4_X_POSITION;
	}

	// Calculate the x offset.
	x_position += (block_number % BUNKER_NUMBER_BLOCKS_X) * BUNKER_X_OFFSET;

	// Calculate the y offset
	if((block_number >= BUNKER_ROW_1) && (block_number < BUNKER_ROW_2)){
		y_position += BUNKER_Y_OFFSET;
	}
	else if((block_number >= BUNKER_ROW_2) && (block_number < BUNKER_ROW_3)){
		y_position += BUNKER_Y_OFFSET + BUNKER_Y_OFFSET;
	}

	// Actually erode the appropriate bunker.
	uint8_t line, pixel;
    for(line = 0; line < BUNKER_BLOCK_HEIGHT; line++){
    	for(pixel = 0; pixel < BUNKER_BLOCK_WORD_WIDTH; pixel++){
    		if(erosion_number == BUNKER_DAMAGE_1){
        		if(!(bunker_damage_1[line] & (1<<(BUNKER_BLOCK_WORD_WIDTH-1-pixel)))){
        			if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == GREEN){
        				frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK;
        			}
        		}
    		}
    		else if(erosion_number == BUNKER_DAMAGE_2){
        		if(!(bunker_damage_2[line] & (1<<(BUNKER_BLOCK_WORD_WIDTH-1-pixel)))){
        			if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == GREEN){
        				frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK;
        			}
        		}
    		}
    		else if(erosion_number == BUNKER_DAMAGE_3){
        		if(!(bunker_damage_3[line] & (1<<(BUNKER_BLOCK_WORD_WIDTH-1-pixel)))){
        			if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == GREEN){
        				frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK;
        			}
        		}
    		}
    		else if(erosion_number == BUNKER_DAMAGE_4){
    			if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == GREEN){
    				frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK;
    			}
    		}

    	}
    }

}

void drawBunker(uint16_t x_position, uint16_t y_position){
    uint8_t line, pixel;
    for(line = 0; line < BUNKER_HEIGHT; line++){
    	for(pixel = 0; pixel < BUNKER_WORD_WIDTH; pixel++){
    		if((bunker_left_half[line] & (1<<(BUNKER_WORD_WIDTH-1-pixel)))){
    			frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = GREEN;
    		}
    		if((bunker_right_half[line] & (1<<(BUNKER_WORD_WIDTH-1-pixel)))){
    			frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + BUNKER_WORD_WIDTH + x_position)] = GREEN;
    		}
    	}
    }
}

void drawTank(uint8_t direction){

	if(direction == TANK_LEFT){
		// Move the tank left.
		setTankPosition(getTankPosition() - MOVE);
	}
	else if(direction == TANK_RIGHT){
		// Move the tank left.
		setTankPosition(getTankPosition() + MOVE);
	}

    uint8_t line, pixel;
    for(line = 0; line < TANK_HEIGHT; line++){
    	for(pixel = 0; pixel < TANK_WORD_WIDTH; pixel++){
    		// Stuff to do to move the tank left
    		if(direction == TANK_LEFT){
    			// Draw the left side of the moving tank
        		if((tank_symbol[line] & (1<<(TANK_WORD_WIDTH-1-pixel)))){
        			if(frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] == BLACK){
        				frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] = GREEN;
        			}
        		}
        		else{
        			if(frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] == GREEN){
        				frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] = BLACK;
        			}
        		}
        		// Erase the right side of the moving tank
        		if(pixel >= (TANK_WORD_WIDTH - MOVE_LEFT)){
        			frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + MOVE + getTankPosition())] = BLACK;
        		}
    		}
    		// Stuff to do to move the tank right
    		else if(direction == TANK_RIGHT){
    			// Draw the Right side of the moving tank
    			if((tank_symbol[line] & (1<<(TANK_WORD_WIDTH-1-pixel)))){
        			if(frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] == BLACK){
        				frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] = GREEN;
        			}
    			}
        		else{
        			if(frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] == GREEN){
        				frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] = BLACK;
        			}
        		}
    			// Erase the left side of the moving tank
    			if(pixel < (TANK_WORD_WIDTH - MOVE_RIGHT)){
    				frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel - MOVE + getTankPosition())] = BLACK;
    			}
    		}
    	}
    }
}

void drawLife(uint16_t x_position, uint16_t y_position){
    uint8_t line, pixel;
    for(line = 0; line < TANK_HEIGHT; line++){
    	for(pixel = 0; pixel < TANK_WORD_WIDTH; pixel++){
    		if((tank_symbol[line] & (1<<(TANK_WORD_WIDTH-1-pixel)))){
    			frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = GREEN;
    		}
    	}
    }
}

unsigned int * draw_start_screen(){

	setTankPosition(TANK_INITIAL_X_POSITION);

    uint16_t row=0, col=0;
    for( row=0; row<480; row++) {
    	for(col=0; col<640; col++) {
    		if(row == GROUND_LEVEL || row == (GROUND_LEVEL + 1)){
    			frame_pointer[row*SCREEN_WIDTH + col] = GREEN;
    		}
    		else{
    			frame_pointer[row*SCREEN_WIDTH + col] = BLACK;
    		}
    	}
    }

    uint16_t tank_position;
    tank_position = TANK_INITIAL_X_POSITION;
    setTankPosition(tank_position);
    drawLife(TANK_INITIAL_X_POSITION, TANK_Y_POSITION);
    drawLife(LIFE_1_X_POSITION, LIFE_Y_POSITION);
    drawLife(LIFE_2_X_POSITION, LIFE_Y_POSITION);
    drawLife(LIFE_3_X_POSITION, LIFE_Y_POSITION);
    drawBunker(BUNKER_1_X_POSITION, BUNKER_Y_POSITION);
    drawBunker(BUNKER_2_X_POSITION, BUNKER_Y_POSITION);
    drawBunker(BUNKER_3_X_POSITION, BUNKER_Y_POSITION);
    drawBunker(BUNKER_4_X_POSITION, BUNKER_Y_POSITION);

    point_t alien_block_position;
    alien_block_position.x = ALIEN_INITIAL_X_POSITION;
    alien_block_position.y = ALIEN_INITIAL_Y_POSITION;
    setAlienBlockPosition(alien_block_position);
    drawAlienBlock();

    return frame_pointer;
}
