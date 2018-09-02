; /*** DO NOT EDIT - GENERATED AUTOMATICALLY ***/
; /*** Copyright (C) 1996-2002 Markus F.X.J. Oberhumer ***/

.386p
.model flat

.code
public _lzo1x_decompress_asm

_lzo1x_decompress_asm:
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
                xor     eax,eax
                xor     ebx,ebx
                lodsb
                cmp     al,11H
                jbe     L6
                sub     al,11H
                cmp     al,04H
                jae     L7
                mov     ecx,eax
                jmp     L9
L3:             add     eax,000000ffH
L4:             mov     bl,[esi]
                inc     esi
                or      bl,bl
                je      L3
                lea     eax,+12H[eax+ebx]
                jmp     L7
                lea     esi,+0H[esi]
L5:             mov     al,[esi]
                inc     esi
L6:             cmp     al,10H
                jae     L10
                or      al,al
                je      L4
                add     eax,00000003H
L7:             mov     ecx,eax
                shr     eax,02H
                and     ecx,ebp
L8:             mov     edx,[esi]
                add     esi,00000004H
                mov     [edi],edx
                add     edi,00000004H
                dec     eax
                jne     L8
L9:             repe    movsb
                mov     al,[esi]
                inc     esi
                cmp     al,10H
                jae     L10
                shr     eax,02H
                mov     bl,[esi]
                lea     edx,-801H[edi]
                lea     eax,[eax+ebx*4]
                inc     esi
                sub     edx,eax
                mov     al,[edx]
                mov     [edi],al
                mov     al,+1H[edx]
                mov     +1H[edi],al
                mov     al,+2H[edx]
                mov     +2H[edi],al
                add     edi,ebp
                jmp     L18
L10:            cmp     al,40H
                jb      L13
                mov     ecx,eax
                shr     eax,02H
                lea     edx,-1H[edi]
                and     eax,00000007H
                mov     bl,[esi]
                shr     ecx,05H
                lea     eax,[eax+ebx*8]
                inc     esi
                sub     edx,eax
                inc     ecx
                cmp     eax,ebp
                jae     L15
                jmp     L20
L11:            add     eax,000000ffH
L12:            mov     bl,[esi]
                inc     esi
                or      bl,bl
                je      L11
                lea     ecx,+21H[eax+ebx]
                xor     eax,eax
                jmp     L14
                lea     esi,+0H[esi]
L13:            cmp     al,20H
                jb      L23
                and     eax,0000001fH
                je      L12
                lea     ecx,+2H[eax]
L14:            mov     ax,[esi]
                lea     edx,-1H[edi]
                shr     eax,02H
                add     esi,00000002H
                sub     edx,eax
                cmp     eax,ebp
                jb      L20
L15:            mov     ebx,ecx
                shr     ebx,02H
                je      L17
L16:            mov     eax,[edx]
                add     edx,00000004H
                mov     [edi],eax
                add     edi,00000004H
                dec     ebx
                jne     L16
                and     ecx,ebp
                je      L18
L17:            mov     al,[edx]
                inc     edx
                mov     [edi],al
                inc     edi
                dec     ecx
                jne     L17
L18:            mov     al,-2H[esi]
                and     eax,ebp
                je      L5
L19:            mov     cl,[esi]
                inc     esi
                mov     [edi],cl
                inc     edi
                dec     eax
                jne     L19
                mov     al,[esi]
                inc     esi
                jmp     L10
                nop
                lea     esi,+0H[esi]
L20:            xchg    edx,esi
                repe    movsb
                mov     esi,edx
                jmp     L18
L21:            add     ecx,000000ffH
L22:            mov     bl,[esi]
                inc     esi
                or      bl,bl
                je      L21
                lea     ecx,+9H[ebx+ecx]
                jmp     L24
                nop
                lea     esi,+0H[esi]
L23:            cmp     al,10H
                jb      L25
                mov     ecx,eax
                and     eax,00000008H
                shl     eax,0dH
                and     ecx,00000007H
                je      L22
                add     ecx,00000002H
L24:            mov     ax,[esi]
                add     esi,00000002H
                lea     edx,-4000H[edi]
                shr     eax,02H
                je      L26
                sub     edx,eax
                jmp     L15
                lea     esi,+0H[esi]
L25:            shr     eax,02H
                mov     bl,[esi]
                lea     edx,-1H[edi]
                lea     eax,[eax+ebx*4]
                inc     esi
                sub     edx,eax
                mov     al,[edx]
                mov     [edi],al
                mov     bl,+1H[edx]
                mov     +1H[edi],bl
                add     edi,00000002H
                jmp     L18
L26:            cmp     ecx,00000003H
                setne   al
                mov     edx,+28H[esp]
                add     edx,+2cH[esp]
                cmp     esi,edx
                ja      L29
                jb      L28
L27:            sub     edi,+30H[esp]
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
                jmp     L27
L28:            mov     eax,00000008H
                jmp     L27
L29:            mov     eax,00000004H
                jmp     L27
                nop

end
