/*
 * main.c
 *
 *  Created on: Oct 20, 2017
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

#define FRAME_BUFFER_0_ADDR 0xC1000000  // Starting location in DDR where we will store the images that we display.

uint32_t currentButtonState = 0;
uint32_t debouncedButtonState = 0;	// Saves the debounced button states
uint16_t btn_count; //Timer for buttons

XGpio gpPB;   // This is a handle for the push-button GPIO block.

uint32_t interruptCounter = 0;

// Main interrupt handler, queries the interrupt controller to see what peripheral
// fired the interrupt and then dispatches the corresponding interrupt handler.
// This routine acks the interrupt at the controller level but the peripheral
// interrupt must be ack'd by the dispatched interrupt handler.
void interrupt_handler_dispatcher(void* ptr) {
	int intc_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);
	// Check the FIT interrupt first.
	if (intc_status & XPAR_FIT_TIMER_0_INTERRUPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
		interruptCounter++;
		xil_printf("%d\n\r", interruptCounter);
	}
}

int main()
{
	init_platform();

	microblaze_register_handler(interrupt_handler_dispatcher, NULL);
	XIntc_EnableIntr(XPAR_INTC_0_BASEADDR, (XPAR_FIT_TIMER_0_INTERRUPT_MASK));
	XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);
	microblaze_enable_interrupts();

	xil_printf("Start\r\n");
	while (1);

	cleanup_platform();

	return 0;
}

