/*
 * draw_alien_bullet.c
 *
 *  Created on: Oct 21, 2017
 *      Author: superman
 */

#include <stdbool.h>
#include "draw_alien_bullet.h"
#include "draw_aliens.h"
#include "images.h"
#include "draw_bunker.h"

#define ALIEN_BULLET_GROUND_LEVEL 450 //This is the ground level of the game

#define ALIEN_BULLET_1 1 //Alien bullet number 1
#define ALIEN_BULLET_2 2 //Alien bullet number 2
#define ALIEN_BULLET_3 3 //Alien bullet number 3
#define ALIEN_BULLET_4 4 //Alien bullet number 4

#define BULLET_TYPE_1 0 //Bullet type number 1
#define BULLET_TYPE_2 1 //Bullet type number 2
#define BULLET_MAX_COUNT 4 //Maximum number of alien bullets
#define BULLET_MIDDLE_ALIEN 12 //The middle of an alien

#define CROSS_1 1 //Bullet cross number 1
#define CROSS_2 2 //Bullet cross number 2
#define CROSS_3 3 //Bullet cross number 3
#define NUMBER_OF_CROSS_TYPES 3 //3 types of cross bullets
#define NUMBER_OF_ZIGZAG_TYPES 2 //2 types of cross bullets
#define ZIGZAG_1 1 //Bullet ZIGZAG number 1
#define ZIGZAG_2 2 //Bullet ZIGZAG number 2

static point_t alienCrossBulletPosition; //Variable to keep track of tank bullet position

static point_t alienBulletPosition1; //Variable to keep track of alien bullet 1 position
static point_t alienBulletPosition2; //Variable to keep track of alien bullet 2 position
static point_t alienBulletPosition3; //Variable to keep track of alien bullet 3 position
static point_t alienBulletPosition4; //Variable to keep track of alien bullet 4 position

static uint8_t bullet_1_type; //Keep track of alien bullet 1 type
static uint8_t bullet_2_type; //Keep track of alien bullet 2 type
static uint8_t bullet_3_type; //Keep track of alien bullet 3 type
static uint8_t bullet_4_type; //Keep track of alien bullet 4 type

static bool bullet_1_shot = false; //Keep track of whether alien bullet 1 was shot
static bool bullet_2_shot = false; //Keep track of whether alien bullet 2 was shot
static bool bullet_3_shot = false; //Keep track of whether alien bullet 3 was shot
static bool bullet_4_shot = false; //Keep track of whether alien bullet 4 was shot

static uint8_t alien_bullet_count = RESET; //Initialize alien bullet count

static uint8_t bullet1_cross; //Keep track of alien bullet 1 cross
static uint8_t bullet2_cross; //Keep track of alien bullet 2 cross
static uint8_t bullet3_cross; //Keep track of alien bullet 3 cross
static uint8_t bullet4_cross; //Keep track of alien bullet 4 cross
static uint8_t bullet1_zigzag; //Keep track of alien bullet 1 zigzag
static uint8_t bullet2_zigzag; //Keep track of alien bullet 2 zigzag
static uint8_t bullet3_zigzag; //Keep track of alien bullet 3 zigzag
static uint8_t bullet4_zigzag; //Keep track of alien bullet 4 zigzag

static bool bullet1collision = false;
static bool bullet2collision = false;
static bool bullet3collision = false;
static bool bullet4collision = false;

bool alien_cross_bullet_drawn = false;

point_t collision_position;

uint8_t alien_bullet_array[4] = {0, 0, 0, 0}; //Default is not shot
uint8_t alien_bullet_type[4] = {0, 0, 0, 0}; //default type is cross
uint8_t alien_cross[4] = {1, 1, 1, 1}; //default is cross_1
uint8_t alien_zigzag[4] = {1, 1, 1, 1}; //Default is zigzag_1

static bool collision = false;
point_t collision_position;

extern unsigned int * frame_pointer;

void setAlienBulletPosition(point_t val, uint8_t bullet_number){ //Set the alien bullet position given a point and a number
	if(bullet_number == ALIEN_BULLET_1){ //Number 1
		alienBulletPosition1.x = val.x; //X position
		alienBulletPosition1.y = val.y; //Y position
	}
	else if(bullet_number == ALIEN_BULLET_2){ //Number 2
		alienBulletPosition2.x = val.x; //X position
		alienBulletPosition2.y = val.y; //Y position
	}
	else if(bullet_number == ALIEN_BULLET_3){ //Number 3
		alienBulletPosition3.x = val.x; //X position
		alienBulletPosition3.y = val.y; //Y position
	}
	else if(bullet_number == ALIEN_BULLET_4){ //Number 4
		alienBulletPosition4.x = val.x; //X position
		alienBulletPosition4.y = val.y; //Y position
	}
}

point_t getAlienBulletPosition(uint8_t bullet_number){ //Get the position for the alien bullet when given a bullet
	if(bullet_number == ALIEN_BULLET_1){ //Number 1
		return alienBulletPosition1;
	}
	else if(bullet_number == ALIEN_BULLET_2){ //Number 2
		return alienBulletPosition2;
	}
	else if(bullet_number == ALIEN_BULLET_3){ //Number 3
		return alienBulletPosition3;
	}
	else{ //Number 4
		return alienBulletPosition4;
	}
}

void drawAlienBullet(uint8_t alienNum, uint8_t bullet_type){ //Draw alien bullet when given an alien and a bullet type
	int8_t alien_shooter = getMyAlienNumber(alienNum); //Get the alien that shoots
	if(alien_shooter != ALIEN_NULL){ //If the column that the alien shooter is in is not null
		if(alien_bullet_count < BULLET_MAX_COUNT){ //Check to make sure that we don't have the maximum bullets out
			alien_bullet_count++; //increment bullet count
			//if(alien_bullet_count == ALIEN_BULLET_1){ //if we have one bullet
			if(!bullet_1_shot){ //If bullet one hasn't been shot
				bullet1collision = false;
				bullet_1_shot = true; //Set to true
				bullet_1_type = bullet_type; //Set the bullet type
				if(bullet_1_type == BULLET_TYPE_1){ //bullet type is a cross
					bullet1_cross = CROSS_1; //Set to cross one
					bullet1_zigzag = false; //Not zigzag
				}
				else{
					bullet1_zigzag = ZIGZAG_1; //Set to zigzag one
					bullet1_cross = false; //Not cross
				}
			}
			//}
			//else if(alien_bullet_count == ALIEN_BULLET_2){ //If we have two bullets
			else if(!bullet_2_shot){ //IF bullet two hasn't been shot
				bullet2collision = false;
				bullet_2_shot = true; //Set to true
				bullet_2_type = bullet_type; //Set the bullet type
				if(bullet_2_type == BULLET_TYPE_1){ //Bullet type is a cross
					bullet2_cross = CROSS_1; //Set to cross one
					bullet2_zigzag = false; //Not zigzag
				}
				else{
					bullet2_zigzag = ZIGZAG_1; //Set to zigzag one
					bullet2_cross = false; //Not cross
				}
			}
			//}
			//else if(alien_bullet_count == ALIEN_BULLET_3){ //If we have three bullets
			else if(!bullet_3_shot){ //Bullet three hasn't been shot
				bullet3collision = false;
				bullet_3_shot = true; //Set to true
				bullet_3_type = bullet_type; //Set the bullet type
				if(bullet_3_type == BULLET_TYPE_1){ //Bullet type is a cross
					bullet3_cross = CROSS_1;//Set to cross one
					bullet3_zigzag = false; //Not zigzag
				}
				else{
					bullet3_zigzag = ZIGZAG_1; //Set to zigzag one
					bullet3_cross = false; //Not cross
				}
			}
			//}
			//else{
			else if(!bullet_4_shot){ //Bullet four hasn't been shot
				bullet4collision = false;
				bullet_4_shot = true; //Set to true
				bullet_4_type = bullet_type; //Set bullet type
				if(bullet_4_type == BULLET_TYPE_1){ //bullet type is a cross
					bullet4_cross = CROSS_1; //Set to cross one
					bullet4_zigzag = false; //Not zigzag
				}
				else{
					bullet4_zigzag = ZIGZAG_1; //Set to zigzag one
					bullet4_cross = false; //Not cross
				}
			}
			//}



			point_t myalienPos = calculateAlienPosition(alien_shooter); //Calculate the alien position
			myalienPos.x += BULLET_MIDDLE_ALIEN; //Set the x
			myalienPos.y += ALIEN_HEIGHT; //Set the y
			setAlienBulletPosition(myalienPos, alien_bullet_count); //Set the position
			if(bullet_type == BULLET_TYPE_1){ //Cross
				uint8_t line, pixel;
				for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){ //For height
					for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){//For width
						if((alien_cross_bullet_1[line] & (SHIFT<<(ALIEN_CROSS_BULLET_WORD_WIDTH-SHIFT-pixel)))){
							frame_pointer[(line + myalienPos.y) * SCREEN_WIDTH + (pixel + myalienPos.x)] = WHITE; //Set to white
						}
					}
				}
			}
			else if(bullet_type == BULLET_TYPE_2){ //Zigzag
				uint8_t line, pixel;
				for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){ //For height
					for(pixel = 0; pixel < ALIEN_ZIGZAG_BULLET_WORD_WIDTH; pixel++){ //For width
						if((alien_zig_zag_bullet_1[line] & (SHIFT<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-SHIFT-pixel)))){
							frame_pointer[(line + myalienPos.y) * SCREEN_WIDTH + (pixel + myalienPos.x)] = WHITE; //Set to white
						}
					}
				}
			}
		}
	}
}

void setAlienCrossBulletPosition(point_t val){
	alienCrossBulletPosition.x = val.x;
	alienCrossBulletPosition.y = val.y;
}
point_t getAlienCrossBulletPosition(){
	return alienCrossBulletPosition;
}

void drawCrossAlienBullet(uint8_t alienNumber){
	int8_t alien_shooter = getMyAlienNumber(alienNumber); //Get the alien that shoots
	if(alien_shooter != ALIEN_NULL){ //If the column that the alien shooter is in is not null
		if(!alien_cross_bullet_drawn){
			alien_cross_bullet_drawn = true;
			point_t updateBullet;
			point_t alienPos = calculateAlienPosition(alien_shooter);
			updateBullet.x = alienPos.x + BULLET_MIDDLE_ALIEN;
			updateBullet.y = alienPos.y + ALIEN_HEIGHT;

			setAlienCrossBulletPosition(updateBullet);
			uint8_t line, pixel;
			for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
				for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
					if((alien_cross_bullet_1[line] & (SHIFT<<(ALIEN_CROSS_BULLET_WORD_WIDTH-SHIFT-pixel)))){
						//xil_printf("We shot an alien bullet from alien %d with an x: %d and y: %d\n\r", alien_shooter, updateBullet.x, updateBullet.y);
						frame_pointer[(line + updateBullet.y) * SCREEN_WIDTH + (pixel + updateBullet.x)] = RED; //Set to red
					}
				}
			}
		}
	}
}

void eraseAlienCrossBullet(point_t bullet_pos){
	bullet_pos.x += BULLET_MIDDLE_ALIEN;
	uint8_t line, pixel;
	for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){ //Height
		for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){ //Width
			frame_pointer[(bullet_pos.y - line - FIVE_GAME_PIXELS) * SCREEN_WIDTH + (pixel + bullet_pos.x)] = BLACK;//Black out the last shape
			frame_pointer[(line - FIVE_GAME_PIXELS + bullet_pos.y) * SCREEN_WIDTH + (pixel + ONE_GAME_PIXELS + bullet_pos.x)] = BLACK;//Black out the last shape
			frame_pointer[(line - FIVE_GAME_PIXELS + bullet_pos.y) * SCREEN_WIDTH + (pixel - ONE_GAME_PIXELS + bullet_pos.x)] = BLACK;//Black out the last shape

			//frame_pointer[(line + bullet_pos.y) * SCREEN_WIDTH + (pixel + bullet_pos.x)] = BLACK; //Set to red
		}
	}
}

uint8_t updateCrossAlienBullet(){
	if(alien_cross_bullet_drawn){
		point_t old_alien_cross_bullet_position = getAlienCrossBulletPosition(); //Get tank bullet position
		old_alien_cross_bullet_position.y += (FIVE_GAME_PIXELS); //Increment by 8 pixels
		setAlienCrossBulletPosition(old_alien_cross_bullet_position); //Set tank bullet position
		point_t new_alien_cross_bullet_position = getAlienCrossBulletPosition(); //Get tank bullet position
		uint8_t line, pixel;
		uint8_t stop = false;
		for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
			for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
				if(old_alien_cross_bullet_position.y < GROUND_LEVEL && !stop){
					point_t cross;
					cross.x = pixel + new_alien_cross_bullet_position.x;
					cross.y = line + new_alien_cross_bullet_position.y;
					if(calculateBunkerNumber(cross) != WRONG_BUNKER){
						if(calculateBunkerNumber(cross) == BUNKER1){
							if(calculateBlockNumber(BUNKER1, cross) != WRONG_BUNKER){
								uint8_t bunkerNumber = calculateBunkerNumber(cross);
							    uint8_t blockNumber = calculateBlockNumber(bunkerNumber, cross);
								if(getErosionStage(bunkerNumber, blockNumber) != 3){
									stop = true;
									setDidTankKillBunkerFlag(true);
									point_t bunkerPosition;
									bunkerPosition.x = pixel + new_alien_cross_bullet_position.x;
									bunkerPosition.y = line + new_alien_cross_bullet_position.y;
									setShotBunkerPosition(bunkerPosition);
								}
							}
						}
						else if(calculateBunkerNumber(cross) == BUNKER2){
							if(calculateBlockNumber(BUNKER2, cross) != WRONG_BUNKER){
								uint8_t bunkerNumber = calculateBunkerNumber(cross);
							    uint8_t blockNumber = calculateBlockNumber(bunkerNumber, cross);
								if(getErosionStage(bunkerNumber, blockNumber) != 3){
									stop = true;
									setDidTankKillBunkerFlag(true);
									point_t bunkerPosition;
									bunkerPosition.x = pixel + new_alien_cross_bullet_position.x;
									bunkerPosition.y = line + new_alien_cross_bullet_position.y;
									setShotBunkerPosition(bunkerPosition);
								}
							}
						}
						else if(calculateBunkerNumber(cross) == BUNKER3){
							if(calculateBlockNumber(BUNKER3, cross) != WRONG_BUNKER){
								uint8_t bunkerNumber = calculateBunkerNumber(cross);
							    uint8_t blockNumber = calculateBlockNumber(bunkerNumber, cross);
								if(getErosionStage(bunkerNumber, blockNumber) != 3){
									stop = true;
									setDidTankKillBunkerFlag(true);
									point_t bunkerPosition;
									bunkerPosition.x = pixel + new_alien_cross_bullet_position.x;
									bunkerPosition.y = line + new_alien_cross_bullet_position.y;
									setShotBunkerPosition(bunkerPosition);
								}
							}
						}
						else if(calculateBunkerNumber(cross) == BUNKER4){
							if(calculateBlockNumber(BUNKER4, cross) != WRONG_BUNKER){
								uint8_t bunkerNumber = calculateBunkerNumber(cross);
							    uint8_t blockNumber = calculateBlockNumber(bunkerNumber, cross);
								if(getErosionStage(bunkerNumber, blockNumber) != 3){
									stop = true;
									setDidTankKillBunkerFlag(true);
									point_t bunkerPosition;
									bunkerPosition.x = pixel + new_alien_cross_bullet_position.x;
									bunkerPosition.y = line + new_alien_cross_bullet_position.y;
									setShotBunkerPosition(bunkerPosition);
								}
							}
						}

					}
					else if(frame_pointer[(line + new_alien_cross_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_cross_bullet_position.x)] == BLACK){//!RED
						//xil_printf("Are we gonna draw this new bullet??\n\r");
						frame_pointer[(line + new_alien_cross_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_cross_bullet_position.x)] = RED; //Set to red
					}
					else if(frame_pointer[(line + new_alien_cross_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_cross_bullet_position.x)] == RED){
						frame_pointer[(line + new_alien_cross_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_cross_bullet_position.x)] = BLACK; //Black out the last shape
					}
					if(frame_pointer[(line - FIVE_GAME_PIXELS + new_alien_cross_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_cross_bullet_position.x)] == RED){ //Set to black
						frame_pointer[(line - FIVE_GAME_PIXELS + new_alien_cross_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_cross_bullet_position.x)] = BLACK;//Black out the last shape
						frame_pointer[(line - FIVE_GAME_PIXELS + new_alien_cross_bullet_position.y) * SCREEN_WIDTH + (pixel + ONE_GAME_PIXELS + new_alien_cross_bullet_position.x)] = BLACK;//Black out the last shape
						frame_pointer[(line - FIVE_GAME_PIXELS + new_alien_cross_bullet_position.y) * SCREEN_WIDTH + (pixel - ONE_GAME_PIXELS + new_alien_cross_bullet_position.x)] = BLACK;//Black out the last shape
					}
					//if((calculateBlockNumber(calculateBunkerNumber(tank), tank) != WRONG_BUNKER) && ){

					//}

				}
				else{
					frame_pointer[(line - FIVE_GAME_PIXELS + new_alien_cross_bullet_position.y) * SCREEN_WIDTH + (pixel + new_alien_cross_bullet_position.x)] = BLACK; //Make the last pixel black
					alien_cross_bullet_drawn = false; //Bullet set to false
				}
				if(stop){
					eraseAlienCrossBullet(old_alien_cross_bullet_position);
					//frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = BLACK; //Make the last pixel black
					alien_cross_bullet_drawn = false; //Bullet set to false
				}
			}
		}
	}
	return alien_cross_bullet_drawn;
}

void fireAlienBullet(uint8_t alienNum, uint8_t bullet_type){
	int8_t alien_shooter = getMyAlienNumber(alienNum); // Get the alien number
	if(alien_shooter != ALIEN_NULL){
		if(alien_bullet_count < BULLET_MAX_COUNT){
			alien_bullet_count++; //increment bullet count
			uint8_t count;
			uint8_t stop = false;
			uint8_t bullet_num;
			for(count = 0; count < BULLET_MAX_COUNT && !stop; count++){
				if(!alien_bullet_array[count]){
					alien_bullet_array[count] = true;
					alien_bullet_type[count] = 0; //bullet_type;
					//if(alien_bullet_type[count] == BULLET_TYPE)
					bullet_num = count;
					stop = true;
				}
			}
			//xil_printf("This is the bullet weare on up to 3 it is: %d \n\r", bullet_num);
			//This assumption is that count keeps its value when I break out of this loop
			point_t myalienPos = calculateAlienPosition(alien_shooter);
			myalienPos.x += BULLET_MIDDLE_ALIEN; //Set the x
			myalienPos.y += ALIEN_HEIGHT; //Set the y
			setAlienBulletPosition(myalienPos, alien_bullet_count); //Set the position
			if(!alien_bullet_type[bullet_num]){
				uint8_t line, pixel;
				for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){ //For height
					for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){//For width
						if((alien_cross_bullet_1[line] & (SHIFT<<(ALIEN_CROSS_BULLET_WORD_WIDTH-SHIFT-pixel)))){
							frame_pointer[(line + myalienPos.y) * SCREEN_WIDTH + (pixel + myalienPos.x)] = WHITE; //Set to white
						}
					}
				}
			}
			else{
				uint8_t line, pixel;
				for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){ //For height
					for(pixel = 0; pixel < ALIEN_ZIGZAG_BULLET_WORD_WIDTH; pixel++){ //For width
						if((alien_zig_zag_bullet_1[line] & (SHIFT<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-SHIFT-pixel)))){
							frame_pointer[(line + myalienPos.y) * SCREEN_WIDTH + (pixel + myalienPos.x)] = WHITE; //Set to white
						}
					}
				}
			}
		}
	}
}

uint8_t draw_alien_cross_type(uint8_t my_bullet_shot, uint8_t my_bullet_cross, point_t my_old_alien_bullet_position, point_t my_new_alien_bullet_position){
	uint8_t line, pixel;
	uint8_t stop = false;
	if(!collision){
		for(line = 0; line < ALIEN_BULLET_HEIGHT && !stop; line++){
			for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH && !stop; pixel++){
				uint8_t mine = false;
				if((my_old_alien_bullet_position.y < ALIEN_BULLET_GROUND_LEVEL) && !stop){
					if(my_bullet_cross == CROSS_1){ //If cross one
						if(alien_cross_bullet_2[line] & (SHIFT<<(ALIEN_CROSS_BULLET_WORD_WIDTH-SHIFT-pixel))){ //Use cross 2
							mine = true; //Set to true
						}
					}
					else if(my_bullet_cross == CROSS_2){ //If cross two
						if(alien_cross_bullet_3[line] & (SHIFT<<(ALIEN_CROSS_BULLET_WORD_WIDTH-SHIFT-pixel))){ //Use cross 3
							mine = true; //Set to true
						}
					}
					else if(my_bullet_cross == CROSS_3){ //If cross three
						if(alien_cross_bullet_1[line] & (SHIFT<<(ALIEN_CROSS_BULLET_WORD_WIDTH-SHIFT-pixel))){ //Use cross 1
							mine = true; //Set to true
						}
					}
					else{
						mine = false; //Set to false
					}
					if(mine){ //If bool is true
						if(frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 	my_new_alien_bullet_position.x)] == GREEN){ //Said not white
							collision = true;
							collision_position.x = pixel + my_new_alien_bullet_position.x - ALIEN_CROSS_BULLET_WORD_WIDTH;
							collision_position.y = line + my_new_alien_bullet_position.y - ALIEN_BULLET_HEIGHT;
							//xil_printf("We have a collision\n\r");
							stop = true;
						}
						else if(frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] != WHITE){ //Said not white
							frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = WHITE; //Set to white
						}
						else if(frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] == WHITE){
							frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK; //Black out the last shape
						}
						if(frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] == WHITE){
							frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK;//Black out the last shape
							frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + ONE_GAME_PIXELS + my_new_alien_bullet_position.x)] = BLACK;//Black out the last shape
							frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - ONE_GAME_PIXELS + my_new_alien_bullet_position.x)] = BLACK;//Black out the last shape
						}
					}
				}
				else if(stop){
					frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK; //Black out the last shape
					my_bullet_shot = false; //Set to false
				}
				else{
					frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK; //Black out the last shape
					my_bullet_shot = false; //Set to false
				}
			}
		}
	}
	if(collision){
		uint8_t pixel, line;
		for(line = 0; line < ALIEN_BULLET_HEIGHT + 4; line++){
			for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
				if(frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] == WHITE){
					frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK;//Black out the last shape
					frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + ONE_GAME_PIXELS + my_new_alien_bullet_position.x)] = BLACK;//Black out the last shape
					frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - ONE_GAME_PIXELS + my_new_alien_bullet_position.x)] = BLACK;//Black out the last shape
				}
			}
		}
	}

	return my_bullet_shot;
}

uint8_t draw_alien_zigzag_type(uint8_t my_bullet_shot, uint8_t my_bullet_zigzag, point_t my_old_alien_bullet_position, point_t my_new_alien_bullet_position){
	uint8_t line, pixel;
	for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){ //Height
		for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){ //Width
			if(my_old_alien_bullet_position.y < ALIEN_BULLET_GROUND_LEVEL){ //We are at ground level
				bool mine = false; //Set to false
				if(my_bullet_zigzag == ZIGZAG_1){ //We are type 1
					if(alien_zig_zag_bullet_2[line] & (SHIFT<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-SHIFT-pixel))){ //Set to type 2
						mine = true; //Set to true
					}
				}
				else if(my_bullet_zigzag == ZIGZAG_2){ //We are tpe 2
					if(alien_zig_zag_bullet_1[line] & (SHIFT<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-SHIFT-pixel))){ //Set to type 1
						mine = true; //Set to true
					}
				}
				else{
					mine = false; //Set to false
				}
				if(mine){ //If bool is true
					if(frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] != WHITE){
						frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = WHITE; //Set to white
					}
					else if(frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] == WHITE){
						frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK; //If white, make black
					}
					if(frame_pointer[(line - SIX_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] == WHITE){
						frame_pointer[(line - SIX_GAME_PIXELS + my_new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK;//Set to black
					}
				}
			}
			else{
				frame_pointer[(line - FOUR_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK; //Black out the last shape
				frame_pointer[(line - SIX_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK; //Black out the last shape
				my_bullet_shot = false; //Set to false
			}
		}
	}
	return my_bullet_shot;
}

void updateIndividualAlienBullet(uint8_t bullet_number){
	point_t old_alien_bullet_position;
	point_t new_alien_bullet_position;

	if(bullet_number == ALIEN_BULLET_1){ //Bullet 1
		if(bullet_1_shot){ //Bullet one was shot
			old_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien position
			old_alien_bullet_position.y += ALIEN_BULLET_HEIGHT; //Add to the height
			setAlienBulletPosition(old_alien_bullet_position, bullet_number); //Set the alien bullet position
			new_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien bullet position
			if(bullet1_cross){ //Bullet cross  is true
				if(!bullet1collision){
					bullet_1_shot = draw_alien_cross_type(bullet_1_shot, bullet1_cross, old_alien_bullet_position, new_alien_bullet_position);
					if(collision){
						bullet1collision = true;
						collision = false;
					}
					if(bullet1_cross < CROSS_3){
						bullet1_cross++; //Increment cross shape
					}
					else{
						bullet1_cross = CROSS_1; //When maxed out set to the first
					}
				}
			}
			else if(bullet1_zigzag){ //We have a zigzag bullet
				bullet_1_shot = draw_alien_zigzag_type(bullet_1_shot, bullet1_zigzag, old_alien_bullet_position, new_alien_bullet_position);
				if(bullet1_zigzag < ZIGZAG_2){
					bullet1_zigzag++; //Increment zigzag shape
				}
				else{
					bullet1_zigzag = ZIGZAG_1; //When maxed out set to the first
				}
			}
			if(!bullet_1_shot){ //When we turn off the first bullet
				alien_bullet_count--; //Decrement alien bullet count
			}
		}
	}
	else if(bullet_number == ALIEN_BULLET_2){ //bullet 2
		if(bullet_2_shot){ //Bullet two was shot
			old_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien position
			old_alien_bullet_position.y += ALIEN_BULLET_HEIGHT; //Add to the height
			setAlienBulletPosition(old_alien_bullet_position, bullet_number); //Set alien bullet position
			new_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien bullet position
			if(bullet2_cross){ //Bullet cross  is true
				if(!bullet2collision){
					bullet_2_shot = draw_alien_cross_type(bullet_2_shot, bullet2_cross, old_alien_bullet_position, new_alien_bullet_position);
					if(collision){
						bullet2collision = true;
						collision = false;
					}
					if(bullet2_cross < CROSS_3){
						bullet2_cross++; //Increment cross shape
					}
					else{
						bullet2_cross = CROSS_1; //When maxed out set to the first
					}
				}
			}
			else if(bullet2_zigzag){
				bullet_2_shot = draw_alien_zigzag_type(bullet_2_shot, bullet2_zigzag, old_alien_bullet_position, new_alien_bullet_position);
				if(bullet2_zigzag < ZIGZAG_2){
					bullet2_zigzag++; //Increment zigzag shape
				}
				else{
					bullet2_zigzag = ZIGZAG_1; //When maxed out set to the first
				}
			}
			if(!bullet_2_shot){ //When we turn off the second bullet
				alien_bullet_count--; //Decrement alien bullet count
			}
		}
	}
	else if(bullet_number == ALIEN_BULLET_3){
		if(bullet_3_shot){
			old_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien position
			old_alien_bullet_position.y += ALIEN_BULLET_HEIGHT; //Add to the height
			setAlienBulletPosition(old_alien_bullet_position, bullet_number); //Set alien bullet position
			new_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien bullet position
			if(bullet3_cross){ //Bullet cross  is true
				if(!bullet3collision){
					bullet_3_shot = draw_alien_cross_type(bullet_3_shot, bullet3_cross, old_alien_bullet_position, new_alien_bullet_position);
					if(collision){
						bullet3collision = true;
						collision = false;
					}
					if(bullet3_cross < CROSS_3){
						bullet3_cross++; //Increment cross shape
					}
					else{
						bullet3_cross = CROSS_1; //When maxed out set to the first
					}
				}
			}
			else if(bullet3_zigzag){
				bullet_3_shot = draw_alien_zigzag_type(bullet_3_shot, bullet3_zigzag, old_alien_bullet_position, new_alien_bullet_position);
				if(bullet3_zigzag < ZIGZAG_2){
					bullet3_zigzag++; //Increment zigzag shape
				}
				else{
					bullet3_zigzag = ZIGZAG_1; //When maxed out set to the first
				}
			}
			if(!bullet_3_shot){ //When we turn off the third bullet
				alien_bullet_count--; //Decrement alien bullet count
			}
		}
	}
	else if(bullet_number == ALIEN_BULLET_4){
		if(bullet_4_shot){
			old_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien position
			old_alien_bullet_position.y += ALIEN_BULLET_HEIGHT; //Add to the height
			setAlienBulletPosition(old_alien_bullet_position, bullet_number); //Set alien bullet position
			new_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien bullet position
			if(bullet4_cross){//Bullet cross  is true
				if(!bullet4collision){
					bullet_4_shot = draw_alien_cross_type(bullet_4_shot, bullet4_cross, old_alien_bullet_position, new_alien_bullet_position);
					if(collision){
						bullet4collision = true;
						collision = false;
					}
					if(bullet4_cross < CROSS_3){
						bullet4_cross++; //Increment cross shape
					}
					else {
						bullet4_cross = CROSS_1; //When maxed out set to the first
					}
				}
			}
			else if(bullet4_zigzag){
				bullet_4_shot = draw_alien_zigzag_type(bullet_4_shot, bullet4_zigzag, old_alien_bullet_position, new_alien_bullet_position);
				if(bullet4_zigzag < ZIGZAG_2){
					bullet4_zigzag++; //Increment zigzag shape
				}
				else{
					bullet4_zigzag = ZIGZAG_1; //When maxed out set to the first
				}
			}
			if(!bullet_4_shot){ //When we turn off the fourth bullet
				alien_bullet_count--; //Decrement alien bullet count
			}
		}
	}
}

uint8_t updateAlienBullet(){
	updateIndividualAlienBullet(ALIEN_BULLET_1); //Update bullet 1
	updateIndividualAlienBullet(ALIEN_BULLET_2); //Update bullet 2
	updateIndividualAlienBullet(ALIEN_BULLET_3); //Update bullet 3
	updateIndividualAlienBullet(ALIEN_BULLET_4); //Update bullet 4
	return alien_bullet_count; //Return the number of alien bullets on the screen
}