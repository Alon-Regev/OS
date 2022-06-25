[bits 16]
[org 0x7C00]

KERNEL_OFFSET equ 0x1000
KERNEL_SECTOR_COUNT equ 1

; start
mov [BOOT_DRIVE], dl

; init stack
mov bp, 0x9000
mov sp, bp

; welcome msg
mov bx, BOOT_MSG
call boot_print

; move to kernel in protected mode
call load_kernel
call switch_to_protected_mode


; function loads kernel to memory at <KERNEL_OFFSET>
load_kernel:
    mov bx, KERNEL_LOAD_MSG
    call boot_print

    ; get kernel from disk
    mov bx, KERNEL_OFFSET
    mov dh, KERNEL_SECTOR_COUNT
    mov dl, [BOOT_DRIVE]
    call disk_load

    ret

; includes
%include "boot/prints.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/pm_switch.asm"

; data
BOOT_MSG db "Hello! Switching to protected mode...", 0x0A, 0x0D, 0
KERNEL_LOAD_MSG db "Loading kernel...", 0x0A, 0x0D, 0
BOOT_DRIVE db 0

; format boot sector
times 510-($-$$) db 0
; magic number
dw 0xAA55
