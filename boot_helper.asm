[org 0x7C00]

; function prints a string in the bootloader
; input: null-terminated string in bx
print:
    pusha

    mov ah, 0xe ; for print interrupt
    loop_start:
        mov al, [bx]
        cmp al, 0
        je loop_end

        mov ah, 0xe
        int 0x10
        add bx, 1
        jmp loop_start
    loop_end:

    popa
    ret

