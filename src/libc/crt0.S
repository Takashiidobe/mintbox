				.text
        .even
        .globl  _start
        .type   _start,@function

_start:
        subl    %a6, %a6                

        | ---- Detect ACC vs PRG ----
        cmpl    #0, %a0
        beqs    .Lstart_prg             | a0 == 0 => program
        tstl    %a0@(36)                | parent basepage pointer
        bnes    .Lstart_prg             | non-zero => treat as program

        | ---- Accessory entry ----
        movel   %a0, %a5                 | a5 := basepage
        lea     %a0@(252), %sp           | temporary stack (command line area)
        bra     .Lafter_stack

.Lstart_prg:
        | ---- Program entry ----
        movel   %sp@(4), %a5             | a5 := basepage
        movel   %a5@(4), %d0             | d0 := p_hitpa
        bclr    #0, %d0                  | word-align (round down)
        movel   %d0, %sp
        subl    #64, %sp                 | small scratch per mintlib convention

.Lafter_stack:
        | ---- Clear BSS using [_edata, _end) ----
        lea     _edata, %a0
        lea     _end,   %a1
.Lbss_loop:
        cmpa.l  %a1, %a0
        bhs     .Lbss_done
        clrb    (%a0)+
        bra     .Lbss_loop
.Lbss_done:

        | ---- Publish environ from basepage->p_env (offset 0x2C) ----
        movel   %a5@(44), %a1            | a1 := envp (p_env)
        lea     environ, %a2
        movel   %a1, (%a2)

        | ---- Build minimal argv on stack: argv = { NULL } ----
        subq.l  #4, %sp
        clrl    (%sp)                    | argv[0] = NULL
        movel   %sp, %a0                 | a0 := argv
        moveq   #0, %d0                  | d0 := argc = 0

        | ---- Call _main(argc, argv, envp) ----
        movel   %a1, -(%sp)              | envp
        movel   %a0, -(%sp)              | argv
        movel   %d0, -(%sp)              | argc
        jsr     _main
        add.l   #12, %sp                 | pop args

        | ---- Exit via GEMDOS Pterm (0x4C), status on stack ----
        movew   %d0, -(%sp)              | status (low 16 bits)
        movew   #0x4c, -(%sp)
        trap    #1                       | does not return

.Lhang:
        bra     .Lhang                   | safety if trap returns

        .size   _start,.-_start

        .data
        .align  2
        .globl  environ
environ:
        .long   0
