################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Atmega8testBoard_ADC.lss \

FLASH_IMAGE += \
Atmega8testBoard_ADC.hex \

EEPROM_IMAGE += \
Atmega8testBoard_ADC.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Atmega8testBoard_ADC.elf secondary-outputs

# Tool invocations
Atmega8testBoard_ADC.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Atmega8testBoard_ADC.map -mmcu=atmega8 -o "Atmega8testBoard_ADC.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Atmega8testBoard_ADC.lss: Atmega8testBoard_ADC.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Atmega8testBoard_ADC.elf  >"Atmega8testBoard_ADC.lss"
	@echo 'Finished building: $@'
	@echo ' '

Atmega8testBoard_ADC.hex: Atmega8testBoard_ADC.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Atmega8testBoard_ADC.elf  "Atmega8testBoard_ADC.hex"
	@echo 'Finished building: $@'
	@echo ' '

Atmega8testBoard_ADC.eep: Atmega8testBoard_ADC.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Atmega8testBoard_ADC.elf  "Atmega8testBoard_ADC.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Atmega8testBoard_ADC.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 Atmega8testBoard_ADC.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Atmega8testBoard_ADC.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
