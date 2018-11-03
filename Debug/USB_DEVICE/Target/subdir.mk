################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_DEVICE/Target/usbd_conf.c 

OBJS += \
./USB_DEVICE/Target/usbd_conf.o 

C_DEPS += \
./USB_DEVICE/Target/usbd_conf.d 


# Each subdirectory must supply rules for building sources it contributes
USB_DEVICE/Target/%.o: ../USB_DEVICE/Target/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/USB_DEVICE/App" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/USB_DEVICE/Target" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/Core/Inc" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


