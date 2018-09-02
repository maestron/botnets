#include "Main.h"

int hideandshow(char * text,char * hiddentext) {
	const unsigned char encvalues[8]={193,127,143,121,167,179,187,191};
	char ch;
	int max=strlen(text);
	int i;
	int eindex=0;
	for (i=0;i<max;i++) {
		ch=*text++;
		if (ch)
			*hiddentext++ = ch ^ encvalues[eindex++];
		else
			*hiddentext='\0';
		eindex %=8;
	}
	return max;
}
