# SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
#
# SPDX-License-Identifier: GPL-2.0-only

.PHONY: clean all data Aurus BINion AAM BINion-Maker ATX-Parser AAM-Maker clean-data

# Include subproject makefiles
include ATX-Parser/makefile
include AAM-Maker/makefile
include BINion-Parser/makefile
include LibAurusAnim/makefile
include LibBINion/makefile
include Aurus-Engine/makefile

define EXTRA_COMPILE_FLAGS 
endef
define EXTRA_OS_FLAGS_GUI_TERM
endef

# Force Make to use bash, not sh or cmd
SHELL := /bin/bash

# Ensure we fail on any syntax weirdness
$(info Makefile loaded, OS=$(OS), SHELL=$(SHELL))

ifeq ($(OS),Windows_NT) 
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		$(error Aurus Engine does not support 32 Bit, please build on 64 bit aware target)
	endif		
	EXTRA_COMPILE_FLAGS := -mwin32
	EXTRA_OS_FLAGS_GUI_TERM := -mwindows -mwin32 
	EXTRA_OS_FLAGS_LIB := -mdll
	COMPILER_DISABLE_ENABLE_CPU_FEATURES := -m64 -mno-mavx512vbmi2 -mno-mavx512bf16 -mno-mavx512fp16 -mno-mavx512f -mno-mavx512cd -mno-mavx512vl -mno-mavx512bw -mno-mavx512dq -mno-mavx512ifma -mno-mavx512vbmi
	endif
else
	CPU_Arch := $(shell uname -m)
	ifeq ($(CPU_Arch),native)
		CPU_Arch := $(shell $(CC) -dM -E - </dev/null | grep -q "__LP64__" && echo 64 || echo 32)
		ifeq ($(CPU_Arch),32)
			$(error Aurus Engine does not support 32 Bit, please build on 64 bit aware target)			
		endif
		ifeq ($(CPU_Arch).64) #imply we are on x64 but something made it not get arch
			COMPILER_DISABLE_ENABLE_CPU_FEATURES :=  -m64 \
    			-mno-avx512f -mno-avx512cd -mno-avx512bw -mno-avx512dq -mno-avx512ifma -mno-avx512vbmi -mno-avx512vl \
    			-mno-avx512vbmi2 -mno-avx512bf16 -mno-avx512fp16
		endif
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
		COMPILER_DISABLE_ENABLE_CPU_FEATURES :=  -m64 \
			-mno-avx512f -mno-avx512cd -mno-avx512bw -mno-avx512dq -mno-avx512ifma -mno-avx512vbmi -mno-avx512vl \
			-mno-avx512vbmi2 -mno-avx512bf16 -mno-avx512fp16
	endif
endif


.PHONY: all benis clean

CC := gcc

MK_PATH   := $(abspath $(lastword $(MAKEFILE_LIST)))
MK_DIR    := $(dir $(MK_PATH))

BUILD_DIR := $(MK_DIR)build

SRC_DIRS := \
    $(MK_DIR)libBINion/src \
    $(MK_DIR)libAurusAnim/src \
    $(MK_DIR)Aurus-Engine/src \
    $(MK_DIR)Aurus-Engine/data/bakeddata

C_STD := gnu23

# Find all .c and .s files
SRCS := $(shell find $(SRC_DIRS) -type f \( -name '*.c' -o -name '*.s' \))

# Objects
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(filter %.c,$(SRCS)))
OBJS += $(patsubst %.s,$(BUILD_DIR)/%.o,$(filter %.s,$(SRCS)))

# Dependencies
DEPS := $(OBJS:.o=.d)

INC_DIRS := \
    $(MK_DIR)libBINion/include \
    $(MK_DIR)libAurusAnim/include \
    $(MK_DIR)Aurus-Engine/include

INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS := \
    $(INC_FLAGS) \
    -std=$(C_STD) \
    -MMD -MP \
    -O2 \
	$(COMPILER_DISABLE_ENABLE_CPU_FEATURES)
    # -Wall -Wextra -Werror  

all: data AAM BINion Aurus

data: clean-data BCH-init ATX-Parser AAM-Maker BINion-Maker

Aurus: $(OBJS)
	@echo "[LINK]  Aurus-Engine"
	$(CC) $(OBJS) -o Aurus-Engine $(LDFLAGS)

#Rule for c files
$(BUILD_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@echo "[CC]    $< → $@"
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for asm
$(BUILD_DIR)/%.o : %.s
	@mkdir -p $(dir $@)
	@echo "[AS]    $< → $@"
	$(CC) $(CFLAGS) -c $< -o $@

# Include generated dependency files
-include $(DEPS)

clean:
	rm -r $(BUILD_DIR)

clean-data:
	[ -d $(BUILD_DIR)/data ] && rm -rf $(BUILD_DIR)/data || true
	[ -d $(BUILD_DIR)/temp_data ] && rm -rf $(BUILD_DIR)/temp_data || true
	[ -d $(BUILD_DIR)/data_cache ] && rm -rf $(BUILD_DIR)/data_cache || true

-include $(DEPS)