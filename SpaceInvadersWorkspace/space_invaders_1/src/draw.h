/*
 * draw.h
 *
 *  Created on: Oct 5, 2017
 *      Author: superman
 */

#ifndef DRAW_H_
#define DRAW_H_

#include <stdint.h>

#define TANK_LEFT 1 // Tells the tank it needs to move left.
#define TANK_RIGHT 2 // Tells the tank it needs to move right.
#define TANK_STAY 0 // Tells the tank it needs to stay put.

#define BUNKER_1 0 // The number assigned to bunker 1.
#define BUNKER_2 1 // The number assigned to bunker 1.
#define BUNKER_3 2 // The number assigned to bunker 1.
#define BUNKER_4 3 // The number assigned to bunker 1.

#define NUMBER_OF_ALIEN_BULLETS 4 // The number of bullets the aliens can shoot.

typedef struct point_t { // A new data structure to hold the x and y coordinates for individaul parts.
	uint16_t x;
	uint16_t y;
};

typedef struct point_t point_t; // Andy you put this here because according to Kelly you didn't like my declaration of point_t I'm gonna have to ask you about that later.
int8_t getMyAlienNumber(int8_t alienIndex); // This get's the aleins number.

void setTankPosition(uint16_t val); // This sets the tank's position.
uint16_t getTankPosition(); // This gets the tank's position.

void setTankBulletPosition(point_t val); // This sets the tank's bullet position.
point_t getTankBulletPosition(); // This gets the tank's bullet position.

void setAlienBlockPosition(point_t val); // This sets the aliens' block position.
point_t getAlienBlockPosition(); // This gets the aliens' block position

void setAlienBulletPosition(point_t val, uint8_t bullet_number); // This sets the alien's bullet position for a given bullet number.
point_t getAlienBulletPosition(uint8_t bullet_number); // This gets the alien's bullet position for a given bullet numbe.r

void drawAlienBullet(uint8_t alien_number, uint8_t bullet_type); // Draws the alien's bullet.
uint8_t updateAlienBullet(); // Updates the aliens bullet.

point_t calculateAlienPosition(uint8_t alien_number); // This calculates an individual aleins posisiton.

void killAlien(uint8_t alien_number); // This kills an individual alein.

void drawAlienBlock(); // This draws the entire aliens block.

void erodeBunker(uint8_t bunker_number, uint8_t block_number); // This erodes a certain block in a certain bunker.

void drawTankBullet(); // This draws the tank's bullet.
uint8_t updateTankBullet(); // Updates the tank's bullet.

void drawTank(uint8_t direction); // This draws the tank.

unsigned int * draw_start_screen(); // This draws the inital start screen.

#endif /* DRAW_H_ */
