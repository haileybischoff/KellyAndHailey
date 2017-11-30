/*
 * draw_aliens.h
 *
 *  Created on: Oct 20, 2017
 *      Author: superman
 */

#ifndef DRAW_ALIENS_H_
#define DRAW_ALIENS_H_

#include <stdint.h>
#include <stdbool.h>
#include "draw.h"

#define ALIEN_NULL -1 //Null
#define WRONG_ALIEN 61

/******* The start of alien rows *******/
#define ALIEN_ROW_1 11 //Alien row 1
#define ALIEN_ROW_2 22 //Alien row 2
#define ALIEN_ROW_3 33 //Alien row 3
#define ALIEN_ROW_4 44 //Alien row 4
#define ALIEN_ROW_5 55 //Alien row 5

void initializeAlienBlock(); // This initializes the alien block position.

int8_t getMyAlienNumber(int8_t alienIndex); // This get's the aliens number.

uint16_t getAlienCount(); //Get the number of aliens

bool isAlienAlive(uint8_t alienIndex); // This returns true if the given alien is alive.

bool didTankKillAlien(); //Set if tank killed an alien

void setDeadAlienPosition(point_t deadAlienPosition); //Set the position of the dead alien

void eraseAlien(uint16_t x_position, uint16_t y_position); //, uint8_t alien_type);

void eraseAllAliens(); //Erase all of the aliens

point_t getDeadAlienPosition(); //Get the position of the dead alien

void setDidTankKillAlienFlag(bool killAlien); //Set the flag for the tank killing an alien

void setAlienBlockPosition(point_t val); // This sets the aliens' block position.

point_t getAlienBlockPosition(); // This gets the aliens' block position

bool cantGoLower(); //Set the boundaries for the aliens to win

point_t calculateAlienPosition(uint8_t alien_number); // This calculates an individual aliens position.

uint8_t calculateAlienNumber(point_t some_position); // This calculates which alien is at the position.

uint8_t getAlienColumn(uint8_t alien_number);

uint8_t calculateBottomAlienBasedOnXPosition(point_t some_position);

void killAlien(uint8_t alien_number); // This kills an individual alien.

void drawAlienBlock(); // This draws the entire aliens block.

void explosionKill(uint8_t deadAlien, bool add, uint8_t value);


void setAlienColor();

#endif /* DRAW_ALIENS_H_ */
