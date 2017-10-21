/*
 * draw.h
 *
 *  Created on: Oct 5, 2017
 *      Author: superman
 */

#ifndef DRAW_H_
#define DRAW_H_

#include <stdint.h>

/******* Colors *******/
#define RED 0x00FF0000 // Hexadecimal color value for Red
#define GREEN 0x0000FF00 // Hexadecimal color value for Green
#define WHITE 0x00FFFFFF // Hexadecimal color value for White
#define BLACK 0x00000000 // Hexadecimal color value for Black

/******* General Useful Defines *******/
#define SHIFT 1 //We are shifting by 1
#define RESET 0 //Reset is 0
#define INCREMENT_OR_DECREMENT 1 //We want to increment or decrement by 1

/******* Parameters *******/
#define SCREEN_WIDTH 640 //Width of the screen
#define LEFT_BORDER 0 //The left border is 0
#define RIGHT_BORDER 640 //The right border is 640

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

uint8_t updateCrossAlienBullet();

point_t getShotBunkerPosition();
uint8_t calculateBlockNumber(uint8_t bunkerNum, point_t bunkerPosition);
uint8_t calculateBunkerNumber(point_t bunkerPosition);
void setDidTankKillBunker();
uint8_t didTankKillBunker();

void computeScore(uint8_t alien_number);

uint32_t getScore();
void setScore(uint32_t score);

void setTankBulletPosition(point_t val); // This sets the tank's bullet position.
point_t getTankBulletPosition(); // This gets the tank's bullet position.

void setAlienCrossBulletPosition(point_t val); // This sets the tank's bullet position.
point_t getAlienCrossBulletPosition(); // This gets the tank's bullet position.

void drawCrossAlienBullet(uint8_t alienNumber);

void setAlienBulletPosition(point_t val, uint8_t bullet_number); // This sets the alien's bullet position for a given bullet number.
point_t getAlienBulletPosition(uint8_t bullet_number); // This gets the alien's bullet position for a given bullet numbe.r

void fireAlienBullet(uint8_t alien_number, uint8_t bullet_type); // Draws the alien's bullet.
void drawAlienBullet(uint8_t alien_number, uint8_t bullet_type); // Draws the alien's bullet.
uint8_t updateAlienBullet(); // Updates the aliens bullet.

void erodeBunker(uint8_t bunker_number, uint8_t block_number); // This erodes a certain block in a certain bunker.

void drawTankBullet(); // This draws the tank's bullet.
uint8_t updateTankBullet(); // Updates the tank's bullet.

unsigned int * draw_start_screen(); // This draws the inital start screen.

#endif /* DRAW_H_ */
