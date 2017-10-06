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

typedef struct {uint16_t x; uint16_t y;} point_t;

void setTankPosition(uint16_t val);
uint16_t getTankPosition();

void setTankBulletPosition(point_t val);
point_t getTankBulletPosition();

void setAlienBlockPosition(point_t val);
point_t getAlienBlockPosition();

void setAlienBulletPosition(point_t val);
point_t getAlienBulletPosition();

void killAlien(uint8_t alien_number);

void drawAlienBlock();

void erodeBunker(uint8_t bunker_number, uint8_t block_number);

void drawTank(uint8_t direction);

unsigned int * draw_start_screen();

#endif /* DRAW_H_ */