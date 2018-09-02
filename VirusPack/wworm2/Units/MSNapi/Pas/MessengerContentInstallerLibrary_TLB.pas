unit MessengerContentInstallerLibrary_TLB;

// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// PASTLWTR : 1.2
// File generated on 06/04/2007 10:52:48 AM from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\Delphi7SE\Lib\MSN\TYPELIB_7.tlb (1)
// LIBID: {C1637F37-3FC8-4B37-B3B2-6CC5E202390D}
// LCID: 0
// Helpfile: 
// HelpString: Messenger Content Installer Type Library
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\System32\stdole2.tlb)
// ************************************************************************ //
// *************************************************************************//
// NOTE:                                                                      
// Items guarded by $IFDEF_LIVE_SERVER_AT_DESIGN_TIME are used by properties  
// which return objects that may need to be explicitly created via a function 
// call prior to any access via the property. These items have been disabled  
// in order to prevent accidental use from within the object inspector. You   
// may enable them by defining LIVE_SERVER_AT_DESIGN_TIME or by selectively   
// removing them from the $IFDEF blocks. However, such items must still be    
// programmatically created via a method of the appropriate CoClass before    
// they can be used.                                                          
{$TYPEDADDRESS OFF} // Unit must be compiled without type-checked pointers. 
{$WARN SYMBOL_PLATFORM OFF}
{$WRITEABLECONST ON}
{$VARPROPSETTER ON}
interface

uses Windows, ActiveX, Classes, Graphics, OleServer, StdVCL, Variants;
  

// *********************************************************************//
// GUIDS declared in the TypeLibrary. Following prefixes are used:        
//   Type Libraries     : LIBID_xxxx                                      
//   CoClasses          : CLASS_xxxx                                      
//   DISPInterfaces     : DIID_xxxx                                       
//   Non-DISP interfaces: IID_xxxx                                        
// *********************************************************************//
const
  // TypeLibrary Major and minor versions
  MessengerContentInstallerLibraryMajorVersion = 1;
  MessengerContentInstallerLibraryMinorVersion = 0;

  LIBID_MessengerContentInstallerLibrary: TGUID = '{C1637F37-3FC8-4B37-B3B2-6CC5E202390D}';

  DIID_DMessengerContentEvents: TGUID = '{51A01E38-7505-401B-ABC9-F460E1499728}';
  IID_IMessengerContent: TGUID = '{83B2A407-22B9-4842-97C6-DE30EC6DAC3E}';
  CLASS_MessengerContentInstaller: TGUID = '{F06608C7-1874-4EEA-B3B2-DF99EBB144B8}';
type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  DMessengerContentEvents = dispinterface;
  IMessengerContent = interface;
  IMessengerContentDisp = dispinterface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  MessengerContentInstaller = IMessengerContent;


// *********************************************************************//
// DispIntf:  DMessengerContentEvents
// Flags:     (4112) Hidden Dispatchable
// GUID:      {51A01E38-7505-401B-ABC9-F460E1499728}
// *********************************************************************//
  DMessengerContentEvents = dispinterface
    ['{51A01E38-7505-401B-ABC9-F460E1499728}']
    procedure OnContentInstalled(lhrResult: Integer); dispid 0;
  end;

// *********************************************************************//
// Interface: IMessengerContent
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {83B2A407-22B9-4842-97C6-DE30EC6DAC3E}
// *********************************************************************//
  IMessengerContent = interface(IDispatch)
    ['{83B2A407-22B9-4842-97C6-DE30EC6DAC3E}']
    procedure InstallContent(const bstrURL: WideString); safecall;
    procedure InstallIndirectContent(const bstrURL: WideString); safecall;
  end;

// *********************************************************************//
// DispIntf:  IMessengerContentDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {83B2A407-22B9-4842-97C6-DE30EC6DAC3E}
// *********************************************************************//
  IMessengerContentDisp = dispinterface
    ['{83B2A407-22B9-4842-97C6-DE30EC6DAC3E}']
    procedure InstallContent(const bstrURL: WideString); dispid 0;
    procedure InstallIndirectContent(const bstrURL: WideString); dispid 1;
  end;

// *********************************************************************//
// The Class CoMessengerContentInstaller provides a Create and CreateRemote method to          
// create instances of the default interface IMessengerContent exposed by              
// the CoClass MessengerContentInstaller. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoMessengerContentInstaller = class
    class function Create: IMessengerContent;
    class function CreateRemote(const MachineName: string): IMessengerContent;
  end;

  TMessengerContentInstallerOnContentInstalled = procedure(ASender: TObject; lhrResult: Integer) of object;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TMessengerContentInstaller
// Help String      : Messenger Content Installer Object
// Default Interface: IMessengerContent
// Def. Intf. DISP? : No
// Event   Interface: DMessengerContentEvents
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TMessengerContentInstallerProperties= class;
{$ENDIF}
  TMessengerContentInstaller = class(TOleServer)
  private
    FOnContentInstalled: TMessengerContentInstallerOnContentInstalled;
    FIntf:        IMessengerContent;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TMessengerContentInstallerProperties;
    function      GetServerProperties: TMessengerContentInstallerProperties;
{$ENDIF}
    function      GetDefaultInterface: IMessengerContent;
  protected
    procedure InitServerData; override;
    procedure InvokeEvent(DispID: TDispID; var Params: TVariantArray); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IMessengerContent);
    procedure Disconnect; override;
    procedure InstallContent(const bstrURL: WideString);
    procedure InstallIndirectContent(const bstrURL: WideString);
    property DefaultInterface: IMessengerContent read GetDefaultInterface;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TMessengerContentInstallerProperties read GetServerProperties;
{$ENDIF}
    property OnContentInstalled: TMessengerContentInstallerOnContentInstalled read FOnContentInstalled write FOnContentInstalled;
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TMessengerContentInstaller
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TMessengerContentInstallerProperties = class(TPersistent)
  private
    FServer:    TMessengerContentInstaller;
    function    GetDefaultInterface: IMessengerContent;
    constructor Create(AServer: TMessengerContentInstaller);
  protected
  public
    property DefaultInterface: IMessengerContent read GetDefaultInterface;
  published
  end;
{$ENDIF}


procedure Register;

resourcestring
  dtlServerPage = 'ActiveX';

  dtlOcxPage = 'ActiveX';

implementation

uses ComObj;

class function CoMessengerContentInstaller.Create: IMessengerContent;
begin
  Result := CreateComObject(CLASS_MessengerContentInstaller) as IMessengerContent;
end;

class function CoMessengerContentInstaller.CreateRemote(const MachineName: string): IMessengerContent;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_MessengerContentInstaller) as IMessengerContent;
end;

procedure TMessengerContentInstaller.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{F06608C7-1874-4EEA-B3B2-DF99EBB144B8}';
    IntfIID:   '{83B2A407-22B9-4842-97C6-DE30EC6DAC3E}';
    EventIID:  '{51A01E38-7505-401B-ABC9-F460E1499728}';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TMessengerContentInstaller.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    ConnectEvents(punk);
    Fintf:= punk as IMessengerContent;
  end;
end;

procedure TMessengerContentInstaller.ConnectTo(svrIntf: IMessengerContent);
begin
  Disconnect;
  FIntf := svrIntf;
  ConnectEvents(FIntf);
end;

procedure TMessengerContentInstaller.DisConnect;
begin
  if Fintf <> nil then
  begin
    DisconnectEvents(FIntf);
    FIntf := nil;
  end;
end;

function TMessengerContentInstaller.GetDefaultInterface: IMessengerContent;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TMessengerContentInstaller.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TMessengerContentInstallerProperties.Create(Self);
{$ENDIF}
end;

destructor TMessengerContentInstaller.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TMessengerContentInstaller.GetServerProperties: TMessengerContentInstallerProperties;
begin
  Result := FProps;
end;
{$ENDIF}

procedure TMessengerContentInstaller.InvokeEvent(DispID: TDispID; var Params: TVariantArray);
begin
  case DispID of
    -1: Exit;  // DISPID_UNKNOWN
    0: if Assigned(FOnContentInstalled) then
         FOnContentInstalled(Self, Params[0] {Integer});
  end; {case DispID}
end;

procedure TMessengerContentInstaller.InstallContent(const bstrURL: WideString);
begin
  DefaultInterface.InstallContent(bstrURL);
end;

procedure TMessengerContentInstaller.InstallIndirectContent(const bstrURL: WideString);
begin
  DefaultInterface.InstallIndirectContent(bstrURL);
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TMessengerContentInstallerProperties.Create(AServer: TMessengerContentInstaller);
begin
  inherited Create;
  FServer := AServer;
end;

function TMessengerContentInstallerProperties.GetDefaultInterface: IMessengerContent;
begin
  Result := FServer.DefaultInterface;
end;

{$ENDIF}

procedure Register;
begin
  RegisterComponents(dtlServerPage, [TMessengerContentInstaller]);
end;

end.
