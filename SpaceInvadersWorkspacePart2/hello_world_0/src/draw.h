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

typedef struct point_t { // A new data structure to hold the x and y coordinates for individual parts.
	uint16_t x;
	uint16_t y;
};

typedef struct point_t point_t; // Andy you put this here because according to Kelly you didn't like my declaration of point_t I'm gonna have to ask you about that later.
int8_t getMyAlienNumber(int8_t alienIndex); // This get's the aliens number.

uint8_t didTankKillAlien();
point_t getDeadAlienPosition();

void setDidTankKillAlientoFalse();

uint8_t updateCrossAlienBullet();


point_t getShotBunkerPosition();
uint8_t calculateBlockNumber(uint8_t bunkerNum, point_t bunkerPosition);
uint8_t calculateBunkerNumber(point_t bunkerPosition);
void setDidTankKillBunker();
uint8_t didTankKillBunker();

void setDidTankKillSaucertoFalse();
uint8_t didTankKillSaucer();
uint16_t update_saucer_x_position();
uint16_t getSaucerPosition();
void setSaucerPosition(uint16_t val);

uint8_t calculateHitSaucer(point_t some_point);

point_t setUpdatedTopLeftSaucer(point_t some_point);

void computeScore(uint8_t alien_number);

uint32_t getScore();
void setScore(uint32_t score);

point_t getDeadSaucerPosition();


void setTankPosition(uint16_t val); // This sets the tank's position.
uint16_t getTankPosition(); // This gets the tank's position.

void setTankBulletPosition(point_t val); // This sets the tank's bullet position.
point_t getTankBulletPosition(); // This gets the tank's bullet position.

void setAlienCrossBulletPosition(point_t val); // This sets the tank's bullet position.
point_t getAlienCrossBulletPosition(); // This gets the tank's bullet position.

void drawCrossAlienBullet(uint8_t alienNumber);

void setAlienBlockPosition(point_t val); // This sets the aliens' block position.
point_t getAlienBlockPosition(); // This gets the aliens' block position

void setAlienBulletPosition(point_t val, uint8_t bullet_number); // This sets the alien's bullet position for a given bullet number.
point_t getAlienBulletPosition(uint8_t bullet_number); // This gets the alien's bullet position for a given bullet numbe.r

void fireAlienBullet(uint8_t alien_number, uint8_t bullet_type); // Draws the alien's bullet.
void drawAlienBullet(uint8_t alien_number, uint8_t bullet_type); // Draws the alien's bullet.
uint8_t updateAlienBullet(); // Updates the aliens bullet.

point_t calculateAlienPosition(uint8_t alien_number); // This calculates an individual aliens position.

uint8_t calculateAlienNumber(point_t some_position); // This calculates which alien is at the position.

void killAlien(uint8_t alien_number); // This kills an individual alien.

void drawAlienBlock(); // This draws the entire aliens block.

void erodeBunker(uint8_t bunker_number, uint8_t block_number); // This erodes a certain block in a certain bunker.

void drawTankBullet(); // This draws the tank's bullet.
uint8_t updateTankBullet(); // Updates the tank's bullet.

void drawTank(uint8_t direction); // This draws the tank. TANK_RIGHT or TANK_LEFT is the direction we pass in.
uint8_t drawSaucer(); // If it is done moving across the screen then it returns TRUE aka 1 and if it isn't it returns FALSE;

unsigned int * draw_start_screen(); // This draws the inital start screen.

#endif /* DRAW_H_ */
