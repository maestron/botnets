
#include "Include.h"
#include "Hell.h"
#define MAX_LINES 1024


int Split(char *inStr, void *saveArray)
{
	int i,j,index=0;
	
	char *lines[1024];
	
	memset(lines,0,sizeof(lines));
	
	j=strlen(inStr);
	if (j<1) return -1;
	
	lines[index++]=inStr;
	for (i=0;i < j;i++) 
		if ((inStr[i]=='\x0A') || (inStr[i]=='\x0D')) 
			inStr[i]='\x0';
		
		//Now that all cr/lf have been converted to NULL, save the pointers...
		for (i=0;i < j;i++) {
			if ((inStr[i]=='\x0') && (inStr[i+1]!='\x0')) {
				if (index < MAX_LINES) 
					lines[index++] = &inStr[i+1]; 
				else 
					break;
			}
		}
		
		if (saveArray!=0) 
			memcpy(saveArray,lines,sizeof(lines));
		
		return index;
}
