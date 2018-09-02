{
  Delphi Application Unit by Aphex
  http://iamaphex.cjb.net
  unremote@knology.net
}

unit ApplicationUnit;

interface

uses
  Windows, StrList;

type
  TProcedure = procedure;

  TApplication = class(TObject)
  private
    FStartup: TProcedure;
    FMain: TProcedure;
    FShutdown: TProcedure;
    FTerminated: boolean;
    function ProcessMessage(var Msg: TMsg): Boolean;
  protected
  public                                                                          
    property Startup: TProcedure read FStartup write FStartup;
    property Main: TProcedure read FMain write FMain;
    property Shutdown: TProcedure read FShutdown write FShutdown;
    property Terminated: boolean read FTerminated write FTerminated;
    procedure StayResident;
    procedure Terminate;
    procedure ProcessMessages;
  end;

implementation

function TApplication.ProcessMessage(var Msg: TMsg): Boolean;
begin
  Result := False;
  if PeekMessage(Msg, 0, 0, 0, PM_REMOVE) then
  begin
    Result := True;
    if Msg.Message <> $0012 then
    begin
      TranslateMessage(Msg);
      DispatchMessage(Msg);
    end
    else
    begin
      FTerminated := True;
    end;
  end;
end;

procedure TApplication.ProcessMessages;
var
  Msg: TMsg;
begin
  while ProcessMessage(Msg) do;
end;

procedure TApplication.Terminate;
begin
  FTerminated := True;
end;

procedure TApplication.StayResident;
var
  Msg: TMsg;
begin
  if Assigned(FStartup) then FStartup;
  while not FTerminated do
  begin
    while ProcessMessage(Msg) do;
    Sleep(100);
    if Assigned(FMain) then FMain;
  end;
  if Assigned(FShutdown) then FShutdown;
end;

end.
