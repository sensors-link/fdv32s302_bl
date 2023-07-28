################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FDV32S302/stubs/_exit.c \
../FDV32S302/stubs/close.c \
../FDV32S302/stubs/fstat.c \
../FDV32S302/stubs/isatty.c \
../FDV32S302/stubs/lseek.c \
../FDV32S302/stubs/printf.c \
../FDV32S302/stubs/read.c \
../FDV32S302/stubs/sbrk.c \
../FDV32S302/stubs/write.c \
../FDV32S302/stubs/write_hex.c 

OBJS += \
./FDV32S302/stubs/_exit.o \
./FDV32S302/stubs/close.o \
./FDV32S302/stubs/fstat.o \
./FDV32S302/stubs/isatty.o \
./FDV32S302/stubs/lseek.o \
./FDV32S302/stubs/printf.o \
./FDV32S302/stubs/read.o \
./FDV32S302/stubs/sbrk.o \
./FDV32S302/stubs/write.o \
./FDV32S302/stubs/write_hex.o 

C_DEPS += \
./FDV32S302/stubs/_exit.d \
./FDV32S302/stubs/close.d \
./FDV32S302/stubs/fstat.d \
./FDV32S302/stubs/isatty.d \
./FDV32S302/stubs/lseek.d \
./FDV32S302/stubs/printf.d \
./FDV32S302/stubs/read.d \
./FDV32S302/stubs/sbrk.d \
./FDV32S302/stubs/write.d \
./FDV32S302/stubs/write_hex.d 


# Each subdirectory must supply rules for building sources it contributes
FDV32S302/stubs/%.o: ../FDV32S302/stubs/%.c FDV32S302/stubs/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32emac -mabi=ilp32e -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fno-move-loop-invariants -Wall -Wextra  -g3 -DFDV32S302 -I"../include" -I"E:\work\project\fdv32s302_bl\src\config" -I"E:\work\project\fdv32s302_bl\src\kptl" -I"E:\work\project\fdv32s302_bl\src\mcuboot" -I"../FDV32S302/drivers" -I"../FDV32S302/include" -I"../FDV32S302/env" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


