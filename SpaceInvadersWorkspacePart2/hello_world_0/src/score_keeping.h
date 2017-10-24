/*
 * score_keeping.h
 *
 *  Created on: Oct 21, 2017
 *      Author: superman
 */

#ifndef SCORE_KEEPING_H_
#define SCORE_KEEPING_H_

#include <stdint.h>
#include "draw.h"

#define LIFE_1_X_POSITION 449 //Life 1 x position
#define LIFE_2_X_POSITION 489 //Life 2 x position
#define LIFE_3_X_POSITION 529 //Life 3 x position
#define LIFE_Y_POSITION 5 //Y position for life
#define LIVES_MESSAGE_X 393
#define LIVES_MESSAGE_Y 11
#define SCORE_MESSAGE_X 5
#define SCORE_MESSAGE_Y 11
#define SCORE_X 73
#define SCORE_Y 11

void drawScoreMessage(uint16_t x_position, uint16_t y_position);

void drawLifeMessage(uint16_t x_position, uint16_t y_position);

void drawNumber(point_t position, const uint32_t* number);

void eraseSaucerScore();

void drawSaucerScore();

void drawScore();

void computeScore(uint8_t alien_number);

uint32_t getScore();

void setScore(uint32_t score);

void drawLife(uint16_t x_position, uint16_t y_position);

#endif /* SCORE_KEEPING_H_ */
