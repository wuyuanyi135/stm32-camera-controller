################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/led_status.c \
../Core/Src/main.c \
../Core/Src/pt_util.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/task_monitor.c \
../Core/Src/usb_comm.c 

OBJS += \
./Core/Src/led_status.o \
./Core/Src/main.o \
./Core/Src/pt_util.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/task_monitor.o \
./Core/Src/usb_comm.o 

C_DEPS += \
./Core/Src/led_status.d \
./Core/Src/main.d \
./Core/Src/pt_util.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/task_monitor.d \
./Core/Src/usb_comm.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/USB_DEVICE/App" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/USB_DEVICE/Target" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/Core/Inc" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/wuyua/Desktop/stm32-camera-controller/stm32-camera-controller/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


