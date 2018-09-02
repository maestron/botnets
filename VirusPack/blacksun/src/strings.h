static void WINAPI fZeroMemory(LPVOID lpMem, DWORD dwSize) // e.q ZeroMemory
{
	__asm
	{
		mov edi,[lpMem]
		mov ecx,[dwSize]
		xor eax,eax
		rep stosb
	}
}

static void WINAPI fMemCpy(LPVOID lpMem, LPVOID lpMem2, DWORD dwLen) // e.q memcpy
{
	__asm
	{
		mov		edi,[lpMem]
		mov		esi,[lpMem2]
		mov		ecx,[dwLen]
		rep		movsb
	}
}

static void WINAPI fMemSet(void *szBuffer, DWORD dwLen, DWORD dwSym) // e.q memset
{
	__asm
	{
		pushad
		mov		edi,[szBuffer]
		mov		ecx,[dwLen]
		mov		eax,[dwSym]
		rep		stosb
		popad
	} 
	
} 