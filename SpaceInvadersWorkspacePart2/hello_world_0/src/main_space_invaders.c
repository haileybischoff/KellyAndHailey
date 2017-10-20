/*
 * main_space_invaders.c
 *
 *  Created on: Oct 5, 2017
 *      Author: superman
 */

#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "xparameters.h"
#include "xaxivdma.h"
#include "xio.h"
#include "time.h"
#include "unistd.h"
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.
#include "xgpio.h"          // Provides access to PB GPIO driver.
#include "draw.h"
#include <stdbool.h>

#define TANK_LEFT_MASK 8 //This is the hour mask
#define TANK_FIRE_BULLET_MASK 1 //This is the minute mask
#define TANK_RIGHT_MASK 2 //This is the second mask

#define MAX_NUMBER_OF_ALIENS_IN_A_ROW 11
#define TOTAL_NUMBER_OF_BLOCKS 12
#define NUMBER_OF_DIFFERENT_ALIEN_BULLET_TYPES 2
#define MAX_NUMBER_OF_ALIEN_BULLETS 4
#define ALIEN_NULL -1

#define DEFAULT_LIVES 3

#define RESET 0// Reset is 0

#define ALIEN_BULLET_UPDATE_TIME 2500

#define BULLET_UPDATE_TIME 100

#define BLANK_BLOCK_1 9 //This is the blank block for the bunkers
#define BLANK_BLOCK_2 10 //This is the blank block for the bunkers
#define BUTTON_TIME 10000000
#define NUMBER_LENGTH 2 //The length of a number is 2
#define NUMBER_LENGTH_ONE 1 //the length of a number is 1

#define MAX_DEBOUNCE_TIME 100
#define MAX_ALIEN_BULLET_TIME 100000
#define MAX_TANK_BULLET_TIME 100
#define MAX_TANK_DEATH_TIME 100
#define MAX_NUMBER_ALIEN_BULLETS 4
#define MAX_ALIEN_DEATH_TIME 100

#define MOVE_LEFT 4 //move left by 4
#define MOVE_RIGHT 26 //move right by 26

void print(char *str); //This is a void print function

#define SAUCER_MAX_TIME 2000 // This is the max time before a saucer will go accross the board again.

#define FRAME_BUFFER_0_ADDR 0xC1000000  // Starting location in DDR where we will store the images that we display.
#define DEBOUNCE_VALUE 0x0000001F

#define LEFT_BUTTON_MASK 8 //This is the mask for the left push button it moves the tank left.
#define MIDDLE_BUTTON_MASK 1 //This is the mask for the middle push button it shoots a bullet.
#define RIGHT_BUTTON_MASK 2 //This is the mask for the right push button it moves the tank right.
#define TOP_BUTTON_MASK 16 //This is the mask for the top push button it will be used fro incrementing volume eventually
#define BOTTOM_BUTTON_MASK 4 //This is the mask for the bottom push button it will be used for decrementing volume eventually

#define TANK_MOVE_MAX_COUNTER 5 // 5 is a 50th of a second
#define ALIEN_MOVE_MAX_COUNTER 50 // 50 is a half second since the interrupt happens every 10 mS.
#define SAUCER_MOVE_MAX_COUNTER 10 // 10 is a tenth of a second for moving the saucer.

/***************** INTERRUPT HANDLER STUFF *****************************/
XGpio gpPB;   // This is a handle for the push-button GPIO block.

uint16_t alien_bullets = RESET; //Count for the number of alien bullets on the screen
uint32_t alienCounter = RESET; //Alien counter initialized to 0
uint16_t debounceCounter = RESET; //Debounce counter initialized to 0
uint16_t alienDeathCounter = RESET; //Alien Death Counter initialized to 0
uint16_t tankDeathCounter = RESET; //Tank death counter initialized to 0
uint16_t tankBulletFiredMinCounter = RESET; //Bullet Fired Min COunter initialized to 0
uint16_t alienBulletFiredMinCounter = RESET; //Bullet Fired Min COunter initialized to 0

uint32_t updateBulletCounter = RESET;

uint32_t randomCounter = RESET;


uint32_t alienBulletMaxValue = RESET; //Alien bullet max value is initialized to 0
uint16_t alienRandValue = RESET; //


uint8_t alienColumn = RESET;
uint8_t alienBulletType = RESET;

bool alienDeathFlag = false; //Flag for alien death
bool tankDeathFlag = false; //Flag for tank death
bool bulletFireFlag = false; //Flag for whether a bullet has been fired

bool move_alien_recieved_flag = false; //Flag to let us know we went into the alien moved state;
bool button_pressed_recieved_flag = false; //Flag to let us know we went into the button pressed state
bool tank_bullet = false; //Bool for tank bullet

uint32_t currentButtonState = 0;
uint32_t debouncedButtonState = 0;	// Saves the debounced button states
uint16_t btn_count; //Timer for buttons

/****************** DRAW TANK STUFF ************************************/
uint16_t tankMoveCounter = RESET; //Tank move counter initialized to 0
uint8_t moveTankCounter = RESET;

bool moveLeftFlag = false;
bool moveRightFlag = false;

/****************** DRAW TANK BULLET STUFF *****************************/
bool shootTankBulletFlag = false;

/****************** DRAW SUACER STUFF **********************************/
uint16_t saucerMoveCounter = RESET; // This is the counter that counts how long between when we update saucer draw.
uint16_t saucerRandValueCounter = RESET; // This is the time that we have between drawing saucers
uint16_t saucerRandValueMax = RESET; // This value will hold the recalculated max for the Random Value counter

bool drawSaucerFlag = false; // Tells us to draw the saucer
bool saucerDrawnFlag = false;

/***************** FUNCTIONS *******************************************/

void debounce_buttons(){ //this takes the button and debounces it for us it also sets the flags for each button
	debouncedButtonState = currentButtonState & DEBOUNCE_VALUE;
	if((debouncedButtonState & LEFT_BUTTON_MASK) && !(debouncedButtonState & RIGHT_BUTTON_MASK)){
		moveLeftFlag = true;
		moveRightFlag = false;
	}
	if((debouncedButtonState & RIGHT_BUTTON_MASK) && !(debouncedButtonState & LEFT_BUTTON_MASK)){
		moveRightFlag = true;
		moveLeftFlag = false;
	}
	if(debouncedButtonState & MIDDLE_BUTTON_MASK){
		shootTankBulletFlag = true;
	}
}

enum SpaceInvadersControl_st{
	init_st,
	idle_st,
	move_aliens_st,
	update_bullet_st,
	dead_alien_st,
	bunker_st,
	dead_tank_st,
	move_tank_right_st,
	move_tank_left_st,
	draw_saucer_st,
	new_alien_bullet_st
} currentState = init_st;

// Set the seed for the random-number generator.
void wamControl_setRandomSeed(uint32_t seed){

}

//print state machine for debug purposes
void debugStatePrint(){
	static enum SpaceInvadersControl_st previousState;
	static bool firstPass = true;
	// Only print the message if:
	// 1. This the first pass and the value for previousState is unknown.
	// 2. previousState != currentState - this prevents reprinting the same state name over and over.
	if((previousState != currentState) || firstPass) {
		firstPass = false;                // previousState will be defined, firstPass is false.
		previousState = currentState;     // keep track of the last state that you were in.
		switch(currentState){
		case init_st:
			xil_printf("INIT State\n\r");
			break;
		case idle_st:
			xil_printf("IDLE State\n\r");
			break;
		case move_aliens_st:
			xil_printf("MOVE ALIENS State\n\r");
			break;
		case update_bullet_st:
			xil_printf("UPDATE BULLETS State\n\r");
			break;
		case dead_alien_st:
			xil_printf("DEAD ALIEN State\n\r");
			break;
		case bunker_st:
			xil_printf("BUNKER State\n\r");
			break;
		case dead_tank_st:
			xil_printf("DEAD TANK State\n\r");
			break;
		case move_tank_right_st:
			break;
		case move_tank_left_st:
			break;
		case draw_saucer_st:
			break;
		case new_alien_bullet_st:
			xil_printf("NEW ALIEN BULLET State\n\r");
			break;
		default:
			xil_printf("spaceInvaders_tick update: hit default\n\r");
			break;
		}
	}

}

void spaceInvaders_tick(){

	uint8_t isSaucerDrawn = RESET;

	//State actions
	switch(currentState){
	case init_st:
		alienDeathFlag = false; //Alien Death flag set to false
		tankDeathFlag = false; //Tank Death flag set to false
		bulletFireFlag = false; //Bullet Fire flag set to false
		drawSaucerFlag = false; //Saucer flag set to false

		alienCounter = RESET; //Alien counter initialized to 0
		debounceCounter = RESET; //Debounce counter initialized to 0
		alienDeathCounter = RESET; //Alien Death Counter initialized to 0
		tankDeathCounter = RESET; //Tank death counter initialized to 0
		tankBulletFiredMinCounter = RESET; //Bullet Fired Min COunter initialized to 0
		alienBulletFiredMinCounter = RESET; //Bullet Fired Min COunter initialized to 0
		saucerMoveCounter = RESET; //Saucer counter initialized to 0
		saucerRandValueCounter = RESET; // Reset this random value saucer counter.

		moveTankCounter = RESET; //Tank move counter initialized to 0
		moveLeftFlag = false;
		moveRightFlag = false;

		randomCounter = 1000000;//Increment the random counter //TODO
		srand(randomCounter); //Pass the random counter as the seed to srand
		alienRandValue = rand() % MAX_NUMBER_OF_ALIENS_IN_A_ROW; //TODO initialize to rand() % y
		saucerRandValueMax = RESET; //TODO initialize to rand() % x

		break;
	case idle_st:
		debounce_buttons(); // This function debounces the buttons and sets flags.

		//xil_printf("Alien Counter is: %d\n\r", alienCounter);

		moveTankCounter++; // This is a counter to know the timing of when we need to move the tank.

		alienCounter++;
		if(alien_bullets < MAX_NUMBER_ALIEN_BULLETS){
			alienBulletMaxValue++;
			updateBulletCounter++;
		}


		if(drawSaucerFlag){ // If the saucer is supposed to be drawn
			saucerMoveCounter++; // Increment the time for how long between when we move the saucer
		}
		else{ // Otherwise there is no saucer on the screen
			saucerRandValueCounter++; // So we have to count between when the next suacer get's drawn.
			if(saucerMoveCounter >= saucerRandValueMax){ // If we get above our saucer random max then
				drawSaucerFlag = true; // We'll need to set our draw saucer flag to true
				saucerRandValueMax = rand() % SAUCER_MAX_TIME; // We'll need to generate a new random saucer max
				saucerRandValueCounter = RESET; // We'll need to reset the saucer rand value counter.
			}
		}

		//if buttons are pressed
		//debounceCounter++;

		/*
			if(alienDeathFlag == true){
				alienDeathCounter++;
			}
			if(saucerMoveCounter >= saucerRandValue){
				saucerDrawnFlag = true;
			}
			if(tank_bullet == true){
				tankBulletFiredMinCounter++;
			}
			if(alien_bullets > 0){
				alienBulletFiredMinCounter++;
			}
		 */
		break;
	case move_aliens_st:
		alienCounter = RESET; //Reset alien move counter
		//if(saucerDrawnFlag == true){
		//	saucerDrawnFlag = false;
		//call draw saucer function
		//}
		drawAlienBlock(); //Draw the block of aliens
		break;
	case update_bullet_st:
		updateBulletCounter = RESET;
		alien_bullets = updateAlienBullet();
		break;
	case dead_alien_st:
		break;
	case bunker_st:
		break;
	case dead_tank_st:
		break;
	case move_tank_right_st:
		drawTank(TANK_RIGHT);
		break;
	case move_tank_left_st:
		drawTank(TANK_LEFT);
		break;
	case draw_saucer_st:
		isSaucerDrawn = drawSaucer();
		if(!isSaucerDrawn){
			drawSaucerFlag = false;
		}
		break;
	case new_alien_bullet_st:
		alienBulletMaxValue = RESET;
		alien_bullets++;
		//randomCounter = randomCounter % 20000; //TODO
		alienBulletType = rand()%NUMBER_OF_DIFFERENT_ALIEN_BULLET_TYPES; //Set the bullet type
		alienColumn = (rand()%MAX_NUMBER_OF_ALIENS_IN_A_ROW);//Set the column alien number
		while(getMyAlienNumber(alienColumn) == ALIEN_NULL){ //If the column is null
			alienColumn = (rand()%MAX_NUMBER_OF_ALIENS_IN_A_ROW);//Keep trying for a new column
		}
		drawAlienBullet(alienColumn, alienBulletType); //Call draw alien bullet with the column and bullet type
		break;
	default:
		break;
	}


	//State transitions
	switch(currentState){
	case init_st:
		currentState = idle_st;
		break;
	case idle_st:
		/*
			if(debounceCounter >= MAX_DEBOUNCE_TIME){ //Check for debounce time
				currentState = button_pressed_st;
			}
			else if(alienDeathCounter >= MAX_ALIEN_DEATH_TIME){
				currentState = dead_alien_st;
			}
			else if(((tank_bullet == true) && (tankBulletFiredMinCounter >= MAX_TANK_BULLET_TIME))|| ((alien_bullets > 0) && (alienBulletFiredMinCounter >= MAX_ALIEN_BULLET_TIME))){
				currentState = update_bullet_st;
			}
		 */

		if(moveRightFlag && (moveTankCounter >= TANK_MOVE_MAX_COUNTER)){
			moveTankCounter = RESET;
			moveRightFlag = false;
			currentState = move_tank_right_st; // We need to go move the tank right.
		}
		else if(moveLeftFlag && (moveTankCounter >= TANK_MOVE_MAX_COUNTER)){ // Basically if a button is pushed
			moveTankCounter = RESET;
			moveLeftFlag = false;
			currentState = move_tank_left_st; // We need to go move the tank left.
		}
		else if((alien_bullets < MAX_NUMBER_ALIEN_BULLETS) && (alienBulletMaxValue >= randomCounter)){
			currentState = new_alien_bullet_st;
		}
		else if((alien_bullets < MAX_NUMBER_ALIEN_BULLETS) &&(updateBulletCounter >= 15000)){//MAX_ALIEN_BULLET_TIME //TODO
			currentState = update_bullet_st;
		}
		else if(alienCounter >= ALIEN_MOVE_MAX_COUNTER){ //Check for time to move aliens
			currentState = move_aliens_st;
		}
		else if(drawSaucerFlag && saucerMoveCounter >= SAUCER_MOVE_MAX_COUNTER){
			saucerMoveCounter = RESET;
			currentState = draw_saucer_st;
		}
		else{
			currentState = idle_st;
		}
		break;
	case move_aliens_st:
		currentState = idle_st;
		break;
	case update_bullet_st:
		//if bullet has collision with bunker
		//currentState = bunker_st; //Go to bunker state
		//else if tank bullet has collision with alien
		//currentState = deadAlienSt; //Go to dead alien state
		alienDeathFlag = true;
		//else if alien bullet has collision with tank
		//currentState = deadTankSt; //Go to dead tank state
		//else
		currentState = idle_st; //Go to idle state
		break;
	case dead_alien_st:
		currentState = idle_st;
		break;
	case bunker_st:
		currentState = idle_st;
		break;
	case dead_tank_st:
		/*
			if(tankDeathCounter >= MAX_TANK_DEATH_TIME){
				currentState = idle_st;
			}
			else{
				currentState = dead_tank_st;
			}

		 */
		break;
	case move_tank_right_st:
		currentState = idle_st;
		break;
	case move_tank_left_st:
		currentState = idle_st;
		break;
	case draw_saucer_st:
		currentState = idle_st;
		break;
	case new_alien_bullet_st:
		currentState = idle_st;
		break;
	default:
		break;
	}
}

// This is invoked each time there is a change in the button state (result of a push or a bounce).
void pb_interrupt_handler() {
  // Clear the GPIO interrupt.
  XGpio_InterruptGlobalDisable(&gpPB);                // Turn off all PB interrupts for now.
  currentButtonState = XGpio_DiscreteRead(&gpPB, 1);  // Get the current state of the buttons.

  // Reset button counter
  btn_count = 0;
  XGpio_InterruptClear(&gpPB, 0xFFFFFFFF);            // Ack the PB interrupt.
  XGpio_InterruptGlobalEnable(&gpPB);                 // Re-enable PB interrupts.
}

// Main interrupt handler, queries the interrupt controller to see what peripheral
// fired the interrupt and then dispatches the corresponding interrupt handler.
// This routine acks the interrupt at the controller level but the peripheral
// interrupt must be ack'd by the dispatched interrupt handler.
void interrupt_handler_dispatcher(void* ptr) {
	int intc_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);
	// Check the FIT interrupt first.
	if (intc_status & XPAR_FIT_TIMER_0_INTERRUPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
		spaceInvaders_tick();
	}
	// Check the push buttons.
	if (intc_status & XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK);
		pb_interrupt_handler();
	}
}

int main()
{
	init_platform();
	// Initialize the GPIO peripherals.
	int success;
	success = XGpio_Initialize(&gpPB, XPAR_PUSH_BUTTONS_5BITS_DEVICE_ID);
	// Set the push button peripheral to be inputs.
	XGpio_SetDataDirection(&gpPB, 1, 0x0000001F);
	// Enable the global GPIO interrupt for push buttons.
	XGpio_InterruptGlobalEnable(&gpPB);
	// Enable all interrupts in the push button peripheral.
	XGpio_InterruptEnable(&gpPB, 0xFFFFFFFF);

	microblaze_register_handler(interrupt_handler_dispatcher, NULL);
	XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
			(XPAR_FIT_TIMER_0_INTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK));
	XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);
	microblaze_enable_interrupts();

	//init_platform();                   // Necessary for all programs.
	int Status;                        // Keep track of success/failure of system function calls.
	XAxiVdma videoDMAController;
	// There are 3 steps to initializing the vdma driver and IP.
	// Step 1: lookup the memory structure that is used to access the vdma driver.
	XAxiVdma_Config * VideoDMAConfig = XAxiVdma_LookupConfig(XPAR_AXI_VDMA_0_DEVICE_ID);
	// Step 2: Initialize the memory structure and the hardware.
	if(XST_FAILURE == XAxiVdma_CfgInitialize(&videoDMAController, VideoDMAConfig,	XPAR_AXI_VDMA_0_BASEADDR)) {
		xil_printf("VideoDMA Did not initialize.\r\n");
	}
	// Step 3: (optional) set the frame store number.
	if(XST_FAILURE ==  XAxiVdma_SetFrmStore(&videoDMAController, 2, XAXIVDMA_READ)) {
		xil_printf("Set Frame Store Failed.");
	}
	// Initialization is complete at this point.

	// Setup the frame counter. We want two read frames. We don't need any write frames but the
	// function generates an error if you set the write frame count to 0. We set it to 2
	// but ignore it because we don't need a write channel at all.
	XAxiVdma_FrameCounter myFrameConfig;
	myFrameConfig.ReadFrameCount = 2;
	myFrameConfig.ReadDelayTimerCount = 10;
	myFrameConfig.WriteFrameCount =2;
	myFrameConfig.WriteDelayTimerCount = 10;
	Status = XAxiVdma_SetFrameCounter(&videoDMAController, &myFrameConfig);
	if (Status != XST_SUCCESS) {
		xil_printf("Set frame counter failed %d\r\n", Status);
		if(Status == XST_VDMA_MISMATCH_ERROR)
			xil_printf("DMA Mismatch Error\r\n");
	}
	// Now we tell the driver about the geometry of our frame buffer and a few other things.
	// Our image is 480 x 640.
	XAxiVdma_DmaSetup myFrameBuffer;
	myFrameBuffer.VertSizeInput = 480;    // 480 vertical pixels.
	myFrameBuffer.HoriSizeInput = 640*4;  // 640 horizontal (32-bit pixels).
	myFrameBuffer.Stride = 640*4;         // Dont' worry about the rest of the values.
	myFrameBuffer.FrameDelay = 0;
	myFrameBuffer.EnableCircularBuf=1;
	myFrameBuffer.EnableSync = 0;
	myFrameBuffer.PointNum = 0;
	myFrameBuffer.EnableFrameCounter = 0;
	myFrameBuffer.FixedFrameStoreAddr = 0;
	if(XST_FAILURE == XAxiVdma_DmaConfig(&videoDMAController, XAXIVDMA_READ, &myFrameBuffer)) {
		xil_printf("DMA Config Failed\r\n");
	}
	// We need to give the frame buffer pointers to the memory that it will use. This memory
	// is where you will write your video data. The vdma IP/driver then streams it to the HDMI
	// IP.
	myFrameBuffer.FrameStoreStartAddr[0] = FRAME_BUFFER_0_ADDR;
	myFrameBuffer.FrameStoreStartAddr[1] = FRAME_BUFFER_0_ADDR + 4*640*480;

	if(XST_FAILURE == XAxiVdma_DmaSetBufferAddr(&videoDMAController, XAXIVDMA_READ,
			myFrameBuffer.FrameStoreStartAddr)) {
		xil_printf("DMA Set Address Failed Failed\r\n");
	}
	// Print a sanity message if you get this far.
	xil_printf("Woohoo! I made it through initialization.\n\r");
	// Now, let's get ready to start displaying some stuff on the screen.
	// The variables framePointer and framePointer1 are just pointers to the base address
	// of frame 0 and frame 1.
	unsigned int * framePointer0 = draw_start_screen();//(unsigned int *) FRAME_BUFFER_0_ADDR;

	// This tells the HDMI controller the resolution of your display (there must be a better way to do this).
	XIo_Out32(XPAR_AXI_HDMI_0_BASEADDR, 640*480);

	// Start the DMA for the read channel only.
	if(XST_FAILURE == XAxiVdma_DmaStart(&videoDMAController, XAXIVDMA_READ)){
		xil_printf("DMA START FAILED\r\n");
	}
	int frameIndex = 0;
	// We have two frames, let's park on frame 0. Use frameIndex to index them.
	// Note that you have to start the DMA process before parking on a frame.
	if (XST_FAILURE == XAxiVdma_StartParking(&videoDMAController, frameIndex,  XAXIVDMA_READ)) {
		xil_printf("vdma parking failed\n\r");
	}
	// Oscillate between frame 0 and frame 1.
	while (1) { //Keep playing the game until you run out of lives
		//frameIndex = (frameIndex + 1) % 2;  // Alternate between frame 0 and frame 1.
		if (XST_FAILURE == XAxiVdma_StartParking(&videoDMAController, frameIndex,  XAXIVDMA_READ)) {
			xil_printf("vdma parking failed\n\r");
		}
	}
	cleanup_platform();

	return 0;
}
