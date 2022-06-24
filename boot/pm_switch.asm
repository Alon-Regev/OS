[bits 16]

; function switches cpu to protected mode. jumps to PM_BEGIN afterwards.
switch_to_protected_mode: 
    cli
    ; load gdt and switch to protected mode
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1 ; 32-bit mode bit
    mov cr0, eax
    jmp CODE_SEG:init_protected_mode

[bits 32]
; initializes segments for protected mode and jumps to PM_BEGIN
init_protected_mode:
    ; update segment registers (cs already updated)
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ; update stack
    mov ebp, 0x90000
    mov esp, ebp

    ; jmp to kernel entry
    call KERNEL_OFFSET
