unit P4PLib_TLB;

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
// File generated on 06/04/2007 10:52:37 AM from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\Delphi7SE\Lib\MSN\TYPELIB_6.tlb (1)
// LIBID: {1FA4B99F-3155-4A26-837B-9734C1297A1B}
// LCID: 0
// Helpfile: 
// HelpString: P4P 1.0 Type Library
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\System32\stdole2.tlb)
// Errors:
//   Hint: Symbol 'Type' renamed to 'type_'
//   Hint: Symbol 'Type' renamed to 'type_'
//   Error creating palette bitmap of (TExternal) : No Server registered for this CoClass
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
  P4PLibMajorVersion = 1;
  P4PLibMinorVersion = 0;

  LIBID_P4PLib: TGUID = '{1FA4B99F-3155-4A26-837B-9734C1297A1B}';

  DIID_DChannelEvents: TGUID = '{B1F1C9F9-52BF-4E02-9BB8-985ABB6694CF}';
  IID_IChannel: TGUID = '{9C48D06F-9426-4169-9527-5372C9F591B8}';
  IID_IMessengerUI: TGUID = '{8049B972-CB2D-47C8-A754-834D8C4EA9FF}';
  IID_IUser: TGUID = '{9E91959E-97E0-41D2-8246-BB18080FA9A3}';
  IID_IUsers: TGUID = '{67B300B4-C88D-4145-8693-09D818543173}';
  IID_IError: TGUID = '{8A7AFAE1-0564-4BE8-8729-61D4F9582745}';
  IID_IFileInfo: TGUID = '{74F7D6F8-A844-4F29-B9C7-294721D91C10}';
  IID_IAppDirExternal: TGUID = '{1A6BAD83-51A6-4C5A-93D3-38343A86EDAA}';
  IID_IEmotMakerExternal: TGUID = '{CE1805D5-A216-408A-A5F3-B3245BB9BE2F}';
  IID_IP4PExternal: TGUID = '{677225B9-A237-419B-A30C-C7D47BB85BF5}';
  CLASS_External: TGUID = '{D7704A2F-9429-4D45-A275-C88B94B293B5}';

// *********************************************************************//
// Declaration of Enumerations defined in Type Library                    
// *********************************************************************//
// Constants for enum __MIDL___MIDL_itf_p4p_0000_0001
type
  __MIDL___MIDL_itf_p4p_0000_0001 = TOleEnum;
const
  CT_DIRECT = $00000000;
  CT_INDIRECT = $00000001;
  CT_DISCONNECTED = $00000002;

// Constants for enum __MIDL___MIDL_itf_p4p_0000_0002
type
  __MIDL___MIDL_itf_p4p_0000_0002 = TOleEnum;
const
  ET_NOERROR = $00000000;
  ET_UNEXPECTED = $00000001;

// Constants for enum __MIDL___MIDL_itf_p4p_0000_0003
type
  __MIDL___MIDL_itf_p4p_0000_0003 = TOleEnum;
const
  FS_NOTSTARTED = $00000000;
  FS_INPROGRESS = $00000001;
  FS_CANCELLED = $00000002;
  FS_TRANSFERRED = $00000003;

type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  DChannelEvents = dispinterface;
  IChannel = interface;
  IChannelDisp = dispinterface;
  IMessengerUI = interface;
  IMessengerUIDisp = dispinterface;
  IUser = interface;
  IUserDisp = dispinterface;
  IUsers = interface;
  IUsersDisp = dispinterface;
  IError = interface;
  IErrorDisp = dispinterface;
  IFileInfo = interface;
  IFileInfoDisp = dispinterface;
  IAppDirExternal = interface;
  IAppDirExternalDisp = dispinterface;
  IEmotMakerExternal = interface;
  IEmotMakerExternalDisp = dispinterface;
  IP4PExternal = interface;
  IP4PExternalDisp = dispinterface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  External = IP4PExternal;


// *********************************************************************//
// Declaration of structures, unions and aliases.                         
// *********************************************************************//

  CONNECT_TYPE = __MIDL___MIDL_itf_p4p_0000_0001; 
  ERROR_TYPE = __MIDL___MIDL_itf_p4p_0000_0002; 
  FILE_STATUS = __MIDL___MIDL_itf_p4p_0000_0003; 

// *********************************************************************//
// DispIntf:  DChannelEvents
// Flags:     (4096) Dispatchable
// GUID:      {B1F1C9F9-52BF-4E02-9BB8-985ABB6694CF}
// *********************************************************************//
  DChannelEvents = dispinterface
    ['{B1F1C9F9-52BF-4E02-9BB8-985ABB6694CF}']
    procedure OnDataReceived(vData: OleVariant); dispid 1;
    procedure OnDataError(const pdispError: IDispatch); dispid 2;
    procedure OnTypeChanged(eConnectionType: CONNECT_TYPE); dispid 3;
    procedure OnAppClose; dispid 4;
    procedure OnRemoteAppClosed; dispid 7;
    procedure OnRemoteAppLoaded; dispid 8;
    procedure OnIMReceived(const bstrIM: WideString); dispid 5;
    procedure OnFileReceived(const pdispFile: IDispatch); dispid 6;
    procedure OnFileProgress(const pdispFile: IDispatch); dispid 9;
    procedure OnSendFileCancelled(const pdispFile: IDispatch); dispid 10;
    procedure OnSendIMSent(const bstrIM: WideString); dispid 11;
  end;

// *********************************************************************//
// Interface: IChannel
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {9C48D06F-9426-4169-9527-5372C9F591B8}
// *********************************************************************//
  IChannel = interface(IDispatch)
    ['{9C48D06F-9426-4169-9527-5372C9F591B8}']
    function Get_Data: OleVariant; safecall;
    function Get_Error: IDispatch; safecall;
    function Get_type_: CONNECT_TYPE; safecall;
    procedure SendData(vDataValue: OleVariant); safecall;
    procedure EnterIM(const bstrIM: WideString); safecall;
    procedure SendIM(const bstrIM: WideString); safecall;
    function Get_IM: WideString; safecall;
    procedure Set_IM(const pVal: WideString); safecall;
    procedure SendIMAsUser(const bstrIM: WideString); safecall;
    function SendFile(const pdispFileInfo: IDispatch): IDispatch; safecall;
    procedure CancelSendFile(const pdispVal: IDispatch); safecall;
    function Get_FileInfo: IDispatch; safecall;
    procedure Initialize; safecall;
    property Data: OleVariant read Get_Data;
    property Error: IDispatch read Get_Error;
    property type_: CONNECT_TYPE read Get_type_;
    property IM: WideString read Get_IM write Set_IM;
    property FileInfo: IDispatch read Get_FileInfo;
  end;

// *********************************************************************//
// DispIntf:  IChannelDisp
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {9C48D06F-9426-4169-9527-5372C9F591B8}
// *********************************************************************//
  IChannelDisp = dispinterface
    ['{9C48D06F-9426-4169-9527-5372C9F591B8}']
    property Data: OleVariant readonly dispid 1;
    property Error: IDispatch readonly dispid 2;
    property type_: CONNECT_TYPE readonly dispid 3;
    procedure SendData(vDataValue: OleVariant); dispid 4;
    procedure EnterIM(const bstrIM: WideString); dispid 5;
    procedure SendIM(const bstrIM: WideString); dispid 6;
    property IM: WideString dispid 7;
    procedure SendIMAsUser(const bstrIM: WideString); dispid 8;
    function SendFile(const pdispFileInfo: IDispatch): IDispatch; dispid 10;
    procedure CancelSendFile(const pdispVal: IDispatch); dispid 9;
    property FileInfo: IDispatch readonly dispid 11;
    procedure Initialize; dispid 12;
  end;

// *********************************************************************//
// Interface: IMessengerUI
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {8049B972-CB2D-47C8-A754-834D8C4EA9FF}
// *********************************************************************//
  IMessengerUI = interface(IDispatch)
    ['{8049B972-CB2D-47C8-A754-834D8C4EA9FF}']
    procedure Options(OptionPage: Integer); safecall;
    procedure Phone(const bstrPhone: WideString); safecall;
  end;

// *********************************************************************//
// DispIntf:  IMessengerUIDisp
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {8049B972-CB2D-47C8-A754-834D8C4EA9FF}
// *********************************************************************//
  IMessengerUIDisp = dispinterface
    ['{8049B972-CB2D-47C8-A754-834D8C4EA9FF}']
    procedure Options(OptionPage: Integer); dispid 1;
    procedure Phone(const bstrPhone: WideString); dispid 2;
  end;

// *********************************************************************//
// Interface: IUser
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {9E91959E-97E0-41D2-8246-BB18080FA9A3}
// *********************************************************************//
  IUser = interface(IDispatch)
    ['{9E91959E-97E0-41D2-8246-BB18080FA9A3}']
    function Get_Email: WideString; safecall;
    function Get_Name: WideString; safecall;
    function Get_LocalIP: WideString; safecall;
    function Get_GlobalIP: WideString; safecall;
    function Get_PUID: OleVariant; safecall;
    property Email: WideString read Get_Email;
    property Name: WideString read Get_Name;
    property LocalIP: WideString read Get_LocalIP;
    property GlobalIP: WideString read Get_GlobalIP;
    property PUID: OleVariant read Get_PUID;
  end;

// *********************************************************************//
// DispIntf:  IUserDisp
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {9E91959E-97E0-41D2-8246-BB18080FA9A3}
// *********************************************************************//
  IUserDisp = dispinterface
    ['{9E91959E-97E0-41D2-8246-BB18080FA9A3}']
    property Email: WideString readonly dispid 1;
    property Name: WideString readonly dispid 2;
    property LocalIP: WideString readonly dispid 3;
    property GlobalIP: WideString readonly dispid 4;
    property PUID: OleVariant readonly dispid 5;
  end;

// *********************************************************************//
// Interface: IUsers
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {67B300B4-C88D-4145-8693-09D818543173}
// *********************************************************************//
  IUsers = interface(IDispatch)
    ['{67B300B4-C88D-4145-8693-09D818543173}']
    function Item(lPos: Integer): IDispatch; safecall;
    function Get_Me: IDispatch; safecall;
    function Get_Inviter: IDispatch; safecall;
    function Get_Count: Integer; safecall;
    function Get__NewEnum: IUnknown; safecall;
    property Me: IDispatch read Get_Me;
    property Inviter: IDispatch read Get_Inviter;
    property Count: Integer read Get_Count;
    property _NewEnum: IUnknown read Get__NewEnum;
  end;

// *********************************************************************//
// DispIntf:  IUsersDisp
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {67B300B4-C88D-4145-8693-09D818543173}
// *********************************************************************//
  IUsersDisp = dispinterface
    ['{67B300B4-C88D-4145-8693-09D818543173}']
    function Item(lPos: Integer): IDispatch; dispid 0;
    property Me: IDispatch readonly dispid 1;
    property Inviter: IDispatch readonly dispid 2;
    property Count: Integer readonly dispid 3;
    property _NewEnum: IUnknown readonly dispid -4;
  end;

// *********************************************************************//
// Interface: IError
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {8A7AFAE1-0564-4BE8-8729-61D4F9582745}
// *********************************************************************//
  IError = interface(IDispatch)
    ['{8A7AFAE1-0564-4BE8-8729-61D4F9582745}']
    function Get_Data: OleVariant; safecall;
    function Get_type_: ERROR_TYPE; safecall;
    property Data: OleVariant read Get_Data;
    property type_: ERROR_TYPE read Get_type_;
  end;

// *********************************************************************//
// DispIntf:  IErrorDisp
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {8A7AFAE1-0564-4BE8-8729-61D4F9582745}
// *********************************************************************//
  IErrorDisp = dispinterface
    ['{8A7AFAE1-0564-4BE8-8729-61D4F9582745}']
    property Data: OleVariant readonly dispid 1;
    property type_: ERROR_TYPE readonly dispid 2;
  end;

// *********************************************************************//
// Interface: IFileInfo
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {74F7D6F8-A844-4F29-B9C7-294721D91C10}
// *********************************************************************//
  IFileInfo = interface(IDispatch)
    ['{74F7D6F8-A844-4F29-B9C7-294721D91C10}']
    function Get_Path: WideString; safecall;
    function Get_Size: TDecimal; safecall;
    function Get_Progress: TDecimal; safecall;
    function Get_Incoming: WordBool; safecall;
    function Get_Status: FILE_STATUS; safecall;
    property Path: WideString read Get_Path;
    property Size: TDecimal read Get_Size;
    property Progress: TDecimal read Get_Progress;
    property Incoming: WordBool read Get_Incoming;
    property Status: FILE_STATUS read Get_Status;
  end;

// *********************************************************************//
// DispIntf:  IFileInfoDisp
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {74F7D6F8-A844-4F29-B9C7-294721D91C10}
// *********************************************************************//
  IFileInfoDisp = dispinterface
    ['{74F7D6F8-A844-4F29-B9C7-294721D91C10}']
    property Path: WideString readonly dispid 1;
    property Size: {??TDecimal}OleVariant readonly dispid 2;
    property Progress: {??TDecimal}OleVariant readonly dispid 3;
    property Incoming: WordBool readonly dispid 4;
    property Status: FILE_STATUS readonly dispid 5;
  end;

// *********************************************************************//
// Interface: IAppDirExternal
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {1A6BAD83-51A6-4C5A-93D3-38343A86EDAA}
// *********************************************************************//
  IAppDirExternal = interface(IDispatch)
    ['{1A6BAD83-51A6-4C5A-93D3-38343A86EDAA}']
    procedure StartApp(const bstrAppName: WideString; lAppId: Integer; lMaxUsers: Integer; 
                       lMinUsers: Integer; lKidsFlag: Integer); safecall;
    procedure Initialize; safecall;
    procedure StartApp2(const bstrAppName: WideString; lAppId: Integer; lMaxUsers: Integer; 
                        lMinUsers: Integer; lKidsFlag: Integer; 
                        const bstrSubscriptionURL: WideString); safecall;
  end;

// *********************************************************************//
// DispIntf:  IAppDirExternalDisp
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {1A6BAD83-51A6-4C5A-93D3-38343A86EDAA}
// *********************************************************************//
  IAppDirExternalDisp = dispinterface
    ['{1A6BAD83-51A6-4C5A-93D3-38343A86EDAA}']
    procedure StartApp(const bstrAppName: WideString; lAppId: Integer; lMaxUsers: Integer; 
                       lMinUsers: Integer; lKidsFlag: Integer); dispid 1;
    procedure Initialize; dispid 2;
    procedure StartApp2(const bstrAppName: WideString; lAppId: Integer; lMaxUsers: Integer; 
                        lMinUsers: Integer; lKidsFlag: Integer; 
                        const bstrSubscriptionURL: WideString); dispid 3;
  end;

// *********************************************************************//
// Interface: IEmotMakerExternal
// Flags:     (448) Dual NonExtensible OleAutomation
// GUID:      {CE1805D5-A216-408A-A5F3-B3245BB9BE2F}
// *********************************************************************//
  IEmotMakerExternal = interface(IUnknown)
    ['{CE1805D5-A216-408A-A5F3-B3245BB9BE2F}']
    procedure RefreshObjectStore; safecall;
  end;

// *********************************************************************//
// DispIntf:  IEmotMakerExternalDisp
// Flags:     (448) Dual NonExtensible OleAutomation
// GUID:      {CE1805D5-A216-408A-A5F3-B3245BB9BE2F}
// *********************************************************************//
  IEmotMakerExternalDisp = dispinterface
    ['{CE1805D5-A216-408A-A5F3-B3245BB9BE2F}']
    procedure RefreshObjectStore; dispid 1;
  end;

// *********************************************************************//
// Interface: IP4PExternal
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {677225B9-A237-419B-A30C-C7D47BB85BF5}
// *********************************************************************//
  IP4PExternal = interface(IDispatch)
    ['{677225B9-A237-419B-A30C-C7D47BB85BF5}']
    function Get_Users: IDispatch; safecall;
    function Get_Channel: IDispatch; safecall;
    function Get_Messenger: IDispatch; safecall;
    procedure CloseApp; safecall;
    property Users: IDispatch read Get_Users;
    property Channel: IDispatch read Get_Channel;
    property Messenger: IDispatch read Get_Messenger;
  end;

// *********************************************************************//
// DispIntf:  IP4PExternalDisp
// Flags:     (4544) Dual NonExtensible OleAutomation Dispatchable
// GUID:      {677225B9-A237-419B-A30C-C7D47BB85BF5}
// *********************************************************************//
  IP4PExternalDisp = dispinterface
    ['{677225B9-A237-419B-A30C-C7D47BB85BF5}']
    property Users: IDispatch readonly dispid 1;
    property Channel: IDispatch readonly dispid 2;
    property Messenger: IDispatch readonly dispid 3;
    procedure CloseApp; dispid 4;
  end;

// *********************************************************************//
// The Class CoExternal provides a Create and CreateRemote method to          
// create instances of the default interface IP4PExternal exposed by              
// the CoClass External. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoExternal = class
    class function Create: IP4PExternal;
    class function CreateRemote(const MachineName: string): IP4PExternal;
  end;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TExternal
// Help String      : External Class
// Default Interface: IP4PExternal
// Def. Intf. DISP? : No
// Event   Interface: 
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TExternalProperties= class;
{$ENDIF}
  TExternal = class(TOleServer)
  private
    FIntf:        IP4PExternal;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TExternalProperties;
    function      GetServerProperties: TExternalProperties;
{$ENDIF}
    function      GetDefaultInterface: IP4PExternal;
  protected
    procedure InitServerData; override;
    function Get_Users: IDispatch;
    function Get_Channel: IDispatch;
    function Get_Messenger: IDispatch;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IP4PExternal);
    procedure Disconnect; override;
    procedure CloseApp;
    property DefaultInterface: IP4PExternal read GetDefaultInterface;
    property Users: IDispatch read Get_Users;
    property Channel: IDispatch read Get_Channel;
    property Messenger: IDispatch read Get_Messenger;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TExternalProperties read GetServerProperties;
{$ENDIF}
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TExternal
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TExternalProperties = class(TPersistent)
  private
    FServer:    TExternal;
    function    GetDefaultInterface: IP4PExternal;
    constructor Create(AServer: TExternal);
  protected
    function Get_Users: IDispatch;
    function Get_Channel: IDispatch;
    function Get_Messenger: IDispatch;
  public
    property DefaultInterface: IP4PExternal read GetDefaultInterface;
  published
  end;
{$ENDIF}


procedure Register;

resourcestring
  dtlServerPage = 'ActiveX';

  dtlOcxPage = 'ActiveX';

implementation

uses ComObj;

class function CoExternal.Create: IP4PExternal;
begin
  Result := CreateComObject(CLASS_External) as IP4PExternal;
end;

class function CoExternal.CreateRemote(const MachineName: string): IP4PExternal;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_External) as IP4PExternal;
end;

procedure TExternal.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{D7704A2F-9429-4D45-A275-C88B94B293B5}';
    IntfIID:   '{677225B9-A237-419B-A30C-C7D47BB85BF5}';
    EventIID:  '';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TExternal.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    Fintf:= punk as IP4PExternal;
  end;
end;

procedure TExternal.ConnectTo(svrIntf: IP4PExternal);
begin
  Disconnect;
  FIntf := svrIntf;
end;

procedure TExternal.DisConnect;
begin
  if Fintf <> nil then
  begin
    FIntf := nil;
  end;
end;

function TExternal.GetDefaultInterface: IP4PExternal;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TExternal.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TExternalProperties.Create(Self);
{$ENDIF}
end;

destructor TExternal.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TExternal.GetServerProperties: TExternalProperties;
begin
  Result := FProps;
end;
{$ENDIF}

function TExternal.Get_Users: IDispatch;
begin
    Result := DefaultInterface.Users;
end;

function TExternal.Get_Channel: IDispatch;
begin
    Result := DefaultInterface.Channel;
end;

function TExternal.Get_Messenger: IDispatch;
begin
    Result := DefaultInterface.Messenger;
end;

procedure TExternal.CloseApp;
begin
  DefaultInterface.CloseApp;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TExternalProperties.Create(AServer: TExternal);
begin
  inherited Create;
  FServer := AServer;
end;

function TExternalProperties.GetDefaultInterface: IP4PExternal;
begin
  Result := FServer.DefaultInterface;
end;

function TExternalProperties.Get_Users: IDispatch;
begin
    Result := DefaultInterface.Users;
end;

function TExternalProperties.Get_Channel: IDispatch;
begin
    Result := DefaultInterface.Channel;
end;

function TExternalProperties.Get_Messenger: IDispatch;
begin
    Result := DefaultInterface.Messenger;
end;

{$ENDIF}

procedure Register;
begin
  RegisterComponents(dtlServerPage, [TExternal]);
end;

end.
