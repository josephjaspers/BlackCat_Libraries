################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CU_SRCS += \
../NN_Core/Deprecated/Copy\ of\ MNIST_alternatetest.cu 

OBJS += \
./NN_Core/Deprecated/Copy\ of\ MNIST_alternatetest.o 

CU_DEPS += \
./NN_Core/Deprecated/Copy\ of\ MNIST_alternatetest.d 


# Each subdirectory must supply rules for building sources it contributes
NN_Core/Deprecated/Copy\ of\ MNIST_alternatetest.o: ../NN_Core/Deprecated/Copy\ of\ MNIST_alternatetest.cu
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-9.1/bin/nvcc -I/home/joseph/BlackCat_Libraries/BlackCat_Tensors3.3 -I/home/joseph/BlackCat_Libraries/BlackCat_Tensors3.2/BlackCat_Tensors_Functions/Functions -include /home/joseph/BlackCat_Libraries/BlackCat_Tensors3.3/BlackCat_Tensors.h -O3 -Xcompiler -ftemplate-depth=10000 -gencode arch=compute_52,code=sm_52  -odir "NN_Core/Deprecated" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-9.1/bin/nvcc -I/home/joseph/BlackCat_Libraries/BlackCat_Tensors3.3 -I/home/joseph/BlackCat_Libraries/BlackCat_Tensors3.2/BlackCat_Tensors_Functions/Functions -include /home/joseph/BlackCat_Libraries/BlackCat_Tensors3.3/BlackCat_Tensors.h -O3 -Xcompiler -ftemplate-depth=10000 --compile --relocatable-device-code=true -gencode arch=compute_52,code=compute_52 -gencode arch=compute_52,code=sm_52  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

