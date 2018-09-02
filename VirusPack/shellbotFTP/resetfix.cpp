#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct {
	string sProcess;
	int iThreads;
	DWORD dwPID;
} PTINFO;

typedef struct {
	char *criticalProc;
} CRITICAL;

//! Critical process list
CRITICAL cProcesses[] = {
	{ "svchost.exe" },
	{ "System" },
	{ "explorer.exe" }
};

//! Check against any critical processes
bool CheckAgainstCriticals(string sProcess) {
	for(int p=0; p<sizeof(cProcesses)/sizeof(CRITICAL); p++) {
		if (strcmp(cProcesses[p].criticalProc, sProcess.c_str()) == 0)
			return false;
	}
	return true;
}

//! Kill any process that runs more than 30 threads
void FindAndDestroy(vector<PTINFO> processInfo) {
	for(vector<PTINFO>::iterator i = processInfo.begin(); i != processInfo.end(); i++) {		
		if ((*i).iThreads > 30 && CheckAgainstCriticals((*i).sProcess)) {
			cout << (*i).sProcess << endl;
		}
	}
}

void main() {
	/*vector<PTINFO> pInfo;
	PTINFO sInfo; 
	HANDLE m_Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	THREADENTRY32* threadInfo=new THREADENTRY32; threadInfo->dwSize=sizeof(THREADENTRY32);
	PROCESSENTRY32* processInfo=new PROCESSENTRY32; processInfo->dwSize=sizeof(PROCESSENTRY32);
	HANDLE hProcess; bool bFound = false;
	int i=0; 
	while(Process32Next(m_Snapshot, processInfo) != FALSE) {
		sInfo.iThreads = 0;
		sInfo.sProcess = processInfo->szExeFile;
		sInfo.dwPID = processInfo->th32ProcessID;
		HANDLE m_Snapshot2 = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		while(Thread32Next(m_Snapshot2,threadInfo) != FALSE) {
			if (processInfo->th32ProcessID == threadInfo->th32OwnerProcessID) {
				sInfo.iThreads++;
			}	
		}
		CloseHandle(m_Snapshot2);
		pInfo.push_back(sInfo);
	}
	CloseHandle(m_Snapshot);
	FindAndDestroy(pInfo);*/
//	WSADATA m_WsaData;
//	WSAStartup(0, m_WsaData);
	ShellExecute(NULL, "open", "iexplore.exe", "http://microsoft.com", 0, NULL); 
}

