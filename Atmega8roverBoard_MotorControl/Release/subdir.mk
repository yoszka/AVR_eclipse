################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../adc.c \
../main.c \
../motor.c \
../protocol.c \
../system.c \
../tasks.c \
../tasks_aux.c \
../timer.c \
../usart.c \
../util.c 

OBJS += \
./adc.o \
./main.o \
./motor.o \
./protocol.o \
./system.o \
./tasks.o \
./tasks_aux.o \
./timer.o \
./usart.o \
./util.o 

C_DEPS += \
./adc.d \
./main.d \
./motor.d \
./protocol.d \
./system.d \
./tasks.d \
./tasks_aux.d \
./timer.d \
./usart.d \
./util.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"G:\E_ELEKTRONIKA\WinAVR\eclipse_kopia\WORKSPACE\AVR_eclipse\Atmega8roverBoard_MotorControl\headers" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


