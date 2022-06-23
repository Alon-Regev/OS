[org 0x7C00]
mov bp, 0x9000
mov sp, bp

mov bx, boot_msg
call boot_print

call switch_to_protected_mode

; includes
%include "boot_helper.asm"
%include "protected_mode_switch.asm"
%include "helper.asm"

[bits 32]
PM_BEGIN:
    mov ebx, protected_mode_msg
    call print

    jmp $

; data
boot_msg:
    db "Hello! Switching to protected mode...", 0x0A, 0x0D, 0
protected_mode_msg:
    db "Hello from protected mode!", 0x0A, 0x0D, 0

; format boot sector
times 510-($-$$) db 0
; magic number
dw 0xAA55

; example data
times 256 dw 0xabcd
times 256 dw 0xfefe
