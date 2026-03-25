extern kernel_main

global _start

section .text
_start:
    cli

    mov esp, stack_top

    call kernel_main

.hang:
    hlt
    jmp .hang

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:
