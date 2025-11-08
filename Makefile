COMPILER_PREFIX ?= m68k-atari-mintelf
COMPILER ?= $(COMPILER_PREFIX)-gcc
AR ?= $(COMPILER_PREFIX)-ar
RANLIB ?= $(COMPILER_PREFIX)-ranlib

MAKEFLAGS += -j $(shell nproc)

COMMON_CFLAGS := -std=c23 -m68040 -Os -Wall -Werror -ffreestanding -fno-builtin -fno-stack-protector \
                 -fno-pic 


COMMON_LDFLAGS := -nostdlib -Wl,--gc-sections 

CFLAGS ?= -Os -Wall -Werror
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

INCFLAGS := -nostdinc -isystem $(LIBC_INCLUDE_DIR) -isystem $(LIBC_INCLUDE_SRC_DIR)

LIBC_EXCLUDE := 
LIBC_C_SOURCES := $(filter-out $(addprefix $(LIBC_SRC_DIR)/,$(LIBC_EXCLUDE)),$(call rwildcard,$(LIBC_SRC_DIR)/,*.c))
LIBC_ASM_SOURCES := $(filter-out $(LIBC_SRC_DIR)/crt0.S,$(call rwildcard,$(LIBC_SRC_DIR)/,*.S))
LIBC_OBJECTS := \
  $(patsubst $(LIBC_SRC_DIR)/%.c,$(LIBC_OBJS_DIR)/%.o,$(LIBC_C_SOURCES)) \
  $(patsubst $(LIBC_SRC_DIR)/%.S,$(LIBC_OBJS_DIR)/%.o,$(LIBC_ASM_SOURCES))

LIBC_HEADERS := $(call rwildcard,$(LIBC_INCLUDE_SRC_DIR)/,*.h)
LIBC_INSTALLED_HEADERS := $(patsubst $(LIBC_INCLUDE_SRC_DIR)/%,$(LIBC_INCLUDE_DIR)/%,$(LIBC_HEADERS))

BOX_SOURCES := $(wildcard $(BOX_SRC_DIR)/*.c)
OUT_BOX_DIR := out/box
BOX_PROGRAMS := $(patsubst $(BOX_SRC_DIR)/%.c,$(OUT_BOX_DIR)/%,$(BOX_SOURCES))

TESTS_SRC_DIR := src/tests
TESTS_SOURCES := $(wildcard $(TESTS_SRC_DIR)/*.c)
OUT_TESTS_DIR := out/tests
TEST_PROGRAMS := $(patsubst $(TESTS_SRC_DIR)/%.c,$(OUT_TESTS_DIR)/%,$(TESTS_SOURCES))

INCLUDES := -I"$(LIBC_INCLUDE_DIR)" -I"$(LIBC_INCLUDE_SRC_DIR)"

.PHONY: all libc box tests clean

all: libc box tests

libc: $(LIBC_INSTALLED_HEADERS) $(LIBC_LIBRARY) $(LIBC_CRT0)

box: $(BOX_PROGRAMS)

tests: $(TEST_PROGRAMS)

$(LIBC_LIBRARY): $(LIBC_OBJECTS) | $(LIBC_BUILD_DIR)
	$(AR) rcs $@ $^
	$(RANLIB) $@

$(LIBC_CRT0): $(LIBC_SRC_DIR)/crt0.S | $(LIBC_OBJS_DIR)
	$(COMPILER) $(CPUFLAGS) $(CPPFLAGS) $(INCFLAGS) $(COMMON_CFLAGS) -c $< -o $@

$(LIBC_OBJS_DIR)/%.o: $(LIBC_SRC_DIR)/%.c | $(LIBC_OBJS_DIR)
	mkdir -p $(dir $@)
	$(COMPILER) $(CPUFLAGS) $(CPPFLAGS) $(INCFLAGS) $(COMMON_CFLAGS) -c $< -o $@

$(LIBC_OBJS_DIR)/%.o: $(LIBC_SRC_DIR)/%.S | $(LIBC_OBJS_DIR)
	mkdir -p $(dir $@)
	$(COMPILER) $(CPUFLAGS) $(CPPFLAGS) $(INCFLAGS) $(COMMON_CFLAGS) -c $< -o $@

$(LIBC_INCLUDE_DIR)/%.h: $(LIBC_INCLUDE_SRC_DIR)/%.h | $(LIBC_INCLUDE_DIR)
	mkdir -p $(dir $@)
	cp $< $@

$(OUT_BOX_DIR)/%.o: $(BOX_SRC_DIR)/%.c | $(OUT_BOX_DIR)
	$(COMPILER) $(CPUFLAGS) $(CPPFLAGS) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OUT_BOX_DIR)/%: $(LIBC_CRT0) $(OUT_BOX_DIR)/%.o $(LIBC_LIBRARY) | $(OUT_BOX_DIR)
	$(COMPILER) $(CPUFLAGS) $(COMMON_LDFLAGS) \
	    "$(LIBC_CRT0)" $(OUT_BOX_DIR)/$*.o \
	    -Wl,--start-group -L"$(LIBC)" -lcbox -lgcc -Wl,--end-group \
	    -Wl,-Map,$@.map \
	    -o $@

$(OUT_TESTS_DIR)/%.o: $(TESTS_SRC_DIR)/%.c | $(OUT_TESTS_DIR)
	$(COMPILER) $(CPUFLAGS) $(CPPFLAGS) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OUT_TESTS_DIR)/%: $(LIBC_CRT0) $(OUT_TESTS_DIR)/%.o $(LIBC_LIBRARY) | $(OUT_TESTS_DIR)
	$(COMPILER) $(CPUFLAGS) $(COMMON_LDFLAGS) \
	    "$(LIBC_CRT0)" $(OUT_TESTS_DIR)/$*.o \
	    -Wl,--start-group -L"$(LIBC)" -lcbox -lgcc -Wl,--end-group \
	    -Wl,-Map,$@.map \
	    -o $@

$(LIBC_BUILD_DIR) $(LIBC_OBJS_DIR) $(LIBC_INCLUDE_DIR) $(OUT_BOX_DIR) $(OUT_TESTS_DIR):
	mkdir -p $@

clean:
	rm -rf $(OUT_BOX_DIR) $(OUT_TESTS_DIR) $(LIBC_BUILD_DIR)
