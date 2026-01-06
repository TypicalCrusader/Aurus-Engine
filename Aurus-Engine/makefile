# SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
#
# SPDX-License-Identifier: GPL-2.0-only

TARGET_EXEC := AurusEngine
Aurus:
	echo "[CC]  BUILDING ENGINE"
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
$(BUILD_DIR)/%.c.o: %.c
	echo "[CC]	$@"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@