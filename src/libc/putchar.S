        .text
        .even
        .globl  putchar
putchar:
        move.l  4(sp), d0          | d0 = ch (C passes 32-bit)
        move.w  d0, -(sp)          | push char (WORD)
        move.w  #0x02, -(sp)       | GEMDOS Cconout
        trap    #1
        addq.l  #4, sp             | pop (char + function)
        rts
