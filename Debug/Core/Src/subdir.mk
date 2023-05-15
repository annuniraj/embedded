################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Interrupt_Services.c \
../Core/Src/Save_Data.c \
../Core/Src/TCP_IP.c \
../Core/Src/dhcp.c \
../Core/Src/event.c \
../Core/Src/main.c \
../Core/Src/ring.c \
../Core/Src/socket.c \
../Core/Src/state.c \
../Core/Src/state_Handler.c \
../Core/Src/stm32f3xx_hal_msp.c \
../Core/Src/stm32f3xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f3xx.c \
../Core/Src/w5500.c \
../Core/Src/wizchip_conf.c 

OBJS += \
./Core/Src/Interrupt_Services.o \
./Core/Src/Save_Data.o \
./Core/Src/TCP_IP.o \
./Core/Src/dhcp.o \
./Core/Src/event.o \
./Core/Src/main.o \
./Core/Src/ring.o \
./Core/Src/socket.o \
./Core/Src/state.o \
./Core/Src/state_Handler.o \
./Core/Src/stm32f3xx_hal_msp.o \
./Core/Src/stm32f3xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f3xx.o \
./Core/Src/w5500.o \
./Core/Src/wizchip_conf.o 

C_DEPS += \
./Core/Src/Interrupt_Services.d \
./Core/Src/Save_Data.d \
./Core/Src/TCP_IP.d \
./Core/Src/dhcp.d \
./Core/Src/event.d \
./Core/Src/main.d \
./Core/Src/ring.d \
./Core/Src/socket.d \
./Core/Src/state.d \
./Core/Src/state_Handler.d \
./Core/Src/stm32f3xx_hal_msp.d \
./Core/Src/stm32f3xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f3xx.d \
./Core/Src/w5500.d \
./Core/Src/wizchip_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F301x8 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Interrupt_Services.cyclo ./Core/Src/Interrupt_Services.d ./Core/Src/Interrupt_Services.o ./Core/Src/Interrupt_Services.su ./Core/Src/Save_Data.cyclo ./Core/Src/Save_Data.d ./Core/Src/Save_Data.o ./Core/Src/Save_Data.su ./Core/Src/TCP_IP.cyclo ./Core/Src/TCP_IP.d ./Core/Src/TCP_IP.o ./Core/Src/TCP_IP.su ./Core/Src/dhcp.cyclo ./Core/Src/dhcp.d ./Core/Src/dhcp.o ./Core/Src/dhcp.su ./Core/Src/event.cyclo ./Core/Src/event.d ./Core/Src/event.o ./Core/Src/event.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/ring.cyclo ./Core/Src/ring.d ./Core/Src/ring.o ./Core/Src/ring.su ./Core/Src/socket.cyclo ./Core/Src/socket.d ./Core/Src/socket.o ./Core/Src/socket.su ./Core/Src/state.cyclo ./Core/Src/state.d ./Core/Src/state.o ./Core/Src/state.su ./Core/Src/state_Handler.cyclo ./Core/Src/state_Handler.d ./Core/Src/state_Handler.o ./Core/Src/state_Handler.su ./Core/Src/stm32f3xx_hal_msp.cyclo ./Core/Src/stm32f3xx_hal_msp.d ./Core/Src/stm32f3xx_hal_msp.o ./Core/Src/stm32f3xx_hal_msp.su ./Core/Src/stm32f3xx_it.cyclo ./Core/Src/stm32f3xx_it.d ./Core/Src/stm32f3xx_it.o ./Core/Src/stm32f3xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f3xx.cyclo ./Core/Src/system_stm32f3xx.d ./Core/Src/system_stm32f3xx.o ./Core/Src/system_stm32f3xx.su ./Core/Src/w5500.cyclo ./Core/Src/w5500.d ./Core/Src/w5500.o ./Core/Src/w5500.su ./Core/Src/wizchip_conf.cyclo ./Core/Src/wizchip_conf.d ./Core/Src/wizchip_conf.o ./Core/Src/wizchip_conf.su

.PHONY: clean-Core-2f-Src

