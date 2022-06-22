[org 0x7C00]
mov sp, 0x8000

mov bx, hello_msg
call print

jmp $

; includes
%include "boot_helper.asm"

; data
hello_msg:
    db "Hello world!", 0x0A, 0x0D, 0

; format boot sector
times 510-($-$$) db 0
; magic number
dw 0xAA55