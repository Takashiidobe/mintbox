SOURCES := $(wildcard src/*.c)
PROGRAMS := $(basename $(notdir $(SOURCES)))

COMPILER ?= m68k-atari-mint-gcc
LIBCMINI ?= $(abspath build)

OUT_MINTLIB := out/mintlib
OUT_LIBCMINI := out/libcmini

MINTLIB_BINS := $(addprefix $(OUT_MINTLIB)/,$(PROGRAMS))
LIBCMINI_BINS := $(addprefix $(OUT_LIBCMINI)/,$(PROGRAMS))

.PHONY: all mintlib libcmini clean

all: mintlib libcmini

mintlib: $(MINTLIB_BINS)

libcmini: $(LIBCMINI_BINS)

$(OUT_MINTLIB)/%: src/%.c | $(OUT_MINTLIB)
	$(COMPILER) $< -o $@

$(OUT_LIBCMINI)/%: src/%.c | $(OUT_LIBCMINI)
	$(COMPILER) -nostdlib -I"$(LIBCMINI)" "$(LIBCMINI)/objs/crt0.o" $< \
		-L"$(LIBCMINI)" -lgcc -lcmini -lgcc -Os -o $@

$(OUT_MINTLIB) $(OUT_LIBCMINI):
	mkdir -p $@

clean:
	$(RM) -r $(OUT_MINTLIB) $(dir $(OUT_LIBCMINI))
