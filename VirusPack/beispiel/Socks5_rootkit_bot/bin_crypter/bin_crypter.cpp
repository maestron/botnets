// bin_crypter.cpp : Defines the entry point for the console application.
// komarov =/
#define _CRYPTER_
#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include "gost.h"
#define FILE_SIZE 1000000

HANDLE g_hFile = NULL;
ULONG nKeyArray[8] = { 0 };

PBYTE OpenAndRead(char *FileName,LPDWORD Size)
{
	OVERLAPPED Overlapped = { 0 };
	unsigned char *pMem;
	unsigned long nRead = 0;
	unsigned long nFileSize = 0;

	g_hFile = CreateFile(FileName,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(!g_hFile)
	{
		printf("[-] Error open file %s, Last Error [%d]\n",FileName,GetLastError());
		exit(-1);
	}	else
		printf("[+] File %s opened for read, try to allocate memory for buffer..\n",FileName);

	nFileSize = GetFileSize(g_hFile,NULL);
	if(!(pMem= (unsigned char*)malloc(nFileSize)))
	{
		printf("[-] Error allocate memory for file buffer\n");
		exit(-1);
	}	else
		printf("[+] %d bytes allocated for file buffer\n",nFileSize);

	if(!ReadFile(g_hFile,(LPVOID)pMem,nFileSize,&nRead,&Overlapped))
	{
		printf("[-] Error read data from file, readed %d bytes\n",nRead);
	}

	printf("[+] Readed %d bytes from file\n",nFileSize);
	*Size = nFileSize;
	return pMem;
}

void GenerateRandomKey()
{
	BYTE i = 0;
	SYSTEMTIME SystemTime = { 0 };

	GetSystemTime(&SystemTime);
	srand(SystemTime.wMilliseconds+RAND32);
	for(i = 0; i < 8 ; i++)
	{
		printf("[+] Generate key number \t%d.....",i);
		Sleep(50*i);
		GetSystemTime(&SystemTime);
		srand(SystemTime.wMilliseconds+RAND32);

		nKeyArray[i] = (unsigned long)RAND32;
		srand(nKeyArray[i]^RAND32^(DWORD)&GetSystemInfo);
		printf("0x%08X\n",nKeyArray[i]);
	}
	printf("[+] Done, 32 random bytes generated\n");
}
typedef unsigned long * ULONG_PTR;

PFileStorage DeCryptBuffer(PFileStorage pFileStor)
{
	ULONG_PTR pOutMem = NULL,pMem = 0;
	ULONG i = 0;
	ULONG in[2],out[2];
	ULONG_PTR pDecryptMem;
	ULONG Key[8];

	pDecryptMem = (ULONG_PTR)((PBYTE)pFileStor + sizeof(_FILE_STORAGE));

	memcpy(&Key,pFileStor->nKeyArray,32);
#ifdef _CRYPTER_
	printf("[+] DeCryptBuffer : Buffer size : [ %d ] , +Append : [ %d ]\n",		pFileStor->FileSize,pFileStor->BufferSize);
#endif

	pOutMem = (ULONG_PTR)malloc(pFileStor->BufferSize);
	memset(pOutMem,0,pFileStor->BufferSize);
	pMem = pOutMem;
	for( i = 0; i <= pFileStor->BufferSize / 8; i++)
	{
		in[0] = (ULONG)*pDecryptMem;
		(ULONG)*pDecryptMem++;
		in[1] = (ULONG)*pDecryptMem;
		(ULONG)*pDecryptMem--;
		gostdecrypt(in,out,Key);
		memcpy(pDecryptMem,out,8);
					
		pDecryptMem++;
		pDecryptMem++;
#ifdef _CRYPTER_
		if((i % 32) != 0)
			printf("..");
		else printf("\n");	
#endif
	}
	return pFileStor;
}

PVOID CryptBuffer(PVOID pMem,ULONG nSize)
{
	ULONG_PTR pOutBuffer = NULL;
	ULONG nAlign ;
	ULONG nOutBufferSize ;
	PFileStorage pStorage = NULL;
	ULONG i = 0;
	ULONG in[2],out[2];
	
	nAlign = nSize % 8;
	nOutBufferSize = nSize;
	while(nAlign != 0)
	{
		nOutBufferSize += 1;
		nAlign = nOutBufferSize % 8;
	}
	kboxinit();
	printf("[+] Append size [ %d ] , Output buffer size [ %d ], File size [ %d ]\n",nAlign,nOutBufferSize + sizeof(_FILE_STORAGE),nSize);
	pOutBuffer = (ULONG_PTR)malloc(nOutBufferSize + sizeof(_FILE_STORAGE));
	if(!pOutBuffer)
	{
		printf("[-] Error. Cant allocate memory for buffer\n");
	}	else
		printf("[+] Memory allocated [ %d ] bytes\n",nOutBufferSize + sizeof(_FILE_STORAGE));

	memset(pOutBuffer,0,nOutBufferSize + sizeof(_FILE_STORAGE));
	pStorage = (PFileStorage)pOutBuffer;
	for(i = 0;i < 8; i++)
		pStorage->nKeyArray[i] = nKeyArray[i];
	pStorage->FileSize = nSize;
	pStorage->BufferSize = nOutBufferSize;

	pOutBuffer = (ULONG_PTR)((ULONG)pStorage + sizeof(FileStorage));
	memcpy((PVOID)(pOutBuffer),pMem,nSize);
	
	printf("[+] Start crypt data : \n");

	i = nOutBufferSize / 8;
	for( i = 0; i <= nOutBufferSize / 8; i++ )
	{
		//printf("0x%08X : 0x%08X\n",*pOutBuffer,*pOutBuffer+1);
		in[0] = (ULONG)*pOutBuffer;
		(ULONG)*pOutBuffer++;
		in[1] = (ULONG)*pOutBuffer;
		(ULONG)*pOutBuffer--;
		gostcrypt(in,out,nKeyArray);
		memcpy(pOutBuffer,out,8);
					
		pOutBuffer++;
		pOutBuffer++;
		if((i % 16) != 0)
			printf("%02X ",(unsigned char)rand());
		else {
			printf("\n");
			Sleep(50);
		}
	}
	printf("\n");
	return pStorage;
}

int main(int argc, char* argv[])
{
	PVOID pBuff = NULL;
	PVOID pOutBuff = NULL;
	ULONG nSize = 0;
	PFileStorage pFileStor = 0,pFileStor2 = 0;

	if(argc < 3)
	{
		printf("Usage %s file.sys\\bin\\exe\\dll output_name.c\n",argv[0]);
		exit(-1);
	}

	// файл открыт + буфер прочитан	
	pBuff = OpenAndRead(argv[1],&nSize);
	// рандом сгенерирован
	GenerateRandomKey();
	// криптуем
	pFileStor = (PFileStorage)CryptBuffer(pBuff,nSize);

	FILE *fp = fopen(argv[2],"wb+");
	
	nSize = pFileStor->BufferSize + sizeof(_FILE_STORAGE);
	if(fwrite(pFileStor,1,nSize,fp) != nSize)
	{
		printf("[-] Error write buffer to output file [ %s ]\n",argv[2]);
	}	else
		printf("[+] Crypted data writed to %s.Done.\n",argv[2]);
	
	fclose(fp);
	printf("[+] All done.\n");
/*
	
	char cmd[500] = { 0 };
	strcpy(cmd,"bin2text.exe c ");
	strcat(cmd,argv[2]);
	strcat(cmd," ");
	strcat(cmd,argv[2]);
	printf("[+] All done, start convert from bin to text : %s\n",cmd);
	system(cmd);*/
	return 0;
}
