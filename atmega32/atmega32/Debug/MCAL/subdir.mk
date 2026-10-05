################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/DIO.c \
../MCAL/I2C.c \
../MCAL/SPI.c \
../MCAL/USART.c 

OBJS += \
./MCAL/DIO.o \
./MCAL/I2C.o \
./MCAL/SPI.o \
./MCAL/USART.o 

C_DEPS += \
./MCAL/DIO.d \
./MCAL/I2C.d \
./MCAL/SPI.d \
./MCAL/USART.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -IC:/Users/hamdy/Desktop/COTS_AVR/COTS/APP/test2 -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


