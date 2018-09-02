unit objects;

interface
uses KOL, Windows, Messages;

type
  TWndMethod = procedure(var Message: TMessage) of object;

function MakeObjectInstance(Method: TWndMethod): Pointer;
procedure FreeObjectInstance(ObjectInstance: Pointer);
function AllocateHWnd(Method: TWndMethod): HWND;
procedure DeallocateHWnd(Wnd: HWND);

implementation

type
  PObjectInstance = ^TObjectInstance;
  TObjectInstance = packed record
    Code: Byte;
    Offset: Integer;
    case Integer of
      0: (Next: PObjectInstance);
      1: (Method: TWndMethod);
  end;

type
  PInstanceBlock = ^TInstanceBlock;
  TInstanceBlock = packed record
    Next: PInstanceBlock;
    Code: array[1..2] of Byte;
    WndProcPtr: Pointer;
    Instances: array[0..100] of TObjectInstance;
  end;

var
  InstBlockList: PInstanceBlock;
  InstFreeList: PObjectInstance;

{ Standard window procedure }
{ In    ECX = Address of method pointer }
{ Out   EAX = Result }

function StdWndProc(Window: HWND; Message, WParam: Longint;
  LParam: Longint): Longint; stdcall; assembler;
asm
        XOR     EAX,EAX
        PUSH    EAX
        PUSH    LParam
        PUSH    WParam
        PUSH    Message
        MOV     EDX,ESP
        MOV     EAX,[ECX].Longint[4]
        CALL    [ECX].Pointer
        ADD     ESP,12
        POP     EAX
end;

{ Allocate an object instance }

function CalcJmpOffset(Src, Dest: Pointer): Longint;
begin
  Result := Longint(Dest) - (Longint(Src) + 5);
end;

function MakeObjectInstance(Method: TWndMethod): Pointer;
const
  BlockCode: array[1..2] of Byte = (
    $59,       { POP ECX }
    $E9);      { JMP StdWndProc }
  PageSize = 4096;
var
  Block: PInstanceBlock;
  Instance: PObjectInstance;
begin
  if InstFreeList = nil then
  begin
    Block := VirtualAlloc(nil, PageSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    Block^.Next := InstBlockList;
    Move(BlockCode, Block^.Code, SizeOf(BlockCode));
    Block^.WndProcPtr := Pointer(CalcJmpOffset(@Block^.Code[2], @StdWndProc));
    Instance := @Block^.Instances;
    repeat
      Instance^.Code := $E8;  { CALL NEAR PTR Offset }
      Instance^.Offset := CalcJmpOffset(Instance, @Block^.Code);
      Instance^.Next := InstFreeList;
      InstFreeList := Instance;
      Inc(Longint(Instance), SizeOf(TObjectInstance));
    until Longint(Instance) - Longint(Block) >= SizeOf(TInstanceBlock);
    InstBlockList := Block;
  end;
  Result := InstFreeList;
  Instance := InstFreeList;
  InstFreeList := Instance^.Next;
  Instance^.Method := Method;
end;

{ Free an object instance }

procedure FreeObjectInstance(ObjectInstance: Pointer);
begin
  if ObjectInstance <> nil then
  begin
    PObjectInstance(ObjectInstance)^.Next := InstFreeList;
    InstFreeList := ObjectInstance;
  end;
end;

var
  UtilWindowClass: TWndClass = (
    style: 0;
    lpfnWndProc: @DefWindowProc;
    cbClsExtra: 0;
    cbWndExtra: 0;
    hInstance: 0;
    hIcon: 0;
    hCursor: 0;
    hbrBackground: 0;
    lpszMenuName: nil;
    lpszClassName: 'KOLSocketUtilWindow');

function AllocateHWnd(Method: TWndMethod): HWND;
var
  TempClass: TWndClass;
  ClassRegistered: Boolean;
begin
  UtilWindowClass.hInstance := HInstance;
  ClassRegistered := GetClassInfo(HInstance, UtilWindowClass.lpszClassName,
    TempClass);
  if not ClassRegistered or (TempClass.lpfnWndProc <> @DefWindowProc) then
  begin
    if ClassRegistered then
      Windows.UnregisterClass(UtilWindowClass.lpszClassName, HInstance);
    Windows.RegisterClass(UtilWindowClass);
  end;
  Result := CreateWindowEx(WS_EX_TOOLWINDOW, UtilWindowClass.lpszClassName,
    '', WS_POPUP {!0}, 0, 0, 0, 0, 0, 0, HInstance, nil);
  if Assigned(Method) then
    SetWindowLong(Result, GWL_WNDPROC, Longint(MakeObjectInstance(Method)));
end;

procedure DeallocateHWnd(Wnd: HWND);
var
  Instance: Pointer;
begin
  Instance := Pointer(GetWindowLong(Wnd, GWL_WNDPROC));
  DestroyWindow(Wnd);
  if Instance <> @DefWindowProc then FreeObjectInstance(Instance);
end;

begin
  InstBlockList := nil;
  InstFreeList := nil;
end.
