; /*** DO NOT EDIT - GENERATED AUTOMATICALLY ***/
; /*** Copyright (C) 1996-2002 Markus F.X.J. Oberhumer ***/

.386p
.model flat

.code
public _lzo1x_decompress_asm_fast_safe

_lzo1x_decompress_asm_fast_safe:
                push    ebp
                push    edi
                push    esi
                push    ebx
                push    ecx
                push    edx
                sub     esp,0000000cH
                cld
                mov     esi,+28H[esp]
                mov     edi,+30H[esp]
                mov     ebp,00000003H
                lea     eax,-3H[esi]
                add     eax,+2cH[esp]
                mov     +4H[esp],eax
                mov     eax,edi
                mov     edx,+34H[esp]
                add     eax,[edx]
                mov     [esp],eax
                xor     eax,eax
                xor     ebx,ebx
                lodsb
                cmp     al,11H
                jbe     L6
                sub     al,0eH
                jmp     L7
L3:             add     eax,000000ffH
                lea     edx,+12H[esi+eax]
                cmp     +4H[esp],edx
                jb      L26
L4:             mov     bl,[esi]
                inc     esi
                or      bl,bl
                je      L3
                lea     eax,+15H[eax+ebx]
                jmp     L7
                lea     esi,+0H[esi]
L5:             cmp     +4H[esp],esi
                jb      L26
                mov     al,[esi]
                inc     esi
L6:             cmp     al,10H
                jae     L9
                or      al,al
                je      L4
                add     eax,00000006H
L7:             lea     edx,-3H[edi+eax]
                cmp     [esp],edx
                jb      L27
                lea     edx,-3H[esi+eax]
                cmp     +4H[esp],edx
                jb      L26
                mov     ecx,eax
                xor     eax,ebp
                shr     ecx,02H
                and     eax,ebp
L8:             mov     edx,[esi]
                add     esi,00000004H
                mov     [edi],edx
                add     edi,00000004H
                dec     ecx
                jne     L8
                sub     esi,eax
                sub     edi,eax
                mov     al,[esi]
                inc     esi
                cmp     al,10H
                jae     L9
                lea     edx,+3H[edi]
                cmp     [esp],edx
                jb      L27
                shr     eax,02H
                mov     bl,[esi]
                lea     edx,-801H[edi]
                lea     eax,[eax+ebx*4]
                inc     esi
                sub     edx,eax
                cmp     edx,+30H[esp]
                jb      L28
                mov     ecx,[edx]
                mov     [edi],ecx
                add     edi,ebp
                jmp     L16
                mov     esi,esi
L9:             cmp     al,40H
                jb      L12
                mov     ecx,eax
                shr     eax,02H
                lea     edx,-1H[edi]
                and     eax,00000007H
                mov     bl,[esi]
                shr     ecx,05H
                lea     eax,[eax+ebx*8]
                inc     esi
                sub     edx,eax
                add     ecx,00000004H
                cmp     eax,ebp
                jae     L14
                jmp     L17
L10:            add     eax,000000ffH
                lea     edx,+3H[esi]
                cmp     +4H[esp],edx
                jb      L26
L11:            mov     bl,[esi]
                inc     esi
                or      bl,bl
                je      L10
                lea     ecx,+24H[eax+ebx]
                xor     eax,eax
                jmp     L13
                nop
L12:            cmp     al,20H
                jb      L20
                and     eax,0000001fH
                je      L11
                lea     ecx,+5H[eax]
L13:            mov     ax,[esi]
                lea     edx,-1H[edi]
                shr     eax,02H
                add     esi,00000002H
                sub     edx,eax
                cmp     eax,ebp
                jb      L17
L14:            cmp     edx,+30H[esp]
                jb      L28
                lea     eax,-3H[edi+ecx]
                shr     ecx,02H
                cmp     [esp],eax
                jb      L27
L15:            mov     ebx,[edx]
                add     edx,00000004H
                mov     [edi],ebx
                add     edi,00000004H
                dec     ecx
                jne     L15
                mov     edi,eax
                xor     ebx,ebx
L16:            mov     al,-2H[esi]
                and     eax,ebp
                je      L5
                lea     edx,[edi+eax]
                cmp     [esp],edx
                jb      L27
                lea     edx,[esi+eax]
                cmp     +4H[esp],edx
                jb      L26
                mov     edx,[esi]
                add     esi,eax
                mov     [edi],edx
                add     edi,eax
                mov     al,[esi]
                inc     esi
                jmp     L9
                lea     esi,+0H[esi]
L17:            cmp     edx,+30H[esp]
                jb      L28
                lea     eax,-3H[edi+ecx]
                cmp     [esp],eax
                jb      L27
                xchg    edx,esi
                sub     ecx,ebp
                repe    movsb
                mov     esi,edx
                jmp     L16
L18:            add     ecx,000000ffH
                lea     edx,+3H[esi]
                cmp     +4H[esp],edx
                jb      L26
L19:            mov     bl,[esi]
                inc     esi
                or      bl,bl
                je      L18
                lea     ecx,+0cH[ebx+ecx]
                jmp     L21
                lea     esi,+0H[esi]
L20:            cmp     al,10H
                jb      L22
                mov     ecx,eax
                and     eax,00000008H
                shl     eax,0dH
                and     ecx,00000007H
                je      L19
                add     ecx,00000005H
L21:            mov     ax,[esi]
                add     esi,00000002H
                lea     edx,-4000H[edi]
                shr     eax,02H
                je      L23
                sub     edx,eax
                jmp     L14
                lea     esi,+0H[esi]
L22:            lea     edx,+2H[edi]
                cmp     [esp],edx
                jb      L27
                shr     eax,02H
                mov     bl,[esi]
                lea     edx,-1H[edi]
                lea     eax,[eax+ebx*4]
                inc     esi
                sub     edx,eax
                cmp     edx,+30H[esp]
                jb      L28
                mov     al,[edx]
                mov     [edi],al
                mov     bl,+1H[edx]
                mov     +1H[edi],bl
                add     edi,00000002H
                jmp     L16
L23:            cmp     ecx,00000006H
                setne   al
                cmp     edi,[esp]
                ja      L27
                mov     edx,+28H[esp]
                add     edx,+2cH[esp]
                cmp     esi,edx
                ja      L26
                jb      L25
L24:            sub     edi,+30H[esp]
                mov     edx,+34H[esp]
                mov     [edx],edi
                neg     eax
                add     esp,0000000cH
                pop     edx
                pop     ecx
                pop     ebx
                pop     esi
                pop     edi
                pop     ebp
                ret
                mov     eax,00000001H
                jmp     L24
L25:            mov     eax,00000008H
                jmp     L24
L26:            mov     eax,00000004H
                jmp     L24
L27:            mov     eax,00000005H
                jmp     L24
L28:            mov     eax,00000006H
                jmp     L24

end
