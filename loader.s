bits 32

section .text
align 4
dd 0x1badb002
dd 0x00
dd - (0x1badb002 + 0x00)

global start
extern main

start:
    cli
    mov esp, stack
    call main
    hlt

global init_gdt
extern gp

init_gdt:
    lgdt [gp]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:init_gdt_ret
init_gdt_ret:
    ret

global init_idt
extern idtp

init_idt:
    lidt [idtp]
    ret

section .bss
resb 8192
stack:
