################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lcd_jokii.c \
../main.c \
../system.c \
../tasks.c \
../usart.c \
../util.c 

OBJS += \
./lcd_jokii.o \
./main.o \
./system.o \
./tasks.o \
./usart.o \
./util.o 

C_DEPS += \
./lcd_jokii.d \
./main.d \
./system.d \
./tasks.d \
./usart.d \
./util.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


