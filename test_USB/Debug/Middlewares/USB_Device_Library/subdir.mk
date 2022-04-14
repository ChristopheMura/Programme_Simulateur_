################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/usbd_customhid.c \
/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c 

OBJS += \
./Middlewares/USB_Device_Library/usbd_core.o \
./Middlewares/USB_Device_Library/usbd_ctlreq.o \
./Middlewares/USB_Device_Library/usbd_customhid.o \
./Middlewares/USB_Device_Library/usbd_ioreq.o 

C_DEPS += \
./Middlewares/USB_Device_Library/usbd_core.d \
./Middlewares/USB_Device_Library/usbd_ctlreq.d \
./Middlewares/USB_Device_Library/usbd_customhid.d \
./Middlewares/USB_Device_Library/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/USB_Device_Library/usbd_core.o: /Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c Middlewares/USB_Device_Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L073xx -c -I../Core/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/STM32L0xx_HAL_Driver/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/USB_Device_Library/usbd_ctlreq.o: /Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c Middlewares/USB_Device_Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L073xx -c -I../Core/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/STM32L0xx_HAL_Driver/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/USB_Device_Library/usbd_customhid.o: /Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/usbd_customhid.c Middlewares/USB_Device_Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L073xx -c -I../Core/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/STM32L0xx_HAL_Driver/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/USB_Device_Library/usbd_ioreq.o: /Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c Middlewares/USB_Device_Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L073xx -c -I../Core/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/STM32L0xx_HAL_Driver/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I/Users/christophemura/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.1/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-USB_Device_Library

clean-Middlewares-2f-USB_Device_Library:
	-$(RM) ./Middlewares/USB_Device_Library/usbd_core.d ./Middlewares/USB_Device_Library/usbd_core.o ./Middlewares/USB_Device_Library/usbd_ctlreq.d ./Middlewares/USB_Device_Library/usbd_ctlreq.o ./Middlewares/USB_Device_Library/usbd_customhid.d ./Middlewares/USB_Device_Library/usbd_customhid.o ./Middlewares/USB_Device_Library/usbd_ioreq.d ./Middlewares/USB_Device_Library/usbd_ioreq.o

.PHONY: clean-Middlewares-2f-USB_Device_Library

