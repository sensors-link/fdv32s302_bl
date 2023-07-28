################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FDV32S302/drivers/anac.c \
../FDV32S302/drivers/efc.c \
../FDV32S302/drivers/iom.c \
../FDV32S302/drivers/lptimer.c \
../FDV32S302/drivers/spi.c \
../FDV32S302/drivers/sysc.c \
../FDV32S302/drivers/timer.c \
../FDV32S302/drivers/twc.c \
../FDV32S302/drivers/uart.c \
../FDV32S302/drivers/wdt.c 

OBJS += \
./FDV32S302/drivers/anac.o \
./FDV32S302/drivers/efc.o \
./FDV32S302/drivers/iom.o \
./FDV32S302/drivers/lptimer.o \
./FDV32S302/drivers/spi.o \
./FDV32S302/drivers/sysc.o \
./FDV32S302/drivers/timer.o \
./FDV32S302/drivers/twc.o \
./FDV32S302/drivers/uart.o \
./FDV32S302/drivers/wdt.o 

C_DEPS += \
./FDV32S302/drivers/anac.d \
./FDV32S302/drivers/efc.d \
./FDV32S302/drivers/iom.d \
./FDV32S302/drivers/lptimer.d \
./FDV32S302/drivers/spi.d \
./FDV32S302/drivers/sysc.d \
./FDV32S302/drivers/timer.d \
./FDV32S302/drivers/twc.d \
./FDV32S302/drivers/uart.d \
./FDV32S302/drivers/wdt.d 


# Each subdirectory must supply rules for building sources it contributes
FDV32S302/drivers/%.o: ../FDV32S302/drivers/%.c FDV32S302/drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32emac -mabi=ilp32e -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fno-move-loop-invariants -Wall -Wextra  -g3 -DFDV32S302 -I"../include" -I"E:\work\project\fdv32s302_bl\src\config" -I"E:\work\project\fdv32s302_bl\src\kptl" -I"E:\work\project\fdv32s302_bl\src\mcuboot" -I"../FDV32S302/drivers" -I"../FDV32S302/include" -I"../FDV32S302/env" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


