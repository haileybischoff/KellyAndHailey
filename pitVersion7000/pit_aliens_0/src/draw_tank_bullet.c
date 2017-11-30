/*
 * draw_tank_bullet.c
 *
 *  Created on: Oct 21, 2017
 *      Author: superman
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "draw_aliens.h"
#include "draw_alien_bullet.h"
#include "draw_bunker.h"
#include "draw_saucer.h"
#include "draw_tank.h"
#include "draw_tank_bullet.h"
#include "images.h"
#include "score_keeping.h"
#include "sound.h"

#define TANK_HALF_HEIGHT 8 //Half of the height for the tank is 8
#define TANK_HALF_WIDTH 14 //Half of the width for the tank
#define THREE_EROSION_PATTERNS 3
#define COLOR_CHOICES 10

#define SWITCH_0 128
#define SWITCH_1 64
#define SWITCH_2 32
#define SWITCH_3 16
#define SWITCH_4 8
#define SWITCH_5 4
#define SWITCH_6 2
#define SWITCH_7 1

extern uint32_t switches;

static uint32_t point_threshold = 0;

static bool score_0_firstPass = true;
static bool score_1_firstPass = true;
static bool score_2_firstPass = true;
static bool score_3_firstPass = true;
static bool score_4_firstPass = true;
static bool score_5_firstPass = true;
static bool score_6_firstPass = true;

static bool fun_bullets = false;

bool getFunBulletStatus(){
	return fun_bullets;
}

static point_t tankBulletPosition; //Variable to keep track of tank bullet position

static bool tankBulletsDrawn[5] = {false, false, false, false, false};

static point_t allTankBulletPositions[5];

static uint32_t bullet_colors[COLOR_CHOICES]={TURQUOISE, PINK, ORANGE, LIME, SKY, GOLD, PURPLE, BLUE, RED, WHITE};

extern unsigned int * frame_pointer;

static bool tank_Bullet_Drawn = false; //Was the tank bullet shot

static bool tank_Laser_Bullet = false;

static bool tank_Explosion_Bullet = false;

static bool tank_multiple_bullet = false; //TODO ERASE

static bool freeze_aliens = false;

static bool tank_Guided_Bullet = false;

static bool tank_Color_Bullet = false;//TODO

static bool colorAliens = false;

static bool rogueAlienBullet = false;

bool getFreezeAliens(){
	return freeze_aliens;
}

void setFreezeAliens(bool value){
	freeze_aliens = true;
}

void setTankLaserBullet(bool value){
	tank_Laser_Bullet = value;
}

bool getTankMultipleBullets(){
	return tank_multiple_bullet;
}

void setTankMultipleBullets(bool value){
	tank_multiple_bullet = value;
}

bool getWhichBulletDrawn(uint8_t number){
	return tankBulletsDrawn[number];
}

void setWhichBulletDrawn(uint8_t number, bool value){
	tankBulletsDrawn[number] = value;
}

bool getTankLaserBullet(){
	return tank_Laser_Bullet;
}

void setTankGuidedBullet(bool value){
	tank_Guided_Bullet = value;
}

void setTankExplosionBullet(bool value){
	tank_Explosion_Bullet = value;
}

bool getTankExplosionBullet(){
	return tank_Explosion_Bullet;
}

bool getRogueAlienBullet(){
	return rogueAlienBullet;
}

void setRogueAlienBullet(bool value){
	rogueAlienBullet = value;
}


void resetThresholdScoreFirstPass(){
	score_0_firstPass = false;
	score_1_firstPass = false;
	score_2_firstPass = false;
	score_3_firstPass = false;
	score_4_firstPass = false;
	score_5_firstPass = false;
	score_6_firstPass = false;
}

void setBulletType(){
	if(score_0_firstPass){
		point_threshold += SCORE_0;
		score_0_firstPass = false;
	}

	if(switches & SWITCH_7){
		fun_bullets = true;
		if(switches & SWITCH_0){
			tank_Color_Bullet = true;
			colorAliens = false;
			tank_Guided_Bullet = false;
			tank_Laser_Bullet = false;
			rogueAlienBullet = false;
			tank_Explosion_Bullet = false;
			freeze_aliens = false;
		}
		else if(switches & SWITCH_1){
			tank_Color_Bullet = true;
			colorAliens = true;
			tank_Guided_Bullet = false;
			tank_Laser_Bullet = false;
			rogueAlienBullet = false;
			tank_Explosion_Bullet = false;
			freeze_aliens = false;
		}
		else if(switches & SWITCH_2){
			tank_Color_Bullet = false;
			colorAliens = false;
			tank_Guided_Bullet = true;
			tank_Laser_Bullet = false;
			rogueAlienBullet = false;
			tank_Explosion_Bullet = false;
			freeze_aliens = false;
		}
		else if(switches & SWITCH_3){
			tank_Color_Bullet = false;
			colorAliens = false;
			tank_Guided_Bullet = false;
			tank_Laser_Bullet = true;
			rogueAlienBullet = false;
			tank_Explosion_Bullet = false;
			freeze_aliens = false;
		}
		else if(switches & SWITCH_4){
			tank_Color_Bullet = false;
			colorAliens = false;
			tank_Guided_Bullet = false;
			tank_Laser_Bullet = false;
			rogueAlienBullet = true;
			tank_Explosion_Bullet = false;
			freeze_aliens = false;
		}
		else if(switches & SWITCH_5){
			tank_Color_Bullet = false;
			colorAliens = false;
			tank_Guided_Bullet = false;
			tank_Laser_Bullet = false;
			rogueAlienBullet = false;
			tank_Explosion_Bullet = true;
			freeze_aliens = false;
		}
		else if(switches & SWITCH_6){
			tank_Color_Bullet = false;
			colorAliens = false;
			tank_Guided_Bullet = false;
			tank_Laser_Bullet = false;
			rogueAlienBullet = false;
			tank_Explosion_Bullet = false;
			freeze_aliens = true;
		}
	}
	else if((switches & SWITCH_0) && getScore() >= point_threshold){
		fun_bullets = false;
		tank_Color_Bullet = true;
		colorAliens = false;
		tank_Guided_Bullet = false;
		tank_Laser_Bullet = false;
		rogueAlienBullet = false;
		tank_Explosion_Bullet = false;
		freeze_aliens = false;
	}
	else if((switches & SWITCH_1) && getScore() >= point_threshold){
		if(score_1_firstPass){
			point_threshold += SCORE_1;
			score_1_firstPass = false;
		}
		fun_bullets = false;
		tank_Color_Bullet = true;
		colorAliens = true;
		tank_Guided_Bullet = false;
		tank_Laser_Bullet = false;
		rogueAlienBullet = false;
		tank_Explosion_Bullet = false;
		freeze_aliens = false;
	}
	else if((switches & SWITCH_2) && getScore() >= point_threshold){
		if(score_2_firstPass){
			point_threshold += SCORE_2;
			score_2_firstPass = false;
		}

		fun_bullets = false;
		tank_Color_Bullet = false;
		colorAliens = false;
		tank_Guided_Bullet = true;
		tank_Laser_Bullet = false;
		rogueAlienBullet = false;
		tank_Explosion_Bullet = false;
		freeze_aliens = false;
	}
	else if((switches & SWITCH_3) && getScore() >= point_threshold){
		if(score_3_firstPass){
			point_threshold += SCORE_3;
			score_3_firstPass = false;
		}

		fun_bullets = false;
		tank_Color_Bullet = false;
		colorAliens = false;
		tank_Guided_Bullet = false;
		tank_Laser_Bullet = true;
		rogueAlienBullet = false;
		tank_Explosion_Bullet = false;
		freeze_aliens = false;
	}
	else if((switches & SWITCH_4) && getScore() >= point_threshold){
		if(score_4_firstPass){
			point_threshold += SCORE_4;
			score_4_firstPass = false;
		}

		fun_bullets = false;
		tank_Color_Bullet = false;
		colorAliens = false;
		tank_Guided_Bullet = false;
		tank_Laser_Bullet = false;
		rogueAlienBullet = true;
		tank_Explosion_Bullet = false;
		freeze_aliens = false;
	}
	else if((switches & SWITCH_5) && getScore() >= point_threshold){
		if(score_5_firstPass){
			point_threshold += SCORE_5;
			score_5_firstPass = false;
		}

		fun_bullets = false;
		tank_Color_Bullet = false;
		colorAliens = false;
		tank_Guided_Bullet = false;
		tank_Laser_Bullet = false;
		rogueAlienBullet = false;
		tank_Explosion_Bullet = true;
		freeze_aliens = false;
	}
	else if((switches & SWITCH_6) && getScore() >= point_threshold){
		if(score_6_firstPass){
			point_threshold += SCORE_6;
			score_6_firstPass = false;
		}

		fun_bullets = false;
		tank_Color_Bullet = false;
		colorAliens = false;
		tank_Guided_Bullet = false;
		tank_Laser_Bullet = false;
		rogueAlienBullet = false;
		tank_Explosion_Bullet = false;
		freeze_aliens = true;
	}
	else{
		fun_bullets = false;
		tank_Color_Bullet = false;
		colorAliens = false;
		tank_Guided_Bullet = false;
		tank_Laser_Bullet = false;
		rogueAlienBullet = false;
		tank_Explosion_Bullet = false;
		freeze_aliens = false;
	}
}


uint32_t previous_tank_bullet_color = RED;
uint32_t tank_bullet_color = RED;

void setTankBulletColor(){
	bool check = true;
	if(tank_Color_Bullet){
		if(getFunBulletStatus() == false){
			check = decrementScore(SCORE_0);
			drawScore();
		}
		if(check){
			previous_tank_bullet_color = tank_bullet_color;
			uint8_t color_choice = rand() % COLOR_CHOICES;
			tank_bullet_color = bullet_colors[color_choice];
			if(previous_tank_bullet_color == tank_bullet_color){
				uint8_t new_color_choice = rand() % COLOR_CHOICES;
				tank_bullet_color = bullet_colors[new_color_choice];
			}
			if(previous_tank_bullet_color == tank_bullet_color){
				uint8_t new_color_choice = rand() % COLOR_CHOICES;
				tank_bullet_color = bullet_colors[new_color_choice];
			}
		}
	}
	else{
		tank_bullet_color = RED;
	}
	if(!check){
		tank_bullet_color = RED;
	}

}

uint32_t getTankBulletColor(){
	return tank_bullet_color;
}


void setTankBulletPosition(point_t val){ //Set the position of the tank bullet
	tankBulletPosition.x = val.x; //X position of bullet
	tankBulletPosition.y = val.y; //Y position of bullet
}


void setTheTankBulletPosition(point_t val, uint8_t number){
	allTankBulletPositions[number].x = val.x;
	allTankBulletPositions[number].y = val.y;
}

point_t getTheTankBulletPosition(uint8_t number){
	return allTankBulletPositions[number];
}

point_t getTankBulletPosition(){ //get position of the tank bullet
	return tankBulletPosition;
}

uint8_t getBulletDrawn(){ //Get the bullet drawn
	return tank_Bullet_Drawn;
}

void eraseTheTankBullet(){
	if(tank_Bullet_Drawn){
		point_t updateBullet = getTankBulletPosition(); //Get the tank position
		uint8_t line, pixel;
		for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
			for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
				frame_pointer[(line + updateBullet.y)*SCREEN_WIDTH + (pixel + updateBullet.x)] = BLACK; //Set to black
				tank_Bullet_Drawn = false;
			}
		}
	}
}

void eraseWhichTankBullet(uint8_t number){
	if(getWhichBulletDrawn(number)){
		point_t updateBullet = getTheTankBulletPosition(number); //Get the tank position
		uint8_t line, pixel;
		for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
			for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
				frame_pointer[(line + updateBullet.y)*SCREEN_WIDTH + (pixel + updateBullet.x)] = BLACK; //Set to black
				tank_Bullet_Drawn = false;
			}
		}
	}
}


point_t alien_position;
uint8_t targetedAlien;
uint16_t targetedXDistance;
uint16_t targetedXAlienPos;
uint8_t countNumberUp = 0;

void drawTankBullet(){
	bool check = true;
	bool multipleCheck = true;
	if(getTankMultipleBullets()){
		if(getFunBulletStatus() == false){
			multipleCheck = decrementScore(10);
			drawScore();
		}
		if(multipleCheck){
			uint8_t bullet_number = 33;
			uint8_t i;
			bool stop = false;
			for(i = 0; !stop && i < 5; i++){
				if(!getWhichBulletDrawn(i)){
					//xil_printf("we found an empty bullet %d\n\r", i);
					bullet_number = i;
					stop = true;
				}
			}
			if(bullet_number != 33){
				//xil_printf(" we have a real bullet number\n\r");
				countNumberUp++;
				setTankBulletColor();
				sound_init_tank_fire();
				setWhichBulletDrawn(bullet_number, true);
				point_t updateBullet;
				updateBullet.x = getTankPosition() + TANK_HALF_WIDTH; //move x position
				updateBullet.y = TANK_Y_POSITION - TANK_HALF_HEIGHT; //Move y position
				setTheTankBulletPosition(updateBullet, bullet_number);
				uint8_t line, pixel;
				for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
					for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
						frame_pointer[(line + updateBullet.y)*SCREEN_WIDTH + (pixel + updateBullet.x)] = tank_bullet_color; //Set to red
					}
				}
				if(countNumberUp > 5){
					//setTankMultipleBullets(false);//TODO
				}
			}
		}

	}
	//tankBulletsDrawn

	//if(!multipleCheck || !getTankMultipleBullets()){
		if(!tank_Bullet_Drawn){ //If not fired
			//setFreezeAliens(true);
			//xil_printf("back to normal\n\r");
			setTankBulletColor();
			sound_init_tank_fire();
			tank_Bullet_Drawn = true; //Set drawn to true
			//point_t bullet_from_tank_point = getTankBulletPosition();
			point_t updateBullet;
			updateBullet.x = getTankPosition() + TANK_HALF_WIDTH; //move x position
			updateBullet.y = TANK_Y_POSITION - TANK_HALF_HEIGHT; //Move y position
			setTankBulletPosition(updateBullet); //Set tank bullet position
			uint8_t line, pixel;
			for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
				for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
					frame_pointer[(line + updateBullet.y)*SCREEN_WIDTH + (pixel + updateBullet.x)] = tank_bullet_color; //Set to red
				}
			}
			///setTankGuidedBullet(true); //We need this to run the guided bullet especially for the updated bullet
			if(tank_Guided_Bullet){
				if(getFunBulletStatus() == false){
					check = decrementScore(SCORE_2);
					drawScore();
				}
				if(check){
					targetedAlien = calculateBottomAlienBasedOnXPosition(updateBullet);
					if(targetedAlien < 55){
						alien_position = calculateAlienPosition(targetedAlien);
						targetedXAlienPos = alien_position.x;
						targetedXDistance = abs(targetedXAlienPos - updateBullet.x);
						//we are on the right track
					}
					else{
						setTankGuidedBullet(false); //There is no alien to track //we may change this so you are guaranteed to kill an alien...
					}
				}
				else{
					setTankGuidedBullet(false); //There is no alien to track //we may change this so you are guaranteed to kill an alien...
				}
			}
		}
	//}
}

void eraseTankBullet(point_t bullet_pos){
	uint8_t line, pixel;
	for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
		for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
			frame_pointer[(line + bullet_pos.y) * SCREEN_WIDTH + (pixel + bullet_pos.x)] = BLACK; //Set to black
		}
	}
}

uint8_t tankMayErodeBunker(uint8_t bunkerNumber, uint8_t blockNumber, uint8_t pixel, uint8_t line, point_t new_tank_bullet_position){ //Tank erode bunker
	if(getErosionStage(bunkerNumber, blockNumber) != THREE_EROSION_PATTERNS){ //Get the erosion pattern
		setDidTankKillBunkerFlag(true);
		point_t bunkerPosition; //Bunker was hit
		bunkerPosition.x = pixel + new_tank_bullet_position.x; //Set position
		bunkerPosition.y = line + new_tank_bullet_position.y;
		setShotBunkerPosition(bunkerPosition); //Set bunker shot position
		return true;
	}
	else{
		return false;
	}
}

uint8_t whichBunkerNumber(point_t tank, uint8_t pixel, uint8_t line, point_t new_tank_bullet_position){ //Which bunker was it
	uint8_t stop = false;
	uint8_t bunkerNumber = calculateBunkerNumber(tank);
	uint8_t blockNumber = calculateBlockNumber(bunkerNumber, tank);
	if((calculateBunkerNumber(tank) == BUNKER1 && calculateBlockNumber(BUNKER1, tank) != WRONG_BUNKER)
			|| (calculateBunkerNumber(tank) == BUNKER2 && calculateBlockNumber(BUNKER2, tank) != WRONG_BUNKER)
			|| (calculateBunkerNumber(tank) == BUNKER3 && calculateBlockNumber(BUNKER3, tank) != WRONG_BUNKER)
			|| (calculateBunkerNumber(tank) == BUNKER4 && calculateBlockNumber(BUNKER4, tank) != WRONG_BUNKER)){
		stop = tankMayErodeBunker(bunkerNumber, blockNumber, pixel, line, new_tank_bullet_position); //Return the bunker
	}
	return stop;
}

uint8_t tankHitsAliens(uint8_t pixel, uint8_t line, point_t new_tank_bullet_position, point_t tank){ //Tank hits an alien
	uint8_t stop = false;
	bool check = true;
	bool rogueCheck = false;
	if(isAlienAlive(calculateAlienNumber(tank))){ //is the alien alive
		if(colorAliens){
			//eraseAlienBlock
			//eraseAllAliens();
			if(getFunBulletStatus() == false){
				check = decrementScore(SCORE_1);
				drawScore();
			}
			if(check){
				setAlienColor();
			}
		}
		if(getRogueAlienBullet()){
			if(!getFunBulletStatus()){
				rogueCheck = decrementScore(SCORE_4);
				drawScore();
			}
			if(rogueCheck || getFunBulletStatus()){
				stop = true;////Not sure about this
				setRogueBullet(true);
				point_t rogueAlienPosition;
				rogueAlienPosition.x = pixel + new_tank_bullet_position.x;
				rogueAlienPosition.y = line + new_tank_bullet_position.y;
				point_t rogueAlienBulletPosition = rogueAlienPosition;
				setRogueAlienNumber(calculateAlienNumber(tank));
				rogueAlienBulletPosition.y -= ALIEN_HEIGHT; //We are now above the alien
				rogueAlienBulletPosition.y -= ALIEN_BULLET_HEIGHT; //This should be the top of the alien bullet
				setRogueBulletPosition(rogueAlienBulletPosition);
				drawRogueBullet();//fire rogue alien bullet
				//make sure to update the rogue alien bullet
				//in update, if rogue alien bullet hits alien, kill that alien and reset the alien bullet position to top of alien
				//if rogue alien bullet hits the dead zone, kill alien and stop setting bullets
			}
		}
		if(!rogueCheck || colorAliens){
			stop = true;
			setDidTankKillAlienFlag(true); //Set flag to true
			point_t deadAlienPosition;
			deadAlienPosition.x = pixel + new_tank_bullet_position.x;
			deadAlienPosition.y = line + new_tank_bullet_position.y;
			setDeadAlienPosition(deadAlienPosition); //Set dead alien position
		}
	}
	return stop;
}

/*
point_t alien_position;
uint8_t targetedAlien;
uint16_t targetedXDistance;
uint16_t targetedXAlienPos;
 */
uint8_t updateTankBullet(){ //Update the tank bullet
	//bool laser = false;
	if(tank_Bullet_Drawn){
		point_t old_tank_bullet_position = getTankBulletPosition(); //Get tank bullet position
		point_t temp = old_tank_bullet_position;
		if(tank_Guided_Bullet){
			point_t new_alien_pos = calculateAlienPosition(targetedAlien);
			if(new_alien_pos.x != alien_position.x){
				alien_position = new_alien_pos;
				if(new_alien_pos.x > alien_position.x){
					temp.x += 4;
					//alien has moved right
				}
				else{
					temp.x -= 4;
					//alien has moved left
				}
			}
		}
		temp.y -= (FOUR_GAME_PIXELS); //Increment by 8 pixels
		setTankBulletPosition(temp); //Set tank bullet position
		point_t new_tank_bullet_position = getTankBulletPosition(); //Get tank bullet position
		uint8_t line, pixel;
		uint8_t stop = false;
		for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
			for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
				if(new_tank_bullet_position.y > ELEVEN_GAME_PIXELS && !stop){ //If we below the top of the screen and stop is not true
					point_t tank;
					tank.x = pixel + new_tank_bullet_position.x;
					tank.y = line + new_tank_bullet_position.y;
					if(calculateBunkerNumber(tank) != WRONG_BUNKER){ //Calculate the bunker number
						stop =  whichBunkerNumber(tank, pixel, line, new_tank_bullet_position);
					}
					if(calculateAlienNumber(tank) != WRONG_ALIEN){ //Calculate the alien number
						//xil_printf("do we kill an alien\n\r");
						stop = tankHitsAliens(pixel, line, new_tank_bullet_position, tank);
					}
					//if(frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == tank_bullet_color){
					if(calculateHitSaucer(tank)){ //if we hit the saucer
						stop = true;
					}
					//}
					else if(frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == BLACK){//!RED
						frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = tank_bullet_color; //Set to red
					}
					if(new_tank_bullet_position.x != old_tank_bullet_position.x){
						if(frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + old_tank_bullet_position.x)] == tank_bullet_color){ //Set to black
							frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y)*SCREEN_WIDTH + (pixel + old_tank_bullet_position.x)] = BLACK;//Set to black
						}
					}
					else{
						if(frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == tank_bullet_color){ //Set to black
							frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y)*SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = BLACK;//Set to black
						}
					}
				}
				else{
					frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = BLACK; //Make the last pixel black
					tank_Bullet_Drawn = false; //Bullet set to false
				}
				if(stop){
					eraseTankBullet(old_tank_bullet_position); //Erase the tank bullet
					eraseTankBullet(new_tank_bullet_position); //Erase the tank bullet
					tank_Bullet_Drawn = false; //Bullet set to false
				}
			}
		}
	}
	return tank_Bullet_Drawn;
}

void updateAllBullets(){

	//bool laser = false;
	uint8_t k;
	for(k = 0; k <5; k++){
		if(getWhichBulletDrawn(k)){
			point_t old_tank_bullet_position = getTheTankBulletPosition(k); //Get tank bullet position
			point_t temp = old_tank_bullet_position;
			temp.y -= (FOUR_GAME_PIXELS); //Increment by 8 pixels
			setTheTankBulletPosition(temp, k);//Set tank bullet position
			point_t new_tank_bullet_position = getTheTankBulletPosition(k); //Get tank bullet position
			uint8_t line, pixel;
			uint8_t stop = false;
			for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
				for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
					if(new_tank_bullet_position.y > ELEVEN_GAME_PIXELS && !stop){ //If we below the top of the screen and stop is not true
						point_t tank;
						tank.x = pixel + new_tank_bullet_position.x;
						tank.y = line + new_tank_bullet_position.y;

						if(calculateBunkerNumber(tank) != WRONG_BUNKER){ //Calculate the bunker number
							stop =  whichBunkerNumber(tank, pixel, line, new_tank_bullet_position);
						}

						if(calculateAlienNumber(tank) != WRONG_ALIEN){ //Calculate the alien number
							stop = tankHitsAliens(pixel, line, new_tank_bullet_position, tank);
						}

						//if(frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == tank_bullet_color){
						if(calculateHitSaucer(tank)){ //if we hit the saucer
							stop = true;
						}

						//}
						else if(frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == BLACK){//!RED
							frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = tank_bullet_color; //Set to red
						}
						if(new_tank_bullet_position.x != old_tank_bullet_position.x){
							if(frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + old_tank_bullet_position.x)] == tank_bullet_color){ //Set to black
								frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y)*SCREEN_WIDTH + (pixel + old_tank_bullet_position.x)] = BLACK;//Set to black
							}
						}
						else{
							if(frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == tank_bullet_color){ //Set to black
								frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y)*SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = BLACK;//Set to black
							}
						}
					}
					else{
						frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = BLACK; //Make the last pixel black
						setWhichBulletDrawn(k, false);
						///countNumberUp--;
					}
					if(stop){
						//TODO
						//eraseWhichTankBullet(old_tank_bullet_position);
						//eraseWhichTankBullet(new_tank_bullet_position);
						eraseTankBullet(old_tank_bullet_position); //Erase the tank bullet
						eraseTankBullet(new_tank_bullet_position); //Erase the tank bullet
						setWhichBulletDrawn(k, false);
					}
				}
			}
		}
	}

}


