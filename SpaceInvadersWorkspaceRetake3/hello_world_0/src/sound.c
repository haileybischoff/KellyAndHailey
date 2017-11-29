/*
 * sound.c
 *
 *  Created on: Nov 3, 2017
 *      Author: superman
 */

#include <stdint.h>
#include <stdbool.h>
#include "xac97_l.h"
#include "xparameters.h"

#define ZERO 0
#define INCREMENT_SOUND 100
#define VOLUME_STEP 300
#define SHIFT 16
#define VOLUME_STEP_LEVEL 0x101

#define SET_VOLUME(vol) \
		XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCMOutVol, (vol)); \
		XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_AuxOutVol, (vol)); \
		XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVol, (vol))

//From the Shot.c file
extern int32_t tankFire_sampleRate;
extern int32_t tankFire_length;
extern int32_t tankFire_data[];

struct tankFire_sound{
	int32_t count; // = tankFire_length;
}tankFire_sound;

//struct tankFire_sound tank_sound = {tankFire_length;}

//From the BaseHit.c
extern int32_t tankDeathSampleRate;
extern int32_t tankDeathSound_length;
extern int32_t tankDeathSound_data[];
struct tankDeath_sound{
	int32_t count ;//= tankDeathSound_length;
}tankDeath_sound;

//From the InvHit.c
//extern int32_t alienHitSound_sampleRate;
//extern int32_t alienHitSound_length;
//extern int32_t alienHitSound_data[];

extern int32_t alienKilled_sampleRate;
extern int32_t alienKilled_length;
extern int32_t alienKilled_data[];


struct alienHit_sound{
	int32_t count ;//= alienKilled_length;
}alienHit_sound;

//From the Walk1.c
extern int32_t alienMoveSound1_sampleRate;
extern int32_t alienMoveSound1_length;
extern int32_t alienMoveSound1_data[];
struct alienWalk_sound1{
	int32_t count ;//= alienMoveSound1_length;
}alienWalk_sound1;

//From the Walk2.c
extern int32_t alienMoveSound2_sampleRate;
extern int32_t alienMoveSound2_length;
extern int32_t alienMoveSound2_data[];
struct alienWalk_sound2{
	int32_t count ;//= alienMoveSound2_length;
}alienWalk_sound2;

//From the Walk3.c
extern int32_t alienMoveSound3_sampleRate;
extern int32_t alienMoveSound3_length;
extern int32_t alienMoveSound3_data[];
struct alienWalk_sound3{
	int32_t count ;//= alienMoveSound3_length;
}alienWalk_sound3;

//From the Walk4.c
extern int32_t alienMoveSound4_sampleRate;
extern int32_t alienMoveSound4_length;
extern int32_t alienMoveSound4_data[];
struct alienWalk_sound4{
	int32_t count ;//= alienMoveSound4_length;
}alienWalk_sound4;

//From the Ufo.c

//extern int32_t saucer_sampleRate;
//extern int32_t saucer_length;
//extern int32_t saucer_data[];

//extern int32_t ufoSound_sampleRate;
//extern int32_t ufoSound_length;
//extern int32_t ufoSound_data[];
struct ufo_sound{
	int32_t count ;//= motherShipLowSoundFrames;
}ufo_sound;

//From the UfoHit.c

//extern int32_t saucerHit_sampleRate;
//extern int32_t saucerHit_length;
//extern int32_t saucerHit_data[];

//extern int32_t ufoHitSound_sampleRate;
//extern int32_t ufoHitSound_length;
//extern int32_t ufoHitSound_data[];




extern int32_t motherShipLowSoundRate;// sample rate
extern int32_t motherShipLowSoundFrames;// size of array

extern int32_t motherShipLowSound[];


extern int32_t motherShipHighSoundRate;// sample rate
extern int32_t motherShipHighSoundFrames;// size of array

extern int32_t motherShipHighSound[];





struct ufoHit_sound{
	int32_t count ;//= motherShipHighSoundFrames;
}ufoHit_sound;

static uint32_t sound_vol = AC97_VOL_MAX;


void sound_init_AC_97(){
	//Reset the AC_97 --------------------------------
	XAC97_HardReset(XPAR_AXI_AC97_0_BASEADDR);

	//Init the Audio ---------------------------------
	XAC97_InitAudio(XPAR_AXI_AC97_0_BASEADDR, 0);

	//Wait -------------------------------------------
	XAC97_AwaitCodecReady(XPAR_AXI_AC97_0_BASEADDR);

	//enable VRA -------------------------------------
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_ExtendedAudioStat, AC97_EXTENDED_AUDIO_CONTROL_VRA);

	//set frequency DAC ------------------------------
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCM_DAC_Rate, AC97_PCM_RATE_8000_HZ);

	//set volumes-------------------------------------
	sound_vol = AC97_VOL_MAX; //AC97_Vol_MAX
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVol, sound_vol);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_AuxOutVol, sound_vol);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVolMono, sound_vol);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCBeepVol, sound_vol);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCMOutVol, sound_vol);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_LineInVol, sound_vol);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MicVol, sound_vol);


	//XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCMOutVol, AC97_VOL_MID); --Just Andy

	//clear FIFO
	XAC97_ClearFifos(XPAR_AXI_AC97_0_BASEADDR);

	//set control bit to cause IN_FIFO interrupts
	XAC97_mSetControl(XPAR_AXI_AC97_0_BASEADDR, AC97_ENABLE_IN_FIFO_INTERRUPT);
}

//Initialize the tank fire counter

void initial_sound_init_tank_fire(){
	tankFire_sound.count = tankFire_length;
}

void sound_init_tank_fire(){
	tankFire_sound.count = ZERO;
}

void initial_sound_init_tank_hit(){
	tankDeath_sound.count = tankDeathSound_length;
}

//Initialize the tank hit counter
void sound_init_tank_hit(){
	tankDeath_sound.count = ZERO;
}

void initial_sound_init_alien_hit(){
	alienHit_sound.count = alienKilled_length;
}

//Initialize the alien hit counter
void sound_init_alien_hit(){
	alienHit_sound.count = ZERO;
}

void initial_sound_init_move1(){
	//xil_printf("we have initialized alien movement 1\n\r");
	alienWalk_sound1.count = alienMoveSound1_length;
}

//Initialize the alien move 1 counter
void sound_init_move1(){
	//xil_printf("we have initialized alien movement 1\n\r");
	alienWalk_sound1.count = ZERO;
}

void initial_sound_init_move2(){
	alienWalk_sound2.count = alienMoveSound2_length;
}

//Initialize the alien move 2 counter
void sound_init_move2(){
	alienWalk_sound2.count = ZERO;
}

void initial_sound_init_move3(){
	alienWalk_sound3.count = alienMoveSound3_length;
}

//Initialize the alien move 3 counter
void sound_init_move3(){
	alienWalk_sound3.count = ZERO;
}

void initial_sound_init_move4(){
	alienWalk_sound4.count = alienMoveSound4_length;
}

//Initialize the alien move 4 counter
void sound_init_move4(){
	alienWalk_sound4.count = ZERO;
}

void initial_sound_init_saucer_move(){
	ufo_sound.count = motherShipLowSoundFrames;
}

//Initialize the Saucer move counter
void sound_init_saucer_move(){
	if(ufo_sound.count >= motherShipLowSoundFrames){
		ufo_sound.count = ZERO;
	}
}

void initial_sound_init_saucer_hit(){ //High
	ufoHit_sound.count = motherShipHighSoundFrames;
}

//Initialize the Saucer hit counter
void sound_init_saucer_hit(){ //High
	ufoHit_sound.count = ZERO;
}

void alien_move1_sound_method(){
	uint32_t i;
	uint32_t sample = ZERO;
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCM_DAC_Rate, alienMoveSound1_sampleRate);
	for(i = 0; i < INCREMENT_SOUND; i++){
		alienWalk_sound1.count++;
		//int32_t mine1 = alienWalk_sound1.count;
		//uint32_t check1 = alienMoveSound1_data[mine1] << SHIFT;
		sample = (alienMoveSound1_data[alienWalk_sound1.count] << SHIFT) | alienMoveSound1_data[alienWalk_sound1.count];
		XAC97_mSetInFifoData(XPAR_AXI_AC97_0_BASEADDR, sample);
		if(alienWalk_sound1.count >= alienMoveSound1_length){
			XAC97_ClearFifos(XPAR_AXI_AC97_0_BASEADDR);
			XAC97_mSetControl(XPAR_AXI_AC97_0_BASEADDR, AC97_ENABLE_IN_FIFO_INTERRUPT);
		}
	}
}

//Tank fire sound method
void sound_method(int32_t SoundRate, int32_t Sound_length, int32_t Sound[], int32_t counter){
	uint32_t i;
	uint32_t sample = ZERO;
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCM_DAC_Rate, SoundRate);
	for(i = 0; i < INCREMENT_SOUND; i++){
		counter++;
		sample = (Sound[counter] << SHIFT) | Sound[counter];
		XAC97_mSetInFifoData(XPAR_AXI_AC97_0_BASEADDR, sample);
		if(counter >= Sound_length){
			XAC97_ClearFifos(XPAR_AXI_AC97_0_BASEADDR);
			XAC97_mSetControl(XPAR_AXI_AC97_0_BASEADDR, AC97_ENABLE_IN_FIFO_INTERRUPT);
		}
	}
}




void alien_sound_method(int32_t SoundRate, int32_t Sound_length, int32_t Sound[], int32_t * count){
	uint32_t i;
	uint32_t sample = ZERO;
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCM_DAC_Rate, SoundRate);
	for(i = 0; i < INCREMENT_SOUND; i++){
		(*count)++;
		sample = (Sound[*count] << SHIFT) | Sound[*count];
		XAC97_mSetInFifoData(XPAR_AXI_AC97_0_BASEADDR, sample);
		if(*count >= Sound_length){
			XAC97_ClearFifos(XPAR_AXI_AC97_0_BASEADDR);
			XAC97_mSetControl(XPAR_AXI_AC97_0_BASEADDR, AC97_ENABLE_IN_FIFO_INTERRUPT);
		}
		//if()
	}
}

//Tank fire sound method
/*
void alien_sound_method(int32_t SoundRate, int32_t Sound_length, int32_t Sound[], struct alienWalk_sound1 sound_st){
	uint32_t i;
	uint32_t sample = ZERO;
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCM_DAC_Rate, SoundRate);
	for(i = 0; i < INCREMENT_SOUND; i++){
		sound_st.count++;
		sample = (Sound[sound_st.count] << SHIFT) | Sound[sound_st.count];
		XAC97_mSetInFifoData(XPAR_AXI_AC97_0_BASEADDR, sample);
		if(sound_st.count >= Sound_length){
			XAC97_ClearFifos(XPAR_AXI_AC97_0_BASEADDR);
			XAC97_mSetControl(XPAR_AXI_AC97_0_BASEADDR, AC97_ENABLE_IN_FIFO_INTERRUPT);
		}
	}
}
 */
void turn_sound_vol_up(){
	if(sound_vol == AC97_VOL_MAX){ //If we are at max do nothing

	}
	else if(sound_vol == AC97_VOL_MUTE){ //If we are at the mute sound, set to min
		sound_vol = AC97_VOL_MIN;
	}
	else{
		if(sound_vol < VOLUME_STEP_LEVEL){ //If we subtract the level & it's negative do nothing

		}
		else{
			sound_vol -= VOLUME_STEP_LEVEL; //Increment by a nice level
		}
	}
	SET_VOLUME(sound_vol); //Set the sound
}
void turn_sound_vol_down(){
	if(sound_vol == AC97_VOL_MUTE){ //If we are at mute, do nothing

	}
	else if(sound_vol >= AC97_VOL_MIN){ //If at the min
		sound_vol = AC97_VOL_MIN; //Set to the min
	}
	else{
		if((AC97_VOL_MIN - sound_vol) < VOLUME_STEP_LEVEL){ //If we subtract and its not there
				//Do nothing
		}
		else {
			sound_vol += VOLUME_STEP_LEVEL;//Decrement by a nice level
		}
	}
	SET_VOLUME(sound_vol); //Set the sound
}
void sound_saucer_stop(){
	ufo_sound.count = motherShipLowSoundFrames + VOLUME_STEP;
}

void sound_run(){
	bool tankShot = false; //Bool to know the priority of tank shot
	bool tankKilled = false; //Bool to know the priority of tank killed
	bool alienKilled = false; //Bool to know the priority of alien killed
	bool alienMove1 = false; //Bool to know the priority of alien move 1
	bool alienMove2 = false; //Bool to know the priority of alien move 2
	bool alienMove3 = false; //Bool to know the priority of alien move 3
	bool alienMove4 = false; //Bool to know the priority of lien move 4
	bool saucerMove = false; //Bool to know the priority of saucer move
	bool saucerKilled = false; //Bool to know the priority of saucer killed


	if(tankFire_sound.count <= tankFire_length){
		tankShot = true; //Priority for tank shot and set the fifo
		alien_sound_method(tankFire_sampleRate, tankFire_length, tankFire_data, &tankFire_sound.count);
	}
	//Fourth tank death
	else if(tankDeath_sound.count <= tankDeathSound_length){
		tankKilled = true; //Priority for tank death and set the fifo
		alien_sound_method(tankDeathSampleRate, tankDeathSound_length, tankDeathSound_data, &tankDeath_sound.count);
	}
	//Sixth kill alien
	else if(alienHit_sound.count <= alienKilled_length){
		alienKilled = true; //Priority for alien death and set the fifo
		alien_sound_method(alienKilled_sampleRate, alienKilled_length, alienKilled_data, &alienHit_sound.count);
	}
	//Fifth move aliens
	else if(alienWalk_sound1.count <= alienMoveSound1_length){
		alienMove1 = true; //Priority for alien move 1 and set the fifo
		alien_sound_method(alienMoveSound1_sampleRate, alienMoveSound1_length, alienMoveSound1_data, &alienWalk_sound1.count);
	}
	else if(alienWalk_sound2.count <= alienMoveSound2_length){
		alienMove2 = true; //Priority for alien move 2 and set the fifo
		alien_sound_method(alienMoveSound2_sampleRate, alienMoveSound2_length, alienMoveSound2_data, &alienWalk_sound2.count);
	}
	else if(alienWalk_sound3.count <= alienMoveSound3_length){
		alienMove3 = true; //Priority for alien move 3 and set the fifo
		alien_sound_method(alienMoveSound3_sampleRate, alienMoveSound3_length, alienMoveSound3_data, &alienWalk_sound3.count);
	}
	else if(alienWalk_sound4.count <= alienMoveSound4_length){
		alienMove4 = true; //Priority for alien move 4 and set the fifo
		alien_sound_method(alienMoveSound4_sampleRate, alienMoveSound4_length, alienMoveSound4_data, &alienWalk_sound4.count);
	}
	//Second ufo
	else if(ufo_sound.count <= motherShipLowSoundFrames){
		saucerMove = true; //Priority for saucer move and set the fifo
		alien_sound_method(motherShipLowSoundRate, motherShipLowSoundFrames, motherShipLowSound, &ufo_sound.count);
	}
	//Third ufo hit
	else if(ufoHit_sound.count <= motherShipHighSoundFrames){
		saucerKilled = true; //Priority for saucer killed and set the fifo
		alien_sound_method(motherShipHighSoundRate, motherShipHighSoundFrames, motherShipHighSound, &ufoHit_sound.count);
	}
	else{
		XAC97_ClearFifos(XPAR_AXI_AC97_0_BASEADDR);
		XAC97_mSetControl(XPAR_AXI_AC97_0_BASEADDR, AC97_ENABLE_IN_FIFO_INTERRUPT);
	}
	/* Alien hit was here */
	if((tankDeath_sound.count <= tankDeathSound_length) && !tankShot){
		tankDeath_sound.count += INCREMENT_SOUND; //Increment the tank death
	}
	//Sixth kill alien
	if((alienHit_sound.count <= alienKilled_length) && !tankKilled){
		alienHit_sound.count += INCREMENT_SOUND; //Increment the alien death
	}
	//Fifth move aliens
	if((alienWalk_sound1.count <= alienMoveSound1_length) && !alienMove1){
		alienWalk_sound1.count += INCREMENT_SOUND; //Increment the alien move 1
	}
	if((alienWalk_sound2.count <= alienMoveSound2_length) && !alienMove2){
		alienWalk_sound2.count += INCREMENT_SOUND; //Increment the alien move 2
	}
	if((alienWalk_sound3.count <= alienMoveSound3_length) && !alienMove3){
		alienWalk_sound3.count += INCREMENT_SOUND; //Increment the alien move 3
	}
	if((alienWalk_sound4.count <= alienMoveSound4_length) && !alienMove4){
		alienWalk_sound4.count += INCREMENT_SOUND; //Increment the alien move 4
	}
	//Second ufo
	if((ufo_sound.count <= motherShipLowSoundFrames) && !saucerMove){
		ufo_sound.count += INCREMENT_SOUND; //Increment the saucer move
	}
	//Third ufo hit
	if((ufoHit_sound.count <= motherShipHighSoundFrames) && !saucerKilled){
		ufoHit_sound.count += INCREMENT_SOUND; //Increment the saucer death
	}
}
