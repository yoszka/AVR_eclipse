################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usart/usart.c 

OBJS += \
./usart/usart.o 

C_DEPS += \
./usart/usart.d 


# Each subdirectory must supply rules for building sources it contributes
usart/%.o: ../usart/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"G:/E_ELEKTRONIKA/WinAVR/eclipse_kopia/WORKSPACE/AVR_eclipse/Atmega8testBoard_I2C_master/usart" -I"G:/E_ELEKTRONIKA/WinAVR/eclipse_kopia/WORKSPACE/AVR_eclipse/Atmega8testBoard_I2C_master/headers" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


