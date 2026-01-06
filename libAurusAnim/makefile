# SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
#
# SPDX-License-Identifier: LGPL-2.1-only

TARGET_EXEC := libAAM
.PHONY: clean all 

all:
	echo "[CC]  BUILDING libAAM"
$(BUILD_DIR)/%.c.o: %.c
	echo "[CC]	$@"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(EXTRA_OS_FLAGS_LIB) -c $< -o $@

clean:
	rm -r $(BUILD_DIR)
-include $(DEPS)