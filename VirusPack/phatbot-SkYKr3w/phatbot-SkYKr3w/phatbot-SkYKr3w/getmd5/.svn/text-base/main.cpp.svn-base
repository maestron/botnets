/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

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

#include <stdio.h>
#include <string.h>
#include "global.h"
#include "md5.h"

int main(int argc, char **argv)
{	if(!argv[1]) return 1;
	MD5_CTX md5; MD5Init(&md5); unsigned char szMD5[16];
	MD5Update(&md5, (unsigned char*)argv[1], strlen(argv[1]));
	MD5Final(szMD5, &md5);

	printf("MD5 of \"%s\" is \"", argv[1]);
	
	for(int i=0;i<16;i++)
		printf("%2.2X", szMD5[i]);
	
	printf("\"\n");
	
	return 0; };
