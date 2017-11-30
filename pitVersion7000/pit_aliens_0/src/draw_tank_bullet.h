/*
 * draw_tank_bullet.h
 *
 *  Created on: Oct 21, 2017
 *      Author: superman
 */

#ifndef DRAW_TANK_BULLET_H_
#define DRAW_TANK_BULLET_H_

#include <stdint.h>
#include <stdbool.h>
#include "draw.h"

#define SCORE_0 10
#define SCORE_1 20
#define SCORE_2 30
#define SCORE_3 40
#define SCORE_4 50
#define SCORE_5 110
#define SCORE_6 200

void setTankBulletPosition(point_t val); // This sets the tank's bullet position.

point_t getTankBulletPosition(); // This gets the tank's bullet position.

uint8_t getBulletDrawn(); //Get the bullet drawn

void eraseTheTankBullet(); //Erase the tank bullet

bool getFreezeAliens();

void drawTankBullet(); // This draws the tank's bullet.

void drawTankExplosionBullet(); // This draws the tank's bullet.

void drawTankColorBullet(); // This draws the tank's bullet.

void drawTankGuidedBullet(); // This draws the tank's bullet.

void drawTankLaserBullet(); // This draws the tank's bullet.

void setTankLaserBullet(bool value);

bool getTankLaserBullet();

void setBulletType();

bool getRogueAlienBullet();

void setRogueAlienBullet(bool value);

void setTankGuidedBullet(bool value);

void setTankExplosionBullet(bool value);

bool getTankExplosionBullet();

bool getFunBulletStatus();

void updateAllBullets();

void setTankBulletColor();

uint32_t getTankBulletColor();

void updateAllBullets();

uint8_t updateTankBullet(); // Updates the tank's bullet.

uint8_t updateTankExplosionBullet(); // Updates the tank's bullet.

uint8_t updateTankGuidedBullet(); // Updates the tank's bullet.

uint8_t updateTankLaserBullet(); // Updates the tank's bullet.


#endif /* DRAW_TANK_BULLET_H_ */
