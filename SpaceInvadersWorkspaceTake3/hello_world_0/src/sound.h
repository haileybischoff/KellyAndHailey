/*
 * sound.h
 *
 *  Created on: Nov 3, 2017
 *      Author: superman
 */

#ifndef SOUND_H_
#define SOUND_H_

void sound_init_AC_97();

void turn_sound_vol_up();
void turn_sound_vol_down();

void initial_sound_init_tank_fire();
void sound_init_tank_fire();
void initial_sound_init_tank_hit();
void sound_init_tank_hit();
void initial_sound_init_alien_hit();
void sound_init_alien_hit();
void initial_sound_init_move1();
void sound_init_move1();
void initial_sound_init_move2();
void sound_init_move2();
void initial_sound_init_move3();
void sound_init_move3();
void initial_sound_init_move4();
void sound_init_move4();
void initial_sound_init_saucer_move();
void sound_init_saucer_move();
void initial_sound_init_saucer_hit();
void sound_init_saucer_hit();

void sound_saucer_stop();

void sound_run();


#endif /* SOUND_H_ */
