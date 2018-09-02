unit DispImpl_TLB;

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
// File generated on 06/04/2007 10:51:55 AM from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\Delphi7SE\Lib\MSN\TYPELIB_3.tlb (1)
// LIBID: {9071135F-52C4-4D38-A787-2C5367CB5075}
// LCID: 0
// Helpfile: 
// HelpString: Messenger Dispatch Implementation
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

uses Windows, ActiveX, Classes, Graphics, StdVCL, Variants;
  

// *********************************************************************//
// GUIDS declared in the TypeLibrary. Following prefixes are used:        
//   Type Libraries     : LIBID_xxxx                                      
//   CoClasses          : CLASS_xxxx                                      
//   DISPInterfaces     : DIID_xxxx                                       
//   Non-DISP interfaces: IID_xxxx                                        
// *********************************************************************//
const
  // TypeLibrary Major and minor versions
  DispImplMajorVersion = 1;
  DispImplMinorVersion = 0;

  LIBID_DispImpl: TGUID = '{9071135F-52C4-4D38-A787-2C5367CB5075}';

  IID_IMsgrWebScriptManager: TGUID = '{CB643558-61CD-42B2-A9A5-496A7884AD61}';
  IID_IMsgrPassportClient: TGUID = '{97C3808A-ECA1-4CA6-8D09-122A3CC54B3B}';
  IID_IMsgrHost: TGUID = '{06F6EA9D-88B0-45A9-9F26-CE0898D9EA1C}';
  IID_IMsgrHost2: TGUID = '{15B18DA9-EAA0-43C4-BDF7-E1CB3511EC62}';
  IID_IMsgrDownloadPicturesHost: TGUID = '{1B11F615-5B1F-488D-9E85-5C68A283EB19}';
  IID_IMsgrCTHost: TGUID = '{0F66BF7B-F997-4A4B-A465-EDEEB05523B6}';
  IID_ICTSysSettings: TGUID = '{C2325C63-1493-42B8-BC59-D41DE180B793}';
  IID_ICTAppCompat: TGUID = '{AD7F317C-679F-4E2C-81C0-EFCF7DF9E70F}';
  IID_ICTDiagnostic: TGUID = '{5AD2732D-9388-4664-956C-92EEA10CD8A3}';
type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  IMsgrWebScriptManager = interface;
  IMsgrWebScriptManagerDisp = dispinterface;
  IMsgrPassportClient = interface;
  IMsgrPassportClientDisp = dispinterface;
  IMsgrHost = interface;
  IMsgrHostDisp = dispinterface;
  IMsgrHost2 = interface;
  IMsgrHost2Disp = dispinterface;
  IMsgrDownloadPicturesHost = interface;
  IMsgrDownloadPicturesHostDisp = dispinterface;
  IMsgrCTHost = interface;
  IMsgrCTHostDisp = dispinterface;
  ICTSysSettings = interface;
  ICTSysSettingsDisp = dispinterface;
  ICTAppCompat = interface;
  ICTAppCompatDisp = dispinterface;
  ICTDiagnostic = interface;
  ICTDiagnosticDisp = dispinterface;

// *********************************************************************//
// Interface: IMsgrWebScriptManager
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {CB643558-61CD-42B2-A9A5-496A7884AD61}
// *********************************************************************//
  IMsgrWebScriptManager = interface(IDispatch)
    ['{CB643558-61CD-42B2-A9A5-496A7884AD61}']
    function Get_PassportClient: IDispatch; safecall;
    function Get_MsgrHost: IDispatch; safecall;
    function Get_MsgrHost2: IDispatch; safecall;
    property PassportClient: IDispatch read Get_PassportClient;
    property MsgrHost: IDispatch read Get_MsgrHost;
    property MsgrHost2: IDispatch read Get_MsgrHost2;
  end;

// *********************************************************************//
// DispIntf:  IMsgrWebScriptManagerDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {CB643558-61CD-42B2-A9A5-496A7884AD61}
// *********************************************************************//
  IMsgrWebScriptManagerDisp = dispinterface
    ['{CB643558-61CD-42B2-A9A5-496A7884AD61}']
    property PassportClient: IDispatch readonly dispid 1610743808;
    property MsgrHost: IDispatch readonly dispid 1610743809;
    property MsgrHost2: IDispatch readonly dispid 1610743810;
  end;

// *********************************************************************//
// Interface: IMsgrPassportClient
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {97C3808A-ECA1-4CA6-8D09-122A3CC54B3B}
// *********************************************************************//
  IMsgrPassportClient = interface(IDispatch)
    ['{97C3808A-ECA1-4CA6-8D09-122A3CC54B3B}']
    procedure SwitchUser(lState: Integer; const bstrSwitchURL: WideString; 
                         const bstrStayURL: WideString); safecall;
  end;

// *********************************************************************//
// DispIntf:  IMsgrPassportClientDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {97C3808A-ECA1-4CA6-8D09-122A3CC54B3B}
// *********************************************************************//
  IMsgrPassportClientDisp = dispinterface
    ['{97C3808A-ECA1-4CA6-8D09-122A3CC54B3B}']
    procedure SwitchUser(lState: Integer; const bstrSwitchURL: WideString; 
                         const bstrStayURL: WideString); dispid 1610743808;
  end;

// *********************************************************************//
// Interface: IMsgrHost
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {06F6EA9D-88B0-45A9-9F26-CE0898D9EA1C}
// *********************************************************************//
  IMsgrHost = interface(IDispatch)
    ['{06F6EA9D-88B0-45A9-9F26-CE0898D9EA1C}']
    procedure OpenWithAuth(const bstrURL: WideString; lSiteID: Integer); safecall;
    procedure ShowMessengerHostWnd(bPopInfront: WordBool); safecall;
    procedure LaunchP4App(const bstrAppID: WideString; const bstrUserID: WideString); safecall;
  end;

// *********************************************************************//
// DispIntf:  IMsgrHostDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {06F6EA9D-88B0-45A9-9F26-CE0898D9EA1C}
// *********************************************************************//
  IMsgrHostDisp = dispinterface
    ['{06F6EA9D-88B0-45A9-9F26-CE0898D9EA1C}']
    procedure OpenWithAuth(const bstrURL: WideString; lSiteID: Integer); dispid 100;
    procedure ShowMessengerHostWnd(bPopInfront: WordBool); dispid 101;
    procedure LaunchP4App(const bstrAppID: WideString; const bstrUserID: WideString); dispid 102;
  end;

// *********************************************************************//
// Interface: IMsgrHost2
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {15B18DA9-EAA0-43C4-BDF7-E1CB3511EC62}
// *********************************************************************//
  IMsgrHost2 = interface(IMsgrHost)
    ['{15B18DA9-EAA0-43C4-BDF7-E1CB3511EC62}']
    function Get_LocalFriendlyName: WideString; safecall;
    procedure ShowTab(const bstrTabID: WideString); safecall;
    procedure OpenBrowser(const bstrURL: WideString; lSiteID: Integer; fNewProcess: WordBool; 
                          const bstrFeatures: WideString); safecall;
    property LocalFriendlyName: WideString read Get_LocalFriendlyName;
  end;

// *********************************************************************//
// DispIntf:  IMsgrHost2Disp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {15B18DA9-EAA0-43C4-BDF7-E1CB3511EC62}
// *********************************************************************//
  IMsgrHost2Disp = dispinterface
    ['{15B18DA9-EAA0-43C4-BDF7-E1CB3511EC62}']
    property LocalFriendlyName: WideString readonly dispid 103;
    procedure ShowTab(const bstrTabID: WideString); dispid 104;
    procedure OpenBrowser(const bstrURL: WideString; lSiteID: Integer; fNewProcess: WordBool; 
                          const bstrFeatures: WideString); dispid 105;
    procedure OpenWithAuth(const bstrURL: WideString; lSiteID: Integer); dispid 100;
    procedure ShowMessengerHostWnd(bPopInfront: WordBool); dispid 101;
    procedure LaunchP4App(const bstrAppID: WideString; const bstrUserID: WideString); dispid 102;
  end;

// *********************************************************************//
// Interface: IMsgrDownloadPicturesHost
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {1B11F615-5B1F-488D-9E85-5C68A283EB19}
// *********************************************************************//
  IMsgrDownloadPicturesHost = interface(IDispatch)
    ['{1B11F615-5B1F-488D-9E85-5C68A283EB19}']
    procedure PictureInfo(const bstrFriendlyName: WideString; const bstrURL: WideString; 
                          const bstrImageType: WideString); safecall;
  end;

// *********************************************************************//
// DispIntf:  IMsgrDownloadPicturesHostDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {1B11F615-5B1F-488D-9E85-5C68A283EB19}
// *********************************************************************//
  IMsgrDownloadPicturesHostDisp = dispinterface
    ['{1B11F615-5B1F-488D-9E85-5C68A283EB19}']
    procedure PictureInfo(const bstrFriendlyName: WideString; const bstrURL: WideString; 
                          const bstrImageType: WideString); dispid 1610743808;
  end;

// *********************************************************************//
// Interface: IMsgrCTHost
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {0F66BF7B-F997-4A4B-A465-EDEEB05523B6}
// *********************************************************************//
  IMsgrCTHost = interface(IDispatch)
    ['{0F66BF7B-F997-4A4B-A465-EDEEB05523B6}']
    function Get_SysSettings: IDispatch; safecall;
    function Get_AppCompat: IDispatch; safecall;
    function Get_Diagnostic: IDispatch; safecall;
    function Get_LastRun: Integer; safecall;
    function CheckConnectivity(fRedirect: Integer): Integer; safecall;
    procedure CloseWindow; safecall;
    function LaunchPassportPage: Integer; safecall;
    procedure PromptPassword; safecall;
    procedure SetLastRunNow; safecall;
    function GetXML: WideString; safecall;
    procedure GoToMoreHelp(const bstrKeyword: WideString; fTopic: Integer); safecall;
    procedure GoToLocalErrorPage; safecall;
    procedure ClearPassword; safecall;
    property SysSettings: IDispatch read Get_SysSettings;
    property AppCompat: IDispatch read Get_AppCompat;
    property Diagnostic: IDispatch read Get_Diagnostic;
    property LastRun: Integer read Get_LastRun;
  end;

// *********************************************************************//
// DispIntf:  IMsgrCTHostDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {0F66BF7B-F997-4A4B-A465-EDEEB05523B6}
// *********************************************************************//
  IMsgrCTHostDisp = dispinterface
    ['{0F66BF7B-F997-4A4B-A465-EDEEB05523B6}']
    property SysSettings: IDispatch readonly dispid 1610743808;
    property AppCompat: IDispatch readonly dispid 1610743809;
    property Diagnostic: IDispatch readonly dispid 1610743810;
    property LastRun: Integer readonly dispid 1610743811;
    function CheckConnectivity(fRedirect: Integer): Integer; dispid 1610743812;
    procedure CloseWindow; dispid 1610743813;
    function LaunchPassportPage: Integer; dispid 1610743814;
    procedure PromptPassword; dispid 1610743815;
    procedure SetLastRunNow; dispid 1610743816;
    function GetXML: WideString; dispid 1610743817;
    procedure GoToMoreHelp(const bstrKeyword: WideString; fTopic: Integer); dispid 1610743818;
    procedure GoToLocalErrorPage; dispid 1610743819;
    procedure ClearPassword; dispid 1610743820;
  end;

// *********************************************************************//
// Interface: ICTSysSettings
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {C2325C63-1493-42B8-BC59-D41DE180B793}
// *********************************************************************//
  ICTSysSettings = interface(IDispatch)
    ['{C2325C63-1493-42B8-BC59-D41DE180B793}']
    function GetSettingsXML: WideString; safecall;
    function RegMatchDWORD(iHKEY: SYSINT; const bstrSubKey: WideString; 
                           const bstrValue: WideString; lData: Integer): Integer; safecall;
    function RegMatchString(iHKEY: SYSINT; const bstrSubKey: WideString; 
                            const bstrValue: WideString; const bstrData: WideString): Integer; safecall;
    function RegExists(iHKEY: SYSINT; const bstrSubKey: WideString; const bstrValue: WideString): Integer; safecall;
    function GetUTCTime: OleVariant; safecall;
    function GetWinsockVer: LongWord; safecall;
    function GetFileVer(const strFile: WideString): LongWord; safecall;
    procedure EnableIESSL; safecall;
    function IsSSLEnabled: Integer; safecall;
    function IsMsgrProxyEnabled: Integer; safecall;
    procedure SetMsgrProxy(dwProxyType: LongWord; const bstrServer: WideString; iPort: SYSINT); safecall;
    procedure ResetMsgrProxy; safecall;
    procedure ClearDAServerAndConfigVersion; safecall;
  end;

// *********************************************************************//
// DispIntf:  ICTSysSettingsDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {C2325C63-1493-42B8-BC59-D41DE180B793}
// *********************************************************************//
  ICTSysSettingsDisp = dispinterface
    ['{C2325C63-1493-42B8-BC59-D41DE180B793}']
    function GetSettingsXML: WideString; dispid 1610743808;
    function RegMatchDWORD(iHKEY: SYSINT; const bstrSubKey: WideString; 
                           const bstrValue: WideString; lData: Integer): Integer; dispid 1610743809;
    function RegMatchString(iHKEY: SYSINT; const bstrSubKey: WideString; 
                            const bstrValue: WideString; const bstrData: WideString): Integer; dispid 1610743810;
    function RegExists(iHKEY: SYSINT; const bstrSubKey: WideString; const bstrValue: WideString): Integer; dispid 1610743811;
    function GetUTCTime: OleVariant; dispid 1610743812;
    function GetWinsockVer: LongWord; dispid 1610743813;
    function GetFileVer(const strFile: WideString): LongWord; dispid 1610743814;
    procedure EnableIESSL; dispid 1610743815;
    function IsSSLEnabled: Integer; dispid 1610743816;
    function IsMsgrProxyEnabled: Integer; dispid 1610743817;
    procedure SetMsgrProxy(dwProxyType: LongWord; const bstrServer: WideString; iPort: SYSINT); dispid 1610743818;
    procedure ResetMsgrProxy; dispid 1610743819;
    procedure ClearDAServerAndConfigVersion; dispid 1610743820;
  end;

// *********************************************************************//
// Interface: ICTAppCompat
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {AD7F317C-679F-4E2C-81C0-EFCF7DF9E70F}
// *********************************************************************//
  ICTAppCompat = interface(IDispatch)
    ['{AD7F317C-679F-4E2C-81C0-EFCF7DF9E70F}']
    function GetAppsXML: WideString; safecall;
  end;

// *********************************************************************//
// DispIntf:  ICTAppCompatDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {AD7F317C-679F-4E2C-81C0-EFCF7DF9E70F}
// *********************************************************************//
  ICTAppCompatDisp = dispinterface
    ['{AD7F317C-679F-4E2C-81C0-EFCF7DF9E70F}']
    function GetAppsXML: WideString; dispid 1610743808;
  end;

// *********************************************************************//
// Interface: ICTDiagnostic
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {5AD2732D-9388-4664-956C-92EEA10CD8A3}
// *********************************************************************//
  ICTDiagnostic = interface(IDispatch)
    ['{5AD2732D-9388-4664-956C-92EEA10CD8A3}']
    function Logon(dwAttemptType: LongWord): Integer; safecall;
    procedure CancelLogon; safecall;
    function GetErrorsXML: WideString; safecall;
    function Get_IsVerSent: Integer; safecall;
    function Get_IsVerReceived: Integer; safecall;
    function Get_IsPasswordError: Integer; safecall;
    property IsVerSent: Integer read Get_IsVerSent;
    property IsVerReceived: Integer read Get_IsVerReceived;
    property IsPasswordError: Integer read Get_IsPasswordError;
  end;

// *********************************************************************//
// DispIntf:  ICTDiagnosticDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {5AD2732D-9388-4664-956C-92EEA10CD8A3}
// *********************************************************************//
  ICTDiagnosticDisp = dispinterface
    ['{5AD2732D-9388-4664-956C-92EEA10CD8A3}']
    function Logon(dwAttemptType: LongWord): Integer; dispid 1610743808;
    procedure CancelLogon; dispid 1610743809;
    function GetErrorsXML: WideString; dispid 1610743810;
    property IsVerSent: Integer readonly dispid 1610743811;
    property IsVerReceived: Integer readonly dispid 1610743812;
    property IsPasswordError: Integer readonly dispid 1610743813;
  end;

implementation

uses ComObj;

end.
