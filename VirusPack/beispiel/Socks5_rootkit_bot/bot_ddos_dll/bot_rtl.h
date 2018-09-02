void WINAPI rtl_strcpy( char *szBuf, const char *szStr )
{
	__asm
	{
		pushad
		mov		esi,[szStr]
		mov		edi,[szBuf]
	__copy:
			lodsb
			test	al,al
			stosb
			jnz		__copy

		popad
	} // end asm
}
//=======================================================================
void WINAPI rtl_strcat( char *szBuf, const char *szStr )
{
	__asm
	{
		pushad
		mov		esi,[szBuf]
	__again:
			lodsb
			test	al,al
			jnz		__again

		dec		esi
		xchg	esi,edi
		mov		esi,[szStr]
	__copy:
			lodsb
			test	al,al
			stosb
			jnz		__copy
		popad
	}
}
//=======================================================================
void WINAPI rtl_memset( void *szBuffer, DWORD dwLen, DWORD dwSym )
{
	__asm
	{
		pushad
		mov		edi,[szBuffer]
		mov		ecx,[dwLen]
		mov		eax,[dwSym]
		rep		stosb
		popad
	} // end asm
	
} //