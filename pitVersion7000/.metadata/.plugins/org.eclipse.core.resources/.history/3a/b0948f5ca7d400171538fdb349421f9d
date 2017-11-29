/*
 * tank_move_state_machine.c
 *
 *  Created on: Nov 18, 2017
 *      Author: superman
 */

#include "tank_move_state_machine.h"
#include "draw_tank.h"
#include "game.h"
#include <stdbool.h>
#include <stdint.h>

#define MOVE_TANK_LEFT 1
#define MOVE_TANK_RIGHT 2
#define RESET 0
#define MAX_MOVE_TANK_VALUE 3
#define DEBOUNCE_VALUE 0x0000001F
#define LEFT_BUTTON_MASK 8 //This is the mask for the left push button it moves the tank left.
#define RIGHT_BUTTON_MASK 2 //This is the mask for the right push button it moves the tank right.

bool tankMoveLeftFlag;
bool tankMoveRightFlag;
uint32_t debounceButtonState = 0;	// Saves the debounced button states

extern uint32_t currentButtonState;

void debounced_buttons(){ //this takes the button and debounces it for us it also sets the flags for each button
	debounceButtonState = currentButtonState & DEBOUNCE_VALUE;
	if((debounceButtonState & LEFT_BUTTON_MASK) && !(debounceButtonState & RIGHT_BUTTON_MASK)){
		tankMoveLeftFlag = true;
		//xil_printf("we have pressed the left button\n\r");
		tankMoveRightFlag = false;
	}
	if((debounceButtonState & RIGHT_BUTTON_MASK) && !(debounceButtonState & LEFT_BUTTON_MASK)){
		tankMoveRightFlag = true;
		//xil_printf("we have pressed the right button\n\r");
		tankMoveLeftFlag = false;
	}
}

enum TankMove_st{
	tank_init_st,
	tank_idle_st,
	tank_move_left_st,
	tank_move_right_st,
	game_over_st
} tank_currentState = tank_init_st;

uint32_t tankMoveCounter;
void TankMove_tick(){
	//Actions
	switch(tank_currentState){
	case tank_init_st:
		tankMoveLeftFlag = false;
		tankMoveRightFlag = false;
		tankMoveCounter = RESET;
		break;
	case tank_idle_st:
		debounced_buttons();
		if(!getTankStatus()){
			tankMoveCounter++;
			//xil_printf("the tank move count is: %d\n\r", tankMoveCounter);
		}
		break;
	case tank_move_left_st:
		//xil_printf("we are in the tank_move_left_state\n\r");
		tankMoveCounter++;
		drawTank(MOVE_TANK_LEFT);
		break;
	case tank_move_right_st:
		//xil_printf("we are in the tank_move_right_state\n\r");
		tankMoveCounter++;
		drawTank(MOVE_TANK_RIGHT);
		break;
	case game_over_st:

		break;
	default:
		break;
	}

	//Transitions
	switch(tank_currentState){
	case tank_init_st:
		//xil_printf("we are in the init state\n\r");
		tank_currentState = tank_idle_st;
		break;
	case tank_idle_st:
		if(getGameOverStatus()){
			tank_currentState = game_over_st;
		}
		else if((tankMoveLeftFlag && (tankMoveCounter >= MAX_MOVE_TANK_VALUE)) && !getTankStatus()){
			tankMoveCounter = RESET;
			tankMoveLeftFlag = false;
			tank_currentState = tank_move_left_st;
		}
		else if((tankMoveRightFlag && (tankMoveCounter >= MAX_MOVE_TANK_VALUE)) && !getTankStatus()){
			tankMoveCounter = RESET;
			tankMoveRightFlag = false;
			tank_currentState = tank_move_right_st;
		}
		break;
	case tank_move_left_st:
			tank_currentState = tank_idle_st;
		break;
	case tank_move_right_st:
		tank_currentState = tank_idle_st;
		break;
	case game_over_st:
		//xil_printf("we are in the game over state\n\r");
		break;
	default:
		break;
	}
}
