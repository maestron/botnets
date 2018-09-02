unit abWinsock;

interface
  uses Windows, Winsock;

type
  TClientSocket = class(TObject)
  private
    FAddress: PChar;
    FData: Pointer;
    FTag: Integer;
    FConnected: Boolean;
  protected
    FSocket: TSocket;
  public
    property Connected: Boolean read FConnected;
    property Data: Pointer read FData write FData;
    property Socket: TSocket read FSocket;
    property Tag: integer read FTag write FTag;
    
    procedure Connect(Address: string; Port: Integer);
    destructor Destroy; override;
    procedure Disconnect();
    function ReceiveBuffer(var Buffer; BufferSize: Integer): Integer;
    function ReceiveLength(): Integer;
    function ReceiveString(): String;
    function SendBuffer(var Buffer; BufferSize: Integer): Integer;
    function SendString(const Buffer: String): Integer;
  end;

var
  WSAData: TWSAData;

implementation

procedure TClientSocket.Connect(Address: String; Port: Integer);
var
  SockAddrIn: TSockAddrIn;
  HostEnt: PHostEnt;
begin
  Disconnect;
  FAddress := pchar(Address);
  FSocket := Winsock.socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  SockAddrIn.sin_family := AF_INET;
  SockAddrIn.sin_port := htons(Port);
  SockAddrIn.sin_addr.s_addr := inet_addr(FAddress);
  if SockAddrIn.sin_addr.s_addr = INADDR_NONE then
  begin
    HostEnt := gethostbyname(FAddress);
    if HostEnt = nil then
    begin
      Exit;
    end;
    SockAddrIn.sin_addr.s_addr := Longint(PLongint(HostEnt^.h_addr_list^)^);
  end;
  Winsock.Connect(FSocket, SockAddrIn, SizeOf(SockAddrIn));
  FConnected := True;
end;

procedure TClientSocket.Disconnect();
begin
  closesocket(FSocket);
  FConnected := False;
end;

function TClientSocket.ReceiveLength(): Integer;
begin
  Result := ReceiveBuffer(Pointer(nil)^, -1);
end;

function TClientSocket.ReceiveBuffer(var Buffer; BufferSize: Integer): Integer;
begin
  if BufferSize = -1 then
  begin
    if ioctlsocket(FSocket, FIONREAD, Longint(Result)) = SOCKET_ERROR then
    begin
      Result := SOCKET_ERROR;
      Disconnect;
    end;
  end
  else
  begin
     Result := recv(FSocket, Buffer, BufferSize, 0);
     if Result = 0 then
     begin
       Disconnect;
     end;
     if Result = SOCKET_ERROR then
     begin
       Result := WSAGetLastError;
       if Result = WSAEWOULDBLOCK then
       begin
         Result := 0;
       end
       else
       begin
         Disconnect;
       end;
     end;
  end;
end;

function TClientSocket.ReceiveString(): String;
begin
  SetLength(Result, ReceiveBuffer(Pointer(nil)^, -1));
  SetLength(Result, ReceiveBuffer(Pointer(Result)^, Length(Result)));
end;

function TClientSocket.SendBuffer(var Buffer; BufferSize: Integer): Integer;
var
  ErrorCode: Integer;
begin
  Result := send(FSocket, Buffer, BufferSize, 0);
  if Result = SOCKET_ERROR then
  begin
    ErrorCode := WSAGetLastError;
    if (ErrorCode = WSAEWOULDBLOCK) then
    begin
      Result := -1;
    end
    else
    begin
      Disconnect;
    end;
  end;
end;

function TClientSocket.SendString(const Buffer: String): Integer;
begin
  Result := SendBuffer(Pointer(Buffer)^, Length(Buffer));
end;

destructor TClientSocket.Destroy;
begin
  inherited Destroy;
  Disconnect;
end;

initialization
  WSAStartUp(257, WSAData);

finalization
  WSACleanup;

end.

