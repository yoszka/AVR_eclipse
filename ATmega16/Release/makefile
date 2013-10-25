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
ATmega16.lss \

FLASH_IMAGE += \
ATmega16.hex \

EEPROM_IMAGE += \
ATmega16.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ATmega16.elf secondary-outputs

# Tool invocations
ATmega16.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ATmega16.map -mmcu=atmega16 -o "ATmega16.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ATmega16.lss: ATmega16.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ATmega16.elf  >"ATmega16.lss"
	@echo 'Finished building: $@'
	@echo ' '

ATmega16.hex: ATmega16.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex ATmega16.elf  "ATmega16.hex"
	@echo 'Finished building: $@'
	@echo ' '

ATmega16.eep: ATmega16.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ATmega16.elf  "ATmega16.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ATmega16.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 ATmega16.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) ATmega16.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
