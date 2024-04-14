.586P
.mmx
.MODEL FLAT, C
.CODE

_str2$ = 8                                    ; size = 4
_table$ = 8                                   ; size = 4
_hash_val$ = 12                               ; size = 4
_value$ = 16

find_key_asm PROC

        mov     eax, DWORD PTR _table$[esp-4]    ; pointer to table in eax
        mov     ecx, DWORD PTR _hash_val$[esp-4] ; hash value in ecx

        push    esi
        push    edi

        mov     esi, DWORD PTR _value$[esp+4]   ; str to find in esi (we don't have to do it
        vmovdqu ymm0, YMMWORD PTR [esi]        ;                        every time in cycle)

        mov     eax, DWORD PTR [eax]            ; pointer to table->cells in eax
        mov     ecx, DWORD PTR [eax+ecx*8]      ; table->cells[hash_val].head in ecx

        test    ecx, ecx                        ; check if table->cells[hash_val].head == NULL
        je      SHORT Not_found

Srtcmp:
        mov     eax, DWORD PTR [ecx]
        mov     DWORD PTR _str2$[esp+4], eax
        mov     edi, DWORD PTR _str2$[esp+4]    ; str in list in edi
        xor     eax, eax

        vmovdqu ymm1, YMMWORD PTR [edi]
        vptest  ymm0, ymm1                      ; compare strings

        setae   al                              ;set bit if CF == 0
        test    eax, eax

        je      SHORT Found
        mov     ecx, DWORD PTR [ecx+4]
        test    ecx, ecx

        jne     SHORT Srtcmp


Not_found:
        vzeroupper
        xor     eax, eax
        pop     edi
        pop     esi
        ret     0

Found:
        vzeroupper
        mov     eax, 1
        pop     edi
        pop     esi
        ret     0

find_key_asm ENDP
END
