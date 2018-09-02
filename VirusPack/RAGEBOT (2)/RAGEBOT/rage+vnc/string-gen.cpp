#include "externs.h"
#include "include.h"

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