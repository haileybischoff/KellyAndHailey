/*
 * draw_aliens.c
 *
 *  Created on: Oct 20, 2017
 *      Author: superman
 */

#include "draw_aliens.h"
#include "images.h"

#define EMPTY_COL_COUNT_INITIALIEZED_TO_ONE 1 //Initialize colum to 1
#define ALIEN_INITIAL_X_POSITION 144 //Initial alien x position
#define ALIEN_INITIAL_Y_POSITION 51 //Initial alien  position
#define ALIEN_X_OFFSET ALIEN_WORD_WIDTH //Alien x offset
#define ALIEN_Y_OFFSET (ALIEN_HEIGHT + 8) //Alien y offset
#define ALIEN_AMOUNT 55 //Number of aliens
#define ALIEN_BLOCK_WIDTH 352 //the width of the alien block
#define SQUID_IN 1 //The squid in
#define SQUID_OUT 2 //the squid out
#define BUG_IN 3 //The bug in
#define BUG_OUT 4 //The bug out
#define JELLYFISH_IN 5 //The jellyfish in
#define JELLYFISH_OUT 6 //The jellyfish out
#define ALIEN_MAX_COL 11 //Maximum column of aliens
#define ALIEN_MAX_ROW 5 //maximum rows of aliens
#define ALIEN_ROW_2_OFFSET 1 //Alien row 1 offset
#define ALIEN_ROW_3_OFFSET 2 //Alien row 2 offset
#define ALIEN_ROW_4_OFFSET 3 //Alien row 3 offset
#define ALIEN_ROW_5_OFFSET 4 //Alien row 4 offset
#define ALIEN_ERASE 0 //Erase
#define ALIEN_MOVE_HORIZONTAL 4 //Move horizontal
#define ALIEN_MOVE_VERTICAL 24 //Move vertical
#define ALIEN_MIN_LEFT_MOVE_DEFAULT 0 //Left Default
#define ALIEN_MAX_RIGHT_MOVE_DEFAULT 288 //Right Default
#define ALIEN_COLUMN_EMPTY 0 //Empty
#define ALIEN_NEXT_COL 1 //Column

#define ALIEN_FOURTY_FOUR 44 //Initial bottom alien 1
#define ALIEN_FOURTY_FIVE 45 //Initial bottom alien 2
#define ALIEN_FOURTY_SIX 46 //Initial bottom alien 3
#define ALIEN_FOURTY_SEVEN 47 //Initial bottom alien 4
#define ALIEN_FOURTY_EIGHT 48 //Initial bottom alien 5
#define ALIEN_FOURTY_NINE 49 //Initial bottom alien 6
#define ALIEN_FIFTY 50 //Initial bottom alien 7
#define ALIEN_FIFTY_ONE 51 //Initial bottom alien 8
#define ALIEN_FIFTY_TWO 52 //Initial bottom alien 9
#define ALIEN_FIFTY_THREE 53 //Initial bottom alien 10
#define ALIEN_FIFTY_FOUR 54 //Initial bottom alien 11

static uint8_t alien_block[ALIEN_AMOUNT] = {1,1,1,1,1,1,1,1,1,1,1, \
		1,1,1,1,1,1,1,1,1,1,1, \
		1,1,1,1,1,1,1,1,1,1,1, \
		1,1,1,1,1,1,1,1,1,1,1, \
		1,1,1,1,1,1,1,1,1,1,1};

static uint8_t alien_row_dead[ALIEN_MAX_COL] = {ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW};

// This keeps track of the alien that shoots.
static int8_t my_alien_row_dead[ALIEN_MAX_COL] = {ALIEN_FOURTY_FOUR,ALIEN_FOURTY_FIVE,ALIEN_FOURTY_SIX,ALIEN_FOURTY_SEVEN,ALIEN_FOURTY_EIGHT,ALIEN_FOURTY_NINE,ALIEN_FIFTY,ALIEN_FIFTY_ONE,ALIEN_FIFTY_TWO,ALIEN_FIFTY_THREE,ALIEN_FIFTY_FOUR};

static uint8_t all_left_columns_alive = true; //All columns are alive

static int8_t left_most_alien_column; //Left most alien column

static bool alien_move_right = true; //Start by moving right
static bool alien_step_out = false; //Alien step out
static bool erase_top_row = false; //Erase the top row
static point_t last_alien_position;

static point_t alienBlockPosition; //Keep track of alien block position
static point_t alien_dead;
static bool tank_killed_alien = false;

extern unsigned int * frame_pointer;

void initializeAlienBlock(){
	alienBlockPosition.x = ALIEN_INITIAL_X_POSITION; //Alien x
	alienBlockPosition.y = ALIEN_INITIAL_Y_POSITION; //Alien y
}

int8_t getMyAlienNumber(int8_t alienIndex){ //Get the number for an alien when given a number
	return my_alien_row_dead[alienIndex];//Return the index of the bottom most alien or null
}

bool isAlienAlive(uint8_t alienIndex){
	return alien_block[alienIndex];
}

bool didTankKillAlien(){
	return tank_killed_alien;
}

void setDidTankKillAlienFlag(bool killAlien){
	tank_killed_alien = killAlien;
}

void setDeadAlienPosition(point_t deadAlienPosition){
	alien_dead.x = deadAlienPosition.x;
	alien_dead.y = deadAlienPosition.y;
}

point_t getDeadAlienPosition(){
	return alien_dead;
}

void setAlienBlockPosition(point_t val){ //Set the position of the alien block
	alienBlockPosition.x = val.x; //X position
	alienBlockPosition.y = val.y; //Y position
}

point_t getAlienBlockPosition(){ //Get the alien block position
	return alienBlockPosition;
}

point_t calculateAlienPosition(uint8_t alien_number){ //Calculate the position of the alien
	point_t position = getAlienBlockPosition(); //Get the position
	// Get the y_position for all the aliens.
	if((alien_number >= ALIEN_ROW_1) && (alien_number < ALIEN_ROW_2)){
		position.y += (ALIEN_Y_OFFSET * ALIEN_ROW_2_OFFSET); //Set the y
	}
	else if((alien_number >= ALIEN_ROW_2) && (alien_number < ALIEN_ROW_3)){
		position.y += (ALIEN_Y_OFFSET * ALIEN_ROW_3_OFFSET); //Set the y
	}
	else if((alien_number >= ALIEN_ROW_3) && (alien_number < ALIEN_ROW_4)){
		position.y += (ALIEN_Y_OFFSET * ALIEN_ROW_4_OFFSET); //Set the y
	}
	else if((alien_number >= ALIEN_ROW_4) && (alien_number < ALIEN_ROW_5)){
		position.y += (ALIEN_Y_OFFSET * ALIEN_ROW_5_OFFSET); //Set the y
	}
	// Get the x_position for all the aliens.
	position.x += (alien_number % ALIEN_MAX_COL)*ALIEN_X_OFFSET; //The x is the same
	return position;
}

uint8_t calculateAlienNumber(point_t some_position){
	uint16_t x_position, y_position;
	x_position = some_position.x;
	y_position = some_position.y;

	uint8_t alienNumber = WRONG_ALIEN;

	point_t blockPosition = getAlienBlockPosition(); // This is getting the AlienBlockPosition

	uint8_t h;
	for(h = 0; h < ALIEN_MAX_ROW; h++){ // Calculating the numbers for the row.
		uint8_t i;

		uint16_t topOfAlien = blockPosition.y + (ALIEN_Y_OFFSET * h); // this is just getting the top of the Alien boundary
		uint16_t bottomOfAlien = blockPosition.y + (ALIEN_Y_OFFSET * h) + ALIEN_HEIGHT; // This is just getting the bottom of the alien boundary

		if((y_position >= topOfAlien && y_position <= bottomOfAlien)){ // No need to go through this for loop more than we have to
			for(i = 0; i < ALIEN_MAX_COL; i++){ // Calculating the number for the column
				uint16_t leftOfAlien = blockPosition.x + (ALIEN_X_OFFSET * i); // The left boundary of the alien.
				uint16_t rightOfAlien = blockPosition.x + (ALIEN_X_OFFSET * (i + INCREMENT_OR_DECREMENT)); // the right boundary of the alien.

				if((x_position >= leftOfAlien) && (x_position < rightOfAlien)){ // If the x_poisition is in the boundaries.
					alienNumber = (h * ALIEN_MAX_COL) + i; // calculate alienNumber.
					return alienNumber;
				}
			}
		}
	}

	return alienNumber;
}

uint16_t getLeftAlienBorder(){//Get the left border for the aliens
	uint16_t left_position = ALIEN_MIN_LEFT_MOVE_DEFAULT;//This is the default
	uint8_t left_most_alive_col; //Create left most column variable
	for(left_most_alive_col = 0; left_most_alive_col < ALIEN_MAX_COL; left_most_alive_col++){
		if(alien_row_dead[left_most_alive_col] != ALIEN_COLUMN_EMPTY){ //If column is not empty
			break;
		}
	}
	if(left_most_alive_col){ //If we have a column
		all_left_columns_alive = false; //Set to false
		left_position += RIGHT_BORDER - ((left_most_alive_col) * ALIEN_WORD_WIDTH); //Set the left position to the right - the number of dead columns
	}
	else{
		left_position += ((left_most_alive_col) * ALIEN_WORD_WIDTH); //Set the left position to the left most column
	}
	//xil_printf("left position %d\n\r", left_position);
	return left_position;
}

uint16_t getRightAlienBorder(){ //Get the right border for the aliens
	uint16_t right_position = ALIEN_MAX_RIGHT_MOVE_DEFAULT; //Set to default
	uint8_t right_most_alive_col; //Right most column
	for(right_most_alive_col = ALIEN_MAX_COL; right_most_alive_col > 0; right_most_alive_col--){
		if(alien_row_dead[right_most_alive_col - ALIEN_NEXT_COL] != ALIEN_COLUMN_EMPTY){ //If column is not empty
			break;
		}
	}
	right_position += ((ALIEN_MAX_COL - right_most_alive_col) * ALIEN_WORD_WIDTH);//Set right position
	//xil_printf("right position %d\n\r", right_position);
	return right_position;
}

void eraseAlien(uint16_t x_position, uint16_t y_position, uint8_t alien_type){
	uint8_t line, pixel;
	for(line = 0; line < ALIEN_HEIGHT; line++){ //Height
		for(pixel = 0; pixel < ALIEN_WORD_WIDTH; pixel++){ //Width
			if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == WHITE)
				frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
		}
	}
}

void killAlien(uint8_t alien_number){
	point_t position = calculateAlienPosition(alien_number); //Calculate alien position
	uint16_t x_position = position.x; //X position
	uint16_t y_position = position.y; //Y position
	uint8_t get_alien_num = alien_number; //Get alien number
	uint8_t alien_column = alien_number % ALIEN_MAX_COL; //Figure out alien column
	uint8_t new_alien_number = alien_row_dead[alien_column]; //Get new alien number
	uint8_t my_new_alien_number = my_alien_row_dead[alien_column];
	uint8_t found = false; //Set found bool to false
	if(alien_row_dead[alien_column] != ALIEN_COLUMN_EMPTY){ //If column is not empty
		alien_row_dead[alien_column] = --new_alien_number; //Decrement alien number
	}
	if(my_alien_row_dead[alien_column] != ALIEN_NULL){ //If column is not null
		if(my_new_alien_number == alien_number){ //If the number is the same
			uint8_t i;
			for(i = 1; i < ALIEN_MAX_ROW; i++){
				if(alien_block[get_alien_num - (i * ALIEN_MAX_COL)] != false){
					my_alien_row_dead[alien_column] = my_new_alien_number - (i * ALIEN_MAX_COL); //Create new number
					found = true; //Set found to true
					break;
				}
			}
			if(found == false){ //If false
				my_alien_row_dead[alien_column] = ALIEN_NULL; //Set to null
			}
		}
	}
	alien_block[alien_number] = ALIEN_ERASE; //Erase alien
	uint8_t line, pixel;
	for(line = 0; line < ALIEN_HEIGHT; line++){ //Height
		for(pixel = 0; pixel < ALIEN_WORD_WIDTH; pixel++){ //Width
			if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] != BLACK){
				frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
			}
		}
	}
}

void drawAlien(uint16_t x_position, uint16_t y_position, uint8_t alien_type){ //ANDY SAID THAT OUR ALIENS NEED TO MOVE OVER BY EITHER 4 OR 6 PIXELS
	uint8_t line, pixel;
	for(line = 0; line < ALIEN_HEIGHT; line++){ //Height
		for(pixel = 0; pixel < ALIEN_WORD_WIDTH; pixel++){ //Width
			if(alien_type == SQUID_IN){ //Squid in
				if((squid_step_in_symbol[line] & (SHIFT<<(ALIEN_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == BLACK){//Said not white
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = WHITE; //Set to white
					}
				}
				else{
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == WHITE){
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
					}
				}
			}
			else if(alien_type == SQUID_OUT){ //Squid out
				if((squid_step_out_symbol[line] & (SHIFT<<(ALIEN_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == BLACK){//Said not white
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = WHITE; //Set to white
					}
				}
				else{
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == WHITE){
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
					}
				}
			}
			else if(alien_type == BUG_IN){ //Bug in
				if((bug_step_in_symbol[line] & (SHIFT<<(ALIEN_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == BLACK){//Said not white
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = WHITE; //Set to white
					}
				}
				else{
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == WHITE){
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
					}
				}
			}
			else if(alien_type == BUG_OUT){ //Bug out
				if((bug_step_out_symbol[line] & (SHIFT<<(ALIEN_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == BLACK){//Said not white
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = WHITE; //Set to white
					}
				}
				else{
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == WHITE){
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
					}
				}
			}
			else if(alien_type == JELLYFISH_IN){ //Jelly fish in
				if((jellyfish_step_in_symbol[line] & (SHIFT<<(ALIEN_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == BLACK){//Said not white
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = WHITE; //Set to white
					}
				}
				else{
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == WHITE){
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
					}
				}
			}
			else if(alien_type == JELLYFISH_OUT){ //Jellyfish out
				if((jellyfish_step_out_symbol[line] & (SHIFT<<(ALIEN_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == BLACK){//Said not white
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = WHITE; //Set to white
					}
				}
				else{
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == WHITE){
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
					}
				}
			}
		}
	}
}

void eraseTopRowAliens(int8_t howManyRows){ //Erase the tops rows
	uint8_t line;
	uint16_t pixel;
	for(line = 0; line < (ALIEN_Y_OFFSET * howManyRows); line++){ //Height increased by the number of empty rows
		for(pixel = 0; pixel < ALIEN_BLOCK_WIDTH; pixel++){ //Width
			if(frame_pointer[(line + last_alien_position.y)*SCREEN_WIDTH + (pixel + last_alien_position.x)] == WHITE){
				frame_pointer[(line + last_alien_position.y)*SCREEN_WIDTH + (pixel + last_alien_position.x)] = BLACK; //Set to black
			}
		}
	}
}

void updateAlienPosition(){
	point_t alien_position = getAlienBlockPosition(); //Get alien block position
	last_alien_position = getAlienBlockPosition(); //Make a copy of the alien block position to manipulate
	if((alien_position.x == LEFT_BORDER && all_left_columns_alive) || alien_position.x == getLeftAlienBorder()){//If we hit the left border then change to move right
		alien_position.y += ALIEN_MOVE_VERTICAL;//This it moves the block down but it doesn't erase the ones that didn't move
		alien_move_right = true; //Set to true
		erase_top_row = true; //Set to true

		if(alien_position.x == LEFT_BORDER && !all_left_columns_alive){
			alien_position.x = RIGHT_BORDER; //Set to right border
		}
	}
	else if(alien_position.x == getRightAlienBorder()){//If we hit the right border then change to move left
		alien_position.y += ALIEN_MOVE_VERTICAL;//This it moves the block down but it doesn't erase the ones that didn't move
		alien_move_right = false; //Set move right to false
		erase_top_row = true; //Set erase top row to true
	}

	if(alien_move_right){ //If move right then increment horizontally
		if(alien_position.x == RIGHT_BORDER && !all_left_columns_alive){
			alien_position.x = LEFT_BORDER; //Set to the left border
			alien_position.y += INCREMENT_OR_DECREMENT; //Increment by 1
		}
		alien_position.x += ALIEN_MOVE_HORIZONTAL; //Move horizontally
	}
	else{ //Else decrement horizontally
		if(alien_position.x == LEFT_BORDER && !all_left_columns_alive){
			alien_position.x = RIGHT_BORDER; //Set to right border
			alien_position.y -= INCREMENT_OR_DECREMENT; //Decrement by 1
		}
		alien_position.x -= ALIEN_MOVE_HORIZONTAL; //Move horizontally
	}
	setAlienBlockPosition(alien_position); //Set alien block position
}

void drawAlienBlock(){ //Draw alien block
	uint8_t i;
	for(i = 0; i < ALIEN_MAX_COL; i++){
		if(getMyAlienNumber(i) != ALIEN_NULL){ //Find the left most column
			left_most_alien_column = i;
			break;
		}
	}
	if(alien_step_out){ //Alternate between in and out
		alien_step_out = false; //Set to false if true
	}
	else{
		alien_step_out = true; //Set to true if false
	}
	uint8_t alien_number;
	uint8_t alien_type;
	for(alien_number = 0; alien_number < ALIEN_AMOUNT; alien_number++){
		// Get which type of alien we are drawing.
		if(alien_step_out){ //If out
			if(alien_number < ALIEN_ROW_1){
				alien_type = SQUID_OUT; //Set to squid out
			}
			else if((alien_number >= ALIEN_ROW_1) && (alien_number < ALIEN_ROW_3)){

				alien_type = BUG_OUT; //Set to bug out
			}
			else if((alien_number >= ALIEN_ROW_3) && (alien_number < ALIEN_ROW_5)){

				alien_type = JELLYFISH_OUT; //Set to jellyfish out
			}
		}
		else{
			if(alien_number < ALIEN_ROW_1){
				alien_type = SQUID_IN; //Set to squid in
			}
			else if((alien_number >= ALIEN_ROW_1) && (alien_number < ALIEN_ROW_3)){

				alien_type = BUG_IN; //Set to bug in
			}
			else if((alien_number >= ALIEN_ROW_3) && (alien_number < ALIEN_ROW_5)){

				alien_type = JELLYFISH_IN; //Set to jellyfish in
			}
		}
		point_t position = calculateAlienPosition(alien_number); //Calculate alien position
		uint16_t alien_x_position = position.x;
		uint16_t alien_y_position = position.y;

		// Draw the alien.
		if(alien_block[alien_number]){ //If alien is supposed to be drawn then draw
			drawAlien(alien_x_position, alien_y_position, alien_type);
		}
		else{
			eraseAlien(alien_x_position, alien_y_position, alien_type); //Erase what ever is in that square
		}
	}
	if(erase_top_row){ //We need to erase the top row
		int8_t number_of_blank_rows = EMPTY_COL_COUNT_INITIALIEZED_TO_ONE;
		uint8_t i, j;
		int8_t count = RESET;
		for(i = 0; i < ALIEN_MAX_ROW; i++){ //Height
			for(j = 0; j < ALIEN_MAX_COL; j++){ //Row
				int8_t num = (i * ALIEN_MAX_COL) + j;
				if(alien_block[num] == false){ //Doesn't exist
					count++; //Increment count
				}
				if(count == ALIEN_MAX_COL){ //Count is 11
					number_of_blank_rows++; //Increment blank rows
					count = RESET; //Reset count
				}
			}
		}
		eraseTopRowAliens(number_of_blank_rows); //Erase top row of aliens
		erase_top_row = false; //Set to false
	}
	updateAlienPosition();
}