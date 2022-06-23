[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

; function prints a string in 32-bit protected mode
; input: string in ebx
print:
    pusha

    mov edx, VIDEO_MEMORY

    mov ah, WHITE_ON_BLACK
    print_loop_start:
        ; check null char
        mov al, [ebx]
        cmp al, 0
        je print_loop_end
        ; print char and increment pointers (copy to video memory)
        mov [edx], ax
        add edx, 2
        add ebx, 1 
        jmp print_loop_start
    print_loop_end:

    popa
    ret
