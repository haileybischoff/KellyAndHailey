/*
 * game.h
 *
 *  Created on: Oct 20, 2017
 *      Author: superman
 */

#ifndef GAME_H_
#define GAME_H_

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

bool getSaucerGotShot();
bool setSaucerGotShot(bool val);

void setSaucerDrawnFlag(bool value);

void setSaucerScoreFlag(bool value);

#endif /* GAME_H_ */
