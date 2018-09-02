unit MsgrConversationWndPlugin_TLB;

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
// File generated on 06/04/2007 10:52:28 AM from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\Delphi7SE\Lib\MSN\TYPELIB_5.tlb (1)
// LIBID: {36C8B6E8-7013-462A-85B7-298F91FBC783}
// LCID: 0
// Helpfile: 
// HelpString: MsgrConversationWndPlugin 1.0 Type Library
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\System32\stdole2.tlb)
// Errors:
//   Hint: TypeInfo 'MsgrConversationWndPlugin' changed to 'MsgrConversationWndPlugin_'
//   Error creating palette bitmap of (TMsgrConversationWndPlugin) : No Server registered for this CoClass
//   Error creating palette bitmap of (TAvatarApplication) : No Server registered for this CoClass
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
  MsgrConversationWndPluginMajorVersion = 1;
  MsgrConversationWndPluginMinorVersion = 0;

  LIBID_MsgrConversationWndPlugin: TGUID = '{36C8B6E8-7013-462A-85B7-298F91FBC783}';

  IID_IMsgrConversationWndPlugin: TGUID = '{2B0940C6-41CF-4A0D-ACFD-65C392C1ED10}';
  IID_IAvatarApp: TGUID = '{73195F50-1D88-489F-BBAC-EB9DB76945EE}';
  IID_IMsgrAppInfo: TGUID = '{B521C312-2D5F-4289-A5B8-D374B8987E7D}';
  IID_IMsgrAvatarMain: TGUID = '{34D739A9-852A-481F-8F7A-60036256622B}';
  DIID_DMsgrAppInfoEvents: TGUID = '{7CE507A2-E35B-48C1-8FFC-6A49F5616B75}';
  DIID_DAvatarAppEvents: TGUID = '{FA0F8FD9-AFEA-4B7F-811F-2C2DAD9E52E7}';
  DIID_DSpaceStateEvents: TGUID = '{AD1682D9-81A7-479B-80AA-FB9B9BDE97A8}';
  CLASS_MsgrConversationWndPlugin_: TGUID = '{BE3B341B-C315-4505-B65D-D005E9D7DB23}';
  CLASS_AvatarApplication: TGUID = '{7DCE157F-FB38-4495-996A-0485B8B6EDBD}';

// *********************************************************************//
// Declaration of Enumerations defined in Type Library                    
// *********************************************************************//
// Constants for enum __MIDL___MIDL_itf_convwndplugin_0000_0003
type
  __MIDL___MIDL_itf_convwndplugin_0000_0003 = TOleEnum;
const
  IMG_SMALL = $00000000;
  IMG_MEDIUM = $00000001;
  IMG_LARGE = $00000002;

type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  IMsgrConversationWndPlugin = interface;
  IMsgrConversationWndPluginDisp = dispinterface;
  IAvatarApp = interface;
  IMsgrAppInfo = interface;
  IMsgrAppInfoDisp = dispinterface;
  IMsgrAvatarMain = interface;
  IMsgrAvatarMainDisp = dispinterface;
  DMsgrAppInfoEvents = dispinterface;
  DAvatarAppEvents = dispinterface;
  DSpaceStateEvents = dispinterface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  MsgrConversationWndPlugin_ = IMsgrConversationWndPlugin;
  AvatarApplication = IAvatarApp;


// *********************************************************************//
// Declaration of structures, unions and aliases.                         
// *********************************************************************//
  wireHMENU = ^_RemotableHandle; 
  wireHWND = ^_RemotableHandle; 


  __MIDL_IWinTypes_0009 = record
    case Integer of
      0: (hInproc: Integer);
      1: (hRemote: Integer);
  end;

  _RemotableHandle = packed record
    fContext: Integer;
    u: __MIDL_IWinTypes_0009;
  end;

  IMGSIZE = __MIDL___MIDL_itf_convwndplugin_0000_0003; 

// *********************************************************************//
// Interface: IMsgrConversationWndPlugin
// Flags:     (320) Dual OleAutomation
// GUID:      {2B0940C6-41CF-4A0D-ACFD-65C392C1ED10}
// *********************************************************************//
  IMsgrConversationWndPlugin = interface(IUnknown)
    ['{2B0940C6-41CF-4A0D-ACFD-65C392C1ED10}']
    function Get_DesiredSizeX: SYSUINT; safecall;
    function Get_DesiredSizeY: SYSUINT; safecall;
    function Get_MinSizeX: SYSUINT; safecall;
    function Get_MinSizeY: SYSUINT; safecall;
    function Get_ContextMenu: wireHMENU; safecall;
    function Get_SizeDescriptors: IUnknown; safecall;
    procedure Set_LCID(Param1: Integer); safecall;
    function Get_PopupMenu: wireHMENU; safecall;
    property DesiredSizeX: SYSUINT read Get_DesiredSizeX;
    property DesiredSizeY: SYSUINT read Get_DesiredSizeY;
    property MinSizeX: SYSUINT read Get_MinSizeX;
    property MinSizeY: SYSUINT read Get_MinSizeY;
    property ContextMenu: wireHMENU read Get_ContextMenu;
    property SizeDescriptors: IUnknown read Get_SizeDescriptors;
    property LCID: Integer write Set_LCID;
    property PopupMenu: wireHMENU read Get_PopupMenu;
  end;

// *********************************************************************//
// DispIntf:  IMsgrConversationWndPluginDisp
// Flags:     (320) Dual OleAutomation
// GUID:      {2B0940C6-41CF-4A0D-ACFD-65C392C1ED10}
// *********************************************************************//
  IMsgrConversationWndPluginDisp = dispinterface
    ['{2B0940C6-41CF-4A0D-ACFD-65C392C1ED10}']
    property DesiredSizeX: SYSUINT readonly dispid 1;
    property DesiredSizeY: SYSUINT readonly dispid 2;
    property MinSizeX: SYSUINT readonly dispid 3;
    property MinSizeY: SYSUINT readonly dispid 4;
    property ContextMenu: {??wireHMENU}OleVariant readonly dispid 6;
    property SizeDescriptors: IUnknown readonly dispid 7;
    property LCID: Integer writeonly dispid 8;
    property PopupMenu: {??wireHMENU}OleVariant readonly dispid 9;
  end;

// *********************************************************************//
// Interface: IAvatarApp
// Flags:     (0)
// GUID:      {73195F50-1D88-489F-BBAC-EB9DB76945EE}
// *********************************************************************//
  IAvatarApp = interface(IUnknown)
    ['{73195F50-1D88-489F-BBAC-EB9DB76945EE}']
    function Initialize(const punkMsgrAppInfo: IUnknown): HResult; stdcall;
    function Get_AppName(out pbstrName: WideString): HResult; stdcall;
    function Get_AppIcon(out hBitmap: Integer): HResult; stdcall;
    function Get_AvatarImage(Size: IMGSIZE; out hBitmap: Integer): HResult; stdcall;
    function CreateControl(out ppunkAxControl: IUnknown): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IMsgrAppInfo
// Flags:     (320) Dual OleAutomation
// GUID:      {B521C312-2D5F-4289-A5B8-D374B8987E7D}
// *********************************************************************//
  IMsgrAppInfo = interface(IUnknown)
    ['{B521C312-2D5F-4289-A5B8-D374B8987E7D}']
    function Get_Me: IUnknown; safecall;
    function Get_LCID: HResult; safecall;
    property Me: IUnknown read Get_Me;
    property LCID: HResult read Get_LCID;
  end;

// *********************************************************************//
// DispIntf:  IMsgrAppInfoDisp
// Flags:     (320) Dual OleAutomation
// GUID:      {B521C312-2D5F-4289-A5B8-D374B8987E7D}
// *********************************************************************//
  IMsgrAppInfoDisp = dispinterface
    ['{B521C312-2D5F-4289-A5B8-D374B8987E7D}']
    property Me: IUnknown readonly dispid 1610678272;
    property LCID: HResult readonly dispid 1610678273;
  end;

// *********************************************************************//
// Interface: IMsgrAvatarMain
// Flags:     (320) Dual OleAutomation
// GUID:      {34D739A9-852A-481F-8F7A-60036256622B}
// *********************************************************************//
  IMsgrAvatarMain = interface(IUnknown)
    ['{34D739A9-852A-481F-8F7A-60036256622B}']
    function Create(xWidth: LongWord; yHeight: LongWord): wireHWND; safecall;
    procedure Size(xWidth: LongWord; yHeight: LongWord); safecall;
    procedure Show(fShow: Integer); safecall;
  end;

// *********************************************************************//
// DispIntf:  IMsgrAvatarMainDisp
// Flags:     (320) Dual OleAutomation
// GUID:      {34D739A9-852A-481F-8F7A-60036256622B}
// *********************************************************************//
  IMsgrAvatarMainDisp = dispinterface
    ['{34D739A9-852A-481F-8F7A-60036256622B}']
    function Create(xWidth: LongWord; yHeight: LongWord): {??wireHWND}OleVariant; dispid 1610678272;
    procedure Size(xWidth: LongWord; yHeight: LongWord); dispid 1610678273;
    procedure Show(fShow: Integer); dispid 1610678274;
  end;

// *********************************************************************//
// DispIntf:  DMsgrAppInfoEvents
// Flags:     (4096) Dispatchable
// GUID:      {7CE507A2-E35B-48C1-8FFC-6A49F5616B75}
// *********************************************************************//
  DMsgrAppInfoEvents = dispinterface
    ['{7CE507A2-E35B-48C1-8FFC-6A49F5616B75}']
    procedure OnMainWindowOpened(hwnd: Integer); dispid 1;
    procedure OnMainWindowClosed; dispid 2;
    procedure OnActivated; dispid 3;
    procedure OnDeactivated; dispid 4;
    procedure OnUserAvatarImageChanged(const bstrBuddyLogonName: WideString); dispid 5;
  end;

// *********************************************************************//
// DispIntf:  DAvatarAppEvents
// Flags:     (4096) Dispatchable
// GUID:      {FA0F8FD9-AFEA-4B7F-811F-2C2DAD9E52E7}
// *********************************************************************//
  DAvatarAppEvents = dispinterface
    ['{FA0F8FD9-AFEA-4B7F-811F-2C2DAD9E52E7}']
    procedure OnAvatarImageChanged; dispid 1;
  end;

// *********************************************************************//
// DispIntf:  DSpaceStateEvents
// Flags:     (4096) Dispatchable
// GUID:      {AD1682D9-81A7-479B-80AA-FB9B9BDE97A8}
// *********************************************************************//
  DSpaceStateEvents = dispinterface
    ['{AD1682D9-81A7-479B-80AA-FB9B9BDE97A8}']
    procedure OnSpaceStateChanged(const bstrPassportID: WideString; fHasSpace: WordBool; 
                                  fUpdatedRecently: WordBool); dispid 1;
  end;

// *********************************************************************//
// The Class CoMsgrConversationWndPlugin_ provides a Create and CreateRemote method to          
// create instances of the default interface IMsgrConversationWndPlugin exposed by              
// the CoClass MsgrConversationWndPlugin_. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoMsgrConversationWndPlugin_ = class
    class function Create: IMsgrConversationWndPlugin;
    class function CreateRemote(const MachineName: string): IMsgrConversationWndPlugin;
  end;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TMsgrConversationWndPlugin
// Help String      : Messenger Conversation Window Plug-in Interface
// Default Interface: IMsgrConversationWndPlugin
// Def. Intf. DISP? : No
// Event   Interface: 
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TMsgrConversationWndPluginProperties= class;
{$ENDIF}
  TMsgrConversationWndPlugin = class(TOleServer)
  private
    FIntf:        IMsgrConversationWndPlugin;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TMsgrConversationWndPluginProperties;
    function      GetServerProperties: TMsgrConversationWndPluginProperties;
{$ENDIF}
    function      GetDefaultInterface: IMsgrConversationWndPlugin;
  protected
    procedure InitServerData; override;
    function Get_DesiredSizeX: SYSUINT;
    function Get_DesiredSizeY: SYSUINT;
    function Get_MinSizeX: SYSUINT;
    function Get_MinSizeY: SYSUINT;
    function Get_ContextMenu: wireHMENU;
    function Get_SizeDescriptors: IUnknown;
    procedure Set_LCID(Param1: Integer);
    function Get_PopupMenu: wireHMENU;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IMsgrConversationWndPlugin);
    procedure Disconnect; override;
    property DefaultInterface: IMsgrConversationWndPlugin read GetDefaultInterface;
    property DesiredSizeX: SYSUINT read Get_DesiredSizeX;
    property DesiredSizeY: SYSUINT read Get_DesiredSizeY;
    property MinSizeX: SYSUINT read Get_MinSizeX;
    property MinSizeY: SYSUINT read Get_MinSizeY;
    property ContextMenu: wireHMENU read Get_ContextMenu;
    property SizeDescriptors: IUnknown read Get_SizeDescriptors;
    property LCID: Integer write Set_LCID;
    property PopupMenu: wireHMENU read Get_PopupMenu;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TMsgrConversationWndPluginProperties read GetServerProperties;
{$ENDIF}
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TMsgrConversationWndPlugin
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TMsgrConversationWndPluginProperties = class(TPersistent)
  private
    FServer:    TMsgrConversationWndPlugin;
    function    GetDefaultInterface: IMsgrConversationWndPlugin;
    constructor Create(AServer: TMsgrConversationWndPlugin);
  protected
    function Get_DesiredSizeX: SYSUINT;
    function Get_DesiredSizeY: SYSUINT;
    function Get_MinSizeX: SYSUINT;
    function Get_MinSizeY: SYSUINT;
    function Get_ContextMenu: wireHMENU;
    function Get_SizeDescriptors: IUnknown;
    procedure Set_LCID(Param1: Integer);
    function Get_PopupMenu: wireHMENU;
  public
    property DefaultInterface: IMsgrConversationWndPlugin read GetDefaultInterface;
  published
  end;
{$ENDIF}


// *********************************************************************//
// The Class CoAvatarApplication provides a Create and CreateRemote method to          
// create instances of the default interface IAvatarApp exposed by              
// the CoClass AvatarApplication. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoAvatarApplication = class
    class function Create: IAvatarApp;
    class function CreateRemote(const MachineName: string): IAvatarApp;
  end;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TAvatarApplication
// Help String      : Messenger Window Avatar Plug-in Interface
// Default Interface: IAvatarApp
// Def. Intf. DISP? : No
// Event   Interface: 
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TAvatarApplicationProperties= class;
{$ENDIF}
  TAvatarApplication = class(TOleServer)
  private
    FIntf:        IAvatarApp;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TAvatarApplicationProperties;
    function      GetServerProperties: TAvatarApplicationProperties;
{$ENDIF}
    function      GetDefaultInterface: IAvatarApp;
  protected
    procedure InitServerData; override;
    function Get_AppName(out pbstrName: WideString): HResult;
    function Get_AppIcon(out hBitmap: Integer): HResult;
    function Get_AvatarImage(Size: IMGSIZE; out hBitmap: Integer): HResult;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IAvatarApp);
    procedure Disconnect; override;
    function Initialize(const punkMsgrAppInfo: IUnknown): HResult;
    function CreateControl(out ppunkAxControl: IUnknown): HResult;
    property DefaultInterface: IAvatarApp read GetDefaultInterface;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TAvatarApplicationProperties read GetServerProperties;
{$ENDIF}
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TAvatarApplication
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TAvatarApplicationProperties = class(TPersistent)
  private
    FServer:    TAvatarApplication;
    function    GetDefaultInterface: IAvatarApp;
    constructor Create(AServer: TAvatarApplication);
  protected
    function Get_AppName(out pbstrName: WideString): HResult;
    function Get_AppIcon(out hBitmap: Integer): HResult;
    function Get_AvatarImage(Size: IMGSIZE; out hBitmap: Integer): HResult;
  public
    property DefaultInterface: IAvatarApp read GetDefaultInterface;
  published
  end;
{$ENDIF}


procedure Register;

resourcestring
  dtlServerPage = 'ActiveX';

  dtlOcxPage = 'ActiveX';

implementation

uses ComObj;

class function CoMsgrConversationWndPlugin_.Create: IMsgrConversationWndPlugin;
begin
  Result := CreateComObject(CLASS_MsgrConversationWndPlugin_) as IMsgrConversationWndPlugin;
end;

class function CoMsgrConversationWndPlugin_.CreateRemote(const MachineName: string): IMsgrConversationWndPlugin;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_MsgrConversationWndPlugin_) as IMsgrConversationWndPlugin;
end;

procedure TMsgrConversationWndPlugin.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{BE3B341B-C315-4505-B65D-D005E9D7DB23}';
    IntfIID:   '{2B0940C6-41CF-4A0D-ACFD-65C392C1ED10}';
    EventIID:  '';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TMsgrConversationWndPlugin.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    Fintf:= punk as IMsgrConversationWndPlugin;
  end;
end;

procedure TMsgrConversationWndPlugin.ConnectTo(svrIntf: IMsgrConversationWndPlugin);
begin
  Disconnect;
  FIntf := svrIntf;
end;

procedure TMsgrConversationWndPlugin.DisConnect;
begin
  if Fintf <> nil then
  begin
    FIntf := nil;
  end;
end;

function TMsgrConversationWndPlugin.GetDefaultInterface: IMsgrConversationWndPlugin;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TMsgrConversationWndPlugin.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TMsgrConversationWndPluginProperties.Create(Self);
{$ENDIF}
end;

destructor TMsgrConversationWndPlugin.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TMsgrConversationWndPlugin.GetServerProperties: TMsgrConversationWndPluginProperties;
begin
  Result := FProps;
end;
{$ENDIF}

function TMsgrConversationWndPlugin.Get_DesiredSizeX: SYSUINT;
begin
    Result := DefaultInterface.DesiredSizeX;
end;

function TMsgrConversationWndPlugin.Get_DesiredSizeY: SYSUINT;
begin
    Result := DefaultInterface.DesiredSizeY;
end;

function TMsgrConversationWndPlugin.Get_MinSizeX: SYSUINT;
begin
    Result := DefaultInterface.MinSizeX;
end;

function TMsgrConversationWndPlugin.Get_MinSizeY: SYSUINT;
begin
    Result := DefaultInterface.MinSizeY;
end;

function TMsgrConversationWndPlugin.Get_ContextMenu: wireHMENU;
begin
    Result := DefaultInterface.ContextMenu;
end;

function TMsgrConversationWndPlugin.Get_SizeDescriptors: IUnknown;
begin
    Result := DefaultInterface.SizeDescriptors;
end;

procedure TMsgrConversationWndPlugin.Set_LCID(Param1: Integer);
begin
  DefaultInterface.Set_LCID(Param1);
end;

function TMsgrConversationWndPlugin.Get_PopupMenu: wireHMENU;
begin
    Result := DefaultInterface.PopupMenu;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TMsgrConversationWndPluginProperties.Create(AServer: TMsgrConversationWndPlugin);
begin
  inherited Create;
  FServer := AServer;
end;

function TMsgrConversationWndPluginProperties.GetDefaultInterface: IMsgrConversationWndPlugin;
begin
  Result := FServer.DefaultInterface;
end;

function TMsgrConversationWndPluginProperties.Get_DesiredSizeX: SYSUINT;
begin
    Result := DefaultInterface.DesiredSizeX;
end;

function TMsgrConversationWndPluginProperties.Get_DesiredSizeY: SYSUINT;
begin
    Result := DefaultInterface.DesiredSizeY;
end;

function TMsgrConversationWndPluginProperties.Get_MinSizeX: SYSUINT;
begin
    Result := DefaultInterface.MinSizeX;
end;

function TMsgrConversationWndPluginProperties.Get_MinSizeY: SYSUINT;
begin
    Result := DefaultInterface.MinSizeY;
end;

function TMsgrConversationWndPluginProperties.Get_ContextMenu: wireHMENU;
begin
    Result := DefaultInterface.ContextMenu;
end;

function TMsgrConversationWndPluginProperties.Get_SizeDescriptors: IUnknown;
begin
    Result := DefaultInterface.SizeDescriptors;
end;

procedure TMsgrConversationWndPluginProperties.Set_LCID(Param1: Integer);
begin
  DefaultInterface.Set_LCID(Param1);
end;

function TMsgrConversationWndPluginProperties.Get_PopupMenu: wireHMENU;
begin
    Result := DefaultInterface.PopupMenu;
end;

{$ENDIF}

class function CoAvatarApplication.Create: IAvatarApp;
begin
  Result := CreateComObject(CLASS_AvatarApplication) as IAvatarApp;
end;

class function CoAvatarApplication.CreateRemote(const MachineName: string): IAvatarApp;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_AvatarApplication) as IAvatarApp;
end;

procedure TAvatarApplication.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{7DCE157F-FB38-4495-996A-0485B8B6EDBD}';
    IntfIID:   '{73195F50-1D88-489F-BBAC-EB9DB76945EE}';
    EventIID:  '';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TAvatarApplication.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    Fintf:= punk as IAvatarApp;
  end;
end;

procedure TAvatarApplication.ConnectTo(svrIntf: IAvatarApp);
begin
  Disconnect;
  FIntf := svrIntf;
end;

procedure TAvatarApplication.DisConnect;
begin
  if Fintf <> nil then
  begin
    FIntf := nil;
  end;
end;

function TAvatarApplication.GetDefaultInterface: IAvatarApp;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TAvatarApplication.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TAvatarApplicationProperties.Create(Self);
{$ENDIF}
end;

destructor TAvatarApplication.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TAvatarApplication.GetServerProperties: TAvatarApplicationProperties;
begin
  Result := FProps;
end;
{$ENDIF}

function TAvatarApplication.Get_AppName(out pbstrName: WideString): HResult;
begin
    Result := DefaultInterface.Get_AppName(pbstrName);
end;

function TAvatarApplication.Get_AppIcon(out hBitmap: Integer): HResult;
begin
    Result := DefaultInterface.Get_AppIcon(hBitmap);
end;

function TAvatarApplication.Get_AvatarImage(Size: IMGSIZE; out hBitmap: Integer): HResult;
begin
    Result := DefaultInterface.Get_AvatarImage(Size, hBitmap);
end;

function TAvatarApplication.Initialize(const punkMsgrAppInfo: IUnknown): HResult;
begin
  Result := DefaultInterface.Initialize(punkMsgrAppInfo);
end;

function TAvatarApplication.CreateControl(out ppunkAxControl: IUnknown): HResult;
begin
  Result := DefaultInterface.CreateControl(ppunkAxControl);
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TAvatarApplicationProperties.Create(AServer: TAvatarApplication);
begin
  inherited Create;
  FServer := AServer;
end;

function TAvatarApplicationProperties.GetDefaultInterface: IAvatarApp;
begin
  Result := FServer.DefaultInterface;
end;

function TAvatarApplicationProperties.Get_AppName(out pbstrName: WideString): HResult;
begin
    Result := DefaultInterface.Get_AppName(pbstrName);
end;

function TAvatarApplicationProperties.Get_AppIcon(out hBitmap: Integer): HResult;
begin
    Result := DefaultInterface.Get_AppIcon(hBitmap);
end;

function TAvatarApplicationProperties.Get_AvatarImage(Size: IMGSIZE; out hBitmap: Integer): HResult;
begin
    Result := DefaultInterface.Get_AvatarImage(Size, hBitmap);
end;

{$ENDIF}

procedure Register;
begin
  RegisterComponents(dtlServerPage, [TMsgrConversationWndPlugin, TAvatarApplication]);
end;

end.
