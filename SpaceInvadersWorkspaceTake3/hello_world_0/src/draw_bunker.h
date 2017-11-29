/*
 * draw_bunker.h
 *
 *  Created on: Oct 21, 2017
 *      Author: superman
 */

#ifndef DRAW_BUNKER_H_
#define DRAW_BUNKER_H_

#include <stdint.h>
#include "draw.h"

#define BUNKER1 0
#define BUNKER2 1
#define BUNKER3 2
#define BUNKER4 3
#define BUNKER_1_X_POSITION 104 //First bunker x position
#define BUNKER_2_X_POSITION	232 //Second bunker x position
#define BUNKER_3_X_POSITION 360 //Third bunker x position
#define BUNKER_4_X_POSITION	488 //Fourth bunker x position
#define BUNKER_Y_POSITION 367 //Y position for bunkers
#define WRONG_BUNKER 13

void setShotBunkerPosition(point_t bunkerPosition); //Set the position for the shot bunker

point_t getShotBunkerPosition(); // get the shot bunker position

uint8_t getErosionStage(uint8_t bunkerNum, uint8_t blockNumber); //Get the erosion stage for a bunker and block

uint8_t calculateBlockNumber(uint8_t bunkerNum, point_t bunkerPosition); //Calculate the block number

uint8_t calculateBunkerNumber(point_t bunkerPosition); //Calculate the bunker number

void setDidTankKillBunkerFlag(bool tankKilledBunkerFlag); //Set the flag for the tank killed bunker

void setDidAlienKillBunkerFlag(bool alienKilledBunkerFlag); //Set the flag for the alien killed bunker

void eraseBunkers(); //Erase bunkers

uint8_t didTankKillBunker(); //Did tank kill a bunker

uint8_t didAlienKillBunker(); //did alien killa bunker

void drawBunker(uint16_t x_position, uint16_t y_position); //Draw a bunker

void erodeBunker(uint8_t bunker_number, uint8_t block_number); // This erodes a certain block in a certain bunker.

#endif /* DRAW_BUNKER_H_ */
