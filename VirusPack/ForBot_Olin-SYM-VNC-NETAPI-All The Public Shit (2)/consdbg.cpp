#include "main.h"
#include "mainctrl.h"
#include "consdbg.h"

#define LOGBUF_SIZE 8192

void CConsDbg::Init(int iDebugLevel){
#ifdef WIN32
	if(g_cMainCtrl.m_cCmdLine.m_cConfig.bDebug){
		AllocConsole(); m_hStdOut=GetStdHandle(STD_OUTPUT_HANDLE); m_hStdErr=GetStdHandle(STD_ERROR_HANDLE); }
#endif
	m_bEnabled=true; m_iDebugLevel=iDebugLevel; }

void CConsDbg::DeInit()
{
#ifdef WIN32
	if(g_cMainCtrl.m_cCmdLine.m_cConfig.bDebug)
	{	FreeConsole(); m_hStdOut=INVALID_HANDLE_VALUE; m_hStdErr=INVALID_HANDLE_VALUE; }
#endif
	m_bEnabled=false; }

#ifdef DBGCONSOLE
void CConsDbg::Log(int iDebugLevel, const char *logfmt, ...){
	va_list va_alist; char logbuf[LOGBUF_SIZE]; char logbuf2[LOGBUF_SIZE];
	va_start(va_alist, logfmt); vsprintf(logbuf2, logfmt, va_alist); va_end(va_alist);
	sprintf(logbuf, "[%d/%d] %s", iDebugLevel, m_iDebugLevel, logbuf2);

#ifdef _DEBUG
	FILE *fp=fopen("c:\\debugger.txt", "a");
	fprintf(fp, "%s", logbuf);
	fclose(fp);
#endif // _DEBUG

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
