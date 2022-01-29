################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /home/nanker/ti/ccs1110/ccs/tools/compiler/ti-cgt-pru_2.3.3

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./delay.obj" \
"./main.obj" \
"./spi8343.obj" \
"./transfer.obj" \
"../AM335x_PRU.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
pru0-spi.out \

EXE_OUTPUTS__QUOTED += \
"pru0-spi.out" \

BIN_OUTPUTS += \
pru0-spi.hex \

BIN_OUTPUTS__QUOTED += \
"pru0-spi.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "pru0-spi.out"

# Tool invocations
pru0-spi.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: PRU Linker'
	"/home/nanker/ti/ccs1110/ccs/tools/compiler/ti-cgt-pru_2.3.3/bin/clpru" -v3 -O4 --define=am3359 --define=pru0 -g --diag_warning=225 --diag_wrap=off --display_error_number --endian=little --hardware_mac=on -z -m"pru0-spi.map" --heap_size=0x100 --stack_size=0x100 -i"/home/nanker/ti/ccs1110/ccs/tools/compiler/ti-cgt-pru_2.3.3/lib" -i"/home/nanker/ti/ccs1110/ccs/tools/compiler/ti-cgt-pru_2.3.3/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="pru0-spi_linkInfo.xml" --rom_model -o "pru0-spi.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

pru0-spi.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: PRU Hex Utility'
	"/home/nanker/ti/ccs1110/ccs/tools/compiler/ti-cgt-pru_2.3.3/bin/hexpru" --diag_wrap=off -o "pru0-spi.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "delay.obj" "main.obj" "spi8343.obj" "transfer.obj" 
	-$(RM) "main.d" "spi8343.d" "transfer.d" 
	-$(RM) "delay.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-ssh root@10.10.10.2 "echo 'stop' > /sys/class/remoteproc/remoteproc1/state"
	-scp pru0-spi.out root@10.10.10.2:/lib/firmware/am335x-pru0-fw
	-ssh root@10.10.10.2 "echo 'start' > /sys/class/remoteproc/remoteproc1/state"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

