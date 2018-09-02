unit MessengerAPI_TLB;

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
// File generated on 06/04/2007 10:51:38 AM from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\Delphi7SE\Lib\MSN\TYPELIB_2.tlb (1)
// LIBID: {E02AD29E-80F5-46C6-B416-9B3EBDDF057E}
// LCID: 0
// Helpfile: 
// HelpString: Messenger API Type Library
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\System32\stdole2.tlb)
// Errors:
//   Hint: Member 'Property' of 'IMessenger3' changed to 'Property_'
//   Hint: Member 'Property' of 'IMessengerWindow' changed to 'Property_'
//   Hint: Member 'Property' of 'IMessengerContact' changed to 'Property_'
//   Hint: Member 'Property' of 'IMessengerService' changed to 'Property_'
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
  MessengerAPIMajorVersion = 1;
  MessengerAPIMinorVersion = 0;

  LIBID_MessengerAPI: TGUID = '{E02AD29E-80F5-46C6-B416-9B3EBDDF057E}';

  IID_IMessenger: TGUID = '{D50C3186-0F89-48F8-B204-3604629DEE10}';
  IID_IMessenger2: TGUID = '{D50C3286-0F89-48F8-B204-3604629DEE10}';
  IID_IMessenger3: TGUID = '{D50C3386-0F89-48F8-B204-3604629DEE10}';
  DIID_DMessengerEvents: TGUID = '{C9A6A6B6-9BC1-43A5-B06B-E58874EEBC96}';
  IID_IMessengerWindow: TGUID = '{D6B0E4C8-FAD6-4885-B271-0DC5A584ADF8}';
  IID_IMessengerConversationWnd: TGUID = '{D6B0E4C9-FAD6-4885-B271-0DC5A584ADF8}';
  IID_IMessengerContact: TGUID = '{E7479A0F-BB19-44A5-968F-6F41D93EE0BC}';
  IID_IMessengerContacts: TGUID = '{E7479A0D-BB19-44A5-968F-6F41D93EE0BC}';
  IID_IMessengerService: TGUID = '{2E50547C-A8AA-4F60-B57E-1F414711007B}';
  IID_IMessengerServices: TGUID = '{2E50547B-A8AA-4F60-B57E-1F414711007B}';
  IID_IMessengerGroup: TGUID = '{E1AF1038-B884-44CB-A535-1C3C11A3D1DB}';
  IID_IMessengerGroups: TGUID = '{E1AF1028-B884-44CB-A535-1C3C11A3D1DB}';
  CLASS_Messenger: TGUID = '{B69003B3-C55E-4B48-836C-BC5946FC3B28}';

// *********************************************************************//
// Declaration of Enumerations defined in Type Library                    
// *********************************************************************//
// Constants for enum __MIDL___MIDL_itf_msgrua_0000_0007
type
  __MIDL___MIDL_itf_msgrua_0000_0007 = TOleEnum;
const
  MOPT_GENERAL_PAGE = $00000000;
  MOPT_PRIVACY_PAGE = $00000001;
  MOPT_EXCHANGE_PAGE = $00000002;
  MOPT_ACCOUNTS_PAGE = $00000003;
  MOPT_CONNECTION_PAGE = $00000004;
  MOPT_PREFERENCES_PAGE = $00000005;
  MOPT_SERVICES_PAGE = $00000006;
  MOPT_PHONE_PAGE = $00000007;

// Constants for enum __MIDL___MIDL_itf_msgrua_0000_0006
type
  __MIDL___MIDL_itf_msgrua_0000_0006 = TOleEnum;
const
  MPHONE_TYPE_ALL = $FFFFFFFF;
  MPHONE_TYPE_HOME = $00000000;
  MPHONE_TYPE_WORK = $00000001;
  MPHONE_TYPE_MOBILE = $00000002;
  MPHONE_TYPE_CUSTOM = $00000003;

// Constants for enum __MIDL___MIDL_itf_msgrua_0000_0002
type
  __MIDL___MIDL_itf_msgrua_0000_0002 = TOleEnum;
const
  MISTATUS_UNKNOWN = $00000000;
  MISTATUS_OFFLINE = $00000001;
  MISTATUS_ONLINE = $00000002;
  MISTATUS_INVISIBLE = $00000006;
  MISTATUS_BUSY = $0000000A;
  MISTATUS_BE_RIGHT_BACK = $0000000E;
  MISTATUS_IDLE = $00000012;
  MISTATUS_AWAY = $00000022;
  MISTATUS_ON_THE_PHONE = $00000032;
  MISTATUS_OUT_TO_LUNCH = $00000042;
  MISTATUS_LOCAL_FINDING_SERVER = $00000100;
  MISTATUS_LOCAL_CONNECTING_TO_SERVER = $00000200;
  MISTATUS_LOCAL_SYNCHRONIZING_WITH_SERVER = $00000300;
  MISTATUS_LOCAL_DISCONNECTING_FROM_SERVER = $00000400;

// Constants for enum __MIDL___MIDL_itf_msgrua_0000_0008
type
  __MIDL___MIDL_itf_msgrua_0000_0008 = TOleEnum;
const
  MUAFOLDER_INBOX = $00000000;
  MUAFOLDER_ALL_OTHER_FOLDERS = $00000001;

// Constants for enum __MIDL___MIDL_itf_msgrua_0000_0004
type
  __MIDL___MIDL_itf_msgrua_0000_0004 = TOleEnum;
const
  MCONTACTPROP_INVALID_PROPERTY = $FFFFFFFF;
  MCONTACTPROP_GROUPS_PROPERTY = $00000000;
  MCONTACTPROP_EMAIL = $00000001;
  MCONTACTPROP_USERTILE_PATH = $00000002;

// Constants for enum __MIDL___MIDL_itf_msgrua_0000_0010
type
  __MIDL___MIDL_itf_msgrua_0000_0010 = TOleEnum;
const
  MUASORT_GROUPS = $00000000;
  MUASORT_ONOFFLINE = $00000001;

// Constants for enum __MIDL___MIDL_itf_msgrua_0000_0003
type
  __MIDL___MIDL_itf_msgrua_0000_0003 = TOleEnum;
const
  MMESSENGERPROP_VERSION = $00000000;
  MMESSENGERPROP_PLCID = $00000001;

// Constants for enum __MIDL___MIDL_itf_msgrua_0000_0005
type
  __MIDL___MIDL_itf_msgrua_0000_0005 = TOleEnum;
const
  MWINDOWPROP_INVALID_PROPERTY = $FFFFFFFF;
  MWINDOWPROP_VIEW_SIDEBAR = $00000000;
  MWINDOWPROP_VIEW_TOOLBAR = $00000001;

// Constants for enum __MIDL___MIDL_itf_msgrua_0000_0009
type
  __MIDL___MIDL_itf_msgrua_0000_0009 = TOleEnum;
const
  MSERVICEPROP_INVALID_PROPERTY = $FFFFFFFF;

type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  IMessenger = interface;
  IMessengerDisp = dispinterface;
  IMessenger2 = interface;
  IMessenger2Disp = dispinterface;
  IMessenger3 = interface;
  IMessenger3Disp = dispinterface;
  DMessengerEvents = dispinterface;
  IMessengerWindow = interface;
  IMessengerWindowDisp = dispinterface;
  IMessengerConversationWnd = interface;
  IMessengerConversationWndDisp = dispinterface;
  IMessengerContact = interface;
  IMessengerContactDisp = dispinterface;
  IMessengerContacts = interface;
  IMessengerContactsDisp = dispinterface;
  IMessengerService = interface;
  IMessengerServiceDisp = dispinterface;
  IMessengerServices = interface;
  IMessengerServicesDisp = dispinterface;
  IMessengerGroup = interface;
  IMessengerGroupDisp = dispinterface;
  IMessengerGroups = interface;
  IMessengerGroupsDisp = dispinterface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  Messenger = IMessenger3;


// *********************************************************************//
// Declaration of structures, unions and aliases.                         
// *********************************************************************//

  MOPTIONPAGE = __MIDL___MIDL_itf_msgrua_0000_0007; 
  MPHONE_TYPE = __MIDL___MIDL_itf_msgrua_0000_0006; 
  MISTATUS = __MIDL___MIDL_itf_msgrua_0000_0002; 
  MUAFOLDER = __MIDL___MIDL_itf_msgrua_0000_0008; 
  MCONTACTPROPERTY = __MIDL___MIDL_itf_msgrua_0000_0004; 
  MUASORT = __MIDL___MIDL_itf_msgrua_0000_0010; 
  MMESSENGERPROPERTY = __MIDL___MIDL_itf_msgrua_0000_0003; 
  MWINDOWPROPERTY = __MIDL___MIDL_itf_msgrua_0000_0005; 
  MSERVICEPROPERTY = __MIDL___MIDL_itf_msgrua_0000_0009; 

// *********************************************************************//
// Interface: IMessenger
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {D50C3186-0F89-48F8-B204-3604629DEE10}
// *********************************************************************//
  IMessenger = interface(IDispatch)
    ['{D50C3186-0F89-48F8-B204-3604629DEE10}']
    function Get_Window: IDispatch; safecall;
    procedure ViewProfile(vContact: OleVariant); safecall;
    function Get_ReceiveFileDirectory: WideString; safecall;
    function StartVoice(vContact: OleVariant): IDispatch; safecall;
    function InviteApp(vContact: OleVariant; const bstrAppID: WideString): IDispatch; safecall;
    procedure SendMail(vContact: OleVariant); safecall;
    procedure OpenInbox; safecall;
    function SendFile(vContact: OleVariant; const bstrFileName: WideString): IDispatch; safecall;
    procedure Signout; safecall;
    procedure Signin(hwndParent: Integer; const bstrSigninName: WideString; 
                     const bstrPassword: WideString); safecall;
    function GetContact(const bstrSigninName: WideString; const bstrServiceId: WideString): IDispatch; safecall;
    procedure OptionsPages(hwndParent: Integer; MOPTIONPAGE: MOPTIONPAGE); safecall;
    procedure AddContact(hwndParent: Integer; const bstrEMail: WideString); safecall;
    procedure FindContact(hwndParent: Integer; const bstrFirstName: WideString; 
                          const bstrLastName: WideString; vbstrCity: OleVariant; 
                          vbstrState: OleVariant; vbstrCountry: OleVariant); safecall;
    function InstantMessage(vContact: OleVariant): IDispatch; safecall;
    function Phone(vContact: OleVariant; ePhoneNumber: MPHONE_TYPE; const bstrNumber: WideString): IDispatch; safecall;
    procedure MediaWizard(hwndParent: Integer); safecall;
    function Page(vContact: OleVariant): IDispatch; safecall;
    procedure AutoSignin; safecall;
    function Get_MyContacts: IDispatch; safecall;
    function Get_MySigninName: WideString; safecall;
    function Get_MyFriendlyName: WideString; safecall;
    procedure Set_MyStatus(pmStatus: MISTATUS); safecall;
    function Get_MyStatus: MISTATUS; safecall;
    function Get_UnreadEmailCount(mFolder: MUAFOLDER): Integer; safecall;
    function Get_MyServiceName: WideString; safecall;
    function Get_MyPhoneNumber(PhoneType: MPHONE_TYPE): WideString; safecall;
    function Get_MyProperty(ePropType: MCONTACTPROPERTY): OleVariant; safecall;
    procedure Set_MyProperty(ePropType: MCONTACTPROPERTY; pvPropVal: OleVariant); safecall;
    function Get_MyServiceId: WideString; safecall;
    function Get_Services: IDispatch; safecall;
    property Window: IDispatch read Get_Window;
    property ReceiveFileDirectory: WideString read Get_ReceiveFileDirectory;
    property MyContacts: IDispatch read Get_MyContacts;
    property MySigninName: WideString read Get_MySigninName;
    property MyFriendlyName: WideString read Get_MyFriendlyName;
    property MyStatus: MISTATUS read Get_MyStatus write Set_MyStatus;
    property UnreadEmailCount[mFolder: MUAFOLDER]: Integer read Get_UnreadEmailCount;
    property MyServiceName: WideString read Get_MyServiceName;
    property MyPhoneNumber[PhoneType: MPHONE_TYPE]: WideString read Get_MyPhoneNumber;
    property MyProperty[ePropType: MCONTACTPROPERTY]: OleVariant read Get_MyProperty write Set_MyProperty;
    property MyServiceId: WideString read Get_MyServiceId;
    property Services: IDispatch read Get_Services;
  end;

// *********************************************************************//
// DispIntf:  IMessengerDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {D50C3186-0F89-48F8-B204-3604629DEE10}
// *********************************************************************//
  IMessengerDisp = dispinterface
    ['{D50C3186-0F89-48F8-B204-3604629DEE10}']
    property Window: IDispatch readonly dispid 1283;
    procedure ViewProfile(vContact: OleVariant); dispid 1285;
    property ReceiveFileDirectory: WideString readonly dispid 1280;
    function StartVoice(vContact: OleVariant): IDispatch; dispid 1281;
    function InviteApp(vContact: OleVariant; const bstrAppID: WideString): IDispatch; dispid 1295;
    procedure SendMail(vContact: OleVariant); dispid 1298;
    procedure OpenInbox; dispid 1293;
    function SendFile(vContact: OleVariant; const bstrFileName: WideString): IDispatch; dispid 1292;
    procedure Signout; dispid 1291;
    procedure Signin(hwndParent: Integer; const bstrSigninName: WideString; 
                     const bstrPassword: WideString); dispid 1297;
    function GetContact(const bstrSigninName: WideString; const bstrServiceId: WideString): IDispatch; dispid 1286;
    procedure OptionsPages(hwndParent: Integer; MOPTIONPAGE: MOPTIONPAGE); dispid 1287;
    procedure AddContact(hwndParent: Integer; const bstrEMail: WideString); dispid 1288;
    procedure FindContact(hwndParent: Integer; const bstrFirstName: WideString; 
                          const bstrLastName: WideString; vbstrCity: OleVariant; 
                          vbstrState: OleVariant; vbstrCountry: OleVariant); dispid 1289;
    function InstantMessage(vContact: OleVariant): IDispatch; dispid 1290;
    function Phone(vContact: OleVariant; ePhoneNumber: MPHONE_TYPE; const bstrNumber: WideString): IDispatch; dispid 1300;
    procedure MediaWizard(hwndParent: Integer); dispid 1301;
    function Page(vContact: OleVariant): IDispatch; dispid 1302;
    procedure AutoSignin; dispid 1299;
    property MyContacts: IDispatch readonly dispid 1303;
    property MySigninName: WideString readonly dispid 1304;
    property MyFriendlyName: WideString readonly dispid 1282;
    property MyStatus: MISTATUS dispid 1305;
    property UnreadEmailCount[mFolder: MUAFOLDER]: Integer readonly dispid 1284;
    property MyServiceName: WideString readonly dispid 1294;
    property MyPhoneNumber[PhoneType: MPHONE_TYPE]: WideString readonly dispid 1296;
    property MyProperty[ePropType: MCONTACTPROPERTY]: OleVariant dispid 1306;
    property MyServiceId: WideString readonly dispid 1307;
    property Services: IDispatch readonly dispid 1308;
  end;

// *********************************************************************//
// Interface: IMessenger2
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {D50C3286-0F89-48F8-B204-3604629DEE10}
// *********************************************************************//
  IMessenger2 = interface(IMessenger)
    ['{D50C3286-0F89-48F8-B204-3604629DEE10}']
    function Get_ContactsSortOrder: MUASORT; safecall;
    procedure Set_ContactsSortOrder(pSort: MUASORT); safecall;
    function StartVideo(vContact: OleVariant): IDispatch; safecall;
    function Get_MyGroups: IDispatch; safecall;
    function CreateGroup(const bstrName: WideString; vService: OleVariant): IDispatch; safecall;
    property ContactsSortOrder: MUASORT read Get_ContactsSortOrder write Set_ContactsSortOrder;
    property MyGroups: IDispatch read Get_MyGroups;
  end;

// *********************************************************************//
// DispIntf:  IMessenger2Disp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {D50C3286-0F89-48F8-B204-3604629DEE10}
// *********************************************************************//
  IMessenger2Disp = dispinterface
    ['{D50C3286-0F89-48F8-B204-3604629DEE10}']
    property ContactsSortOrder: MUASORT dispid 1313;
    function StartVideo(vContact: OleVariant): IDispatch; dispid 1310;
    property MyGroups: IDispatch readonly dispid 1311;
    function CreateGroup(const bstrName: WideString; vService: OleVariant): IDispatch; dispid 1312;
    property Window: IDispatch readonly dispid 1283;
    procedure ViewProfile(vContact: OleVariant); dispid 1285;
    property ReceiveFileDirectory: WideString readonly dispid 1280;
    function StartVoice(vContact: OleVariant): IDispatch; dispid 1281;
    function InviteApp(vContact: OleVariant; const bstrAppID: WideString): IDispatch; dispid 1295;
    procedure SendMail(vContact: OleVariant); dispid 1298;
    procedure OpenInbox; dispid 1293;
    function SendFile(vContact: OleVariant; const bstrFileName: WideString): IDispatch; dispid 1292;
    procedure Signout; dispid 1291;
    procedure Signin(hwndParent: Integer; const bstrSigninName: WideString; 
                     const bstrPassword: WideString); dispid 1297;
    function GetContact(const bstrSigninName: WideString; const bstrServiceId: WideString): IDispatch; dispid 1286;
    procedure OptionsPages(hwndParent: Integer; MOPTIONPAGE: MOPTIONPAGE); dispid 1287;
    procedure AddContact(hwndParent: Integer; const bstrEMail: WideString); dispid 1288;
    procedure FindContact(hwndParent: Integer; const bstrFirstName: WideString; 
                          const bstrLastName: WideString; vbstrCity: OleVariant; 
                          vbstrState: OleVariant; vbstrCountry: OleVariant); dispid 1289;
    function InstantMessage(vContact: OleVariant): IDispatch; dispid 1290;
    function Phone(vContact: OleVariant; ePhoneNumber: MPHONE_TYPE; const bstrNumber: WideString): IDispatch; dispid 1300;
    procedure MediaWizard(hwndParent: Integer); dispid 1301;
    function Page(vContact: OleVariant): IDispatch; dispid 1302;
    procedure AutoSignin; dispid 1299;
    property MyContacts: IDispatch readonly dispid 1303;
    property MySigninName: WideString readonly dispid 1304;
    property MyFriendlyName: WideString readonly dispid 1282;
    property MyStatus: MISTATUS dispid 1305;
    property UnreadEmailCount[mFolder: MUAFOLDER]: Integer readonly dispid 1284;
    property MyServiceName: WideString readonly dispid 1294;
    property MyPhoneNumber[PhoneType: MPHONE_TYPE]: WideString readonly dispid 1296;
    property MyProperty[ePropType: MCONTACTPROPERTY]: OleVariant dispid 1306;
    property MyServiceId: WideString readonly dispid 1307;
    property Services: IDispatch readonly dispid 1308;
  end;

// *********************************************************************//
// Interface: IMessenger3
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {D50C3386-0F89-48F8-B204-3604629DEE10}
// *********************************************************************//
  IMessenger3 = interface(IMessenger2)
    ['{D50C3386-0F89-48F8-B204-3604629DEE10}']
    function Get_Property_(ePropType: MMESSENGERPROPERTY): OleVariant; safecall;
    procedure Set_Property_(ePropType: MMESSENGERPROPERTY; pvPropVal: OleVariant); safecall;
    property Property_[ePropType: MMESSENGERPROPERTY]: OleVariant read Get_Property_ write Set_Property_;
  end;

// *********************************************************************//
// DispIntf:  IMessenger3Disp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {D50C3386-0F89-48F8-B204-3604629DEE10}
// *********************************************************************//
  IMessenger3Disp = dispinterface
    ['{D50C3386-0F89-48F8-B204-3604629DEE10}']
    property Property_[ePropType: MMESSENGERPROPERTY]: OleVariant dispid 1314;
    property ContactsSortOrder: MUASORT dispid 1313;
    function StartVideo(vContact: OleVariant): IDispatch; dispid 1310;
    property MyGroups: IDispatch readonly dispid 1311;
    function CreateGroup(const bstrName: WideString; vService: OleVariant): IDispatch; dispid 1312;
    property Window: IDispatch readonly dispid 1283;
    procedure ViewProfile(vContact: OleVariant); dispid 1285;
    property ReceiveFileDirectory: WideString readonly dispid 1280;
    function StartVoice(vContact: OleVariant): IDispatch; dispid 1281;
    function InviteApp(vContact: OleVariant; const bstrAppID: WideString): IDispatch; dispid 1295;
    procedure SendMail(vContact: OleVariant); dispid 1298;
    procedure OpenInbox; dispid 1293;
    function SendFile(vContact: OleVariant; const bstrFileName: WideString): IDispatch; dispid 1292;
    procedure Signout; dispid 1291;
    procedure Signin(hwndParent: Integer; const bstrSigninName: WideString; 
                     const bstrPassword: WideString); dispid 1297;
    function GetContact(const bstrSigninName: WideString; const bstrServiceId: WideString): IDispatch; dispid 1286;
    procedure OptionsPages(hwndParent: Integer; MOPTIONPAGE: MOPTIONPAGE); dispid 1287;
    procedure AddContact(hwndParent: Integer; const bstrEMail: WideString); dispid 1288;
    procedure FindContact(hwndParent: Integer; const bstrFirstName: WideString; 
                          const bstrLastName: WideString; vbstrCity: OleVariant; 
                          vbstrState: OleVariant; vbstrCountry: OleVariant); dispid 1289;
    function InstantMessage(vContact: OleVariant): IDispatch; dispid 1290;
    function Phone(vContact: OleVariant; ePhoneNumber: MPHONE_TYPE; const bstrNumber: WideString): IDispatch; dispid 1300;
    procedure MediaWizard(hwndParent: Integer); dispid 1301;
    function Page(vContact: OleVariant): IDispatch; dispid 1302;
    procedure AutoSignin; dispid 1299;
    property MyContacts: IDispatch readonly dispid 1303;
    property MySigninName: WideString readonly dispid 1304;
    property MyFriendlyName: WideString readonly dispid 1282;
    property MyStatus: MISTATUS dispid 1305;
    property UnreadEmailCount[mFolder: MUAFOLDER]: Integer readonly dispid 1284;
    property MyServiceName: WideString readonly dispid 1294;
    property MyPhoneNumber[PhoneType: MPHONE_TYPE]: WideString readonly dispid 1296;
    property MyProperty[ePropType: MCONTACTPROPERTY]: OleVariant dispid 1306;
    property MyServiceId: WideString readonly dispid 1307;
    property Services: IDispatch readonly dispid 1308;
  end;

// *********************************************************************//
// DispIntf:  DMessengerEvents
// Flags:     (4112) Hidden Dispatchable
// GUID:      {C9A6A6B6-9BC1-43A5-B06B-E58874EEBC96}
// *********************************************************************//
  DMessengerEvents = dispinterface
    ['{C9A6A6B6-9BC1-43A5-B06B-E58874EEBC96}']
    procedure OnGroupAdded(hr: Integer; const pMGroup: IDispatch); dispid 1045;
    procedure OnGroupRemoved(hr: Integer; const pMGroup: IDispatch); dispid 1046;
    procedure OnGroupNameChanged(hr: Integer; const pMGroup: IDispatch); dispid 1047;
    procedure OnContactAddedToGroup(hr: Integer; const pMGroup: IDispatch; 
                                    const pMContact: IDispatch); dispid 1048;
    procedure OnContactRemovedFromGroup(hr: Integer; const pMGroup: IDispatch; 
                                        const pMContact: IDispatch); dispid 1049;
    procedure OnIMWindowCreated(const pIMWindow: IDispatch); dispid 1041;
    procedure OnIMWindowDestroyed(const pIMWindow: IDispatch); dispid 1042;
    procedure OnIMWindowContactAdded(const pContact: IDispatch; const pIMWindow: IDispatch); dispid 1043;
    procedure OnIMWindowContactRemoved(const pContact: IDispatch; const pIMWindow: IDispatch); dispid 1044;
    procedure OnAppShutdown; dispid 1032;
    procedure OnSignin(hr: Integer); dispid 1024;
    procedure OnSignout; dispid 1025;
    procedure OnContactListAdd(hr: Integer; const pMContact: IDispatch); dispid 1026;
    procedure OnContactListRemove(hr: Integer; const pMContact: IDispatch); dispid 1027;
    procedure OnMyFriendlyNameChange(hr: Integer; const bstrPrevFriendlyName: WideString); dispid 1029;
    procedure OnMyStatusChange(hr: Integer; mMyStatus: MISTATUS); dispid 1031;
    procedure OnMyPhoneChange(PhoneType: MPHONE_TYPE; const bstrNumber: WideString); dispid 1038;
    procedure OnMyPropertyChange(hr: Integer; ePropType: MCONTACTPROPERTY; vPropVal: OleVariant); dispid 1033;
    procedure OnContactFriendlyNameChange(hr: Integer; const pMContact: IDispatch; 
                                          const bstrPrevFriendlyName: WideString); dispid 1028;
    procedure OnContactStatusChange(const pMContact: IDispatch; mStatus: MISTATUS); dispid 1030;
    procedure OnContactPropertyChange(hr: Integer; const pContact: IDispatch; 
                                      ePropType: MCONTACTPROPERTY; vPropVal: OleVariant); dispid 1034;
    procedure OnContactBlockChange(hr: Integer; const pContact: IDispatch; pBoolBlock: WordBool); dispid 1035;
    procedure OnContactPagerChange(hr: Integer; const pContact: IDispatch; pBoolPage: WordBool); dispid 1036;
    procedure OnContactPhoneChange(hr: Integer; const pContact: IDispatch; PhoneType: MPHONE_TYPE; 
                                   const bstrNumber: WideString); dispid 1037;
    procedure OnUnreadEmailChange(mFolder: MUAFOLDER; cUnreadEmail: Integer; 
                                  var pBoolfEnableDefault: WordBool); dispid 1039;
    procedure OnEmoticonListChange; dispid 1050;
  end;

// *********************************************************************//
// Interface: IMessengerWindow
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {D6B0E4C8-FAD6-4885-B271-0DC5A584ADF8}
// *********************************************************************//
  IMessengerWindow = interface(IDispatch)
    ['{D6B0E4C8-FAD6-4885-B271-0DC5A584ADF8}']
    procedure Close; safecall;
    function Get_HWND: Integer; safecall;
    function Get_Left: Integer; safecall;
    procedure Set_Left(plLeft: Integer); safecall;
    function Get_Top: Integer; safecall;
    procedure Set_Top(plTop: Integer); safecall;
    function Get_Width: Integer; safecall;
    procedure Set_Width(plWidth: Integer); safecall;
    function Get_Height: Integer; safecall;
    procedure Set_Height(plHeight: Integer); safecall;
    function Get_IsClosed: WordBool; safecall;
    procedure Show; safecall;
    function Get_Property_(ePropType: MWINDOWPROPERTY): OleVariant; safecall;
    procedure Set_Property_(ePropType: MWINDOWPROPERTY; pvPropVal: OleVariant); safecall;
    property HWND: Integer read Get_HWND;
    property Left: Integer read Get_Left write Set_Left;
    property Top: Integer read Get_Top write Set_Top;
    property Width: Integer read Get_Width write Set_Width;
    property Height: Integer read Get_Height write Set_Height;
    property IsClosed: WordBool read Get_IsClosed;
    property Property_[ePropType: MWINDOWPROPERTY]: OleVariant read Get_Property_ write Set_Property_;
  end;

// *********************************************************************//
// DispIntf:  IMessengerWindowDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {D6B0E4C8-FAD6-4885-B271-0DC5A584ADF8}
// *********************************************************************//
  IMessengerWindowDisp = dispinterface
    ['{D6B0E4C8-FAD6-4885-B271-0DC5A584ADF8}']
    procedure Close; dispid 2053;
    property HWND: Integer readonly dispid 2048;
    property Left: Integer dispid 2049;
    property Top: Integer dispid 2050;
    property Width: Integer dispid 2051;
    property Height: Integer dispid 2052;
    property IsClosed: WordBool readonly dispid 2055;
    procedure Show; dispid 2054;
    property Property_[ePropType: MWINDOWPROPERTY]: OleVariant dispid 2056;
  end;

// *********************************************************************//
// Interface: IMessengerConversationWnd
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {D6B0E4C9-FAD6-4885-B271-0DC5A584ADF8}
// *********************************************************************//
  IMessengerConversationWnd = interface(IMessengerWindow)
    ['{D6B0E4C9-FAD6-4885-B271-0DC5A584ADF8}']
    function Get_Contacts: IDispatch; safecall;
    function Get_History: WideString; safecall;
    procedure AddContact(vContact: OleVariant); safecall;
    property Contacts: IDispatch read Get_Contacts;
    property History: WideString read Get_History;
  end;

// *********************************************************************//
// DispIntf:  IMessengerConversationWndDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {D6B0E4C9-FAD6-4885-B271-0DC5A584ADF8}
// *********************************************************************//
  IMessengerConversationWndDisp = dispinterface
    ['{D6B0E4C9-FAD6-4885-B271-0DC5A584ADF8}']
    property Contacts: IDispatch readonly dispid 2057;
    property History: WideString readonly dispid 2058;
    procedure AddContact(vContact: OleVariant); dispid 2059;
    procedure Close; dispid 2053;
    property HWND: Integer readonly dispid 2048;
    property Left: Integer dispid 2049;
    property Top: Integer dispid 2050;
    property Width: Integer dispid 2051;
    property Height: Integer dispid 2052;
    property IsClosed: WordBool readonly dispid 2055;
    procedure Show; dispid 2054;
    property Property_[ePropType: MWINDOWPROPERTY]: OleVariant dispid 2056;
  end;

// *********************************************************************//
// Interface: IMessengerContact
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {E7479A0F-BB19-44A5-968F-6F41D93EE0BC}
// *********************************************************************//
  IMessengerContact = interface(IDispatch)
    ['{E7479A0F-BB19-44A5-968F-6F41D93EE0BC}']
    function Get_FriendlyName: WideString; safecall;
    function Get_Status: MISTATUS; safecall;
    function Get_SigninName: WideString; safecall;
    function Get_ServiceName: WideString; safecall;
    function Get_Blocked: WordBool; safecall;
    procedure Set_Blocked(pBoolBlock: WordBool); safecall;
    function Get_CanPage: WordBool; safecall;
    function Get_PhoneNumber(PhoneType: MPHONE_TYPE): WideString; safecall;
    function Get_IsSelf: WordBool; safecall;
    function Get_Property_(ePropType: MCONTACTPROPERTY): OleVariant; safecall;
    procedure Set_Property_(ePropType: MCONTACTPROPERTY; pvPropVal: OleVariant); safecall;
    function Get_ServiceId: WideString; safecall;
    property FriendlyName: WideString read Get_FriendlyName;
    property Status: MISTATUS read Get_Status;
    property SigninName: WideString read Get_SigninName;
    property ServiceName: WideString read Get_ServiceName;
    property Blocked: WordBool read Get_Blocked write Set_Blocked;
    property CanPage: WordBool read Get_CanPage;
    property PhoneNumber[PhoneType: MPHONE_TYPE]: WideString read Get_PhoneNumber;
    property IsSelf: WordBool read Get_IsSelf;
    property Property_[ePropType: MCONTACTPROPERTY]: OleVariant read Get_Property_ write Set_Property_;
    property ServiceId: WideString read Get_ServiceId;
  end;

// *********************************************************************//
// DispIntf:  IMessengerContactDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {E7479A0F-BB19-44A5-968F-6F41D93EE0BC}
// *********************************************************************//
  IMessengerContactDisp = dispinterface
    ['{E7479A0F-BB19-44A5-968F-6F41D93EE0BC}']
    property FriendlyName: WideString readonly dispid 1536;
    property Status: MISTATUS readonly dispid 1537;
    property SigninName: WideString readonly dispid 1538;
    property ServiceName: WideString readonly dispid 1539;
    property Blocked: WordBool dispid 1540;
    property CanPage: WordBool readonly dispid 1543;
    property PhoneNumber[PhoneType: MPHONE_TYPE]: WideString readonly dispid 1544;
    property IsSelf: WordBool readonly dispid 1541;
    property Property_[ePropType: MCONTACTPROPERTY]: OleVariant dispid 1542;
    property ServiceId: WideString readonly dispid 1545;
  end;

// *********************************************************************//
// Interface: IMessengerContacts
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {E7479A0D-BB19-44A5-968F-6F41D93EE0BC}
// *********************************************************************//
  IMessengerContacts = interface(IDispatch)
    ['{E7479A0D-BB19-44A5-968F-6F41D93EE0BC}']
    function Get_Count: Integer; safecall;
    function Item(Index: Integer): IDispatch; safecall;
    procedure Remove(const pMContact: IDispatch); safecall;
    function Get__NewEnum: IUnknown; safecall;
    property Count: Integer read Get_Count;
    property _NewEnum: IUnknown read Get__NewEnum;
  end;

// *********************************************************************//
// DispIntf:  IMessengerContactsDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {E7479A0D-BB19-44A5-968F-6F41D93EE0BC}
// *********************************************************************//
  IMessengerContactsDisp = dispinterface
    ['{E7479A0D-BB19-44A5-968F-6F41D93EE0BC}']
    property Count: Integer readonly dispid 1792;
    function Item(Index: Integer): IDispatch; dispid 0;
    procedure Remove(const pMContact: IDispatch); dispid 1793;
    property _NewEnum: IUnknown readonly dispid -4;
  end;

// *********************************************************************//
// Interface: IMessengerService
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {2E50547C-A8AA-4F60-B57E-1F414711007B}
// *********************************************************************//
  IMessengerService = interface(IDispatch)
    ['{2E50547C-A8AA-4F60-B57E-1F414711007B}']
    function Get_ServiceName: WideString; safecall;
    function Get_ServiceId: WideString; safecall;
    function Get_MyFriendlyName: WideString; safecall;
    function Get_MyStatus: MISTATUS; safecall;
    function Get_MySigninName: WideString; safecall;
    function Get_Property_(ePropType: MSERVICEPROPERTY): OleVariant; safecall;
    procedure Set_Property_(ePropType: MSERVICEPROPERTY; pvPropVal: OleVariant); safecall;
    property ServiceName: WideString read Get_ServiceName;
    property ServiceId: WideString read Get_ServiceId;
    property MyFriendlyName: WideString read Get_MyFriendlyName;
    property MyStatus: MISTATUS read Get_MyStatus;
    property MySigninName: WideString read Get_MySigninName;
    property Property_[ePropType: MSERVICEPROPERTY]: OleVariant read Get_Property_ write Set_Property_;
  end;

// *********************************************************************//
// DispIntf:  IMessengerServiceDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {2E50547C-A8AA-4F60-B57E-1F414711007B}
// *********************************************************************//
  IMessengerServiceDisp = dispinterface
    ['{2E50547C-A8AA-4F60-B57E-1F414711007B}']
    property ServiceName: WideString readonly dispid 2178;
    property ServiceId: WideString readonly dispid 2183;
    property MyFriendlyName: WideString readonly dispid 2179;
    property MyStatus: MISTATUS readonly dispid 2181;
    property MySigninName: WideString readonly dispid 2184;
    property Property_[ePropType: MSERVICEPROPERTY]: OleVariant dispid 2182;
  end;

// *********************************************************************//
// Interface: IMessengerServices
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {2E50547B-A8AA-4F60-B57E-1F414711007B}
// *********************************************************************//
  IMessengerServices = interface(IDispatch)
    ['{2E50547B-A8AA-4F60-B57E-1F414711007B}']
    function Get_PrimaryService: IDispatch; safecall;
    function Get_Count: Integer; safecall;
    function Item(Index: Integer): IDispatch; safecall;
    function Get__NewEnum: IUnknown; safecall;
    property PrimaryService: IDispatch read Get_PrimaryService;
    property Count: Integer read Get_Count;
    property _NewEnum: IUnknown read Get__NewEnum;
  end;

// *********************************************************************//
// DispIntf:  IMessengerServicesDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {2E50547B-A8AA-4F60-B57E-1F414711007B}
// *********************************************************************//
  IMessengerServicesDisp = dispinterface
    ['{2E50547B-A8AA-4F60-B57E-1F414711007B}']
    property PrimaryService: IDispatch readonly dispid 2176;
    property Count: Integer readonly dispid 2177;
    function Item(Index: Integer): IDispatch; dispid 0;
    property _NewEnum: IUnknown readonly dispid -4;
  end;

// *********************************************************************//
// Interface: IMessengerGroup
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {E1AF1038-B884-44CB-A535-1C3C11A3D1DB}
// *********************************************************************//
  IMessengerGroup = interface(IDispatch)
    ['{E1AF1038-B884-44CB-A535-1C3C11A3D1DB}']
    function Get_Contacts: IDispatch; safecall;
    function Get_Name: WideString; safecall;
    procedure Set_Name(const bstrName: WideString); safecall;
    procedure AddContact(vContact: OleVariant); safecall;
    procedure RemoveContact(vContact: OleVariant); safecall;
    function Get_Service: IDispatch; safecall;
    property Contacts: IDispatch read Get_Contacts;
    property Name: WideString read Get_Name write Set_Name;
    property Service: IDispatch read Get_Service;
  end;

// *********************************************************************//
// DispIntf:  IMessengerGroupDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {E1AF1038-B884-44CB-A535-1C3C11A3D1DB}
// *********************************************************************//
  IMessengerGroupDisp = dispinterface
    ['{E1AF1038-B884-44CB-A535-1C3C11A3D1DB}']
    property Contacts: IDispatch readonly dispid 1667;
    property Name: WideString dispid 1668;
    procedure AddContact(vContact: OleVariant); dispid 1669;
    procedure RemoveContact(vContact: OleVariant); dispid 1670;
    property Service: IDispatch readonly dispid 1671;
  end;

// *********************************************************************//
// Interface: IMessengerGroups
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {E1AF1028-B884-44CB-A535-1C3C11A3D1DB}
// *********************************************************************//
  IMessengerGroups = interface(IDispatch)
    ['{E1AF1028-B884-44CB-A535-1C3C11A3D1DB}']
    procedure Remove(const pGroup: IDispatch); safecall;
    function Get_Count: Integer; safecall;
    function Item(Index: Integer): IDispatch; safecall;
    function Get__NewEnum: IUnknown; safecall;
    property Count: Integer read Get_Count;
    property _NewEnum: IUnknown read Get__NewEnum;
  end;

// *********************************************************************//
// DispIntf:  IMessengerGroupsDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {E1AF1028-B884-44CB-A535-1C3C11A3D1DB}
// *********************************************************************//
  IMessengerGroupsDisp = dispinterface
    ['{E1AF1028-B884-44CB-A535-1C3C11A3D1DB}']
    procedure Remove(const pGroup: IDispatch); dispid 1665;
    property Count: Integer readonly dispid 1666;
    function Item(Index: Integer): IDispatch; dispid 0;
    property _NewEnum: IUnknown readonly dispid -4;
  end;

// *********************************************************************//
// The Class CoMessenger provides a Create and CreateRemote method to          
// create instances of the default interface IMessenger3 exposed by              
// the CoClass Messenger. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoMessenger = class
    class function Create: IMessenger3;
    class function CreateRemote(const MachineName: string): IMessenger3;
  end;

implementation

uses ComObj;

class function CoMessenger.Create: IMessenger3;
begin
  Result := CreateComObject(CLASS_Messenger) as IMessenger3;
end;



class function CoMessenger.CreateRemote(const MachineName: string): IMessenger3;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_Messenger) as IMessenger3;
end;

end.
