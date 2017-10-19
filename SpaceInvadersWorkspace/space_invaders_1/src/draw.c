/*
 * draw.c
 *
 *  Created on: Oct 5, 2017
 *      Author: superman
 */

#include "draw.h"
#include "images.h"
#define FRAME_BUFFER_0_ADDR_BASE 0xC1000000  // Starting location in DDR where we will store the images that we display.
#define TRUE 1 //True is 1
#define FALSE 0 //False is 0

#define RED 0x00FF0000 // Hexadecimal color value for Red
#define GREEN 0x0000FF00 // Hexadecimal color value for Green
#define WHITE 0x00FFFFFF // Hexadecimal color value for White
#define BLACK 0x00000000 // Hexadecimal color value for Black
#define _ALIEN_BULLET_GROUND_LEVEL 450 //This is the groung level of the game
#define GROUND_LEVEL 459 //This is the groung level of the game
#define LEFT_BORDER 0 //The left border is 0
#define RIGHT_BORDER 640 //The right border is 640
#define SHIFT 1 //We are shifting by 1
#define INCREMENT_OR_DECREMENT 1 //We want to increment or decrement by 1
#define RESET 0 //Reset is 0

#define SCREEN_HEIGHT 480 //Height of screen
#define SCREEN_WIDTH 640 //Width of the screen

#define TANK_Y_POSITION 423 //The top position of the tank
#define TANK_INITIAL_X_POSITION 304 //The Initial c position for the tank
#define TANK_RIGHT_BORDER SCREEN_WIDTH - 32 //The right border is the screen width - 32
#define TANK_LEFT_BORDER 0 //The tank left border is 0
#define TANK_HALF_HEIGHT 8 //Half of the height for the tank is 8
#define TANK_HALF_WIDTH 14 //Half of the width for the tank
#define MOVE_LEFT 4 //move left by 4
#define MOVE_RIGHT 26 //move right by 26
#define MOVE 4 //Move is 4

#define LIFE_1_X_POSITION 449 //Life 1 x position
#define LIFE_2_X_POSITION 489 //Life 2 x position
#define LIFE_3_X_POSITION 529 //Life 3 x position
#define LIFE_Y_POSITION 5 //Y position for life
#define ALIEN_BULLET_1 1 //Alien bullet number 1
#define ALIEN_BULLET_2 2 //Alien bullet number 2
#define ALIEN_BULLET_3 3 //Alien bullet number 3
#define ALIEN_BULLET_4 4 //Alien bullet number 4

#define BULLET_TYPE_1 0 //Bullet type number 1
#define BULLET_TYPE_2 1 //Bullet type number 2
#define BULLET_MAX_COUNT 4 //Maximum number of alien bullets
#define BULLET_MIDDLE_ALIEN 12 //The middle of an alien

#define CROSS_1 1 //Bullet cross number 1
#define CROSS_2 2 //Bullet cross number 2
#define CROSS_3 3 //Bullet cross number 3
#define NUMBER_OF_CROSS_TYPES 3 //3 types of cross bullets
#define NUMBER_OF_ZIGZAG_TYPES 2 //2 types of cross bullets
#define ZIGZAG_1 1 //Bullet ZIGZAG number 1
#define ZIGZAG_2 2 //Bullet ZIGZAG number 2

#define BUNKER_X_OFFSET BUNKER_BLOCK_WORD_WIDTH //Bunker x offset
#define BUNKER_Y_OFFSET BUNKER_BLOCK_HEIGHT //Bunker y offset
#define BUNKER_NUMBER_BLOCKS_X 4 //Number of x bunker blocks
#define BUNKER_NUMBER_BLOCKS_Y 3 //Number of y bunker blocks
#define BUNKER_NUMBER_TOTAL_BLOCKS 12 //Total number of bunker blocks
#define BUNKER_ROW_1 4 //The first row of bunker blocks
#define BUNKER_ROW_2 8 //The second row of bunker blocks
#define BUNKER_ROW_3 12 //The third row of bunker blocks
#define BUNKER_1_X_POSITION 104 //First bunker x position
#define BUNKER_2_X_POSITION	232 //Second bunker x position
#define BUNKER_3_X_POSITION 360 //Third bunker x position
#define BUNKER_4_X_POSITION	488 //Fourth bunker x position
#define BUNKER_Y_POSITION 367 //Y position for bunkers
#define BUNKER_DEAD_BLOCK 4 //Dead bunker block
#define BUNKER_DAMAGE_1 0 //Bunker damage 1
#define BUNKER_DAMAGE_2 1 //Bunker damage 2
#define BUNKER_DAMAGE_3 2 //Bunker damage 3
#define BUNKER_DAMAGE_4 3 //Bunker damage 4

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
#define ALIEN_ROW_1 11 //Alien row 1
#define ALIEN_ROW_2 22 //Alien row 2
#define ALIEN_ROW_3 33 //Alien row 3
#define ALIEN_ROW_4 44 //Alien row 4
#define ALIEN_ROW_5 55 //Alien row 5
#define ALIEN_ROW_2_OFFSET 1 //Alien row 1 offset
#define ALIEN_ROW_3_OFFSET 2 //Alien row 2 offset
#define ALIEN_ROW_4_OFFSET 3 //Alien row 3 offset
#define ALIEN_ROW_5_OFFSET 4 //Alien row 4 offset
#define ALIEN_ERASE 0 //Erase
#define ALIEN_MOVE_HORIZONTAL 2 //Move horizontal
#define ALIEN_MOVE_VERTICAL 24 //Move vertical
#define ALIEN_MIN_LEFT_MOVE_DEFAULT 0 //Left Default
#define ALIEN_MAX_RIGHT_MOVE_DEFAULT 288 //Right Default
#define ALIEN_COLUMN_EMPTY 0 //Empty
#define ALIEN_NEXT_COL 1 //Column
#define ALIEN_NULL -1 //Null
#define EMPTY_COL_COUNT_INITIALIEZED_TO_ONE 1 //Initialize colum to 1

#define ONE_GAME_PIXELS 2 //One game pixel is 2 pixels
#define TWO_GAME_PIXELS 4 //Two game pixel is 4 pixels
#define THREE_GAME_PIXELS 6 //Three game pixel is 6 pixels
#define FOUR_GAME_PIXELS 8 //Four game pixel is 8 pixels
#define FIVE_GAME_PIXELS 10 //Five game pixel is 10 pixels
#define SIX_GAME_PIXELS 12 //Six game pixel is 12 pixels
#define ELEVEN_GAME_PIXELS 22 //Eleven game pixel is 22 pixels

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

unsigned int * frame_pointer = (unsigned int *) FRAME_BUFFER_0_ADDR_BASE;

static uint8_t alien_block[ALIEN_AMOUNT] = {1,1,1,1,1,1,1,1,1,1,1, \
		1,1,1,1,1,1,1,1,1,1,1, \
		1,1,1,1,1,1,1,1,1,1,1, \
		1,1,1,1,1,1,1,1,1,1,1, \
		1,1,1,1,1,1,1,1,1,1,1};

static uint8_t alien_row_dead[ALIEN_MAX_COL] = {ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW,ALIEN_MAX_ROW};
static int8_t my_alien_row_dead[ALIEN_MAX_COL] = {ALIEN_FOURTY_FOUR,ALIEN_FOURTY_FIVE,ALIEN_FOURTY_SIX,ALIEN_FOURTY_SEVEN,ALIEN_FOURTY_EIGHT,ALIEN_FOURTY_NINE,ALIEN_FIFTY,ALIEN_FIFTY_ONE,ALIEN_FIFTY_TWO,ALIEN_FIFTY_THREE,ALIEN_FIFTY_FOUR};

static uint8_t bunker_1_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,4,4,0};
static uint8_t bunker_2_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,4,4,0};
static uint8_t bunker_3_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,4,4,0};
static uint8_t bunker_4_block_erosion[BUNKER_NUMBER_TOTAL_BLOCKS] = {0,0,0,0,0,0,0,0,0,4,4,0};

static uint16_t tankPosition; //Variable to keep track of tank position

static point_t tankBulletPosition; //Variable to keep track of tank bullet position

static point_t alienBlockPosition; //Keep track of alien block position
static point_t alienBulletPosition1; //Variable to keep track of alien bullet 1 position
static point_t alienBulletPosition2; //Variable to keep track of alien bullet 2 position
static point_t alienBulletPosition3; //Variable to keep track of alien bullet 3 position
static point_t alienBulletPosition4; //Variable to keep track of alien bullet 4 position

static uint8_t bullet_1_type; //Keep track of alien bullet 1 type
static uint8_t bullet_2_type; //Keep track of alien bullet 2 type
static uint8_t bullet_3_type; //Keep track of alien bullet 3 type
static uint8_t bullet_4_type; //Keep track of alien bullet 4 type

static uint8_t bullet_1_shot = FALSE; //Keep track of whether alien bullet 1 was shot
static uint8_t bullet_2_shot = FALSE; //Keep track of whether alien bullet 2 was shot
static uint8_t bullet_3_shot = FALSE; //Keep track of whether alien bullet 3 was shot
static uint8_t bullet_4_shot = FALSE; //Keep track of whether alien bullet 4 was shot

static uint8_t alien_bullet_count = RESET; //Initialize alien bullet count

static uint8_t bullet1_cross; //Keep track of alien bullet 1 cross
static uint8_t bullet2_cross; //Keep track of alien bullet 2 cross
static uint8_t bullet3_cross; //Keep track of alien bullet 3 cross
static uint8_t bullet4_cross; //Keep track of alien bullet 4 cross
static uint8_t bullet1_zigzag; //Keep track of alien bullet 1 zigzag
static uint8_t bullet2_zigzag; //Keep track of alien bullet 2 zigzag
static uint8_t bullet3_zigzag; //Keep track of alien bullet 3 zigzag
static uint8_t bullet4_zigzag; //Keep track of alien bullet 4 zigzag

static int8_t left_most_alien_column; //Left most alien column
static uint8_t all_left_columns_alive = TRUE; //All columns are alive

static uint8_t alien_move_right = TRUE; //Start by moving right
static uint8_t alien_step_out = FALSE; //Alien step out
static uint8_t erase_top_row = FALSE; //Erase the top row
static point_t last_alien_position;

static uint8_t tank_Bullet_Drawn = FALSE; //Was the tank bullet shot

int8_t getMyAlienNumber(int8_t alienIndex){ //Get the number for an alien when given a number
	return my_alien_row_dead[alienIndex];//Return the index of the bottom most alien or null
}

void setTankPosition(uint16_t val){ //Set the position of the tank
	tankPosition = val;
}

uint16_t getTankPosition(){ //get the position of the tank
	return tankPosition;
}

void setTankBulletPosition(point_t val){ //Set the position of the tank bullet
	tankBulletPosition.x = val.x; //X position of bullet
	tankBulletPosition.y = val.y; //Y position of bullet
}

point_t getTankBulletPosition(){ //get position of the tank bullet
	return tankBulletPosition;
}

void setAlienBlockPosition(point_t val){ //Set the position of the alien block
	alienBlockPosition.x = val.x; //X position
	alienBlockPosition.y = val.y; //Y position
}

point_t getAlienBlockPosition(){ //Get the alien block position
	return alienBlockPosition;
}

void setAlienBulletPosition(point_t val, uint8_t bullet_number){ //Set the alien bullet position given a point and a number
	if(bullet_number == ALIEN_BULLET_1){ //Number 1
		alienBulletPosition1.x = val.x; //X position
		alienBulletPosition1.y = val.y; //Y position
	}
	else if(bullet_number == ALIEN_BULLET_2){ //Number 2
		alienBulletPosition2.x = val.x; //X position
		alienBulletPosition2.y = val.y; //Y position
	}
	else if(bullet_number == ALIEN_BULLET_3){ //Number 3
		alienBulletPosition3.x = val.x; //X position
		alienBulletPosition3.y = val.y; //Y position
	}
	else if(bullet_number == ALIEN_BULLET_4){ //Number 4
		alienBulletPosition4.x = val.x; //X position
		alienBulletPosition4.y = val.y; //Y position
	}
}
point_t getAlienBulletPosition(uint8_t bullet_number){ //Get the position for the alien bullet when given a bullet
	if(bullet_number == ALIEN_BULLET_1){ //Number 1
		return alienBulletPosition1;
	}
	else if(bullet_number == ALIEN_BULLET_2){ //Number 2
		return alienBulletPosition2;
	}
	else if(bullet_number == ALIEN_BULLET_3){ //Number 3
		return alienBulletPosition3;
	}
	else{ //Number 4
		return alienBulletPosition4;
	}
}

void drawAlienBullet(uint8_t alienNum, uint8_t bullet_type){ //Draw alien bullet when given an alien and a bullet type
	int8_t alien_shooter = my_alien_row_dead[alienNum]; //Get the alien that shoots
	if(alien_shooter != ALIEN_NULL){ //If the column that the alien shooter is in is not null
		if(alien_bullet_count < BULLET_MAX_COUNT){ //Check to make sure that we don't have the maximum bullets out
			alien_bullet_count++; //increment bullet count


			/*
			//if(alien_bullet_count == ALIEN_BULLET_1){ //if we have one bullet
				if(!bullet_1_shot){ //If bullet one hasn't been shot
					bullet_1_shot = TRUE; //Set to true
					bullet_1_type = bullet_type; //Set the bullet type
					if(bullet_1_type == BULLET_TYPE_1){ //bullet type is a cross
						bullet1_cross = CROSS_1; //Set to cross one
						bullet1_zigzag = FALSE; //Not zigzag
					}
					else{
						bullet1_zigzag = ZIGZAG_1; //Set to zigzag one
						bullet1_cross = FALSE; //Not cross
					}
				}
			//}
			//else if(alien_bullet_count == ALIEN_BULLET_2){ //If we have two bullets
				else if(!bullet_2_shot){ //IF bullet two hasn't been shot
					bullet_2_shot = TRUE; //Set to true
					bullet_2_type = bullet_type; //Set the bullet type
					if(bullet_2_type == BULLET_TYPE_1){ //Bullet type is a cross
						bullet2_cross = CROSS_1; //Set to cross one
						bullet2_zigzag = FALSE; //Not zigzag
					}
					else{
						bullet2_zigzag = ZIGZAG_1; //Set to zigzag one
						bullet2_cross = FALSE; //Not cross
					}
				}
			//}
			//else if(alien_bullet_count == ALIEN_BULLET_3){ //If we have three bullets
				else if(!bullet_3_shot){ //Bullet three hasn't been shot
					bullet_3_shot = TRUE; //Set to true
					bullet_3_type = bullet_type; //Set the bullet type
					if(bullet_3_type == BULLET_TYPE_1){ //Bullet type is a cross
						bullet3_cross = CROSS_1;//Set to cross one
						bullet3_zigzag = FALSE; //Not zigzag
					}
					else{
						bullet3_zigzag = ZIGZAG_1; //Set to zigzag one
						bullet3_cross = FALSE; //Not cross
					}
				}
			//}
			//else{
				else if(!bullet_4_shot){ //Bullet four hasn't been shot
					bullet_4_shot = TRUE; //Set to true
					bullet_4_type = bullet_type; //Set bullet type
					if(bullet_4_type == BULLET_TYPE_1){ //bullet type is a cross
						bullet4_cross = CROSS_1; //Set to cross one
						bullet4_zigzag = FALSE; //Not zigzag
					}
					else{
						bullet4_zigzag = ZIGZAG_1; //Set to zigzag one
						bullet4_cross = FALSE; //Not cross
					}
				}
			//}
			 *
			 *
			 */
			point_t myalienPos = calculateAlienPosition(alien_shooter); //Calculate the alien position
			myalienPos.x += BULLET_MIDDLE_ALIEN; //Set the x
			myalienPos.y += ALIEN_HEIGHT; //Set the y
			setAlienBulletPosition(myalienPos, alien_bullet_count); //Set the position
			if(bullet_type == BULLET_TYPE_1){ //Cross
				uint8_t line, pixel;
				for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){ //For height
					for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){//For width
						if((alien_cross_bullet_1[line] & (SHIFT<<(ALIEN_CROSS_BULLET_WORD_WIDTH-SHIFT-pixel)))){
							frame_pointer[(line + myalienPos.y) * SCREEN_WIDTH + (pixel + myalienPos.x)] = WHITE; //Set to white
						}
					}
				}
			}
			else if(bullet_type == BULLET_TYPE_2){ //Zigzag
				uint8_t line, pixel;
				for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){ //For height
					for(pixel = 0; pixel < ALIEN_ZIGZAG_BULLET_WORD_WIDTH; pixel++){ //For width
						if((alien_zig_zag_bullet_1[line] & (SHIFT<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-SHIFT-pixel)))){
							frame_pointer[(line + myalienPos.y) * SCREEN_WIDTH + (pixel + myalienPos.x)] = WHITE; //Set to white
						}
					}
				}
			}
		}
	}
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

uint16_t getLeftAlienBorder(){//Get the left border for the aliens
	uint16_t left_position = ALIEN_MIN_LEFT_MOVE_DEFAULT;//This is the default
	uint8_t left_most_alive_col; //Create left most column variablle
	for(left_most_alive_col = 0; left_most_alive_col < ALIEN_MAX_COL; left_most_alive_col++){
		if(alien_row_dead[left_most_alive_col] != ALIEN_COLUMN_EMPTY){ //If column is not empty
			break;
		}
	}
	if(left_most_alive_col){ //If we have a column
		all_left_columns_alive = FALSE; //Set to false
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

void killAlien(uint8_t alien_number){
	point_t position = calculateAlienPosition(alien_number); //Calculate alien position
	uint16_t x_position = position.x; //X position
	uint16_t y_position = position.y; //Y position
	uint8_t get_alien_num = alien_number; //Get alien number
	uint8_t alien_column = alien_number % ALIEN_MAX_COL; //Figure out alien column
	uint8_t new_alien_number = alien_row_dead[alien_column]; //Get new alien number
	uint8_t my_new_alien_number = my_alien_row_dead[alien_column];
	uint8_t found = FALSE; //Set found bool to false
	if(alien_row_dead[alien_column] != ALIEN_COLUMN_EMPTY){ //If column is not empty
		alien_row_dead[alien_column] = --new_alien_number; //Decrement alien number
	}
	if(my_alien_row_dead[alien_column] != ALIEN_NULL){ //If column is not null
		if(my_new_alien_number == alien_number){ //If the number is the same
			uint8_t i;
			for(i = 1; i < ALIEN_MAX_ROW; i++){
				if(alien_block[get_alien_num - (i * ALIEN_MAX_COL)] != FALSE){
					my_alien_row_dead[alien_column] = my_new_alien_number - (i * ALIEN_MAX_COL); //Create new number
					found = TRUE; //Set found to true
					break;
				}
			}
			if(found == FALSE){ //If false
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

void eraseAlien(uint16_t x_position, uint16_t y_position, uint8_t alien_type){
	uint8_t line, pixel;
	for(line = 0; line < ALIEN_HEIGHT; line++){ //Height
		for(pixel = 0; pixel < ALIEN_WORD_WIDTH; pixel++){ //Width
			if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == WHITE)
				frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
		}
	}
}

void drawAlien(uint16_t x_position, uint16_t y_position, uint8_t alien_type){
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
		alien_move_right = TRUE; //Set to true
		erase_top_row = TRUE; //Set to true

		if(alien_position.x == LEFT_BORDER && !all_left_columns_alive){
			alien_position.x = RIGHT_BORDER; //Set to right border
		}
	}
	else if(alien_position.x == getRightAlienBorder()){//If we hit the right border then change to move left
		alien_position.y += ALIEN_MOVE_VERTICAL;//This it moves the block down but it doesn't erase the ones that didn't move
		alien_move_right = FALSE; //Set move right to false
		erase_top_row = TRUE; //Set erase top row to true
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
		alien_step_out = FALSE; //Set to false if true
	}
	else{
		alien_step_out = TRUE; //Set to true if false
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
				if(alien_block[num] == FALSE){ //Doesn't exist
					count++; //Increment count
				}
				if(count == ALIEN_MAX_COL){ //Count is 11
					number_of_blank_rows++; //Increment blank rows
					count = RESET; //Reset count
				}
			}
		}
		eraseTopRowAliens(number_of_blank_rows); //Erase top row of aliens
		erase_top_row = FALSE; //Set to false
	}
	updateAlienPosition();
}

void erodeBunker(uint8_t bunker_number, uint8_t block_number){
	uint16_t x_position, y_position;
	uint8_t erosion_number;
	// Set the initial y_position
	y_position = BUNKER_Y_POSITION;
	// Set the initial x_position and increment the appropriate damage for the bunker
	if(bunker_number == BUNKER_1){ //Bunker 1
		if(bunker_1_block_erosion[block_number] < BUNKER_DEAD_BLOCK){
			erosion_number = bunker_1_block_erosion[block_number];
			bunker_1_block_erosion[block_number] = ++erosion_number; //Increment erosion
		}
		x_position = BUNKER_1_X_POSITION;
	}
	else if(bunker_number == BUNKER_2){ //Bunker 2
		if(bunker_2_block_erosion[block_number] < BUNKER_DEAD_BLOCK){
			erosion_number = bunker_2_block_erosion[block_number];
			bunker_2_block_erosion[block_number] = ++erosion_number; //Increment erosion
		}
		x_position = BUNKER_2_X_POSITION;
	}
	else if(bunker_number == BUNKER_3){ //Bunker 3
		if(bunker_3_block_erosion[block_number] < BUNKER_DEAD_BLOCK){
			erosion_number = bunker_3_block_erosion[block_number];
			bunker_3_block_erosion[block_number] = ++erosion_number; //Increment erosion
		}
		x_position = BUNKER_3_X_POSITION;
	}
	else if(bunker_number == BUNKER_4){ //Bunker 4
		if(bunker_4_block_erosion[block_number] < BUNKER_DEAD_BLOCK){
			erosion_number = bunker_4_block_erosion[block_number];
			bunker_4_block_erosion[block_number] = ++erosion_number; //Increment erosion
		}
		x_position = BUNKER_4_X_POSITION;
	}
	// Calculate the x offset.
	x_position += (block_number % BUNKER_NUMBER_BLOCKS_X) * BUNKER_X_OFFSET;
	// Calculate the y offset
	if((block_number >= BUNKER_ROW_1) && (block_number < BUNKER_ROW_2)){
		y_position += BUNKER_Y_OFFSET; //Set y position
	}
	else if((block_number >= BUNKER_ROW_2) && (block_number < BUNKER_ROW_3)){
		y_position += BUNKER_Y_OFFSET + BUNKER_Y_OFFSET; //Set y position
	}
	// Actually erode the appropriate bunker.
	uint8_t line, pixel;
	for(line = 0; line < BUNKER_BLOCK_HEIGHT; line++){ //Height
		for(pixel = 0; pixel < BUNKER_BLOCK_WORD_WIDTH; pixel++){ //Width
			if(erosion_number == BUNKER_DAMAGE_1){ //Bunker damage 1
				if(!(bunker_damage_1[line] & (SHIFT<<(BUNKER_BLOCK_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == GREEN){
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
					}
				}
			}
			else if(erosion_number == BUNKER_DAMAGE_2){ //Bunker damage 2
				if(!(bunker_damage_2[line] & (SHIFT<<(BUNKER_BLOCK_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == GREEN){
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
					}
				}
			}
			else if(erosion_number == BUNKER_DAMAGE_3){ //Bunker damage 3
				if(!(bunker_damage_3[line] & (SHIFT<<(BUNKER_BLOCK_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == GREEN){
						frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
					}
				}
			}
			else if(erosion_number == BUNKER_DAMAGE_4){ //Bunker damage 4
				if(frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] == GREEN){
					frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = BLACK; //Set to black
				}
			}
		}
	}
}

void drawBunker(uint16_t x_position, uint16_t y_position){
	uint8_t line, pixel;
	for(line = 0; line < BUNKER_HEIGHT; line++){ //Height
		for(pixel = 0; pixel < BUNKER_WORD_WIDTH; pixel++){ //Width
			if((bunker_left_half[line] & (SHIFT<<(BUNKER_WORD_WIDTH-SHIFT-pixel)))){
				frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = GREEN; //Set to green
			}
			if((bunker_right_half[line] & (SHIFT<<(BUNKER_WORD_WIDTH-SHIFT-pixel)))){
				frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + BUNKER_WORD_WIDTH + x_position)] = GREEN; //Set to green
			}
		}
	}
}

void drawTankBullet(){
	if(!tank_Bullet_Drawn){ //If not fired
		tank_Bullet_Drawn = TRUE; //Set drawn to true
		//point_t bullet_from_tank_point = getTankBulletPosition();
		point_t updateBullet;
		updateBullet.x = getTankPosition() + TANK_HALF_WIDTH; //mpove x position
		updateBullet.y = TANK_Y_POSITION - TANK_HALF_HEIGHT; //Move y position
		setTankBulletPosition(updateBullet); //Set tank bullet position
		uint8_t line, pixel;
		for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
			for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
				frame_pointer[(line + updateBullet.y)*SCREEN_WIDTH + (pixel + updateBullet.x)] = RED; //Set to red
			}
		}
	}
}

void drawTank(uint8_t direction){
	if(direction == TANK_LEFT){
		// Move the tank left.
		if(getTankPosition() != TANK_LEFT_BORDER){ //This is to make sure that it doesn't go over to the left of the screen when it is at the edge;
			setTankPosition(getTankPosition() - MOVE);
		}
	}
	else if(direction == TANK_RIGHT){
		// Move the tank left.
		if(getTankPosition() < (TANK_RIGHT_BORDER)){ //This should make sure that the tank doesn't go off the edge of the screen might make it (640-32) instead of (640-30)
			setTankPosition(getTankPosition() + MOVE);
		}
	}
	uint8_t line, pixel;
	for(line = 0; line < TANK_HEIGHT; line++){
		for(pixel = 0; pixel < TANK_WORD_WIDTH; pixel++){
			// Stuff to do to move the tank left
			if(direction == TANK_LEFT){
				// Draw the left side of the moving tank
				if((tank_symbol[line] & (SHIFT<<(TANK_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] == BLACK){
						frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] = GREEN; //Set to green
					}
				}
				else{
					if(frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] == GREEN){
						frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] = BLACK; //Set to black
					}
				}
				// Erase the right side of the moving tank
				if(pixel >= (TANK_WORD_WIDTH - MOVE_LEFT)){
					frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + MOVE + getTankPosition())] = BLACK; //Set to black
				}
			}
			// Stuff to do to move the tank right
			else if(direction == TANK_RIGHT){
				// Draw the Right side of the moving tank
				if((tank_symbol[line] & (SHIFT<<(TANK_WORD_WIDTH-SHIFT-pixel)))){
					if(frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] == BLACK){
						frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] = GREEN; //Set to green
					}
				}
				else{
					if(frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] == GREEN){
						frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel + getTankPosition())] = BLACK; //Set to black
					}
				}
				// Erase the left side of the moving tank
				if(pixel < (TANK_WORD_WIDTH - MOVE_RIGHT)){
					frame_pointer[(line + TANK_Y_POSITION)*SCREEN_WIDTH + (pixel - MOVE + getTankPosition())] = BLACK; //Set to black
				}
			}
		}
	}
}

uint8_t updateTankBullet(){
	if(tank_Bullet_Drawn){
		point_t old_tank_bullet_position = getTankBulletPosition(); //Get tank bullet position
		old_tank_bullet_position.y -= (FOUR_GAME_PIXELS); //Increment by 8 pixels
		setTankBulletPosition(old_tank_bullet_position); //Set tank bullet position
		point_t new_tank_bullet_position = getTankBulletPosition(); //Get tank bullet position
		uint8_t line, pixel;
		for(line = 0; line < TANK_BULLET_HEIGHT; line++){ //Height
			for(pixel = 0; pixel < TANK_BULLET_WORD_WIDTH; pixel++){ //Width
				if(old_tank_bullet_position.y > ELEVEN_GAME_PIXELS){
					if(frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] != RED){
						frame_pointer[(line + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = RED; //Set to red
					}
					if(frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] == RED){ //Set to black
						frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y)*SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = BLACK;//Set to black
					}
				}
				else{
					frame_pointer[(line + TANK_HALF_HEIGHT + new_tank_bullet_position.y) * SCREEN_WIDTH + (pixel + new_tank_bullet_position.x)] = BLACK; //Make the last pixel black
					tank_Bullet_Drawn = FALSE; //Bullet set to false
				}
			}
		}
	}
	return tank_Bullet_Drawn;
}

uint8_t draw_alien_cross_type(uint8_t my_bullet_shot, uint8_t my_bullet_cross, point_t my_old_alien_bullet_position, point_t my_new_alien_bullet_position){
	uint8_t line, pixel;
	for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){
		for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){
			if(my_old_alien_bullet_position.y < _ALIEN_BULLET_GROUND_LEVEL){
				uint8_t mine = FALSE;
				if(my_bullet_cross == CROSS_1){ //If cross one
					if(alien_cross_bullet_2[line] & (SHIFT<<(ALIEN_CROSS_BULLET_WORD_WIDTH-SHIFT-pixel))){ //Use cross 2
						mine = TRUE; //Set to true
					}
				}
				else if(my_bullet_cross == CROSS_2){ //If cross two
					if(alien_cross_bullet_3[line] & (SHIFT<<(ALIEN_CROSS_BULLET_WORD_WIDTH-SHIFT-pixel))){ //Use cross 3
						mine = TRUE; //Set to true
					}
				}
				else if(my_bullet_cross == CROSS_3){ //If cross three
					if(alien_cross_bullet_1[line] & (SHIFT<<(ALIEN_CROSS_BULLET_WORD_WIDTH-SHIFT-pixel))){ //Use cross 1
						mine = TRUE; //Set to true
					}
				}
				else{
					mine = FALSE; //Set to false
				}
				if(mine){ //If bool is true
					if(frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + 	my_new_alien_bullet_position.x)] != WHITE){
						frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = WHITE; //Set to white
					}
					else if(frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] == WHITE){
						frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK; //Black out the last shape
					}
					if(frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] == WHITE){
						frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK;//Black out the last shape
						frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + ONE_GAME_PIXELS + my_new_alien_bullet_position.x)] = BLACK;//Black out the last shape
						frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel - ONE_GAME_PIXELS + my_new_alien_bullet_position.x)] = BLACK;//Black out the last shape
					}
				}
			}
			else{
				frame_pointer[(line - FIVE_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK; //Black out the last shape
				my_bullet_shot = FALSE; //Set to false
			}
		}
	}
	return my_bullet_shot;
}

uint8_t draw_alien_zigzag_type(uint8_t my_bullet_shot, uint8_t my_bullet_zigzag, point_t my_old_alien_bullet_position, point_t my_new_alien_bullet_position){
	uint8_t line, pixel;
	for(line = 0; line < ALIEN_BULLET_HEIGHT; line++){ //Height
		for(pixel = 0; pixel < ALIEN_CROSS_BULLET_WORD_WIDTH; pixel++){ //Width
			if(my_old_alien_bullet_position.y < _ALIEN_BULLET_GROUND_LEVEL){ //We are at ground level
				uint8_t mine = FALSE; //Set to false
				if(my_bullet_zigzag == ZIGZAG_1){ //We are type 1
					if(alien_zig_zag_bullet_2[line] & (SHIFT<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-SHIFT-pixel))){ //Set to type 2
						mine = TRUE; //Set to true
					}
				}
				else if(my_bullet_zigzag == ZIGZAG_2){ //We are tpe 2
					if(alien_zig_zag_bullet_1[line] & (SHIFT<<(ALIEN_ZIGZAG_BULLET_WORD_WIDTH-SHIFT-pixel))){ //Set to type 1
						mine = TRUE; //Set to true
					}
				}
				else{
					mine = FALSE; //Set to false
				}
				if(mine){ //If bool is true
					if(frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] != WHITE){
						frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = WHITE; //Set to white
					}
					else if(frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] == WHITE){
						frame_pointer[(line + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK; //If white, make black
					}
					if(frame_pointer[(line - SIX_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] == WHITE){
						frame_pointer[(line - SIX_GAME_PIXELS + my_new_alien_bullet_position.y)*SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK;//Set to black
					}
				}
			}
			else{
				frame_pointer[(line - FOUR_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK; //Black out the last shape
				frame_pointer[(line - SIX_GAME_PIXELS + my_new_alien_bullet_position.y) * SCREEN_WIDTH + (pixel + my_new_alien_bullet_position.x)] = BLACK; //Black out the last shape
				my_bullet_shot = FALSE; //Set to false
			}
		}
	}
	return my_bullet_shot;
}

void updateIndividualAlienBullet(uint8_t bullet_number){
	point_t old_alien_bullet_position;
	point_t new_alien_bullet_position;

	if(bullet_number == ALIEN_BULLET_1){ //Bullet 1
		if(bullet_1_shot){ //Bullet one was shot
			old_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien position
			old_alien_bullet_position.y += ALIEN_BULLET_HEIGHT; //Add to the height
			setAlienBulletPosition(old_alien_bullet_position, bullet_number); //Set the alien bullet position
			new_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien bullet position
			if(bullet1_cross){ //Bullet cross  is true
				bullet_1_shot = draw_alien_cross_type(bullet_1_shot, bullet1_cross, old_alien_bullet_position, new_alien_bullet_position);
				if(bullet1_cross < CROSS_3){
					bullet1_cross++; //Increment cross shape
				}
				else{
					bullet1_cross = CROSS_1; //When maxed out set to the first
				}
			}
			else if(bullet1_zigzag){ //We have a zigzag bullet
				bullet_1_shot = draw_alien_zigzag_type(bullet_1_shot, bullet1_zigzag, old_alien_bullet_position, new_alien_bullet_position);
				if(bullet1_zigzag < ZIGZAG_2){
					bullet1_zigzag++; //Increment zigzag shape
				}
				else{
					bullet1_zigzag = ZIGZAG_1; //When maxed out set to the first
				}
			}
			if(!bullet_1_shot){ //When we turn off the first bullet
				alien_bullet_count--; //Decrement alien bullet count
			}
		}
	}
	else if(bullet_number == ALIEN_BULLET_2){ //bullet 2
		if(bullet_2_shot){ //Bullet two was shot
			old_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien position
			old_alien_bullet_position.y += ALIEN_BULLET_HEIGHT; //Add to the height
			setAlienBulletPosition(old_alien_bullet_position, bullet_number); //Set alien bullet position
			new_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien bullet position
			if(bullet2_cross){ //Bullet cross  is true
				bullet_2_shot = draw_alien_cross_type(bullet_2_shot, bullet2_cross, old_alien_bullet_position, new_alien_bullet_position);
				if(bullet2_cross < CROSS_3){
					bullet2_cross++; //Increment cross shape
				}
				else{
					bullet2_cross = CROSS_1; //When maxed out set to the first
				}
			}
			else if(bullet2_zigzag){
				bullet_2_shot = draw_alien_zigzag_type(bullet_2_shot, bullet2_zigzag, old_alien_bullet_position, new_alien_bullet_position);
				if(bullet2_zigzag < ZIGZAG_2){
					bullet2_zigzag++; //Increment zigzag shape
				}
				else{
					bullet2_zigzag = ZIGZAG_1; //When maxed out set to the first
				}
			}
			if(!bullet_2_shot){ //When we turn off the second bullet
				alien_bullet_count--; //Decrement alien bullet count
			}
		}
	}
	else if(bullet_number == ALIEN_BULLET_3){
		if(bullet_3_shot){
			old_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien position
			old_alien_bullet_position.y += ALIEN_BULLET_HEIGHT; //Add to the height
			setAlienBulletPosition(old_alien_bullet_position, bullet_number); //Set alien bullet position
			new_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien bullet position
			if(bullet3_cross){ //Bullet cross  is true
				bullet_3_shot = draw_alien_cross_type(bullet_3_shot, bullet3_cross, old_alien_bullet_position, new_alien_bullet_position);
				if(bullet3_cross < CROSS_3){
					bullet3_cross++; //Increment cross shape
				}
				else{
					bullet3_cross = CROSS_1; //When maxed out set to the first
				}
			}
			else if(bullet3_zigzag){
				bullet_3_shot = draw_alien_zigzag_type(bullet_3_shot, bullet3_zigzag, old_alien_bullet_position, new_alien_bullet_position);
				if(bullet3_zigzag < ZIGZAG_2){
					bullet3_zigzag++; //Increment zigzag shape
				}
				else{
					bullet3_zigzag = ZIGZAG_1; //When maxed out set to the first
				}
			}
			if(!bullet_3_shot){ //When we turn off the third bullet
				alien_bullet_count--; //Decrement alien bullet count
			}
		}
	}
	else if(bullet_number == ALIEN_BULLET_4){
		if(bullet_4_shot){
			old_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien position
			old_alien_bullet_position.y += ALIEN_BULLET_HEIGHT; //Add to the height
			setAlienBulletPosition(old_alien_bullet_position, bullet_number); //Set alien bullet position
			new_alien_bullet_position = getAlienBulletPosition(bullet_number); //Get alien bullet position
			if(bullet4_cross){//Bullet cross  is true
				bullet_4_shot = draw_alien_cross_type(bullet_4_shot, bullet4_cross, old_alien_bullet_position, new_alien_bullet_position);
				if(bullet4_cross < CROSS_3){
					bullet4_cross++; //Increment cross shape
				}
				else {
					bullet4_cross = CROSS_1; //When maxed out set to the first
				}
			}
			else if(bullet4_zigzag){
				bullet_4_shot = draw_alien_zigzag_type(bullet_4_shot, bullet4_zigzag, old_alien_bullet_position, new_alien_bullet_position);
				if(bullet4_zigzag < ZIGZAG_2){
					bullet4_zigzag++; //Increment zigzag shape
				}
				else{
					bullet4_zigzag = ZIGZAG_1; //When maxed out set to the first
				}
			}
			if(!bullet_4_shot){ //When we turn off the fourth bullet
				alien_bullet_count--; //Decrement alien bullet count
			}
		}
	}
}

uint8_t updateAlienBullet(){
	updateIndividualAlienBullet(ALIEN_BULLET_1); //Update bullet 1
	updateIndividualAlienBullet(ALIEN_BULLET_2); //Update bullet 2
	updateIndividualAlienBullet(ALIEN_BULLET_3); //Update bullet 3
	updateIndividualAlienBullet(ALIEN_BULLET_4); //Update bullet 4
	return alien_bullet_count; //Return the number of alien bullets on the screen
}

void drawLife(uint16_t x_position, uint16_t y_position){ //Draw life function
	uint8_t line, pixel;
	for(line = 0; line < TANK_HEIGHT; line++){ //For height
		for(pixel = 0; pixel < TANK_WORD_WIDTH; pixel++){ //For width
			if((tank_symbol[line] & (SHIFT<<(TANK_WORD_WIDTH-SHIFT-pixel)))){
				frame_pointer[(line + y_position)*SCREEN_WIDTH + (pixel + x_position)] = GREEN; //Set to green
			}
		}
	}
}

unsigned int * draw_start_screen(){
	setTankPosition(TANK_INITIAL_X_POSITION); //Set tank position
	uint16_t row, col;
	for(row=0; row < SCREEN_HEIGHT; row++) {
		for(col=0; col < SCREEN_WIDTH; col++) {
			if(row == GROUND_LEVEL || row == (GROUND_LEVEL - INCREMENT_OR_DECREMENT)){ //This is to draw the bottom line of the game
				frame_pointer[row*SCREEN_WIDTH + col] = GREEN;
			}
			else{
				frame_pointer[row*SCREEN_WIDTH + col] = BLACK;
			}
		}
	}
	uint16_t tank_position;
	tank_position = TANK_INITIAL_X_POSITION;
	setTankPosition(tank_position); //Set tank
	drawLife(TANK_INITIAL_X_POSITION, TANK_Y_POSITION); //Draw tank
	drawLife(LIFE_1_X_POSITION, LIFE_Y_POSITION); //Draw life 1
	drawLife(LIFE_2_X_POSITION, LIFE_Y_POSITION); //Draw life 2
	drawLife(LIFE_3_X_POSITION, LIFE_Y_POSITION); //Draw life 3
	drawBunker(BUNKER_1_X_POSITION, BUNKER_Y_POSITION); //Draw bunker 1
	drawBunker(BUNKER_2_X_POSITION, BUNKER_Y_POSITION); //Draw bunker 2
	drawBunker(BUNKER_3_X_POSITION, BUNKER_Y_POSITION); //Draw bunker 3
	drawBunker(BUNKER_4_X_POSITION, BUNKER_Y_POSITION); //Draw bunker 4
	point_t alien_block_position;
	alien_block_position.x = ALIEN_INITIAL_X_POSITION; //Alien x
	alien_block_position.y = ALIEN_INITIAL_Y_POSITION; //Alien y
	setAlienBlockPosition(alien_block_position); //Set the alien block position
	drawAlienBlock(); //Draw the alien block
	return frame_pointer; //Return the fram pointer
}
