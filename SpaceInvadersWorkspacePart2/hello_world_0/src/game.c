/*
 * game.c
 *
 *  Created on: Oct 20, 2017
 *      Author: superman
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

#define SAUCER_Y_POSITION 29 // This is the Y position for when we draw the saucer.

#define RESET 0// Reset is 0

#define BULLET_UPDATE_TIME 100

#define BLANK_BLOCK_1 9 //This is the blank block for the bunkers
#define BLANK_BLOCK_2 10 //This is the blank block for the bunkers
#define BUTTON_TIME 10000000
#define NUMBER_LENGTH 2 //The length of a number is 2
#define NUMBER_LENGTH_ONE 1 //the length of a number is 1

#define MAX_DEBOUNCE_TIME 100
#define MAX_ALIEN_BULLET_TIME 5 //TODO from pull
#define MAX_TANK_BULLET_TIME 100
#define MAX_TANK_DEATH_TIME 100
#define MAX_NUMBER_ALIEN_BULLETS 4
#define MAX_ALIEN_DEATH_TIME 100

#define MOVE_LEFT 4 //move left by 4
#define MOVE_RIGHT 26 //move right by 26

#define SAUCER_NUMBER 66

#define SAUCER_MAX_TIME 2000 // This is the max time before a saucer will go across the board again.

#define DEBOUNCE_VALUE 0x0000001F

#define LEFT_BUTTON_MASK 8 //This is the mask for the left push button it moves the tank left.
#define MIDDLE_BUTTON_MASK 1 //This is the mask for the middle push button it shoots a bullet.
#define RIGHT_BUTTON_MASK 2 //This is the mask for the right push button it moves the tank right.
#define TOP_BUTTON_MASK 16 //This is the mask for the top push button it will be used fro incrementing volume eventually
#define BOTTOM_BUTTON_MASK 4 //This is the mask for the bottom push button it will be used for decrementing volume eventually

#define TANK_MOVE_MAX_COUNTER 5 // 5 is a 50th of a second
#define ALIEN_MOVE_MAX_COUNTER 50 // 50 is a half second since the interrupt happens every 10 mS.
#define SAUCER_MOVE_MAX_COUNTER 10 // 10 is a tenth of a second for moving the saucer.

uint16_t alien_bullets = RESET; //Count for the number of alien bullets on the screen
uint32_t alienCounter = RESET; //Alien counter initialized to 0
uint16_t debounceCounter = RESET; //Debounce counter initialized to 0
uint16_t alienDeathCounter = RESET; //Alien Death Counter initialized to 0
uint16_t tankDeathCounter = RESET; //Tank death counter initialized to 0
uint16_t tankBulletFiredMinCounter = RESET; //Bullet Fired Min COunter initialized to 0
uint16_t alienBulletFiredMinCounter = RESET; //Bullet Fired Min COunter initialized to 0

uint32_t updateBulletCounter = RESET;

uint32_t randomCounter = RESET;


uint8_t bunker1blocks[12] = {1,1,1,1,1,1,1,1,1,0,0,1};
uint8_t bunker2blocks[12] = {1,1,1,1,1,1,1,1,1,0,0,1};
uint8_t bunker3blocks[12] = {1,1,1,1,1,1,1,1,1,0,0,1};
uint8_t bunker4blocks[12] = {1,1,1,1,1,1,1,1,1,0,0,1};

uint32_t alienBulletMaxValue = RESET; //Alien bullet max value is initialized to 0
uint16_t alienRandValue = RESET; //

uint8_t alienColumn = RESET;
uint8_t alienBulletType = RESET;

bool alienDeathFlag = false; //Flag for alien death
bool tankDeathFlag = false; //Flag for tank death
bool bulletFireFlag = false; //Flag for whether a bullet has been fired

bool move_alien_recieved_flag = false; //Flag to let us know we went into the alien moved state;
bool button_pressed_recieved_flag = false; //Flag to let us know we went into the button pressed state
bool tank_bullet = false; //Bool for tank bullet

uint32_t debouncedButtonState = 0;	// Saves the debounced button states

/****************** DRAW TANK STUFF ************************************/
uint16_t tankMoveCounter = RESET; //Tank move counter initialized to 0
uint8_t moveTankCounter = RESET;

bool moveLeftFlag = false;
bool moveRightFlag = false;

bool shootAlienCrossBulletFlag = false;

/****************** DRAW TANK BULLET STUFF *****************************/
bool shootTankBulletFlag = false;

/****************** DRAW SUACER STUFF **********************************/
uint16_t saucerMoveCounter = RESET; // This is the counter that counts how long between when we update saucer draw.
uint16_t saucerRandValueCounter = RESET; // This is the time that we have between drawing saucers
uint16_t saucerRandValueMax = RESET; // This value will hold the recalculated max for the Random Value counter

bool drawSaucerFlag = false; // Tells us to draw the saucer
bool saucerDrawnFlag = false;

/***************** FUNCTIONS *******************************************/

uint32_t interruptCounter = 0;

extern uint32_t currentButtonState;

void debounce_buttons(){ //this takes the button and debounces it for us it also sets the flags for each button
	debouncedButtonState = currentButtonState & DEBOUNCE_VALUE;
	if((debouncedButtonState & LEFT_BUTTON_MASK) && !(debouncedButtonState & RIGHT_BUTTON_MASK)){
		moveLeftFlag = true;
		moveRightFlag = false;
	}
	if((debouncedButtonState & RIGHT_BUTTON_MASK) && !(debouncedButtonState & LEFT_BUTTON_MASK)){
		moveRightFlag = true;
		moveLeftFlag = false;
	}
	if(debouncedButtonState & MIDDLE_BUTTON_MASK){
		shootTankBulletFlag = true;
		shootAlienCrossBulletFlag = true;
	}
}

enum SpaceInvadersControl_st{
	init_st,
	idle_st,
	move_aliens_st,
	update_bullet_st,
	dead_alien_st,
	bunker_st,
	dead_tank_st,
	move_tank_right_st,
	move_tank_left_st,
	draw_saucer_st,
	new_alien_bullet_st
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
		case move_aliens_st:
			//xil_printf("MOVE ALIENS State\n\r");
			break;
		case update_bullet_st:
			xil_printf("UPDATE BULLETS State\n\r");
			break;
		case dead_alien_st:
			xil_printf("DEAD ALIEN State\n\r");
			break;
		case bunker_st:
			xil_printf("BUNKER State\n\r");
			break;
		case dead_tank_st:
			xil_printf("DEAD TANK State\n\r");
			break;
		case move_tank_right_st:
			break;
		case move_tank_left_st:
			break;
		case draw_saucer_st:
			break;
		case new_alien_bullet_st:
			xil_printf("NEW ALIEN BULLET State\n\r");
			break;
		default:
			xil_printf("spaceInvaders_tick update: hit default\n\r");
			break;
		}
	}

}
uint8_t isTankBulletDrawn = false;
uint8_t isAlienCrossBulletDrawn = false;
uint32_t alienBulletCounter;
void spaceInvaders_tick(){

	uint16_t saucerX;
	point_t saucer;
	uint8_t isSaucerDrawn = RESET;
	point_t bunk_pos;
	uint8_t bunkerNumber;
	uint8_t blockNumber;

	interruptCounter++;
	xil_printf("%d\n\r", interruptCounter);

	//State actions
	switch(currentState){
	case init_st:
		alienDeathFlag = false; //Alien Death flag set to false
		tankDeathFlag = false; //Tank Death flag set to false
		bulletFireFlag = false; //Bullet Fire flag set to false
		drawSaucerFlag = false; //Saucer flag set to false

		alienCounter = RESET; //Alien counter initialized to 0
		debounceCounter = RESET; //Debounce counter initialized to 0
		alienDeathCounter = RESET; //Alien Death Counter initialized to 0
		tankDeathCounter = RESET; //Tank death counter initialized to 0
		tankBulletFiredMinCounter = RESET; //Bullet Fired Min COunter initialized to 0
		alienBulletFiredMinCounter = RESET; //Bullet Fired Min COunter initialized to 0
		saucerMoveCounter = RESET; //Saucer counter initialized to 0
		saucerRandValueCounter = RESET; // Reset this random value saucer counter.
		alienBulletCounter = RESET;
		moveTankCounter = RESET; //Tank move counter initialized to 0
		moveLeftFlag = false;
		moveRightFlag = false;

		randomCounter = 200;//Increment the random counter //TODO from pull
		srand(randomCounter); //Pass the random counter as the seed to srand
		alienRandValue = rand() % MAX_NUMBER_OF_ALIENS_IN_A_ROW; //TODO initialize to rand() % y
		saucerRandValueMax = RESET; //TODO initialize to rand() % x

		break;
	case idle_st:
		debounce_buttons();
		//xil_printf("Alien Counter is: %d\n\r", alienCounter);

		moveTankCounter++; // This is a counter to know the timing of when we need to move the tank.
		alienBulletCounter++; //
		alienCounter++;
		if(alien_bullets <= MAX_NUMBER_ALIEN_BULLETS){
			alienBulletMaxValue++;
			updateBulletCounter++;
		}


		if(drawSaucerFlag){ // If the saucer is supposed to be drawn
			saucerMoveCounter++; // Increment the time for how long between when we move the saucer
		}
		else{ // Otherwise there is no saucer on the screen
			saucerRandValueCounter++; // So we have to count between when the next suacer get's drawn.
			if(saucerMoveCounter >= saucerRandValueMax){ // If we get above our saucer random max then
				drawSaucerFlag = true; // We'll need to set our draw saucer flag to true
				saucerRandValueMax = rand() % SAUCER_MAX_TIME; // We'll need to generate a new random saucer max
				saucerRandValueCounter = RESET; // We'll need to reset the saucer rand value counter.
			}
		}
		if(shootTankBulletFlag){
			shootTankBulletFlag = false;
			isTankBulletDrawn = true;
			drawTankBullet();
		}
		//xil_printf("Alien bullet counter is: %d\n\r", alienBulletCounter);
		//if(alienBulletCounter >= ALIEN_BULLET_WAIT_TIME && !isAlienCrossBulletDrawn){
			//xil_printf("Do we make it in here????\n\r");
		//	shootAlienCrossBulletFlag = TRUE;
		//}

		if(shootAlienCrossBulletFlag){
			alienBulletCounter = RESET;
			shootAlienCrossBulletFlag = false;
			isAlienCrossBulletDrawn = true;
			//TODO
			alienColumn = (rand()%MAX_NUMBER_OF_ALIENS_IN_A_ROW);//Set the column alien number
			while(getMyAlienNumber(alienColumn) == ALIEN_NULL){ //If the column is null // TODO Get rid of the while loop this will cause major problems.
				alienColumn = (rand()%MAX_NUMBER_OF_ALIENS_IN_A_ROW);//Keep trying for a new column
			}
			drawCrossAlienBullet(alienColumn);
		}


		//if buttons are pressed
		//debounceCounter++;

		/*
			if(alienDeathFlag == true){
				alienDeathCounter++;
			}
			if(saucerMoveCounter >= saucerRandValue){
				saucerDrawnFlag = true;
			}
			if(tank_bullet == true){
				tankBulletFiredMinCounter++;
			}
			if(alien_bullets > 0){
				alienBulletFiredMinCounter++;
			}
		 */
		break;
	case move_aliens_st:
		alienCounter = RESET; //Reset alien move counter
		//if(saucerDrawnFlag == true){
		//	saucerDrawnFlag = false;
		//call draw saucer function
		//}
		drawAlienBlock(); //Draw the block of aliens
		break;
	case update_bullet_st:
		updateBulletCounter = RESET;
		if(isTankBulletDrawn){
			//xil_printf("Do we come in here???? \n\r");
			isTankBulletDrawn = updateTankBullet();
		}
		if(isAlienCrossBulletDrawn){
			//xil_printf("Do we come in here\n\r");
			////isAlienCrossBulletDrawn = updateCrossAlienBullet();
			point_t check = getAlienCrossBulletPosition();
			check.y -= 10;
			//////eraseAlienCrossBullet(check);
		}
		//alien_bullets = updateAlienBullet();
		//xil_printf("Alien bullets: %d \n\r", alien_bullets);
		break;
	case dead_alien_st:
		if(didTankKillAlien()){
			killAlien(calculateAlienNumber(getDeadAlienPosition()));
			computeScore(calculateAlienNumber(getDeadAlienPosition()));
			setDidTankKillAlienFlag(false);
		}
		if(didTankKillSaucer()){
			computeScore(SAUCER_NUMBER);
			saucerX = getSaucerPosition();
			saucer.x = saucerX;
			saucer.y = SAUCER_Y_POSITION;
			eraseSaucer(setUpdatedTopLeftSaucer(getDeadSaucerPosition()));//said saucer also said calculateHit
			setDidTankKillSaucertoFalse();
			//isSaucerDrawn = false;//Not sure if we need this or it is correct
			drawSaucerFlag = false;
		}
		break;
	case bunker_st:
		bunk_pos = getShotBunkerPosition();
		bunkerNumber = calculateBunkerNumber(bunk_pos);
		blockNumber = calculateBlockNumber(bunkerNumber, bunk_pos);
		erodeBunker(bunkerNumber, blockNumber); // This erodes a certain block in a certain bunker.
		setDidTankKillBunkerFlag(false);
		//getShotBunkerPosition
		break;
	case dead_tank_st:
		break;
	case move_tank_right_st:
		drawTank(TANK_RIGHT);
		break;
	case move_tank_left_st:
		drawTank(TANK_LEFT);
		break;
	case draw_saucer_st:
		isSaucerDrawn = drawSaucer();
		if(!isSaucerDrawn || didTankKillSaucer()){
			drawSaucerFlag = false;
		}
		break;
	case new_alien_bullet_st:
		alienBulletMaxValue = RESET;
		alien_bullets++;
		//randomCounter = randomCounter % 20000; //TODO
		alienBulletType = rand()%NUMBER_OF_DIFFERENT_ALIEN_BULLET_TYPES; //Set the bullet type
		alienColumn = (rand()%MAX_NUMBER_OF_ALIENS_IN_A_ROW);//Set the column alien number
		while(getMyAlienNumber(alienColumn) == ALIEN_NULL){ //If the column is null //TODO try to get rid of this while loop because that could be a major problem with alien bullets.
			alienColumn = (rand()%MAX_NUMBER_OF_ALIENS_IN_A_ROW);//Keep trying for a new column
		}

		drawCrossAlienBullet(alienColumn);

		//fireAlienBullet(alienColumn, alienBulletType); //Call draw alien bullet with the column and bullet type //Said draw
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
		/*
			if(debounceCounter >= MAX_DEBOUNCE_TIME){ //Check for debounce time
				currentState = button_pressed_st;
			}
			else if(alienDeathCounter >= MAX_ALIEN_DEATH_TIME){
				currentState = dead_alien_st;
			}
			else if(((tank_bullet == true) && (tankBulletFiredMinCounter >= MAX_TANK_BULLET_TIME))|| ((alien_bullets > 0) && (alienBulletFiredMinCounter >= MAX_ALIEN_BULLET_TIME))){
				currentState = update_bullet_st;
			}
		 */

		if(moveRightFlag && (moveTankCounter >= TANK_MOVE_MAX_COUNTER)){
			moveTankCounter = RESET; // We reset the tank counter
			moveRightFlag = false; // Reset the flag.
			currentState = move_tank_right_st; // We need to go move the tank right.
		}
		else if(moveLeftFlag && (moveTankCounter >= TANK_MOVE_MAX_COUNTER)){ // Basically if a button is pushed
			moveTankCounter = RESET; // We reset the tank counter
			moveLeftFlag = false; // Reset the flag.
			currentState = move_tank_left_st; // We need to go move the tank left.
		}
		//else if(){

		//}
		/*
		if((alien_bullets < 4) && (alienBulletMaxValue >= randomCounter)){//TODO
			currentState = new_alien_bullet_st;
		}*/
		else if((alien_bullets <= MAX_NUMBER_ALIEN_BULLETS) &&(updateBulletCounter >= MAX_ALIEN_BULLET_TIME)){//5 MAX_ALIEN_BULLET_TIME //TODO from pull
			currentState = update_bullet_st;
		}

		else if(alienCounter >= ALIEN_MOVE_MAX_COUNTER){ //Check for time to move aliens
			currentState = move_aliens_st;
		}
		else if(drawSaucerFlag && saucerMoveCounter >= SAUCER_MOVE_MAX_COUNTER){
			saucerMoveCounter = RESET;
			currentState = draw_saucer_st;
		}
		else{
			currentState = idle_st;
		}
		break;
	case move_aliens_st:
		currentState = idle_st;
		break;
	case update_bullet_st:
		//if bullet has collision with bunker
		//currentState = bunker_st; //Go to bunker state
		//else if tank bullet has collision with alien
		//currentState = deadAlienSt; //Go to dead alien state
		alienDeathFlag = true;
		if(didTankKillAlien() || didTankKillSaucer()){
			currentState = dead_alien_st;
		}
		else if(didTankKillBunker()){
			currentState = bunker_st;
		}
		else{
			//else if alien bullet has collision with tank
			//currentState = deadTankSt; //Go to dead tank state
			//else
			currentState = idle_st; //Go to idle state
		}
		break;
	case dead_alien_st:
		currentState = idle_st;
		break;
	case bunker_st:
		currentState = idle_st;
		break;
	case dead_tank_st:
		/*
			if(tankDeathCounter >= MAX_TANK_DEATH_TIME){
				currentState = idle_st;
			}
			else{
				currentState = dead_tank_st;
			}

		 */
		break;
	case move_tank_right_st:
		currentState = idle_st;
		break;
	case move_tank_left_st:
		currentState = idle_st;
		break;
	case draw_saucer_st:
		currentState = idle_st;
		break;
	case new_alien_bullet_st:
		currentState = idle_st;
		break;
	default:
		break;
	}
}