[org 0x7C00]
mov bp, 0x8000
mov sp, bp

mov bx, hello_msg
call print

; load from disk
mov bx, 0x9000
mov dh, 2   ; read 2 sectors
call disk_load

mov dx, [0x9000]    ; sector 2
call print_hex
mov dx, [0x9000 + 512]  ; sector 3
call print_hex

jmp $

; includes
%include "boot_helper.asm"
%include "boot_disk_helper.asm"

; data
hello_msg:
    db "Hello! Loading from disk...", 0x0A, 0x0D, 0

; format boot sector
times 510-($-$$) db 0
; magic number
dw 0xAA55

; example data
times 256 dw 0xabcd
times 256 dw 0xfefe
