// Blow.cpp : Defines the entry point for the console application.
//
#pragma comment(linker,"/RELEASE")			// Release code
//#pragma comment(linker, "/ALIGN:4096")		// This will save you some size on the executable.
//#pragma comment(linker, "/IGNORE:4108 ")	// This is only here for when you use /ALIGN:4096.
#pragma pack(1)			

#include "stdafx.h"
#include "fish.h"	// holds the random digit tables
#include "../rndnick.h"
#define NO_CRYPT
#include "../configs.h"
//#include "../sha/sha.h"

void blowcryptp(char *data, char name[]){
	if (!((botid==NULL||data==NULL) ||(*botid==NULL || *data==NULL))){
    char *p = encrypt_string(botid,data);
	printf ("char %s[]=\"%s\"; //%s\r\n",name,p,data);
	delete p;
	}
} 

int _tmain(int argc, _TCHAR* argv[])
{

	char blowpass[16];//[]="secret";
	char content[512];


	return 0;
}

