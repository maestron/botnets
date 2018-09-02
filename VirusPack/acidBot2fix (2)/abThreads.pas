unit abThreads;

interface
  uses Windows;

type
  TThread = class;
  TThreadProcedure = procedure(Thread: TThread);
  TSynchronizeProcedure = procedure;
  TThread = class
  private
    FThreadHandle: longword;
    FThreadID: longword;
    FExitCode: longword;
    FTerminated: boolean;
    FExecute: TThreadProcedure;
    FData: pointer;
  protected
  public
    constructor Create(ThreadProcedure: TThreadProcedure; CreationFlags: Cardinal);
    destructor Destroy; override;
    procedure Synchronize(Synchronize: TSynchronizeProcedure);
    procedure Lock;
    procedure Unlock;
    property Terminated: Boolean read FTerminated write FTerminated;
    property ThreadHandle: LongWord read FThreadHandle;
    property ThreadID: LongWord read FThreadID;
    property ExitCode: LongWord read FExitCode;
    property Data: Pointer read FData write FData;
  end;

implementation

var
  ThreadLock: TRTLCriticalSection;

procedure ThreadWrapper(Thread: TThread);
var
  ExitCode: dword;
begin
  Thread.FTerminated := False;
  try
    Thread.FExecute(Thread);
  finally
    GetExitCodeThread(Thread.FThreadHandle, ExitCode);
    Thread.FExitCode := ExitCode;
    Thread.FTerminated := True;
    ExitThread(ExitCode);
  end;
end;

constructor TThread.Create(ThreadProcedure: TThreadProcedure; CreationFlags: Cardinal);
begin
  inherited Create;
  FExitCode := 0;
  FExecute := ThreadProcedure;
  FThreadHandle := BeginThread(nil, 0, @ThreadWrapper, Pointer(Self), CreationFlags, FThreadID);
end;

destructor TThread.Destroy;
begin
  inherited;
  CloseHandle(FThreadHandle);
end;

procedure TThread.Synchronize(Synchronize: TSynchronizeProcedure);
begin
  EnterCriticalSection(ThreadLock);
  try
    Synchronize;
  finally
    LeaveCriticalSection(ThreadLock);
  end;
end;

procedure TThread.Lock;
begin
  EnterCriticalSection(ThreadLock);
end;

procedure TThread.Unlock;
begin
  LeaveCriticalSection(ThreadLock);
end;

initialization
  InitializeCriticalSection(ThreadLock);

finalization
  DeleteCriticalSection(ThreadLock);

end.

