################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/draw.c \
../src/draw_alien_bullet.c \
../src/draw_aliens.c \
../src/draw_bunker.c \
../src/draw_saucer.c \
../src/draw_tank.c \
../src/draw_tank_bullet.c \
../src/game.c \
../src/main_space_invaders.c \
../src/platform.c \
../src/score_keeping.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/draw.o \
./src/draw_alien_bullet.o \
./src/draw_aliens.o \
./src/draw_bunker.o \
./src/draw_saucer.o \
./src/draw_tank.o \
./src/draw_tank_bullet.o \
./src/game.o \
./src/main_space_invaders.o \
./src/platform.o \
./src/score_keeping.o 

C_DEPS += \
./src/draw.d \
./src/draw_alien_bullet.d \
./src/draw_aliens.d \
./src/draw_bunker.d \
./src/draw_saucer.d \
./src/draw_tank.d \
./src/draw_tank_bullet.d \
./src/game.d \
./src/main_space_invaders.d \
./src/platform.d \
./src/score_keeping.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../hello_world_bsp_0/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


