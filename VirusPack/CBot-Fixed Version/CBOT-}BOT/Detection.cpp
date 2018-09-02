#include "Include.h"
#include "Hell.h"
#ifndef NO_DDETECT
#pragma warning(disable:4035)
#pragma warning(disable:4731)



__inline bool IsODBGLoaded()
{
	char *caption="DAEMON";
	_asm
	{
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

/*	Function: IsSoftIceNTLoaded
	Description: Like the previous one but for use under Win NT only
	Returns: true if SoftIce is loaded */
__inline BOOL IsSoftIceNTLoaded()
{
    HANDLE hFile=CreateFile("\\\\.\\NTICE", GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
							NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		return TRUE;
	}
    return FALSE;
}

/*	Functions are declared as __inline, this causes the expansion of this code each time a function is invoked, this is to difficult the cracker work by using this function more than once time
	Function: IsBPX
	Description: Checks if the given memory address is a breakpoint
	Returns: true if it is a breakpoint */
__inline bool IsBPX(void *address)
{
	_asm
	{
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

/* executes VMware backdoor I/O function call */
#define VMWARE_MAGIC		0x564D5868	// Backdoor magic number
#define VMWARE_PORT			0x5658		// Backdoor port number
#define VMCMD_GET_VERSION	0x0a		// Get version number

int VMBackDoor(unsigned long *reg_a, unsigned long *reg_b, unsigned long *reg_c, unsigned long *reg_d)
{
	unsigned long a, b, c, d;
	b=reg_b?*reg_b:0;
	c=reg_c?*reg_c:0;
	try {
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
	} catch(...) {}
	
	if(reg_a)
		*reg_a=a;
	if(reg_b)
		*reg_b=b;
	if(reg_c)
		*reg_c=c;
	if(reg_d)
		*reg_d=d;
	return a;
}

/* Check VMware version only */
int VMGetVersion()
{
	unsigned long version, magic, command;
	command=VMCMD_GET_VERSION;
	VMBackDoor(&version, &magic, &command, NULL);
	if(magic==VMWARE_MAGIC)
		return version;
	else return 0;
}

/* Check if running inside VMWare */
int IsVMWare()
{
	int version=VMGetVersion();
	if(version)
		return TRUE;
	else
		return FALSE;
}

/* Fool ProcDump with increasing size */
void FoolProcDump()
{
	__asm {
		mov eax, fs:[0x30]
		mov eax, [eax+0xC]
		mov eax, [eax+0xC]
		add dword ptr [eax+0x20], 0x2000	// increase size variable
	}
}
#endif

typedef BOOL (*pfnIsDebuggerPresent)(void);
BOOL IsDebug=FALSE;
BOOL IsBugged()
{
#ifdef _DEBUG
	return FALSE;
#else

	if(IsDebug)
		return true;

	pfnIsDebuggerPresent IsDbgPresent=NULL;
	HMODULE hK32=GetModuleHandle("KERNEL32.DLL");
	if(!hK32)
		hK32=LoadLibrary("KERNEL32.DLL");

	if(hK32)
		IsDbgPresent=(pfnIsDebuggerPresent)GetProcAddress(hK32, "IsDebuggerPresent");

	FoolProcDump();

	unsigned long lStartTime=GetTickCount();

	if(IsBPX(&IsBPX))
	{
		IsDebug=TRUE;
		return TRUE;
	}
	

	if(IsBPX(&IsSoftIceNTLoaded))
	{
		IsDebug=TRUE;
		return TRUE;
	}
	if(IsBPX(&IsVMWare))
	{

	}

	if(IsSoftIceNTLoaded())
	{
		IsDebug=TRUE;
		return TRUE;
	}



	if(IsDbgPresent)
	{
		if(IsBPX(&IsDbgPresent))
		{

			IsDebug=TRUE;
			return TRUE;
		}

		if(IsDbgPresent())
		{
			IsDebug=TRUE;
			return TRUE;
		}
	}


	if((GetTickCount()-lStartTime) > 5000)
	{
		IsDebug=TRUE;
		return TRUE;
	}
	return FALSE;

#endif 
}