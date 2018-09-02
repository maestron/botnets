unit mckSocket;

interface

uses
  Windows, Classes, Messages, Winsock, Forms, SysUtils,
  KOLSocket, mirror;

type

  TSocketMessageEvent = procedure (SocketMessage: TWMSocket) of object;

  TKOLSocket = class(TKOLObj)
  private
    fIPAddress: string;
    fPortNumber: word;
    FOnError:           TSocketMessageEvent;
    FOnAccept:          TSocketMessageEvent;
    FOnClose:           TSocketMessageEvent;
    FOnConnect:         TSocketMessageEvent;
    FOnRead:            TSocketMessageEvent;
    FOnWrite:           TSocketMessageEvent;
    FOnListen:          TSocketMessageEvent;
    FOnOOB:             TSocketMessageEvent;
  protected
    function  AdditionalUnits: string; override;   
    procedure SetupFirst( SL: TStringList; const AName, AParent, Prefix: String ); override;
    procedure SetupLast( SL: TStringList; const AName, AParent, Prefix: String ); override;
    procedure AssignEvents( SL: TStringList; const AName: String ); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;

    function GetPortNumber: LongInt;
    function GetIPAddress: String;

    procedure SetPortNumber(NewPortNumber: LongInt);
    procedure SetIPAddress(NewIPAddress: String);

    procedure SetOnAccept(Value: TSocketMessageEvent);
    procedure SetOnClose(Value: TSocketMessageEvent);
    procedure SetOnConnect(Value: TSocketMessageEvent);
    procedure SetOnError(Value: TSocketMessageEvent);
    procedure SetOnListen(Value: TSocketMessageEvent);
    procedure SetOnOOB(Value: TSocketMessageEvent);
    procedure SetOnRead(Value: TSocketMessageEvent);
    procedure SetOnWrite(Value: TSocketMessageEvent);

  published
    property IPAddress: String read GetIPAddress write SetIPAddress;
    property PortNumber: LongInt read GetPortNumber write SetPortNumber;
    property OnError: TSocketMessageEvent read FOnError write SetOnError;
    property OnAccept: TSocketMessageEvent read FOnAccept write SetOnAccept;
    property OnClose: TSocketMessageEvent read FOnClose write SetOnClose;
    property OnConnect: TSocketMessageEvent read FOnConnect write SetOnConnect;
    property OnRead: TSocketMessageEvent read FOnRead write SetOnRead;
    property OnWrite: TSocketMessageEvent read FOnWrite write SetOnWrite;
    property OnOOB: TSocketMessageEvent read FOnOOB write SetOnOOB;
    property OnListen: TSocketMessageEvent read FOnListen write SetOnListen;
  end;

  procedure Register;

implementation

{$R *.dcr}

constructor TKOLSocket.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  InstanceCount := InstanceCount + 1;
end;  // constructor TKOLSocket.Create

destructor TKOLSocket.Destroy;
begin
  inherited Destroy;
end;  // destructor TKOLSocket.Destroy;

function TKOLSocket.GetIPAddress: String;
begin
  Result := fIPAddress;
end;  // function TKOLSocket.GetIPAddress: String

function TKOLSocket.GetPortNumber: LongInt;
begin
  Result := fPortNumber;
end;  // function TKOLSocket.GetPortNumber: Word

procedure TKOLSocket.SetIPAddress(NewIPAddress: String);
begin
  fIPAddress := NewIPAddress;
  Change;
end;  // procedure TKOLSocket.SetIPAddress(NewIPAddress: String)

procedure TKOLSocket.SetPortNumber(NewPortNumber: LongInt);
begin
  fPortNumber := NewPortNumber;
  Change;
end;  // procedure TKOLSocket.SetPortNumber(NewPortNumber: Word)

procedure TKOLSocket.SetOnAccept;
begin
   fOnAccept := Value;
   Change;
end; 

procedure TKOLSocket.SetOnClose;
begin
   fOnClose := Value;
   Change;
end; 

procedure TKOLSocket.SetOnConnect;
begin
   fOnConnect := Value;
   Change;
end; 

procedure TKOLSocket.SetOnError;
begin
   fOnError := Value;
   Change;
end; 

procedure TKOLSocket.SetOnListen;
begin
   fOnListen := Value;
   Change;
end; 

procedure TKOLSocket.SetOnOOB;
begin
   fOnOOB := Value;
   Change;
end; 

procedure TKOLSocket.SetOnRead;
begin
   fOnRead := Value;
   Change;
end; 

procedure TKOLSocket.SetOnWrite;
begin
   fOnWrite := Value;
   Change;
end; 

function TKOLSocket.AdditionalUnits;
begin
   result := ', KOLSocket';
end;

procedure TKOLSocket.SetupFirst(SL: TStringList; const AName,
  AParent, Prefix: String);
begin
  SL.Add( Prefix + AName + ' := NewAsyncSocket;' );
  SL.Add( Prefix + AName + '.PortNumber := ' + inttostr(fPortNumber) + ';');
  SL.Add( Prefix + AName + '.IPAddress  := ''' + fIPAddress + ''';');
end;

procedure TKOLSocket.SetupLast(SL: TStringList; const AName,
  AParent, Prefix: String);
begin
   //
end;

procedure TKOLSocket.AssignEvents(SL: TStringList; const AName: String);
begin
  inherited;
  DoAssignEvents( SL, AName,
  [ 'OnConnect', 'OnAccept', 'OnListen', 'OnRead', 'OnWrite', 'OnOOB', 'OnClose', 'OnError' ],
  [ @OnConnect , @OnAccept , @OnListen , @OnRead , @OnWrite , @OnOOB , @OnClose , @OnError  ]);
end;

procedure Register;
begin
  RegisterComponents('KOLUtil', [TKOLSocket]);
end;

end.

