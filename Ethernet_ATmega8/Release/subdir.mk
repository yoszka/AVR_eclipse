################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AtMegaEth.cpp \
../ENC28J60.cpp \
../aux_globals.cpp \
../hw_enc28j60.cpp \
../ip_arp_udp_tcp.cpp 

OBJS += \
./AtMegaEth.o \
./ENC28J60.o \
./aux_globals.o \
./hw_enc28j60.o \
./ip_arp_udp_tcp.o 

CPP_DEPS += \
./AtMegaEth.d \
./ENC28J60.d \
./aux_globals.d \
./hw_enc28j60.d \
./ip_arp_udp_tcp.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega8 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


