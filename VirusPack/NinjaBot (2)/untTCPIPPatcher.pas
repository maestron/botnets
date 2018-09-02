unit untTCPIPPatcher;

interface

uses
  Windows;

  procedure ptcpip;

implementation

function checkos: boolean;
var
  verinfo       :tosversioninfo;
begin
  result := false;
  verinfo.dwOSVersionInfoSize := sizeof(tosversioninfo);
  getversionex(verinfo);

  if (verinfo.dwMajorVersion = 5) and
     (verinfo.dwMinorVersion = 1) and
     (verinfo.szCSDVersion[13] = '2') then
       result := true;
end;

procedure Disable_WFP(szFile :string);
type
  cpp   = function(param1:dword; param2:pwidechar; param3: dword): dword; stdcall;
var
  path  :pwidechar;
  hmod  :thandle;
  SetSfcFileException: cpp;
begin
  getmem(path, 256);
  multibytetowidechar(cp_acp, 0, pchar(szfile), -1, path, 256);

  hmod := loadlibrary('sfc_os.dll');
  SetSfcFileException := getprocaddress(hmod, LPCSTR(5));
  SetSfcFileException(0, path, dword(-1));
end;

function patch_tcpip: boolean;
type
  orglist = record
    offset      :integer;
    value       :char;
  end;
  bytelist = record
    offset      :integer;
    value       :char;
  end;
const
  orgb          :array [0..3] of orglist =
                           ((offset:$00130;value:#$6E),
                            (offset:$00131;value:#$12),
                            (offset:$4f322;value:#$0A),
                            (offset:$4f323;value:#$00));
  bytes         :array [0..3] of bytelist =
                           ((offset:$00130;value:#$4C),
                            (offset:$00131;value:#$16),
                            (offset:$4f322;value:#$E8),
                            (offset:$4f323;value:#$03));
var
  szByte        :byte;
  szPath        :string;
  szSysDir      :array[0..MAX_PATH] of char;
  c             :array[0..8] of char;
  f             :file;
  i             :integer;
  match         :integer;
begin
  result := false;

  szByte := 1;
  if not checkos() then exit;

  GetSystemDirectory(szSysDir, sizeof(szSysDir));
  szPath := szSysDir + '\drivers\tcpip.sys';
  Disable_WFP(szpath);

  assignfile(f, szpath);
  reset(f, 1);

  zeromemory(@i, sizeof(i));
  match := 0;
  for i := 0 to 3 do
  begin
    seek(f, orgb[i].offset);
    blockread(f, szByte, 1);
    if chr(szByte) = orgb[i].value then inc(match);
  end;

  zeromemory(@i, sizeof(i));
  for i := 0 to 3 do
  begin
    seek(f, bytes[i].offset);
    blockwrite(f, bytes[i].value, 1);
  end;

  closefile(f);
  result := true;
end;

function backup: boolean;
var
  szSysDir      :array[0..MAX_PATH] of char;
  szPath        :string;
  szBckPath     :string;
begin
  GetSystemDirectory(szSysDir, sizeof(szSysDir));
  szPath := szSysDir + '\drivers\tcpip.sys';
  szBckPath := szSysDir + '\drivers\tcpip.sys.bck';
  if copyfile(pchar(szPath), pchar(szBckPath), false) then result := true
  else result := false;
end;

procedure ptcpip;
begin
  backup();
  patch_tcpip();
end;

end.


