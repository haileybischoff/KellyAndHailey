/*
 * draw.h
 *
 *  Created on: Oct 5, 2017
 *      Author: superman
 */

#ifndef DRAW_H_
#define DRAW_H_

#include <stdint.h>

/******* Colors *******/
#define RED 0x00FF0000 // Hexadecimal color value for Red
#define GREEN 0x0000FF00 // Hexadecimal color value for Green
#define WHITE 0x00FFFFFF // Hexadecimal color value for White
#define BLACK 0x00000000 // Hexadecimal color value for Black

/******* General Useful Defines *******/
#define SHIFT 1 //We are shifting by 1
#define RESET 0 //Reset is 0
#define INCREMENT_OR_DECREMENT 1 //We want to increment or decrement by 1

/******* Parameters *******/
#define SCREEN_WIDTH 640 //Width of the screen
#define LEFT_BORDER 0 //The left border is 0
#define RIGHT_BORDER 640 //The right border is 640
#define GROUND_LEVEL 459 //This is the ground level of the game

/******* Bunker Numbers *******/
#define BUNKER_1 0 // The number assigned to bunker 1.
#define BUNKER_2 1 // The number assigned to bunker 1.
#define BUNKER_3 2 // The number assigned to bunker 1.
#define BUNKER_4 3 // The number assigned to bunker 1.

/******* Game Pixel Values *******/
#define ONE_GAME_PIXELS 2 //One game pixel is 2 pixels
#define TWO_GAME_PIXELS 4 //Two game pixel is 4 pixels
#define THREE_GAME_PIXELS 6 //Three game pixel is 6 pixels
#define FOUR_GAME_PIXELS 8 //Four game pixel is 8 pixels
#define FIVE_GAME_PIXELS 10 //Five game pixel is 10 pixels
#define SIX_GAME_PIXELS 12 //Six game pixel is 12 pixels
#define ELEVEN_GAME_PIXELS 22 //Eleven game pixel is 22 pixels

#define NUMBER_OF_ALIEN_BULLETS 4 // The number of bullets the aliens can shoot.

typedef struct point_t { // A new data structure to hold the x and y coordinates for individual parts.
	uint16_t x;
	uint16_t y;
};

typedef struct point_t point_t; // Andy you put this here because according to Kelly you didn't like my declaration of point_t I'm gonna have to ask you about that later.

void eraseLives(uint8_t lives);

void clearScreen();

unsigned int * draw_start_screen(); // This draws the initial start screen.

#endif /* DRAW_H_ */
