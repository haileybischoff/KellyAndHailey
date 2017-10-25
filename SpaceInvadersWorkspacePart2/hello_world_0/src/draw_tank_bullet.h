/*
 * draw_tank_bullet.h
 *
 *  Created on: Oct 21, 2017
 *      Author: superman
 */

#ifndef DRAW_TANK_BULLET_H_
#define DRAW_TANK_BULLET_H_

#include <stdint.h>
#include "draw.h"

void setTankBulletPosition(point_t val); // This sets the tank's bullet position.

point_t getTankBulletPosition(); // This gets the tank's bullet position.

uint8_t getBulletDrawn(); //Get the bullet drawn

void eraseTheTankBullet(); //Erase the tank bullet

void drawTankBullet(); // This draws the tank's bullet.

uint8_t updateTankBullet(); // Updates the tank's bullet.

#endif /* DRAW_TANK_BULLET_H_ */
