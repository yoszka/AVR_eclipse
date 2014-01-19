################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sensors/dht11.c \
../sensors/ds1820.c 

OBJS += \
./sensors/dht11.o \
./sensors/ds1820.o 

C_DEPS += \
./sensors/dht11.d \
./sensors/ds1820.d 


# Each subdirectory must supply rules for building sources it contributes
sensors/%.o: ../sensors/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -DARDUINO_UNO=1 -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


