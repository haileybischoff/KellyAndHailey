################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/sound/BaseHit.c \
../src/sound/InvHit.c \
../src/sound/Shot.c \
../src/sound/Walk1.c \
../src/sound/Walk2.c \
../src/sound/Walk3.c \
../src/sound/Walk4.c \
../src/sound/alienKilled.c \
../src/sound/newUfo.c \
../src/sound/newUfoHit.c \
../src/sound/oldUfo.c \
../src/sound/oldUfoHit.c \
../src/sound/saucer.c \
../src/sound/saucerHit.c \
../src/sound/sound_motherShipHigh.c \
../src/sound/sound_motherShipLow.c \
../src/sound/tankFireSound.c 

OBJS += \
./src/sound/BaseHit.o \
./src/sound/InvHit.o \
./src/sound/Shot.o \
./src/sound/Walk1.o \
./src/sound/Walk2.o \
./src/sound/Walk3.o \
./src/sound/Walk4.o \
./src/sound/alienKilled.o \
./src/sound/newUfo.o \
./src/sound/newUfoHit.o \
./src/sound/oldUfo.o \
./src/sound/oldUfoHit.o \
./src/sound/saucer.o \
./src/sound/saucerHit.o \
./src/sound/sound_motherShipHigh.o \
./src/sound/sound_motherShipLow.o \
./src/sound/tankFireSound.o 

C_DEPS += \
./src/sound/BaseHit.d \
./src/sound/InvHit.d \
./src/sound/Shot.d \
./src/sound/Walk1.d \
./src/sound/Walk2.d \
./src/sound/Walk3.d \
./src/sound/Walk4.d \
./src/sound/alienKilled.d \
./src/sound/newUfo.d \
./src/sound/newUfoHit.d \
./src/sound/oldUfo.d \
./src/sound/oldUfoHit.d \
./src/sound/saucer.d \
./src/sound/saucerHit.d \
./src/sound/sound_motherShipHigh.d \
./src/sound/sound_motherShipLow.d \
./src/sound/tankFireSound.d 


# Each subdirectory must supply rules for building sources it contributes
src/sound/%.o: ../src/sound/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../hello_world_bsp_0/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


