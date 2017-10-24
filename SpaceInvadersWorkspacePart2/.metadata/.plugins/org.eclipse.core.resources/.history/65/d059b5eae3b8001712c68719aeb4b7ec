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

bool isAlienAlive(uint8_t alienIndex); // This returns true if the given alien is alive.

bool didTankKillAlien();

void setDeadAlienPosition(point_t deadAlienPosition);

point_t getDeadAlienPosition();

void setDidTankKillAlienFlag(bool killAlien);

void setAlienBlockPosition(point_t val); // This sets the aliens' block position.

point_t getAlienBlockPosition(); // This gets the aliens' block position

point_t calculateAlienPosition(uint8_t alien_number); // This calculates an individual aliens position.

uint8_t calculateAlienNumber(point_t some_position); // This calculates which alien is at the position.

void killAlien(uint8_t alien_number); // This kills an individual alien.

void drawAlienBlock(); // This draws the entire aliens block.

#endif /* DRAW_ALIENS_H_ */
