#include "includes.h"
#include "extern.h"

DWORD __forceinline IsInsideVPC_exceptionFilter(LPEXCEPTION_POINTERS ep)
{
  PCONTEXT ctx = ep->ContextRecord;
  ctx->Ebx = -1;						// Not running VPC
  ctx->Eip += 4;						// skip past the "call VPC" opcodes
  return EXCEPTION_CONTINUE_EXECUTION;
}

bool DetectVPC()
{
	bool bVPCIsPresent = FALSE;

	__try
	{
		_asm push ebx
		_asm mov  ebx, 0 // It will stay ZERO if VPC is running
		_asm mov  eax, 1 // VPC function number
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
			mov    ebx, 0		// any value but not the MAGIC VALUE
			mov    ecx, 10		// get VMWare version
			mov    edx, 'VX'	// port number

			in     eax, dx		// read port
				 				// on return EAX returns the VERSION
			cmp    ebx, 'VMXh'	// is it a reply from VMWare?
			setz   [bVMWareIsPresent]	// set return value

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

bool DetectAnubis()
{
	char szBotFile[MAX_PATH];
	bool bAnubisIsPresent = FALSE;

	if (strstr(szBotFile, "C:\\InsideTm\\"))
		bAnubisIsPresent = TRUE;



	return bAnubisIsPresent;
}

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

