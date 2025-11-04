# Compile a binary with libcmini:

After building libcmini:

```bash
LIBCMINI=$PWD/build/ m68k-atari-mint-gcc \
    -nostdlib \
    -I"$LIBCMINI" \
    "$LIBCMINI/objs/crt0.o" \
    hello.c \
    -L"$LIBCMINI" \
    -lgcc \
    -lcmini \
    -lgcc \
    -o hello.tos
```

To run a given `.tos` file, in this case, `test.tos`:

```bash
hatari-prg-args -q \
  --tos emutos-512k/etos512us.img \
  --conout 2 \
  -- "$(pwd)/test.tos"
```
