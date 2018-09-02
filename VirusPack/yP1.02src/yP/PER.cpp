/* PER.cpp --

   This file is part of the "yoda's Protector".

   Copyright (C) 2004-2005 Ashkbiz Danehkar
   Copyright (C) 2000-2001 yoda/FReAK2FReAK
   All Rights Reserved.

   yoda's Protector library are free software; you can redistribute them
   and/or modify them under the terms of the GNU General Public License as
   published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYRIGHT.TXT.
   If not, write to the Free Software Foundation, Inc.,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   Ashkbiz Danehkar
   <ashkbiz@yahoo.com>
*/
#include "stdafx.h"
#include "yP.h"
#include "PER.h"
#include <stdlib.h>
#include <time.h>
#include <list>
#include <commctrl.h>

#ifdef _DEBUG
#define DEBUG_NEW
#endif

bool ProceedBar=TRUE;

void InitRandom();
void _ror(DWORD *Value,UCHAR Shift);
void _rol(DWORD *Value,UCHAR Shift);
DWORD random(DWORD dwRange);
void EncryptBuff(char* Base,DWORD dwRV,DWORD Size);
void MakePER(char* pDecryptBuff,DWORD dwSize);

// -> Polymorphic En-/Decryption routine generator for per byte encryption <-
// by yoda
//---- STRUCTs ----
// RandNumType:
// 0 - no random num needed
// 1 - 3th byte must be a random number
// 2 - 2nd byte must be a random number
struct sPERTable{
	DWORD dwSize;
	DWORD dwEncrypt;
	DWORD dwDecrypt;
	DWORD RandNumType;
}; 
//----- EQUs -----
#define PERItems	20//24
//----- CONST ----
// all opcodes are in reverse order
const sPERTable PERTable[PERItems]={
	{0x01,
	 0x90,		// NOP
	 0x90,		// NOP
	 0x00},		   

	{0x01,
	 0xF9,		// STC
	 0xF9,		// STC
	 0x00},		   

	{0x01,
	 0xF8,		// CLC
	 0xF8,		// CLC
	 0x00},

	{0x02,
	 0xC0FE,	// INC  AL
	 0xC8FE,	// DEC  AL
	 0x00},

/*	{0x02,
	 0xC8FE,	// DEC  AL
	 0xC0FE,	// INC  AL
	 0x00},

	{0x02,
	 0xC3FE,	// INC  BL
	 0xCBFE,	// DEC  BL
	 0x00},


	{0x02,
	 0xC302,	// ADD  AL,BL
	 0xC32A,	// SUB	AL,BL
	 0x00},

	{0x02,
	 0xC32A,	// SUB	AL,BL
	 0xC302,	// ADD  AL,BL
	 0x00},*/

	{0x02,
	 0x0004,	// ADD AL, 0
	 0x002C,	// SUB AL, 0
	 0x02},

	{0x02,
	 0x002C,	// SUB AL, 0
	 0x0004,	// ADD AL, 0
	 0x02},

	{0x02,
	 0xC102,	// ADD AL, CL
	 0xC12A,	// SUB AL, CL
	 0x00},

	{0x02,
	 0xC12A,	// SUB AL, CL
	 0xC102,	// ADD AL, CL
	 0x00},

	{0x02,
	 0x0034,	// XOR AL, 0
	 0x0034,	// XOR AL, 0
	 0x02},

	{0x03,
	 0x00C8C0,	// ROR  AL, 0
	 0x00C0C0,	// ROL  AL, 0
	 0x01},

	{0x03,
	 0x00C0C0,	// ROL  AL, 0
	 0x00C8C0,	// ROR  AL, 0
	 0x01},		   

	{0x03,
	 0xE801EB,	// Self modifing
	 0xE801EB,	// Self modifing
	 0x00},		   

	{0x03,
	 0xE901EB,	// Self modifing
	 0xE901EB,	// Self modifing
	 0x00},		   

	{0x03,
	 0xC201EB,	// Self modifing
	 0xC201EB,	// Self modifing
	 0x00},


	{0x03,
	 0xE801EB,	// Self modifing
	 0xE801EB,	// Self modifing
	 0x00},		   

	{0x03,
	 0xE901EB,	// Self modifing
	 0xE901EB,	// Self modifing
	 0x00},		   

	{0x03,
	 0xC201EB,	// Self modifing
	 0xC201EB,	// Self modifing
	 0x00},


	{0x03,
	 0xE801EB,	// Self modifing
	 0xE801EB,	// Self modifing
	 0x00},		   

	{0x03,
	 0xE901EB,	// Self modifing
	 0xE901EB,	// Self modifing
	 0x00},		   

	{0x03,
	 0xC201EB,	// Self modifing
	 0xC201EB,	// Self modifing
	 0x00}
};

struct TCommandCode
{
	DWORD OpCode;
	UCHAR Data;
};

using namespace std;
list <TCommandCode> Encodenode,Decodenode;
list <TCommandCode>::iterator Iter;

UCHAR regAL,regBL;

//------- CODE ---------
void SwapDW(DWORD Value1,DWORD Value2)
{
	DWORD Value=Value1;
	Value1=Value2;
	Value2=Value;
}

void _ror(DWORD *Value,UCHAR Shift)
{
	DWORD _Value=*Value;
	_asm
	{
		XOR ECX,ECX
		MOV CL,Shift
		MOV EAX,_Value
		ROR EAX,CL
		MOV _Value,EAX
	}
	*Value=_Value;
}

void _rol(DWORD *Value,UCHAR Shift)
{
	DWORD _Value=*Value;
	_asm
	{
		XOR ECX,ECX
		MOV CL,Shift
		MOV EAX,_Value
		ROL EAX,CL
		MOV _Value,EAX
	}
	*Value=_Value;
}

DWORD random(DWORD dwRange)
{
	// generate new random number
	DWORD RValue= rand();
	// force dwRange//the last rang is RAND_MAX
	DWORD rand_by_rang=RValue%dwRange;
	return(rand_by_rang);
}

//srand should only called one time !!!
void InitRandom()
{
	//manage the random generator //srand(GetTickCount());
	srand((unsigned)time(NULL));
}
//----------------------------------------------------------------
UCHAR EncodeRoutine(UCHAR Value,UCHAR Count)
{
	regAL=Value;
	UCHAR _Data;
	TCommandCode command;
	for(Iter=Encodenode.begin();Iter!=Encodenode.end();Iter++)
	{
		command=*Iter;
		_Data=command.Data;
		switch(command.OpCode)
		{
		case 0xC0FE:	// INC  AL
			_asm
			{
				INC regAL
			}
			break;

/*		case 0xC8FE:	// DEC  AL
			_asm
			{
				DEC regAL
			}
			break;

		case 0xC3FE:	// INC  BL
			_asm
			{
				INC regBL
			}
			break;

		case 0xC302:	// ADD  AL,BL
			_asm
			{
				MOV CL,regBL
				ADD regAL,CL
			}
			break;

		case 0xC32A:	// SUB	AL,BL
			_asm
			{
				MOV CL,regBL
				SUB regAL,CL
			}
			break;*/

		case 0x0004:	// ADD AL, 0
			_asm
			{
				MOV CL,_Data
				ADD regAL,CL
			}
			break;

		case 0x002C:	// SUB AL, 0
			_asm
			{
				MOV CL,_Data
				SUB regAL,CL
			}
			break;

		case 0xC102:	// ADD AL, CL
			_asm
			{
				MOV CL,Count
				ADD regAL,CL
			}
			break;

		case 0xC12A:	// SUB AL, CL
			_asm
			{
				MOV CL,Count
				SUB regAL,CL
			}
			break;

		case 0x0034:	// XOR AL, 0
			_asm
			{
				MOV CL,_Data
				XOR regAL,CL
			}
			break;

		case 0x00C8C0:	// ROR  AL, 0
			_asm
			{
				MOV CL,_Data
				ROR regAL,CL
			}
			break;

		case 0x00C0C0:	// ROL  AL, 0
			_asm
			{
				MOV CL,_Data
				ROL regAL,CL
			}
			break;
		}
	}
	return(regAL);
}
//----------------------------------------------------------------
/*UCHAR DecodeRoutine(UCHAR Value,UCHAR Count)
{
	UCHAR regAL=Value;
	UCHAR regBL=0;
	UCHAR _Data;
	TCommandCode command;
	for(Iter=Decodenode.begin();Iter!=Decodenode.end();Iter++)
	{
		command=*Iter;
		_Data=command.Data;
		switch(command.OpCode)
		{
		case 0xC8FE:	// DEC  AL
			_asm
			{
				DEC regAL
			}
			break;

		case 0xC0FE:	// INC  AL
			_asm
			{
				INC regAL
			}
			break;

		case 0xCBFE:	// DEC  BL
			_asm
			{
				INC regBL
			}
			break;

		case 0xC32A:	// SUB	AL,BL
			_asm
			{
				MOV CL,regBL
				SUB regAL,CL
			}
			break;

		case 0xC302:	// ADD  AL,BL
			_asm
			{
				MOV CL,regBL
				ADD regAL,CL
			}
			break;

		case 0x002C:	// SUB AL, 0
			_asm
			{
				MOV CL,_Data
				SUB regAL,CL
			}
			break;

		case 0x0004:	// ADD AL, 0
			_asm
			{
				MOV CL,_Data
				ADD regAL,CL
			}
			break;

		case 0xC12A:	// SUB AL, CL
			_asm
			{
				MOV CL,Count
				SUB regAL,CL
			}
			break;

		case 0xC102:	// ADD AL, CL
			_asm
			{
				MOV CL,Count
				ADD regAL,CL
			}
			break;

		case 0x0034:	// XOR AL, 0
			_asm
			{
				MOV CL,_Data
				XOR regAL,CL
			}
			break;

		case 0x00C0C0:	// ROL  AL, 0
			_asm
			{
				MOV CL,_Data
				ROL regAL,CL
			}
			break;

		case 0x00C8C0:	// ROR  AL, 0
			_asm
			{
				MOV CL,_Data
				ROR regAL,CL
			}
			break;
		}
	}
	return(regAL);
}*/
//----------------------------------------------------------------
void EncryptBuff(char* Base,DWORD dwRVA,DWORD dwSize)
{
	UCHAR _temp;
	DWORD dwStep=1;
	if(ProceedBar)
	{
		dwStep=dwSize/100;
		SendDlgItemMessage(hwndMain,IDC_PROGRESS1,PBM_SETSTEP,1,0);
		SendDlgItemMessage(hwndMain,IDC_PROGRESS1,PBM_SETPOS,0,0);
	}
	UCHAR count=UCHAR(dwSize);
	regBL=0;
	for(DWORD i=0;i<dwSize;i++)
	{
		if(ProceedBar)
		{
			if((i%dwStep)==0)
			{
				SendDlgItemMessage(hwndMain,IDC_PROGRESS1,PBM_SETPOS,DWORD((i+1)/dwStep),0);
			}
		}
		CopyMemory(&_temp,Base+dwRVA+i,1);//_temp=Base[dwRV+i];
		_temp=EncodeRoutine(_temp,count);
		CopyMemory(Base+dwRVA+i,&_temp,1);//Base[dwRV+i]=_temp;
		count--;
	}
	DWORD WW=regBL;
}
//----------------------------------------------------------------
/*void DecryptBuff(char* Base,DWORD dwRVA,DWORD dwSize)
{
	UCHAR _temp;
	UCHAR count=UCHAR(dwSize);
	for(DWORD i=0;i<dwSize;i++)
	{
		CopyMemory(&_temp,Base+dwRVA+i,1);//_temp=Base[dwRV+i];
		_temp=DecodeRoutine(_temp,count);
		CopyMemory(Base+dwRVA+i,&_temp,1);//Base[dwRV+i]=_temp;
		count--;
	}	
}*/
//----------------------------------------------------------------
void MakePER(char* pDecryptBuff,DWORD dwSize)
{
	DWORD dwCurRandNum;
	DWORD dwRandom;
	DWORD _dwSize=dwSize;
	sPERTable pertable;
	TCommandCode DecodeCommand,EncodeCommand;
	// prepare some things
	char* pENC=new TCHAR[_dwSize];//-> EncryptBuffer will be filled from down to top
	char* pDEC=new TCHAR[_dwSize];//-> DecryptBuffer	
	// generate !
	int dwENC,dwDEC;
	dwENC=_dwSize;
	dwDEC=0;
	Encodenode.clear();
	Decodenode.clear();
	do
	{
		// get a random PER Item
		dwRandom=random(PERItems);
		pertable=PERTable[dwRandom];
		if(pertable.dwSize<=_dwSize)// check if this item is too big
		{
			//---- past the Opcode ----
			//-> encryption buffer
			if(((pertable.dwSize==1)||(pertable.dwSize==2))&&(pertable.RandNumType==0))
			{
				EncodeCommand.Data=0;
				EncodeCommand.OpCode=pertable.dwEncrypt;
				Encodenode.push_front(EncodeCommand);
				DecodeCommand.Data=0;
				DecodeCommand.OpCode=pertable.dwDecrypt;
				Decodenode.push_back(DecodeCommand);
			}
			if((pertable.RandNumType==1)||(pertable.RandNumType==2))
			{
				// generate the random num
				dwRandom=random(0xF8);
				dwRandom++;// avoid 0 !
				// update variables/pointers
				dwCurRandNum=dwRandom&0x000000FF;
				EncodeCommand.Data=UCHAR(dwCurRandNum);
				EncodeCommand.OpCode=pertable.dwEncrypt;
				Encodenode.push_front(EncodeCommand);
				DecodeCommand.Data=UCHAR(dwCurRandNum);
				DecodeCommand.OpCode=pertable.dwDecrypt;
				Decodenode.push_back(DecodeCommand);
				if(pertable.RandNumType==1) _rol(&dwCurRandNum,16);
				else _rol(&dwCurRandNum,8);
				//-> decryption buffer
				pertable.dwEncrypt=pertable.dwEncrypt | dwCurRandNum;
				pertable.dwDecrypt=pertable.dwDecrypt | dwCurRandNum;

			}
			CopyMemory(pDEC+dwDEC,&pertable.dwDecrypt,pertable.dwSize);
			dwDEC= dwDEC + pertable.dwSize;
			dwENC= dwENC - pertable.dwSize;
			CopyMemory(pENC+dwENC,&pertable.dwEncrypt,pertable.dwSize);			  
			_dwSize=_dwSize-pertable.dwSize;
		}
	}while(_dwSize!=0);
	//CopyMemory(pEncryptBuff,pENC,dwSize);//-> EncryptBuffer
	CopyMemory(pDecryptBuff,pDEC,dwSize);//-> DecryptBuffer
}
