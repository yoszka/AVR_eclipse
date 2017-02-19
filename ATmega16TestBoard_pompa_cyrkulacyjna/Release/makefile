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
ATmega16TestBoard_pompa_cyrkulacyjna.lss \

FLASH_IMAGE += \
ATmega16TestBoard_pompa_cyrkulacyjna.hex \

EEPROM_IMAGE += \
ATmega16TestBoard_pompa_cyrkulacyjna.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ATmega16TestBoard_pompa_cyrkulacyjna.elf secondary-outputs

# Tool invocations
ATmega16TestBoard_pompa_cyrkulacyjna.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ATmega16TestBoard_pompa_cyrkulacyjna.map -mmcu=atmega16 -o "ATmega16TestBoard_pompa_cyrkulacyjna.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ATmega16TestBoard_pompa_cyrkulacyjna.lss: ATmega16TestBoard_pompa_cyrkulacyjna.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ATmega16TestBoard_pompa_cyrkulacyjna.elf  >"ATmega16TestBoard_pompa_cyrkulacyjna.lss"
	@echo 'Finished building: $@'
	@echo ' '

ATmega16TestBoard_pompa_cyrkulacyjna.hex: ATmega16TestBoard_pompa_cyrkulacyjna.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ATmega16TestBoard_pompa_cyrkulacyjna.elf  "ATmega16TestBoard_pompa_cyrkulacyjna.hex"
	@echo 'Finished building: $@'
	@echo ' '

ATmega16TestBoard_pompa_cyrkulacyjna.eep: ATmega16TestBoard_pompa_cyrkulacyjna.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ATmega16TestBoard_pompa_cyrkulacyjna.elf  "ATmega16TestBoard_pompa_cyrkulacyjna.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ATmega16TestBoard_pompa_cyrkulacyjna.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 ATmega16TestBoard_pompa_cyrkulacyjna.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ATmega16TestBoard_pompa_cyrkulacyjna.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
