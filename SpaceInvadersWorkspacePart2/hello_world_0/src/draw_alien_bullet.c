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
#include "draw_tank.h"

#define ALIEN_BULLET_GROUND_LEVEL 450 //This is the ground level of the game

#define ALIEN_BULLET_1 0 //Alien bullet number 1
#define ALIEN_BULLET_2 1 //Alien bullet number 2
#define ALIEN_BULLET_3 2 //Alien bullet number 3
#define ALIEN_BULLET_4 3 //Alien bullet number 4

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

static point_t alienBulletPosition1; //Variable to keep track of alien bullet 1 position
static point_t alienBulletPosition2; //Variable to keep track of alien bullet 2 position
static point_t alienBulletPosition3; //Variable to keep track of alien bullet 3 position
static point_t alienBulletPosition4; //Variable to keep track of alien bullet 4 position
bool alien_cross_bullet_drawn = false;
bool alien_zigzag_bullet_drawn = false;

#define ALIEN_NULL -1

static uint8_t alienBulletCount = 0; //TODO

uint8_t alien_bullet_array[4] = {0, 0, 0, 0}; //Default is not shot //TODO
int8_t alien_bullet_type[4] = {-1, -1, -1, -1}; //default type is cross //TODO
uint8_t alien_cross[4] = {1, 1, 1, 1}; //default is cross_1 //TODO
uint8_t alien_zigzag[4] = {1, 1, 1, 1}; //Default is zigzag_1 //TODO

extern unsigned int * frame_pointer;

uint8_t getAlienBulletCount(){
	return alienBulletCount;
}

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

void drawAlienBullet(uint8_t alienNumber, uint8_t type){
	uint8_t width;
	int8_t alien_shooter = getMyAlienNumber(alienNumber); //Get the alien that shoots
	if(alien_shooter != ALIEN_NULL){ //If the column that the alien shooter is in is not null
		point_t updateBullet;
		point_t alienPos = calculateAlienPosition(alien_shooter);
		updateBullet.x = alienPos.x + (BULLET_MIDDLE_ALIEN - 2);  //TODO
		updateBullet.y = alienPos.y + ALIEN_HEIGHT;
		uint8_t i, num;
		uint8_t stop = false;
		for(num = 0; num < 4 && !stop; num++){  //TODO
			if(alien_bullet_type[num] == -1){  //TODO
				i = num;
				alien_bullet_type[i] = type;
				stop = true;
			}
		}
		if(type == 0){  //TODO
			if(alienBulletCount < 4){ //!alien_cross_bullet_drawn  //TODO
				setAlienBulletPosition(updateBullet, i);
				width = ALIEN_CROSS_BULLET_WORD_WIDTH;
				drawBullet(alien_cross_bullet_1, updateBullet, width);
				alienBulletCount++;
			}
		}
		else {
			if(alienBulletCount < 4){//!alien_zigzag_bullet_drawn  //TODO
				setAlienBulletPosition(updateBullet, i);
				width = ALIEN_ZIGZAG_BULLET_WORD_WIDTH;
				drawBullet(alien_zig_zag_bullet_1, updateBullet, width);
				alienBulletCount++;
			}
		}
	}
}

void drawBullet(const uint32_t* alien_cross_bullet, point_t updateBullet, uint8_t width){
	uint8_t line, pixel;
	for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
		for(pixel = 0; pixel < width; pixel++){
			if((alien_cross_bullet[line] & (SHIFT<<(width-SHIFT-pixel)))){
				frame_pointer[(line + updateBullet.y) * SCREEN_WIDTH + (pixel + updateBullet.x)] = RED; //Set to red
			}
		}
	}
}

void eraseBullets(const uint32_t * alien_cross_bullet, point_t position, uint8_t width){
	uint8_t line, pixel;
	for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
		for(pixel = 0; pixel < width; pixel++){
			if((alien_cross_bullet[line] & (SHIFT<<(width-SHIFT-pixel)))){
				frame_pointer[(line + position.y) * SCREEN_WIDTH + (pixel + 2 + position.x)] = BLACK; //Set to red  //TODO
				frame_pointer[(line + position.y) * SCREEN_WIDTH + (pixel + position.x)] = BLACK; //Set to red
				frame_pointer[(line + position.y) * SCREEN_WIDTH + (pixel + position.x - 2)] = BLACK; //Set to red  //TODO
			}
		}
	}
}

void eraseAllAlienBullets(){
	uint8_t number;
	uint8_t width;
	for(number = 0; number < 4; number++){  //TODO
		point_t position = getAlienBulletPosition(number);
		if(alien_bullet_type[number] == 0){  //TODO
			width = ALIEN_CROSS_BULLET_WORD_WIDTH;
			if(alien_cross[number] == 1){  //TODO
				alien_bullet_type[number] = -1;  //TODO
				alienBulletCount--;
				eraseBullets(alien_cross_bullet_1, position, width); //Said 2
				eraseBullets(alien_cross_bullet_2, position, width); //Said 1
				eraseBullets(alien_cross_bullet_3, position, width); //Said 1

			}
			else if(alien_cross[number] == 2){  //TODO
				alien_bullet_type[number] = -1;  //TODO
				alienBulletCount--;
				eraseBullets(alien_cross_bullet_2, position, width); //Said 3
				eraseBullets(alien_cross_bullet_3, position, width); //Said 1
				eraseBullets(alien_cross_bullet_1, position, width); //Said 1

			}
			else{
				alien_bullet_type[number] = -1;  //TODO
				alienBulletCount--;
				eraseBullets(alien_cross_bullet_3, position, width); //Said 1
				eraseBullets(alien_cross_bullet_2, position, width); //Said 1
				eraseBullets(alien_cross_bullet_1, position, width); //Said 1
			}
		}
		else if(alien_bullet_type[number] == 1){  //TODO
			width = ALIEN_ZIGZAG_BULLET_WORD_WIDTH;
			if(alien_zigzag[number] == 1){  //TODO
				alien_bullet_type[number] = -1;  //TODO
				alienBulletCount--;
				eraseBullets(alien_zig_zag_bullet_2, position, width); //Said 2
				eraseBullets(alien_zig_zag_bullet_1, position, width); //Said 2
			}
			else{
				alien_bullet_type[number] = -1;  //TODO
				alienBulletCount--;  //TODO
				eraseBullets(alien_zig_zag_bullet_2, position, width); //Said 1
				eraseBullets(alien_zig_zag_bullet_1, position, width); //Said 2
			}
		}
	}
}

uint8_t alienMayErodeBunker(uint8_t bunkerNumber, uint8_t blockNumber, uint8_t pixel, uint8_t line, point_t new_bullet_position){
	if(getErosionStage(bunkerNumber, blockNumber) != 3){  //TODO
		setDidAlienKillBunkerFlag(true);
		point_t bunkerPosition;
		bunkerPosition.x = pixel + new_bullet_position.x;
		bunkerPosition.y = line + new_bullet_position.y;
		setShotBunkerPosition(bunkerPosition);
		return true;
	}
	else{
		return false;
	}
}

uint8_t whichAlienBunkerNumber(point_t bullet, uint8_t pixel, uint8_t line, point_t new_bullet_position){
	uint8_t stop = false;
	uint8_t bunkerNumber = calculateBunkerNumber(bullet);
	uint8_t blockNumber = calculateBlockNumber(bunkerNumber, bullet);
	if((calculateBunkerNumber(bullet) == BUNKER1 && calculateBlockNumber(BUNKER1, bullet) != WRONG_BUNKER)
			|| (calculateBunkerNumber(bullet) == BUNKER2 && calculateBlockNumber(BUNKER2, bullet) != WRONG_BUNKER)
			|| (calculateBunkerNumber(bullet) == BUNKER3 && calculateBlockNumber(BUNKER3, bullet) != WRONG_BUNKER)
			|| (calculateBunkerNumber(bullet) == BUNKER4 && calculateBlockNumber(BUNKER4, bullet) != WRONG_BUNKER)){
		stop = alienMayErodeBunker(bunkerNumber, blockNumber, pixel, line, new_bullet_position);
	}
	return stop;
}

void eraseAlienBullet(const uint32_t* alien_cross_bullet, point_t bullet_pos, uint8_t width){
	uint8_t line, pixel;
	for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){ //Height
		for(pixel = 0; pixel < width; pixel++){ //Width
			if((alien_cross_bullet[line] & (SHIFT<<(width-SHIFT-pixel)))){
				frame_pointer[(line + bullet_pos.y) * SCREEN_WIDTH + (pixel + bullet_pos.x)] = BLACK; //Set to red
			}
		}
	}
}

uint8_t generalUpdateBullet(const uint32_t* alien_cross_bullet, uint8_t bulletNum, uint8_t type){
	int8_t bullet_drawn = type;
	point_t my_updateBullet = getAlienBulletPosition(bulletNum);
	point_t temp = my_updateBullet;
	temp.y += 10; //Was 10  //TODO
	setAlienBulletPosition(temp, bulletNum);
	uint8_t line, pixel;
	uint8_t stop = false;
	for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
		for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
			if((temp.y + 10) <= (GROUND_LEVEL - 10) && !stop){  //TODO
				point_t bullet;
				bullet.x = pixel + temp.x;
				bullet.y = line + temp.y;
				if(calculateTank(bullet) != 0){
					stop = true;
				}
				if(calculateBunkerNumber(bullet) != WRONG_BUNKER){
					stop = whichAlienBunkerNumber(bullet, pixel, line, temp);
				}
				if(frame_pointer[(my_updateBullet.y + line) * SCREEN_WIDTH + (pixel + my_updateBullet.x)] == RED){//Black out the last shape
					frame_pointer[(my_updateBullet.y + line) * SCREEN_WIDTH + (pixel + my_updateBullet.x)] = BLACK; //Set to red
				}
				if((alien_cross_bullet[line] & (SHIFT<<(ALIEN_CROSS_BULLET_WORD_WIDTH-SHIFT-pixel)))){
					//xil_printf("We shot an alien bullet from alien %d with an x: %d and y: %d\n\r", alien_shooter, updateBullet.x, updateBullet.y);
					frame_pointer[(line + temp.y) * SCREEN_WIDTH + (pixel + temp.x)] = RED; //Set to red
				}
				if(stop){
					eraseAlienBullet(alien_cross_bullet, temp, ALIEN_CROSS_BULLET_WORD_WIDTH);
					bullet_drawn = -1; //Bullet set to false  //TODO
					alien_bullet_type[bulletNum] = -1;  //TODO
				}
			}
			else{
				if(frame_pointer[(my_updateBullet.y + line) * SCREEN_WIDTH + (pixel + my_updateBullet.x)] == RED){//Black out the last shape
					frame_pointer[(my_updateBullet.y + line) * SCREEN_WIDTH + (pixel + my_updateBullet.x)] = BLACK; //Set to red
					bullet_drawn = -1;  //TODO
					alien_bullet_type[bulletNum] = -1;  //TODO
				}
			}
			if(stop){
				frame_pointer[(my_updateBullet.y + line) * SCREEN_WIDTH + (pixel + my_updateBullet.x)] = BLACK; //Set to red
				//eraseTankBullet(temp);
				bullet_drawn = -1; //Bullet set to false  //TODO
				alien_bullet_type[bulletNum] = -1;  //TODO
			}
		}
	}
	return bullet_drawn;
}

uint8_t updateEachBullet(){ //This is cool
	uint8_t i;
	uint8_t total = false;;
	for(i = 0; i < 4; i++){  //TODO
		if(alien_bullet_type[i] == 0){  //TODO
			if(alien_cross[i] == 1){  //TODO
				alien_cross[i]++;
				alien_bullet_type[i] = generalUpdateBullet(alien_cross_bullet_2, i, 0);  //TODO
				if(alien_bullet_type[i] == -1){  //TODO
					alienBulletCount--;
				}
				total += alien_cross_bullet_drawn;
			}
			else if(alien_cross[i] == 2){  //TODO
				alien_cross[i]++;
				alien_bullet_type[i] = generalUpdateBullet(alien_cross_bullet_3, i, 0);  //TODO
				total += alien_cross_bullet_drawn;
				if(alien_bullet_type[i] == -1){  //TODO
					alienBulletCount--;
				}
			}
			else{
				alien_cross[i] = 1;  //TODO
				alien_bullet_type[i] = generalUpdateBullet(alien_cross_bullet_1, i, 0);  //TODO
				total += alien_cross_bullet_drawn;
				if(alien_bullet_type[i] == -1){  //TODO
					alienBulletCount--;
				}
			}
		}
		else if(alien_bullet_type[i] == 1){  //TODO
			if(alien_zigzag[i] == ZIGZAG_1){
				alien_zigzag[i]++;  //TODO
				alien_bullet_type[i] = generalUpdateBullet(alien_zig_zag_bullet_2, i, 1); //TODO
				total += alien_zigzag_bullet_drawn;
				if(alien_bullet_type[i] == -1){  //TODO
					alienBulletCount--;
				}
			}
			else{
				alien_zigzag[i] = ZIGZAG_1;
				alien_bullet_type[i] = generalUpdateBullet(alien_zig_zag_bullet_1, i, 1);
				total += alien_zigzag_bullet_drawn;
				if(alien_bullet_type[i] == -1){  //TODO
					alienBulletCount--;
				}
			}
		}
	}
	return alienBulletCount;
}
