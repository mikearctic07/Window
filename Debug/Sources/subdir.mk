################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Clocks.c" \
"../Sources/GPIO.c" \
"../Sources/Interruptions.c" \
"../Sources/Movement.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/Clocks.c \
../Sources/GPIO.c \
../Sources/Interruptions.c \
../Sources/Movement.c \
../Sources/main.c \

OBJS_OS_FORMAT += \
./Sources/Clocks.o \
./Sources/GPIO.o \
./Sources/Interruptions.o \
./Sources/Movement.o \
./Sources/main.o \

C_DEPS_QUOTED += \
"./Sources/Clocks.d" \
"./Sources/GPIO.d" \
"./Sources/Interruptions.d" \
"./Sources/Movement.d" \
"./Sources/main.d" \

OBJS += \
./Sources/Clocks.o \
./Sources/GPIO.o \
./Sources/Interruptions.o \
./Sources/Movement.o \
./Sources/main.o \

OBJS_QUOTED += \
"./Sources/Clocks.o" \
"./Sources/GPIO.o" \
"./Sources/Interruptions.o" \
"./Sources/Movement.o" \
"./Sources/main.o" \

C_DEPS += \
./Sources/Clocks.d \
./Sources/GPIO.d \
./Sources/Interruptions.d \
./Sources/Movement.d \
./Sources/main.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/Clocks.o: ../Sources/Clocks.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/Clocks.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/Clocks.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/GPIO.o: ../Sources/GPIO.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/GPIO.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/GPIO.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Interruptions.o: ../Sources/Interruptions.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/Interruptions.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/Interruptions.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Movement.o: ../Sources/Movement.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/Movement.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/Movement.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/main.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


