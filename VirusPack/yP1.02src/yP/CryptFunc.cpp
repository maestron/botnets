/* CryptFunc.cpp --

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
#include "CryptVar.h"
#include "CryptFunc.h"
#include "PER.h"
#include <tlhelp32.h>
#include <Winbase.h>

#if(ANTIDEBUGACTIVE	== 1)
void AntiDebug();
#endif

void FillWithShit(char* Base,DWORD dwSize);
void GetEncryptRO(char* pFuncBody);
void GetOepJumpCodeRO(char* pFuncBody);
void OepJumpEncrypt(char* Base);
void CrypterPackerwithCall(char* pFuncBody,DWORD dwSize);

DWORD	dwRO_PackEncrypt;
DWORD   dwRO_VariableEncrypt;
DWORD   dwRO_SectionInfoEncrypt;
DWORD   dwRO_SectionEncrypt;
DWORD   dwRO_CODESectionEncrypt;
DWORD   dwRO_DATASectionEncrypt;
DWORD   dwRO_RSRCSectionEncrypt;
DWORD   dwRO_IDATASectionEncrypt;
DWORD   dwRO_EDATASectionEncrypt;
DWORD   dwRO_OEPEncrypt;
DWORD	dwRO_OEP_JUMP_CODE_START;
DWORD	dwRO_OEP_JUMP_CODE_END;
DWORD	OEP_JUMP_CODE_SIZE; 

//---------------------------------------------------------------------------
#if(ANTIDEBUGACTIVE	== 1)
void GetFileNameFromPath(char* szSource)
{
	char *szTemp=strrchr(szSource,'\\');	
	if(szTemp!=NULL)
	{
		szTemp++;
		DWORD l=DWORD(strlen(szTemp))+1;
		CopyMemory(szSource,szTemp,l);
	}
}

void AntiDebug()
{
	char lpszSystemInfo[MAX_PATH];
	HANDLE hSnapshot=NULL;
	DWORD PID_child;
	DWORD PID_parent;
	DWORD PID_explorer=0;
	HANDLE hh_parnet = NULL;
    PROCESSENTRY32	pe32 = {0};
	pe32.dwSize = sizeof(PROCESSENTRY32);//0x128;
    PID_child=GetCurrentProcessId();//getpid();
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if (Process32First(hSnapshot, &pe32))
    {
		while (Process32Next(hSnapshot, &pe32))
		{
			GetFileNameFromPath(pe32.szExeFile);
            CharUpperBuff(pe32.szExeFile,(DWORD)strlen(pe32.szExeFile));
            if(strcmp(pe32.szExeFile,"EXPLORER.EXE")==0)
            {
                if(PID_explorer==0)PID_explorer=pe32.th32ProcessID;
            }
			if(pe32.th32ProcessID==PID_child)
			{
				PID_parent=pe32.th32ParentProcessID;
			}
		}
	}
	if(IsDebuggerPresent())
	{
        hh_parnet= OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID_parent);
        TerminateProcess(hh_parnet, 0);
	}
	else
	{
		hh_parnet= OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID_parent);
		WaitForInputIdle(hh_parnet,INFINITE);
	}
//    if(PID_parent!=PID_explorer)
//    {
//        hh_parnet= OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID_parent);
//        TerminateProcess(hh_parnet, 0);
//    }
	/*else
	{
		MODULEENTRY32	me32 = {0};
		me32.dwSize = sizeof(MODULEENTRY32);
		hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,PID_explorer);
		if (Module32First(hSnapshot, &me32))
		{
		    do
            {
			    if(PID_explorer==me32.th32ProcessID)
			    {
					GetWindowsDirectory(lpszSystemInfo, MAX_PATH+1);
					CharUpperBuff(lpszSystemInfo,strlen(lpszSystemInfo));
					strcat(lpszSystemInfo,"\\");
					strcat(lpszSystemInfo,"EXPLORER.EXE");
					CharUpperBuff(me32.szExePath,strlen(me32.szExePath));
					if(strncmp(me32.szExePath,lpszSystemInfo,strlen(lpszSystemInfo)))
					{
						GetFileNameFromPath(me32.szExePath);
						if(strcmp(me32.szExePath,"EXPLORER.EXE")==0)
						{
							hh_parnet= OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID_explorer);
							TerminateProcess(hh_parnet, 0);
						}
					}
                }
            }while (Module32Next(hSnapshot, &me32));
		}
	}*/
}
#endif

//----- CONST ----
// all opcodes are in reverse order
struct sShitStruct{
	DWORD dwSize;
	DWORD dwShitOpCode;
}; 
//----- EQUs -----
#define ShitItems	12
const sShitStruct ShitTable[ShitItems]={
	{0x01,
	 0x90},		// NOP		   

	{0x01,
	 0xF9},		// STC
	   
	{0x01,
	 0xF8},		// CLC

	{0x03,
	 0xE801EB},	// Self modifing
	   
	{0x03,
	 0xE901EB},	// Self modifing
	   
	{0x03,
	 0xC201EB},	// Self modifing

	{0x03,
	 0xE801EB},	// Self modifing
   
	{0x03,
	 0xE901EB},	// Self modifing
		   
	{0x03,
	 0xC201EB},	// Self modifing

	{0x03,
	 0xE801EB},	// Self modifing
	   
	{0x03,
	 0xE901EB},	// Self modifing	   

	{0x03,
	 0xC201EB}	// Self modifing
};

//----------------------------------------------------------------
void FillWithShit(char* Base,DWORD dwSize)
{
	DWORD dwRandom;
	DWORD _dwSize=dwSize;
	sShitStruct shittable;
	DWORD dwPos=0;
	do
	{
		// get a random Shit Item
		dwRandom=random(ShitItems);
		shittable=ShitTable[dwRandom];
		if(shittable.dwSize<=_dwSize)// check if this item is too big
		{
			//---- past the Opcode ----
			CopyMemory(Base+dwPos,&shittable.dwShitOpCode,shittable.dwSize);
			dwPos= dwPos + shittable.dwSize;
			_dwSize=_dwSize-shittable.dwSize;
		}
	}while(_dwSize!=0);
}
//----------------------------------------------------------------
DWORD GetCallOpCodeRandom()
{
	DWORD dwRandom=random(9);
	switch(dwRandom)
	{
	case 0:return(0xE801EB);break;// Self modifing
	case 1:return(0xE901EB);break;// Self modifing
	case 2:return(0xC201EB);break;// Self modifing

	case 3:return(0xE801EB);break;// Self modifing
	case 4:return(0xE901EB);break;// Self modifing
	case 5:return(0xC201EB);break;// Self modifing

	case 6:return(0xE801EB);break;// Self modifing
	case 7:return(0xE901EB);break;// Self modifing
	case 8:return(0xC201EB);break;// Self modifing

	case 9:return(0xE801EB);break;// Self modifing
	}
	return(0x909090);
}
//----------------------------------------------------------------
//return Raw Data address of Loader Crypter Codes
void GetEncryptRO(char* pFuncBody)
{
	DWORD l=0;
	DWORD tmp;
	UCHAR _temp;
	do
	{
		CopyMemory(&_temp,pFuncBody+l,1);
		l++;
	}while(_temp==0xCC);
	l=l+4;
	do
	{
		CopyMemory(&tmp,pFuncBody+l,4);
		l++;
	}while(tmp!=0xCCCCCCCC);
	tmp=GetCallOpCodeRandom();
	tmp=(tmp<<8)|0x90;//0xC201EB90;
	CopyMemory(pFuncBody+l-1,&tmp,4);
	l=l+3;
	do
	{
		CopyMemory(&_temp,pFuncBody+l,1);
		l++;
	}while((_temp!=0xAC));
	dwRO_PackEncrypt=l;
	l=l+3;
	do
	{
		CopyMemory(&tmp,pFuncBody+l,4);
		l++;
	}while(tmp!=0xCCCCCCCC);
	tmp=GetCallOpCodeRandom();
	tmp=(tmp<<8)|0x90;//0xC201EB90;
	CopyMemory(pFuncBody+l-1,&tmp,4);
	l=l+3;
	do
	{
		CopyMemory(&_temp,pFuncBody+l,1);
		l++;
	}while((_temp!=0xAC));
	dwRO_VariableEncrypt=l;
	l=l+3;
	do
	{
		CopyMemory(&tmp,pFuncBody+l,4);
		l++;
	}while(tmp!=0xCCCCCCCC);
	tmp=GetCallOpCodeRandom();
	tmp=(tmp<<8)|0x90;//0xC201EB90;
	CopyMemory(pFuncBody+l-1,&tmp,4);
	l=l+3;
	do
	{
		CopyMemory(&_temp,pFuncBody+l,1);
		l++;
	}while((_temp!=0xAC));
	dwRO_SectionInfoEncrypt=l;
	l=l+3;
	do
	{
		CopyMemory(&tmp,pFuncBody+l,4);
		l++;
	}while(tmp!=0xCCCCCCCC);
	tmp=GetCallOpCodeRandom();
	tmp=(tmp<<8)|0x90;//0xC201EB90;
	CopyMemory(pFuncBody+l-1,&tmp,4);
	l=l+3;
	do
	{
		CopyMemory(&_temp,pFuncBody+l,1);
		l++;
	}while((_temp!=0xAC));
	dwRO_SectionEncrypt=l;
	l=l+3;
	do
	{
		CopyMemory(&tmp,pFuncBody+l,4);
		l++;
	}while(tmp!=0xCCCCCCCC);
	tmp=GetCallOpCodeRandom();
	tmp=(tmp<<8)|0x90;//0xC201EB90;
	CopyMemory(pFuncBody+l-1,&tmp,4);
	l=l+3;
	do
	{
		CopyMemory(&_temp,pFuncBody+l,1);
		l++;
	}while((_temp!=0xAC));
	dwRO_CODESectionEncrypt=l;
	l=l+3;
	do
	{
		CopyMemory(&tmp,pFuncBody+l,4);
		l++;
	}while(tmp!=0xCCCCCCCC);
	tmp=GetCallOpCodeRandom();
	tmp=(tmp<<8)|0x90;//0xC201EB90;
	CopyMemory(pFuncBody+l-1,&tmp,4);
	l=l+3;
	do
	{
		CopyMemory(&_temp,pFuncBody+l,1);
		l++;
	}while((_temp!=0xAC));
	dwRO_DATASectionEncrypt=l;
	l=l+3;
	do
	{
		CopyMemory(&tmp,pFuncBody+l,4);
		l++;
	}while(tmp!=0xCCCCCCCC);
	tmp=GetCallOpCodeRandom();
	tmp=(tmp<<8)|0x90;//0xC201EB90;
	CopyMemory(pFuncBody+l-1,&tmp,4);
	l=l+3;
	do
	{
		CopyMemory(&_temp,pFuncBody+l,1);
		l++;
	}while((_temp!=0xAC));
	dwRO_RSRCSectionEncrypt=l;
	l=l+3;
	do
	{
		CopyMemory(&tmp,pFuncBody+l,4);
		l++;
	}while(tmp!=0xCCCCCCCC);
	tmp=GetCallOpCodeRandom();
	tmp=(tmp<<8)|0x90;//0xC201EB90;
	CopyMemory(pFuncBody+l-1,&tmp,4);
	l=l+3;
	do
	{
		CopyMemory(&_temp,pFuncBody+l,1);
		l++;
	}while((_temp!=0xAC));
	dwRO_IDATASectionEncrypt=l;
	l=l+3;
	do
	{
		CopyMemory(&tmp,pFuncBody+l,4);
		l++;
	}while(tmp!=0xCCCCCCCC);
	tmp=GetCallOpCodeRandom();
	tmp=(tmp<<8)|0x90;//0xC201EB90;
	CopyMemory(pFuncBody+l-1,&tmp,4);
	l=l+3;
	do
	{
		CopyMemory(&_temp,pFuncBody+l,1);
		l++;
	}while((_temp!=0xAC));
	dwRO_EDATASectionEncrypt=l;
	l=l+3;
	do
	{
		CopyMemory(&tmp,pFuncBody+l,4);
		l++;
	}while(tmp!=0xCCCCCCCC);
	tmp=GetCallOpCodeRandom();
	tmp=(tmp<<8)|0x90;//0xC201EB90;
	CopyMemory(pFuncBody+l-1,&tmp,4);
	l=l+3;
	do
	{
		CopyMemory(&_temp,pFuncBody+l,1);
		l++;
	}while((_temp!=0xAC));
	dwRO_OEPEncrypt=l;
}
//----------------------------------------------------------------
//return Raw Data address of OEP JUMP Codes
void GetOepJumpCodeRO(char* pFuncBody)
{
	DWORD l=DEPACKER_CODE_SIZE-2;
	DWORD tmp;
	do
	{
		l--;
	}while(UCHAR(pFuncBody[l])==0xCC);
	l=l-4;
	do
	{
		CopyMemory(&tmp,pFuncBody+l,4);
		l--;
	}while(tmp!=0xCCCCCCCC);
	tmp=GetCallOpCodeRandom();
	tmp=(tmp<<8)|0x90;//0xC201EB90;
	CopyMemory(pFuncBody+l+1,&tmp,4);
	dwRO_OEP_JUMP_CODE_END=l;
	l=l-4;
	do
	{
		l--;
		CopyMemory(&tmp,pFuncBody+l,4);
	}while(tmp!=0xCCCCCCCC);
	tmp=GetCallOpCodeRandom();
	tmp=(tmp<<8)|0x90;//0xC201EB90;
	CopyMemory(pFuncBody+l,&tmp,4);
	l=l+4;
	dwRO_OEP_JUMP_CODE_START=l;
	OEP_JUMP_CODE_SIZE=dwRO_OEP_JUMP_CODE_END-dwRO_OEP_JUMP_CODE_START;
}
//----------------------------------------------------------------
// This functin encryptes the OEP JUMP Codes
void OepJumpEncrypt(char* Base)
{
	DWORD i;
	UCHAR _temp=0;
	UCHAR _tempC=UCHAR(OEP_JUMP_CODE_SIZE);
	for(i=dwRO_OEP_JUMP_CODE_START;i<=dwRO_OEP_JUMP_CODE_END;i++)
	{
		CopyMemory(&_temp,Base+i,1);
		_asm
		{
			MOV AL,_temp
   			ROR  AL, 2
   			ADD  AL, _tempC
   			XOR  AL, OEP_JUMP_ENCRYPT_NUM	
			MOV _temp,AL
			DEC _tempC
		}
		CopyMemory(Base+i,&_temp,1);
	}
}
//----------------------------------------------------------------
void CrypterPackerwithCall(char* pFuncBody,DWORD dwSize)
{
	DWORD l=0;
	DWORD64 tmp,tmp1;
	do
	{
		l++;
		CopyMemory(&tmp,pFuncBody+l,8);
		if(tmp==0x9090909090909090)
		{
			tmp=0x00000003E8;
			tmp1=GetCallOpCodeRandom();
			tmp1=tmp1<<40;
			tmp=tmp|tmp1;
			CopyMemory(pFuncBody+l,&tmp,8);
		}
	}while(l!=dwSize);
}
