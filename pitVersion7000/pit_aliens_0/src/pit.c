/*
 * pit.c
 *
 *  Created on: Nov 9, 2017
 *      Author: superman
 */

#include "pit.h"
#include "xparameters.h"


#define CONTROL_ALL_ON 7 //This turns bits 0-2 on on the control
#define MILLION 1000000 //This is the number we choose to initialize as the delaay for our clock

void init_pit(){
	PIT_mWriteSlaveReg2(XPAR_PIT_0_BASEADDR,CONTROL_ALL_ON); //Control reg write
	PIT_mWriteSlaveReg1(XPAR_PIT_0_BASEADDR,MILLION); //Delay is set
}
