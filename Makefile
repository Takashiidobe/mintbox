COMPILER ?= m68k-atari-mint-gcc
AR ?= m68k-atari-mint-ar
RANLIB ?= m68k-atari-mint-ranlib

CFLAGS ?= -Os
CPPFLAGS ?=

LIBC_SRC_DIR := src/libc
LIBC_INCLUDE_SRC_DIR := $(LIBC_SRC_DIR)/include
BOX_SRC_DIR := src/box

rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

LIBC ?= $(abspath build)
LIBC_BUILD_DIR := $(LIBC)
LIBC_OBJS_DIR := $(LIBC_BUILD_DIR)/objs
LIBC_INCLUDE_DIR := $(LIBC_BUILD_DIR)/include
LIBC_LIBRARY := $(LIBC_BUILD_DIR)/libcbox.a
LIBC_CRT0 := $(LIBC_OBJS_DIR)/crt0.o

LIBC_EXCLUDE := 
LIBC_C_SOURCES := $(filter-out $(addprefix $(LIBC_SRC_DIR)/,$(LIBC_EXCLUDE)),$(call rwildcard,$(LIBC_SRC_DIR)/,*.c))
LIBC_ASM_SOURCES := $(filter-out $(LIBC_SRC_DIR)/crt0.S,$(call rwildcard,$(LIBC_SRC_DIR)/,*.S))
LIBC_OBJECTS := \
  $(patsubst $(LIBC_SRC_DIR)/%.c,$(LIBC_OBJS_DIR)/%.o,$(LIBC_C_SOURCES)) \
  $(patsubst $(LIBC_SRC_DIR)/%.S,$(LIBC_OBJS_DIR)/%.o,$(LIBC_ASM_SOURCES))

LIBC_HEADERS := $(wildcard $(LIBC_INCLUDE_SRC_DIR)/*.h)
LIBC_INSTALLED_HEADERS := $(patsubst $(LIBC_INCLUDE_SRC_DIR)/%,$(LIBC_INCLUDE_DIR)/%,$(LIBC_HEADERS))

BOX_SOURCES := $(wildcard $(BOX_SRC_DIR)/*.c)
OUT_BOX_DIR := out/box
BOX_PROGRAMS := $(patsubst $(BOX_SRC_DIR)/%.c,$(OUT_BOX_DIR)/%,$(BOX_SOURCES))

INCLUDES := -I"$(LIBC_INCLUDE_DIR)"

.PHONY: all libc box clean

all: libc box

libc: $(LIBC_INSTALLED_HEADERS) $(LIBC_LIBRARY) $(LIBC_CRT0)

box: $(BOX_PROGRAMS)

$(LIBC_LIBRARY): $(LIBC_OBJECTS) | $(LIBC_BUILD_DIR)
	$(AR) rcs $@ $^
	$(RANLIB) $@

$(LIBC_CRT0): $(LIBC_SRC_DIR)/crt0.S | $(LIBC_OBJS_DIR)
	$(COMPILER) $(CPPFLAGS) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(LIBC_OBJS_DIR)/%.o: $(LIBC_SRC_DIR)/%.c | $(LIBC_OBJS_DIR)
	mkdir -p $(dir $@)
	$(COMPILER) $(CPPFLAGS) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(LIBC_OBJS_DIR)/%.o: $(LIBC_SRC_DIR)/%.S | $(LIBC_OBJS_DIR)
	mkdir -p $(dir $@)
	$(COMPILER) $(CPPFLAGS) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(LIBC_INCLUDE_DIR)/%.h: $(LIBC_INCLUDE_SRC_DIR)/%.h | $(LIBC_INCLUDE_DIR)
	cp $< $@

$(OUT_BOX_DIR)/%: $(BOX_SRC_DIR)/%.c $(LIBC_LIBRARY) $(LIBC_CRT0) | $(OUT_BOX_DIR)
	$(COMPILER) -nostdlib $(CPPFLAGS) $(INCLUDES) -I"$(LIBC)" "$(LIBC_CRT0)" $< \
		-L"$(LIBC)" -lgcc -lcbox -lgcc $(CFLAGS) -o $@

$(LIBC_BUILD_DIR) $(LIBC_OBJS_DIR) $(LIBC_INCLUDE_DIR) $(OUT_BOX_DIR):
	mkdir -p $@

clean:
	rm -rf $(OUT_BOX_DIR) $(LIBC_BUILD_DIR)
