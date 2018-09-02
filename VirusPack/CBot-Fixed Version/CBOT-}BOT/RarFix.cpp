#include "include.h"
#include "externs.h"

#pragma pack(push, 1)

typedef struct RAR_FILE_HEADER
{
	WORD	HEAD_CRC;
	BYTE	HEAD_TYPE;
	WORD	HEAD_FLAGS;
	WORD	HEAD_SIZE;
	DWORD	PACK_SIZE;
	DWORD	UNP_SIZE;
	BYTE	HOST_OS;
	DWORD	FILE_CRC;
	DWORD	FTIME;
	BYTE	UNP_VER;
	BYTE	METHOD;
	WORD	NAME_SIZE;
	DWORD	ATTR;
}RarFileHeader;

#pragma pack(pop)

DWORD crc32(void *xdata,int xsize) 
{
	HGLOBAL crc32table;
	DWORD retvalue;
	crc32table=GlobalAlloc(GPTR,0x400);
	if(crc32table!=NULL)
	{
		__asm
		{
			;build crc32 table
			;---------------------
			mov		edi,crc32table
			xor		ecx,ecx
	L2:		push	ecx
			mov		eax,ecx
			mov		ecx,8h
	L1:		mov		edx,eax
			and		edx,1h
			jne		equ_1
			shr		eax,1h
			jmp		__1
	equ_1:  shr		eax,1h
			xor		eax,0edb88320h ;polynomial
	__1:    loop	L1
			stosd
			pop		ecx
			inc		ecx
			cmp		ecx,100h
            jb		L2
			;calc crc32 checksum
			;-------------------
			mov		esi,xdata
			mov		edi,xsize
			xor		ecx,ecx
			mov		ebx,0ffffffffh
	crc:	push	ecx
			xor		eax,eax
			lodsb
			mov		edx,ebx
			shr		ebx,8h
			push	ebx
			xchg	edx,ebx
			and		ebx,0ffh
			xor		ebx,eax
			xchg	eax,ebx
			mov		ecx,4h
			mul		ecx
			xchg	eax,ebx
			mov		eax,crc32table
			add		eax,ebx
			mov		eax,dword ptr [eax]
			pop		ebx
			xor		eax,ebx
			mov		ebx,eax
			pop		ecx
			inc		ecx
			cmp		ecx,edi
			jb		crc
			not		eax
			mov		retvalue,eax
		}
		GlobalFree(crc32table);
		return(retvalue);
	}
	return 0;
}


BOOL AddToRar(char RarFile[],char FileToAdd[],char PackedFileName[],DWORD Attributes)
{

	unsigned char RarMainHeader[20] = // Rar_MARK_HEAD & Rar_MAIN_HEAD
	{
		0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x00, 0xCF, 0x90, 0x73,
		0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	} ;

	unsigned char EndOfRar[7]=
	{
		0xC4, 0x3D, 0x7B, 0x00, 0x40, 0x07, 0x00,
	};

	HANDLE hrarfile,hfile,hmap,mapbase;

	DWORD IO_Buffer,FileSize,RarFileSize;

	RarFileHeader RarHeader;

	char WorkBuffer[128],*WBp;

	hfile=CreateFile(FileToAdd,GENERIC_READ,FILE_SHARE_READ,0,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

	if(hfile==INVALID_HANDLE_VALUE)	
		return FALSE;


	FileSize=GetFileSize(hfile,NULL);

	if(FileSize==0xFFFFFFFF)
	{
		CloseHandle(hfile);
		return FALSE;
	}

	hrarfile=CreateFile(RarFile,GENERIC_WRITE,FILE_SHARE_READ,0,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

	if(hrarfile==INVALID_HANDLE_VALUE)
	{
		hrarfile=CreateFile(RarFile,GENERIC_WRITE,FILE_SHARE_READ,0,
		CREATE_NEW,FILE_ATTRIBUTE_NORMAL,0);

		if(hrarfile==INVALID_HANDLE_VALUE)		//if we fail exit
		{
			CloseHandle(hfile);
			return FALSE;
		}
		WriteFile(hrarfile,&RarMainHeader,sizeof(RarMainHeader),&IO_Buffer,NULL);

	}
	else
	{

		RarFileSize=GetFileSize(hrarfile,NULL);

		if(RarFileSize==0xFFFFFFFF)
		{
			CloseHandle(hfile);
			CloseHandle(hrarfile);
			return FALSE;
		}
		SetFilePointer(hrarfile,RarFileSize-sizeof(EndOfRar),NULL,FILE_BEGIN);
	}
	hmap=CreateFileMapping(hfile,NULL,PAGE_READONLY,NULL,NULL,NULL);

	if(hmap==NULL)				//fail ?
	{
		CloseHandle(hfile);
		CloseHandle(hrarfile);
		return FALSE;
	}

	mapbase=MapViewOfFile(hmap,FILE_MAP_READ,NULL,NULL,NULL);

	if(mapbase==NULL)			//fail ?
	{
		CloseHandle(hmap);
		CloseHandle(hfile);
		CloseHandle(hrarfile);
		return FALSE;
	}
	memset(&RarHeader,0,sizeof(RarHeader));			//zero struct

	RarHeader.HEAD_TYPE=0x74;
	RarHeader.FILE_CRC=crc32(mapbase,FileSize);		//calc & set the added file crc32
	RarHeader.HEAD_FLAGS=0x8000;
	RarHeader.METHOD=0x30;
	RarHeader.UNP_VER=0x14;
	RarHeader.ATTR=Attributes;
	RarHeader.UNP_SIZE=FileSize;
	RarHeader.PACK_SIZE=FileSize;
	RarHeader.NAME_SIZE=lstrlen(PackedFileName);
	RarHeader.HEAD_SIZE=(sizeof(RarHeader)+RarHeader.NAME_SIZE);
	memset(WorkBuffer,0,sizeof(WorkBuffer));
	memcpy(WorkBuffer,&RarHeader,sizeof(RarHeader));
	WBp=WorkBuffer;
	WBp+=sizeof(RarHeader);
	memcpy(WBp,PackedFileName,RarHeader.NAME_SIZE);
	crc32(WorkBuffer+2,sizeof(RarHeader)+RarHeader.NAME_SIZE-2);	//+2 = skip the HEAD_CRC field

	__asm
	{
		mov word ptr [RarHeader.HEAD_CRC],ax
	}
	WriteFile(hrarfile,&RarHeader,sizeof(RarHeader),&IO_Buffer,NULL);

	WriteFile(hrarfile,PackedFileName,RarHeader.NAME_SIZE,&IO_Buffer,NULL);

	WriteFile(hrarfile,mapbase,FileSize,&IO_Buffer,NULL);

	WriteFile(hrarfile,EndOfRar,sizeof(EndOfRar),&IO_Buffer,NULL);

	//close/unmap files

	UnmapViewOfFile(mapbase);
	CloseHandle(hmap);
	CloseHandle(hfile);
	CloseHandle(hrarfile);

	return TRUE;
}
