/*
 * score_keeping.h
 *
 *  Created on: Oct 21, 2017
 *      Author: superman
 */

#ifndef SCORE_KEEPING_H_
#define SCORE_KEEPING_H_

#include <stdint.h>
#include <stdbool.h>
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

void drawScoreMessage(uint16_t x_position, uint16_t y_position); //Draw the score message

void drawLifeMessage(uint16_t x_position, uint16_t y_position); //Draw the life message

void drawNumber(point_t position, const uint32_t* number); //Draw a number

void drawGameOverMessage(); //Draw game over message

void eraseSaucerScore(); //Erase the saucer score

void drawSaucerScore(); //Draw the saucer score

void drawScore(); //Draw the score

void computeScore(uint8_t alien_number); //Compute the score

uint32_t getScore(); //Get the score

void setScore(uint32_t score); //Set the score

bool decrementScore(uint32_t score);

void drawLife(uint16_t x_position, uint16_t y_position); //Draw a life

#endif /* SCORE_KEEPING_H_ */
