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

#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "cstring.h"
#include "cmdbase.h"
#include "message.h"

using namespace std;

class CCommands : public CCommandHandler
{
public:
	CCommands();
	void RegisterCommand(command *pCommand, const char *szName, const char *szDescription, CCommandHandler *pHandler);
	command *FindCommandByName(const char *szName, bool bExact);

	bool HandleCommand(CMessage *pMsg);

	command m_cmdList;
protected:
	list<command*> m_lCommands;
};

#endif // __COMMANDS_H__
