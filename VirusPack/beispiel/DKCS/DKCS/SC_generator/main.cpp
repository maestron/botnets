#include <windows.h>	
#include <stdio.h>	
void main(void){	
    HANDLE hfile    = ::CreateFile("file.sys",GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);	
    HANDLE hfile2    = ::CreateFile("file.txt",GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);	
    DWORD i,dw,size    = ::GetFileSize(hfile,NULL);	
    LPBYTE lpImage    = (LPBYTE)malloc(size);	
    char    sex[100000];	
    ReadFile(hfile,lpImage,size,&dw,NULL);	
    CloseHandle(hfile);	
    int j=0;
	int c=0;
    for(i = 0;i < size;i++){
		if(c==15){
			wsprintf(&sex[j], "\n");
			j++;
			c=0;
		}
		c++;
        printf("0x%.2X,",lpImage[i]);	
        wsprintf(&sex[j], "0x%.2X,", lpImage[i]);	
        j=j+5;	
    }
	wsprintf(&sex[j+1], "\0");
    WriteFile(hfile2,sex,strlen(sex),&dw, NULL);	
    free(lpImage);	
}