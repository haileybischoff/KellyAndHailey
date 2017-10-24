/*
 * draw_tank_bullet.c
 *
 *  Created on: Oct 21, 2017
 *      Author: superman
 */

#include <stdbool.h>
#include "draw_tank_bullet.h"
#include "draw_bunker.h"
#include "images.h"
#include "draw_aliens.h"
#include "draw_tank.h"
#include "draw_saucer.h"

#define TANK_HALF_HEIGHT 8 //Half of the height for the tank is 8
#define TANK_HALF_WIDTH 14 //Half of the width for the tank

static point_t tankBulletPosition; //Variable to keep track of tank bullet position

extern unsigned int * frame_pointer;

static bool tank_Bullet_Drawn = false; //Was the tank bullet shot

void setTankBulletPosition(point_t val){ //Set the position of the tank bullet
	tankBulletPosition.x = val.x; //X position of bullet
	tankBulletPosition.y = val.y; //Y position of bullet
}

point_t getTankBulletPosition(){ //get position of the tank bullet
	return tankBulletPosition;
}

uint8_t getBulletDrawn(){
	return tank_Bullet_Drawn;
}

void eraseTheTankBullet(){
	if(tank_Bullet_Drawn){
		point_t updateBullet = getTankBulletPosition();
		uint8_t line, pixel;
		for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
			for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
				frame_pointer[(line + updateBullet.y)*SCREEN_WIDTH + (pixel + updateBullet.x)] = BLACK; //Set to red
				tank_Bullet_Drawn = false;
			}
		}
	}
}

void drawTankBullet(){
	if(!tank_Bullet_Drawn){ //If not fired
		tank_Bullet_Drawn = true; //Set drawn to true
		//point_t bullet_from_tank_point = getTankBulletPosition();
		point_t updateBullet;
		updateBullet.x = getTankPosition() + TANK_HALF_WIDTH; //mpove x position
		updateBullet.y = TANK_Y_POSITION - TANK_HALF_HEIGHT; //Move y position
		setTankBulletPosition(updateBullet); //Set tank bullet position
		uint8_t line, pixel;
		for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
			for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
				frame_pointer[(line + updateBullet.y)*SCREEN_WIDTH + (pixel + updateBullet.x)] = RED; //Set to red
			}
		}
	}
}

void eraseTankBullet(point_t bullet_pos){
	uint8_t line, pixel;
	for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
		for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
			frame_pointer[(line + bullet_pos.y) * SCREEN_WIDTH + (pixel + bullet_pos.x)] = BLACK; //Set to red
		}
	}
}

uint8_t tankMayErodeBunker(uint8_t bunkerNumber, uint8_t blockNumber, uint8_t pixel, uint8_t line, point_t new_tank_bullet_position){
	if(getErosionStage(bunkerNumber, blockNumber) != 3){
		setDidTankKillBunkerFlag(true);
		point_t bunkerPosition;
		bunkerPosition.x = pixel + new_tank_bullet_position.x;
		bunkerPosition.y = line + new_tank_bullet_position.y;
		setShotBunkerPosition(bunkerPosition);
		return true;
	}
	else{
		return false;
	}
}

uint8_t whichBunkerNumber(point_t tank, uint8_t pixel, uint8_t line, point_t new_tank_bullet_position){
	uint8_t stop = false;
	uint8_t bunkerNumber = calculateBunkerNumber(tank);
	uint8_t blockNumber = calculateBlockNumber(bunkerNumber, tank);
	if((calculateBunkerNumber(tank) == BUNKER1 && calculateBlockNumber(BUNKER1, tank) != WRONG_BUNKER)
			|| (calculateBunkerNumber(tank) == BUNKER2 && calculateBlockNumber(BUNKER2, tank) != WRONG_BUNKER)
			|| (calculateBunkerNumber(tank) == BUNKER3 && calculateBlockNumber(BUNKER3, tank) != WRONG_BUNKER)
			|| (calculateBunkerNumber(tank) == BUNKER4 && calculateBlockNumber(BUNKER4, tank) != WRONG_BUNKER)){
		stop = tankMayErodeBunker(bunkerNumber, blockNumber, pixel, line, new_tank_bullet_position);
	}
	return stop;
}

/*uint8_t tankHitsSaucer(uint8_t pixel, uint8_t line, point_t new_tank_bullet_position, point_t tank){
	uint8_t stop = false;
	if(calculateHitSaucer(tank)){
		stop = true;
		point_t deadSaucer;
		deadSaucer.x = pixel + new_tank_bullet_position.x;
		deadSaucer.y = line + new_tank_bullet_position.y;
		setDeadSaucerPosition(deadSaucer);
	}
	return stop;
}*/

uint8_t tankHitsAliens(uint8_t pixel, uint8_t line, point_t new_tank_bullet_position, point_t tank){
	uint8_t stop = false;
	if(isAlienAlive(calculateAlienNumber(tank))){
		stop = true;
		setDidTankKillAlienFlag(true);
		point_t deadAlienPosition;
		deadAlienPosition.x = pixel + new_tank_bullet_position.x;
		deadAlienPosition.y = line + new_tank_bullet_position.y;
		setDeadAlienPosition(deadAlienPosition);
	}
	return stop;
}

uint8_t updateTankBullet(){
	if(tank_Bullet_Drawn){
		point_t old_tank_bullet_position = getTankBulletPosition(); //Get tank bullet position
		point_t temp = old_tank_bullet_position;
		temp.y -= (FOUR_GAME_PIXELS); //Increment by 8 pixels
		setTankBulletPosition(temp); //Set tank bullet position
		point_t new_tank_bullet_position = getTankBulletPosition(); //Get tank bullet position
		uint8_t line, pixel;
		uint8_t stop = false;
		for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
			for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
				if(new_tank_bullet_position.y > ELEVEN_GAME_PIXELS && !stop){
					point_t tank;
					tank.x = pixel + new_tank_bullet_position.x;
					tank.y = line + new_tank_bullet_position.y;
					if(calculateBunkerNumber(tank) != WRONG_BUNKER){
						stop =  whichBunkerNumber(tank, pixel, line, new_tank_bullet_position);
					}
					if(calculateAlienNumber(tank) != WRONG_ALIEN){
						stop = tankHitsAliens(pixel, line, new_tank_bullet_position, tank);
					}
					if(frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == RED){
						if(calculateHitSaucer(tank)){
							stop = true;
						}
					}
					else if(frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == BLACK){//!RED
						frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = RED; //Set to red
					}
					if(frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == RED){ //Set to black
						frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y)*SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = BLACK;//Set to black
					}
				}
				else{
					frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = BLACK; //Make the last pixel black
					tank_Bullet_Drawn = false; //Bullet set to false
				}
				if(stop){
					eraseTankBullet(new_tank_bullet_position);
					tank_Bullet_Drawn = false; //Bullet set to false
				}
			}
		}
	}
	return tank_Bullet_Drawn;
}
