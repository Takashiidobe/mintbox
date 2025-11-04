        .text
        .even
        .globl  _start
        .type   _start,@function

_start:
        subl    %a6, %a6                | clear a6 (helps some debuggers)

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
        lea     %a0@(252), %sp         | temporary stack (command line area)
        bra     after_stack

start_prg:
        | ---- Program entry ----
        | For PRGs, basepage is at sp@(4)
        movel   %sp@(4), %a5           | a5 := basepage
        | Set stack from p_hitpa (basepage+4), clear bit 0, -64 bytes
        movel   %a5@(4), %d0           | d0 := p_hitpa
        bclr    #0, %d0                | word-align (round down)
        movel   %d0, %sp
        subl    #64, %sp               | small scratch, per mintlib convention

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

        | ---- Publish environ from basepage->p_env (offset 0x2C) ----
        movel   %a5@(44), %a1          | a1 := envp (p_env)
        lea     environ, %a2
        movel   %a1, (%a2)

        | ---- Build minimal argv on stack: argv = { NULL } ----
        subq.l  #4, %sp
        clrl    (%sp)                  | argv[0] = NULL
        movel   %sp, %a0               | a0 := argv
        moveq   #0, %d0                | d0 := argc = 0

        | ---- Call _main(argc, argv, envp) ----
        movel   %a1, -(%sp)            | envp
        movel   %a0, -(%sp)            | argv
        movel   %d0, -(%sp)            | argc
        jsr     _main
        add.l  #12, %sp                | pop args

        | ---- Exit via GEMDOS Pterm (0x4C), status on stack ----
        movew   %d0, -(%sp)            | status (low 16 bits)
        movew   #0x4c, -(%sp)
        trap    #1                     | does not return

hang:
        bra     hang                 | safety if trap returns

        .size   _start,.-_start

        .data
        .align  2
        .globl  environ
environ:
        .long   0

        .bss
        .align  2
