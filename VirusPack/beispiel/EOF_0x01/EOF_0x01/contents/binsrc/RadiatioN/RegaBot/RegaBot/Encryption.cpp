#include "stdafx.h"

char * CIRC::EncryptString(char *szString, int iShift, int iKey)
{
	//this function encrypts a string with key and shift
	int iLen=(int)strlen(szString);

	for(int i=0; i<iLen; i++)
	{
		szString[i]+=iShift;
		szString[i]=szString[i]^iKey;
		szString[i]+=iShift;
	}

	return szString;
}

char * CIRC::DecryptString(char *szString, int iShift, int iKey)
{
	//this function decrypts a string with shift and key
	int iLen=(int)strlen(szString);

	for(int i=0; i<iLen; i++)
	{
		szString[i]-=iShift;
		szString[i]=szString[i]^iKey;
		szString[i]-=iShift;		
	}

	return szString;
}

int CIRC::GetDay(void)
{
	//return day for encryption/decryption
	SYSTEMTIME SysTime;
	
	GetSystemTime(&SysTime);

	return SysTime.wDay;
}

int CIRC::GetMonth(void)
{
	//return month for encryption/decryption
	SYSTEMTIME SysTime;
	
	GetSystemTime(&SysTime);

	return SysTime.wMonth;
}