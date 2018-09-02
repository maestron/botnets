unit KOLSocket;

interface

uses
  KOL, Windows, Messages, Winsock;

const
  WM_SOCKET                 = WM_USER + $7000;
  WM_SOCKETERROR            = WM_USER + $7001;
  WM_SOCKETCLOSE            = WM_USER + $7002;
  WM_SOCKETREAD             = WM_USER + $7003;
  WM_SOCKETCONNECT          = WM_USER + $7004;
  WM_SOCKETACCEPT           = WM_USER + $7005;
  WM_SOCKETWRITE            = WM_USER + $7006;
  WM_SOCKETOOB              = WM_USER + $7007;
  WM_SOCKETLISTEN           = WM_USER + $7008;
  WM_SOCKETLOOKUP           = WM_USER + $7009;

  EVENTS_DOLISTEN           = FD_CLOSE OR FD_ACCEPT;
  EVENTS_DOCONNECT          = FD_CONNECT OR FD_CLOSE OR FD_READ;
  EVENTS_SETSOCKETHANDLE    = FD_READ OR FD_CLOSE OR FD_CONNECT;

  MaxWord                   = 65535;
  MinWord                   = 0;

  c_FIRST                   = 1;

  INVALID_SOCKET            = winsock.INVALID_SOCKET;

type

  TWndMethod = procedure(var Message: TMessage) of object;

  PhWnd =^ThWnd;
  ThWnd = object( TObj )
  protected
    m_hWnd: hWnd;
    destructor Destroy; virtual;
  public
    property Handle: hWnd read m_hWnd;
  end;

  PAsyncSocket =^TAsyncSocket;
  TKOLSocket   = PAsyncSocket;

  TWMSocket = record
    Msg: Word;
    case Integer of
    0: (
      SocketWParam: Word;
      SocketDataSize: LongInt;
      SocketNumber: Longint;
      SocketAddress: PAsyncSocket);
    1: (
      WParamLo: Byte;
      WParamHi: Byte;
      SocketEvent: Word;
      SocketError: Word;
      ResultLo: Word;
      ResultHi: Word);
    2: (
      WParam: Word;
      TaskHandle: Word;
      WordHolder: Word;
      pHostStruct: Pointer);
  end;

  TBArray = array[0..65534] of byte;

  TBufRecord = record
     i: integer;
     p:^TBArray;
  end;

  TSocketMessageEvent = procedure (SocketMessage: TWMSocket) of object;

  TAsyncSocket = object( TObj )
    m_SockAddr:         TSockAddr;
    m_Handle:           TSocket;
    m_hWnd:             PhWnd;
    fConnected:         boolean;
    fDNSResult:         string;
    fDNSHandle:         integer;
    FDnsBuffer:         array [0..MAXGETHOSTSTRUCT] of char;
    FList:              PList;
    FOnError:           TSocketMessageEvent;
    FOnLookup:          TSocketMessageEvent;
    FOnAccept:          TSocketMessageEvent;
    FOnClose:           TSocketMessageEvent;
    FOnConnect:         TSocketMessageEvent;
    FOnRead:            TSocketMessageEvent;
    FOnWrite:           TSocketMessageEvent;
    FOnListen:          TSocketMessageEvent;
    FOnOOB:             TSocketMessageEvent;

  protected
    destructor Destroy; virtual;

  private
    function GetCount: LongInt;
    function GetPortNumber: LongInt;
    function GetIPAddress: String;
    function ErrorTest(Evaluation: LongInt): LongInt;

    procedure AllocateSocket;
    procedure KillWinsockBug;
    procedure SetPortNumber(NewPortNumber: LongInt);
    procedure SetIPAddress(NewIPAddress: String);
    procedure SetSocketHandle(NewSocketHandle: TSocket);
    function  GetConnected: boolean;

    // Message Handlers

    procedure HWndProcedure(var Message: TMessage);

    procedure Message_Error(var Message: TWMSocket);
    procedure Message_Lookup(var Message: TWMSocket);
    procedure Message_Close(var Message: TWMSocket);
    procedure Message_Accept(var Message: TWMSocket);
    procedure Message_Read(var Message: TWMSocket);
    procedure Message_Connect(var Message: TWMSocket);
    procedure Message_Write(var Message: TWMSocket);
    procedure Message_OOB(var Message: TWMSocket);
    procedure Message_Listen(var Message: TWMSocket);
    procedure DoReceive(Buffer: Pointer; var ReceiveLen: LongInt);
    procedure DoFinal(Abort: boolean);

  public
    procedure ProcessMessages;
    function  DoGetHostByAddr(IPAddr: PChar): String;
    function  DoGetHostByName(Name: PChar): String;

    procedure DoLookup(host: string);
    procedure DoClose;
    procedure DoSend(Buffer: Pointer; var SendLen: LongInt);
    procedure DoListen;
    procedure DoConnect;
    procedure DoAccept(var AcceptSocket: PAsyncSocket);

    procedure SendString(fString: String);

    function  ReadData(b: pointer; c: integer): integer;
    function  ReadLine(c: char): string; overload;
    function  ReadLine(c: char; t: integer): string; overload;
    function  ErrToStr(Err: LongInt): String;
    function  LocalIP: String;
    function  LocalPort: integer;

    property  SocketHandle: TSocket read m_Handle write SetSocketHandle;
    property  IPAddress: String read GetIPAddress write SetIPAddress;
    property  PortNumber: LongInt read GetPortNumber write SetPortNumber;
    property  Count: LongInt read GetCount;
    property  Connected: boolean read GetConnected;
    property  DNSResult: string read fDNSResult write fDNSResult;

    property  OnError: TSocketMessageEvent read FOnError write FOnError;
    property  OnLookup: TSocketMessageEvent read FOnLookup write FOnLookup;
    property  OnAccept: TSocketMessageEvent read FOnAccept write FOnAccept;
    property  OnClose: TSocketMessageEvent read FOnClose write FOnClose;
    property  OnConnect: TSocketMessageEvent read FOnConnect write FOnConnect;
    property  OnRead: TSocketMessageEvent read FOnRead write FOnRead;
    property  OnWrite: TSocketMessageEvent read FOnWrite write FOnWrite;
    property  OnOOB: TSocketMessageEvent read FOnOOB write FOnOOB;
    property  OnListen: TSocketMessageEvent read FOnListen write FOnListen;
  end;

  function NewThWnd(WndMethod: TWndMethod): PhWnd;
  function NewAsyncSocket: PAsyncSocket;

var
  InstanceCount: LongInt = 0;

implementation

uses objects;

function NewThWnd;
begin
  New(Result, Create);
  Result.m_hWnd := AllocateHWnd(WndMethod);
end;  // constructor ThWnd.Create(WndMethod: TWndMethod)

destructor ThWnd.Destroy;
begin
  DeallocateHWnd(m_hWnd);
  inherited;
end;

function NewAsyncSocket;
var
  TempWSAData: TWSAData;
begin
  InstanceCount := InstanceCount + 1;
  New(Result, Create);
  if (InstanceCount = c_FIRST) then
    Result.ErrorTest(WSAStartup($101, TempWSAData));
  Result.KillWinsockBug;
  Result.m_Handle := INVALID_SOCKET;
  Result.m_SockAddr.sin_family := AF_INET;
  Result.m_SockAddr.sin_addr.s_addr := INet_Addr('0.0.0.0');
  Result.PortNumber := 0;
  Result.FList := NewList;
  Result.m_hWnd := NewThWnd(Result.HWndProcedure);
end;  // constructor TAsyncSocket.Create

function TAsyncSocket.GetCount;
var i: integer;
    t:^TBufRecord;
begin
   result := 0;
   for i := 0 to FList.Count - 1 do begin
      t := FList.Items[i];
      result := result + t^.i;
   end;
end;

function TAsyncSocket.ReadData;
var n,
    r: integer;
    t:^TBufRecord;
    u:^TBufRecord;
    a:^TBArray;
begin
   if FList.count = 0 then begin
      result := 0;
      exit;
   end;
   n := 0;
   a := b;
   while (n < c) and (n < count) do begin
      r := c - n;
      t := FList.Items[0];
      if r > t^.i then r := t^.i;
      move(t^.p^, a^[n], r);
      n := n + r;
      if r = t^.i then begin
         FreeMem(t^.p, t^.i);
         FreeMem(t, SizeOf(TBufRecord));
         FList.Delete(0);
      end else begin
         GetMem(u, SizeOf(TBufRecord));
         u^.i := t^.i - r;
         GetMem(u^.p, u^.i);
         move(t^.p^[r], u^.p^, u^.i);
         FreeMem(t^.p, t^.i);
         FreeMem(t, SizeOf(TBufRecord));
         FList.Items[0] := u;
      end;
   end;
   result := n;
end;

function TAsyncSocket.ReadLine(c: char): string;
var i,
    n,
    j: integer;
    t:^TBufRecord;
    s: string;
begin
   result := '';
   n := 0;
   if count = 0 then exit;
   for i := 0 to FList.Count - 1 do begin
      t := FList.Items[i];
      for j := 0 to t^.i - 1 do begin
         inc(n);
         if chr(t^.p^[j]) = c then begin
            setlength(s, n - 1);
            ReadData(@s[1], n - 1);
            ReadData(@n   ,     1);
            result := s;
            exit;
         end;
      end;
   end;
   setlength(s, n);
   ReadData(@s[1], n);
   Result := s;
end;

function TAsyncSocket.ReadLine(c: char; t: integer): string;
var tt: longint;
   Msg: tagMSG;
begin
   result := '';
   tt := gettickcount;
   while (result = '') and (longint(gettickcount) < tt + t * 1000) do begin
      if PeekMessage(Msg, m_hWnd.m_hWnd, 0, 0, PM_REMOVE) then begin
         DispatchMessage(Msg);
      end;
      result := ReadLine(c);
      if m_Handle = INVALID_SOCKET then exit;
   end;
end;

function TAsyncSocket.GetIPAddress: String;
begin
  Result := INet_NToA(m_SockAddr.sin_addr);
end;  // function TAsyncSocket.GetIPAddress: String

function TAsyncSocket.GetPortNumber: LongInt;
begin
  Result := NToHS(m_SockAddr.sin_port);
end;  // function TAsyncSocket.GetPortNumber: Word

procedure TAsyncSocket.AllocateSocket;
begin
  if (m_Handle = INVALID_SOCKET) then
    begin
    m_Handle := ErrorTest(socket(AF_INET, SOCK_STREAM, 0));
    end;  // if (m_Handle = INVALID_SOCKET) then
end;  // procedure TAsyncSocket.AllocateSocket

procedure TAsyncSocket.SetSocketHandle(NewSocketHandle: TSocket);
begin
  DoFinal(True);
  m_Handle := NewSocketHandle;
  ErrorTest(WSAAsyncSelect(m_Handle, m_hWnd.Handle, WM_SOCKET, EVENTS_SETSOCKETHANDLE));
end;  // procedure TAsyncSocket.SetSocketHandle(NewSocketHandle: TSocket)

function TAsyncSocket.GetConnected;
begin
   result := m_Handle <> INVALID_SOCKET;
end;

function TAsyncSocket.ErrorTest(Evaluation: LongInt): LongInt;
var
  TempMessage: TWMSocket;
begin
  if ((Evaluation = SOCKET_ERROR) OR (Evaluation = INVALID_SOCKET)) then
    begin
    TempMessage.Msg := WM_SOCKETERROR;
    TempMessage.SocketError := WSAGetLastError;
    TempMessage.SocketNumber := m_Handle;
    TempMessage.SocketAddress := @self;
    Message_Error(TempMessage);
    Result := Evaluation;
    end  // if ((Evaluation = SOCKET_ERROR) OR (Evaluation = INVALID_SOCKET)) then
  else
    Result := Evaluation;
end;  // function ErrorTest(Evaluation: LongInt): LongInt;

procedure TAsyncSocket.KillWinsockBug;
var
  Addr: Integer;
begin
  Addr := 0;
  // For an unknown reason, if a call is made to GetHostByName and it should
  // fail, the following call to GetHostByAddr will not fail, but return '>'
  // in the place of the host name.  This clears the problem up.
  GetHostByName('');
  GetHostByAddr(@Addr, SizeOf(Integer), PF_INET);
  GetHostByName('');
end;

procedure TAsyncSocket.SetIPAddress(NewIPAddress: String);
var
   pTempHostEnt: PHostEnt;
begin
  m_SockAddr.sin_addr.s_addr := INet_Addr(PChar(NewIPAddress));
  if (m_SockAddr.sin_addr.s_addr = u_long(INADDR_NONE))  then
     begin
     pTempHostEnt := GetHostByName(PChar(NewIPAddress));
     if (pTempHostEnt <> Nil) then
        m_SockAddr.sin_addr.s_addr := PInAddr(pTempHostEnt^.h_addr_list^)^.s_addr;
     end;
end;  // procedure TAsyncSocket.SetIPAddress(NewIPAddress: String)

procedure TAsyncSocket.SetPortNumber(NewPortNumber: LongInt);
begin
  if ((NewPortNumber > 0) AND (NewPortNumber <= MaxWord)) then
    m_SockAddr.sin_port := HToNS(NewPortNumber);
end;  // procedure TAsyncSocket.SetPortNumber(NewPortNumber: Word)

procedure TAsyncSocket.DoReceive(Buffer: Pointer; var ReceiveLen: LongInt);
begin
  ReceiveLen := recv(m_Handle, Buffer^, ReceiveLen, 0);
  ErrorTest(ReceiveLen);
end;  // TAsyncSocket.DoReceive(Buffer: Pointer; BufferLen: LongInt)

procedure TAsyncSocket.DoSend(Buffer: Pointer; var SendLen: LongInt);
begin
  SendLen := send(m_Handle, Buffer^, SendLen, 0);
  ErrorTest(SendLen);
end;  // procedure TAsyncSocket.DoSend(Buffer: Pointer; BufferLen: LongInt)

procedure TAsyncSocket.DoLookup;
var
   IPAddr  : TInAddr;
begin
   if Host = '' then begin
      Exit;
   end;

   { Cancel any pending lookup }
   if FDnsHandle <> 0 then
      WSACancelAsyncRequest(FDnsHandle);

    FDnsResult := '';

    IPAddr.S_addr := Inet_addr(PChar(Host));
    if IPAddr.S_addr <> u_long(INADDR_NONE) then begin
        FDnsResult := inet_ntoa(IPAddr);
{        TriggerDnsLookupDone(0);}
        Exit;
    end;

    FDnsHandle := WSAAsyncGetHostByName(m_hWnd.Handle,
                                        WM_SOCKETLOOKUP,
                                        @Host[1],
                                        @FDnsBuffer,
                                        SizeOf(FDnsBuffer));
    if FDnsHandle = 0 then begin
       ErrorTest(WSAGetLastError);
       Exit;
    end;
end;

procedure TAsyncSocket.DoClose;
begin
   DoFinal(True);
end;

procedure TAsyncSocket.DoFinal;
var
  TempMessage: TWMSocket;
begin
  if (m_Handle <> INVALID_SOCKET) then begin
    if not Abort then begin
       ProcessMessages;
    end;
    TempMessage.Msg := WM_SOCKETCLOSE;
    TempMessage.SocketNumber := m_Handle;
    TempMessage.SocketAddress := @self;
    Message_Close(TempMessage);
    ErrorTest(closesocket(m_Handle));
    m_Handle := INVALID_SOCKET;
    end;
end;

procedure TAsyncSocket.DoAccept(var AcceptSocket: PAsyncSocket);
var
  TempSize: Integer;
  TempSock: TSocket;
  TempAddr: TSockAddrIn;
begin
  TempSize := SizeOf(TSockAddr);
  TempSock := accept(m_Handle, @TempAddr, @TempSize);
  AcceptSocket.m_SockAddr := TempAddr;
  if (ErrorTest(TempSock) <> INVALID_SOCKET) then
    AcceptSocket.SocketHandle := TempSock;
end;  // procedure TAsyncSocket.DoAccept(var AcceptSocket: TAsyncSocket)

procedure TAsyncSocket.DoListen;
var
  TempMessage: TWMSocket;
begin
  DoClose;
  AllocateSocket;
  if
    (ErrorTest(WSAAsyncSelect(m_Handle, m_hWnd.Handle, WM_SOCKET, EVENTS_DOLISTEN))
      <> SOCKET_ERROR) AND
    (ErrorTest(bind(m_Handle, m_SockAddr, SizeOf(TSockAddr))) <> SOCKET_ERROR) AND
    (ErrorTest(listen(m_Handle, 5)) <> SOCKET_ERROR) then
    begin
    TempMessage.Msg := WM_SOCKETLISTEN;
    TempMessage.SocketNumber := m_Handle;
    TempMessage.SocketAddress := @self;
    Message_Listen(TempMessage);
    end
  else
    DoClose;
end;  // procedure TAsyncSocket.DoListen

procedure TAsyncSocket.DoConnect;
var
  TempResult: LongInt;
begin
  DoClose;
  AllocateSocket;
  ErrorTest(WSAAsyncSelect(m_Handle, m_hWnd.Handle, WM_SOCKET, EVENTS_DOCONNECT));
  TempResult := connect(m_Handle, m_SockAddr, SizeOf(TSockAddr));
  if ((TempResult = SOCKET_ERROR) AND (WSAGetLastError <> WSAEWOULDBLOCK)) then
    ErrorTest(SOCKET_ERROR);
end;  // procedure TAsyncSocket.DoConnect

procedure TAsyncSocket.SendString;
var
  L: LongInt;
begin
  L := Length(fString);
  DoSend(PChar(fString), L);
end;

function TAsyncSocket.DoGetHostByName(Name: PChar): String;
var
   pTempHostEnt: PHostEnt;
begin
  pTempHostEnt := GetHostByName(Name);
  if (pTempHostEnt <> Nil) then
    Result := inet_ntoa(pInAddr(pTempHostEnt^.h_addr_list^)^)
  else
    Result := '';
end;

procedure TAsyncSocket.ProcessMessages;
var Msg: TMsg;
begin
   while PeekMessage(Msg, m_hWnd.m_hWnd, WM_SOCKET, WM_SOCKETLOOKUP, PM_REMOVE) do begin
      DispatchMessage(Msg);
   end;
end;

function TAsyncSocket.DoGetHostByAddr(IPAddr: PChar): String;
var
   pTempHostEnt: PHostEnt;
   TempAddr: LongInt;
begin
  TempAddr := INet_Addr(IPAddr);
  pTempHostEnt := GetHostByAddr(@TempAddr, SizeOf(TempAddr), PF_INET);
  if (pTempHostEnt <> Nil) then
    Result := pTempHostEnt^.h_name
  else
    Result := '';
end;

procedure TAsyncSocket.HWndProcedure(var Message: TMessage);
var
  TempMessage: TWMSocket;
begin
  case Message.Msg of
    WM_SOCKETLOOKUP:
      begin
         TempMessage.Msg := WM_SOCKETLOOKUP;
         TempMessage.SocketNumber := m_Handle;
         TempMessage.SocketAddress := @self;
         Message_Lookup(TempMessage);
      end;
    WM_SOCKET:
      begin
      if (Message.LParamHi > WSABASEERR) then
        begin
        WSASetLastError(Message.LParamHi);
        ErrorTest(SOCKET_ERROR);
        end  // if (Message.LParamHi > WSABASEERR) then
      else
        begin
        case Message.LParamLo of
          FD_READ:
            begin
            TempMessage.SocketDataSize := 0;
            ErrorTest(IOCtlSocket(m_Handle, FIONREAD, TempMessage.SocketDataSize));
            TempMessage.Msg := WM_SOCKETREAD;
            TempMessage.SocketNumber := m_Handle;
            TempMessage.SocketAddress := @self;
            Message_Read(TempMessage);
            end;  // FD_READ
          FD_CLOSE:
            begin
            DoFinal(False);
            end; // FD_CLOSE
          FD_CONNECT:
            begin
            TempMessage.Msg := WM_SOCKETCONNECT;
            TempMessage.SocketNumber := m_Handle;
            TempMessage.SocketAddress := @self;
            Message_Connect(TempMessage);
            end;  // FD_CONNECT
          FD_ACCEPT:
            begin
            TempMessage.Msg := WM_SOCKETACCEPT;
            TempMessage.SocketNumber := m_Handle;
            TempMessage.SocketAddress := @self;
            Message_Accept(TempMessage);
            end;  // FD_ACCEPT
          FD_WRITE:
            begin
            TempMessage.Msg := WM_SOCKETWRITE;
            TempMessage.SocketNumber := m_Handle;
            TempMessage.SocketAddress := @self;
            Message_Write(TempMessage);
            end;  // FD_WRITE
          FD_OOB:
            begin
            TempMessage.Msg := WM_SOCKETOOB;
            TempMessage.SocketNumber := m_Handle;
            TempMessage.SocketAddress := @self;
            Message_OOB(TempMessage);
            end;  // FD_OOB
          end;  // case Message.LParamLo of
        end  // else (if (Message.LParamHi > WSABASEERR) then)
      end;  // WM_SOCKET:
      else
      Message.Result := DefWindowProc(m_hWnd.m_hWnd, Message.Msg, Message.WParam, Message.LParam);
    end;  // case Message.Msg of
end;  // procedure TAsyncSocket.HWndProcedure(var Message: TMessage)

procedure TAsyncSocket.Message_Error(var Message: TWMSocket);
begin
  if Assigned(FOnError) then FOnError(Message)
  else
  MessageBox(HWND_DESKTOP, PChar(ErrToStr(Message.SocketError) + ' on socket ' +
    Int2Str(Message.SocketNumber)), 'Message_Error', MB_OK);
end;  // procedure TAsyncSocket.Message_Error(var Message: TWMSocket)

procedure TAsyncSocket.Message_Lookup(var Message: TWMSocket);
var p: PHostEnt;
begin
  p := @fDNSBuffer;
  fDNSResult := p.h_name;
  if Assigned(FOnLookup) then FOnLookup(Message)
  else
  MessageBox(HWND_DESKTOP, PChar('WM_SOCKETLOOKUP on socket ' + Int2Str(Message.SocketNumber)),
    'Message_Lookup', MB_OK);
end;  // procedure TAsyncSocket.Message_LookUp(var Message: TWMSocket)

procedure TAsyncSocket.Message_Close(var Message: TWMSocket);
begin
  fConnected := False;
  if Assigned(FOnClose) then FOnClose(Message)
  else
  MessageBox(HWND_DESKTOP, PChar('WM_SOCKETCLOSE on socket ' + Int2Str(Message.SocketNumber)),
    'Message_Close', MB_OK);
end;  // procedure TAsyncSocket.Message_Close(var Message: TWMSocket)

procedure TAsyncSocket.Message_Accept(var Message: TWMSocket);
begin
  fConnected := True;
  if Assigned(FOnAccept) then FOnAccept(Message)
  else
  MessageBox(HWND_DESKTOP, PChar('WM_SOCKETACCEPT on socket ' + Int2Str(Message.SocketNumber)),
    'Message_Accept', MB_OK);
end;  // procedure TAsyncSocket.Message_Accept(var Message: TWMSocket)

procedure TAsyncSocket.Message_Read(var Message: TWMSocket);
var t:^TBufRecord;
begin
  if Message.SocketDataSize > 0 then begin
     fConnected := True;
     GetMem(t, sizeof(TBufRecord));
     t^.i := Message.SocketDataSize;
     GetMem(t^.p, t^.i);
     DoReceive(t^.p, t^.i);
     FList.Add(t);
  end;
  if Assigned(FOnRead) then FOnRead(Message)
  else
  MessageBox(HWND_DESKTOP, PChar('WM_SOCKETREAD on socket ' + Int2Str(Message.SocketNumber)),
    'Message_Read', MB_OK);
end;  // procedure TAsyncSocket.Message_Read(var Message: TWMSocket)

procedure TAsyncSocket.Message_Connect(var Message: TWMSocket);
begin
  fConnected := True;
  if Assigned(FOnConnect) then FOnConnect(Message)
  else
  MessageBox(HWND_DESKTOP, PChar('WM_SOCKETCONNECT on socket ' + Int2Str(Message.SocketNumber)),
    'Message_Connect', MB_OK);
end;  // procedure TAsyncSocket.Message_Connect(var Message: TWMSocket)

procedure TAsyncSocket.Message_Write(var Message: TWMSocket);
begin
  fConnected := True;
  if Assigned(FOnWrite) then FOnWrite(Message)
  else
  MessageBox(HWND_DESKTOP, PChar('WM_SOCKETWRITE on socket ' + Int2Str(Message.SocketNumber)),
    'Message_Write', MB_OK);
end;  // procedure TAsyncSocket.Message_Write(var Message: TWMSocket)

procedure TAsyncSocket.Message_OOB(var Message: TWMSocket);
begin
  if Assigned(FOnOOB) then FOnOOB(Message)
  else
  MessageBox(HWND_DESKTOP, PChar('WM_SOCKETOOB on socket ' + Int2Str(Message.SocketNumber)),
    'Message_OOB', MB_OK);
end;  // procedure TAsyncSocket.Message_OOB(var Message: TWMSocket)

procedure TAsyncSocket.Message_Listen(var Message: TWMSocket);
begin
  if Assigned(FOnListen) then FOnListen(Message)
  else
  MessageBox(HWND_DESKTOP, PChar('WM_SOCKETLISTEN on socket ' + Int2Str(Message.SocketNumber)),
    'Message_Listen', MB_OK);
end;  // procedure TAsyncSocket.Message_Listen(var Message: TWMSocket)

destructor TAsyncSocket.Destroy;
var t:^TBufRecord;
    i: integer;
begin
  DoClose;
  if (InstanceCount = c_FIRST) then
    ErrorTest(WSACleanup);
  m_hWnd.Free;
  for i := 0 to FList.Count - 1 do begin
     t := FList.Items[i];
     FreeMem(t^.p, t^.i);
     FreeMem(t, SizeOf(TBufRecord));
  end;
  FList.Free;
  InstanceCount := InstanceCount - 1;
  inherited;
end;

function TAsyncSocket.ErrToStr(Err: LongInt): String;
begin
  case Err of
    WSAEINTR:
      Result := 'WSAEINTR';
    WSAEBADF:
      Result := 'WSAEBADF';
    WSAEACCES:
      Result := 'WSAEACCES';
    WSAEFAULT:
      Result := 'WSAEFAULT';
    WSAEINVAL:
      Result := 'WSAEINVAL';
    WSAEMFILE:
      Result := 'WSAEMFILE';
    WSAEWOULDBLOCK:
      Result := 'WSAEWOULDBLOCK';
    WSAEINPROGRESS:
      Result := 'WSAEINPROGRESS';
    WSAEALREADY:
      Result := 'WSAEALREADY';
    WSAENOTSOCK:
      Result := 'WSAENOTSOCK';
    WSAEDESTADDRREQ:
      Result := 'WSAEDESTADDRREQ';
    WSAEMSGSIZE:
      Result := 'WSAEMSGSIZE';
    WSAEPROTOTYPE:
      Result := 'WSAEPROTOTYPE';
    WSAENOPROTOOPT:
      Result := 'WSAENOPROTOOPT';
    WSAEPROTONOSUPPORT:
      Result := 'WSAEPROTONOSUPPORT';
    WSAESOCKTNOSUPPORT:
      Result := 'WSAESOCKTNOSUPPORT';
    WSAEOPNOTSUPP:
      Result := 'WSAEOPNOTSUPP';
    WSAEPFNOSUPPORT:
      Result := 'WSAEPFNOSUPPORT';
    WSAEAFNOSUPPORT:
      Result := 'WSAEAFNOSUPPORT';
    WSAEADDRINUSE:
      Result := 'WSAEADDRINUSE';
    WSAEADDRNOTAVAIL:
      Result := 'WSAEADDRNOTAVAIL';
    WSAENETDOWN:
      Result := 'WSAENETDOWN';
    WSAENETUNREACH:
      Result := 'WSAENETUNREACH';
    WSAENETRESET:
      Result := 'WSAENETRESET';
    WSAECONNABORTED:
      Result := 'WSAECONNABORTED';
    WSAECONNRESET:
      Result := 'WSAECONNRESET';
    WSAENOBUFS:
      Result := 'WSAENOBUFS';
    WSAEISCONN:
      Result := 'WSAEISCONN';
    WSAENOTCONN:
      Result := 'WSAENOTCONN';
    WSAESHUTDOWN:
      Result := 'WSAESHUTDOWN';
    WSAETOOMANYREFS:
      Result := 'WSAETOOMANYREFS';
    WSAETIMEDOUT:
      Result := 'WSAETIMEDOUT';
    WSAECONNREFUSED:
      Result := 'WSAECONNREFUSED';
    WSAELOOP:
      Result := 'WSAELOOP';
    WSAENAMETOOLONG:
      Result := 'WSAENAMETOOLONG';
    WSAEHOSTDOWN:
      Result := 'WSAEHOSTDOWN';
    WSAEHOSTUNREACH:
      Result := 'WSAEHOSTUNREACH';
    WSAENOTEMPTY:
      Result := 'WSAENOTEMPTY';
    WSAEPROCLIM:
      Result := 'WSAEPROCLIM';
    WSAEUSERS:
      Result := 'WSAEUSERS';
    WSAEDQUOT:
      Result := 'WSAEDQUOT';
    WSAESTALE:
      Result := 'WSAESTALE';
    WSAEREMOTE:
      Result := 'WSAEREMOTE';
    WSASYSNOTREADY:
      Result := 'WSASYSNOTREADY';
    WSAVERNOTSUPPORTED:
      Result := 'WSAVERNOTSUPPORTED';
    WSANOTINITIALISED:
      Result := 'WSANOTINITIALISED';
    WSAHOST_NOT_FOUND:
      Result := 'WSAHOST_NOT_FOUND';
    WSATRY_AGAIN:
      Result := 'WSATRY_AGAIN';
    WSANO_RECOVERY:
      Result := 'WSANO_RECOVERY';
    WSANO_DATA:
      Result := 'WSANO_DATA';
    else Result := 'UNDEFINED WINSOCK ERROR';
    end;  // case Err of
end;  // function TAsyncSocket.ErrToStr(Err: LongInt): String

function TAsyncSocket.LocalIP;
var Name: TSockAddrIn;
     len: integer;
begin
   GetSockName(m_Handle, Name, len);
   Result := int2str(ord(Name.sin_addr.S_un_b.s_b1)) + '.' +
             int2str(ord(Name.sin_addr.S_un_b.s_b2)) + '.' +
             int2str(ord(Name.sin_addr.S_un_b.s_b3)) + '.' +
             int2str(ord(Name.sin_addr.S_un_b.s_b4));
end;

function TAsyncSocket.LocalPort;
var Name: TSockAddrIn;
     len: integer;
begin
   GetSockName(m_Handle, Name, len);
   Result  := NToHS(Name.sin_port);
end;

end.

