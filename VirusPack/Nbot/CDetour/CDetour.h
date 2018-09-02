/*
	CDetour 2.0 by Sinner, don't forget to credit me!

	Credits:
	LanceVorgin (his CDetour class) + z0mbie (ADE32)
*/
//modified by s0beit

#pragma once

#pragma warning(disable: 4311)
#pragma warning(disable: 4312)

#include <windows.h>
#include <stdio.h>
#include "ADE32.h"

// I recommend you use DETOUR_TYPE_JMP to DETOUR_TYPE_CLC_JNC
typedef enum detour_types_s
{
	DETOUR_TYPE_NOT_SET = -1,
	DETOUR_TYPE_OBS_RAND,
	DETOUR_TYPE_JMP,
	DETOUR_TYPE_PUSH_RET,
	DETOUR_TYPE_NOP_JMP,
	DETOUR_TYPE_NOP_NOP_JMP,
	DETOUR_TYPE_STC_JC,
	DETOUR_TYPE_CLC_JNC,
	DETOUR_TYPE_OBS_ADD,
	DETOUR_TYPE_OBS_XOR,
	DETOUR_TYPE_OBS_STACKADD,
	DETOUR_TYPE_OBS_ROR,
	DETOUR_TYPE_OBS_ADDNOT,

} detour_types_t;

#define DetourRandTypeLow		DETOUR_TYPE_OBS_ADD
#define DetourRandTypeHigh		DETOUR_TYPE_OBS_ADDNOT

class CDetour
{
public:
	void *memcpy_s( void* pvAddress, const void* pvBuffer, size_t stLen );
	void *Create( BYTE *orig, const BYTE *det, int iPatchType, int len=0 );
	bool PatchHook( void* pvPatchAddress, void* pvBuffer, int len );
	bool BackupFunction( BYTE* func, int iSize );
	bool RestoreFunction( );

	DWORD FindPattern( DWORD dwAddress, DWORD dwLen, BYTE *bMask, char* szMask );

	BYTE *bBackup;
	int iBackSize;

	bool IsHooked;
	bool IsStored;

private:
	bool Detour(BYTE *&jmp, BYTE *&orig, const BYTE *&det, int iPatchType, int len);
	int GetDetourLen(int iPatchType);
	int GetDetourLenAuto(BYTE *&orig, int iMinLen);

	bool bDataCompare( const BYTE* pData, const BYTE* bMask, const char* szMask );

private:
	HMODULE m_hModule;
	DWORD m_dwAddress;
	BYTE* orig_bk;
};