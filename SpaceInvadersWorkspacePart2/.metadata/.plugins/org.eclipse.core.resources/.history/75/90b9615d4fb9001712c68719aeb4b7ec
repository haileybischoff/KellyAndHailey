/*
 * draw_saucer.h
 *
 *  Created on: Oct 20, 2017
 *      Author: superman
 */

#ifndef DRAW_SAUCER_H_
#define DRAW_SAUCER_H_

#include <stdint.h>
#include <stdbool.h>
#include "draw.h"

#define SAUCER_Y_POSITION 29 // This is the Y position for when we draw the saucer.

uint16_t getSaucerPosition();

uint16_t getSaucerDeathPosition();

void setSaucerDeathPosition(uint16_t deathPosition);

void setDidTankKillSaucerFlag(bool saucerFlag);

bool didTankKillSaucer();

void setSaucerPosition(uint16_t val);

bool calculateHitSaucer(point_t some_point);

void eraseSaucer();

bool drawSaucer(); // If it is done moving across the screen then it returns TRUE aka 1 and if it isn't it returns FALSE;

#endif /* DRAW_SAUCER_H_ */
