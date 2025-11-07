OUTPUT_FORMAT(elf32-m68k)
OUTPUT_ARCH(m68k)
ENTRY(_start)

PHDRS
{
  text PT_LOAD FILEHDR PHDRS FLAGS(5);  /* R|X */
  data PT_LOAD             FLAGS(6);    /* R|W */
}

SECTIONS
{
  /* Start at 0, but then reserve space for the ELF header + PHDR table
     so the first PT_LOAD segment can include them cleanly. */
  . = 0;
  . = SIZEOF_HEADERS;        /* <-- this line is the key */

  .text : ALIGN(2)
  {
    KEEP(*(.text._start))
    *(.text .text.*)
    KEEP(*(.init)) KEEP(*(.fini))
  } :text

  .rodata : ALIGN(2) { *(.rodata .rodata.*) } :text

  .init_array : ALIGN(2) { KEEP(*(.init_array .init_array.*)) } :data
  .fini_array : ALIGN(2) { KEEP(*(.fini_array .fini_array.*)) } :data

  .data : ALIGN(2) { *(.data .data.*) } :data

  .bss (NOLOAD) : ALIGN(2)
  {
    __bss_start = .;
    *(.bss .bss.*) *(COMMON)
    __bss_end = .; 
  } :data

  /DISCARD/ : { *(.comment) *(.note*) *(.eh_frame*) *(.stab*) *(.debug*) *(.gnu.*) }
}
