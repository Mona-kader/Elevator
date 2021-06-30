################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/timer/subdir.mk
-include HAL/keypad/subdir.mk
-include APP/subdir.mk
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
elevator_pro3.lss \

FLASH_IMAGE += \
elevator_pro3.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: elevator_pro3.elf secondary-outputs

# Tool invocations
elevator_pro3.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,elevator_pro3.map -mmcu=atmega16 -o "elevator_pro3.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

elevator_pro3.lss: elevator_pro3.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S elevator_pro3.elf  >"elevator_pro3.lss"
	@echo 'Finished building: $@'
	@echo ' '

elevator_pro3.hex: elevator_pro3.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex elevator_pro3.elf  "elevator_pro3.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: elevator_pro3.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 elevator_pro3.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: elevator_pro3.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm16 -cusbasp -Uflash:w:elevator_pro3.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) elevator_pro3.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
