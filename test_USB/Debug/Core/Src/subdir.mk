################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/main.c \
../Core/Src/stm32l0xx_hal_msp.c \
../Core/Src/stm32l0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l0xx.c 

OBJS += \
./Core/Src/main.o \
./Core/Src/stm32l0xx_hal_msp.o \
./Core/Src/stm32l0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l0xx.o 

C_DEPS += \
./Core/Src/main.d \
./Core/Src/stm32l0xx_hal_msp.d \
./Core/Src/stm32l0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L073xx -c -I../Core/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/STM32L0xx_HAL_Driver/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/stm32l0xx_hal_msp.d ./Core/Src/stm32l0xx_hal_msp.o ./Core/Src/stm32l0xx_it.d ./Core/Src/stm32l0xx_it.o ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/system_stm32l0xx.d ./Core/Src/system_stm32l0xx.o

.PHONY: clean-Core-2f-Src

