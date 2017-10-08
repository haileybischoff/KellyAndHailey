/*
 * draw.c
 *
 *  Created on: Oct 5, 2017
 *      Author: superman
 */

#include "draw.h"
#include "images.h"

#define FRAME_BUFFER_0_ADDR_BASE 0xC1000000  // Starting location in DDR where we will store the images that we display.

#define TRUE 1
#define FALSE 0

#define RED 0x00FF0000 // Hexadecimal color value for Red
#define GREEN 0x0000FF00 // Hexadecimal color value for Green
#define WHITE 0x00FFFFFF // Hexadecimal color value for White
#define BLACK 0x00000000 // Hexadecimal color value for Black

#define GROUND_LEVEL 459
#define LEFT_BORDER 0
#define RIGHT_BORDER

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

#define TANK_Y_POSITION 423
#define TANK_INITIAL_X_POSITION 304
#define TANK_RIGHT_BORDER SCREEN_WIDTH - 32
#define TANK_LEFT_BORDER 0
#define MOVE_LEFT 4
#define MOVE_RIGHT 26
#define MOVE 4

#define LIFE_1_X_POSITION 449
#define LIFE_2_X_POSITION 489
#define LIFE_3_X_POSITION 529
#define LIFE_Y_POSITION 5
#define ALIEN_BULLET_1 1
#define ALIEN_BULLET_2 2
#define ALIEN_BULLET_3 3
#define ALIEN_BULLET_4 4

#define BULLET_TYPE_1 0
#define BULLET_TYPE_2 1

#define CROSS_1 1
#define CROSS_2 2
#define CROSS_3 3
#define ZIGZAG_1 1
#define ZIGZAG_2 2

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
#define BUNKER_DAMAGE_1 0
#define BUNKER_DAMAGE_2 1
#define BUNKER_DAMAGE_3 2
#define BUNKER_DAMAGE_4 3

#define ALIEN_INITIAL_X_POSITION 144
#define ALIEN_INITIAL_Y_POSITION 51
#define ALIEN_X_OFFSET ALIEN_WORD_WIDTH
#define ALIEN_Y_OFFSET (ALIEN_HEIGHT + 8)
#define ALIEN_AMOUNT 55
#define ALIEN_BLOCK_WIDTH 352
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
#define ALIEN_MOVE_VERTICAL 24
#define ALIEN_MIN_LEFT_MOVE_DEFAULT 0
#define ALIEN_MAX_RIGHT_MOVE_DEFAULT 288
#define ALIEN_COLUMN_EMPTY 0
#define ALIEN_NEXT_COL 1

unsigned int * frame_pointer = (unsigned int *) FRAME_BUFFER_0_ADDR_BASE;

static uint8_t alien_block[ALIEN_AMOUNT] = {1,1,1,1,1,1,1,1,1,1,1, \
		1,1,1,1,1,1,1,1,1,1,1, \
		1,1,1,1,1,1,1,1,1,1,1, \
		1,1,1,1,1,1,1,1,1,1,1, \
		1,1,1,1,1,1,1,1,1,1,1};

static uint8_t alien_row_dead[ALIEN_MAX_COL] = {5,5,5,5,5,5,5,5,5,5,5};

static uint8_t bunker_1_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,4,4,0};
static uint8_t bunker_2_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,4,4,0};
static uint8_t bunker_3_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,4,4,0};
static uint8_t bunker_4_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,4,4,0};

static uint16_t tankPosition;

static point_t tankBulletPosition;

static point_t alienBlockPosition;
static point_t alienBulletPosition1;
static point_t alienBulletPosition2;
static point_t alienBulletPosition3;
static point_t alienBulletPosition4;

static uint8_t bullet_1_type;
static uint8_t bullet_2_type;
static uint8_t bullet_3_type;
static uint8_t bullet_4_type;

static uint8_t bullet_1_shot = 0;
static uint8_t bullet_2_shot = 0;
static uint8_t bullet_3_shot = 0;
static uint8_t bullet_4_shot = 0;


static uint8_t alien_bullet_count = 0;

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

void setAlienBulletPosition(point_t val, uint8_t bullet_number){
	if(bullet_number == ALIEN_BULLET_1){
		alienBulletPosition1.x = val.x;
		alienBulletPosition1.y = val.y;
	}
	else if(bullet_number == ALIEN_BULLET_2){
		alienBulletPosition2.x = val.x;
		alienBulletPosition2.y = val.y;
	}
	else if(bullet_number == ALIEN_BULLET_3){
		alienBulletPosition3.x = val.x;
		alienBulletPosition3.y = val.y;
	}
	else if(bullet_number == ALIEN_BULLET_4){
		alienBulletPosition4.x = val.x;
		alienBulletPosition4.y = val.y;
	}
}
point_t getAlienBulletPosition(uint8_t bullet_number){
	if(bullet_number == ALIEN_BULLET_1){
		return alienBulletPosition1;
	}
	else if(bullet_number == ALIEN_BULLET_2){
		return alienBulletPosition2;
	}
	else if(bullet_number == ALIEN_BULLET_3){
		return alienBulletPosition3;
	}
	else{
		return alienBulletPosition4;
	}
}

static uint8_t bullet1_cross;
static uint8_t bullet2_cross;
static uint8_t bullet3_cross;
static uint8_t bullet4_cross;
static uint8_t bullet1_zigzag;
static uint8_t bullet2_zigzag;
static uint8_t bullet3_zigzag;
static uint8_t bullet4_zigzag;
void drawAlienBullet(uint8_t alienNum, uint8_t bullet_type){
	if(alien_bullet_count < 4){ // TODO magic number
		alien_bullet_count++;


		if(alien_bullet_count == ALIEN_BULLET_1){
			if(!bullet_1_shot){
				bullet_1_shot = TRUE;
				bullet_1_type = bullet_type;
				if(bullet_1_type == BULLET_TYPE_1){
					bullet1_cross = CROSS_1;
					bullet1_zigzag = FALSE;
				}
				else{
					bullet1_zigzag = ZIGZAG_1;
					bullet1_cross = FALSE;
				}
			}
		}

		else if(alien_bullet_count == ALIEN_BULLET_2){
			if(!bullet_2_shot){
				bullet_2_shot = TRUE;
				bullet_2_type = bullet_type;
				if(bullet_2_type == BULLET_TYPE_1){
					bullet2_cross = CROSS_1;
					bullet2_zigzag = FALSE;
				}
				else{
					bullet2_zigzag = ZIGZAG_1;
					bullet2_cross = FALSE;
				}
			}
		}

		else if(alien_bullet_count == ALIEN_BULLET_3){
			if(!bullet_3_shot){
				bullet_3_shot = TRUE;
				bullet_3_type = bullet_type;
				if(bullet_3_type == BULLET_TYPE_1){
					bullet3_cross = CROSS_1;
					bullet3_zigzag = FALSE;
				}
				else{
					bullet3_zigzag = ZIGZAG_1;
					bullet3_cross = FALSE;
				}
			}
		}
		else{
			if(!bullet_4_shot){
				bullet_4_shot = 1;
				bullet_4_type = bullet_type;
				if(bullet_4_type == BULLET_TYPE_1){
					bullet4_cross = CROSS_1;
					bullet4_zigzag = FALSE;
				}
				else{
					bullet4_zigzag = ZIGZAG_1;
					bullet4_cross = FALSE;
				}
			}
		}
		point_t myalienPos = calculateAlienPosition(alienNum);
		myalienPos.x += 16; // TODO magic number
		myalienPos.y += 16; // TODO magic number
		setAlienBulletPosition(myalienPos, alien_bullet_count);
		if(bullet_type == BULLET_TYPE_1){
			uint8_t line, pixel;
			for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
				for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
					if((alien_cross_bullet_1[line] & (1<<(ALIEN_CROSS_BULLET_WORD_WIDTH-1-pixel)))){
						frame_pointer[(line + myalienPos.y) * SCREEN_WIDTH + (pixel + myalienPos.x)] = WHITE;
					}
				}
			}
		}
		else if(bullet_type == BULLET_TYPE_2){
			uint8_t line, pixel;
			for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
				for(pixel = 0; pixel < ALIEN_ZIGZAG_BULLET_WORD_WIDTH; pixel++){
					if((alien_zig_zag_bullet_1[line] & (1<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-1-pixel)))){
						frame_pointer[(line + myalienPos.y) * SCREEN_WIDTH + (pixel + myalienPos.x)] = WHITE;
					}
				}
			}
		}
	}
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

uint16_t getLeftAlienBorder(){
	uint16_t left_position = ALIEN_MIN_LEFT_MOVE_DEFAULT;


	return left_position;
}

uint16_t getRightAlienBorder(){
	uint16_t right_position = ALIEN_MAX_RIGHT_MOVE_DEFAULT;
	uint8_t right_most_alive_col;
	for(right_most_alive_col = ALIEN_MAX_COL; right_most_alive_col > 0; right_most_alive_col--){
		if(alien_row_dead[right_most_alive_col - ALIEN_NEXT_COL] != ALIEN_COLUMN_EMPTY){
			break;
		}
	}

	right_position += ((ALIEN_MAX_COL - right_most_alive_col) * ALIEN_WORD_WIDTH);
	xil_printf("right position %d\n\r", right_position);
	return right_position;
}

void killAlien(uint8_t alien_number){
	point_t position = calculateAlienPosition(alien_number);
	uint16_t x_position = position.x;
	uint16_t y_position = position.y;

	uint8_t alien_column = alien_number % ALIEN_MAX_COL;
	uint8_t new_alien_number = alien_row_dead[alien_column];
	if(alien_row_dead[alien_column] != ALIEN_COLUMN_EMPTY){
		alien_row_dead[alien_column] = --new_alien_number;
	}

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

static uint8_t alien_move_right = TRUE; //Start by moving right
static uint8_t alien_step_out = FALSE; //Moved this out of draw alien block so we could use it in other functions
static uint8_t erase_top_row = FALSE;
static point_t last_alien_position;


void eraseTopRowAliens(){
	uint8_t line;
	uint16_t pixel;
	for(line = 0; line < ALIEN_HEIGHT; line++){
		for(pixel = 0; pixel < ALIEN_BLOCK_WIDTH; pixel++){
			if(frame_pointer[(line + last_alien_position.y)*SCREEN_WIDTH + (pixel + last_alien_position.x)] == WHITE){
				frame_pointer[(line + last_alien_position.y)*SCREEN_WIDTH + (pixel + last_alien_position.x)] = BLACK;
			}
		}
	}
}

void updateAlienPosition(){
	point_t alien_position = getAlienBlockPosition();
	last_alien_position = getAlienBlockPosition();

	if(alien_position.x == 0){//TODO //If we hit the left border then change to move right // TODO magic number
		alien_position.y += ALIEN_MOVE_VERTICAL;//This it moves the block down but it doesn't erase the ones that didn't move
		alien_move_right = TRUE;
		erase_top_row = TRUE;
	}
	else if(alien_position.x >= getRightAlienBorder()){//TODO //If we hit the right border then change to move left
		alien_position.y += ALIEN_MOVE_VERTICAL;//This it moves the block down but it doesn't erase the ones that didn't move
		alien_move_right = FALSE;
		erase_top_row = TRUE;
	}

	if(alien_move_right){ //If move right then increment horizontally
		alien_position.x += ALIEN_MOVE_HORIZONTAL; //Hailey just had this
	}
	else{ //Else decrement horizontally
		alien_position.x -= ALIEN_MOVE_HORIZONTAL;
	}

	setAlienBlockPosition(alien_position);
}

void drawAlienBlock(){

	if(alien_step_out){
		alien_step_out = FALSE;
	}
	else{
		alien_step_out = TRUE;
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
	if(erase_top_row){
		eraseTopRowAliens();
		erase_top_row = FALSE;
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

static uint8_t tank_Bullet_Drawn = 0;

void drawTankBullet(){
	if(!tank_Bullet_Drawn){
		tank_Bullet_Drawn = 1; // TODO magic number
		//point_t bullet_from_tank_point = getTankBulletPosition();
		point_t updateBullet;
		updateBullet.x = getTankPosition() + 14; // TODO magic number
		updateBullet.y = TANK_Y_POSITION - 8; // TODO magic number
		setTankBulletPosition(updateBullet);
		uint8_t line, pixel;
		for(line = 0; line < TANK_BULLET_HEIGHT; line++){
			for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){
				//if((tank_bullet[line] & (1<<(TANK_BULLET_WORD_WIDTH-1-pixel)))){//Don't seem to need this line
				frame_pointer[(line + updateBullet.y)*SCREEN_WIDTH + (pixel + updateBullet.x)] = RED; //TODO
				//}
			}
		}
	}


	/* this works. I came up with it on my own.
	point_t bullet_from_tank_point = getTankBulletPosition();
	uint16_t tank_point_bullet_x = getTankPosition() + 15;//TODO //might change
	point_t updateBullet;
	updateBullet.x = tank_point_bullet_x;
	updateBullet.y = 80;
	setTankBulletPosition(updateBullet);
    uint8_t line, pixel;
	for(line = 0; line < 8; line++){
		for(pixel = 0; pixel < 2; pixel++){
			frame_pointer[(line + TANK_Y_POSITION - 8)*SCREEN_WIDTH + (pixel + getTankPosition() + 14)] = RED; //TODO
		}
	}


	 */
}

void drawTank(uint8_t direction){

	if(direction == TANK_LEFT){
		// Move the tank left.
		if(getTankPosition() != TANK_LEFT_BORDER){ //This is to make sure that it doesn't go over to the left of the screen when it is at the edge;
			setTankPosition(getTankPosition() - MOVE);
		}
	}
	else if(direction == TANK_RIGHT){
		// Move the tank left.
		if(getTankPosition() < (TANK_RIGHT_BORDER)){ //This should make sure that the tank doesn't go off the edge of the screen might make it (640-32) instead of (640-30)
			setTankPosition(getTankPosition() + MOVE);
		}
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

uint8_t updateTankBullet(){
	if(tank_Bullet_Drawn){
		point_t old_tank_bullet_position = getTankBulletPosition();
		//if(old_tank_bullet_position.y > 5){//TODO //This line makes it bounce back and forth at the top
		old_tank_bullet_position.y -= (2*MOVE);
		setTankBulletPosition(old_tank_bullet_position);
		//}
		point_t new_tank_bullet_position = getTankBulletPosition();

		uint8_t line, pixel;
		for(line = 0; line < TANK_BULLET_HEIGHT; line++){
			for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){
				if(old_tank_bullet_position.y > 22){
					if(frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] != RED){
						frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = RED;
					}
					//else if(frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == RED){
					//frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = BLACK;
					//}
					if(frame_pointer[(line + 8 + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == RED){ //this if statement does nothing
						frame_pointer[(line + 8 + new_tank_bullet_position.y)*SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = BLACK;//this line does nothing
					}
				}
				else{
					frame_pointer[(line + 8 + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = BLACK;
					tank_Bullet_Drawn = 0;
				}
			}
		}
	}
	return tank_Bullet_Drawn;
}



void updateInvdidualAlienBullet(uint8_t bullet_number){
	//xil_printf("Did we come in here to update for a bullet??\n\r");
	if(bullet_number == ALIEN_BULLET_1){
		//xil_printf("Did we come in here to update for the first bullet??\n\r");
		if(bullet_1_shot > 0){ // TODO magic number
			//xil_printf("Is the first bullet a cross?\n\r");
			point_t old_alien_bullet_position = getAlienBulletPosition(bullet_number);
			old_alien_bullet_position.y += ALIEN_BULLET_HEIGHT;
			setAlienBulletPosition(old_alien_bullet_position, bullet_number);
			point_t new_alien_bullet_position = getAlienBulletPosition(bullet_number);
			if(bullet1_cross > 0){ // TODO magic number
				if(bullet1_cross == CROSS_1){
					//xil_printf("Are we in the first cross position???\n\r");
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_cross_bullet_2[line] & (1<<(ALIEN_CROSS_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									}  // TODO magic number
									if(frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;  // TODO magic number
								bullet_1_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet1_cross++;
				}
				else if(bullet1_cross == CROSS_2){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_cross_bullet_3[line] & (1<<(ALIEN_CROSS_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_1_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet1_cross++;
				}
				else if(bullet1_cross == CROSS_3){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_cross_bullet_1[line] & (1<<(ALIEN_CROSS_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_1_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet1_cross = CROSS_1;
				}

			}
			//if(bullet_1_shot == 0){
			//alien_bullet_count--;
			//}

			if(bullet1_zigzag > 0){
				if(bullet1_zigzag == ZIGZAG_1){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_ZIGZAG_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_zig_zag_bullet_2[line] & (1<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										//frame_pointer[(line - 8 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										//frame_pointer[(line - 8 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 12 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 8 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_1_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}

					bullet1_zigzag++;
				}
				else if(bullet1_zigzag == ZIGZAG_2){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_ZIGZAG_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_zig_zag_bullet_1[line] & (1<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										//frame_pointer[(line - 8 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										//frame_pointer[(line - 8 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 12 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 8 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_1_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet1_zigzag = ZIGZAG_1;
				}


			}
			if(bullet_1_shot == 0){ // TODO magic number
				alien_bullet_count--;
			}
		}
		if(bullet_1_type == BULLET_TYPE_1){//CROSS

		}
		else{//ZIGZAG

		}
	}
	else if(bullet_number == ALIEN_BULLET_2){
		if(bullet_2_shot > 0){ // TODO magic number
			//xil_printf("Is the first bullet a cross?\n\r");
			point_t old_alien_bullet_position = getAlienBulletPosition(bullet_number);
			old_alien_bullet_position.y += ALIEN_BULLET_HEIGHT;
			setAlienBulletPosition(old_alien_bullet_position, bullet_number);
			point_t new_alien_bullet_position = getAlienBulletPosition(bullet_number);
			if(bullet2_cross > 0){ // TODO magic number
				if(bullet2_cross == CROSS_1){
					//xil_printf("Are we in the first cross position???\n\r");
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_cross_bullet_2[line] & (1<<(ALIEN_CROSS_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_2_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet2_cross++;
				}
				else if(bullet2_cross == CROSS_2){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_cross_bullet_3[line] & (1<<(ALIEN_CROSS_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_2_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet2_cross++;
				}
				else if(bullet2_cross == CROSS_3){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_cross_bullet_1[line] & (1<<(ALIEN_CROSS_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_2_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet2_cross = CROSS_1;
				}
				//if(bullet_1_shot == 0){
				//alien_bullet_count--;
				//}
			}

			if(bullet2_zigzag > 0){ // TODO magic number
				if(bullet2_zigzag == ZIGZAG_1){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_ZIGZAG_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_zig_zag_bullet_2[line] & (1<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										//frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										//frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 12 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 8 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_2_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}

					bullet2_zigzag++;
				}
				else if(bullet2_zigzag == ZIGZAG_2){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_ZIGZAG_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_zig_zag_bullet_1[line] & (1<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										//frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										//frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 12 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 8 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_2_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet2_zigzag = ZIGZAG_1;
				}

			}
			if(bullet_2_shot == 0){ // TODO magic number
				alien_bullet_count--;
			}
		}







		/*
				static uint8_t bullet1_cross;
		static uint8_t bullet2_cross;
		static uint8_t bullet3_cross;
		static uint8_t bullet4_cross;
		static uint8_t bullet1_zigzag;
		static uint8_t bullet2_zigzag;
		static uint8_t bullet3_zigzag;
		static uint8_t bullet4_zigzag
		 */
		if(bullet_2_type == BULLET_TYPE_1){//CROSS

		}
		else{//ZIGZAG

		}
	}
	else if(bullet_number == ALIEN_BULLET_3){
		if(bullet_3_shot > 0){ // TODO magic number
			//xil_printf("Is the first bullet a cross?\n\r");
			point_t old_alien_bullet_position = getAlienBulletPosition(bullet_number);
			old_alien_bullet_position.y += ALIEN_BULLET_HEIGHT;
			setAlienBulletPosition(old_alien_bullet_position, bullet_number);
			point_t new_alien_bullet_position = getAlienBulletPosition(bullet_number);
			if(bullet3_cross > 0){ // TODO magic number
				if(bullet3_cross == CROSS_1){
					//xil_printf("Are we in the first cross position???\n\r");
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_cross_bullet_2[line] & (1<<(ALIEN_CROSS_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_3_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet3_cross++;
				}
				else if(bullet3_cross == CROSS_2){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){
								if((alien_cross_bullet_3[line] & (1<<(ALIEN_CROSS_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									}
									if(frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
								bullet_3_shot = 0;
								//alien_bullet_count--;
							}
						}
					}
					bullet3_cross++;
				}
				else if(bullet3_cross == CROSS_3){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_cross_bullet_1[line] & (1<<(ALIEN_CROSS_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_3_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet3_cross = CROSS_1;
				}
			}
			//if(bullet_1_shot == 0){
			//alien_bullet_count--;
			//}

			if(bullet3_zigzag > 0){ // TODO magic number
				if(bullet3_zigzag == ZIGZAG_1){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_ZIGZAG_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_zig_zag_bullet_2[line] & (1<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										//frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										//frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 12 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 8 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_3_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}

					bullet3_zigzag++;
				}
				else if(bullet3_zigzag == ZIGZAG_2){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_ZIGZAG_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_zig_zag_bullet_1[line] & (1<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										//frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										//frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 12 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 8 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_3_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet3_zigzag = ZIGZAG_1;
				}

			}
			if(bullet_3_shot == 0){ // TODO magic number
				alien_bullet_count--;
			}

		}




		/*
				static uint8_t bullet1_cross;
		static uint8_t bullet2_cross;
		static uint8_t bullet3_cross;
		static uint8_t bullet4_cross;
		static uint8_t bullet1_zigzag;
		static uint8_t bullet2_zigzag;
		static uint8_t bullet3_zigzag;
		static uint8_t bullet4_zigzag
		 */
		if(bullet_3_type == BULLET_TYPE_1){//CROSS

		}
		else{//ZIGZAG

		}
	}
	else{
		if(bullet_4_shot > 0){ // TODO magic number
			//xil_printf("Is the first bullet a cross?\n\r");
			point_t old_alien_bullet_position = getAlienBulletPosition(bullet_number);
			old_alien_bullet_position.y += ALIEN_BULLET_HEIGHT;
			setAlienBulletPosition(old_alien_bullet_position, bullet_number);
			point_t new_alien_bullet_position = getAlienBulletPosition(bullet_number);
			if(bullet4_cross > 0){ // TODO magic number
				if(bullet4_cross == CROSS_1){
					//xil_printf("Are we in the first cross position???\n\r");
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_cross_bullet_2[line] & (1<<(ALIEN_CROSS_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_4_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet4_cross++;
				}
				else if(bullet4_cross == CROSS_2){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_cross_bullet_3[line] & (1<<(ALIEN_CROSS_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_4_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet4_cross++;
				}
				else if(bullet4_cross == CROSS_3){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_cross_bullet_1[line] & (1<<(ALIEN_CROSS_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 10 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_4_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet4_cross = CROSS_1;
				}
				//if(bullet_1_shot == 0){
				//alien_bullet_count--;
				//}

			}
			if(bullet4_zigzag > 0){ // TODO magic number
				if(bullet4_zigzag == ZIGZAG_1){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_ZIGZAG_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_zig_zag_bullet_2[line] & (1<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										//frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										//frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 12 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 8 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_4_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}

					bullet4_zigzag++;
				}
				else if(bullet4_zigzag == ZIGZAG_2){
					uint8_t line, pixel;
					for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
						for(pixel = 0; pixel < ALIEN_ZIGZAG_BULLET_WORD_WIDTH; pixel++){
							if(old_alien_bullet_position.y < 400){ // TODO magic number
								if((alien_zig_zag_bullet_1[line] & (1<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-1-pixel)))){
									if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] != WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = WHITE;
									}
									else if(frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){
										frame_pointer[(line + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;
									} // TODO magic number
									if(frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] == WHITE){ //this if statement does nothing
										//frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										//frame_pointer[(line - 10 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - 2 + new_alien_bullet_position.x)] = BLACK;//this line does nothing
										frame_pointer[(line - 12 + new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK;//this line does nothing
									}
								}
							}
							else{
								frame_pointer[(line - 8 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								frame_pointer[(line - 12 + new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_bullet_position.x)] = BLACK; // TODO magic number
								bullet_4_shot = 0; // TODO magic number
								//alien_bullet_count--;
							}
						}
					}
					bullet4_zigzag = ZIGZAG_1;
				}

			}
			if(bullet_4_shot == 0){ // TODO magic number
				alien_bullet_count--;
			}
		}
	}
}

uint8_t updateAlienBullet(){
	uint8_t total;
	updateInvdidualAlienBullet(ALIEN_BULLET_1);
	updateInvdidualAlienBullet(ALIEN_BULLET_2);
	updateInvdidualAlienBullet(ALIEN_BULLET_3);
	updateInvdidualAlienBullet(ALIEN_BULLET_4);


	if(alien_bullet_count < 5){ // TODO magic number
		//xil_printf("Did we come in here??\n\r");

		/*
		if(alien_bullet_count == ALIEN_BULLET_1){
			//xil_printf("Did we come in here for one bullet??\n\r");
			total = updateInvdidualAlienBullet(ALIEN_BULLET_1);
		}
		else if(alien_bullet_count == ALIEN_BULLET_2){
			total += updateInvdidualAlienBullet(ALIEN_BULLET_1);
			total += updateInvdidualAlienBullet(ALIEN_BULLET_2);
		}
		else if(alien_bullet_count == ALIEN_BULLET_3){
			total+= updateInvdidualAlienBullet(ALIEN_BULLET_1);
			total+= updateInvdidualAlienBullet(ALIEN_BULLET_2);
			total+= updateInvdidualAlienBullet(ALIEN_BULLET_3);
		}
		else{
			total+= updateInvdidualAlienBullet(ALIEN_BULLET_1);
			total+= updateInvdidualAlienBullet(ALIEN_BULLET_2);
			total+= updateInvdidualAlienBullet(ALIEN_BULLET_3);
			total+= updateInvdidualAlienBullet(ALIEN_BULLET_4);
		}*/
	}
	return alien_bullet_count;
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
	for( row=0; row<480; row++) { // TODO magic number
		for(col=0; col<640; col++) { // TODO magic number
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
