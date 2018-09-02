BOOL WksSvc(EXINFO exinfo);
int WksSocket(int tm, int port, const char* IpAddy);

typedef VOID (*MYPROC)(IN  LPCWSTR Server OPTIONAL,
    IN  LPCWSTR AlternateName,
    IN  LPCWSTR DomainAccount OPTIONAL,
    IN  LPCWSTR DomainAccountPassword OPTIONAL,
    IN  ULONG Reserved
    );