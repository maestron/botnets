// str_hash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

unsigned long CalcHash(char *s)
{
	unsigned long dwHash = 0;

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


int main(int argc, char* argv[])
{
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
	while(fgets((char *)&szStr,100,fp))
	{		
		szStr[strlen(szStr)-1] = 0x00;
		printf("0x%08X\t/* %-35s */,\n",CalcHash((char *)&szStr),szStr);
		memset(szStr,0,1024);
	}
	return 0;
}
