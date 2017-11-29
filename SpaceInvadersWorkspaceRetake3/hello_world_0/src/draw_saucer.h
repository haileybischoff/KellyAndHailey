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

uint16_t getSaucerPosition(); //Get the saucer position

uint16_t getSaucerDeathPosition(); //Get the saucer death position

void setSaucerDeathPosition(uint16_t deathPosition); //Set the saucer death position

void setDidTankKillSaucerFlag(bool saucerFlag); //Set the flag

bool didTankKillSaucer(); //Did tank kill saucer

void setSaucerPosition(uint16_t val); //Set the saucer position

bool calculateHitSaucer(point_t some_point); //Calculate whether a saucer was hit

void eraseSaucer(); //Erase the saucer

bool drawSaucer(); // If it is done moving across the screen then it returns TRUE aka 1 and if it isn't it returns FALSE;

#endif /* DRAW_SAUCER_H_ */
