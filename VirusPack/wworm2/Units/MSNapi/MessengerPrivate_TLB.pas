unit MessengerPrivate_TLB;

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
// File generated on 06/04/2007 10:53:56 AM from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\Delphi7SE\Lib\MSN\msn_type_lib1.ocx (1)
// LIBID: {53CED51D-432B-45B2-A3E0-0CE2C24235D4}
// LCID: 0
// Helpfile: 
// HelpString: Messenger Private Type Library
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
  MessengerPrivateMajorVersion = 1;
  MessengerPrivateMinorVersion = 0;

  LIBID_MessengerPrivate: TGUID = '{53CED51D-432B-45B2-A3E0-0CE2C24235D4}';

  IID_IMsgrSessionManager: TGUID = '{305D86C6-6896-4099-91F5-CB7BA7733563}';
  IID_IMsgrSession: TGUID = '{42D7CAFC-0167-4941-A5D8-9FD7F104C41A}';
  IID_IMsgrLock: TGUID = '{36602AFA-4859-4DF5-820B-BF35ACAA16CA}';
  IID_IMessengerPrivate: TGUID = '{7C95459B-C8E7-4605-B641-45EB06866659}';
  DIID_DMessengerPrivateEvents: TGUID = '{D21454F8-43E3-4D64-B1E3-84911BAF207D}';
  DIID_DMsgrSessionManagerEvents: TGUID = '{52AC8B62-8F88-46CA-902A-1F9106B0A9F4}';
  DIID_DMsgrSessionEvents: TGUID = '{1847A74F-2E7F-43AF-B7F9-55A4DE3276F5}';
  CLASS_MessengerPriv: TGUID = '{AB1D8565-40E9-4616-984D-98465687E82C}';
  CLASS_MsgrSessionManager: TGUID = '{E3A3B1D9-5675-43C0-BF04-37BE11939FB7}';
  CLASS_MsgrSession: TGUID = '{E3A3B1D8-5675-43C0-BF04-37BE11939FB7}';

// *********************************************************************//
// Declaration of Enumerations defined in Type Library                    
// *********************************************************************//
// Constants for enum __MIDL___MIDL_itf_msgrpriv_0000_0001
type
  __MIDL___MIDL_itf_msgrpriv_0000_0001 = TOleEnum;
const
  SS_UNKNOWN = $00000000;
  SS_READY = $00000001;
  SS_INVITATION = $00000002;
  SS_ACCEPTED = $00000003;
  SS_CONNECTED = $00000004;
  SS_CANCELLED = $00000005;
  SS_DECLINED = $00000006;
  SS_TERMINATED = $00000007;
  SS_FALLBACK_INVITER = $00000008;
  SS_FALLBACK_INVITEE = $00000009;

// Constants for enum __MIDL___MIDL_itf_msgrpriv_0000_0005
type
  __MIDL___MIDL_itf_msgrpriv_0000_0005 = TOleEnum;
const
  LOCK_NOTINITIALIZED = $00000001;
  LOCK_INITIALIZED = $00000002;
  LOCK_PENDINGRESULT = $00000003;
  LOCK_UNLOCKED = $00000004;
  LOCK_UNLOCKFAILED = $00000005;
  LOCK_DISABLED = $00000006;

type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  IMsgrSessionManager = interface;
  IMsgrSessionManagerDisp = dispinterface;
  IMsgrSession = interface;
  IMsgrSessionDisp = dispinterface;
  IMsgrLock = interface;
  IMessengerPrivate = interface;
  IMessengerPrivateDisp = dispinterface;
  DMessengerPrivateEvents = dispinterface;
  DMsgrSessionManagerEvents = dispinterface;
  DMsgrSessionEvents = dispinterface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  MessengerPriv = IMessengerPrivate;
  MsgrSessionManager = IMsgrSessionManager;
  MsgrSession = IMsgrSession;


// *********************************************************************//
// Declaration of structures, unions and aliases.                         
// *********************************************************************//

  SESSION_STATE = __MIDL___MIDL_itf_msgrpriv_0000_0001; 
  LockStatus = __MIDL___MIDL_itf_msgrpriv_0000_0005; 

// *********************************************************************//
// Interface: IMsgrSessionManager
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {305D86C6-6896-4099-91F5-CB7BA7733563}
// *********************************************************************//
  IMsgrSessionManager = interface(IDispatch)
    ['{305D86C6-6896-4099-91F5-CB7BA7733563}']
    function CreateSession: IDispatch; safecall;
    function GetLaunchingSession(lProcessID: Integer): IDispatch; safecall;
    procedure RegisterApplication(const bstrAppGUID: WideString; const bstrAppName: WideString; 
                                  const bstrAppURL: WideString; const bstrPath: WideString; 
                                  ulFlags: Integer); safecall;
    procedure UnRegisterApplication(const bstrAppGUID: WideString); safecall;
    function Get_Applications: IDispatch; safecall;
    property Applications: IDispatch read Get_Applications;
  end;

// *********************************************************************//
// DispIntf:  IMsgrSessionManagerDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {305D86C6-6896-4099-91F5-CB7BA7733563}
// *********************************************************************//
  IMsgrSessionManagerDisp = dispinterface
    ['{305D86C6-6896-4099-91F5-CB7BA7733563}']
    function CreateSession: IDispatch; dispid 0;
    function GetLaunchingSession(lProcessID: Integer): IDispatch; dispid 1;
    procedure RegisterApplication(const bstrAppGUID: WideString; const bstrAppName: WideString; 
                                  const bstrAppURL: WideString; const bstrPath: WideString; 
                                  ulFlags: Integer); dispid 2;
    procedure UnRegisterApplication(const bstrAppGUID: WideString); dispid 3;
    property Applications: IDispatch readonly dispid 4;
  end;

// *********************************************************************//
// Interface: IMsgrSession
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {42D7CAFC-0167-4941-A5D8-9FD7F104C41A}
// *********************************************************************//
  IMsgrSession = interface(IDispatch)
    ['{42D7CAFC-0167-4941-A5D8-9FD7F104C41A}']
    function Get_Application: WideString; safecall;
    procedure Set_Application(const pbstrAppGUID: WideString); safecall;
    function Get_State: SESSION_STATE; safecall;
    procedure Invite(const pUser: IDispatch; const bstrAppData: WideString); safecall;
    procedure Decline(const bstrAppData: WideString); safecall;
    procedure Cancel(hr: Integer; const bstrAppData: WideString); safecall;
    procedure Accept(const bstrAppData: WideString); safecall;
    function Get_RemoteAddress: WideString; safecall;
    function Get_SessionID: WideString; safecall;
    function Get_ContextData: WideString; safecall;
    function Get_ApplicationName: WideString; safecall;
    function Get_ApplicationURL: WideString; safecall;
    function Get_Flags: Integer; safecall;
    function Get_User: IDispatch; safecall;
    procedure Set_LocalAddress(const pbstrLocalAddress: WideString); safecall;
    function Get_LocalAddress: WideString; safecall;
    procedure SendContextData(const bstrData: WideString); safecall;
    property Application: WideString read Get_Application write Set_Application;
    property State: SESSION_STATE read Get_State;
    property RemoteAddress: WideString read Get_RemoteAddress;
    property SessionID: WideString read Get_SessionID;
    property ContextData: WideString read Get_ContextData;
    property ApplicationName: WideString read Get_ApplicationName;
    property ApplicationURL: WideString read Get_ApplicationURL;
    property Flags: Integer read Get_Flags;
    property User: IDispatch read Get_User;
    property LocalAddress: WideString read Get_LocalAddress write Set_LocalAddress;
  end;

// *********************************************************************//
// DispIntf:  IMsgrSessionDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {42D7CAFC-0167-4941-A5D8-9FD7F104C41A}
// *********************************************************************//
  IMsgrSessionDisp = dispinterface
    ['{42D7CAFC-0167-4941-A5D8-9FD7F104C41A}']
    property Application: WideString dispid 0;
    property State: SESSION_STATE readonly dispid 1;
    procedure Invite(const pUser: IDispatch; const bstrAppData: WideString); dispid 2;
    procedure Decline(const bstrAppData: WideString); dispid 3;
    procedure Cancel(hr: Integer; const bstrAppData: WideString); dispid 4;
    procedure Accept(const bstrAppData: WideString); dispid 5;
    property RemoteAddress: WideString readonly dispid 6;
    property SessionID: WideString readonly dispid 7;
    property ContextData: WideString readonly dispid 8;
    property ApplicationName: WideString readonly dispid 9;
    property ApplicationURL: WideString readonly dispid 10;
    property Flags: Integer readonly dispid 11;
    property User: IDispatch readonly dispid 12;
    property LocalAddress: WideString dispid 13;
    procedure SendContextData(const bstrData: WideString); dispid 14;
  end;

// *********************************************************************//
// Interface: IMsgrLock
// Flags:     (256) OleAutomation
// GUID:      {36602AFA-4859-4DF5-820B-BF35ACAA16CA}
// *********************************************************************//
  IMsgrLock = interface(IUnknown)
    ['{36602AFA-4859-4DF5-820B-BF35ACAA16CA}']
    function Get_Status(out peStatus: LockStatus): HResult; stdcall;
    function RequestChallenge(lCookie: Integer): HResult; stdcall;
    function SendResponse(const bstrAppStrId: WideString; const bstrResponse: WideString; 
                          lCookie: Integer): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IMessengerPrivate
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {7C95459B-C8E7-4605-B641-45EB06866659}
// *********************************************************************//
  IMessengerPrivate = interface(IDispatch)
    ['{7C95459B-C8E7-4605-B641-45EB06866659}']
    procedure EnableAlertEvents(var ppsaSiteIds: PSafeArray); safecall;
    procedure AddContact(const bstrSiginName: WideString; vService: OleVariant); safecall;
  end;

// *********************************************************************//
// DispIntf:  IMessengerPrivateDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {7C95459B-C8E7-4605-B641-45EB06866659}
// *********************************************************************//
  IMessengerPrivateDisp = dispinterface
    ['{7C95459B-C8E7-4605-B641-45EB06866659}']
    procedure EnableAlertEvents(var ppsaSiteIds: {??PSafeArray}OleVariant); dispid 1408;
    procedure AddContact(const bstrSiginName: WideString; vService: OleVariant); dispid 1409;
  end;

// *********************************************************************//
// DispIntf:  DMessengerPrivateEvents
// Flags:     (4096) Dispatchable
// GUID:      {D21454F8-43E3-4D64-B1E3-84911BAF207D}
// *********************************************************************//
  DMessengerPrivateEvents = dispinterface
    ['{D21454F8-43E3-4D64-B1E3-84911BAF207D}']
    procedure OnLockChallenge(lCookie: Integer; const bstrChallenge: WideString); dispid 145;
    procedure OnLockResult(lCookie: Integer; fSucceed: WordBool); dispid 146;
    procedure OnLockEnable(fEnable: WordBool); dispid 147;
    procedure OnLockStatusChanged(eStatus: LockStatus); dispid 12288;
    procedure OnAlertReceived(const bstrAlert: WideString; var pBoolfEnableDefault: WordBool); dispid 1040;
    procedure OnContactListAdd(hr: Integer; const pMContact: IDispatch); dispid 1026;
  end;

// *********************************************************************//
// DispIntf:  DMsgrSessionManagerEvents
// Flags:     (4096) Dispatchable
// GUID:      {52AC8B62-8F88-46CA-902A-1F9106B0A9F4}
// *********************************************************************//
  DMsgrSessionManagerEvents = dispinterface
    ['{52AC8B62-8F88-46CA-902A-1F9106B0A9F4}']
    procedure OnInvitation(const pSession: IDispatch; const bstrAppData: WideString; 
                           var pfHandled: WordBool); dispid 100;
    procedure OnAppRegistered(const bstrAppGUID: WideString); dispid 101;
    procedure OnAppUnRegistered(const bstrAppGUID: WideString); dispid 102;
    procedure OnLockChallenge(lCookie: Integer; const bstrChallenge: WideString); dispid 145;
    procedure OnLockResult(lCookie: Integer; fSucceed: WordBool); dispid 146;
    procedure OnLockEnable(fEnable: WordBool); dispid 147;
    procedure OnLockStatusChanged(eStatus: LockStatus); dispid 12288;
    procedure OnAppShutdown; dispid 126;
  end;

// *********************************************************************//
// DispIntf:  DMsgrSessionEvents
// Flags:     (4096) Dispatchable
// GUID:      {1847A74F-2E7F-43AF-B7F9-55A4DE3276F5}
// *********************************************************************//
  DMsgrSessionEvents = dispinterface
    ['{1847A74F-2E7F-43AF-B7F9-55A4DE3276F5}']
    procedure OnStateChanged(prevState: SESSION_STATE); dispid 103;
    procedure OnAppNotPresent(const bstrAppName: WideString; const bstrAppURL: WideString); dispid 104;
    procedure OnAccepted(const bstrAppData: WideString); dispid 105;
    procedure OnDeclined(const bstrAppData: WideString); dispid 106;
    procedure OnCancelled(const bstrAppData: WideString); dispid 107;
    procedure OnTermination(hr: Integer; const bstrAppData: WideString); dispid 108;
    procedure OnReadyToLaunch; dispid 109;
    procedure BeforeAppLaunch(var pfEnableDefault: WordBool); dispid 112;
    procedure OnContextData(const bstrContextData: WideString); dispid 110;
    procedure OnSendError(hr: Integer); dispid 111;
  end;

// *********************************************************************//
// The Class CoMessengerPriv provides a Create and CreateRemote method to          
// create instances of the default interface IMessengerPrivate exposed by              
// the CoClass MessengerPriv. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoMessengerPriv = class
    class function Create: IMessengerPrivate;
    class function CreateRemote(const MachineName: string): IMessengerPrivate;
  end;

  TMessengerPrivOnLockChallenge = procedure(ASender: TObject; lCookie: Integer; 
                                                              const bstrChallenge: WideString) of object;
  TMessengerPrivOnLockResult = procedure(ASender: TObject; lCookie: Integer; fSucceed: WordBool) of object;
  TMessengerPrivOnLockEnable = procedure(ASender: TObject; fEnable: WordBool) of object;
  TMessengerPrivOnLockStatusChanged = procedure(ASender: TObject; eStatus: LockStatus) of object;
  TMessengerPrivOnAlertReceived = procedure(ASender: TObject; const bstrAlert: WideString; 
                                                              var pBoolfEnableDefault: WordBool) of object;
  TMessengerPrivOnContactListAdd = procedure(ASender: TObject; hr: Integer; 
                                                               const pMContact: IDispatch) of object;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TMessengerPriv
// Help String      : Messenger Private Object
// Default Interface: IMessengerPrivate
// Def. Intf. DISP? : No
// Event   Interface: DMessengerPrivateEvents
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TMessengerPrivProperties= class;
{$ENDIF}
  TMessengerPriv = class(TOleServer)
  private
    FOnLockChallenge: TMessengerPrivOnLockChallenge;
    FOnLockResult: TMessengerPrivOnLockResult;
    FOnLockEnable: TMessengerPrivOnLockEnable;
    FOnLockStatusChanged: TMessengerPrivOnLockStatusChanged;
    FOnAlertReceived: TMessengerPrivOnAlertReceived;
    FOnContactListAdd: TMessengerPrivOnContactListAdd;
    FIntf:        IMessengerPrivate;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TMessengerPrivProperties;
    function      GetServerProperties: TMessengerPrivProperties;
{$ENDIF}
    function      GetDefaultInterface: IMessengerPrivate;
  protected
    procedure InitServerData; override;
    procedure InvokeEvent(DispID: TDispID; var Params: TVariantArray); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IMessengerPrivate);
    procedure Disconnect; override;
    procedure EnableAlertEvents(var ppsaSiteIds: PSafeArray);
    procedure AddContact(const bstrSiginName: WideString; vService: OleVariant);
    property DefaultInterface: IMessengerPrivate read GetDefaultInterface;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TMessengerPrivProperties read GetServerProperties;
{$ENDIF}
    property OnLockChallenge: TMessengerPrivOnLockChallenge read FOnLockChallenge write FOnLockChallenge;
    property OnLockResult: TMessengerPrivOnLockResult read FOnLockResult write FOnLockResult;
    property OnLockEnable: TMessengerPrivOnLockEnable read FOnLockEnable write FOnLockEnable;
    property OnLockStatusChanged: TMessengerPrivOnLockStatusChanged read FOnLockStatusChanged write FOnLockStatusChanged;
    property OnAlertReceived: TMessengerPrivOnAlertReceived read FOnAlertReceived write FOnAlertReceived;
    property OnContactListAdd: TMessengerPrivOnContactListAdd read FOnContactListAdd write FOnContactListAdd;
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TMessengerPriv
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TMessengerPrivProperties = class(TPersistent)
  private
    FServer:    TMessengerPriv;
    function    GetDefaultInterface: IMessengerPrivate;
    constructor Create(AServer: TMessengerPriv);
  protected
  public
    property DefaultInterface: IMessengerPrivate read GetDefaultInterface;
  published
  end;
{$ENDIF}


// *********************************************************************//
// The Class CoMsgrSessionManager provides a Create and CreateRemote method to          
// create instances of the default interface IMsgrSessionManager exposed by              
// the CoClass MsgrSessionManager. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoMsgrSessionManager = class
    class function Create: IMsgrSessionManager;
    class function CreateRemote(const MachineName: string): IMsgrSessionManager;
  end;

  TMsgrSessionManagerOnInvitation = procedure(ASender: TObject; const pSession: IDispatch; 
                                                                const bstrAppData: WideString; 
                                                                var pfHandled: WordBool) of object;
  TMsgrSessionManagerOnAppRegistered = procedure(ASender: TObject; const bstrAppGUID: WideString) of object;
  TMsgrSessionManagerOnAppUnRegistered = procedure(ASender: TObject; const bstrAppGUID: WideString) of object;
  TMsgrSessionManagerOnLockChallenge = procedure(ASender: TObject; lCookie: Integer; 
                                                                   const bstrChallenge: WideString) of object;
  TMsgrSessionManagerOnLockResult = procedure(ASender: TObject; lCookie: Integer; fSucceed: WordBool) of object;
  TMsgrSessionManagerOnLockEnable = procedure(ASender: TObject; fEnable: WordBool) of object;
  TMsgrSessionManagerOnLockStatusChanged = procedure(ASender: TObject; eStatus: LockStatus) of object;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TMsgrSessionManager
// Help String      : Messenger Session Manager Object
// Default Interface: IMsgrSessionManager
// Def. Intf. DISP? : No
// Event   Interface: DMsgrSessionManagerEvents
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TMsgrSessionManagerProperties= class;
{$ENDIF}
  TMsgrSessionManager = class(TOleServer)
  private
    FOnInvitation: TMsgrSessionManagerOnInvitation;
    FOnAppRegistered: TMsgrSessionManagerOnAppRegistered;
    FOnAppUnRegistered: TMsgrSessionManagerOnAppUnRegistered;
    FOnLockChallenge: TMsgrSessionManagerOnLockChallenge;
    FOnLockResult: TMsgrSessionManagerOnLockResult;
    FOnLockEnable: TMsgrSessionManagerOnLockEnable;
    FOnLockStatusChanged: TMsgrSessionManagerOnLockStatusChanged;
    FOnAppShutdown: TNotifyEvent;
    FIntf:        IMsgrSessionManager;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TMsgrSessionManagerProperties;
    function      GetServerProperties: TMsgrSessionManagerProperties;
{$ENDIF}
    function      GetDefaultInterface: IMsgrSessionManager;
  protected
    procedure InitServerData; override;
    procedure InvokeEvent(DispID: TDispID; var Params: TVariantArray); override;
    function Get_Applications: IDispatch;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IMsgrSessionManager);
    procedure Disconnect; override;
    function CreateSession: IDispatch;
    function GetLaunchingSession(lProcessID: Integer): IDispatch;
    procedure RegisterApplication(const bstrAppGUID: WideString; const bstrAppName: WideString; 
                                  const bstrAppURL: WideString; const bstrPath: WideString; 
                                  ulFlags: Integer);
    procedure UnRegisterApplication(const bstrAppGUID: WideString);
    property DefaultInterface: IMsgrSessionManager read GetDefaultInterface;
    property Applications: IDispatch read Get_Applications;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TMsgrSessionManagerProperties read GetServerProperties;
{$ENDIF}
    property OnInvitation: TMsgrSessionManagerOnInvitation read FOnInvitation write FOnInvitation;
    property OnAppRegistered: TMsgrSessionManagerOnAppRegistered read FOnAppRegistered write FOnAppRegistered;
    property OnAppUnRegistered: TMsgrSessionManagerOnAppUnRegistered read FOnAppUnRegistered write FOnAppUnRegistered;
    property OnLockChallenge: TMsgrSessionManagerOnLockChallenge read FOnLockChallenge write FOnLockChallenge;
    property OnLockResult: TMsgrSessionManagerOnLockResult read FOnLockResult write FOnLockResult;
    property OnLockEnable: TMsgrSessionManagerOnLockEnable read FOnLockEnable write FOnLockEnable;
    property OnLockStatusChanged: TMsgrSessionManagerOnLockStatusChanged read FOnLockStatusChanged write FOnLockStatusChanged;
    property OnAppShutdown: TNotifyEvent read FOnAppShutdown write FOnAppShutdown;
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TMsgrSessionManager
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TMsgrSessionManagerProperties = class(TPersistent)
  private
    FServer:    TMsgrSessionManager;
    function    GetDefaultInterface: IMsgrSessionManager;
    constructor Create(AServer: TMsgrSessionManager);
  protected
    function Get_Applications: IDispatch;
  public
    property DefaultInterface: IMsgrSessionManager read GetDefaultInterface;
  published
  end;
{$ENDIF}


// *********************************************************************//
// The Class CoMsgrSession provides a Create and CreateRemote method to          
// create instances of the default interface IMsgrSession exposed by              
// the CoClass MsgrSession. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoMsgrSession = class
    class function Create: IMsgrSession;
    class function CreateRemote(const MachineName: string): IMsgrSession;
  end;

procedure Register;

resourcestring
  dtlServerPage = 'ActiveX';

  dtlOcxPage = 'ActiveX';

implementation

uses ComObj;

class function CoMessengerPriv.Create: IMessengerPrivate;
begin
  Result := CreateComObject(CLASS_MessengerPriv) as IMessengerPrivate;
end;

class function CoMessengerPriv.CreateRemote(const MachineName: string): IMessengerPrivate;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_MessengerPriv) as IMessengerPrivate;
end;

procedure TMessengerPriv.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{AB1D8565-40E9-4616-984D-98465687E82C}';
    IntfIID:   '{7C95459B-C8E7-4605-B641-45EB06866659}';
    EventIID:  '{D21454F8-43E3-4D64-B1E3-84911BAF207D}';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TMessengerPriv.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    ConnectEvents(punk);
    Fintf:= punk as IMessengerPrivate;
  end;
end;

procedure TMessengerPriv.ConnectTo(svrIntf: IMessengerPrivate);
begin
  Disconnect;
  FIntf := svrIntf;
  ConnectEvents(FIntf);
end;

procedure TMessengerPriv.DisConnect;
begin
  if Fintf <> nil then
  begin
    DisconnectEvents(FIntf);
    FIntf := nil;
  end;
end;

function TMessengerPriv.GetDefaultInterface: IMessengerPrivate;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TMessengerPriv.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TMessengerPrivProperties.Create(Self);
{$ENDIF}
end;

destructor TMessengerPriv.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TMessengerPriv.GetServerProperties: TMessengerPrivProperties;
begin
  Result := FProps;
end;
{$ENDIF}

procedure TMessengerPriv.InvokeEvent(DispID: TDispID; var Params: TVariantArray);
begin
  case DispID of
    -1: Exit;  // DISPID_UNKNOWN
    145: if Assigned(FOnLockChallenge) then
         FOnLockChallenge(Self,
                          Params[0] {Integer},
                          Params[1] {const WideString});
    146: if Assigned(FOnLockResult) then
         FOnLockResult(Self,
                       Params[0] {Integer},
                       Params[1] {WordBool});
    147: if Assigned(FOnLockEnable) then
         FOnLockEnable(Self, Params[0] {WordBool});
    12288: if Assigned(FOnLockStatusChanged) then
         FOnLockStatusChanged(Self, Params[0] {LockStatus});
    1040: if Assigned(FOnAlertReceived) then
         FOnAlertReceived(Self,
                          Params[0] {const WideString},
                          WordBool((TVarData(Params[1]).VPointer)^) {var WordBool});
    1026: if Assigned(FOnContactListAdd) then
         FOnContactListAdd(Self,
                           Params[0] {Integer},
                           Params[1] {const IDispatch});
  end; {case DispID}
end;

procedure TMessengerPriv.EnableAlertEvents(var ppsaSiteIds: PSafeArray);
begin
  DefaultInterface.EnableAlertEvents(ppsaSiteIds);
end;

procedure TMessengerPriv.AddContact(const bstrSiginName: WideString; vService: OleVariant);
begin
  DefaultInterface.AddContact(bstrSiginName, vService);
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TMessengerPrivProperties.Create(AServer: TMessengerPriv);
begin
  inherited Create;
  FServer := AServer;
end;

function TMessengerPrivProperties.GetDefaultInterface: IMessengerPrivate;
begin
  Result := FServer.DefaultInterface;
end;

{$ENDIF}

class function CoMsgrSessionManager.Create: IMsgrSessionManager;
begin
  Result := CreateComObject(CLASS_MsgrSessionManager) as IMsgrSessionManager;
end;

class function CoMsgrSessionManager.CreateRemote(const MachineName: string): IMsgrSessionManager;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_MsgrSessionManager) as IMsgrSessionManager;
end;

procedure TMsgrSessionManager.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{E3A3B1D9-5675-43C0-BF04-37BE11939FB7}';
    IntfIID:   '{305D86C6-6896-4099-91F5-CB7BA7733563}';
    EventIID:  '{52AC8B62-8F88-46CA-902A-1F9106B0A9F4}';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TMsgrSessionManager.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    ConnectEvents(punk);
    Fintf:= punk as IMsgrSessionManager;
  end;
end;

procedure TMsgrSessionManager.ConnectTo(svrIntf: IMsgrSessionManager);
begin
  Disconnect;
  FIntf := svrIntf;
  ConnectEvents(FIntf);
end;

procedure TMsgrSessionManager.DisConnect;
begin
  if Fintf <> nil then
  begin
    DisconnectEvents(FIntf);
    FIntf := nil;
  end;
end;

function TMsgrSessionManager.GetDefaultInterface: IMsgrSessionManager;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TMsgrSessionManager.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TMsgrSessionManagerProperties.Create(Self);
{$ENDIF}
end;

destructor TMsgrSessionManager.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TMsgrSessionManager.GetServerProperties: TMsgrSessionManagerProperties;
begin
  Result := FProps;
end;
{$ENDIF}

procedure TMsgrSessionManager.InvokeEvent(DispID: TDispID; var Params: TVariantArray);
begin
  case DispID of
    -1: Exit;  // DISPID_UNKNOWN
    100: if Assigned(FOnInvitation) then
         FOnInvitation(Self,
                       Params[0] {const IDispatch},
                       Params[1] {const WideString},
                       WordBool((TVarData(Params[2]).VPointer)^) {var WordBool});
    101: if Assigned(FOnAppRegistered) then
         FOnAppRegistered(Self, Params[0] {const WideString});
    102: if Assigned(FOnAppUnRegistered) then
         FOnAppUnRegistered(Self, Params[0] {const WideString});
    145: if Assigned(FOnLockChallenge) then
         FOnLockChallenge(Self,
                          Params[0] {Integer},
                          Params[1] {const WideString});
    146: if Assigned(FOnLockResult) then
         FOnLockResult(Self,
                       Params[0] {Integer},
                       Params[1] {WordBool});
    147: if Assigned(FOnLockEnable) then
         FOnLockEnable(Self, Params[0] {WordBool});
    12288: if Assigned(FOnLockStatusChanged) then
         FOnLockStatusChanged(Self, Params[0] {LockStatus});
    126: if Assigned(FOnAppShutdown) then
         FOnAppShutdown(Self);
  end; {case DispID}
end;

function TMsgrSessionManager.Get_Applications: IDispatch;
begin
    Result := DefaultInterface.Applications;
end;

function TMsgrSessionManager.CreateSession: IDispatch;
begin
  Result := DefaultInterface.CreateSession;
end;

function TMsgrSessionManager.GetLaunchingSession(lProcessID: Integer): IDispatch;
begin
  Result := DefaultInterface.GetLaunchingSession(lProcessID);
end;

procedure TMsgrSessionManager.RegisterApplication(const bstrAppGUID: WideString; 
                                                  const bstrAppName: WideString; 
                                                  const bstrAppURL: WideString; 
                                                  const bstrPath: WideString; ulFlags: Integer);
begin
  DefaultInterface.RegisterApplication(bstrAppGUID, bstrAppName, bstrAppURL, bstrPath, ulFlags);
end;

procedure TMsgrSessionManager.UnRegisterApplication(const bstrAppGUID: WideString);
begin
  DefaultInterface.UnRegisterApplication(bstrAppGUID);
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TMsgrSessionManagerProperties.Create(AServer: TMsgrSessionManager);
begin
  inherited Create;
  FServer := AServer;
end;

function TMsgrSessionManagerProperties.GetDefaultInterface: IMsgrSessionManager;
begin
  Result := FServer.DefaultInterface;
end;

function TMsgrSessionManagerProperties.Get_Applications: IDispatch;
begin
    Result := DefaultInterface.Applications;
end;

{$ENDIF}

class function CoMsgrSession.Create: IMsgrSession;
begin
  Result := CreateComObject(CLASS_MsgrSession) as IMsgrSession;
end;

class function CoMsgrSession.CreateRemote(const MachineName: string): IMsgrSession;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_MsgrSession) as IMsgrSession;
end;

procedure Register;
begin
  RegisterComponents(dtlServerPage, [TMessengerPriv, TMsgrSessionManager]);
end;

end.
