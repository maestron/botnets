#include <windows.h>
#include <stdio.h>
#include <string.h>

const char *riddle_enc(char *buf) {
    unsigned long x;
    char *tmp=malloc(strlen(buf)+0x1);
    strcpy(tmp,buf);   
	for(x=0x0; x<strlen(tmp); x++) {
		   tmp[x] += (strlen(tmp));
     }
    return(tmp);
}

int
LogToFile
(char *fname, char *buf) {
   FILE *fp=fopen(fname,"a");
   if(fp == NULL) return(0x0);
   else fprintf(fp,"%s\r\n",buf);
   fclose(fp);
   return(0x1);
} 

int main(int argc, char *argv[]) {
    printf("Data Output: %s\r\n",riddle_enc(argv[0x1]));
    //LogToFile("out.txt",riddle_enc(argv[0x1]));
    HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,200);
    char *hClipboardData=(TCHAR*)GlobalLock(hGlobal); 
    strcpy(hClipboardData,riddle_enc(argv[0x1]));
    if(OpenClipboard(NULL)) {
       EmptyClipboard();
       GlobalUnlock(hGlobal);
       if(SetClipboardData(CF_TEXT,hClipboardData)) 
          CloseClipboard();
       } 
    getchar();
}
