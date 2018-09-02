unit EliRT;

interface

function RT_GetVersion(pReserved :Pointer) :LongWord; stdcall;
function xVirtualAllocEx(hProcess :LongWord; lpAddress :Pointer; dwSize :LongWord; flAllocationType :LongWord; flProtect :LongWord) :Pointer; stdcall;
function xVirtualFreeEx(hProcess :LongWord; lpAddress :Pointer; dwSize :LongWord; dwFreeType :LongWord) :Boolean; stdcall;
function xCreateRemoteThread(hProcess :LongWord; lpThreadAttributes :Pointer; dwStackSize :LongWord; lpStartAddress :Pointer; lpParameter :Pointer; dwCreationFlags :LongWord; lpThreadId :Pointer) :LongWord; stdcall;
function xOpenThread(dwDesiredAccess :LongWord; bInheritHandle :Boolean; dwThreadId :LongWord) :LongWord; stdcall;

implementation

uses Windows;
{$L EliRT_OMF_B.obj}
function RT_GetVersion(pReserved :Pointer) :LongWord; stdcall; external;
function xVirtualAllocEx(hProcess :LongWord; lpAddress :Pointer; dwSize :LongWord; flAllocationType :LongWord; flProtect :LongWord) :Pointer; stdcall; external;
function xVirtualFreeEx(hProcess :LongWord; lpAddress :Pointer; dwSize :LongWord; dwFreeType :LongWord) :Boolean; stdcall; external;
function xCreateRemoteThread(hProcess :LongWord; lpThreadAttributes :Pointer; dwStackSize :LongWord; lpStartAddress :Pointer; lpParameter :Pointer; dwCreationFlags :LongWord; lpThreadId :Pointer) :LongWord; stdcall; external;
function xOpenThread(dwDesiredAccess :LongWord; bInheritHandle :Boolean; dwThreadId :LongWord) :LongWord; stdcall; external;

end.