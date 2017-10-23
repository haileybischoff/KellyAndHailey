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

uint16_t getSaucerPosition();

void setDeadSaucerPosition(point_t deadSaucer);

point_t getDeadSaucerPosition();

void setDidTankKillSaucertoFalse();

bool didTankKillSaucer();

void setSaucerPosition(uint16_t val);

point_t setUpdatedTopLeftSaucer(point_t some_point);

bool calculateHitSaucer(point_t some_point);

void eraseSaucer(point_t position);

bool drawSaucer(); // If it is done moving across the screen then it returns TRUE aka 1 and if it isn't it returns FALSE;

#endif /* DRAW_SAUCER_H_ */
