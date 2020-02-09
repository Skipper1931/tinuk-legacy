; (Taken from https://wiki.osdev.org/Setting_Up_Long_Mode)

BITS 32

SECTION .text
GLOBAL check_64

check_64:
    call check_cpuid
    cmp eax, 0x0
    je .NoLongMode

    mov eax, 0x80000000    
    cpuid   
    cmp eax, 0x80000001
    jb .NoLongMode       ; It is less, there is no long mode.

    mov eax, 0x80000001    
    cpuid                  
    test edx, 1 << 29   ; Test if the LM-bit, which is bit 29, is set in the D-register.
    jz .NoLongMode       ; They aren't, there is no long mode.

    mov eax, 0x1
    ret
.NoLongMode:
    cli
    hlt
    jmp .NoLongMode

check_cpuid: 
    ; Check if CPUID is supported by attempting to flip the ID bit (bit 21) in
    ; the FLAGS register. If we can flip it, CPUID is available.
    push ecx

    ; Copy FLAGS in to EAX via stack
    pushfd
    pop eax
 
    ; Copy to ECX as well for comparing later on
    mov ecx, eax
 
    ; Flip the ID bit
    xor eax, 1 << 21
 
    ; Copy EAX to FLAGS via the stack
    push eax
    popfd
 
    ; Copy FLAGS back to EAX (with the flipped bit if CPUID is supported)
    pushfd
    pop eax
 
    ; Restore FLAGS from the old version stored in ECX (i.e. flipping the ID bit
    ; back if it was ever flipped).
    push ecx
    popfd
 
    ; Compare EAX and ECX. If they are equal then that means the bit wasn't
    ; flipped, and CPUID isn't supported.
    cmp eax, ecx
    je .noCPUID
    mov eax, 0x1
    jmp .endCPUID
.noCPUID:
    mov eax,0x0
.endCPUID:
    pop ecx
    ret