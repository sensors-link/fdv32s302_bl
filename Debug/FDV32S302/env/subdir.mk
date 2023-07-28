################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FDV32S302/env/init.c \
../FDV32S302/env/system_phnx04.c 

S_UPPER_SRCS += \
../FDV32S302/env/entry.S \
../FDV32S302/env/start.S 

OBJS += \
./FDV32S302/env/entry.o \
./FDV32S302/env/init.o \
./FDV32S302/env/start.o \
./FDV32S302/env/system_phnx04.o 

S_UPPER_DEPS += \
./FDV32S302/env/entry.d \
./FDV32S302/env/start.d 

C_DEPS += \
./FDV32S302/env/init.d \
./FDV32S302/env/system_phnx04.d 


# Each subdirectory must supply rules for building sources it contributes
FDV32S302/env/%.o: ../FDV32S302/env/%.S FDV32S302/env/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv-none-embed-gcc -march=rv32emac -mabi=ilp32e -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fno-move-loop-invariants -Wall -Wextra  -g3 -x assembler-with-cpp -D_DEBUG -DFDV32S302 -I"../include" -I"../FDV32S302/drivers" -I"../FDV32S302/include" -I"../FDV32S302/env" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FDV32S302/env/%.o: ../FDV32S302/env/%.c FDV32S302/env/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32emac -mabi=ilp32e -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fno-move-loop-invariants -Wall -Wextra  -g3 -DFDV32S302 -I"../include" -I"E:\work\project\fdv32s302_bl\src\config" -I"E:\work\project\fdv32s302_bl\src\kptl" -I"E:\work\project\fdv32s302_bl\src\mcuboot" -I"../FDV32S302/drivers" -I"../FDV32S302/include" -I"../FDV32S302/env" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


