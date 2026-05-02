################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/OSKernal.c \
../Src/led.c \
../Src/main.c \
../Src/mutex_queue.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/uart.c 

OBJS += \
./Src/OSKernal.o \
./Src/led.o \
./Src/main.o \
./Src/mutex_queue.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/uart.o 

C_DEPS += \
./Src/OSKernal.d \
./Src/led.d \
./Src/main.d \
./Src/mutex_queue.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"C:/Users/Netcom/Documents/PERSONAL_DOCUMENT/BARE_METAL_DOCUMENTS/chip_register/Include" -I"C:/Users/Netcom/Documents/PERSONAL_DOCUMENT/BARE_METAL_DOCUMENTS/chip_register/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/OSKernal.cyclo ./Src/OSKernal.d ./Src/OSKernal.o ./Src/OSKernal.su ./Src/led.cyclo ./Src/led.d ./Src/led.o ./Src/led.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/mutex_queue.cyclo ./Src/mutex_queue.d ./Src/mutex_queue.o ./Src/mutex_queue.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/uart.cyclo ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src

