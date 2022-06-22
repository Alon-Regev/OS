; function loads data from disk
; input: 
;   dh: number of sectors to read
;   dl: drive to read from
;   ds:bx: memory address to write to
; return: none
disk_load:
    pusha
    push dx ; save to check errors

    ; prepare parameters
    mov ah, 0x02    ; interrupt 0x13 function (read)
    mov al, dh      ; number of sectors to read
    mov cl, 0x02    ; sector (1 is boot)
    mov ch, 0       ; cylinder (+2 high bits of cl)
    ; dl = drive number (caller gets it from BIOS)
    mov dh, 0       ; head number
    ; es:bx = pointer to buffer (from caller)
    int 0x13
    jc disk_read_error

    pop dx
    cmp al, dh  ; al = sectors read, dh = sectors requested
    jne sector_count_error
    popa
    ret

    ; error handling
    disk_read_error:
        mov bx, DISK_ERROR_MSG
        call print

        mov dh, ah  ; ah = error code, dl = drive where the error happened
        call print_hex

        jmp disk_halt

    sector_count_error:
        mov bx, SECTOR_COUNT_ERROR
        call print
        jmp disk_halt

    disk_halt:
        jmp $

; error messages
DISK_ERROR_MSG:
    db "Disk read error: ", 0
SECTOR_COUNT_ERROR:
    db "Incorrect number of sectors read.", 0
