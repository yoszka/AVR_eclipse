################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include system/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
RF_ATmega8_Transmitter.lss \

FLASH_IMAGE += \
RF_ATmega8_Transmitter.hex \

EEPROM_IMAGE += \
RF_ATmega8_Transmitter.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: RF_ATmega8_Transmitter.elf secondary-outputs

# Tool invocations
RF_ATmega8_Transmitter.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,RF_ATmega8_Transmitter.map -mmcu=atmega8 -o "RF_ATmega8_Transmitter.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

RF_ATmega8_Transmitter.lss: RF_ATmega8_Transmitter.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S RF_ATmega8_Transmitter.elf  >"RF_ATmega8_Transmitter.lss"
	@echo 'Finished building: $@'
	@echo ' '

RF_ATmega8_Transmitter.hex: RF_ATmega8_Transmitter.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex RF_ATmega8_Transmitter.elf  "RF_ATmega8_Transmitter.hex"
	@echo 'Finished building: $@'
	@echo ' '

RF_ATmega8_Transmitter.eep: RF_ATmega8_Transmitter.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex RF_ATmega8_Transmitter.elf  "RF_ATmega8_Transmitter.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: RF_ATmega8_Transmitter.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 RF_ATmega8_Transmitter.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) RF_ATmega8_Transmitter.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
