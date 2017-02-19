################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app_timer.c \
../gpio_int.c \
../main.c \
../system.c \
../usart.c 

OBJS += \
./app_timer.o \
./gpio_int.o \
./main.o \
./system.o \
./usart.o 

C_DEPS += \
./app_timer.d \
./gpio_int.d \
./main.d \
./system.d \
./usart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"G:/E_ELEKTRONIKA/WinAVR/eclipse_kopia/WORKSPACE/AVR_eclipse/ATmega16TestBoard_pompa_cyrkulacyjna/headers" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


