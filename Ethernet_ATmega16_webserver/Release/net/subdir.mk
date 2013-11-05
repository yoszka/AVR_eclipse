################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../net/enc28j60.c \
../net/ip_arp_udp_tcp.c 

OBJS += \
./net/enc28j60.o \
./net/ip_arp_udp_tcp.o 

C_DEPS += \
./net/enc28j60.d \
./net/ip_arp_udp_tcp.d 


# Each subdirectory must supply rules for building sources it contributes
net/%.o: ../net/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


