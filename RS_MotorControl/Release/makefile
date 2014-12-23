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
RS_MotorControl.lss \

FLASH_IMAGE += \
RS_MotorControl.hex \

EEPROM_IMAGE += \
RS_MotorControl.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: RS_MotorControl.elf secondary-outputs

# Tool invocations
RS_MotorControl.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,RS_MotorControl.map -mmcu=atmega8 -o "RS_MotorControl.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

RS_MotorControl.lss: RS_MotorControl.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S RS_MotorControl.elf  >"RS_MotorControl.lss"
	@echo 'Finished building: $@'
	@echo ' '

RS_MotorControl.hex: RS_MotorControl.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex RS_MotorControl.elf  "RS_MotorControl.hex"
	@echo 'Finished building: $@'
	@echo ' '

RS_MotorControl.eep: RS_MotorControl.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex RS_MotorControl.elf  "RS_MotorControl.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: RS_MotorControl.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 RS_MotorControl.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) RS_MotorControl.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
