BITS 32

SECTION .bss
align 4096
p4_table:
    resb 4096
p3_table:
    resb 4096
p2_table:
    resb 4096

SECTION .text
GLOBAL setup_page_tables
setup_page_tables:
    ; Point the first entry of the level 4 page table to the first entry in the
    ; p3 table
    mov eax, p3_table
    or eax, 0b11 ;
    mov dword [p4_table + 0], eax

    ; Point the first entry of the level 3 page table to the first entry in the
    ; p2 table
    mov eax, p2_table
    or eax, 0b11
    mov dword [p3_table + 0], eax

    ; point each page table level two entry to a page
    mov ecx, 0         ; counter variable
.map_p2_table:
    mov eax, 0x200000  ; 2MiB
    mul ecx
    or eax, 0b10000011
    mov [p2_table + ecx * 8], eax

    inc ecx
    cmp ecx, 512
    jne .map_p2_table

    mov eax, p4_table

    ret
    cli ; if for some reason the CPU keeps going past ret, halt here so we dont execute the page tables lol
    hlt