# SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
#
# SPDX-License-Identifier: LGPL-2.1-only

TARGET_EXEC := libBINion
SRCS := $(shell find $(SRC_DIRS) -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
.PHONY: clean all 

all:
	echo "[CC]  BUILDING libBINion"
$(BUILD_DIR)/%.c.o: %.c
	echo "[CC]	$@"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(EXTRA_OS_FLAGS_LIB) -c $< -o $@

clean:
	rm -r $(BUILD_DIR)
-include $(DEPS)