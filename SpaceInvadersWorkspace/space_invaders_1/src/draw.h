/*
 * draw.h
 *
 *  Created on: Oct 5, 2017
 *      Author: superman
 */

#ifndef DRAW_H_
#define DRAW_H_

#include <stdint.h>

#define TANK_LEFT 1
#define TANK_RIGHT 2
#define TANK_STAY 0

#define BUNKER_1 0
#define BUNKER_2 1
#define BUNKER_3 2
#define BUNKER_4 3

#define NUMBER_OF_ALIEN_BULLETS 4

typedef struct {uint16_t x; uint16_t y;} point_t;

void setTankPosition(uint16_t val);
uint16_t getTankPosition();

void setTankBulletPosition(point_t val);
point_t getTankBulletPosition();

void setAlienBlockPosition(point_t val);
point_t getAlienBlockPosition();

void setAlienBulletPosition(point_t val, uint8_t bullet_number);
point_t getAlienBulletPosition(uint8_t bullet_number);
uint8_t updateAlienBullet();
void drawAlienBullet(uint8_t alienNum, uint8_t bullet_type);

point_t calculateAlienPosition(uint8_t alien_number);



//void setAlienBulletPosition2(point_t val);
//point_t getAlienBulletPosition2();

//void setAlienBulletPosition3(point_t val);
//point_t getAlienBulletPosition3();

//void setAlienBulletPosition4(point_t val);
//point_t getAlienBulletPosition4();

void killAlien(uint8_t alien_number);

void drawAlienBlock();

void erodeBunker(uint8_t bunker_number, uint8_t block_number);

void drawTankBullet();
uint8_t updateTankBullet();

void drawAlienBullet(uint8_t alien_number, uint8_t bullet_type);
uint8_t updateAlienBullet();
void drawTank(uint8_t direction);

unsigned int * draw_start_screen();

#endif /* DRAW_H_ */
