global load_idt

; function loads new idt
; input: idt pointer
; return: none
load_idt:
    mov eax, [esp + 4]  ; idt pointer param
    lidt [eax]
    ret