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

uint8_t getAlienBulletCount();

void setAlienBulletPosition(point_t val, uint8_t bullet_number);

point_t getAlienBulletPosition(uint8_t bullet_number);

void drawAlienBullet(uint8_t alienNumber, uint8_t type);

void drawBullet(const uint32_t* alien_cross_bullet, point_t updateBullet, uint8_t width);

uint8_t alienMayErodeBunker(uint8_t bunkerNumber, uint8_t blockNumber, uint8_t pixel, uint8_t line, point_t new_bullet_position);

uint8_t whichAlienBunkerNumber(point_t bullet, uint8_t pixel, uint8_t line, point_t new_bullet_position);

void eraseAlienBullet(const uint32_t* alien_cross_bullet, point_t bullet_pos, uint8_t width);

void eraseAllAlienBullets();

uint8_t generalUpdateBullet(const uint32_t* alien_cross_bullet, uint8_t bulletNum, uint8_t type);

uint8_t updateEachBullet();

#endif /* DRAW_ALIEN_BULLET_H_ */
