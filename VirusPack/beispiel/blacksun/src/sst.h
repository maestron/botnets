// (c) Cr4sh

typedef struct 
{
    WORD    offset:12;
    WORD    type:4;
} IMAGE_FIXUP_ENTRY, 
*PIMAGE_FIXUP_ENTRY;

// address of SST
DWORD sstaddr;
// number of services to restore
DWORD dwServices;

#define RVATOVA( base, offset )(((DWORD)(base) + (DWORD)(offset))) 
//--------------------------------------------------------------------------------------
// parse PE-header
void GetHeaders(PCHAR ibase, PIMAGE_FILE_HEADER *pfh, PIMAGE_OPTIONAL_HEADER *poh, PIMAGE_SECTION_HEADER *psh)
{
	PIMAGE_DOS_HEADER mzhead = (PIMAGE_DOS_HEADER)ibase;

	*pfh = (PIMAGE_FILE_HEADER)&ibase[mzhead->e_lfanew];

	*pfh = (PIMAGE_FILE_HEADER)((PBYTE)*pfh + sizeof(IMAGE_NT_SIGNATURE));

	*poh = (PIMAGE_OPTIONAL_HEADER)((PBYTE)*pfh + sizeof(IMAGE_FILE_HEADER));

	*psh = (PIMAGE_SECTION_HEADER)((PBYTE)*poh + sizeof(IMAGE_OPTIONAL_HEADER));
}
//--------------------------------------------------------------------------------------
// find SST in kernel image
DWORD FindKiServiceTable(HMODULE hModule, DWORD dwKSDT)
{
	PIMAGE_FILE_HEADER		pfh;
	PIMAGE_OPTIONAL_HEADER	poh;
	PIMAGE_SECTION_HEADER	psh;
	PIMAGE_FIXUP_ENTRY 		pfe;
	BOOL bFirstChunk;
	DWORD dwPointerRva;
	DWORD dwPointsToRva;
	UINT i;
	GetHeaders((PCHAR)hModule, &pfh, &poh, &psh);

	if ((poh->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress) &&
		(!((pfh->Characteristics)&IMAGE_FILE_RELOCS_STRIPPED)))
	{
		PIMAGE_BASE_RELOCATION pbr = (PIMAGE_BASE_RELOCATION)
			RVATOVA(poh->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress, hModule);
        
		bFirstChunk = TRUE;

		while (bFirstChunk || pbr->VirtualAddress) 
		{
			bFirstChunk = FALSE;

			pfe = (PIMAGE_FIXUP_ENTRY)((DWORD)pbr + sizeof(IMAGE_BASE_RELOCATION));

			for (i = 0; i < (pbr->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) >> 1; i++, pfe++) 
			{
				if (pfe->type == IMAGE_REL_BASED_HIGHLOW) 
				{
					dwPointerRva = pbr->VirtualAddress + pfe->offset;
					dwPointsToRva = *(PDWORD)((DWORD)hModule + dwPointerRva) - (DWORD)poh->ImageBase;

					if (dwPointsToRva == dwKSDT) 
					{
						if (*(PWORD)((DWORD)hModule + dwPointerRva - 2) == 0x05c7) 
							return *(PDWORD)((DWORD)hModule + dwPointerRva + 4) - poh->ImageBase;
					}
				}
			}
			*(PDWORD)&pbr += pbr->SizeOfBlock;
		}
	}    
    
    return 0;
}
//--------------------------------------------------------------------------------------
BOOL ReadSST(PDWORD psst)
{    
	NTSTATUS ns;
	DWORD dwKernelBase;
	char *pKernelName;
	HMODULE hKernel;
	DWORD dwKSDT;
	PSYSTEM_MODULE_INFORMATION pModules;
	DWORD dwNeededSize;
	DWORD dwKiServiceTable;
	PDWORD pService;
	
	PIMAGE_FILE_HEADER		pfh;
	PIMAGE_OPTIONAL_HEADER	poh;
	PIMAGE_SECTION_HEADER	psh;
	
	pModules = (PSYSTEM_MODULE_INFORMATION)&pModules;
	dwNeededSize = 0;
	
dwServices = 0;

	ns = NtQuerySystemInformation(SystemModuleInformation, pModules, 4, &dwNeededSize);
	if (ns == STATUS_INFO_LENGTH_MISMATCH) 
	{
		pModules = (PSYSTEM_MODULE_INFORMATION)VirtualAlloc(NULL, dwNeededSize, 
			MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		if (pModules == NULL)
		{
			return FALSE;
		}

        ns = NtQuerySystemInformation(SystemModuleInformation, pModules, dwNeededSize, NULL);
    }

	if (ns != STATUS_SUCCESS) 
	{
		return FALSE;
	}
    
	dwKernelBase = pModules->aSM[0].Base;
	pKernelName = pModules->aSM[0].ModuleNameOffset + pModules->aSM[0].ImageName;
	hKernel = LoadLibraryEx(pKernelName, 0, DONT_RESOLVE_DLL_REFERENCES);
	
	if (hKernel == NULL)
	{
		return FALSE;
	}

	VirtualFree(pModules, 0, MEM_RELEASE);

	if (!(dwKSDT = (DWORD)GetProcAddress(hKernel, "KeServiceDescriptorTable")))
	{
		return FALSE;
	}

	dwKSDT -= (DWORD)hKernel;

	if (!(dwKiServiceTable = FindKiServiceTable(hKernel, dwKSDT)))
	{
		return FALSE;
	}

	GetHeaders((PCHAR)hKernel, &pfh, &poh, &psh);

	pService = (PDWORD)((DWORD)hKernel + dwKiServiceTable);

	for (pService = (PDWORD)((DWORD)hKernel + dwKiServiceTable);
		*pService-poh->ImageBase < poh->SizeOfImage;
		pService++, dwServices++) 
	{
		psst[dwServices] = *pService - poh->ImageBase + dwKernelBase;
	}

	sstaddr = (DWORD)(dwKernelBase + dwKSDT);

    FreeLibrary(hKernel);

	return TRUE;
}
//--------------------------------------------------------------------------------------
// EoF
