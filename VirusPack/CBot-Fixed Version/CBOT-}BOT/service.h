#ifndef SERVICE
void svc_main();
void svc_ctrlhandler(unsigned long opcode); 
void WINAPI svc_start(DWORD argc, LPTSTR *argv);
int service();
#endif