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

uint8_t updateTankBullet(){
	if(tank_Bullet_Drawn){
		point_t old_tank_bullet_position = getTankBulletPosition(); //Get tank bullet position
		old_tank_bullet_position.y -= (FOUR_GAME_PIXELS); //Increment by 8 pixels
		setTankBulletPosition(old_tank_bullet_position); //Set tank bullet position
		point_t new_tank_bullet_position = getTankBulletPosition(); //Get tank bullet position
		uint8_t line, pixel;
		uint8_t stop = false;
		for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
			for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
				if(old_tank_bullet_position.y > ELEVEN_GAME_PIXELS && !stop){
					point_t tank;
					tank.x = pixel + new_tank_bullet_position.x;
					tank.y = line + new_tank_bullet_position.y;
					if(calculateBunkerNumber(tank) != WRONG_BUNKER){
						if(calculateBunkerNumber(tank) == BUNKER1){
							if(calculateBlockNumber(BUNKER1, tank) != WRONG_BUNKER){
								uint8_t bunkerNumber = calculateBunkerNumber(tank);
							    uint8_t blockNumber = calculateBlockNumber(bunkerNumber, tank);
								if(getErosionStage(bunkerNumber, blockNumber) != 3){
									stop = true;
									setDidTankKillBunkerFlag(true);
									point_t bunkerPosition;
									bunkerPosition.x = pixel + new_tank_bullet_position.x;
									bunkerPosition.y = line + new_tank_bullet_position.y;
									setShotBunkerPosition(bunkerPosition);
								}
							}
						}
						else if(calculateBunkerNumber(tank) == BUNKER2){
							if(calculateBlockNumber(BUNKER2, tank) != WRONG_BUNKER){
								uint8_t bunkerNumber = calculateBunkerNumber(tank);
							    uint8_t blockNumber = calculateBlockNumber(bunkerNumber, tank);
								if(getErosionStage(bunkerNumber, blockNumber) != 3){
									stop = true;
									setDidTankKillBunkerFlag(true);
									point_t bunkerPosition;
									bunkerPosition.x = pixel + new_tank_bullet_position.x;
									bunkerPosition.y = line + new_tank_bullet_position.y;
									setShotBunkerPosition(bunkerPosition);
								}
							}
						}
						else if(calculateBunkerNumber(tank) == BUNKER3){
							if(calculateBlockNumber(BUNKER3, tank) != WRONG_BUNKER){
								uint8_t bunkerNumber = calculateBunkerNumber(tank);
							    uint8_t blockNumber = calculateBlockNumber(bunkerNumber, tank);
								if(getErosionStage(bunkerNumber, blockNumber) != 3){
									stop = true;
									setDidTankKillBunkerFlag(true);
									point_t bunkerPosition;
									bunkerPosition.x = pixel + new_tank_bullet_position.x;
									bunkerPosition.y = line + new_tank_bullet_position.y;
									setShotBunkerPosition(bunkerPosition);
								}
							}
						}
						else if(calculateBunkerNumber(tank) == BUNKER4){
							if(calculateBlockNumber(BUNKER4, tank) != WRONG_BUNKER){
								uint8_t bunkerNumber = calculateBunkerNumber(tank);
							    uint8_t blockNumber = calculateBlockNumber(bunkerNumber, tank);
								if(getErosionStage(bunkerNumber, blockNumber) != 3){
									stop = true;
									setDidTankKillBunkerFlag(true);
									point_t bunkerPosition;
									bunkerPosition.x = pixel + new_tank_bullet_position.x;
									bunkerPosition.y = line + new_tank_bullet_position.y;
									setShotBunkerPosition(bunkerPosition);
								}
							}
						}
						//if((calculateBlockNumber(calculateBunkerNumber(tank), tank) != WRONG_BUNKER) && ){

						//}
					}
					if(calculateAlienNumber(tank) != WRONG_ALIEN){
						if(isAlienAlive(calculateAlienNumber(tank))){
							stop = true;
							setDidTankKillAlienFlag(true);
							point_t deadAlienPosition;
							deadAlienPosition.x = pixel + new_tank_bullet_position.x;
							deadAlienPosition.y = line + new_tank_bullet_position.y;
							setDeadAlienPosition(deadAlienPosition);
						}
					}
					if(frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == RED){
						//xil_printf("Did we come in here???? \n\r");
						if(calculateHitSaucer(tank)){
							stop = true;
						}
					}
					if(frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == WHITE){//!RED
						stop = true;
						setDidTankKillAlienFlag(true);
						point_t deadAlienPosition;
						deadAlienPosition.x = pixel + new_tank_bullet_position.x;
						deadAlienPosition.y = line + new_tank_bullet_position.y;
						setDeadAlienPosition(deadAlienPosition);
						//frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = RED; //Set to red
					}

					else if(frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == GREEN){//!RED
						stop = true;
						setDidTankKillBunkerFlag(true);
						point_t bunkerPosition;
						bunkerPosition.x = pixel + new_tank_bullet_position.x;
						bunkerPosition.y = line + new_tank_bullet_position.y;
						setShotBunkerPosition(bunkerPosition);
						//	frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = RED; //Set to red
					}
					//else if(frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == GREEN){//!RED
					//	frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = RED; //Set to red
					//}
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
					eraseTankBullet(old_tank_bullet_position);
					//frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = BLACK; //Make the last pixel black
					tank_Bullet_Drawn = false; //Bullet set to false
				}
			}
		}
	}
	return tank_Bullet_Drawn;
}
