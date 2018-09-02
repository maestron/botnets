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

CCmdLine::CCmdLine() { m_szCmdLine=NULL; }
CCmdLine::~CCmdLine() { if(m_szCmdLine) free(m_szCmdLine); }

void CCmdLine::Parse(const char *szCmdLine)
{	// Copy command line
	char *szCmdLineCopy; if(m_szCmdLine) free(m_szCmdLine);
	m_szCmdLine=(char*)malloc(strlen(szCmdLine)+1); strcpy(m_szCmdLine, szCmdLine);

	// Create defaults
#ifndef _DEBUG
	m_cConfig.bDebug=false; m_cConfig.iDebugLevel=0;
#else
	m_cConfig.bDebug=true; m_cConfig.iDebugLevel=10;
#endif

	m_cConfig.bUpdate=false;
	
	// Tokenize command line
	szCmdLineCopy=(char*)malloc(strlen(m_szCmdLine)+1); strcpy(szCmdLineCopy, m_szCmdLine);
	int iLoop=0; char *szCmdLineTok[256]; szCmdLineTok[0]=strtok(szCmdLineCopy, " ");
	for(iLoop=1;iLoop<256;iLoop++) szCmdLineTok[iLoop]=strtok(NULL, " ");

	// Scan command line tokens for params
	iLoop=0; while(szCmdLineTok[iLoop])
	{	if(!strcmp(szCmdLineTok[iLoop], "-debug")) // Set the debug mode to enabled
		{	m_cConfig.bDebug=true; }
		else if(!strcmp(szCmdLineTok[iLoop], "-debuglevel")) // Set the debug level to value
		{	if(szCmdLineTok[iLoop+1]) m_cConfig.iDebugLevel=atoi(szCmdLineTok[iLoop+1]); iLoop++; }
		else if(!strcmp(szCmdLineTok[iLoop], "-update"))
		{	m_cConfig.bUpdate=true; }
		iLoop++; }

	// Zero debug level if not debugging
	if(!m_cConfig.bDebug) m_cConfig.iDebugLevel=0;
	// Lowest debug level as default
	if(!m_cConfig.iDebugLevel && m_cConfig.bDebug) m_cConfig.iDebugLevel=1;

#ifndef DBGCONSOLE
	m_cConfig.bDebug=0; m_cConfig.iDebugLevel=0;
#endif
}
