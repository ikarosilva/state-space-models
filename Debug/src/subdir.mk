################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/conway.c \
../src/five.c \
../src/hh.c \
../src/inflammation.c \
../src/logistic.c \
../src/lorenz.c \
../src/models.c \
../src/one.c \
../src/rungekutta4.c \
../src/sine.c \
../src/three.c \
../src/wbc.c \
../src/white.c 

OBJS += \
./src/conway.o \
./src/five.o \
./src/hh.o \
./src/inflammation.o \
./src/logistic.o \
./src/lorenz.o \
./src/models.o \
./src/one.o \
./src/rungekutta4.o \
./src/sine.o \
./src/three.o \
./src/wbc.o \
./src/white.o 

C_DEPS += \
./src/conway.d \
./src/five.d \
./src/hh.d \
./src/inflammation.d \
./src/logistic.d \
./src/lorenz.d \
./src/models.d \
./src/one.d \
./src/rungekutta4.d \
./src/sine.d \
./src/three.d \
./src/wbc.d \
./src/white.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


