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
Atmega8testBoard_SPI_master.lss \

FLASH_IMAGE += \
Atmega8testBoard_SPI_master.hex \

EEPROM_IMAGE += \
Atmega8testBoard_SPI_master.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Atmega8testBoard_SPI_master.elf secondary-outputs

# Tool invocations
Atmega8testBoard_SPI_master.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Atmega8testBoard_SPI_master.map -mmcu=atmega8 -o "Atmega8testBoard_SPI_master.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Atmega8testBoard_SPI_master.lss: Atmega8testBoard_SPI_master.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Atmega8testBoard_SPI_master.elf  >"Atmega8testBoard_SPI_master.lss"
	@echo 'Finished building: $@'
	@echo ' '

Atmega8testBoard_SPI_master.hex: Atmega8testBoard_SPI_master.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Atmega8testBoard_SPI_master.elf  "Atmega8testBoard_SPI_master.hex"
	@echo 'Finished building: $@'
	@echo ' '

Atmega8testBoard_SPI_master.eep: Atmega8testBoard_SPI_master.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Atmega8testBoard_SPI_master.elf  "Atmega8testBoard_SPI_master.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Atmega8testBoard_SPI_master.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 Atmega8testBoard_SPI_master.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Atmega8testBoard_SPI_master.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
