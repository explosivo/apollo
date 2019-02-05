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

init_gdt:
    mov eax, [esp + 4]
    lgdt [eax]
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

init_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret

global _switchPageDir
_switchPageDir:
    mov eax, [esp + 4]
    mov cr3, eax
    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax
    ret

section .bss
resb 8192
stack:
