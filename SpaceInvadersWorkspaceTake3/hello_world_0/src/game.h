/*
 * game.h
 *
 *  Created on: Oct 20, 2017
 *      Author: superman
 */

#ifndef GAME_H_
#define GAME_H_

#include <stdbool.h>
#include <stdint.h>

bool getGameOverStatus();

void setGameOverStatus(bool stat);

bool getTankStatus();

void setTankStatus(bool stat);

void spaceInvaders_tick();




void setDownBtnFlag(bool val);
void setUpBtnFlag(bool val);

bool getDownBtnFlag();
bool getUpBtnFlag();


#endif /* GAME_H_ */
