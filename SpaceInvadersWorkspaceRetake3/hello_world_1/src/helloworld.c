/*
 * Copyright (c) 2009 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "platform.h"

FILE *fileptr;			// Pointer to input file
FILE *outFILE;			// Pointer to output file
char *buffer;			// the buffer for reading chars in
long filelen;			// the lenth of the file


void print(char *str);

#define LEN 256
int main()
{
    init_platform();

    /*


    char* filename = "Shot.wav";
    char* outfilename = "shot.c";
    print("Hello World\n\r");

	uint32_t i;
	for(i = 0; i < 10; i++){
		//xil_printf("%d\n\r", i);
		xil_printf("%s\n\r", filename);

		//printf("%d\n\r", i);
	}

	unsigned char buffer[10];
	fileptr = fopen(filename, "rb");
	fread(buffer, sizeof(buffer),1,fileptr);

	int32_t j;
	for(j=0;j<10;j++){					// read 10 bytes of the file, print hex
		xil_printf("%x ", buffer[j]);
	}


	unsigned int single_byte = 0;
	*/

	/*
	while(1){
		fread(&single_byte, sizeof(char), 1, fileptr);
		if(single_byte == 'd'){
			fread(&single_byte, sizeof(char), 1, fileptr);
			if(single_byte == 'a'){
				fread(&single_byte, sizeof(char), 1, fileptr);
				if(single_byte == 't'){
					fread(&single_byte, sizeof(char), 1, fileptr);
					if(single_byte == 'a'){
						break;
					}
				}
			}
		}
	}
	*/

	//fclose(fileptr);

	// If we get here, we have reached the data portion of the wav file.
	// Now to get ready to write
	//outFILE = fopen(outfilename, 'w');	// open the file for writing
	//if(outFILE==NULL){
		//xil_printf("bad file\n\r");		// error message
		//return;
	//}







	   FILE * fp;
	   uint8_t jk;
	   /* open the file for writing*/
	   fp = fopen ("kelly.txt","w");

	   /* write 10 lines of text into the file stream*/
	   for(jk = 0; jk < 10;jk++){
		   //uint8_t k = jk + 1;
	       fprintf (fp, "This is line %d\n", (jk + 1));
	   }

	   /* close the file*/
	   fclose (fp);











/*

	// We are good
	//fprintf(outFILE, "START of our awesome file:\n\n");

	// fread will return 0 into yeah when we reach the end of the file
	size_t yeah;
	while((yeah = fread(&single_byte, sizeof(char), 1, fileptr)) != 0){
		//fprintf(outFILE, "%u, ", single_byte);	// Just write the byte to the new file
	}

		// Close both of the files
	fclose(outFILE);
	fclose(fileptr);

*/

	//fclose(fileptr);
	xil_printf("Finished\n\r");
    cleanup_platform();

    return 0;



}
