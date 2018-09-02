unit P4QuickLaunchLibrary_TLB;

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
// File generated on 06/04/2007 10:52:06 AM from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\Delphi7SE\Lib\MSN\TYPELIB_4.tlb (1)
// LIBID: {03A15869-90E7-4E78-A4B1-12E8F5D3DED4}
// LCID: 0
// Helpfile: 
// HelpString: P4 QuickLaunch Type Library
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
  P4QuickLaunchLibraryMajorVersion = 1;
  P4QuickLaunchLibraryMinorVersion = 0;

  LIBID_P4QuickLaunchLibrary: TGUID = '{03A15869-90E7-4E78-A4B1-12E8F5D3DED4}';

  IID_IP4QuickLaunch: TGUID = '{2EBC7693-0EE8-4BCB-BE80-A019B4051150}';
  CLASS_P4QuickLaunch: TGUID = '{E13AAC70-70AE-4988-808C-B267F2C20E79}';
type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  IP4QuickLaunch = interface;
  IP4QuickLaunchDisp = dispinterface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  P4QuickLaunch = IP4QuickLaunch;


// *********************************************************************//
// Interface: IP4QuickLaunch
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {2EBC7693-0EE8-4BCB-BE80-A019B4051150}
// *********************************************************************//
  IP4QuickLaunch = interface(IDispatch)
    ['{2EBC7693-0EE8-4BCB-BE80-A019B4051150}']
    procedure LaunchApp(const bstrAppID: WideString; const bstrUserID: WideString); safecall;
  end;

// *********************************************************************//
// DispIntf:  IP4QuickLaunchDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {2EBC7693-0EE8-4BCB-BE80-A019B4051150}
// *********************************************************************//
  IP4QuickLaunchDisp = dispinterface
    ['{2EBC7693-0EE8-4BCB-BE80-A019B4051150}']
    procedure LaunchApp(const bstrAppID: WideString; const bstrUserID: WideString); dispid 8448;
  end;

// *********************************************************************//
// The Class CoP4QuickLaunch provides a Create and CreateRemote method to          
// create instances of the default interface IP4QuickLaunch exposed by              
// the CoClass P4QuickLaunch. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoP4QuickLaunch = class
    class function Create: IP4QuickLaunch;
    class function CreateRemote(const MachineName: string): IP4QuickLaunch;
  end;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TP4QuickLaunch
// Help String      : P4 QuickLaunch Object
// Default Interface: IP4QuickLaunch
// Def. Intf. DISP? : No
// Event   Interface: 
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TP4QuickLaunchProperties= class;
{$ENDIF}
  TP4QuickLaunch = class(TOleServer)
  private
    FIntf:        IP4QuickLaunch;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TP4QuickLaunchProperties;
    function      GetServerProperties: TP4QuickLaunchProperties;
{$ENDIF}
    function      GetDefaultInterface: IP4QuickLaunch;
  protected
    procedure InitServerData; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IP4QuickLaunch);
    procedure Disconnect; override;
    procedure LaunchApp(const bstrAppID: WideString; const bstrUserID: WideString);
    property DefaultInterface: IP4QuickLaunch read GetDefaultInterface;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TP4QuickLaunchProperties read GetServerProperties;
{$ENDIF}
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TP4QuickLaunch
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TP4QuickLaunchProperties = class(TPersistent)
  private
    FServer:    TP4QuickLaunch;
    function    GetDefaultInterface: IP4QuickLaunch;
    constructor Create(AServer: TP4QuickLaunch);
  protected
  public
    property DefaultInterface: IP4QuickLaunch read GetDefaultInterface;
  published
  end;
{$ENDIF}


procedure Register;

resourcestring
  dtlServerPage = 'ActiveX';

  dtlOcxPage = 'ActiveX';

implementation

uses ComObj;

class function CoP4QuickLaunch.Create: IP4QuickLaunch;
begin
  Result := CreateComObject(CLASS_P4QuickLaunch) as IP4QuickLaunch;
end;

class function CoP4QuickLaunch.CreateRemote(const MachineName: string): IP4QuickLaunch;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_P4QuickLaunch) as IP4QuickLaunch;
end;

procedure TP4QuickLaunch.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{E13AAC70-70AE-4988-808C-B267F2C20E79}';
    IntfIID:   '{2EBC7693-0EE8-4BCB-BE80-A019B4051150}';
    EventIID:  '';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TP4QuickLaunch.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    Fintf:= punk as IP4QuickLaunch;
  end;
end;

procedure TP4QuickLaunch.ConnectTo(svrIntf: IP4QuickLaunch);
begin
  Disconnect;
  FIntf := svrIntf;
end;

procedure TP4QuickLaunch.DisConnect;
begin
  if Fintf <> nil then
  begin
    FIntf := nil;
  end;
end;

function TP4QuickLaunch.GetDefaultInterface: IP4QuickLaunch;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TP4QuickLaunch.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TP4QuickLaunchProperties.Create(Self);
{$ENDIF}
end;

destructor TP4QuickLaunch.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TP4QuickLaunch.GetServerProperties: TP4QuickLaunchProperties;
begin
  Result := FProps;
end;
{$ENDIF}

procedure TP4QuickLaunch.LaunchApp(const bstrAppID: WideString; const bstrUserID: WideString);
begin
  DefaultInterface.LaunchApp(bstrAppID, bstrUserID);
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TP4QuickLaunchProperties.Create(AServer: TP4QuickLaunch);
begin
  inherited Create;
  FServer := AServer;
end;

function TP4QuickLaunchProperties.GetDefaultInterface: IP4QuickLaunch;
begin
  Result := FServer.DefaultInterface;
end;

{$ENDIF}

procedure Register;
begin
  RegisterComponents(dtlServerPage, [TP4QuickLaunch]);
end;

end.
