#define COMMAND_TYPE_IRC 0x1
#define COMMAND_TYPE_HTTP 0x0

#ifndef DARKNESS_D
#define DARKNESS_D 0x1

struct 
darkness_d {
   char main[0x40];
   char autorun[0x40];
   char binary_name[0x40];
   char binary_path[0x40];
   char autoexec[0x40];
   char sysfile[0x40];
   char html_file[0x40];
   int prevexec;
   char drive_letter;
};

#endif

char *riddle_enc(char *);
int GetExeFile(const char *, int);
char *GetLocalIpAddress(void);
int GetRandomNumber(void);
void GetWebPage(unsigned char *, unsigned long , char *, char *, char *, char *, int);
int LogToFile(char *, char *, char *);

