/*
 * spaceInvadersGame.c
 *
 *  Created on: Nov 2, 2017
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
#include "game.h"
#include "aliens_move_state_machine.h"
#define RESET 0// Reset is 0
#define ALIEN_MAX_MOVE_TIME 50

enum AlienInvaders_st{
	alien_init_st,
	alien_idle_st,
	alien_move_st,
	game_over_st
} alien_currentState = alien_init_st;

uint32_t alien_move_count;

void AlienInvaders_tick(){
	//Actions
	switch(alien_currentState){
	case alien_init_st:
		alien_move_count = RESET;
		break;
	case alien_idle_st:
		if(!getTankStatus()){
			alien_move_count++;
		}
		break;
	case alien_move_st:
		alien_move_count = RESET;
		drawAlienBlock(); //Draw the block of aliens
		break;
	case game_over_st:
		break;
	default:
		break;
	}

	//Transitions
	switch(alien_currentState){
	case alien_init_st:
		alien_currentState = alien_idle_st;
		break;
	case alien_idle_st:
		if(cantGoLower()){
			setGameOverStatus(true);
			clearScreen();
			drawGameOverMessage();
			alien_currentState = game_over_st;
		}
		else if(getGameOverStatus()){
			alien_currentState = game_over_st;
		}
		else if(alien_move_count >= ALIEN_MAX_MOVE_TIME){
			alien_currentState = alien_move_st;
		}
		break;
	case alien_move_st:
		if(getGameOverStatus()){
			alien_currentState = game_over_st;
		}
		else{
			alien_currentState = alien_idle_st;
		}
		break;
	case game_over_st:
		break;
	default:
		break;
	}
}


