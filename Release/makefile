################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ..\makefile.init

RM := del 

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries\PubSubClient\src\subdir.mk
-include core\core\subdir.mk
-include WirelessPart\ESPLineDancerDebug\subdir.mk
-include WirelessPart\ESPLineDancer\subdir.mk
-include StepMotor\testStepperLibrary\subdir.mk
-include StepMotor\testStepMotorBoardJonas\subdir.mk
-include StepMotor\testStepMotorBoard\subdir.mk
-include StepMotor\AccelStepperJonas\subdir.mk
-include AccelStepper\examples\Random\subdir.mk
-include AccelStepper\examples\Quickstop\subdir.mk
-include AccelStepper\examples\ProportionalControl\subdir.mk
-include AccelStepper\examples\Overshoot\subdir.mk
-include AccelStepper\examples\MultipleSteppers\subdir.mk
-include AccelStepper\examples\MultiStepper\subdir.mk
-include AccelStepper\examples\MotorShield\subdir.mk
-include AccelStepper\examples\DualMotorShield\subdir.mk
-include AccelStepper\examples\ConstantSpeed\subdir.mk
-include AccelStepper\examples\Bounce\subdir.mk
-include AccelStepper\examples\Blocking\subdir.mk
-include AccelStepper\examples\AFMotor_MultiStepper\subdir.mk
-include AccelStepper\examples\AFMotor_ConstantSpeed\subdir.mk
-include AccelStepper\subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ..\makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
E:\SloeberWorkspace\DrawingArm\Release\arduino.ar \

ELF += \
DrawingArm.elf \

HEX += \
DrawingArm.hex \


# All Target
all: DrawingArm

# Tool invocations
DrawingArm: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-size" -A "E:/SloeberWorkspace/DrawingArm/Release/DrawingArm.elf"
	@echo 'Finished building target: $@'
	@echo ' '

E:\SloeberWorkspace\DrawingArm\Release\arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs    E:/SloeberWorkspace/DrawingArm/Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

DrawingArm.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -Wall -Wextra -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p -o "E:\SloeberWorkspace\DrawingArm/Release/DrawingArm.elf"   $(LINK_OBJ)   E:/SloeberWorkspace/DrawingArm/Release/arduino.ar  "-LE:\SloeberWorkspace\DrawingArm/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

DrawingArm.hex: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ..\makefile.targets
