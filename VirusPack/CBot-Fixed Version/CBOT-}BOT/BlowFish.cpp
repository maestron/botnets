#include "include.h"
#include "externs.h"
#include "blow/fish.h"	

#ifndef NO_CRYPT 



void BlowCrypt( char botid[], char * data){
	if (!((botid==NULL||data==NULL) ||(*botid==NULL || *data==NULL))){
    char *p = encrypt_string(botid,data);
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




#endif
