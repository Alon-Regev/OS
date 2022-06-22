loop:
    jmp loop

; format boot sector
times 510-($-$$) db 0
; magic number
dw 0xAA55