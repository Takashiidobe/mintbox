        .text
        .even
        .globl  _start
        .type   _start,@function
        .globl  ___libc_start_main
        .globl  _acc_main
        .globl  _base

_start:
        subl    %a6, %a6                | clear a6 (helps some debuggers)
        moveq   #0, %d7                 | assume program

        | ---- Detect ACC vs PRG ----
        | a0 != 0 and a0@(36) == 0  => ACC
        | otherwise                  => PRG
        cmpl    #0, %a0
        beqs    start_prg           | a0 == 0 => program
        tstl    %a0@(36)              | parent basepage pointer
        bnes    start_prg           | if non-zero, treat as program

        | ---- Accessory entry ----
        | ACC basepage is in a0
        movel   %a0, %a5               | a5 := basepage
        moveq   #1, %d7                | mark accessory
        bra     after_stack_setup

start_prg:
        | ---- Program entry ----
        | For PRGs, basepage is at sp@(4)
        movel   %sp@(4), %a5           | a5 := basepage

after_stack_setup:
        | ---- Set stack from p_hitpa (basepage+4) ----
        movel   %a5@(4), %d0           | d0 := p_hitpa
        bclr    #0, %d0                | word-align (round down)
        movel   %d0, %sp
        subl    #64, %sp               | small scratch, per mintlib convention
        movel   %a5, _base

after_stack:
        | ---- Zero BSS: [_edata, _end) ----
        lea     _edata, %a0
        lea     _end,   %a1
bss_loop:
        cmpa.l  %a1, %a0
        bhs     bss_done
        clrb    (%a0)+
        bra     bss_loop
bss_done:

        | ---- Enter C runtime ----
        tstb    %d7
        bnes    accessory_entry
        movel   %a5, -(%sp)
        jsr     ___libc_start_main
        addql   #4, %sp

        | ---- Exit via GEMDOS Pterm (0x4C), status on stack ----
        movew   %d0, -(%sp)            | status (low 16 bits)
        movew   #0x4c, -(%sp)
        trap    #1                     | does not return

accessory_entry:
        jsr     _acc_main

hang:
        bra     hang                 | safety if trap returns

        .size   _start,.-_start
