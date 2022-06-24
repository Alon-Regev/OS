[org 0x7C00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

mov bx, BOOT_MSG
call boot_print

call load_kernel
call switch_to_protected_mode
jmp $

; includes
%include "boot_helper.asm"
%include "boot_disk_helper.asm"
%include "gdt.asm"
%include "helper.asm"
%include "protected_mode_switch.asm"

[bits 16]
load_kernel:
    mov bx, KERNEL_LOAD_MSG
    call boot_print

    ; get kernel from disk
    mov bx, KERNEL_OFFSET
    mov dh, 1
    mov dl, [BOOT_DRIVE]
    call disk_load
    
    ret

[bits 32]
PM_BEGIN:
    mov ebx, PROTECTED_MODE_MSG
    call print
    call KERNEL_OFFSET
    jmp $

; data
BOOT_MSG db "Hello! Switching to protected mode...", 0x0A, 0x0D, 0
KERNEL_LOAD_MSG db "Loading kernel...", 0x0A, 0x0D, 0
PROTECTED_MODE_MSG db "Hello from protected mode!", 0x0A, 0x0D, 0
BOOT_DRIVE db 0

; format boot sector
times 510-($-$$) db 0
; magic number
dw 0xAA55
