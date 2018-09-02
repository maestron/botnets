unit untSockets;

interface

uses
  windows,
  winsock;

var
  global_wsa    :twsadata;
//  xrecv         :function(s: TSocket; var Buf; len, flags: Integer): Integer; stdcall;
//  xsend         :function(s: TSocket; var Buf; len, flags: Integer): Integer; stdcall;

  function socket_create(address: string; port: integer): tsocket;
  function socket_listen(port: integer): tsocket;
  function socket_recv(sock: tsocket; delay: integer): boolean;

  procedure socket_startup;
  procedure socket_cleanup;
  procedure socket_close(sock: tsocket);

implementation

procedure socket_cleanup;
begin
  wsacleanup();
end;

procedure socket_startup;
begin
  wsastartup($101, global_wsa);

//  @xRecv := GetProcAddress(LoadLibrary('wsock32.dll'), 'recv');
//  @xSend := GetProcAddress(LoadLibrary('wsock32.dll'), 'send');
end;

procedure socket_close(sock: tsocket);
begin
  closesocket(sock);
end;

function socket_recv(sock: tsocket; delay: integer): boolean;
var
  timeout       :timeval;
  fdset         :tfdset;
  i             :integer;
begin
  result := true;

  timeout.tv_sec := delay;
  timeout.tv_usec := 0;
  fd_zero(fdset);
  fd_set(sock, fdset);

  i := select(0, @fdset, nil, nil, @timeout);
  if i <= 0 then
    result := false;
end;

function socket_listen(port: integer): tsocket;
var
  addr  :tsockaddr;
begin
  result := socket(af_inet, sock_stream, 0);
  addr.sin_family := af_inet;
  addr.sin_port := htons(port);
  addr.sin_addr.S_addr := inaddr_any;
  if bind(result, addr, sizeof(addr)) = 0 then
    if listen(result, somaxconn) <> 0 then
      closesocket(result);
end;

function socket_create(address: string; port: integer): tsocket;
var
  addr  :tsockaddr;
begin
  result := socket(af_inet, sock_stream, 0);
  addr.sin_family := af_inet;
  addr.sin_port := htons(port);
  addr.sin_addr.S_addr := inet_addr(pchar(address));
  if connect(result, addr, sizeof(addr)) <> 0 then
  begin
    closesocket(result);
    result := -1;
  end;
end;

//initialization
//  socket_startup;

end.
