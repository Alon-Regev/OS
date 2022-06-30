global load_idt

; function loads new idt
; input: idt pointer
; return: none
load_idt:
    mov eax, [esp + 4]  ; idt pointer param
    lidt [eax]
    ret

; common isr handler. saves state and sets up kernel mode segments.
extern isr_handler  ; c implementation
isr_common_handler:
    pusha

    ; save current data segment
    mov ax, ds
    push eax

    ; set kernel mode data segment
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 8
    sti
    iret

; common irq handler. saves state and sets up kernel mode segment. c implementation resets PIC.
extern irq_handler  ; c implementation
irq_common_handler:
    pusha

    ; save current data segment
    mov ax, ds
    push eax

    ; set kernel mode data segment
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call irq_handler

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 8
    sti
    iret

; Interrupt Service Routines

%macro ISR_NO_ERROR_CODE 1
global isr%1
isr%1:
    cli
    push byte 0     ; dummy error code
    push byte %1    ; interrupt number
    jmp isr_common_handler
%endmacro

%macro ISR_ERROR_CODE 1
global isr%1
isr%1:
    cli
    push byte %1    ; interrupt number
    jmp isr_common_handler
%endmacro

; IRQ Interrupts

; macro for IRQ
; params: IRQ number, ISR number
%macro IRQ 2
global irq%1
irq%1: 
    cli
    push byte 0
    push byte %2    ; interrupt number
%endmacro

ISR_NO_ERROR_CODE 0
ISR_NO_ERROR_CODE 1
ISR_NO_ERROR_CODE 2
ISR_NO_ERROR_CODE 3
ISR_NO_ERROR_CODE 4
ISR_NO_ERROR_CODE 5
ISR_NO_ERROR_CODE 6
ISR_NO_ERROR_CODE 7
ISR_ERROR_CODE 8
ISR_NO_ERROR_CODE 9
ISR_ERROR_CODE 10
ISR_ERROR_CODE 11
ISR_ERROR_CODE 12
ISR_ERROR_CODE 13
ISR_ERROR_CODE 14
ISR_NO_ERROR_CODE 15
ISR_NO_ERROR_CODE 16
ISR_NO_ERROR_CODE 17
ISR_NO_ERROR_CODE 18
ISR_NO_ERROR_CODE 19
ISR_NO_ERROR_CODE 20
ISR_NO_ERROR_CODE 21
ISR_NO_ERROR_CODE 22
ISR_NO_ERROR_CODE 23
ISR_NO_ERROR_CODE 24
ISR_NO_ERROR_CODE 25
ISR_NO_ERROR_CODE 26
ISR_NO_ERROR_CODE 27
ISR_NO_ERROR_CODE 28
ISR_NO_ERROR_CODE 29
ISR_NO_ERROR_CODE 30
ISR_NO_ERROR_CODE 31

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47
