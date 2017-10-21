/*
 * draw_tank.h
 *
 *  Created on: Oct 20, 2017
 *      Author: superman
 */

#ifndef DRAW_TANK_H_
#define DRAW_TANK_H_

#include <stdint.h>

#define TANK_LEFT 1 // Tells the tank it needs to move left.
#define TANK_RIGHT 2 // Tells the tank it needs to move right.
#define TANK_Y_POSITION 423 //The top position of the tank
#define TANK_INITIAL_X_POSITION 304 //The Initial c position for the tank

void setTankPosition(uint16_t val); // This sets the tank's position.

uint16_t getTankPosition(); // This gets the tank's position.

void drawTank(uint8_t direction); // This draws the tank. TANK_RIGHT or TANK_LEFT is the direction we pass in.

#endif /* DRAW_TANK_H_ */