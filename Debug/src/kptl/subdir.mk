################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/kptl/kptl.c 

OBJS += \
./src/kptl/kptl.o 

C_DEPS += \
./src/kptl/kptl.d 


# Each subdirectory must supply rules for building sources it contributes
src/kptl/%.o: ../src/kptl/%.c src/kptl/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32emac -mabi=ilp32e -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fno-move-loop-invariants -Wall -Wextra  -g3 -DFDV32S302 -I"../include" -I"E:\work\project\fdv32s302_bl\src\config" -I"E:\work\project\fdv32s302_bl\src\kptl" -I"E:\work\project\fdv32s302_bl\src\mcuboot" -I"../FDV32S302/drivers" -I"../FDV32S302/include" -I"../FDV32S302/env" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


