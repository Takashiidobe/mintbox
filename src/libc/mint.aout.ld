/* TOS/EmuTOS PRG (a.out) layout */
OUTPUT_FORMAT(a.out-mintprg)
OUTPUT_ARCH(m68k)
ENTRY(_start)

/* No PHDRS, no SIZEOF_HEADERS in a.out. Text/Data/Bss are contiguous. */
SECTIONS
{
  /* Start at 0 for PRG (BFD will add the PRG header). */
  . = 0;

  /* --- TEXT + RO --- */
  .text : ALIGN(2)
  {
    KEEP(*(.text._start))          /* ensure _start first */
    *(.text .text.*)
    *(.rodata .rodata.*)
    KEEP(*(.init))
    KEEP(*(.fini))
  }

  /* --- DATA --- */
  .data : ALIGN(2)
  {
    *(.data .data.*)
    *(.sdata .sdata.*)
    *(.init_array .init_array.*)
    *(.fini_array .fini_array.*)
  }

  /* --- BSS --- */
  .bss (NOLOAD) : ALIGN(2)
  {
    __bss_start = .; _bss_start = .;
    *(.bss .bss.*)
    *(COMMON)
    __bss_end   = .; _bss_end   = .;
  }

  /* Strip sections not used on TOS */
  /DISCARD/ :
  {
    *(.comment) *(.note*) *(.eh_frame*) *(.stab*) *(.debug*) *(.gnu.*)
  }
}
