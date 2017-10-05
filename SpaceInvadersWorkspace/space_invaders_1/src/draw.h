/*
 * draw.h
 *
 *  Created on: Oct 5, 2017
 *      Author: superman
 */

#ifndef DRAW_H_
#define DRAW_H_

#include <stdint.h>

typedef struct {uint16_t x; uint16_t y;} point_t;

void setTankPosition(uint16_t val);
uint16_t getTankPosition();

void setTankBulletPosition(point_t val);
point_t getTankBulletPosition();

void setAlienBlockPosition(point_t val);
point_t getAlienBlockPosition();

unsigned int * draw_start_screen();

#endif /* DRAW_H_ */
