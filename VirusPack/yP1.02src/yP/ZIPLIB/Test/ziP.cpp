/* lpack.c -- LZO example program: a simple file packer

   This file is part of the LZO real-time data compression library.

   Copyright (C) 1996-2002 Markus Franz Xaver Johannes Oberhumer
   All Rights Reserved.

   The LZO library is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   The LZO library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the LZO library; see the file COPYING.
   If not, write to the Free Software Foundation, Inc.,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   Markus F.X.J. Oberhumer
   <markus@oberhumer.com>
 */


/*************************************************************************
// NOTE: this is an example program, so do not use to backup your data
//
// This program lacks things like sophisticated file handling but is
// pretty complete regarding compression - it should provide a good
// starting point for adaption for you applications.
//
// Please study LZO.FAQ and simple.c first.
**************************************************************************/

#include "stdafx.h"
#include ".\Ziplib\lutil.h"
#include ".\Ziplib\lzo1x.h"
#include ".\Ziplib\lzo_conf.h"
#include <windows.h>

//#define LZO_999_UNSUPPORTED 0;

#define DICT_LEN	0xbfff
static lzo_byte		dict [ DICT_LEN ];
static lzo_uint		dict_len = 0;
static lzo_uint32	dict_adler32;
int r;
int level;

OPENFILENAME ofn;
BOOL fStatus;
char cFname[256];
char szCurDir[]=".";
char szFilter[]="ExE files (*.exe)|*.exe|All files (*.*)|*.*||";


HANDLE	hFile			= NULL;
DWORD	dwBytesRead		= 0;
DWORD	dwBytesWritten	= 0;
UCHAR	*pMemIn			= NULL;
UCHAR	*pMemOut		= NULL;
UCHAR	*wrkmem			= NULL;
DWORD	dwFsizeIn		= 0;
lzo_uint	dwFsizeOut	= 0;
UCHAR		*newb		=NULL;
lzo_uint	new_len		=0;


/*** DO NOT EDIT - GENERATED AUTOMATICALLY ***/
/*** Copyright (C) 1996-2002 Markus F.X.J. Oberhumer ***/
LZO_EXTERN_CDECL(int)decompress( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem /* NOT USED */ )
{
	int dwret;
/*	PUSH EBP	1
	MOV EBP,ESP 2
	PUSH EBX	1
	PUSH ESI	1
	PUSH EDI	1*/
_asm
{
	MOV EAX,NULL
	PUSH EAX
	MOV EAX,dst_len
	PUSH EAX
	MOV EAX,dst
	PUSH EAX
	MOV EAX,src_len
	PUSH EAX
	MOV EAX,src
	PUSH EAX
	CALL lzo1f_decompress_asm_fast_safe
	MOV dwret,EAX
	ADD ESP,000000CH
	JMP ENDOFPROC
//----------------------------------------------------------
//----------------------- DECOMPRESS -----------------------
/* asm.h -- library assembler function prototypes

   This file is part of the LZO real-time data compression library.

   Copyright (C) 1996-2002 Markus Franz Xaver Johannes Oberhumer
   All Rights Reserved.
   Markus F.X.J. Oberhumer
   <markus@oberhumer.com>
 */
//LZO_EXTERN_CDECL(int)
//lzo1f_decompress_asm_fast_safe
//				(const lzo_byte *src, lzo_uint  src_len,
//				 lzo_byte *dst, lzo_uintp dst_len,
//				 lzo_voidp wrkmem )
lzo1f_decompress_asm_fast_safe:
	PUSH EBP
	PUSH EDI
	PUSH ESI
	PUSH EBX
	PUSH ECX
	PUSH EDX
	SUB ESP,000000CH//SUB ESP,0000000CH
	CLD
	MOV ESI,DWORD PTR SS:[ESP+28H]//->sourc buffer
	MOV EDI,DWORD PTR SS:[ESP+30H]//->dispatch buffer
	MOV EBP,00000003H
	LEA EAX,DWORD PTR DS:[ESI-3H]
	ADD EAX,DWORD PTR SS:[ESP+2CH]//->source size
	MOV DWORD PTR SS:[ESP+4H],EAX
	MOV EAX,EDI
	LEA EDX,DWORD PTR SS:[ESP+34H]//->dispatch size //MOV
	ADD EAX,DWORD PTR DS:[EDX]

	MOV DWORD PTR SS:[ESP],EAX
	XOR EAX,EAX
	XOR EBX,EBX
	LODS BYTE PTR DS:[ESI]
	CMP AL,11H
	JBE L6
	SUB AL,0EH
	JMP L7
L3:	ADD EAX,000000FFH
	LEA EDX,DWORD PTR DS:[ESI+EAX+12H]
	CMP DWORD PTR SS:[ESP+4H],EDX
	JB L26
L4:	MOV BL,BYTE PTR DS:[ESI]
	INC ESI
	OR BL,BL
	JE L3
	LEA EAX,DWORD PTR DS:[EAX+EBX+15H]
	JMP L7
	LEA ESI,DWORD PTR DS:[ESI]
L5:	CMP DWORD PTR SS:[ESP+4H],ESI
	JB L26
	MOV AL,BYTE PTR DS:[ESI]
	INC ESI
L6:	CMP AL,10H
	JNB L9
	OR AL,AL
	JE L4
	ADD EAX,6H
L7:	LEA EDX,DWORD PTR DS:[EDI+EAX-3H]
	CMP DWORD PTR SS:[ESP],EDX
	JB L27
	LEA EDX,DWORD PTR DS:[ESI+EAX-3H]
	CMP DWORD PTR SS:[ESP+4H],EDX
	JB L26
	MOV ECX,EAX
	XOR EAX,EBP
	SHR ECX,02H
	AND EAX,EBP
L8:	MOV EDX,DWORD PTR DS:[ESI]
	ADD ESI,00000004H
	MOV DWORD PTR DS:[EDI],EDX
	ADD EDI,4H
	DEC ECX
	JNZ L8
	SUB ESI,EAX
	SUB EDI,EAX
	MOV AL,BYTE PTR DS:[ESI]
	INC ESI
	CMP AL,10H
	JNB L9
	LEA EDX,DWORD PTR DS:[EDI+3H]
	CMP DWORD PTR SS:[ESP],EDX
	JB L27
	SHR EAX,02H
	MOV BL,BYTE PTR DS:[ESI]
	LEA EDX,DWORD PTR DS:[EDI-801H]
	LEA EAX,DWORD PTR DS:[EAX+EBX*4H]
	INC ESI
	SUB EDX,EAX
	CMP EDX,DWORD PTR SS:[ESP+30H]//->dispatch buffer
	JB L28
	MOV ECX,DWORD PTR DS:[EDX]
	MOV DWORD PTR DS:[EDI],ECX
	ADD EDI,EBP
	JMP L16
	MOV ESI,ESI
L9:	CMP AL,40H
	JB L12
	MOV ECX,EAX
	SHR EAX,02H
	LEA EDX,DWORD PTR DS:[EDI-1H]
	AND EAX,00000007H
	MOV BL,BYTE PTR DS:[ESI]
	SHR ECX,05H
	LEA EAX,DWORD PTR DS:[EAX+EBX*8H]
	INC ESI
	SUB EDX,EAX
	ADD ECX,4H
	CMP EAX,EBP
	JNB L14
	JMP L17
L10:ADD EAX,000000FFH
	LEA EDX,DWORD PTR DS:[ESI+3H]
	CMP DWORD PTR SS:[ESP+4H],EDX//->dispatch buffer
	JB L26
L11:MOV BL,BYTE PTR DS:[ESI]
	INC ESI
	OR BL,BL
	JE L10
	LEA ECX,DWORD PTR DS:[EAX+EBX+24H]
	XOR EAX,EAX
	JMP L13
	NOP
L12:CMP AL,20H
	JB L20
	AND EAX,0000001fH
	JE L11
	LEA ECX,DWORD PTR DS:[EAX+5H]
L13:MOV AX,WORD PTR DS:[ESI]
	LEA EDX,DWORD PTR DS:[EDI-1H]
	SHR EAX,02H
	ADD ESI,02H
	SUB EDX,EAX
	CMP EAX,EBP
	JB L17
L14:CMP EDX,DWORD PTR SS:[ESP+30H]//->dispatch buffer
	JB L28
	LEA EAX,DWORD PTR DS:[EDI+ECX-3H]
	SHR ECX,02H
	CMP DWORD PTR SS:[ESP],EAX
	JB L27
L15:MOV EBX,DWORD PTR DS:[EDX]
	ADD EDX,00000004H
	MOV DWORD PTR DS:[EDI],EBX
	ADD EDI,00000004H
	DEC ECX
	JNZ L15
	MOV EDI,EAX
	XOR EBX,EBX
L16:MOV AL,BYTE PTR DS:[ESI-2H]
	AND EAX,EBP
	JE L5
	LEA EDX,DWORD PTR DS:[EDI+EAX]
	CMP DWORD PTR SS:[ESP],EDX
	JB L27
	LEA EDX,DWORD PTR DS:[ESI+EAX]
	CMP DWORD PTR SS:[ESP+4H],EDX
	JB L26
	MOV EDX,DWORD PTR DS:[ESI]
	ADD ESI,EAX
	MOV DWORD PTR DS:[EDI],EDX
	ADD EDI,EAX
	MOV AL,BYTE PTR DS:[ESI]
	INC ESI
	JMP L9
	LEA ESI,DWORD PTR DS:[ESI]
L17:CMP EDX,DWORD PTR SS:[ESP+30H]//->dispatch buffer
	JB L28
	LEA EAX,DWORD PTR DS:[EDI+ECX-3H]
	CMP DWORD PTR SS:[ESP],EAX
	JB L27
	XCHG ESI,EDX
	SUB ECX,EBP
	REP MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
	MOV ESI,EDX
	JMP L16
L18:ADD ECX,000000FFH
	LEA EDX,DWORD PTR DS:[ESI+3H]
	CMP DWORD PTR SS:[ESP+4H],EDX
	JB L26
L19:MOV BL,BYTE PTR DS:[ESI]
	INC ESI
	OR BL,BL
	JE L18
	LEA ECX,DWORD PTR DS:[EBX+ECX+0CH]
	JMP L21
	LEA ESI,DWORD PTR DS:[ESI]
L20:CMP AL,10H
	JB L22
	MOV ECX,EAX
	AND EAX,00000008H
	SHL EAX,0DH
	AND ECX,00000007H
	JE L19
	ADD ECX,00000005H
L21:MOV AX,WORD PTR DS:[ESI]
	ADD ESI,00000002H
	LEA EDX,DWORD PTR DS:[EDI+0FFFFC000H]
	SHR EAX,02H
	JE L23
	SUB EDX,EAX
	JMP L14
	LEA ESI,DWORD PTR DS:[ESI]
L22:LEA EDX,DWORD PTR DS:[EDI+2H]
	CMP DWORD PTR SS:[ESP],EDX
	JB L27
	SHR EAX,02H
	MOV BL,BYTE PTR DS:[ESI]
	LEA EDX,DWORD PTR DS:[EDI-1H]
	LEA EAX,DWORD PTR DS:[EAX+EBX*4H]
	INC ESI
	SUB EDX,EAX
	CMP EDX,DWORD PTR SS:[ESP+30H]//->dispatch buffer
	JB L28
	MOV AL,BYTE PTR DS:[EDX]
	MOV BYTE PTR DS:[EDI],AL
	MOV BL,BYTE PTR DS:[EDX+1H]
	MOV BYTE PTR DS:[EDI+1H],BL
	ADD EDI,00000002H
	JMP L16
L23:CMP ECX,00000006H
	SETNE AL
	CMP EDI,DWORD PTR SS:[ESP]
	JA L27
	MOV EDX,DWORD PTR SS:[ESP+28H]//->sourc buffer
	ADD EDX,DWORD PTR SS:[ESP+2CH]//->source size
	CMP ESI,EDX
	JA L26
	JB L25
L24:SUB EDI,DWORD PTR SS:[ESP+30H]//->dispatch buffer
	LEA EDX,DWORD PTR SS:[ESP+34H]//->dispatch size //MOV
	MOV DWORD PTR DS:[EDX],EDI
	NEG EAX
	ADD ESP,0CH
	POP EDX
	POP ECX
	POP EBX
	POP ESI
	POP EDI
	POP EBP
	RETN 8
	MOV EAX,00000001H
	JMP L24
L25:MOV EAX,00000008H
	JMP L24
L26:MOV EAX,00000004H
	JMP L24
L27:MOV EAX,00000005H
	JMP L24
L28:MOV EAX,00000006H
	JMP L24
ENDOFPROC:
	NOP
	}
	return(dwret);
}

/*************************************************************************
//
**************************************************************************/
int _tmain(int argc, _TCHAR* argv[])
//int main(int argc, char *argv[])
{
	// get a file path
	level=8;
	cFname[0]=0x00;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.hwndOwner=GetActiveWindow();
	ofn.lpstrFile=cFname;
	ofn.nMaxFile=sizeof(cFname);
	ofn.lStructSize=sizeof(ofn);
	ofn.lpstrFilter=TEXT("ExE files (*.exe)\0*.exe;All files (*.*)\0*.*\0\0");
	ofn.nFilterIndex = 1; 
	//ofn.lpstrInitialDir=szCurDir;
	ofn.Flags=OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_LONGNAMES | OFN_HIDEREADONLY;
	fStatus =GetOpenFileName(&ofn);//(LPOPENFILENAME
	if(!fStatus)
	{
		return 0;
	}

	hFile=CreateFile(cFname,
					 GENERIC_WRITE | GENERIC_READ,
					 FILE_SHARE_WRITE | FILE_SHARE_READ,
	                 NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	dwFsizeIn=GetFileSize(hFile,0);
	if(dwFsizeIn == 0)
	{
		CloseHandle(hFile);
		return 0;
	}
	pMemIn=(lzo_bytep) lzo_malloc(dwFsizeIn);
	if(pMemIn == NULL)
	{
		CloseHandle(hFile);
		return 0;
	}
	pMemOut=(lzo_bytep) lzo_malloc(dwFsizeIn + dwFsizeIn / 64 + 16 + 3);
	if(pMemOut == NULL)
	{
		CloseHandle(hFile);
		return 0;
	}

	newb=(lzo_bytep) lzo_malloc(dwFsizeIn);
	if(newb == NULL)
	{
		CloseHandle(hFile);
		return 0;
	}

	wrkmem=(lzo_bytep) lzo_malloc(LZO1X_999_MEM_COMPRESS);
	if(wrkmem == NULL)
	{
		CloseHandle(hFile);
		return 0;
	}

	ReadFile(hFile,pMemIn,dwFsizeIn,&dwBytesRead,NULL);


	
	r = lzo1x_999_compress_level(pMemIn,dwFsizeIn,
								 pMemOut,&dwFsizeOut,wrkmem,
	                             dict, dict_len, 0, level);
	/*r= lzo1x_1_compress(pMemIn,dwFsizeIn,
						pMemOut,&dwFsizeOut,wrkmem);*/


	if (r != LZO_E_OK)
	{
		/* this should NEVER happen */
		printf("internal error - compression failed: %d\n", r);
		return 1;
	}

	new_len=dwFsizeIn;
	r = decompress(pMemOut,dwFsizeOut,
				   newb,&new_len,NULL);

	if (r != LZO_E_OK)
	{
		/* this should NEVER happen */
		printf("internal error - compression failed: %d\n", r);
		return 1;
	}

	// ----- WRITE FILE MEMORY TO DISK -----
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	WriteFile(hFile,newb,new_len,&dwBytesWritten,NULL);
	
	// ------ FORCE CALCULATED FILE SIZE ------
	SetFilePointer(hFile,new_len,NULL,FILE_BEGIN);
	SetEndOfFile(hFile);

	// ----- CLEAN UP -----
	lzo_free(wrkmem);
//	lzo_free(newb);
	lzo_free(pMemIn);
	lzo_free(pMemOut);
	CloseHandle(hFile);
	return 0;
}


