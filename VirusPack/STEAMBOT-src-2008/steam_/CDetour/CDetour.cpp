/*
	CDetour 2.0 by Sinner, don't forget to credit me!

	Credits:
	LanceVorgin (his CDetour class) + z0mbie (ADE32)
*/
//modified by s0beit

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h> 
#include "CDetour.h"

void* CDetour::memcpy_s( void* pvAddress, const void* pvBuffer, size_t stLen )
{
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery( ( void* )pvAddress, &mbi, sizeof( mbi ) );
	VirtualProtect( mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect );
	void* pvRetn = memcpy( ( void* )pvAddress, ( void* )pvBuffer, stLen );
	VirtualProtect( mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect );
	FlushInstructionCache( GetCurrentProcess( ), ( void* )pvAddress, stLen );
	return pvRetn;
}

void *CDetour::Create(BYTE *orig, const BYTE *det, int iPatchType, int len)
{
	BYTE *jmp = NULL;
	int iMinLen = 0;

	// Get minimum bytes to overwrite
	if(iPatchType == DETOUR_TYPE_OBS_RAND)
		iPatchType = (rand() % (DetourRandTypeHigh - DetourRandTypeLow + 1) + DetourRandTypeLow);

	if(!(iMinLen = GetDetourLen(iPatchType)))
		return 0;

	if(len != 0 && len < iMinLen)
		return 0;

	// Try and find the end of the instruction automatically
	if(len == 0)
	{
		len = GetDetourLenAuto(orig, iMinLen);

		if(len < iMinLen)
			return 0;
	}

	if(!Detour(jmp, orig, det, iPatchType, len))
		return 0;

	IsHooked = true;
	return (jmp-len);
}

bool CDetour::PatchHook( void* pvPatchAddress, void* pvBuffer, int len )
{
	this->memcpy_s( pvPatchAddress, pvBuffer, ( size_t )len );
	if( *( BYTE* )pvPatchAddress == *( BYTE* )pvBuffer )
	{
		this->IsHooked = true;
	}
	return this->IsHooked;
}

bool CDetour::Detour(BYTE *&jmp, BYTE *&orig, const BYTE *&det, int iPatchType, int len)
{
	DWORD dwBack = 0;
	int i = 0;
	BYTE *pPatchBuf = NULL;

	// Allocate space for the jump
	jmp = (BYTE*)malloc(len+5);

	// Force page protection flags to read|write
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery( ( void* )orig, &mbi, sizeof( mbi ) );
	VirtualProtect( mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect );

	// Copy the overwritten opcodes at the original to the malloced space
	memcpy(jmp, orig, len);	
	
	// Increment to the end of the opcodes at the malloced space
	jmp += len;
	
	// Place a jump back to the original at this point
	jmp[0] = 0xE9;
	*(DWORD*)(jmp+1) = (DWORD)(orig+len - jmp) - 5;

	// Generate a random opcode
	int iTmpRnd = (rand() * 0xFF) + rand();
	BYTE bTmpRnd = (BYTE)iTmpRnd;

	// Place a jump at the original to the detour function
	pPatchBuf = new BYTE[len];
	
	// Pad out the bytes with NOPs so we don't have ends of intructions
	memset(pPatchBuf, 0x90, len);

	// Write the opcodes to the buffer according to patch type
	switch(iPatchType)
	{
		case DETOUR_TYPE_JMP:
			pPatchBuf[0] = '\xE9';
			*(DWORD*)&pPatchBuf[1] = (DWORD)(det - orig) - 5;
			break;

		case DETOUR_TYPE_PUSH_RET:
			pPatchBuf[0] = '\x68';
			*(DWORD*)&pPatchBuf[1] = (DWORD)det;
			pPatchBuf[5] = '\xC3';
			break;

		case DETOUR_TYPE_NOP_JMP:
			pPatchBuf[0] = '\x90';
			pPatchBuf[1] = '\xE9';
			*(DWORD*)&pPatchBuf[2] = (DWORD)(det - orig) - 6;
			break;

		case DETOUR_TYPE_NOP_NOP_JMP:
			pPatchBuf[0] = '\x90';
			pPatchBuf[1] = '\x90';
			pPatchBuf[2] = '\xE9';
			*(DWORD*)&pPatchBuf[3] = (DWORD)(det - orig) - 7;
			break;

		case DETOUR_TYPE_STC_JC:
			pPatchBuf[0] = '\xF9';
			pPatchBuf[1] = '\x0F';
			pPatchBuf[2] = '\x82';
			*(DWORD*)&pPatchBuf[3] = (DWORD)(det - orig) - 7;
			break;

		case DETOUR_TYPE_CLC_JNC:
			pPatchBuf[0] = '\xF8';
			pPatchBuf[1] = '\x0F';
			pPatchBuf[2] = '\x83';
			*(DWORD*)&pPatchBuf[3] = (DWORD)(det - orig) - 7;
			break;

		case DETOUR_TYPE_OBS_ADD:
			pPatchBuf[0] = '\xB8'; //mov eax
			*(DWORD*)&pPatchBuf[1] = iTmpRnd;
			pPatchBuf[5] = '\x05'; //add eax
			*(int*)&pPatchBuf[6] = (DWORD)det - iTmpRnd;
			pPatchBuf[10] = '\xFF'; //jmp eax
			pPatchBuf[11] = '\xE0';
			break;

		case DETOUR_TYPE_OBS_XOR:
			pPatchBuf[0] = '\x33'; //xor eax, eax
			pPatchBuf[1] = '\xC0';
			pPatchBuf[2] = '\x2D'; //sub eax
			*(int*)&pPatchBuf[3] = (int)iTmpRnd;
			pPatchBuf[7] = '\x35'; //xor eax
			*(DWORD*)&pPatchBuf[8] = (DWORD)det ^ (-iTmpRnd);
			pPatchBuf[12] = '\xFF'; //jmp eax
			pPatchBuf[13] = '\xE0';
			break;

		case DETOUR_TYPE_OBS_STACKADD:
			pPatchBuf[0] = '\x68'; //push
			*(DWORD*)&pPatchBuf[1] = (DWORD)iTmpRnd;
			pPatchBuf[5] = '\x81'; //xor dword ptr [esp]
			pPatchBuf[6] = '\x34';
			pPatchBuf[7] = '\x24';
			*(DWORD*)&pPatchBuf[8] = (DWORD)det ^ iTmpRnd;
			pPatchBuf[12] = '\xC3'; //ret
			break;

		case DETOUR_TYPE_OBS_ROR:
			while(!(bTmpRnd % 32))
			bTmpRnd = (BYTE)rand();
		
			__asm{
				pushad
				mov cl, bTmpRnd
				mov eax, det
				rol eax, cl
				mov dword ptr det, eax
				popad
			}

			pPatchBuf[0] = '\x51'; //push ecx
			pPatchBuf[1] = '\xB1'; //mov cl, 
			pPatchBuf[2] = bTmpRnd;
			pPatchBuf[3] = '\xB8'; //mov eax
			*(DWORD*)&pPatchBuf[4] = (DWORD)det;
			pPatchBuf[8] = '\xD3'; //ror eax, cl
			pPatchBuf[9] = '\xC8';
			pPatchBuf[10] = '\x59'; //pop ecx
			pPatchBuf[11] = '\xFF'; //jmp eax
			pPatchBuf[12] = '\xE0';
			break;

		case DETOUR_TYPE_OBS_ADDNOT:
			pPatchBuf[0] = '\xB8'; //mov eax
			*(DWORD*)&pPatchBuf[1] = iTmpRnd;
			pPatchBuf[5] = '\x05'; //add eax
			*(int*)&pPatchBuf[6] = (~(DWORD)det) - iTmpRnd;
			pPatchBuf[10] = '\xF7'; //not eax
			pPatchBuf[11] = '\xD0';
			pPatchBuf[12] = '\xFF'; //jmp eax
			pPatchBuf[13] = '\xE0';
			break;

		default:
			return false;
	}

	// Write the detour
	for(i=0; i<len; i++)
		orig[i] = pPatchBuf[i];

	// Put the old page protection flags back
	VirtualProtect( mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect );

	FlushInstructionCache( GetCurrentProcess( ), orig, len );

	return true;
}

bool CDetour::RestoreFunction( )
{
	if( !IsStored )return false;

	MEMORY_BASIC_INFORMATION mbi;
	bool bRet = false;
	VirtualQuery( ( void* )orig_bk, &mbi, sizeof( mbi ) );
	VirtualProtect( mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect );
	memcpy( ( void* )orig_bk, ( void* )bBackup, iBackSize );
	if( *( BYTE* )orig_bk == ( BYTE )bBackup[0] )
	{
		bRet = true;
	}else{
		bRet = false;
	}
	VirtualProtect( mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect );
	FlushInstructionCache( GetCurrentProcess( ), ( void* )orig_bk, iBackSize );
	IsHooked = false;

	return bRet;
}

bool CDetour::BackupFunction( BYTE* func, int iSize )
{
	iBackSize = iSize;
	bBackup = new BYTE[ iBackSize ];
	orig_bk = func;
	MEMORY_BASIC_INFORMATION mbi;
	bool bRet = false;
	VirtualQuery( ( void* )func, &mbi, sizeof( mbi ) );
	VirtualProtect( mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect );
	memcpy( ( void* )bBackup, ( void* )func, iBackSize );
	if( ( BYTE )bBackup[0] == *( BYTE* )func )
	{
		bRet = true;
	}else{
		bRet = false;
	}
	VirtualProtect( mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect );
	FlushInstructionCache( GetCurrentProcess( ), ( void* )func, iBackSize );
	IsStored = true;
	return bRet;
}

int CDetour::GetDetourLen(int iPatchType)
{
	switch(iPatchType)
	{
		case DETOUR_TYPE_JMP:
			return 5;

		case DETOUR_TYPE_PUSH_RET:
		case DETOUR_TYPE_NOP_JMP:
			return 6;
		
		case DETOUR_TYPE_NOP_NOP_JMP:
		case DETOUR_TYPE_STC_JC:
		case DETOUR_TYPE_CLC_JNC:
			return 7;

		case DETOUR_TYPE_OBS_ADD:
			return 12;

		case DETOUR_TYPE_OBS_STACKADD:
		case DETOUR_TYPE_OBS_ROR:
			return 13;

		case DETOUR_TYPE_OBS_XOR:
		case DETOUR_TYPE_OBS_ADDNOT:
			return 14;
		
		default:
			return 0;
	}
}

int CDetour::GetDetourLenAuto(BYTE *&orig, int iMinLen)
{
	int tmpLen = 0;
	BYTE *pCurOp = orig;
	
	while(tmpLen < iMinLen)
	{
		int i = oplen(pCurOp);
		
		if(i == 0 || i == -1)
			return false;

		tmpLen += i;
		pCurOp += i;
	}

	return tmpLen;
}

bool CDetour::bDataCompare( const BYTE* pData, const BYTE* bMask, const char* szMask )
{
    for( ; *szMask; ++szMask, ++pData, ++bMask )
	{
        if( *szMask == 'x' && *pData != *bMask ) 
		{
            return false;
		}
	}
    return ( *szMask ) == NULL;
}

DWORD CDetour::FindPattern( DWORD dwAddress, DWORD dwLen, BYTE *bMask, char* szMask )
{
    for( DWORD i=0; i < dwLen; i++ )
	{
		if( bDataCompare( ( BYTE* )( dwAddress + i ), bMask, szMask) )
		{
			return ( DWORD )( dwAddress + i );
		}
	}
    return 0;
}