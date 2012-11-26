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
Krok.lss \

FLASH_IMAGE += \
Krok.hex \

EEPROM_IMAGE += \
Krok.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Krok.elf secondary-outputs

# Tool invocations
Krok.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Krok.map -mmcu=atmega8 -o "Krok.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Krok.lss: Krok.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Krok.elf  >"Krok.lss"
	@echo 'Finished building: $@'
	@echo ' '

Krok.hex: Krok.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Krok.elf  "Krok.hex"
	@echo 'Finished building: $@'
	@echo ' '

Krok.eep: Krok.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Krok.elf  "Krok.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Krok.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 Krok.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) Krok.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
