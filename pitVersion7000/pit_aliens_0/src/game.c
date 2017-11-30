/*
 * game.c
 *  This should be in spaceInvadersWorkspaceRetake3
 *  Created on: Oct 20, 2017
 *      Author: superman
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sound.h"
#include "game.h"
#include "draw.h"
#include "draw_tank.h"
#include "draw_saucer.h"
#include "draw_aliens.h"
#include "score_keeping.h"
#include "draw_bunker.h"
#include "draw_tank_bullet.h"
#include "draw_alien_bullet.h"

/******* Stuff for shooting bullets for the aliens *******/
#define MAX_NUMBER_OF_ALIENS_IN_A_ROW 11
#define ALIEN_BULLET_UPDATE_TIME 2500
#define ALIEN_BULLET_WAIT_TIME 300
#define NUMBER_OF_DIFFERENT_ALIEN_BULLET_TYPES 2

/******* Stuff for game play *******/
#define DEFAULT_LIVES 3

#define DEBOUNCE_COUNTER_MAX 5

#define SAUCER_Y_POSITION 29 // This is the Y position for when we draw the saucer.

#define RESET 0// Reset is 0

//ALIEN STUFF
#define MAX_ALIEN_BULLET 100
#define MIN_ALIEN_BULLET 50

//BULLET STUFF
#define BULLET_UPDATE_TIME 100
#define MAX_NUMBER_ALIEN_BULLETS 4
#define MAX_ALIEN_DEATH_TIME 100
#define TYPES_OF_ALIEN_BULLETS 2

//TANK STUFF
#define MAX_TANK_BULLET_TIME 100
#define MAX_TANK_DEATH_TIME 8
#define MAX_EXPLOSION_COUNT 20

//BUNKER STUFF
#define BLANK_BLOCK_1 9 //This is the blank block for the bunkers
#define BLANK_BLOCK_2 10 //This is the blank block for the bunkers

#define BUTTON_TIME 10000000
#define NUMBER_LENGTH 2 //The length of a number is 2
#define NUMBER_LENGTH_ONE 1 //the length of a number is 1

#define MAX_DEBOUNCE_TIME 100

/*#define SAUCER_NUMBER 66

#define SAUCER_MAX_TIME 2000 // This is the max time before a saucer will go across the board again.

#define SAUCER_SCORE_MAX_DRAWS 3 // This is how many times we will flash the score.
*/

#define DEBOUNCE_VALUE 0x0000001F

#define RANDOM_COUNTER_TOTAL 200

#define LEFT_BUTTON_MASK 8 //This is the mask for the left push button it moves the tank left.
#define MIDDLE_BUTTON_MASK 1 //This is the mask for the middle push button it shoots a bullet.
#define RIGHT_BUTTON_MASK 2 //This is the mask for the right push button it moves the tank right.
#define TOP_BUTTON_MASK 16 //This is the mask for the top push button it will be used fro incrementing volume eventually
#define BOTTOM_BUTTON_MASK 4 //This is the mask for the bottom push button it will be used for decrementing volume eventually

//#define SAUCER_SCORE_MAX_COUNTER 20 // 20 is a fifth of a second this is for flashing the score.
#define MAX_ALIEN_BULLET_TIME 10
//#define SAUCER_MOVE_MAX_COUNTER 5 // 10 is a tenth of a second for moving the saucer.

bool gameOver = 0;

bool getGameOverStatus(){
	return gameOver;
}

void setGameOverStatus(bool stat){
	gameOver = stat;
}

bool tankShot = 0;

bool getTankStatus(){
	return tankShot;
}

void setTankStatus(bool stat){
	tankShot = stat;
}

uint32_t updateBulletCounter = RESET;
uint8_t alienColumn = RESET;
uint32_t randomCounter = RESET;

uint8_t bunker1blocks[12] = {1,1,1,1,1,1,1,1,1,0,0,1};
uint8_t bunker2blocks[12] = {1,1,1,1,1,1,1,1,1,0,0,1};
uint8_t bunker3blocks[12] = {1,1,1,1,1,1,1,1,1,0,0,1};
uint8_t bunker4blocks[12] = {1,1,1,1,1,1,1,1,1,0,0,1};

uint32_t debouncedButtonState = 0;	// Saves the debounced button states

/****************** DRAW TANK BULLET STUFF *****************************/
bool shootTankBulletFlag = false;

/***************** FUNCTIONS *******************************************/
bool downBtnFlag = false;
bool upBtnFlag = false;

bool check = true;

uint8_t alienType;
uint8_t lives;
static uint8_t total_bullets;

uint32_t down_sound_count = RESET;
uint32_t up_sound_count = RESET;

extern uint32_t currentButtonState;

void debounce_buttons(){ //this takes the button and debounces it for us it also sets the flags for each button
	debouncedButtonState = currentButtonState & DEBOUNCE_VALUE;
	if(debouncedButtonState & MIDDLE_BUTTON_MASK){
		shootTankBulletFlag = true;
	}
}
/*void setSaucerDrawnFlag(bool value){
	drawSaucerFlag = value;
}

void setSaucerScoreFlag(bool value){
	drawSaucerScoreFlag = value;
}*/

void setDownBtnFlag(bool val){
	downBtnFlag = val;
}

void setUpBtnFlag(bool val){
	upBtnFlag = val;
}

bool getDownBtnFlag(){
	return downBtnFlag;
}

bool getUpBtnFlag(){
	return upBtnFlag;
}

bool saucerIsShot = 0;

bool getSaucerGotShot(){
	return saucerIsShot;
}

bool setSaucerGotShot(bool val){
	saucerIsShot = val;
}

enum SpaceInvadersControl_st{
	init_st,
	idle_st,
	update_bullet_st,
	dead_alien_st,
	flash_saucer_score_st,
	bunker_st,
	draw_saucer_st,
	new_alien_bullet_st,
	game_over_st,
	end_st
} currentState = init_st;

// Set the seed for the random-number generator.
void wamControl_setRandomSeed(uint32_t seed){

}

//print state machine for debug purposes
void debugStatePrint(){
	static enum SpaceInvadersControl_st previousState;
	static bool firstPass = true;
	// Only print the message if:
	// 1. This the first pass and the value for previousState is unknown.
	// 2. previousState != currentState - this prevents reprinting the same state name over and over.
	if((previousState != currentState) || firstPass) {
		firstPass = false;                // previousState will be defined, firstPass is false.
		previousState = currentState;     // keep track of the last state that you were in.
		switch(currentState){
		case init_st:
			xil_printf("INIT State\n\r");
			break;
		case idle_st:
			xil_printf("IDLE State\n\r");
			break;
		case update_bullet_st:
			xil_printf("UPDATE BULLETS State\n\r");
			break;
		case dead_alien_st:
			xil_printf("DEAD ALIEN State\n\r");
			break;
		case flash_saucer_score_st:
			xil_printf("FLASH_SAUCER_SCORE State\n\r");
			break;
		case bunker_st:
			xil_printf("BUNKER State\n\r");
			break;
		case draw_saucer_st:
			break;
		case new_alien_bullet_st:
			xil_printf("NEW ALIEN BULLET State\n\r");
			break;
		case game_over_st:
			break;
		default:
			xil_printf("spaceInvaders_tick update: hit default\n\r");
			break;
		}
	}
}
uint8_t wait = 0;

void spaceInvaders_tick(){
	//uint8_t isSaucerDrawn = RESET;
	point_t bunk_pos;
	uint8_t bunkerNumber;
	uint8_t blockNumber;


	//State actions
	switch(currentState){
	case init_st:
		initial_sound_init_tank_fire();
		initial_sound_init_tank_hit();
		initial_sound_init_alien_hit();
		initial_sound_init_move1();
		initial_sound_init_move2();
		initial_sound_init_move3();
		initial_sound_init_move4();
		initial_sound_init_saucer_move();
		initial_sound_init_saucer_hit();
		setGameOverStatus(false);
		setTankStatus(false);
		//drawSaucerFlag = false; //Saucer flag set to false
		//saucerMoveCounter = RESET; //Saucer counter initialized to 0
		//saucerRandValueCounter = RESET; // Reset this random value saucer counter.
		lives = DEFAULT_LIVES;
		randomCounter = RANDOM_COUNTER_TOTAL;//Increment the random counter
		srand(randomCounter); //Pass the random counter as the seed to srand
		//saucerRandValueMax = RESET; //TODO initialize to rand() % x
		break;
	case idle_st:
		total_bullets = getAlienBulletCount() + getBulletDrawn();
		debounce_buttons();
		if((currentButtonState & BOTTOM_BUTTON_MASK )){ //The down button was pressed
			down_sound_count++; //Increment counter
		}
		else{
			setDownBtnFlag(false); //Set flag
			down_sound_count = RESET; //Reset counter
		}
		if(down_sound_count >= DEBOUNCE_COUNTER_MAX){
			setDownBtnFlag(true); //Set flag to true
		}
		if((currentButtonState & TOP_BUTTON_MASK )){ //The up button was pressed
			up_sound_count++; //iIncrement counter
		}
		else{
			setUpBtnFlag(false); //Set flag
			up_sound_count = RESET; //reset counter
		}
		if(up_sound_count >= DEBOUNCE_COUNTER_MAX){
			setUpBtnFlag(true); //Set flag to true
		}
		if(total_bullets != RESET){
			updateBulletCounter++;
		}
		/*if(drawSaucerScoreFlag){
			saucerScoreFlashCounter++;
		}
		if(drawSaucerFlag){ // If the saucer is supposed to be drawn
			saucerMoveCounter++; // Increment the time for how long between when we move the saucer
		}
		else{ // Otherwise there is no saucer on the screen
			saucerRandValueCounter++; // So we have to count between when the next suacer get's drawn.
			if(saucerRandValueCounter >= saucerRandValueMax){ // If we get above our saucer random max then
				drawSaucerFlag = true; // We'll need to set our draw saucer flag to true
				saucerRandValueMax = + (rand() % SAUCER_MAX_TIME); // We'll need to generate a new random saucer max
				saucerRandValueCounter = RESET; // We'll need to reset the saucer rand value counter.
			}
		}*/
		if(shootTankBulletFlag && !getTankStatus()){
			wait++;
			if(wait >= 3){
				wait = RESET;
				shootTankBulletFlag = false;
				drawTankBullet();
			}
		}
		break;
	case update_bullet_st:
		updateBulletCounter = RESET;
		updateTankBullet();
		updateAllBullets();
		break;
	case dead_alien_st:
		check = true;
		if(didTankKillAlien()){
			uint8_t deadAlien = calculateAlienNumber(getDeadAlienPosition());
			if(getTankLaserBullet()){
				if(getFunBulletStatus() == false){
					check = decrementScore(100);
					drawScore();
				}
				if(isAlienAlive(deadAlien) && check){
					uint8_t alienColumn = getAlienColumn(deadAlien);
					uint8_t i;
					for(i = 0; i < 5; i++){
						uint8_t alien_to_kill = alienColumn + (i * 11);
						if(isAlienAlive(alien_to_kill)){
							killAlien(alien_to_kill);
							computeScore(alien_to_kill);
						}
					}
				}
			}
			else if(getTankExplosionBullet()){
				if(getFunBulletStatus() == false){
					check = decrementScore(50);
					drawScore();
				}
				if((isAlienAlive(deadAlien)) && check){
					if(deadAlien < 11) { //we are the top row of aliens
						if(deadAlien == 0){
							killAlien(deadAlien);
							computeScore(deadAlien);
							explosionKill(deadAlien, true, 1); //Kill Alien to the right
							explosionKill(deadAlien, true, 11); //Kill alien below
							explosionKill(deadAlien, true, 12); //Kill alien below and to the right
						}
						else if(deadAlien == 10){
							killAlien(deadAlien);
							computeScore(deadAlien);
							explosionKill(deadAlien, false, 1); //Kill alien to the left
							explosionKill(deadAlien, true, 11); //Kill alien below
							explosionKill(deadAlien, true, 10); //Kill alien below and to the left
						}
						else{
							killAlien(deadAlien);
							computeScore(deadAlien);
							explosionKill(deadAlien, true, 1); //Kill alien to the right
							explosionKill(deadAlien, false, 1); //kill alien to the left
							explosionKill(deadAlien, true, 11); //Kill alien below
							explosionKill(deadAlien, true, 10); //Kill alien below and to the right
							explosionKill(deadAlien, true, 12); //Kill alien below and to the left
						}
					}
					else if(deadAlien > 43) { //we are the bottom row of aliens
						if(deadAlien == 44){
							killAlien(deadAlien);
							computeScore(deadAlien);
							explosionKill(deadAlien, true, 1); //Kill Alien to the right
							explosionKill(deadAlien, false, 11); //Kill alien above
							explosionKill(deadAlien, false, 10); //Kill alien above and to the right
						}
						else if(deadAlien == 54){
							killAlien(deadAlien);
							computeScore(deadAlien);
							explosionKill(deadAlien, false, 1); //Kill alien to the left
							explosionKill(deadAlien, false, 11); //Kill alien above
							explosionKill(deadAlien, false, 12); //Kill alien above and to the left
						}
						else{
							killAlien(deadAlien);
							computeScore(deadAlien);
							explosionKill(deadAlien, true, 1); //Kill alien to the right
							explosionKill(deadAlien, false, 1); //kill alien to the left
							explosionKill(deadAlien, false, 11); //Kill alien above
							explosionKill(deadAlien, false, 10); //Kill alien above and to the right
							explosionKill(deadAlien, false, 12); //Kill alien above and to the left
						}
					}
					else if((deadAlien == 11) || (deadAlien == 22) || (deadAlien == 33)){
						killAlien(deadAlien);
						computeScore(deadAlien);
						explosionKill(deadAlien, true, 1); //Kill Alien to the right
						explosionKill(deadAlien, true, 11); //Kill alien below
						explosionKill(deadAlien, true, 12); //Kill alien below and to the right
						explosionKill(deadAlien, false, 11); //Kill alien above
						explosionKill(deadAlien, false, 10); //Kill alien above and to the right
					}
					else if((deadAlien == 21) || (deadAlien == 32) || (deadAlien == 43)){
						killAlien(deadAlien);
						computeScore(deadAlien);
						explosionKill(deadAlien, false, 1); //Kill alien to the left
						explosionKill(deadAlien, true, 11); //Kill alien below
						explosionKill(deadAlien, true, 10); //Kill alien below and to the left
						explosionKill(deadAlien, false, 11); //Kill alien above
						explosionKill(deadAlien, false, 12); //Kill alien above and to the left
					}
					else{
						killAlien(deadAlien);
						computeScore(deadAlien);
						explosionKill(deadAlien, true, 1); //Kill Alien to the right
						explosionKill(deadAlien, true, 11); //Kill alien below
						explosionKill(deadAlien, true, 12); //Kill alien below and to the right
						explosionKill(deadAlien, false, 11); //Kill alien above
						explosionKill(deadAlien, false, 10); //Kill alien above and to the right
						explosionKill(deadAlien, false, 1); //Kill alien to the left
						explosionKill(deadAlien, true, 10); //Kill alien below and to the left
						explosionKill(deadAlien, false, 12); //Kill alien above and to the left
					}
				}
			}
			else{
				killAlien(calculateAlienNumber(getDeadAlienPosition()));
				computeScore(calculateAlienNumber(getDeadAlienPosition()));
			}
			if(!check){
				killAlien(calculateAlienNumber(getDeadAlienPosition()));
				computeScore(calculateAlienNumber(getDeadAlienPosition()));
			}
			drawScore();
			setDidTankKillAlienFlag(false);
		}
		/*if(didTankKillSaucer()){
			computeScore(SAUCER_NUMBER);
			drawScore();
			eraseSaucer();//said saucer also said calculateHit
			setDidTankKillSaucerFlag(false);
			drawSaucerFlag = false;
			drawSaucerScoreFlag = true;
		}*/
		break;
	case flash_saucer_score_st:
		/*if(eraseSaucerScoreFlag){
			eraseSaucerScore();
			numberOfFlashes++;
			eraseSaucerScoreFlag = false;
		}
		else{
			drawSaucerScore();
			eraseSaucerScoreFlag = true;
		}*/
		break;
	case bunker_st:
		bunk_pos = getShotBunkerPosition();
		bunkerNumber = calculateBunkerNumber(bunk_pos);
		blockNumber = calculateBlockNumber(bunkerNumber, bunk_pos);
		erodeBunker(bunkerNumber, blockNumber); // This erodes a certain block in a certain bunker.
		setDidTankKillBunkerFlag(false);
		break;
	case draw_saucer_st:
		/*isSaucerDrawn = drawSaucer();
		if(!isSaucerDrawn){
			sound_saucer_stop();
		}
		if(!isSaucerDrawn || didTankKillSaucer()){
			drawSaucerFlag = false;
		}
		break;
	case new_alien_bullet_st:
		alienColumn = (rand()%MAX_NUMBER_OF_ALIENS_IN_A_ROW);//Set the column alien number
		alienType = (rand()%TYPES_OF_ALIEN_BULLETS);
		if(getMyAlienNumber(alienColumn) != ALIEN_NULL){
			drawAlienBullet(alienColumn, alienType);
		}*/
		break;
	case game_over_st:
		setGameOverStatus(1);
		//eraseAllAliens();
		//eraseTank();
		//eraseBunkers();
		//eraseTheTankBullet();
		//eraseAllAlienBullets();
		clearScreen();
		drawGameOverMessage();
		break;
	case end_st:
		break;
	default:
		break;
	}

	//State transitions
	switch(currentState){
	case init_st:
		currentState = idle_st;
		break;
	case idle_st:
		if(lives == RESET || getAlienCount() == RESET || getGameOverStatus()){//|| cantGoLower()
			currentState = game_over_st;
		}
		/*else if(drawSaucerScoreFlag && (saucerScoreFlashCounter >= SAUCER_SCORE_MAX_COUNTER)  && (numberOfFlashes < SAUCER_SCORE_MAX_DRAWS)){
			currentState = flash_saucer_score_st;
			saucerScoreFlashCounter = RESET;
		}*/
		else if((updateBulletCounter >= 2)){//5 MAX_ALIEN_BULLET_TIME
			setSaucerGotShot(true);
			currentState = update_bullet_st;
		}
		/*else if(drawSaucerFlag && (saucerMoveCounter >= SAUCER_MOVE_MAX_COUNTER)){
			saucerMoveCounter = RESET;
			currentState = draw_saucer_st;
		}
		else{
			if(numberOfFlashes >= SAUCER_SCORE_MAX_DRAWS){
				drawSaucerScoreFlag = false;
				numberOfFlashes = RESET;
			}
			currentState = idle_st;
		}*/
		break;
	case update_bullet_st:
		if(didTankKillAlien() /*|| didTankKillSaucer()*/){
			currentState = dead_alien_st;
		}
		else if(didTankKillBunker() ){ //|| didAlienKillBunker()){
			currentState = bunker_st;
		}
		else{
			currentState = idle_st; //Go to idle state
		}
		break;
	case dead_alien_st:
		//xil_printf("The number of aliens left is: %d\n\r", getAlienCount());
		currentState = idle_st;
		break;
	case flash_saucer_score_st:
		currentState = idle_st;
		break;
	case bunker_st:
		currentState = idle_st;
		break;
	case draw_saucer_st:
		currentState = idle_st;
		break;
	case new_alien_bullet_st:
		currentState = idle_st;
		break;
	case game_over_st: //Doesn't go anywhere
		currentState = end_st;
		break;
	case end_st:
		break;
	default:
		break;
	}
}
