{******************************************************************************}
{                                                       	               }
{ Shell GUID definitions API interface Unit for Object Pascal                  }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: shlguid.h, released November 2002. The original Pascal }
{ code is: JwaShlGuid.pas, released April 2002. The initial developer of the   }
{ Pascal code is Marcel van Brakel (brakelm@chello.nl).                        }
{                                                                              }
{ Portions created by Marcel van Brakel are Copyright (C) 1999-2001            }
{ Marcel van Brakel. All Rights Reserved.                                      }
{ 								               }
{ Obtained through: Joint Endeavour of Delphi Innovators (Project JEDI)        }
{								               }
{ You may retrieve the latest version of this file at the Project JEDI home    }
{ page, located at http://delphi-jedi.org or my personal homepage located at   }
{ http://members.chello.nl/m.vanbrakel2                                        }
{								               }
{ The contents of this file are used with permission, subject to the Mozilla   }
{ Public License Version 1.1 (the "License"); you may not use this file except }
{ in compliance with the License. You may obtain a copy of the License at      }
{ http://www.mozilla.org/MPL/MPL-1.1.html                                      }
{                                                                              }
{ Software distributed under the License is distributed on an "AS IS" basis,   }
{ WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for }
{ the specific language governing rights and limitations under the License.    }
{                                                                              }
{ Alternatively, the contents of this file may be used under the terms of the  }
{ GNU Lesser General Public License (the  "LGPL License"), in which case the   }
{ provisions of the LGPL License are applicable instead of those above.        }
{ If you wish to allow use of your version of this file only under the terms   }
{ of the LGPL License and not to allow others to use your version of this file }
{ under the MPL, indicate your decision by deleting  the provisions above and  }
{ replace  them with the notice and other provisions required by the LGPL      }
{ License.  If you do not delete the provisions above, a recipient may use     }
{ your version of this file under either the MPL or the LGPL License.          }
{ 								               }
{ For more information about the LGPL: http://www.gnu.org/copyleft/lesser.html }
{ 								               }
{******************************************************************************}

unit JwaShlGuid;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "shlguid.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

//#define DEFINE_SHLGUID(name, l, w1, w2) DEFINE_GUID(name, l, w1, w2, 0xC0,0,0,0,0,0,0,0x46)

const
  CLSID_ShellDesktop: TGUID = (D1:$00021400; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46)); // 00021400-0000-0000-C000-0000000000));
  {$EXTERNALSYM CLSID_ShellDesktop}
  CLSID_ShellLink: TGUID = (D1:$00021401; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46)); // 00021401-0000-0000-C000-0000000000));
  {$EXTERNALSYM CLSID_ShellLink}

  CLSID_NetworkPlaces: TGUID = (D1:$208D2C60; D2:$3AEA; D3:$1069; D4:($A2,$D7,$08,$00,$2B,$30,$30,$9D));//208D2C60-3AEA-1069-A2D7-08002B3030));
  {$EXTERNALSYM CLSID_NetworkPlaces}
  CLSID_NetworkDomain: TGUID = (D1:$46e06680; D2:$4bf0; D3:$11d1; D4:($83,$ee,$00,$a0,$c9,$0d,$c8,$49));//46e06680-4bf0-11d1-83ee-00a0c90dc8));
  {$EXTERNALSYM CLSID_NetworkDomain}
  CLSID_NetworkServer: TGUID = (D1:$c0542a90; D2:$4bf0; D3:$11d1; D4:($83,$ee,$00,$a0,$c9,$0d,$c8,$49));//c0542a90-4bf0-11d1-83ee-00a0c90dc8));
  {$EXTERNALSYM CLSID_NetworkServer}
  CLSID_NetworkShare: TGUID = (D1:$54a754c0; D2:$4bf0; D3:$11d1; D4:($83,$ee,$00,$a0,$c9,$0d,$c8,$49));//54a754c0-4bf1-11d1-83ee-00a0c90dc8));
  {$EXTERNALSYM CLSID_NetworkShare}
  CLSID_MyComputer: TGUID = (D1:$20D04FE0; D2:$3AEA; D3:$1069; D4:($A2,$D8,$08,$00,$2B,$30,$30,$9D));//20D04FE0-3AEA-1069-A2D8-08002B3030));
  {$EXTERNALSYM CLSID_MyComputer}
  CLSID_Internet: TGUID = (D1:$871C5380; D2:$42A0; D3:$1069; D4:($A2,$EA,$08,$00,$2B,$30,$30,$9D));//871C5380-42A0-1069-A2EA-08002B3030));
  {$EXTERNALSYM CLSID_Internet}
  CLSID_ShellFSFolder: TGUID = (D1:$F3364BA0; D2:$65B9; D3:$11CE; D4:($A9,$BA,$00,$AA,$00,$4A,$E8,$37));//F3364BA0-65B9-11CE-A9BA-00AA004AE8));
  {$EXTERNALSYM CLSID_ShellFSFolder}
  CLSID_RecycleBin: TGUID = (D1:$645FF040; D2:$5081; D3:$101B; D4:($9F,$08,$00,$AA,$00,$2F,$95,$4E));//645FF040-5081-101B-9F08-00AA002F95));
  {$EXTERNALSYM CLSID_RecycleBin}
  CLSID_ControlPanel: TGUID = (D1:$21EC2020; D2:$3AEA; D3:$1069; D4:($A2,$DD,$08,$00,$2B,$30,$30,$9D));//21EC2020-3AEA-1069-A2DD-08002B3030));
  {$EXTERNALSYM CLSID_ControlPanel}
  CLSID_Printers: TGUID = (D1:$2227A280; D2:$3AEA; D3:$1069; D4:($A2,$DE,$08,$00,$2B,$30,$30,$9D));
  {$EXTERNALSYM CLSID_Printers}
  CLSID_MyDocuments: TGUID = (D1:$450d8fba; D2:$ad25; D3:$11d0; D4:($98,$a8,$08,$00,$36,$1b,$11,$03));//450D8FBA-AD25-11D0-98A8-0800361B11));
  {$EXTERNALSYM CLSID_MyDocuments}

// string version of above CLSIDs
// useful for doing psfDesktop->ParseDisplayName( L"::" L STR_MYDOCS_CLSID, ...);

  STR_MYDOCS_CLSID = '{450D8FBA-AD25-11D0-98A8-0800361B1103}';
  {$EXTERNALSYM STR_MYDOCS_CLSID}

//#if (_WIN32_IE >= 0x0400)

  CATID_BrowsableShellExt: TGUID = (D1:$00021490; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM CATID_BrowsableShellExt}
  CATID_BrowseInPlace: TGUID = (D1:$00021491; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM CATID_BrowseInPlace}
  CATID_DeskBand: TGUID = (D1:$00021492; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM CATID_DeskBand}
  CATID_InfoBand: TGUID = (D1:$00021493; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM CATID_InfoBand}
  CATID_CommBand: TGUID = (D1:$00021494; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM CATID_CommBand}

//#endif

  PSGUID_INTERNETSHORTCUT: TGUID = (D1:$000214A0; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM PSGUID_INTERNETSHORTCUT}
  FMTID_Intshcut: TGUID = (D1:$000214A0; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM FMTID_Intshcut}

  PSGUID_INTERNETSITE: TGUID = (D1:$000214A1; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM PSGUID_INTERNETSITE}
  FMTID_InternetSite: TGUID = (D1:$000214A1; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM FMTID_InternetSite}

  CGID_Explorer: TGUID = (D1:$000214D0; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM CGID_Explorer}
  CGID_ShellDocView: TGUID = (D1:$000214D1; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM CGID_ShellDocView}

//#if (_WIN32_IE >= 0x0400)

  CGID_ShellServiceObject: TGUID = (D1:$000214D2; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM CGID_ShellServiceObject}
  CGID_ExplorerBarDoc: TGUID = (D1:$000214D3; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM CGID_ExplorerBarDoc}

//#endif

  IID_INewShortcutHookA: TGUID = (D1:$000214E1; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_INewShortcutHookA}
  IID_IShellBrowser: TGUID = (D1:$000214E2; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellBrowser}
  IID_IShellView: TGUID = (D1:$000214E3; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellView}
  IID_IContextMenu: TGUID = (D1:$000214E4; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IContextMenu}
  IID_IShellIcon: TGUID = (D1:$000214E5; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellIcon}
  IID_IShellFolder: TGUID = (D1:$000214E6; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellFolder}
  IID_IShellExtInit: TGUID = (D1:$000214E8; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellExtInit}
  IID_IShellPropSheetExt: TGUID = (D1:$000214E9; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellPropSheetExt}
  IID_IPersistFolder: TGUID = (D1:$000214EA; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IPersistFolder}
  IID_IExtractIconA: TGUID = (D1:$000214EB; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IExtractIconA}
  IID_IShellDetails: TGUID = (D1:$000214EC; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellDetails}
  IID_IDelayedRelease: TGUID = (D1:$000214ED; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IDelayedRelease}
  IID_IShellLinkA: TGUID = (D1:$000214EE; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellLinkA}
  IID_IShellCopyHookA: TGUID = (D1:$000214EF; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellCopyHookA}
  IID_IFileViewerA: TGUID = (D1:$000214F0; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IFileViewerA}
  IID_ICommDlgBrowser: TGUID = (D1:$000214F1; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_ICommDlgBrowser}
  IID_IEnumIDList: TGUID = (D1:$000214F2; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IEnumIDList}
  IID_IFileViewerSite: TGUID = (D1:$000214F3; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IFileViewerSite}
  IID_IContextMenu2: TGUID = (D1:$000214F4; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IContextMenu2}
  IID_IShellExecuteHookA: TGUID = (D1:$000214F5; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellExecuteHookA}
  IID_IPropSheetPage: TGUID = (D1:$000214F6; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IPropSheetPage}
  IID_INewShortcutHookW: TGUID = (D1:$000214F7; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_INewShortcutHookW}
  IID_IFileViewerW: TGUID = (D1:$000214F8; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IFileViewerW}
  IID_IShellLinkW: TGUID = (D1:$000214F9; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellLinkW}
  IID_IExtractIconW: TGUID = (D1:$000214FA; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IExtractIconW}
  IID_IShellExecuteHookW: TGUID = (D1:$000214FB; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellExecuteHookW}
  IID_IShellCopyHookW: TGUID = (D1:$000214FC; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellCopyHookW}

  IID_IRemoteComputer: TGUID = (D1:$000214FE; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IRemoteComputer}

//#define IID_ICopyHookA                  IID_IShellCopyHookA

  IID_ICopyHookA: TGUID = (D1:$000214EF; D2:$0000; D3:$0000; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_ICopyHookA}

//#define IID_ICopyHookW                  IID_IShellCopyHookW

  IID_ICopyHookW: TGUID = (D1:$000214FC; D2:$0000; D3:$0000; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_ICopyHookW}

//#define SID_LinkSite    IID_IShellLinkW     // IServiceProvider::QueryService() access the link object that is defering to you

  SID_LinkSite: TGUID = (D1:$000214F9; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM SID_LinkSite}


//#if (_WIN32_IE >= 0x0400)

  IID_IQueryInfo: TGUID = (D1:$00021500; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IQueryInfo}

//#endif

  IID_IBriefcaseStg: TGUID = (D1:$8BCE1FA1; D2:$0921; D3:$101B; D4:($B1, $FF, $00, $DD, $01, $0C, $CC, $48));
  {$EXTERNALSYM IID_IBriefcaseStg}
  IID_IShellView2: TGUID = (D1:$88E39E80; D2:$3578; D3:$11CF; D4:($AE, $69, $08, $00, $2B, $2E, $12, $62));
  {$EXTERNALSYM IID_IShellView2}
  IID_IShellLinkDataList: TGUID = (D1:$45e2b4ae; D2:$b1c3; D3:$11d0; D4:($b9, $2f, $0, $a0, $c9, $3, $12, $e1));
  {$EXTERNALSYM IID_IShellLinkDataList}
//#if (_WIN32_IE >= 0x0500)
  IID_IResolveShellLink: TGUID = (D1:$5cd52983; D2:$9449; D3:$11d2; D4:($96, $3a, $00, $c0, $4f, $79, $ad, $f0));
  {$EXTERNALSYM IID_IResolveShellLink}
//#endif // _WIN32_IE >= 0x0500

//#if (_WIN32_IE >= 0x0400)

  IID_IURLSearchHook: TGUID = (D1:$AC60F6A0; D2:$0FD9; D3:$11D0; D4:($99, $CB, $00, $C0, $4F, $D6, $44, $97));
  {$EXTERNALSYM IID_IURLSearchHook}
  IID_ISearchContext: TGUID = (D1:$09F656A2; D2:$41AF; D3:$480C; D4:($88, $F7, $16, $CC, $0D, $16, $46, $15));
  {$EXTERNALSYM IID_ISearchContext}
  IID_IURLSearchHook2: TGUID = (D1:$5ee44da4; D2:$6d32; D3:$46e3; D4:($86, $bc, $07, $54, $0d, $ed, $d0, $e0));
  {$EXTERNALSYM IID_IURLSearchHook2}
  IID_IDelegateFolder: TGUID = (D1:$ADD8BA80; D2:$002B; D3:$11D0; D4:($8F, $0F, $00, $C0, $4F, $D7, $D0, $62));
  {$EXTERNALSYM IID_IDelegateFolder}

//#if (_WIN32_IE >= 0x0500)

// CLSID_FolderShortcut {0AFACED1-E828-11D1-9187-B532F1E9575D}

  CLSID_FolderShortcut: TGUID = (D1:$0AFACED1; D2:$E828; D3:$11D1; D4:($91, $87, $B5, $32, $F1, $E9, $57, $5D));
  {$EXTERNALSYM CLSID_FolderShortcut}

// CLSID_StorageFolder {E773F1AF-3A65-4866-857D-846FC9C4598A}

  CLSID_StgFolder: TGUID = (D1:$E773F1AF; D2:$3A65; D3:$4866; D4:($85, $7D, $84, $6F, $C9, $C4, $59, $8A));
  {$EXTERNALSYM CLSID_StgFolder}

//#endif

  IID_IInputObject: TGUID = (D1:$68284faa; D2:$6a48; D3:$11d0; D4:($8c, $78, $0, $c0, $4f, $d9, $18, $b4));
  {$EXTERNALSYM IID_IInputObject}
  IID_IInputObjectSite: TGUID = (D1:$f1db8392; D2:$7331; D3:$11d0; D4:($8c, $99, $0, $a0, $c9, $2d, $bf, $e8));
  {$EXTERNALSYM IID_IInputObjectSite}

  IID_IDockingWindowSite: TGUID = (D1:$2a342fc2; D2:$7b26; D3:$11d0; D4:($8c, $a9, $0, $a0, $c9, $2d, $bf, $e8));
  {$EXTERNALSYM IID_IDockingWindowSite}
  IID_IDockingWindowFrame: TGUID = (D1:$47d2657a; D2:$7b27; D3:$11d0; D4:($8c, $a9, $0, $a0, $c9, $2d, $bf, $e8));
  {$EXTERNALSYM IID_IDockingWindowFrame}

  IID_IShellIconOverlay: TGUID = (D1:$7D688A70; D2:$C613; D3:$11D0; D4:($99, $9B, $00, $C0, $4F, $D6, $55, $E1));
  {$EXTERNALSYM IID_IShellIconOverlay}
  IID_IShellIconOverlayIdentifier: TGUID = (D1:$0C6C4200; D2:$C589; D3:$11D0; D4:($99, $9A, $00, $C0, $4F, $D6, $55, $E1));
  {$EXTERNALSYM IID_IShellIconOverlayIdentifier}

// {10339516-2894-11d2-9039-00C04F8EEB3E}

  IID_ICommDlgBrowser2: TGUID = (D1:$10339516; D2:$2894; D3:$11d2; D4:($90, $39, $0, $c0, $4f, $8e, $eb, $3e));
  {$EXTERNALSYM IID_ICommDlgBrowser2}

// 2047E320-F2A9-11CE-AE65-08002B2E1262

  IID_IShellFolderViewCB: TGUID = (D1:$2047E320; D2:$F2A9; D3:$11CE; D4:($AE, $65, $08, $00, $2B, $2E, $12, $62));
  {$EXTERNALSYM IID_IShellFolderViewCB}

//#define SID_ShellFolderViewCB IID_IShellFolderViewCB

  SID_ShellFolderViewCB: TGUID = (D1:$2047E320; D2:$F2A9; D3:$11CE; D4:($AE, $65, $08, $00, $2B, $2E, $12, $62));
  {$EXTERNALSYM SID_ShellFolderViewCB}

// {CEF04FDF-FE72-11d2-87A5-00C04F6837CF}

  IID_IPersistFolder3: TGUID = (D1:$cef04fdf; D2:$fe72; D3:$11d2; D4:($87, $a5, $0, $c0, $4f, $68, $37, $cf));
  {$EXTERNALSYM IID_IPersistFolder3}

// {63B51F81-C868-11D0-999C-00C04FD655E1}

  CLSID_CFSIconOverlayManager: TGUID = (D1:$63B51F81; D2:$C868; D3:$11D0; D4:($99, $9C, $00, $C0, $4F, $D6, $55, $E1));
  {$EXTERNALSYM CLSID_CFSIconOverlayManager}

// {85788D00-6807-11d0-B810-00C04FD706EC}

  IID_IRunnableTask: TGUID = (D1:$85788d00; D2:$6807; D3:$11d0; D4:($b8, $10, $0, $c0, $4f, $d7, $6, $ec));
  {$EXTERNALSYM IID_IRunnableTask}

// {4ea39266-7211-409f-b622-f63dbd16c533}

  IID_IThumbnailCapture: TGUID = (D1:$4ea39266; D2:$7211; D3:$409f; D4:($b6, $22, $f6, $3d, $bd, $16, $c5, $33));
  {$EXTERNALSYM IID_IThumbnailCapture}

// {BCFCE0A0-EC17-11d0-8D10-00A0C90F2719}

  IID_IContextMenu3: TGUID = (D1:$bcfce0a0; D2:$ec17; D3:$11d0; D4:($8d, $10, $0, $a0, $c9, $f, $27, $19));
  {$EXTERNALSYM IID_IContextMenu3}

//#endif // _WIN32_IE >= 0x0400

//#define SID_SShellBrowser IID_IShellBrowser

  SID_SShellBrowser: TGUID = (D1:$000214E2; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM SID_SShellBrowser}

//#if (_WIN32_IE >= 0x0400)

//#define SID_SShellDesktop CLSID_ShellDesktop

  SID_SShellDesktop: TGUID = (D1:$00021400; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46)); // 00021400-0000-0000-C000-0000000000));
  {$EXTERNALSYM SID_SShellDesktop}

//#endif

//#if (_WIN32_IE >= 0x0400)

//
//  IShellDiscardable is an IID-only interface. If the object supports this
// interface it can be discarded anytime. IWebBrowser::PutProperty QI's for
// this interface to detect discardable properties.
//

  IID_IDiscardableBrowserProperty: TGUID = (D1:$49c3de7c; D2:$d329; D3:$11d0; D4:($ab, $73, $00, $c0, $4f, $c3, $3e, $80));
  {$EXTERNALSYM IID_IDiscardableBrowserProperty}

// IShellChangeNotify is a sink of LPCITEMIDLIST notification events
//
// D82BE2B1-5764-11D0-A96E-00C04FD705A2

  IID_IShellChangeNotify: TGUID = (D1:$D82BE2B1; D2:$5764; D3:$11D0; D4:($A9, $6E, $00, $C0, $4F, $D7, $05, $A2));
  {$EXTERNALSYM IID_IShellChangeNotify}

//#endif // _WIN32_IE >= 0x0400

{$IFDEF UNICODE}

//#define IID_IFileViewer         IID_IFileViewerW
//#define IID_IShellLink          IID_IShellLinkW
//#define IID_IExtractIcon        IID_IExtractIconW
//#define IID_IShellCopyHook      IID_IShellCopyHookW
//#define IID_IShellExecuteHook   IID_IShellExecuteHookW
//#define IID_INewShortcutHook    IID_INewShortcutHookW

  IID_IFileViewer: TGUID = (D1:$000214F8; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IFileViewer}
  IID_IShellLink: TGUID = (D1:$000214F9; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellLink}
  IID_IExtractIcon: TGUID = (D1:$000214FA; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IExtractIcon}
  IID_IShellExecuteHook: TGUID = (D1:$000214FB; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellExecuteHook}
  IID_IShellCopyHook: TGUID = (D1:$000214FC; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellCopyHook}
  IID_INewShortcutHook: TGUID = (D1:$000214F7; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_INewShortcutHook}

{$ELSE}

//#define IID_IFileViewer         IID_IFileViewerA
//#define IID_IShellLink          IID_IShellLinkA
//#define IID_IExtractIcon        IID_IExtractIconA
//#define IID_IShellCopyHook      IID_IShellCopyHookA
//#define IID_IShellExecuteHook   IID_IShellExecuteHookA
//#define IID_INewShortcutHook    IID_INewShortcutHookA

  IID_IFileViewer: TGUID = (D1:$000214F0; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IFileViewer}
  IID_IShellLink: TGUID = (D1:$000214EE; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellLink}
  IID_IExtractIcon: TGUID = (D1:$000214EB; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IExtractIcon}
  IID_IShellCopyHook: TGUID = (D1:$000214EF; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellCopyHook}
  IID_IShellExecuteHook: TGUID = (D1:$000214F5; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_IShellExecuteHook}
  IID_INewShortcutHook: TGUID = (D1:$000214E1; D2:$; D3:$; D4:($C0,0,0,0,0,0,0,$46));
  {$EXTERNALSYM IID_INewShortcutHook}

{$ENDIF}

//#if (_WIN32_IE >= 0x0400)

// UrlHistory Guids

  CLSID_CUrlHistory: TGUID = (D1:$3C374A40; D2:$BAE4; D3:$11CF; D4:($BF, $7D, $00, $AA, $00, $69, $46, $EE));
  {$EXTERNALSYM CLSID_CUrlHistory}

//#define SID_SUrlHistory         CLSID_CUrlHistory

  SID_SUrlHistory: TGUID = (D1:$3C374A40; D2:$BAE4; D3:$11CF; D4:($BF, $7D, $00, $AA, $00, $69, $46, $EE));
  {$EXTERNALSYM SID_SUrlHistory}

//UrlSearchHook Guids

  CLSID_CURLSearchHook: TGUID = (D1:$CFBFAE00; D2:$17A6; D3:$11D0; D4:($99, $CB, $00, $C0, $4F, $D6, $44, $97));
  {$EXTERNALSYM CLSID_CURLSearchHook}

//#define SID_SInternetExplorer IID_IWebBrowserApp
//#define SID_SWebBrowserApp    IID_IWebBrowserApp

// AutoComplete Guids

  IID_IAutoCompList: TGUID = (D1:$00BB2760; D2:$6A77; D3:$11D0; D4:($A5, $35, $00, $C0, $4F, $D7, $D0, $62));
  {$EXTERNALSYM IID_IAutoCompList}
  IID_IObjMgr: TGUID = (D1:$00BB2761; D2:$6A77; D3:$11D0; D4:($A5, $35, $00, $C0, $4F, $D7, $D0, $62));
  {$EXTERNALSYM IID_IObjMgr}
  IID_IACList: TGUID = (D1:$77A130B0; D2:$94FD; D3:$11D0; D4:($A5, $44, $00, $C0, $4F, $D7, $d0, $62));
  {$EXTERNALSYM IID_IACList}
  IID_IACList2: TGUID = (D1:$470141a0; D2:$5186; D3:$11d2; D4:($bb, $b6, $00, $60, $97, $7b, $46, $4c));
  {$EXTERNALSYM IID_IACList2}
  IID_ICurrentWorkingDirectory: TGUID = (D1:$91956d21; D2:$9276; D3:$11d1; D4:($92, $1a, $00, $60, $97, $df, $5b, $d4));     // {91956D21-9276-11d1-921A-006097DF5BD));
  {$EXTERNALSYM IID_ICurrentWorkingDirectory}
  CLSID_AutoComplete: TGUID = (D1:$00BB2763; D2:$6A77; D3:$11D0; D4:($A5, $35, $00, $C0, $4F, $D7, $D0, $62));
  {$EXTERNALSYM CLSID_AutoComplete}
  CLSID_ACLHistory: TGUID = (D1:$00BB2764; D2:$6A77; D3:$11D0; D4:($A5, $35, $00, $C0, $4F, $D7, $D0, $62));
  {$EXTERNALSYM CLSID_ACLHistory}
  CLSID_ACListISF: TGUID = (D1:$03C036F1; D2:$A186; D3:$11D0; D4:($82, $4A, $00, $AA, $00, $5B, $43, $83));
  {$EXTERNALSYM CLSID_ACListISF}
  CLSID_ACLMRU: TGUID = (D1:$6756a641; D2:$de71; D3:$11d0; D4:($83, $1b, $0, $aa, $0, $5b, $43, $83));          // {6756A641-DE71-11d0-831B-00AA005B438));
  {$EXTERNALSYM CLSID_ACLMRU}
  CLSID_ACLMulti: TGUID = (D1:$00BB2765; D2:$6A77; D3:$11D0; D4:($A5, $35, $00, $C0, $4F, $D7, $D0, $62));
  {$EXTERNALSYM CLSID_ACLMulti}
//#if (_WIN32_IE >= 0x0600)
  CLSID_ACLCustomMRU: TGUID = (D1:$6935db93; D2:$21e8; D3:$4ccc; D4:($be, $b9, $9f, $e3, $c7, $7a, $29, $7a));
  {$EXTERNALSYM CLSID_ACLCustomMRU}
//#endif

//#if (_WIN32_IE >= 0x0500)
/// IProgressDialog
// {F8383852-FCD3-11d1-A6B9-006097DF5BD4}
  CLSID_ProgressDialog: TGUID = (D1:$f8383852; D2:$fcd3; D3:$11d1; D4:($a6, $b9, $0, $60, $97, $df, $5b, $d4));
  {$EXTERNALSYM CLSID_ProgressDialog}
// {EBBC7C04-315E-11d2-B62F-006097DF5BD4}
  IID_IProgressDialog: TGUID = (D1:$ebbc7c04; D2:$315e; D3:$11d2; D4:($b6, $2f, $0, $60, $97, $df, $5b, $d4));
  {$EXTERNALSYM IID_IProgressDialog}
//#endif // _WIN32_IE >= 0x0500

//
// Progress objects exposed via QueryService
//

//#define SID_SProgressUI CLSID_ProgressDialog

  SID_SProgressUI: TGUID = (D1:$f8383852; D2:$fcd3; D3:$11d1; D4:($a6, $b9, $0, $60, $97, $df, $5b, $d4));
  {$EXTERNALSYM SID_SProgressUI}

//
// Top-most browser implementation in the heirarchy. use IServiceProvider::QueryService()
// to get to interfaces (IID_IShellBrowser, IID_IBrowserService, etc.)
//

  SID_STopLevelBrowser: TGUID = (D1:$4C96BE40; D2:$915C; D3:$11CF; D4:($99, $D3, $00, $AA, $00, $4A, $E8, $37));
  {$EXTERNALSYM SID_STopLevelBrowser}

//#endif // _WIN32_IE >= 0x0400

//#if (_WIN32_IE >= 0x0400)

// {75048700-EF1F-11D0-9888-006097DEACF9}

   CLSID_ActiveDesktop: TGUID = (D1:$75048700; D2:$EF1F; D3:$11D0; D4:($98, $88, $00, $60, $97, $DE, $AC, $F9));
  {$EXTERNALSYM  CLSID_ActiveDesktop}

// {F490EB00-1240-11D1-9888-006097DEACF9}

  IID_IActiveDesktop: TGUID = (D1:$F490EB00; D2:$1240; D3:$11D1; D4:($98, $88, $00, $60, $97, $DE, $AC, $F9));
  {$EXTERNALSYM IID_IActiveDesktop}

// {74C26041-70D1-11d1-B75A-00A0C90564FE}

  IID_ISynchronizedCallBack: TGUID = (D1:$74c26041; D2:$70d1; D3:$11d1; D4:($b7, $5a, $0, $a0, $c9, $5, $64, $fe));
  {$EXTERNALSYM IID_ISynchronizedCallBack}

// Extended column handler interfaces
// {D2A105C0-87D5-11d1-8391-0000F80461CF}

  IID_IShellDetails3: TGUID = (D1:$d2a105c0; D2:$87d5; D3:$11d1; D4:($83, $91, $0, $0, $f8, $4, $61, $cf));
  {$EXTERNALSYM IID_IShellDetails3}

//  {c46ca590-3c3f-11d2-bee6-0000f805ca57}

  IID_IQueryAssociations: TGUID = (D1:$c46ca590; D2:$3c3f; D3:$11d2; D4:($be, $e6, $00, $00, $f8, $05, $ca, $57));
  {$EXTERNALSYM IID_IQueryAssociations}

// {a07034fd-6caa-4954-ac3f-97a27216f98a}

  CLSID_QueryAssociations: TGUID = (D1:$a07034fd; D2:$6caa; D3:$4954; D4:($ac, $3f, $97, $a2, $72, $16, $f9, $8a));
  {$EXTERNALSYM CLSID_QueryAssociations}

// {E8025004-1C42-11d2-BE2C-00A0C9A83DA1}

  IID_IColumnProvider: TGUID = (D1:$e8025004; D2:$1c42; D3:$11d2; D4:($be, $2c, $0, $a0, $c9, $a8, $3d, $a1));
  {$EXTERNALSYM IID_IColumnProvider}

// {24F14F01-7B1C-11d1-838f-0000F80461CF}

  CLSID_DocFileColumnProvider: TGUID = (D1:$24f14f01; D2:$7b1c; D3:$11d1; D4:($83, $8f, $0, $0, $f8, $4, $61, $cf));
  {$EXTERNALSYM CLSID_DocFileColumnProvider}

// {24F14F02-7B1C-11d1-838f-0000F80461CF}

  CLSID_LinkColumnProvider: TGUID = (D1:$24f14f02; D2:$7b1c; D3:$11d1; D4:($83, $8f, $0, $0, $f8, $4, $61, $cf));
  {$EXTERNALSYM CLSID_LinkColumnProvider}

// {0D2E74C4-3C34-11d2-A27E-00C04FC30871}

  CLSID_FileSysColumnProvider: TGUID = (D1:$d2e74c4; D2:$3c34; D3:$11d2; D4:($a2, $7e, $0, $c0, $4f, $c3, $8, $71));
  {$EXTERNALSYM CLSID_FileSysColumnProvider}

// For Internet Shortcut Creation Command
// The shell uses this command to allow trident to save off it's per frame data in the shortcut
// and to allow it to fire the OnPersist() event on every frame
// {93A68750-951A-11d1-946F-000000000000}

  CGID_ShortCut: TGUID = (D1:$93a68750; D2:$951a; D3:$11d1; D4:($94, $6f, $0, $0, $0, $0, $0, $0));
  {$EXTERNALSYM CGID_ShortCut}

// {FB700430-952C-11d1-946F-000000000000}

  IID_INamedPropertyBag: TGUID = (D1:$fb700430; D2:$952c; D3:$11d1; D4:($94, $6f, $0, $0, $0, $0, $0, $0));
  {$EXTERNALSYM IID_INamedPropertyBag}

// {1E796980-9CC5-11D1-A83F-00C04FC99D61}

  CLSID_InternetButtons: TGUID = (D1:$1E796980; D2:$9CC5; D3:$11D1; D4:($A8, $3F, $00, $C0, $4F, $C9, $9D, $61));
  {$EXTERNALSYM CLSID_InternetButtons}

//#if (_WIN32_IE >= 0x0500)
// {178F34B8-A282-11d2-86C5-00C04F8EEA99}

  CLSID_MSOButtons: TGUID = (D1:$178f34b8; D2:$a282; D3:$11d2; D4:($86, $c5, $0, $c0, $4f, $8e, $ea, $99));
  {$EXTERNALSYM CLSID_MSOButtons}

// {2CE4B5D8-A28F-11d2-86C5-00C04F8EEA99}

  CLSID_ToolbarExtButtons: TGUID = (D1:$2ce4b5d8; D2:$a28f; D3:$11d2; D4:($86, $c5, $0, $c0, $4f, $8e, $ea, $99));
  {$EXTERNALSYM CLSID_ToolbarExtButtons}
//#endif // _WIN32_IE >= 0x0500

// {CFCCC7A0-A282-11D1-9082-006008059382}

  CLSID_DarwinAppPublisher: TGUID = (D1:$CFCCC7A0; D2:$A282; D3:$11D1; D4:($90, $82, $00, $60, $08, $05, $93, $82));
  {$EXTERNALSYM CLSID_DarwinAppPublisher}

// {7057E952-BD1B-11d1-8919-00C04FC2C836}

  CLSID_DocHostUIHandler: TGUID = (D1:$7057e952; D2:$bd1b; D3:$11d1; D4:($89, $19, $0, $c0, $4f, $c2, $c8, $36));
  {$EXTERNALSYM CLSID_DocHostUIHandler}
//#endif  // _WIN32_IE >= 0x0400

//#if (_WIN32_IE >= 0x0500)

// {93F2F68C-1D1B-11d3-A30E-00C04F79ABD1}

  IID_IShellFolder2: TGUID = (D1:$93f2f68c; D2:$1d1b; D3:$11d3; D4:($a3, $e, $0, $c0, $4f, $79, $ab, $d1));
  {$EXTERNALSYM IID_IShellFolder2}

  PSGUID_SHELLDETAILS: TGUID = (D1:$28636aa6; D2:$953d; D3:$11d2; D4:($b5, $d6, $0, $c0, $4f, $d9, $18, $d0));
  {$EXTERNALSYM PSGUID_SHELLDETAILS}
  FMTID_ShellDetails: TGUID = (D1:$28636aa6; D2:$953d; D3:$11d2; D4:($b5, $d6, $0, $c0, $4f, $d9, $18, $d0));
  {$EXTERNALSYM FMTID_ShellDetails}

  PID_FINDDATA        = 0;
  {$EXTERNALSYM PID_FINDDATA}
  PID_NETRESOURCE     = 1;
  {$EXTERNALSYM PID_NETRESOURCE}
  PID_DESCRIPTIONID   = 2;
  {$EXTERNALSYM PID_DESCRIPTIONID}
  PID_WHICHFOLDER     = 3;
  {$EXTERNALSYM PID_WHICHFOLDER}
  PID_NETWORKLOCATION = 4;
  {$EXTERNALSYM PID_NETWORKLOCATION}
  PID_COMPUTERNAME    = 5;
  {$EXTERNALSYM PID_COMPUTERNAME}

// PSGUID_STORAGE comes from ntquery.h
//#define PSGUID_STORAGE    {0xb725f130, 0x47ef, 0x101a, 0xa5, 0xf1, 0x02, 0x60, 0x8c, 0x9e, 0xeb, 0xac}

  FMTID_Storage: TGUID = (D1:$b725f130; D2:$47ef; D3:$101a; D4:($a5, $f1, $02, $60, $8c, $9e, $eb, $ac));
  {$EXTERNALSYM FMTID_Storage}

// Image properties

  PSGUID_IMAGEPROPERTIES: TGUID = (D1:$14b81da1; D2:$0135; D3:$4d31; D4:($96, $d9, $6c, $bf, $c9, $67, $1a, $99));
  {$EXTERNALSYM PSGUID_IMAGEPROPERTIES}

  FMTID_ImageProperties: TGUID = (D1:$14b81da1; D2:$0135; D3:$4d31; D4:($96, $d9, $6c, $bf, $c9, $67, $1a, $99));
  {$EXTERNALSYM FMTID_ImageProperties}

// The GUIDs used to identify shell item attributes (columns). See IShellFolder2::GetDetailsEx implementations...

// {9B174B33-40FF-11d2-A27E-00C04FC30871}

  PSGUID_DISPLACED: TGUID = (D1:$9b174b33; D2:$40ff; D3:$11d2; D4:($a2, $7e, $0, $c0, $4f, $c3, $8, $71));
  {$EXTERNALSYM PSGUID_DISPLACED}

  FMTID_Displaced: TGUID = (D1:$9b174b33; D2:$40ff; D3:$11d2; D4:($a2, $7e, $0, $c0, $4f, $c3, $8, $71));
  {$EXTERNALSYM FMTID_Displaced}

  PID_DISPLACED_FROM = 2;
  {$EXTERNALSYM PID_DISPLACED_FROM}
  PID_DISPLACED_DATE = 3;
  {$EXTERNALSYM PID_DISPLACED_DATE}

// {328D8B21-7729-4bfc-954C-902B329D56B0}

  PSGUID_BRIEFCASE: TGUID = (D1:$328d8b21; D2:$7729; D3:$4bfc; D4:($95, $4c, $90, $2b, $32, $9d, $56, $b0));
  {$EXTERNALSYM PSGUID_BRIEFCASE}

  FMTID_Briefcase: TGUID = (D1:$328d8b21; D2:$7729; D3:$4bfc; D4:($95, $4c, $90, $2b, $32, $9d, $56, $b0));
  {$EXTERNALSYM FMTID_Briefcase}

  PID_SYNC_COPY_IN = 2;
  {$EXTERNALSYM PID_SYNC_COPY_IN}

// {9B174B34-40FF-11d2-A27E-00C04FC30871}

  PSGUID_MISC: TGUID = (D1:$9b174b34; D2:$40ff; D3:$11d2; D4:($a2, $7e, $0, $c0, $4f, $c3, $8, $71));
  {$EXTERNALSYM PSGUID_MISC}

  FMTID_Misc: TGUID = (D1:$9b174b34; D2:$40ff; D3:$11d2; D4:($a2, $7e, $0, $c0, $4f, $c3, $8, $71));
  {$EXTERNALSYM FMTID_Misc}

  PID_MISC_STATUS      = 2;
  {$EXTERNALSYM PID_MISC_STATUS}
  PID_MISC_ACCESSCOUNT = 3;
  {$EXTERNALSYM PID_MISC_ACCESSCOUNT}
  PID_MISC_OWNER       = 4;
  {$EXTERNALSYM PID_MISC_OWNER}
  PID_HTMLINFOTIPFILE  = 5;
  {$EXTERNALSYM PID_HTMLINFOTIPFILE}
  PID_MISC_PICS        = 6;
  {$EXTERNALSYM PID_MISC_PICS}

// {F2275480-F782-4291-BD94-F13693513AEC}

  PSGUID_WEBVIEW: TGUID = (D1:$f2275480; D2:$f782; D3:$4291; D4:($bd, $94, $f1, $36, $93, $51, $3a, $ec));
  {$EXTERNALSYM PSGUID_WEBVIEW}

  FMTID_WebView: TGUID = (D1:$f2275480; D2:$f782; D3:$4291; D4:($bd, $94, $f1, $36, $93, $51, $3a, $ec));
  {$EXTERNALSYM FMTID_WebView}

  PID_DISPLAY_PROPERTIES = 0;
  {$EXTERNALSYM PID_DISPLAY_PROPERTIES}
  PID_INTROTEXT          = 1;
  {$EXTERNALSYM PID_INTROTEXT}

// {56A3372E-CE9C-11d2-9F0E-006097C686F6}

  PSGUID_MUSIC: TGUID = (D1:$56a3372e; D2:$ce9c; D3:$11d2; D4:($9f, $e, $0, $60, $97, $c6, $86, $f6));
  {$EXTERNALSYM PSGUID_MUSIC}

  FMTID_MUSIC: TGUID = (D1:$56a3372e; D2:$ce9c; D3:$11d2; D4:($9f, $e, $0, $60, $97, $c6, $86, $f6));
  {$EXTERNALSYM FMTID_MUSIC}

  PIDSI_ARTIST    = 2;
  {$EXTERNALSYM PIDSI_ARTIST}
  PIDSI_SONGTITLE = 3;
  {$EXTERNALSYM PIDSI_SONGTITLE}
  PIDSI_ALBUM     = 4;
  {$EXTERNALSYM PIDSI_ALBUM}
  PIDSI_YEAR      = 5;
  {$EXTERNALSYM PIDSI_YEAR}
  PIDSI_COMMENT   = 6;
  {$EXTERNALSYM PIDSI_COMMENT}
  PIDSI_TRACK     = 7;
  {$EXTERNALSYM PIDSI_TRACK}
  PIDSI_GENRE     = 11;
  {$EXTERNALSYM PIDSI_GENRE}
  PIDSI_LYRICS    = 12;
  {$EXTERNALSYM PIDSI_LYRICS}

// {AEAC19E4-89AE-4508-B9B7-BB867ABEE2ED}

  PSGUID_DRM: TGUID = (D1:$aeac19e4; D2:$89ae; D3:$4508; D4:($b9, $b7, $bb, $86, $7a, $be, $e2, $ed));
  {$EXTERNALSYM PSGUID_DRM}

  FMTID_DRM: TGUID = (D1:$aeac19e4; D2:$89ae; D3:$4508; D4:($b9, $b7, $bb, $86, $7a, $be, $e2, $ed));
  {$EXTERNALSYM FMTID_DRM}

  PIDDRSI_PROTECTED   = 2;
  {$EXTERNALSYM PIDDRSI_PROTECTED}
  PIDDRSI_DESCRIPTION = 3;
  {$EXTERNALSYM PIDDRSI_DESCRIPTION}
  PIDDRSI_PLAYCOUNT   = 4;
  {$EXTERNALSYM PIDDRSI_PLAYCOUNT}
  PIDDRSI_PLAYSTARTS  = 5;
  {$EXTERNALSYM PIDDRSI_PLAYSTARTS}
  PIDDRSI_PLAYEXPIRES = 6;
  {$EXTERNALSYM PIDDRSI_PLAYEXPIRES}

//#define PSGUID_VIDEO   {0x64440491, 0x4c8b, 0x11d1, 0x8b, 0x70, 0x8, 0x0, 0x36, 0xb1, 0x1a, 0x3}
//  FMTID_VideoSummaryInformation property identifiers

  PIDVSI_STREAM_NAME   = $00000002; // "StreamName", VT_LPWSTR
  {$EXTERNALSYM PIDVSI_STREAM_NAME}
  PIDVSI_FRAME_WIDTH   = $00000003; // "FrameWidth", VT_UI4
  {$EXTERNALSYM PIDVSI_FRAME_WIDTH}
  PIDVSI_FRAME_HEIGHT  = $00000004; // "FrameHeight", VT_UI4
  {$EXTERNALSYM PIDVSI_FRAME_HEIGHT}
  PIDVSI_TIMELENGTH    = $00000007; // "TimeLength", VT_UI4, milliseconds
  {$EXTERNALSYM PIDVSI_TIMELENGTH}
  PIDVSI_FRAME_COUNT   = $00000005; // "FrameCount". VT_UI4
  {$EXTERNALSYM PIDVSI_FRAME_COUNT}
  PIDVSI_FRAME_RATE    = $00000006; // "FrameRate", VT_UI4, frames/millisecond
  {$EXTERNALSYM PIDVSI_FRAME_RATE}
  PIDVSI_DATA_RATE     = $00000008; // "DataRate", VT_UI4, bytes/second
  {$EXTERNALSYM PIDVSI_DATA_RATE}
  PIDVSI_SAMPLE_SIZE   = $00000009; // "SampleSize", VT_UI4
  {$EXTERNALSYM PIDVSI_SAMPLE_SIZE}
  PIDVSI_COMPRESSION   = $0000000A; // "Compression", VT_LPWSTR
  {$EXTERNALSYM PIDVSI_COMPRESSION}
  PIDVSI_STREAM_NUMBER = $0000000B; // "StreamNumber", VT_UI2
  {$EXTERNALSYM PIDVSI_STREAM_NUMBER}

//#define PSGUID_AUDIO   {0x64440490, 0x4c8b, 0x11d1, 0x8b, 0x70, 0x8, 0x0, 0x36, 0xb1, 0x1a, 0x3}
//  FMTID_AudioSummaryInformation property identifiers

  PIDASI_FORMAT        = $00000002; // VT_BSTR
  {$EXTERNALSYM PIDASI_FORMAT}
  PIDASI_TIMELENGTH    = $00000003; // VT_UI4, milliseconds
  {$EXTERNALSYM PIDASI_TIMELENGTH}
  PIDASI_AVG_DATA_RATE = $00000004; // VT_UI4,  Hz
  {$EXTERNALSYM PIDASI_AVG_DATA_RATE}
  PIDASI_SAMPLE_RATE   = $00000005; // VT_UI4,  bits
  {$EXTERNALSYM PIDASI_SAMPLE_RATE}
  PIDASI_SAMPLE_SIZE   = $00000006; // VT_UI4,  bits
  {$EXTERNALSYM PIDASI_SAMPLE_SIZE}
  PIDASI_CHANNEL_COUNT = $00000007; // VT_UI4
  {$EXTERNALSYM PIDASI_CHANNEL_COUNT}
  PIDASI_STREAM_NUMBER = $00000008; // VT_UI2
  {$EXTERNALSYM PIDASI_STREAM_NUMBER}
  PIDASI_STREAM_NAME   = $00000009; // VT_LPWSTR
  {$EXTERNALSYM PIDASI_STREAM_NAME}
  PIDASI_COMPRESSION   = $0000000A; // VT_LPWSTR
  {$EXTERNALSYM PIDASI_COMPRESSION}

// {305CA226-D286-468e-B848-2B2E8E697B74}

//#define PSGUID_CONTROLPANEL {0x305ca226, 0xd286, 0x468e, 0xb8, 0x48, 0x2b, 0x2e, 0x8e, 0x69, 0x7b, 0x74}

  PID_CONTROLPANEL_CATEGORY = 2;
  {$EXTERNALSYM PID_CONTROLPANEL_CATEGORY}

// {9B174B35-40FF-11d2-A27E-00C04FC30871}

  PSGUID_VOLUME: TGUID = (D1:$9b174b35; D2:$40ff; D3:$11d2; D4:($a2, $7e, $0, $c0, $4f, $c3, $8, $71));
  {$EXTERNALSYM PSGUID_VOLUME}

  FMTID_Volume: TGUID = (D1:$9b174b35; D2:$40ff; D3:$11d2; D4:($a2, $7e, $0, $c0, $4f, $c3, $8, $71));
  {$EXTERNALSYM FMTID_Volume}

  PID_VOLUME_FREE       = 2;
  {$EXTERNALSYM PID_VOLUME_FREE}
  PID_VOLUME_CAPACITY   = 3;
  {$EXTERNALSYM PID_VOLUME_CAPACITY}
  PID_VOLUME_FILESYSTEM = 4;
  {$EXTERNALSYM PID_VOLUME_FILESYSTEM}

// {D8C3986F-813B-449c-845D-87B95D674ADE}

//#define PSGUID_SHARE    {0xd8c3986f, 0x813b, 0x449c, 0x84, 0x5d, 0x87, 0xb9, 0x5d, 0x67, 0x4a, 0xde}

  PID_SHARE_CSC_STATUS = 2;
  {$EXTERNALSYM PID_SHARE_CSC_STATUS}

// {B9B4B3FC-2B51-4a42-B5D8-324146AFCF25}

//#define PSGUID_LINK     {0xb9b4b3fc, 0x2b51, 0x4a42, 0xb5, 0xd8, 0x32, 0x41, 0x46, 0xaf, 0xcf, 0x25}

  PID_LINK_TARGET = 2;
  {$EXTERNALSYM PID_LINK_TARGET}

  PSGUID_QUERY_D: TGUID = (D1:$49691c90; D2:$7e17; D3:$101a; D4:($a9,$1c,$08,$00,$2b,$2e,$cd,$a9));
  {$EXTERNALSYM PSGUID_QUERY_D}

  FMTID_Query: TGUID = (D1:$49691c90; D2:$7e17; D3:$101a; D4:($a9,$1c,$08,$00,$2b,$2e,$cd,$a9));
  {$EXTERNALSYM FMTID_Query}

  PID_QUERY_RANK = 2;
  {$EXTERNALSYM PID_QUERY_RANK}

// FMTID_SummaryInformation, see OLE docs for PID_ values for these

//#define PSGUID_SUMMARYINFORMATION       {0xf29f85e0L, 0x4ff9, 0x1068, 0xab, 0x91, 0x08, 0x00, 0x2b, 0x27, 0xb3, 0xd9}

// FMTID_DocumentSummaryInformation, see OLE docs on the PID_ values for this

//#define PSGUID_DOCUMENTSUMMARYINFORMATION {0xd5cdd502L, 0x2e9c, 0x101b, 0x93, 0x97, 0x08, 0x00, 0x2b, 0x2c, 0xf9, 0xae}

// FMTID_MediaFileSummaryInformation, see propidl.h PID_ values for this

//#define PSGUID_MEDIAFILESUMMARYINFORMATION {0x64440492L, 0x4c8b, 0x11d1, 0x8b, 0x70, 0x08, 0x00, 0x36, 0xb1, 0x1a, 0x03}

// FMTID_ImageSummaryInformation,, see propidl.h PID_ values for this

//#define PSGUID_IMAGESUMMARYINFORMATION {0x6444048fL, 0x4c8b, 0x11d1, 0x8b, 0x70, 0x8, 0x00, 0x36, 0xb1, 0x1a, 0x03}

// {0E700BE1-9DB6-11d1-A1CE-00C04FD75D13}

  IID_IEnumExtraSearch: TGUID = (D1:$e700be1; D2:$9db6; D3:$11d1; D4:($a1, $ce, $0, $c0, $4f, $d7, $5d, $13));
  {$EXTERNALSYM IID_IEnumExtraSearch}

// {12518493-00B2-11d2-9FA5-9E3420524153}

  CLSID_MountedVolume: TGUID = (D1:$12518493; D2:$00B2; D3:$11d2; D4:($9F, $A5, $9E, $34, $20, $52, $41, $53));
  {$EXTERNALSYM CLSID_MountedVolume}

// {FFB8655F-81B9-4fce-B89C-9A6BA76D13E7}

  CLSID_HWShellExecute: TGUID = (D1:$ffb8655f; D2:$81b9; D3:$4fce; D4:($b8, $9c, $9a, $6b, $a7, $6d, $13, $e7));
  {$EXTERNALSYM CLSID_HWShellExecute}

// {12518492-00B2-11d2-9FA5-9E3420524153}

  IID_IMountedVolume: TGUID = (D1:$12518492; D2:$00B2; D3:$11d2; D4:($9F, $A5, $9E, $34, $20, $52, $41, $53));
  {$EXTERNALSYM IID_IMountedVolume}

// {4657278A-411B-11d2-839A-00C04FD918D0}

  CLSID_DragDropHelper: TGUID = (D1:$4657278a; D2:$411b; D3:$11d2; D4:($83, $9a, $0, $c0, $4f, $d9, $18, $d0));
  {$EXTERNALSYM CLSID_DragDropHelper}

// {4657278B-411B-11d2-839A-00C04FD918D0}

  IID_IDropTargetHelper: TGUID = (D1:$4657278b; D2:$411b; D3:$11d2; D4:($83, $9a, $0, $c0, $4f, $d9, $18, $d0));
  {$EXTERNALSYM IID_IDropTargetHelper}

// {DE5BF786-477A-11d2-839D-00C04FD918D0}

  IID_IDragSourceHelper: TGUID = (D1:$de5bf786; D2:$477a; D3:$11d2; D4:($83, $9d, $0, $c0, $4f, $d9, $18, $d0));
  {$EXTERNALSYM IID_IDragSourceHelper}

// {3050f3BB-98b5-11cf-bb82-00aa00bdce0b}

  CLSID_CAnchorBrowsePropertyPage: TGUID = (D1:$3050f3BB; D2:$98b5; D3:$11cf; D4:($bb, $82, $00, $aa, $00, $bd, $ce, $0b));
  {$EXTERNALSYM CLSID_CAnchorBrowsePropertyPage}

// {3050f3B3-98b5-11cf-bb82-00aa00bdce0b}

  CLSID_CImageBrowsePropertyPage: TGUID = (D1:$3050f3B3; D2:$98b5; D3:$11cf; D4:($bb, $82, $00, $aa, $00, $bd, $ce, $0b));
  {$EXTERNALSYM CLSID_CImageBrowsePropertyPage}

// {3050f3B4-98b5-11cf-bb82-00aa00bdce0b}

  CLSID_CDocBrowsePropertyPage: TGUID = (D1:$3050f3B4; D2:$98b5; D3:$11cf; D4:($bb, $82, $00, $aa, $00, $bd, $ce, $0b));
  {$EXTERNALSYM CLSID_CDocBrowsePropertyPage}

// {01E18D10-4D8B-11d2-855D-006008059367}

  IID_IFileSystemBindData: TGUID = (D1:$1e18d10; D2:$4d8b; D3:$11d2; D4:($85, $5d, $0, $60, $8, $5, $93, $67));
  {$EXTERNALSYM IID_IFileSystemBindData}

// {49E1B500-4636-11d3-97F7-00C04F45D0B3}

  SID_STopWindow: TGUID = (D1:$49e1b500; D2:$4636; D3:$11d3; D4:($97, $f7, $0, $c0, $4f, $45, $d0, $b3));
  {$EXTERNALSYM SID_STopWindow}

// {889A935D-971E-4B12-B90C-24DFC9E1E5E8}

  SID_SGetViewFromViewDual: TGUID = (D1:$889A935D; D2:$971E; D3:$4B12; D4:($B9, $0C, $24, $DF, $C9, $E1, $E5, $E8));
  {$EXTERNALSYM SID_SGetViewFromViewDual}

//  BHIDs for IShellItem::BindToHandler()
//#define BHID_LocalCopyHelper     CLSID_LocalCopyHelper
//  {3981e224-f559-11d3-8e3a-00c04f6837d5}

  BHID_SFObject: TGUID = (D1:$3981e224; D2:$f559; D3:$11d3; D4:($8e, $3a, $00, $c0, $4f, $68, $37, $d5));
  {$EXTERNALSYM BHID_SFObject}

//  {3981e225-f559-11d3-8e3a-00c04f6837d5}

  BHID_SFUIObject: TGUID = (D1:$3981e225; D2:$f559; D3:$11d3; D4:($8e, $3a, $00, $c0, $4f, $68, $37, $d5));
  {$EXTERNALSYM BHID_SFUIObject}

//  {3981e226-f559-11d3-8e3a-00c04f6837d5}

  BHID_SFViewObject: TGUID = (D1:$3981e226; D2:$f559; D3:$11d3; D4:($8e, $3a, $00, $c0, $4f, $68, $37, $d5));
  {$EXTERNALSYM BHID_SFViewObject}

//  {3981e227-f559-11d3-8e3a-00c04f6837d5}

  BHID_Storage: TGUID = (D1:$3981e227; D2:$f559; D3:$11d3; D4:($8e, $3a, $00, $c0, $4f, $68, $37, $d5));
  {$EXTERNALSYM BHID_Storage}

// {1CEBB3AB-7C10-499a-A417-92CA16C4CB83}

  BHID_Stream: TGUID = (D1:$1cebb3ab; D2:$7c10; D3:$499a; D4:($a4, $17, $92, $ca, $16, $c4, $cb, $83));
  {$EXTERNALSYM BHID_Stream}

//  {3981e228-f559-11d3-8e3a-00c04f6837d5}

  BHID_LinkTargetItem: TGUID = (D1:$3981e228; D2:$f559; D3:$11d3; D4:($8e, $3a, $00, $c0, $4f, $68, $37, $d5));
  {$EXTERNALSYM BHID_LinkTargetItem}

// {4621A4E3-F0D6-4773-8A9C-46E77B174840}

  BHID_StorageEnum: TGUID = (D1:$4621a4e3; D2:$f0d6; D3:$4773; D4:($8a, $9c, $46, $e7, $7b, $17, $48, $40));
  {$EXTERNALSYM BHID_StorageEnum}

//#endif // _WIN32_IE >= 0x0500

//#if _WIN32_IE >= 0x0600

// {faadfc40-b777-4b69-aa81-77035ef0e6e8}

  SID_CtxQueryAssociations: TGUID = (D1:$faadfc40; D2:$b777; D3:$4b69; D4:($aa, $81, $77, $03, $5e, $f0, $e6, $e8));
  {$EXTERNALSYM SID_CtxQueryAssociations}

//#endif // _WIN32_IE >= 0x0600

//#endif // _SHLGUID_H_

implementation

end.
