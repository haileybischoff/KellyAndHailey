################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BaseHit.c \
../src/InvHit.c \
../src/Shot.c \
../src/Walk1.c \
../src/Walk2.c \
../src/Walk3.c \
../src/Walk4.c \
../src/alienKilled.c \
../src/draw.c \
../src/draw_alien_bullet.c \
../src/draw_aliens.c \
../src/draw_bunker.c \
../src/draw_saucer.c \
../src/draw_tank.c \
../src/draw_tank_bullet.c \
../src/game.c \
../src/main_space_invaders.c \
../src/newUfo.c \
../src/newUfoHit.c \
../src/oldUfo.c \
../src/oldUfoHit.c \
../src/platform.c \
../src/saucer.c \
../src/saucerHit.c \
../src/score_keeping.c \
../src/sound.c \
../src/sound_motherShipHigh.c \
../src/sound_motherShipLow.c \
../src/spaceInvadersGame.c \
../src/tankFireSound.c \
../src/xac97_l.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/BaseHit.o \
./src/InvHit.o \
./src/Shot.o \
./src/Walk1.o \
./src/Walk2.o \
./src/Walk3.o \
./src/Walk4.o \
./src/alienKilled.o \
./src/draw.o \
./src/draw_alien_bullet.o \
./src/draw_aliens.o \
./src/draw_bunker.o \
./src/draw_saucer.o \
./src/draw_tank.o \
./src/draw_tank_bullet.o \
./src/game.o \
./src/main_space_invaders.o \
./src/newUfo.o \
./src/newUfoHit.o \
./src/oldUfo.o \
./src/oldUfoHit.o \
./src/platform.o \
./src/saucer.o \
./src/saucerHit.o \
./src/score_keeping.o \
./src/sound.o \
./src/sound_motherShipHigh.o \
./src/sound_motherShipLow.o \
./src/spaceInvadersGame.o \
./src/tankFireSound.o \
./src/xac97_l.o 

C_DEPS += \
./src/BaseHit.d \
./src/InvHit.d \
./src/Shot.d \
./src/Walk1.d \
./src/Walk2.d \
./src/Walk3.d \
./src/Walk4.d \
./src/alienKilled.d \
./src/draw.d \
./src/draw_alien_bullet.d \
./src/draw_aliens.d \
./src/draw_bunker.d \
./src/draw_saucer.d \
./src/draw_tank.d \
./src/draw_tank_bullet.d \
./src/game.d \
./src/main_space_invaders.d \
./src/newUfo.d \
./src/newUfoHit.d \
./src/oldUfo.d \
./src/oldUfoHit.d \
./src/platform.d \
./src/saucer.d \
./src/saucerHit.d \
./src/score_keeping.d \
./src/sound.d \
./src/sound_motherShipHigh.d \
./src/sound_motherShipLow.d \
./src/spaceInvadersGame.d \
./src/tankFireSound.d \
./src/xac97_l.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../hello_world_bsp_0/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


