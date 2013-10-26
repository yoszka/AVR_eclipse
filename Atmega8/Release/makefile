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
Atmega8.lss \

FLASH_IMAGE += \
Atmega8.hex \

EEPROM_IMAGE += \
Atmega8.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Atmega8.elf secondary-outputs

# Tool invocations
Atmega8.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Atmega8.map -mmcu=atmega8 -o "Atmega8.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Atmega8.lss: Atmega8.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Atmega8.elf  >"Atmega8.lss"
	@echo 'Finished building: $@'
	@echo ' '

Atmega8.hex: Atmega8.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Atmega8.elf  "Atmega8.hex"
	@echo 'Finished building: $@'
	@echo ' '

Atmega8.eep: Atmega8.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Atmega8.elf  "Atmega8.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Atmega8.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 Atmega8.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) Atmega8.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
