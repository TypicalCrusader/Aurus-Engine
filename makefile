# SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
#
# SPDX-License-Identifier: GPL-2.0-only

.PHONY: clean all data Aurus BINion AAM BINion-Maker ATX-Parser AAM-Maker clean-data

define EXTRA_COMPILE_FLAGS
define EXTRA_OS_FLAGS_GUI_TERM
ifeq ($(OS),Windows_NT) 
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		$(error Aurus Engine does not support 32 Bit, please build on 64 bit aware target)
	endif		

	EXTRA_COMPILE_FLAGS := -mwin32
	EXTRA_OS_FLAGS_GUI_TERM := -mwindows -mwin32 
	EXTRA_OS_FLAGS_LIB := -mdll
	COMPILER_DISABLE_ENABLE_CPU_FEATURES := -m64 -mno-mavx512vbmi2 -mno-mavx512bf16 -mno-mavx512fp16 -mno-mavx -mno-mavx2 -mno-mavx512f -mno-mavx512cd -mno-mavx512vl -mno-mavx512bw -mno-mavx512dq -mno-mavx512ifma -mno-mavx512vbmi
else
	CPU_Arch := $(shell uname -m)
	ifeq ($(CPU_Arch),native)
		CPU_Arch := $(shell $(CC) -dM -E - </dev/null | grep -q "__LP64__" && echo 64 || echo 32)
		ifeq ($(CPU_Arch),32)
			$(error Aurus Engine does not support 32 Bit, please build on 64 bit aware target)			
		endif
		ifeq ($(CPU_Arch).64) #imply we are on x64 but something made it not get arch
			COMPILER_DISABLE_ENABLE_CPU_FEATURES := -m64 -mno-mavx512vbmi2 -mno-mavx512bf16 -mno-mavx512fp16 -mno-mavx -mno-mavx2 -mno-mavx512f -mno-mavx512cd -mno-mavx512vl -mno-mavx512bw -mno-mavx512dq -mno-mavx512ifma -mno-mavx512vbmi
		else 
			$(error Cant detect CPU architectre and its base architecture)
		endif
	endif		
	ifeq ($(CPU_Arch),x86)
		$(error Aurus Engine does not support 32 Bit, please build on 64 bit aware target)
	endif		
	ifeq ($(CPU_Arch),arm)
		$(error Aurus Engine does not support 32 Bit, please build on 64 bit aware target)
	endif		
	ifeq ($(CPU_Arch),parisc)
		$(error Aurus Engine does not support 32 Bit, please build on 64 bit aware target)
	endif	
	ifeq ($(CPU_Arch),ppc)
		$(error Aurus Engine does not support 32 Bit, please build on 64 bit aware target)
	endif	
	ifeq ($(CPU_Arch),ppc-le)
		$(error Aurus Engine does not support 32 Bit, please build on 64 bit aware target)
	endif	
	ifeq ($(CPU_Arch),arm-be)
		$(error Aurus Engine does not support 32 Bit, please build on 64 bit aware target)
	endif	
	ifeq ($(CPU_Arch),mips)
		$(error Aurus Engine does not support 32 Bit, please build on 64 bit aware target)
	endif		

	EXTRA_OS_FLAGS_LIB := -shared

	ifeq ($(CPU_Arch),x86_64)
		COMPILER_DISABLE_ENABLE_CPU_FEATURES := -m64 -mno-mavx512vbmi2 -mno-mavx512bf16 -mno-mavx512fp16 -mno-mavx -mno-mavx2 -mno-mavx512f -mno-mavx512cd -mno-mavx512vl -mno-mavx512bw -mno-mavx512dq -mno-mavx512ifma -mno-mavx512vbmi
	endif
endif

CC := gcc
MK_PATH   := $(abspath $(lastword $(MAKEFILE_LIST)))
MK_DIR    := $(dir $(MK_PATH))
BUILD_DIR := ./build
SRC_DIRS := /src
C_STD := gnu23
SRCS := $(shell find $(SRC_DIRS) -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
# These files will have .d instead of .o as the output.
# Treat warnings as errors, optimise code, optimise for latest CPU architecture, disable avx
CFLAGS := $(INC_FLAGS) -std=$(C_STD) -lBINion -AAM -MMD -MP -Wall -Wextra -Werror -Wno-unused-parameter -O2 $(COMPILER_DISABLE_ENABLE_CPU_FEATURES) $(EXTRA_COMPILE_FLAGS) $(EXTRA_OS_FLAGS_GUI_TERM_LIB)

all: data AAM BINion Aurus

data: clean-data BCH-init ATX-Parser AAM-Maker BINion-Maker

ATX-Parser:
	include ATX-Parser/makefile

AAM-Maker:
	include AAM-Parser/makefile

BINion-Maker:
	include BINion-Parser/makefile

AAM:
	include LibAurusAnim/makefile

BINion:
	include LibBINion/makefile

Aurus:
	include Aurus-Engine/makefile

clean:
	rm -r $(BUILD_DIR)

clean-data:
	rm -r $(BUILD_DIR)/data
	rm -r $(BUILD_DIR)/temp_data
	rm -r $(BUILD_DIR)/data_cache

-include $(DEPS)