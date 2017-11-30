/*
 * alien_bullet_state_machine.c
 *
 *  Created on: Nov 20, 2017
 *      Author: superman
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "draw.h"
#include "draw_aliens.h"
#include "draw_alien_bullet.h"
#include "draw_bunker.h"
#include "draw_tank.h"
#include "draw_tank_bullet.h"
#include "game.h"
#include "score_keeping.h"

#define RESET 0
#define MAXIMUM_NUMBER_ALIEN_BULLETS 4
#define MIN_ALIEN_BULLET 50
#define MAX_ALIEN_BULLET 100
#define MAX_NUMBER_OF_ALIENS_IN_A_ROW 11
#define TYPES_OF_ALIEN_BULLETS 2
#define RANDOM_COUNTER_TOTAL 200
#define MAX_TANK_DEATH_TIME 8
#define MAX_EXPLOSION_COUNT 20
#define DEFAULT_LIVES 3


enum AlienBullet_st{
	alien_bullet_init_st,
	alien_bullet_idle_st,
	alien_bullet_update_st,
	alien_kill_bunker_st,
	alien_kill_tank_st,
	explosion_tank_st,
	game_over_st
} alien_bullet_currentState = alien_bullet_init_st;

uint32_t alien_bullet_counter = RESET;
uint8_t alien_column = RESET;
uint8_t alien_type;
bool alien_bullet_shot = false;
uint32_t random_counter = RESET;
uint8_t tank_explosion_counter = RESET;
uint16_t tank_death_counter = RESET; //Tank death counter initialized to 0
uint8_t game_lives;
uint8_t maximum_alien_bullet = RESET;
point_t bunker_pos;
uint8_t bunker_number;
uint8_t block_number;
uint8_t between_bullets = RESET;

void AlienBullet_tick(){

	//Actions
	switch(alien_bullet_currentState){
	case alien_bullet_init_st:
		maximum_alien_bullet = RESET; // The max for shooting a random bullet.
		game_lives = DEFAULT_LIVES;
		alien_bullet_counter = RESET;
		random_counter = RANDOM_COUNTER_TOTAL;//Increment the random counter
		srand(random_counter); //Pass the random counter as the seed to srand
		break;

	case alien_bullet_idle_st:
		alien_bullet_counter++;
		between_bullets++;
		if((getAlienBulletCount() < 4)){//needs to say less than 4
			if(between_bullets >= maximum_alien_bullet){
				maximum_alien_bullet = 20 + (rand() % 70);
				//xil_printf("this is the new number: %d\n\r", maximum_alien_bullet);
				between_bullets = RESET;
				//xil_printf("ALIEN BULLET count is: %d\n\r", getAlienBulletCount());
				alien_bullet_shot = true;
			}
		}
		if(alien_bullet_shot){
			alien_bullet_counter = RESET;
			alien_bullet_shot = false;
			alien_column = (rand()%MAX_NUMBER_OF_ALIENS_IN_A_ROW);//Set the column alien number
			alien_type = (rand()%TYPES_OF_ALIEN_BULLETS);
			if(getMyAlienNumber(alien_column) != ALIEN_NULL){
				//xil_printf("do we ever shoot an alien bullet with alien column: %d and type %d?\n\r", alien_column, alien_type);
				drawAlienBullet(alien_column, alien_type);
			}
		}
		if(didAlienKillTank()){
			tank_death_counter = RESET;
			eraseExplosion();
			setDidAlienKillTankFlag(false);
			drawLife(BUNKER_1_X_POSITION, TANK_Y_POSITION); //Draw tank
			setTankPosition(BUNKER_1_X_POSITION); // This sets the tank's position.
		}
		break;

	case alien_bullet_update_st:
		alien_bullet_counter = RESET;
		//xil_printf("we should be updating this bullet!\n\r");
		updateEachBullet();
		break;

	case alien_kill_bunker_st:
		bunker_pos = getShotBunkerPosition();
		bunker_number = calculateBunkerNumber(bunker_pos);
		block_number = calculateBlockNumber(bunker_number, bunker_pos);
		erodeBunker(bunker_number, block_number); // This erodes a certain block in a certain bunker.
		setDidTankKillBunkerFlag(false);
		setDidAlienKillBunkerFlag(false);
		break;
	case alien_kill_tank_st:
		if(tank_explosion_counter == RESET){
			explodeTank();
		}
		tank_explosion_counter++;
		break;
	case explosion_tank_st:
		if(tank_explosion_counter == RESET){
			explodeTankTwo();
		}
		tank_explosion_counter++;
		break;
	case game_over_st:
		setGameOverStatus(1);
		//eraseAllAliens();
		//eraseTank();
		//eraseBunkers();
		//eraseTheTankBullet();
		//eraseAllAlienBullets();
		break;
	default:

		break;
	}

	//Transitions
	switch(alien_bullet_currentState){
	case alien_bullet_init_st:
		alien_bullet_currentState = alien_bullet_idle_st;
		break;
	case alien_bullet_idle_st:
		if(game_lives == RESET || getAlienCount() == RESET || getGameOverStatus()){//|| cantGoLower()
			clearScreen();
			drawGameOverMessage();
			alien_bullet_currentState = game_over_st;
		}
		else if(alien_bullet_counter >= 5){
			alien_bullet_currentState = alien_bullet_update_st;
		}
		break;
	case alien_bullet_update_st:
		if(getGameOverStatus()){
			alien_bullet_currentState = game_over_st;
		}
		else if(didAlienKillTank()){
			eraseTheTankBullet();
			eraseAllAlienBullets();
			setTankStatus(true);
			alien_bullet_currentState = alien_kill_tank_st;
		}
		else if(didAlienKillBunker()){
			alien_bullet_currentState = alien_kill_bunker_st;
		}
		else{
			alien_bullet_currentState = alien_bullet_idle_st;
		}
		break;
	case alien_kill_bunker_st:
		alien_bullet_currentState = alien_bullet_idle_st;
		break;
	case alien_kill_tank_st:
		if(tank_explosion_counter >= MAX_EXPLOSION_COUNT){
			tank_explosion_counter = RESET;
			tank_death_counter++;
			alien_bullet_currentState = explosion_tank_st;
		}
		break;
	case explosion_tank_st:
		if(tank_death_counter >= MAX_TANK_DEATH_TIME){
			game_lives--;
			eraseLives(game_lives);
			setTankStatus(false);
			alien_bullet_currentState = alien_bullet_idle_st;
		}
		if(tank_explosion_counter >= MAX_EXPLOSION_COUNT){
			tank_explosion_counter = RESET;
			tank_death_counter++;
			alien_bullet_currentState = alien_kill_tank_st;
		}
		break;
	case game_over_st:

		break;
	default:

		break;
	}

}
