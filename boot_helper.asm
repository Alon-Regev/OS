[org 0x7C00]

; function prints a string in the bootloader
; input: null-terminated string in bx
boot_print:
    pusha

    mov ah, 0xe ; for print interrupt
    loop_start_0:
        mov al, [bx]
        cmp al, 0
        je loop_end_0

        mov ah, 0xe
        int 0x10
        add bx, 1
        jmp loop_start_0
    loop_end_0:

    popa
    ret

; function prints a hexadecimal number in the bootloader
; input: number in dx
boot_print_hex:
    pusha

    mov bx, hex_format
    call boot_print

    mov ah, 0xe
    mov cx, 4
    loop_start_1:
        rol dx, 4

        mov al, dl  ; working register
        and al, 0xF
        add al, '0' ; show as ascii char
        cmp al, '9'    ; if digit > 9
        jbe print_digit
        ; convert to letter
        add al, 'A' - '0' - 10

        print_digit:
        int 0x10
    loop loop_start_1

    popa
    ret

; data
hex_format:
    db "0x", 0