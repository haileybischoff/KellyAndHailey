/*
 * tank_bullet_state_machine.c
 *
 *  Created on: Nov 18, 2017
 *      Author: superman
 */

//THIS DOES NOT WORK DONT USE IT!!!!

#include "tank_bullet_state_machine.h"
#include "draw_tank_bullet.h"
#include "draw_saucer.h"
#include "draw_aliens.h"
#include "score_keeping.h"
#include "game.h"
#include <stdint.h>
#include <stdbool.h>

#define DEBOUNCE_VALUE 0x0000001F
#define MIDDLE_BUTTON_MASK 1 //This is the mask for the middle push button it shoots a bullet.
#define RESET 0
#define SAUCER_NUMBER 66

bool TankBulletFiredFlag = false;
uint32_t AdebouncedButtonState = 0;	// Saves the debounced button states
extern uint32_t currentButtonState;

uint8_t AisTankBulletDrawn = false;
uint32_t updateTankBulletCounter = RESET;

void Adebounced_buttons(){ //this takes the button and debounces it for us it also sets the flags for each button
	AdebouncedButtonState = currentButtonState & DEBOUNCE_VALUE;
	if(AdebouncedButtonState & MIDDLE_BUTTON_MASK){
		TankBulletFiredFlag = true;
		//shootAlienCrossBulletFlag = true;
	}
}

enum TankBullet_st{
	tank_bullet_init_st,
	tank_bullet_idle_st,
	tank_bullet_update_st,
	tank_kill_st,
	game_over_st
} tank_bullet_currentState = tank_bullet_init_st;



void TankBullet_tick(){

	//Actions
	switch(tank_bullet_currentState){
	case tank_bullet_init_st:
		updateTankBulletCounter = RESET;
		break;
	case tank_bullet_idle_st:
		Adebounced_buttons();
		if(TankBulletFiredFlag){
			drawTankBullet();
			TankBulletFiredFlag = false;
			AisTankBulletDrawn = true;
		}
		if(getBulletDrawn()){
			updateTankBulletCounter++;
		}
		break;
	case tank_bullet_update_st:
		updateTankBulletCounter = RESET;
		AisTankBulletDrawn = updateTankBullet();
		break;
	case tank_kill_st:
		if(didTankKillAlien()){
			killAlien(calculateAlienNumber(getDeadAlienPosition()));
			computeScore(calculateAlienNumber(getDeadAlienPosition()));
			drawScore();
			setDidTankKillAlienFlag(false);
		}
		if(didTankKillSaucer()){
			computeScore(SAUCER_NUMBER);
			drawScore();
			eraseSaucer();//said saucer also said calculateHit
			setDidTankKillSaucerFlag(false);
			setSaucerDrawnFlag(false);
			setSaucerScoreFlag(true);
			//drawSaucerFlag = false;
			//drawSaucerScoreFlag = true;
		}
		break;
	case game_over_st:

	break;
	default:

		break;
	}


	//Transitions
	switch(tank_bullet_currentState){
	case tank_bullet_init_st:
		tank_bullet_currentState = tank_bullet_idle_st;
		break;
	case tank_bullet_idle_st:
		if(updateTankBulletCounter >= 1000){
			tank_bullet_currentState = tank_bullet_update_st;
		}
		break;
	case tank_bullet_update_st:
		if(didTankKillAlien() || didTankKillSaucer()){
			tank_bullet_currentState = tank_kill_st;
		}
		break;
	case tank_kill_st:
		tank_bullet_currentState = tank_bullet_idle_st;
		break;
	case game_over_st:
		break;
	default:

		break;
	}
}
