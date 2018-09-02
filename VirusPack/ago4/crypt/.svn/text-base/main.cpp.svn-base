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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{	if(argc<4) { fprintf(stderr, "Usage: %s <hex/text> <cryptkey> <string>\n", argv[0]); return 1; }
	int iStrLen=strlen(argv[3]); int iKey=atoi(argv[2]);

	for(char i=0; i<iStrLen; i++) argv[3][i]=argv[3][i]^(iKey+(i*(iKey%10)+1));

	if(strstr(argv[1], "hex"))
	{	for(int i=0;i<iStrLen;i++) printf("\\x%2.2X", (unsigned char)argv[3][i]); printf("\n"); }
	else
		printf("%s\n", argv[3]);
		
	return 0; }
