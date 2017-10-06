/*
 * main_space_invaders.c
 *
 *  Created on: Oct 5, 2017
 *      Author: superman
 */

#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xaxivdma.h"
#include "xio.h"
#include "time.h"
#include "unistd.h"

#include "draw.h"

#define MOVE_TANK_RIGHT_KEY '6'
#define MOVE_TANK_LEFT_KEY '4'
#define ERODE_BUNKER '7'
#define KILL_ALIEN '2'
#define UPDATE_ALIEN_POSITION '8'

#define RAND_MAX 65535
#define RESET 0

#define BLANK_BLOCK_1 9
#define BLANK_BLOCK_2 10

#define NUMBER_LENGTH 2

#define DEBUG
void print(char *str);

#define FRAME_BUFFER_0_ADDR 0xC1000000  // Starting location in DDR where we will store the images that we display.

uint8_t getNumber(){
	 char number[NUMBER_LENGTH];
	 int final_number;
	 //fgets(number, sizeof(number), getchar());
	 scanf("%d", &final_number);
	 return final_number;
}

int main()
{
	init_platform();                   // Necessary for all programs.
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
     //unsigned int * framePointer1 = ((unsigned int *) FRAME_BUFFER_0_ADDR) + 640*480;
     // Just paint some large red, green, blue, and white squares in different
     // positions of the image for each frame in the buffer (framePointer0 and framePointer1).
     /*int row=0, col=0;
     for( row=0; row<480; row++) {
    	 for(col=0; col<640; col++) {
    	 if(row < 240) {
    		 if(col<320) {
    			 // upper left corner.
    			 framePointer0[row*640 + col] = 0x00FF0000;  // frame 0 is red here.
    			 framePointer1[row*640 + col] = 0x0000FF00;  // frame 1 is green here.
    		 } else {
    			 // upper right corner.
    			 framePointer0[row*640 + col] = 0x000000FF;  // frame 0 is blue here.
    			 framePointer1[row*640 + col] = 0x00FF0000;  // frame 1 is red here.
    		 }
    	 } else {
    		 if(col<320) {
    			 // lower left corner.
    			 framePointer0[row*640 + col] = 0x0000FF00;  // frame 0 is green here.
    			 framePointer1[row*640 + col] = 0x00FFFFFF;  // frame 1 is white here.
    		 } else {
    			 // lower right corner.
    			 framePointer0[row*640 + col] = 0x00000000;  // frame 0 is black here.
    			 framePointer1[row*640 + col] = 0x000000FF;  // frame 1 is blue here.
    		 }
    	 }
       }
     }*/

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
     uint16_t random_counter = RESET;
     while (1) {
    	 char input = getchar();
    	 random_counter++;
    	 if(random_counter == RAND_MAX)
    	 {
    		 random_counter = RESET;
    	 }
 		 switch(input){
  		 case MOVE_TANK_RIGHT_KEY:
  			 xil_printf("MOVE RIGHT\n\r");
  			 drawTank(TANK_RIGHT);
  			 break;
  		 case MOVE_TANK_LEFT_KEY:
  			 xil_printf("MOVE LEFT\n\r");
  			 drawTank(TANK_LEFT);
  			 break;
  		 case ERODE_BUNKER:
  			 xil_printf("ERODE_BUNKER\n\r");
  			 uint8_t bunker_number, block_number;
  			 bunker_number = random_counter % 4;
  			 block_number = random_counter % 12;
  			 if(block_number == BLANK_BLOCK_1){
  				 block_number--;
  			 }
  			 else if(block_number == BLANK_BLOCK_2){
  				 block_number++;
  			 }
  			 erodeBunker(bunker_number, block_number);
  			 break;
  		 case KILL_ALIEN:
  			 xil_printf("KILL_ALIEN\n\r");
  			 uint8_t alien_number = getNumber();
  			 killAlien(alien_number);
  			 break;
  		 case UPDATE_ALIEN_POSITION:
  			 xil_printf("UPDATE_ALIEN_POSITION\n\r");
  			 drawAlienBlock();
  			 break;
  		 default:
  			 xil_printf("WE PUSHED A DIFFERENT KEY\n\r");
  			 break;
  		 }
         //frameIndex = (frameIndex + 1) % 2;  // Alternate between frame 0 and frame 1.
         if (XST_FAILURE == XAxiVdma_StartParking(&videoDMAController, frameIndex,  XAXIVDMA_READ)) {
        	 xil_printf("vdma parking failed\n\r");
         }
     }
     cleanup_platform();

    return 0;
}