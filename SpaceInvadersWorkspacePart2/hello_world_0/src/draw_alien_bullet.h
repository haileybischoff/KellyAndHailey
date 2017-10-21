/*
 * draw_alien_bullet.h
 *
 *  Created on: Oct 21, 2017
 *      Author: superman
 */

#ifndef DRAW_ALIEN_BULLET_H_
#define DRAW_ALIEN_BULLET_H_

#include <stdint.h>
#include "draw.h"

uint8_t updateCrossAlienBullet();

void setAlienCrossBulletPosition(point_t val); // This sets the tank's bullet position.

point_t getAlienCrossBulletPosition(); // This gets the tank's bullet position.

void drawCrossAlienBullet(uint8_t alienNumber);

void setAlienBulletPosition(point_t val, uint8_t bullet_number); // This sets the alien's bullet position for a given bullet number.

point_t getAlienBulletPosition(uint8_t bullet_number); // This gets the alien's bullet position for a given bullet numbe.r

void fireAlienBullet(uint8_t alien_number, uint8_t bullet_type); // Draws the alien's bullet.

void drawAlienBullet(uint8_t alien_number, uint8_t bullet_type); // Draws the alien's bullet.

uint8_t updateAlienBullet(); // Updates the aliens bullet.

#endif /* DRAW_ALIEN_BULLET_H_ */
