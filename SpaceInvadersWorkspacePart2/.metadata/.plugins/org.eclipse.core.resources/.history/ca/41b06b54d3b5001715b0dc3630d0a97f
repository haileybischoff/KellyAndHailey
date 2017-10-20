################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/draw.c \
../src/main_space_invaders.c \
../src/platform.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/draw.o \
./src/main_space_invaders.o \
./src/platform.o 

C_DEPS += \
./src/draw.d \
./src/main_space_invaders.d \
./src/platform.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../hello_world_bsp_0/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


