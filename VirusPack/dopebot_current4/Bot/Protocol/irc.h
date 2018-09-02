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

void irc_action(SOCKET bsock, char *szAction, char *szParameter);
void irc_disconnect(SOCKET bsock, WSAEVENT event);
void irc_join(SOCKET bsock, char *szChannel, char *szChannelPassword, bool bOSChannel);
void irc_msg(SOCKET bsock, char *szAction, char *szDestination, char *szMessage);
void irc_userinfo(SOCKET bsock, char *szBotNick, char *szServer, char *szServerPassword);
void line_parse(SOCKET bsock, WSAEVENT event, char *szBuffer);