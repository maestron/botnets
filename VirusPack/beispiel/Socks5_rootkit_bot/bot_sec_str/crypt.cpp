#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
char *WINAPI eL_DeCrypt( char *pStr );
char *WINAPI eL_Crypt( char *pStr );

static char szTempBuf[ 256 ];

int
main( int argc, char *argv[])
{
	
	int i = 0;
	int j = 0;
	BYTE b;
	char szStr[1024] = { 0 };
	FILE *fp;

	if(argc < 2)
	{
		printf("str_hash.exe file.txt\n");
		return -1;
	}
	fp = fopen(argv[1],"r");
	if(!fp)
	{
		printf("error open file %s\n",argv[1]);
		return -1;
	}


	while (fgets((char *)&szStr,100,fp)){
		szStr[strlen(szStr)-1] = 0x00;
		//printf("0x%08X\t/* %-35s */,\n",CalcHash((char *)&szStr),szStr);
		printf("/\* %s \*/\t\t\t \"",szStr);
		char *a = 0; 
		a = eL_Crypt(szStr);
		while ( *a != '\0' )
		{
			b = a[ j ];
			printf( "\\x%.2x", b );
			a++;
		}
		printf("\",\n");
	} 
	return 0;
} // end if




/*
================
eL_DeCrypt
================
*/
char * 
WINAPI eL_Crypt( char *pStr )
{
	__asm
	{
		pushad
		mov		esi,[pStr]
		mov		edi,offset szTempBuf
	__again:
			lodsb
			test	al,al
			jz		__to_exit
			// 19/07/86 ( 13h/07h/56h )
			// мой др (:
			sub		al,31h
			xor		al,33h
			add		al,77h
			stosb
			jmp		__again

	__to_exit:
		stosb
		popad
	} // end asm

	return szTempBuf;
} // end of fucntion eL_DeCry


/*
================
eL_DeCrypt
================
*/
char * 
WINAPI eL_DeCrypt( char *pStr )
{
	__asm
	{
		pushad
		mov		esi,[pStr]
		mov		edi,offset szTempBuf
	__again:
			lodsb
			test	al,al
			jz		__to_exit
			sub		al,77h
			xor		al,33h
			add		al,31h
			stosb
			jmp		__again

	__to_exit:
		stosb
		popad
	} // end asm

	return szTempBuf;
} // end of fucntion eL_DeCrypt