static 	OSVERSIONINFO VerInfo;
typedef BOOL (*UCHANGESERVICECONFIG2)(SC_HANDLE, DWORD, LPVOID);
HMODULE hAdvapi;
UCHANGESERVICECONFIG2 uChangeServiceConfig2;

char *show_error(DWORD code) {
	static char buf[1024];
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, code, 0, buf, 1024, NULL);
	return buf;
}


