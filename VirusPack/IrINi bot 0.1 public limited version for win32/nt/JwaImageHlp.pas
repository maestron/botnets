{******************************************************************************}
{                                                       	               }
{ Image Help API interface Unit for Object Pascal                              }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: imagehlp.h, released August 2001. The original Pascal  }
{ code is: ImageHelp.pas, released December 2000. The initial developer of the }
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

unit JwaImageHlp;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "ImageHlp.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  Windows, JwaWinBase, JwaWinNT, JwaWinType;

const
  IMAGE_SEPARATION = (64*1024);
  {$EXTERNALSYM IMAGE_SEPARATION}

type
  PLOADED_IMAGE = ^LOADED_IMAGE;
  {$EXTERNALSYM PLOADED_IMAGE}
  _LOADED_IMAGE = record
    ModuleName: PSTR;
    hFile: HANDLE;
    MappedAddress: PUCHAR;
    FileHeader: PIMAGE_NT_HEADERS32;
    LastRvaSection: PIMAGE_SECTION_HEADER;
    NumberOfSections: ULONG;
    Sections: PIMAGE_SECTION_HEADER;
    Characteristics: ULONG;
    fSystemImage: ByteBool;
    fDOSImage: ByteBool;
    Links: LIST_ENTRY;
    SizeOfImage: ULONG;
  end;
  {$EXTERNALSYM _LOADED_IMAGE}
  LOADED_IMAGE = _LOADED_IMAGE;
  {$EXTERNALSYM LOADED_IMAGE}
  TLoadedImage = LOADED_IMAGE;
  PLoadedImage = PLOADED_IMAGE;

const
  MAX_SYM_NAME = 2000;
  {$EXTERNALSYM MAX_SYM_NAME}

function BindImage(ImageName, DllPath, SymbolPath: PSTR): BOOL; stdcall;
{$EXTERNALSYM BindImage}

type
  _IMAGEHLP_STATUS_REASON = (
    BindOutOfMemory,
    BindRvaToVaFailed,
    BindNoRoomInImage,
    BindImportModuleFailed,
    BindImportProcedureFailed,
    BindImportModule,
    BindImportProcedure,
    BindForwarder,
    BindForwarderNOT,
    BindImageModified,
    BindExpandFileHeaders,
    BindImageComplete,
    BindMismatchedSymbols,
    BindSymbolsNotUpdated,
    BindImportProcedure32,
    BindImportProcedure64,
    BindForwarder32,
    BindForwarder64,
    BindForwarderNOT32,
    BindForwarderNOT64);
  {$EXTERNALSYM _IMAGEHLP_STATUS_REASON}
  IMAGEHLP_STATUS_REASON = _IMAGEHLP_STATUS_REASON;
  {$EXTERNALSYM IMAGEHLP_STATUS_REASON}
  TImageHlpStatusReason = IMAGEHLP_STATUS_REASON;

  PIMAGEHLP_STATUS_ROUTINE = function (Reason: IMAGEHLP_STATUS_REASON;
    ImageName, DllName: PSTR; Va, Parameter: ULONG_PTR): BOOL; stdcall;
  {$EXTERNALSYM PIMAGEHLP_STATUS_ROUTINE}
  PImageHlpStatusRoutine = PIMAGEHLP_STATUS_ROUTINE;

  PIMAGEHLP_STATUS_ROUTINE32 = function (Reason: IMAGEHLP_STATUS_REASON; ImageName, DllName: PSTR;
    Va: ULONG; Parameter: ULONG_PTR): BOOL; stdcall;
  {$EXTERNALSYM PIMAGEHLP_STATUS_ROUTINE32}
  PImageHlpStatusRoutine23 = PIMAGEHLP_STATUS_ROUTINE32;

  PIMAGEHLP_STATUS_ROUTINE64 = function (Reason: IMAGEHLP_STATUS_REASON; ImageName, DllName: PSTR;
    Va: ULONG64; Parameter: ULONG_PTR): BOOL; stdcall;
  {$EXTERNALSYM PIMAGEHLP_STATUS_ROUTINE64}
  PImageHlpStatusRoutine64 = PIMAGEHLP_STATUS_ROUTINE64;

function BindImageEx(Flags: DWORD; ImageName, DllPath, SymbolPath: PSTR;
  StatusRoutine: PIMAGEHLP_STATUS_ROUTINE): BOOL; stdcall;
{$EXTERNALSYM BindImageEx}

const
  BIND_NO_BOUND_IMPORTS  = $00000001;
  {$EXTERNALSYM BIND_NO_BOUND_IMPORTS}
  BIND_NO_UPDATE         = $00000002;
  {$EXTERNALSYM BIND_NO_UPDATE}
  BIND_ALL_IMAGES        = $00000004;
  {$EXTERNALSYM BIND_ALL_IMAGES}
  BIND_CACHE_IMPORT_DLLS = $00000008; // Cache dll's across calls to BindImageEx (same as NT 3.1->NT 4.0)
  {$EXTERNALSYM BIND_CACHE_IMPORT_DLLS}

  BIND_REPORT_64BIT_VA   = $00000010;
  {$EXTERNALSYM BIND_REPORT_64BIT_VA}

function ReBaseImage(CurrentImageName: PSTR; SymbolPath: PSTR; fReBase: BOOL;
  fRebaseSysfileOk: BOOL; fGoingDown: BOOL; CheckImageSize: ULONG;
  var OldImageSize: ULONG; var OldImageBase: ULONG_PTR; var NewImageSize: ULONG;
  var NewImageBase: ULONG_PTR; TimeStamp: ULONG): BOOL; stdcall;
{$EXTERNALSYM ReBaseImage}

function ReBaseImage64(CurrentImageName: PSTR; SymbolPath: PSTR; fReBase: BOOL;
  fRebaseSysfileOk: BOOL; fGoingDown: BOOL; CheckImageSize: ULONG;
  var OldImageSize: ULONG; var OldImageBase: ULONG64; var NewImageSize: ULONG;
  var NewImageBase: ULONG64; TimeStamp: ULONG): BOOL; stdcall;
{$EXTERNALSYM ReBaseImage64}

//
// Define checksum return codes.
//

const
  CHECKSUM_SUCCESS         = 0;
  {$EXTERNALSYM CHECKSUM_SUCCESS}
  CHECKSUM_OPEN_FAILURE    = 1;
  {$EXTERNALSYM CHECKSUM_OPEN_FAILURE}
  CHECKSUM_MAP_FAILURE     = 2;
  {$EXTERNALSYM CHECKSUM_MAP_FAILURE}
  CHECKSUM_MAPVIEW_FAILURE = 3;
  {$EXTERNALSYM CHECKSUM_MAPVIEW_FAILURE}
  CHECKSUM_UNICODE_FAILURE = 4;
  {$EXTERNALSYM CHECKSUM_UNICODE_FAILURE}

// Define Splitsym flags.

  SPLITSYM_REMOVE_PRIVATE = $00000001; // Remove CV types/symbols and Fixup debug
  {$EXTERNALSYM SPLITSYM_REMOVE_PRIVATE}
                                                    //  Used for creating .dbg files that ship
                                                    //  as part of the product.

  SPLITSYM_EXTRACT_ALL = $00000002; // Extract all debug info from image.
  {$EXTERNALSYM SPLITSYM_EXTRACT_ALL}
                                                    //  Normally, FPO is left in the image
                                                    //  to allow stack traces through the code.
                                                    //  Using this switch is similar to linking
                                                    //  with -debug:none except the .dbg file
                                                    //  exists...

  SPLITSYM_SYMBOLPATH_IS_SRC = $00000004; // The SymbolFilePath contains an alternate
  {$EXTERNALSYM SPLITSYM_SYMBOLPATH_IS_SRC}
                                                    //  path to locate the pdb.

//
// Define checksum function prototypes.
//

function CheckSumMappedFile(BaseAddress: PVOID; FileLength: DWORD;
  var HeaderSum, CheckSum: DWORD): PIMAGE_NT_HEADERS; stdcall;
{$EXTERNALSYM CheckSumMappedFile}

function MapFileAndCheckSumA(Filename: PSTR; var HeaderSum, CheckSum: DWORD): DWORD; stdcall;
{$EXTERNALSYM MapFileAndCheckSumA}
function MapFileAndCheckSumW(Filename: PWSTR; var HeaderSum, CheckSum: DWORD): DWORD; stdcall;
{$EXTERNALSYM MapFileAndCheckSumW}

{$IFDEF UNICODE}
function MapFileAndCheckSum(Filename: PWSTR; var HeaderSum, CheckSum: DWORD): DWORD; stdcall;
{$EXTERNALSYM MapFileAndCheckSum}
{$ELSE}
function MapFileAndCheckSum(Filename: PSTR; var HeaderSum, CheckSum: DWORD): DWORD; stdcall;
{$EXTERNALSYM MapFileAndCheckSum}
{$ENDIF}

function GetImageConfigInformation(const LoadedImage: LOADED_IMAGE;
  var ImageConfigInformation: IMAGE_LOAD_CONFIG_DIRECTORY): BOOL; stdcall;
{$EXTERNALSYM GetImageConfigInformation}

function GetImageUnusedHeaderBytes(const LoadedImage: LOADED_IMAGE;
  var SizeUnusedHeaderBytes: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetImageUnusedHeaderBytes}

function SetImageConfigInformation(const LoadedImage: LOADED_IMAGE;
  const ImageConfigInformation: IMAGE_LOAD_CONFIG_DIRECTORY): BOOL; stdcall;
{$EXTERNALSYM SetImageConfigInformation}

// Image Integrity API's

const
  CERT_PE_IMAGE_DIGEST_DEBUG_INFO      = $01;
  {$EXTERNALSYM CERT_PE_IMAGE_DIGEST_DEBUG_INFO}
  CERT_PE_IMAGE_DIGEST_RESOURCES       = $02;
  {$EXTERNALSYM CERT_PE_IMAGE_DIGEST_RESOURCES}
  CERT_PE_IMAGE_DIGEST_ALL_IMPORT_INFO = $04;
  {$EXTERNALSYM CERT_PE_IMAGE_DIGEST_ALL_IMPORT_INFO}
  CERT_PE_IMAGE_DIGEST_NON_PE_INFO     = $08; // include data outside the PE image
  {$EXTERNALSYM CERT_PE_IMAGE_DIGEST_NON_PE_INFO}

  CERT_SECTION_TYPE_ANY = $FF; // Any Certificate type
  {$EXTERNALSYM CERT_SECTION_TYPE_ANY}

type
  DIGEST_HANDLE = PVOID;
  {$EXTERNALSYM DIGEST_HANDLE}
  TDigestHandle = DIGEST_HANDLE;

  DIGEST_FUNCTION = function (refdata: DIGEST_HANDLE; pData: PBYTE; dwLength: DWORD): BOOL; stdcall;
  {$EXTERNALSYM DIGEST_FUNCTION}
  TDigestFunction = DIGEST_FUNCTION;

function ImageGetDigestStream(FileHandle: HANDLE; DigestLevel: DWORD;
  DigestFunction: DIGEST_FUNCTION; DigestHandle: DIGEST_HANDLE): BOOL; stdcall;
{$EXTERNALSYM ImageGetDigestStream}

function ImageAddCertificate(FileHandle: HANDLE; Certificate: PWinCertificate;
  var Index: DWORD): BOOL; stdcall;
{$EXTERNALSYM ImageAddCertificate}

function ImageRemoveCertificate(FileHandle: HANDLE; Index: DWORD): BOOL; stdcall;
{$EXTERNALSYM ImageRemoveCertificate}

function ImageEnumerateCertificates(FileHandle: HANDLE; TypeFilter: WORD;
  var CertificateCount: DWORD; Indices: PDWORD; IndexCount: DWORD): BOOL; stdcall;
{$EXTERNALSYM ImageEnumerateCertificates}

function ImageGetCertificateData(FileHandle: HANDLE; CertificateIndex: DWORD;
  Certificate: PWinCertificate; var RequiredLength: DWORD): BOOL; stdcall;
{$EXTERNALSYM ImageGetCertificateData}

function ImageGetCertificateHeader(FileHandle: HANDLE; CertificateIndex: DWORD;
  Certificateheader: PWinCertificate): BOOL; stdcall;
{$EXTERNALSYM ImageGetCertificateHeader}

function ImageLoad(DllName: PSTR; DllPath: PSTR): PLOADED_IMAGE; stdcall;
{$EXTERNALSYM ImageLoad}

function ImageUnload(const LoadedImage: LOADED_IMAGE): BOOL; stdcall;
{$EXTERNALSYM ImageUnload}

function MapAndLoad(ImageName, DllPath: PSTR; var LoadedImage: LOADED_IMAGE;
  DotDll: BOOL; ReadOnly: BOOL): BOOL; stdcall;
{$EXTERNALSYM MapAndLoad}

function UnMapAndLoad(const LoadedImage: LOADED_IMAGE): BOOL; stdcall;
{$EXTERNALSYM UnMapAndLoad}

function TouchFileTimes(FileHandle: HANDLE; pSystemTime: PSYSTEMTIME): BOOL; stdcall;
{$EXTERNALSYM TouchFileTimes}

function SplitSymbols(ImageName, SymbolsPath, SymbolFilePath: PSTR; Flags: DWORD): BOOL; stdcall;
{$EXTERNALSYM SplitSymbols}

function UpdateDebugInfoFile(ImageFileName, SymbolPath, DebugFilePath: PSTR;
  const NtHeaders: IMAGE_NT_HEADERS32): BOOL; stdcall;
{$EXTERNALSYM UpdateDebugInfoFile}

function UpdateDebugInfoFileEx(ImageFileName, SymbolPath, DebugFilePath: PSTR;
  const NtHeaders: IMAGE_NT_HEADERS32; OldChecksum: DWORD): BOOL; stdcall;
{$EXTERNALSYM UpdateDebugInfoFileEx}

function FindDebugInfoFile(FileName, SymbolPath, DebugFilePath: PSTR): HANDLE; stdcall;
{$EXTERNALSYM FindDebugInfoFile}

type
  PFIND_DEBUG_FILE_CALLBACK = function (FileHandle: HANDLE; FileName: PSTR;
    CallerData: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PFIND_DEBUG_FILE_CALLBACK}
  PFindDebugFileCallback = PFIND_DEBUG_FILE_CALLBACK;

function FindDebugInfoFileEx(FileName, SymbolPath, DebugFilePath: PSTR;
  Callback: PFIND_DEBUG_FILE_CALLBACK; CallerData: PVOID): HANDLE; stdcall;
{$EXTERNALSYM FindDebugInfoFileEx}

type
  PFINDFILEINPATHCALLBACK = function (filename: PSTR; context: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PFINDFILEINPATHCALLBACK}

function SymFindFileInPath(hprocess: HANDLE; SearchPath, FileName: LPSTR; id: PVOID; two, three, flags: DWORD;
  FoundFile: LPSTR; callback: PFINDFILEINPATHCALLBACK; context: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymFindFileInPath}

function FindExecutableImage(FileName, SymbolPath, ImageFilePath: PSTR): HANDLE; stdcall;
{$EXTERNALSYM FindExecutableImage}

type
  PFIND_EXE_FILE_CALLBACK = function (FileHandle: HANDLE; FileName: PSTR;
    CallerData: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PFIND_EXE_FILE_CALLBACK}
  PFindExeFileCallback = PFIND_EXE_FILE_CALLBACK;

function FindExecutableImageEx(FileName, SymbolPath, ImageFilePath: PSTR;
  Callback: PFIND_EXE_FILE_CALLBACK; CallerData: PVOID): HANDLE; stdcall;
{$EXTERNALSYM FindExecutableImageEx}

function ImageNtHeader(Base: PVOID): PIMAGE_NT_HEADERS; stdcall;
{$EXTERNALSYM ImageNtHeader}

function ImageDirectoryEntryToDataEx(Base: PVOID; MappedAsImage: ByteBool;
  DirectoryEntry: USHORT; var Size: ULONG; var FoundHeader: PIMAGE_SECTION_HEADER): PVOID; stdcall;
{$EXTERNALSYM ImageDirectoryEntryToDataEx}

function ImageDirectoryEntryToData(Base: PVOID; MappedAsImage: ByteBool;
  DirectoryEntry: USHORT; var Size: ULONG): PVOID; stdcall;
{$EXTERNALSYM ImageDirectoryEntryToData}

function ImageRvaToSection(NtHeaders: PIMAGE_NT_HEADERS; Base: PVOID; Rva: ULONG): PIMAGE_SECTION_HEADER; stdcall;
{$EXTERNALSYM ImageRvaToSection}

function ImageRvaToVa(NtHeaders: PIMAGE_NT_HEADERS; Base: PVOID; Rva: ULONG;
  var LastRvaSection: PIMAGE_SECTION_HEADER): PVOID; stdcall;
{$EXTERNALSYM ImageRvaToVa}

// Symbol server exports

type
  PSYMBOLSERVERPROC = function (a1, a2: LPCSTR; a3: PVOID; a4, a5: DWORD; a6: LPSTR): BOOL; stdcall;
  {$EXTERNALSYM PSYMBOLSERVERPROC}
  PSYMBOLSERVEROPENPROC = function: BOOL; stdcall;
  {$EXTERNALSYM PSYMBOLSERVEROPENPROC}
  PSYMBOLSERVERCLOSEPROC = function: BOOL; stdcall;
  {$EXTERNALSYM PSYMBOLSERVERCLOSEPROC}
  PSYMBOLSERVERSETOPTIONSPROC = function (a1: UINT_PTR; a2: ULONG64): BOOL; stdcall;
  {$EXTERNALSYM PSYMBOLSERVERSETOPTIONSPROC}
  PSYMBOLSERVERCALLBACKPROC = function (action: UINT_PTR; data: ULONG64; context: ULONG64): BOOL; stdcall;
  {$EXTERNALSYM PSYMBOLSERVERCALLBACKPROC}
  PSYMBOLSERVERGETOPTIONSPROC = function: UINT_PTR; stdcall;
  {$EXTERNALSYM PSYMBOLSERVERGETOPTIONSPROC}
  PSYMBOLSERVERPINGPROC = function (a1: LPCSTR): BOOL; stdcall;
  {$EXTERNALSYM PSYMBOLSERVERPINGPROC}

const
  SSRVOPT_CALLBACK   = $01;
  {$EXTERNALSYM SSRVOPT_CALLBACK}
  SSRVOPT_DWORD      = $02;
  {$EXTERNALSYM SSRVOPT_DWORD}
  SSRVOPT_DWORDPTR   = $04;
  {$EXTERNALSYM SSRVOPT_DWORDPTR}
  SSRVOPT_GUIDPTR    = $08;
  {$EXTERNALSYM SSRVOPT_GUIDPTR}
  SSRVOPT_OLDGUIDPTR = $10;
  {$EXTERNALSYM SSRVOPT_OLDGUIDPTR}
  SSRVOPT_UNATTENDED = $20;
  {$EXTERNALSYM SSRVOPT_UNATTENDED}
  SSRVOPT_RESET      = ULONG_PTR(-1);
  {$EXTERNALSYM SSRVOPT_RESET}

  SSRVACTION_TRACE   = 1;
  {$EXTERNALSYM SSRVACTION_TRACE}

// This api won't be ported to Win64 - Fix your code.

type
  PIMAGE_DEBUG_INFORMATION = ^IMAGE_DEBUG_INFORMATION;
  {$EXTERNALSYM PIMAGE_DEBUG_INFORMATION}
  _IMAGE_DEBUG_INFORMATION = record
    List: LIST_ENTRY;
    ReservedSize: DWORD;
    ReservedMappedBase: PVOID;
    ReservedMachine: USHORT;
    ReservedCharacteristics: USHORT;
    ReservedCheckSum: DWORD;
    ImageBase: DWORD;
    SizeOfImage: DWORD;
    ReservedNumberOfSections: DWORD;
    ReservedSections: PIMAGE_SECTION_HEADER;
    ReservedExportedNamesSize: DWORD;
    ReservedExportedNames: PSTR;
    ReservedNumberOfFunctionTableEntries: DWORD;
    ReservedFunctionTableEntries: PIMAGE_FUNCTION_ENTRY;
    ReservedLowestFunctionStartingAddress: DWORD;
    ReservedHighestFunctionEndingAddress: DWORD;
    ReservedNumberOfFpoTableEntries: DWORD;
    ReservedFpoTableEntries: PFPO_DATA;
    SizeOfCoffSymbols: DWORD;
    CoffSymbols: PIMAGE_COFF_SYMBOLS_HEADER;
    ReservedSizeOfCodeViewSymbols: DWORD;
    ReservedCodeViewSymbols: PVOID;
    ImageFilePath: PSTR;
    ImageFileName: PSTR;
    ReservedDebugFilePath: PSTR;
    ReservedTimeDateStamp: DWORD;
    ReservedRomImage: BOOL;
    ReservedDebugDirectory: PIMAGE_DEBUG_DIRECTORY;
    ReservedNumberOfDebugDirectories: DWORD;
    ReservedOriginalFunctionTableBaseAddress: DWORD;
    Reserved: array [0..1] of DWORD;
  end;
  {$EXTERNALSYM _IMAGE_DEBUG_INFORMATION}
  IMAGE_DEBUG_INFORMATION = _IMAGE_DEBUG_INFORMATION;
  {$EXTERNALSYM IMAGE_DEBUG_INFORMATION}
  TImageDebugInformation = IMAGE_DEBUG_INFORMATION;
  PImageDebugInformation = PIMAGE_DEBUG_INFORMATION;

function MapDebugInformation(FileHandle: HANDLE; FileName, SymbolPath: PSTR;
  ImageBase: DWORD): PIMAGE_DEBUG_INFORMATION; stdcall;
{$EXTERNALSYM MapDebugInformation}

function UnmapDebugInformation(DebugInfo: PIMAGE_DEBUG_INFORMATION): BOOL; stdcall;
{$EXTERNALSYM UnmapDebugInformation}

function SearchTreeForFile(RootPath, InputPathName, OutputPathBuffer: PSTR): BOOL; stdcall;
{$EXTERNALSYM SearchTreeForFile}

type
  PENUMDIRTREE_CALLBACK = function (FilePath: LPCSTR; CallerData: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PENUMDIRTREE_CALLBACK}
  PEnumDirTreeCallback = PENUMDIRTREE_CALLBACK;

function EnumDirTree(hProcess: HANDLE; RootPath, InputPathName, OutputPathBuffer: PSTR;
  Callback: PENUMDIRTREE_CALLBACK; CallbackData: PVOID): BOOL; stdcall;
{$EXTERNALSYM EnumDirTree}

function MakeSureDirectoryPathExists(DirPath: PCSTR): BOOL; stdcall;
{$EXTERNALSYM MakeSureDirectoryPathExists}

//
// UnDecorateSymbolName Flags
//

const
  UNDNAME_COMPLETE               = ($0000); // Enable full undecoration
  {$EXTERNALSYM UNDNAME_COMPLETE}
  UNDNAME_NO_LEADING_UNDERSCORES = ($0001); // Remove leading underscores from MS extended keywords
  {$EXTERNALSYM UNDNAME_NO_LEADING_UNDERSCORES}
  UNDNAME_NO_MS_KEYWORDS         = ($0002); // Disable expansion of MS extended keywords
  {$EXTERNALSYM UNDNAME_NO_MS_KEYWORDS}
  UNDNAME_NO_FUNCTION_RETURNS    = ($0004); // Disable expansion of return type for primary declaration
  {$EXTERNALSYM UNDNAME_NO_FUNCTION_RETURNS}
  UNDNAME_NO_ALLOCATION_MODEL    = ($0008); // Disable expansion of the declaration model
  {$EXTERNALSYM UNDNAME_NO_ALLOCATION_MODEL}
  UNDNAME_NO_ALLOCATION_LANGUAGE = ($0010); // Disable expansion of the declaration language specifier
  {$EXTERNALSYM UNDNAME_NO_ALLOCATION_LANGUAGE}
  UNDNAME_NO_MS_THISTYPE         = ($0020); // NYI Disable expansion of MS keywords on the 'this' type for primary declaration
  {$EXTERNALSYM UNDNAME_NO_MS_THISTYPE}
  UNDNAME_NO_CV_THISTYPE         = ($0040); // NYI Disable expansion of CV modifiers on the 'this' type for primary declaration
  {$EXTERNALSYM UNDNAME_NO_CV_THISTYPE}
  UNDNAME_NO_THISTYPE            = ($0060); // Disable all modifiers on the 'this' type
  {$EXTERNALSYM UNDNAME_NO_THISTYPE}
  UNDNAME_NO_ACCESS_SPECIFIERS   = ($0080); // Disable expansion of access specifiers for members
  {$EXTERNALSYM UNDNAME_NO_ACCESS_SPECIFIERS}
  UNDNAME_NO_THROW_SIGNATURES    = ($0100); // Disable expansion of 'throw-signatures' for functions and pointers to functions
  {$EXTERNALSYM UNDNAME_NO_THROW_SIGNATURES}
  UNDNAME_NO_MEMBER_TYPE         = ($0200); // Disable expansion of 'static' or 'virtual'ness of members
  {$EXTERNALSYM UNDNAME_NO_MEMBER_TYPE}
  UNDNAME_NO_RETURN_UDT_MODEL    = ($0400); // Disable expansion of MS model for UDT returns
  {$EXTERNALSYM UNDNAME_NO_RETURN_UDT_MODEL}
  UNDNAME_32_BIT_DECODE          = ($0800); // Undecorate 32-bit decorated names
  {$EXTERNALSYM UNDNAME_32_BIT_DECODE}
  UNDNAME_NAME_ONLY              = ($1000); // Crack only the name for primary declaration;
  {$EXTERNALSYM UNDNAME_NAME_ONLY}
                                                                                                   //  return just [scope::]name.  Does expand template params
  UNDNAME_NO_ARGUMENTS    = ($2000); // Don't undecorate arguments to function
  {$EXTERNALSYM UNDNAME_NO_ARGUMENTS}
  UNDNAME_NO_SPECIAL_SYMS = ($4000); // Don't undecorate special names (v-table, vcall, vector xxx, metatype, etc)
  {$EXTERNALSYM UNDNAME_NO_SPECIAL_SYMS}

function UnDecorateSymbolName(DecoratedName: PCSTR; UnDecoratedName: PSTR;
  UndecoratedLength: DWORD; Flags: DWORD): DWORD; stdcall;
{$EXTERNALSYM UnDecorateSymbolName}

//
// these values are used for synthesized file types
// that can be passed in as image headers instead of
// the standard ones from ntimage.h
//

const
  DBHHEADER_DEBUGDIRS    = $1;
  {$EXTERNALSYM DBHHEADER_DEBUGDIRS}

type
  _MODLOAD_DATA = record
    ssize: DWORD;                  // size of this struct
    ssig: DWORD;                   // signature identifying the passed data
    data: PVOID;                   // pointer to passed data
    size: DWORD;                   // size of passed data
    flags: DWORD;                  // options
  end;
  {$EXTERNALSYM _MODLOAD_DATA}
  MODLOAD_DATA = _MODLOAD_DATA;
  {$EXTERNALSYM MODLOAD_DATA}
  PMODLOAD_DATA = ^MODLOAD_DATA;
  {$EXTERNALSYM PMODLOAD_DATA}
  TModLoadData = MODLOAD_DATA;
  PModLoadData = PMODLOAD_DATA;

//
// StackWalking API
//

type
  ADDRESS_MODE = (
    AddrMode1616,
    AddrMode1632,
    AddrModeReal,
    AddrModeFlat);
  {$EXTERNALSYM ADDRESS_MODE}
  TAddressMode = ADDRESS_MODE;

  LPADDRESS64 = ^ADDRESS64;
  {$EXTERNALSYM PADDRESS64}
  _tagADDRESS64 = record
    Offset: DWORD64;
    Segment: WORD;
    Mode: ADDRESS_MODE;
  end;
  {$EXTERNALSYM _tagADDRESS64}
  ADDRESS64 = _tagADDRESS64;
  {$EXTERNALSYM ADDRESS64}
  TAddress64 = ADDRESS64;
  PAddress64 = LPADDRESS64;

  LPADDRESS = ^ADDRESS;
  {$EXTERNALSYM PADDRESS}
  _tagADDRESS = record
    Offset: DWORD;
    Segment: WORD;
    Mode: ADDRESS_MODE;
  end;
  {$EXTERNALSYM _tagADDRESS}
  ADDRESS = _tagADDRESS;
  {$EXTERNALSYM ADDRESS}
  TAddress = ADDRESS;
  PAddress = LPADDRESS;

procedure Address32To64(a32: LPADDRESS; a64: LPADDRESS64);
{$EXTERNALSYM Address32To64}

procedure Address64To32(a64: LPADDRESS64; a32: LPADDRESS);
{$EXTERNALSYM Address64To32}

//
// This structure is included in the STACKFRAME structure,
// and is used to trace through usermode callbacks in a thread's
// kernel stack.  The values must be copied by the kernel debugger
// from the DBGKD_GET_VERSION and WAIT_STATE_CHANGE packets.
//

//
// New KDHELP structure for 64 bit system support.
// This structure is preferred in new code.
//

type
  PKDHELP64 = ^KDHELP64;
  {$EXTERNALSYM PKDHELP64}
  _KDHELP64 = record
    //
    // address of kernel thread object, as provided in the
    // WAIT_STATE_CHANGE packet.
    //
    Thread: DWORD64;
    //
    // offset in thread object to pointer to the current callback frame
    // in kernel stack.
    //
    ThCallbackStack: DWORD;
    //
    // offset in thread object to pointer to the current callback backing
    // store frame in kernel stack.
    //
    ThCallbackBStore: DWORD;
    //
    // offsets to values in frame:
    //
    // address of next callback frame
    NextCallback: DWORD;
    // address of saved frame pointer (if applicable)
    FramePointer: DWORD;
    //
    // Address of the kernel function that calls out to user mode
    //
    KiCallUserMode: DWORD64;
    //
    // Address of the user mode dispatcher function
    //
    KeUserCallbackDispatcher: DWORD64;
    //
    // Lowest kernel mode address
    //
    SystemRangeStart: DWORD64;
    Reserved: array [0..7] of DWORD64;
  end;
  {$EXTERNALSYM _KDHELP64}
  KDHELP64 = _KDHELP64;
  {$EXTERNALSYM KDHELP64}
  TKdHelp64 = KDHELP64;
  //PKdHelp64 = PKDHELP64;

  PKDHELP = ^KDHELP;
  {$EXTERNALSYM PKDHELP}
  _KDHELP = record
    //
    // address of kernel thread object, as provided in the
    // WAIT_STATE_CHANGE packet.
    //
    Thread: DWORD;
    //
    // offset in thread object to pointer to the current callback frame
    // in kernel stack.
    //
    ThCallbackStack: DWORD;
    //
    // offsets to values in frame:
    //
    // address of next callback frame
    NextCallback: DWORD;
    // address of saved frame pointer (if applicable)
    FramePointer: DWORD;
    //
    // Address of the kernel function that calls out to user mode
    //
    KiCallUserMode: DWORD;
    //
    // Address of the user mode dispatcher function
    //
    KeUserCallbackDispatcher: DWORD;
    //
    // Lowest kernel mode address
    //
    SystemRangeStart: DWORD;
    //
    // offset in thread object to pointer to the current callback backing
    // store frame in kernel stack.
    //
    ThCallbackBStore: DWORD;
    Reserved: array [0..7] of DWORD;
  end;
  {$EXTERNALSYM _KDHELP}
  KDHELP = _KDHELP;
  {$EXTERNALSYM KDHELP}
  TKdHelp = KDHELP;
  //PKdHelp = PKDHELP;

procedure KdHelp32To64(p32: PKDHELP; p64: PKDHELP64);
{$EXTERNALSYM KdHelp32To64}

type
  LPSTACKFRAME64 = ^STACKFRAME64;
  {$EXTERNALSYM LPSTACKFRAME64}
  _tagSTACKFRAME64 = record
    AddrPC: ADDRESS64; // program counter
    AddrReturn: ADDRESS64; // return address
    AddrFrame: ADDRESS64; // frame pointer
    AddrStack: ADDRESS64; // stack pointer
    AddrBStore: ADDRESS64; // backing store pointer
    FuncTableEntry: PVOID; // pointer to pdata/fpo or NULL
    Params: array [0..3] of DWORD64; // possible arguments to the function
    Far: BOOL; // WOW far call
    Virtual: BOOL; // is this a virtual frame?
    Reserved: array [0..2] of DWORD64;
    KdHelp: KDHELP64;
  end;
  {$EXTERNALSYM _tagSTACKFRAME64}
  STACKFRAME64 = _tagSTACKFRAME64;
  {$EXTERNALSYM STACKFRAME64}
  TStackFrame64 = STACKFRAME64;
  PStackFrame64 = LPSTACKFRAME64;

  LPSTACKFRAME = ^STACKFRAME;
  {$EXTERNALSYM LPSTACKFRAME}
  _tagSTACKFRAME = record
    AddrPC: ADDRESS; // program counter
    AddrReturn: ADDRESS; // return address
    AddrFrame: ADDRESS; // frame pointer
    AddrStack: ADDRESS; // stack pointer
    FuncTableEntry: PVOID; // pointer to pdata/fpo or NULL
    Params: array [0..3] of DWORD; // possible arguments to the function
    Far: BOOL; // WOW far call
    Virtual: BOOL; // is this a virtual frame?
    Reserved: array [0..2] of DWORD;
    KdHelp: KDHELP;
    AddrBStore: ADDRESS; // backing store pointer
  end;
  {$EXTERNALSYM _tagSTACKFRAME}
  STACKFRAME = _tagSTACKFRAME;
  {$EXTERNALSYM STACKFRAME}
  TStackFrame = STACKFRAME;
  PStackFrame = LPSTACKFRAME;

  PREAD_PROCESS_MEMORY_ROUTINE64 = function (hProcess: HANDLE; qwBaseAddress: DWORD64;
    lpBuffer: PVOID; nSize: DWORD; var lpNumberOfBytesRead: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PREAD_PROCESS_MEMORY_ROUTINE64}
  PReadProcessMemoryRoutine64 = PREAD_PROCESS_MEMORY_ROUTINE64;

  PFUNCTION_TABLE_ACCESS_ROUTINE64 = function (hProcess: HANDLE;
    AddrBase: DWORD64): PVOID; stdcall;
  {$EXTERNALSYM PFUNCTION_TABLE_ACCESS_ROUTINE64}
  PFunctionTableAccessRoutine64 = PFUNCTION_TABLE_ACCESS_ROUTINE64;

  PGET_MODULE_BASE_ROUTINE64 = function (hProcess: HANDLE;
    Address: DWORD64): DWORD64; stdcall;
  {$EXTERNALSYM PGET_MODULE_BASE_ROUTINE64}
  PGetModuleBaseRoutine64 = PGET_MODULE_BASE_ROUTINE64;

  PTRANSLATE_ADDRESS_ROUTINE64 = function (hProcess: HANDLE; hThread: HANDLE;
    const lpaddr: ADDRESS64): DWORD64; stdcall;
  {$EXTERNALSYM PTRANSLATE_ADDRESS_ROUTINE64}
  PTranslateAddressRoutine64 = PTRANSLATE_ADDRESS_ROUTINE64;

function StackWalk64(MachineType: DWORD; hProcess: HANDLE; hThread: HANDLE;
  var StackFrame: STACKFRAME64; ContextRecord: PVOID;
  ReadMemoryRoutine: PREAD_PROCESS_MEMORY_ROUTINE64;
  FunctionTableAccessRoutine: PFUNCTION_TABLE_ACCESS_ROUTINE64;
  GetModuleBaseRoutine: PGET_MODULE_BASE_ROUTINE64;
  TranslateAddress: PTRANSLATE_ADDRESS_ROUTINE64): BOOL; stdcall;
{$EXTERNALSYM StackWalk64}

type
  PREAD_PROCESS_MEMORY_ROUTINE = function (hProcess: HANDLE;
    lpBaseAddress: DWORD; lpBuffer: PVOID; nSize: DWORD;
    var lpNumberOfBytesRead: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PREAD_PROCESS_MEMORY_ROUTINE}
  PreadProcessMemoryRoutine = PREAD_PROCESS_MEMORY_ROUTINE;

  PFUNCTION_TABLE_ACCESS_ROUTINE = function (hProcess: HANDLE; AddrBase: DWORD): PVOID; stdcall;
  {$EXTERNALSYM PFUNCTION_TABLE_ACCESS_ROUTINE}
  PFunctionTableAccessRoutine = PFUNCTION_TABLE_ACCESS_ROUTINE;

  PGET_MODULE_BASE_ROUTINE = function (hProcess: HANDLE; Address: DWORD): DWORD; stdcall;
  {$EXTERNALSYM PGET_MODULE_BASE_ROUTINE}
  PGetModuleBaseRoutine = PGET_MODULE_BASE_ROUTINE;

  PTRANSLATE_ADDRESS_ROUTINE = function (hProcess: HANDLE; hThread: HANDLE;
    const lpaddr: ADDRESS): DWORD; stdcall;
  {$EXTERNALSYM PTRANSLATE_ADDRESS_ROUTINE}
  PTranslateAddressRoutine = PTRANSLATE_ADDRESS_ROUTINE;

function StackWalk(MachineType: DWORD; hProcess: HANDLE; hThread: HANDLE;
  var StackFrame: STACKFRAME; ContextRecord: PVOID;
  ReadMemoryRoutine: PREAD_PROCESS_MEMORY_ROUTINE;
  FunctionTableAccessRoutine: PFUNCTION_TABLE_ACCESS_ROUTINE;
  GetModuleBaseRoutine: PGET_MODULE_BASE_ROUTINE;
  TranslateAddress: PTRANSLATE_ADDRESS_ROUTINE): BOOL; stdcall;
{$EXTERNALSYM StackWalk}

const
  API_VERSION_NUMBER = 9;
  {$EXTERNALSYM API_VERSION_NUMBER}

type
  LPAPI_VERSION = ^API_VERSION;
  {$EXTERNALSYM LPAPI_VERSION}
  API_VERSION = record
    MajorVersion: USHORT;
    MinorVersion: USHORT;
    Revision: USHORT;
    Reserved: USHORT;
  end;
  {$EXTERNALSYM API_VERSION}
  TApiVersion = API_VERSION;
  PApiVersion = LPAPI_VERSION;

function ImagehlpApiVersion: LPAPI_VERSION; stdcall;
{$EXTERNALSYM ImagehlpApiVersion}

function ImagehlpApiVersionEx(const AppVersion: API_VERSION): LPAPI_VERSION; stdcall;
{$EXTERNALSYM ImagehlpApiVersionEx}

function GetTimestampForLoadedLibrary(Module: HMODULE): DWORD; stdcall;
{$EXTERNALSYM GetTimestampForLoadedLibrary}

//
// typedefs for function pointers
//

type
  PSYM_ENUMMODULES_CALLBACK64 = function (ModuleName: PSTR; BaseOfDll: DWORD64;
    UserContext: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PSYM_ENUMMODULES_CALLBACK64}
  PSymEnummodulesCallback64 = PSYM_ENUMMODULES_CALLBACK64;

  PSYM_ENUMSYMBOLS_CALLBACK64 = function (SymbolName: PSTR; SymbolAddress: DWORD64;
    SymbolSize: ULONG; UserContext: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PSYM_ENUMSYMBOLS_CALLBACK64}
  PSymEnumsymbolsCallback64 = PSYM_ENUMSYMBOLS_CALLBACK64;

  PSYM_ENUMSYMBOLS_CALLBACK64W = function (SymbolName: PWSTR;
    SymbolAddress: DWORD64; SymbolSize: ULONG; UserContext: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PSYM_ENUMSYMBOLS_CALLBACK64W}
  PSymEnumsymbolsCallback64w = PSYM_ENUMSYMBOLS_CALLBACK64W;

  PENUMLOADED_MODULES_CALLBACK64 = function (ModuleName: PSTR;
    ModuleBase: DWORD64; ModuleSize: ULONG; UserContext: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PENUMLOADED_MODULES_CALLBACK64}
  PSnumloadedModulesCallback64 = PENUMLOADED_MODULES_CALLBACK64;

  PSYMBOL_REGISTERED_CALLBACK64 = function (hProcess: HANDLE; ActionCode: ULONG;
    CallbackData: ULONG64; UserContext: ULONG64): BOOL; stdcall;
  {$EXTERNALSYM PSYMBOL_REGISTERED_CALLBACK64}
  PSymbolRegisteredCallback64 = PSYMBOL_REGISTERED_CALLBACK64;

  PSYMBOL_FUNCENTRY_CALLBACK = function (hProcess: HANDLE; AddrBase: DWORD;
    UserContext: PVOID): PVOID; stdcall;
  {$EXTERNALSYM PSYMBOL_FUNCENTRY_CALLBACK}
  PSymbolFuncentryCallback = PSYMBOL_FUNCENTRY_CALLBACK;

  PSYMBOL_FUNCENTRY_CALLBACK64 = function (hProcess: HANDLE; AddrBase: ULONG64;
    UserContext: ULONG64): PVOID; stdcall;
  {$EXTERNALSYM PSYMBOL_FUNCENTRY_CALLBACK64}
  PSymbolFuncentryCallback64 = PSYMBOL_FUNCENTRY_CALLBACK64;

  PSYM_ENUMMODULES_CALLBACK = function (ModuleName: PSTR; BaseOfDll: ULONG;
    UserContext: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PSYM_ENUMMODULES_CALLBACK}
  PSymEnummodulesCallback = PSYM_ENUMMODULES_CALLBACK;

  PSYM_ENUMSYMBOLS_CALLBACK = function (SymbolName: PSTR; SymbolAddress: ULONG;
    SymbolSize: ULONG; UserContext: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PSYM_ENUMSYMBOLS_CALLBACK}
  PSymEnumsymbolsCallback = PSYM_ENUMSYMBOLS_CALLBACK;

  PSYM_ENUMSYMBOLS_CALLBACKW = function (SymbolName: PWSTR; SymbolAddress: ULONG;
    SymbolSize: ULONG; UserContext: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PSYM_ENUMSYMBOLS_CALLBACKW}
  PSymEnumsymbolsCallbackw = PSYM_ENUMSYMBOLS_CALLBACKW;

  PENUMLOADED_MODULES_CALLBACK = function (ModuleName: PSTR; ModuleBase: ULONG;
    ModuleSize: ULONG; UserContext: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PENUMLOADED_MODULES_CALLBACK}
  PEnumloadedModulesCallback = PENUMLOADED_MODULES_CALLBACK;

  PSYMBOL_REGISTERED_CALLBACK = function (hProcess: HANDLE; ActionCode: ULONG;
    CallbackData: PVOID; UserContext: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PSYMBOL_REGISTERED_CALLBACK}
  PSymbolRegisteredCallback = PSYMBOL_REGISTERED_CALLBACK;

//
// flags found in SYMBOL_INFO.Flags
//

const
  SYMFLAG_VALUEPRESENT   = $00000001;
  {$EXTERNALSYM SYMFLAG_VALUEPRESENT}
  SYMFLAG_REGISTER       = $00000008;
  {$EXTERNALSYM SYMFLAG_REGISTER}
  SYMFLAG_REGREL         = $00000010;
  {$EXTERNALSYM SYMFLAG_REGREL}
  SYMFLAG_FRAMEREL       = $00000020;
  {$EXTERNALSYM SYMFLAG_FRAMEREL}
  SYMFLAG_PARAMETER      = $00000040;
  {$EXTERNALSYM SYMFLAG_PARAMETER}
  SYMFLAG_LOCAL          = $00000080;
  {$EXTERNALSYM SYMFLAG_LOCAL}
  SYMFLAG_CONSTANT       = $00000100;
  {$EXTERNALSYM SYMFLAG_CONSTANT}
  SYMFLAG_EXPORT         = $00000200;
  {$EXTERNALSYM SYMFLAG_EXPORT}
  SYMFLAG_FORWARDER      = $00000400;
  {$EXTERNALSYM SYMFLAG_FORWARDER}
  SYMFLAG_FUNCTION       = $00000800;
  {$EXTERNALSYM SYMFLAG_FUNCTION}
  SYMFLAG_VIRTUAL        = $00001000;
  {$EXTERNALSYM SYMFLAG_VIRTUAL}
  SYMFLAG_THUNK          = $00002000;
  {$EXTERNALSYM SYMFLAG_THUNK}
  SYMFLAG_TLSREL         = $00004000;
  {$EXTERNALSYM SYMFLAG_TLSREL}

//
// symbol type enumeration
//

type
  SYM_TYPE = (
    SymNone,
    SymCoff,
    SymCv,
    SymPdb,
    SymExport,
    SymDeferred,
    SymSym,                   // .sym file
    SymDia,
    SymVirtual,
    NumSymTypes);
  {$EXTERNALSYM SYM_TYPE}
  TSymType = SYM_TYPE;

//
// symbol data structure
//

  PIMAGEHLP_SYMBOL64 = ^IMAGEHLP_SYMBOL64;
  {$EXTERNALSYM PIMAGEHLP_SYMBOL64}
  _IMAGEHLP_SYMBOL64 = record
    SizeOfStruct: DWORD; // set to sizeof(IMAGEHLP_SYMBOL64)
    Address: DWORD64; // virtual address including dll base address
    Size: DWORD; // estimated size of symbol, can be zero
    Flags: DWORD; // info about the symbols, see the SYMF defines
    MaxNameLength: DWORD; // maximum size of symbol name in 'Name'
    Name: array [0..0] of CHAR; // symbol name (null terminated string)
  end;
  {$EXTERNALSYM _IMAGEHLP_SYMBOL64}
  IMAGEHLP_SYMBOL64 = _IMAGEHLP_SYMBOL64;
  {$EXTERNALSYM IMAGEHLP_SYMBOL64}
  TImageHlpSymbol64 = IMAGEHLP_SYMBOL64;
  PImageHlpSymbol64 = PIMAGEHLP_SYMBOL64;

  _IMAGEHLP_SYMBOL64_PACKAGE = record
    sym: IMAGEHLP_SYMBOL64;
    name: array [0..MAX_SYM_NAME] of CHAR;
  end;
  {$EXTERNALSYM _IMAGEHLP_SYMBOL64_PACKAGE}
  IMAGEHLP_SYMBOL64_PACKAGE = _IMAGEHLP_SYMBOL64_PACKAGE;
  {$EXTERNALSYM IMAGEHLP_SYMBOL64_PACKAGE}
  PIMAGEHLP_SYMBOL64_PACKAGE = ^IMAGEHLP_SYMBOL64_PACKAGE;
  {$EXTERNALSYM PIMAGEHLP_SYMBOL64_PACKAGE}
  TImageHlpSymbol64Package = IMAGEHLP_SYMBOL64_PACKAGE;
  PImageHlpSymbol64Package = PIMAGEHLP_SYMBOL64_PACKAGE;  

//#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
//
//#define IMAGEHLP_SYMBOL IMAGEHLP_SYMBOL64
//#define PIMAGEHLP_SYMBOL PIMAGEHLP_SYMBOL64
//#define IMAGEHLP_SYMBOL_PACKAGE IMAGEHLP_SYMBOL64_PACKAGE
//#define PIMAGEHLP_SYMBOL_PACKAGE PIMAGEHLP_SYMBOL64_PACKAGE
//
//#else

  PIMAGEHLP_SYMBOL = ^IMAGEHLP_SYMBOL;
  {$EXTERNALSYM PIMAGEHLP_SYMBOL}
  _IMAGEHLP_SYMBOL = record
    SizeOfStruct: DWORD; // set to sizeof(IMAGEHLP_SYMBOL)
    Address: DWORD; // virtual address including dll base address
    Size: DWORD; // estimated size of symbol, can be zero
    Flags: DWORD; // info about the symbols, see the SYMF defines
    MaxNameLength: DWORD; // maximum size of symbol name in 'Name'
    Name: array [0..0] of CHAR; // symbol name (null terminated string)
  end;
  {$EXTERNALSYM _IMAGEHLP_SYMBOL}
  IMAGEHLP_SYMBOL = _IMAGEHLP_SYMBOL;
  {$EXTERNALSYM IMAGEHLP_SYMBOL}
  TImageHlpSymbol = IMAGEHLP_SYMBOL;
  PImageHlpSymbol = PIMAGEHLP_SYMBOL;

  _IMAGEHLP_SYMBOL_PACKAGE = record
    sym: IMAGEHLP_SYMBOL;
    name: array [0..MAX_SYM_NAME] of CHAR;
  end;
  {$EXTERNALSYM _IMAGEHLP_SYMBOL_PACKAGE}
  IMAGEHLP_SYMBOL_PACKAGE = _IMAGEHLP_SYMBOL_PACKAGE;
  {$EXTERNALSYM IMAGEHLP_SYMBOL_PACKAGE}
  PIMAGEHLP_SYMBOL_PACKAGE = ^IMAGEHLP_SYMBOL_PACKAGE;
  {$EXTERNALSYM PIMAGEHLP_SYMBOL_PACKAGE}
  TImageHlpSymbolPackage = IMAGEHLP_SYMBOL_PACKAGE;
  PImageHlpSymbolPackage = PIMAGEHLP_SYMBOL_PACKAGE;

//#endif

//
// module data structure
//

  PIMAGEHLP_MODULE64 = ^IMAGEHLP_MODULE64;
  {$EXTERNALSYM PIMAGEHLP_MODULE64}
  _IMAGEHLP_MODULE64 = record
    SizeOfStruct: DWORD; // set to sizeof(IMAGEHLP_MODULE64)
    BaseOfImage: DWORD64; // base load address of module
    ImageSize: DWORD; // virtual size of the loaded module
    TimeDateStamp: DWORD; // date/time stamp from pe header
    CheckSum: DWORD; // checksum from the pe header
    NumSyms: DWORD; // number of symbols in the symbol table
    SymType: SYM_TYPE; // type of symbols loaded
    ModuleName: array [0..3] of CHAR; // module name
    ImageName: array [0..255] of CHAR; // image name
    LoadedImageName: array [0..255] of CHAR; // symbol file name
  end;
  {$EXTERNALSYM _IMAGEHLP_MODULE64}
  IMAGEHLP_MODULE64 = _IMAGEHLP_MODULE64;
  {$EXTERNALSYM IMAGEHLP_MODULE64}
  TImageHlpModule64 = IMAGEHLP_MODULE64;
  PImageHlpModule64 = PIMAGEHLP_MODULE64;

  PIMAGEHLP_MODULEW64 = ^IMAGEHLP_MODULEW64;
  {$EXTERNALSYM PIMAGEHLP_MODULEW64}
  _IMAGEHLP_MODULE64W = record
    SizeOfStruct: DWORD; // set to sizeof(IMAGEHLP_MODULE64)
    BaseOfImage: DWORD64; // base load address of module
    ImageSize: DWORD; // virtual size of the loaded module
    TimeDateStamp: DWORD; // date/time stamp from pe header
    CheckSum: DWORD; // checksum from the pe header
    NumSyms: DWORD; // number of symbols in the symbol table
    SymType: SYM_TYPE; // type of symbols loaded
    ModuleName: array [0..31] of WCHAR; // module name
    ImageName: array [0..255] of WCHAR; // image name
    LoadedImageName: array [0..255] of WCHAR; // symbol file name
  end;
  {$EXTERNALSYM _IMAGEHLP_MODULE64W}
  IMAGEHLP_MODULEW64 = _IMAGEHLP_MODULE64W;
  {$EXTERNALSYM IMAGEHLP_MODULEW64}
  TImageHlpModuleW64 = IMAGEHLP_MODULEW64;
  PImageHlpModuleW64 = PIMAGEHLP_MODULEW64;

  PIMAGEHLP_MODULE = ^IMAGEHLP_MODULE;
  {$EXTERNALSYM PIMAGEHLP_MODULE}
  _IMAGEHLP_MODULE = record
    SizeOfStruct: DWORD; // set to sizeof(IMAGEHLP_MODULE)
    BaseOfImage: DWORD; // base load address of module
    ImageSize: DWORD; // virtual size of the loaded module
    TimeDateStamp: DWORD; // date/time stamp from pe header
    CheckSum: DWORD; // checksum from the pe header
    NumSyms: DWORD; // number of symbols in the symbol table
    SymType: SYM_TYPE; // type of symbols loaded
    ModuleName: array [0..31] of CHAR; // module name
    ImageName: array [0..255] of CHAR; // image name
    LoadedImageName: array [0..255] of CHAR; // symbol file name
  end;
  {$EXTERNALSYM _IMAGEHLP_MODULE}
  IMAGEHLP_MODULE = _IMAGEHLP_MODULE;
  {$EXTERNALSYM IMAGEHLP_MODULE}
  TImageHlpModule = IMAGEHLP_MODULE;
  PImageHlpModule = PIMAGEHLP_MODULE;

  PIMAGEHLP_MODULEW = ^IMAGEHLP_MODULEW;
  {$EXTERNALSYM PIMAGEHLP_MODULEW}
  _IMAGEHLP_MODULEW = record
    SizeOfStruct: DWORD; // set to sizeof(IMAGEHLP_MODULE)
    BaseOfImage: DWORD; // base load address of module
    ImageSize: DWORD; // virtual size of the loaded module
    TimeDateStamp: DWORD; // date/time stamp from pe header
    CheckSum: DWORD; // checksum from the pe header
    NumSyms: DWORD; // number of symbols in the symbol table
    SymType: SYM_TYPE; // type of symbols loaded
    ModuleName: array [0..31] of WCHAR; // module name
    ImageName: array [0..255] of WCHAR; // image name
    LoadedImageName: array [0..255] of WCHAR; // symbol file name
  end;
  {$EXTERNALSYM _IMAGEHLP_MODULEW}
  IMAGEHLP_MODULEW = _IMAGEHLP_MODULEW;
  {$EXTERNALSYM IMAGEHLP_MODULEW}
  TImageHlpModuleW = IMAGEHLP_MODULEW;
  PImageHlpModuleW = PIMAGEHLP_MODULEW;

//
// source file line data structure
//

  PIMAGEHLP_LINE64 = ^IMAGEHLP_LINE64;
  {$EXTERNALSYM PIMAGEHLP_LINE64}
  _IMAGEHLP_LINE64 = record
    SizeOfStruct: DWORD; // set to sizeof(IMAGEHLP_LINE64)
    Key: PVOID; // internal
    LineNumber: DWORD; // line number in file
    FileName: PCHAR; // full filename
    Address: DWORD64; // first instruction of line
  end;
  {$EXTERNALSYM _IMAGEHLP_LINE64}
  IMAGEHLP_LINE64 = _IMAGEHLP_LINE64;
  {$EXTERNALSYM IMAGEHLP_LINE64}
  TImageHlpLine64 = IMAGEHLP_LINE64;
  PImageHlpLine64 = PIMAGEHLP_LINE64;

  PIMAGEHLP_LINE = ^IMAGEHLP_LINE;
  {$EXTERNALSYM PIMAGEHLP_LINE}
  _IMAGEHLP_LINE = record
    SizeOfStruct: DWORD; // set to sizeof(IMAGEHLP_LINE)
    Key: PVOID; // internal
    LineNumber: DWORD; // line number in file
    FileName: PCHAR; // full filename
    Address: DWORD; // first instruction of line
  end;
  {$EXTERNALSYM _IMAGEHLP_LINE}
  IMAGEHLP_LINE = _IMAGEHLP_LINE;
  {$EXTERNALSYM IMAGEHLP_LINE}
  TImageHlpLine = IMAGEHLP_LINE;
  PImageHlpLine = PIMAGEHLP_LINE;

//
// source file structure
//

type
  _SOURCEFILE = record
    ModBase: DWORD64;                // base address of loaded module
    FileName: PCHAR;                 // full filename of source
  end;
  {$EXTERNALSYM _SOURCEFILE}
  SOURCEFILE = _SOURCEFILE;
  {$EXTERNALSYM SOURCEFILE}
  PSOURCEFILE = ^SOURCEFILE;
  {$EXTERNALSYM PSOURCEFILE}
  TSourceFile = SOURCEFILE;

//
// data structures used for registered symbol callbacks
//

const
  CBA_DEFERRED_SYMBOL_LOAD_START    = $00000001;
  {$EXTERNALSYM CBA_DEFERRED_SYMBOL_LOAD_START}
  CBA_DEFERRED_SYMBOL_LOAD_COMPLETE = $00000002;
  {$EXTERNALSYM CBA_DEFERRED_SYMBOL_LOAD_COMPLETE}
  CBA_DEFERRED_SYMBOL_LOAD_FAILURE  = $00000003;
  {$EXTERNALSYM CBA_DEFERRED_SYMBOL_LOAD_FAILURE}
  CBA_SYMBOLS_UNLOADED              = $00000004;
  {$EXTERNALSYM CBA_SYMBOLS_UNLOADED}
  CBA_DUPLICATE_SYMBOL              = $00000005;
  {$EXTERNALSYM CBA_DUPLICATE_SYMBOL}
  CBA_READ_MEMORY                   = $00000006;
  {$EXTERNALSYM CBA_READ_MEMORY}
  CBA_DEFERRED_SYMBOL_LOAD_CANCEL   = $00000007;
  {$EXTERNALSYM CBA_DEFERRED_SYMBOL_LOAD_CANCEL}
  CBA_SET_OPTIONS                   = $00000008;
  {$EXTERNALSYM CBA_SET_OPTIONS}
  CBA_EVENT                         = $00000010;
  {$EXTERNALSYM CBA_EVENT}
  CBA_DEFERRED_SYMBOL_LOAD_PARTIAL  = $00000020;
  {$EXTERNALSYM CBA_DEFERRED_SYMBOL_LOAD_PARTIAL}
  CBA_DEBUG_INFO                    = $10000000;
  {$EXTERNALSYM CBA_DEBUG_INFO}

type
  PIMAGEHLP_CBA_READ_MEMORY = ^IMAGEHLP_CBA_READ_MEMORY;
  {$EXTERNALSYM PIMAGEHLP_CBA_READ_MEMORY}
  _IMAGEHLP_CBA_READ_MEMORY = record
    addr: DWORD64; // address to read from
    buf: PVOID; // buffer to read to
    bytes: DWORD; // amount of bytes to read
    bytesread: LPDWORD; // pointer to store amount of bytes read
  end;
  {$EXTERNALSYM _IMAGEHLP_CBA_READ_MEMORY}
  IMAGEHLP_CBA_READ_MEMORY = _IMAGEHLP_CBA_READ_MEMORY;
  {$EXTERNALSYM IMAGEHLP_CBA_READ_MEMORY}
  TImageHlpCbaReadMemory = IMAGEHLP_CBA_READ_MEMORY;
  PImageHlpCbaReadMemory = PIMAGEHLP_CBA_READ_MEMORY;

const
  sevInfo    = 0;
  {$EXTERNALSYM sevInfo}
  sevProblem = 1;
  {$EXTERNALSYM sevProblem}
  sevAttn    = 2;
  {$EXTERNALSYM sevAttn}
  sevFatal   = 3;
  {$EXTERNALSYM sevFatal}
  sevMax     = 4; // unused
  {$EXTERNALSYM sevMax}

type
  _IMAGEHLP_CBA_EVENT = record
    severity: DWORD;                                     // values from sevInfo to sevFatal
    code: DWORD;                                         // numerical code IDs the error
    desc: PCHAR;                                         // may contain a text description of the error
    object_: PVOID;                                      // value dependant upon the error code
  end;
  {$EXTERNALSYM _IMAGEHLP_CBA_EVENT}
  IMAGEHLP_CBA_EVENT = _IMAGEHLP_CBA_EVENT;
  {$EXTERNALSYM IMAGEHLP_CBA_EVENT}
  PIMAGEHLP_CBA_EVENT = ^IMAGEHLP_CBA_EVENT;
  {$EXTERNALSYM PIMAGEHLP_CBA_EVENT}
  TImageHlpCbaEvent = IMAGEHLP_CBA_EVENT;
  PImageHlpCbaEvent = PIMAGEHLP_CBA_EVENT;

  PIMAGEHLP_DEFERRED_SYMBOL_LOAD64 = ^IMAGEHLP_DEFERRED_SYMBOL_LOAD64;
  {$EXTERNALSYM PIMAGEHLP_DEFERRED_SYMBOL_LOAD64}
  _IMAGEHLP_DEFERRED_SYMBOL_LOAD64 = record
    SizeOfStruct: DWORD; // set to sizeof(IMAGEHLP_DEFERRED_SYMBOL_LOAD64)
    BaseOfImage: DWORD64; // base load address of module
    CheckSum: DWORD; // checksum from the pe header
    TimeDateStamp: DWORD; // date/time stamp from pe header
    FileName: array [0..MAX_PATH - 1] of CHAR; // symbols file or image name
    Reparse: ByteBool; // load failure reparse
    hFile: HANDLE; // file handle, if passed
    Flags: DWORD; //
  end;
  {$EXTERNALSYM _IMAGEHLP_DEFERRED_SYMBOL_LOAD64}
  IMAGEHLP_DEFERRED_SYMBOL_LOAD64 = _IMAGEHLP_DEFERRED_SYMBOL_LOAD64;
  {$EXTERNALSYM IMAGEHLP_DEFERRED_SYMBOL_LOAD64}
  TImageHlpDeferredSymbolLoad64 = IMAGEHLP_DEFERRED_SYMBOL_LOAD64;
  PImageHlpDeferredSymbolLoad64 = PIMAGEHLP_DEFERRED_SYMBOL_LOAD64;

const
  DSLFLAG_MISMATCHED_PDB = $1;
  {$EXTERNALSYM DSLFLAG_MISMATCHED_PDB}
  DSLFLAG_MISMATCHED_DBG = $2;
  {$EXTERNALSYM DSLFLAG_MISMATCHED_DBG}

type
  PIMAGEHLP_DEFERRED_SYMBOL_LOAD = ^IMAGEHLP_DEFERRED_SYMBOL_LOAD;
  {$EXTERNALSYM PIMAGEHLP_DEFERRED_SYMBOL_LOAD}
  _IMAGEHLP_DEFERRED_SYMBOL_LOAD = record
    SizeOfStruct: DWORD; // set to sizeof(IMAGEHLP_DEFERRED_SYMBOL_LOAD)
    BaseOfImage: DWORD; // base load address of module
    CheckSum: DWORD; // checksum from the pe header
    TimeDateStamp: DWORD; // date/time stamp from pe header
    FileName: array [0..MAX_PATH - 1] of CHAR; // symbols file or image name
    Reparse: ByteBool; // load failure reparse
    hFile: HANDLE; // file handle, if passed    
  end;
  {$EXTERNALSYM _IMAGEHLP_DEFERRED_SYMBOL_LOAD}
  IMAGEHLP_DEFERRED_SYMBOL_LOAD = _IMAGEHLP_DEFERRED_SYMBOL_LOAD;
  {$EXTERNALSYM IMAGEHLP_DEFERRED_SYMBOL_LOAD}
  TImageHlpDeferredSymbolLoad = IMAGEHLP_DEFERRED_SYMBOL_LOAD;
  PImageHlpDeferredSymbolLoad = PIMAGEHLP_DEFERRED_SYMBOL_LOAD;

  PIMAGEHLP_DUPLICATE_SYMBOL64 = ^IMAGEHLP_DUPLICATE_SYMBOL64;
  {$EXTERNALSYM PIMAGEHLP_DUPLICATE_SYMBOL64}
  _IMAGEHLP_DUPLICATE_SYMBOL64 = record
    SizeOfStruct: DWORD; // set to sizeof(IMAGEHLP_DUPLICATE_SYMBOL64)
    NumberOfDups: DWORD; // number of duplicates in the Symbol array
    Symbol: PIMAGEHLP_SYMBOL64; // array of duplicate symbols
    SelectedSymbol: DWORD; // symbol selected (-1 to start)
  end;
  {$EXTERNALSYM _IMAGEHLP_DUPLICATE_SYMBOL64}
  IMAGEHLP_DUPLICATE_SYMBOL64 = _IMAGEHLP_DUPLICATE_SYMBOL64;
  {$EXTERNALSYM IMAGEHLP_DUPLICATE_SYMBOL64}
  TImageHlpDuplicateSymbol64 = IMAGEHLP_DUPLICATE_SYMBOL64;
  PImageHlpDuplicateSymbol64 = PIMAGEHLP_DUPLICATE_SYMBOL64;

  PIMAGEHLP_DUPLICATE_SYMBOL = ^IMAGEHLP_DUPLICATE_SYMBOL;
  {$EXTERNALSYM PIMAGEHLP_DUPLICATE_SYMBOL}
  _IMAGEHLP_DUPLICATE_SYMBOL = record
    SizeOfStruct: DWORD; // set to sizeof(IMAGEHLP_DUPLICATE_SYMBOL)
    NumberOfDups: DWORD; // number of duplicates in the Symbol array
    Symbol: PIMAGEHLP_SYMBOL; // array of duplicate symbols
    SelectedSymbol: DWORD; // symbol selected (-1 to start)
  end;
  {$EXTERNALSYM _IMAGEHLP_DUPLICATE_SYMBOL}
  IMAGEHLP_DUPLICATE_SYMBOL = _IMAGEHLP_DUPLICATE_SYMBOL;
  {$EXTERNALSYM IMAGEHLP_DUPLICATE_SYMBOL}
  TImageHlpDuplicateSymbol = IMAGEHLP_DUPLICATE_SYMBOL;
  PImageHlpDuplicateSymbol = PIMAGEHLP_DUPLICATE_SYMBOL;

// If dbghelp ever needs to display graphical UI, it will use this as the parent window.

//BOOL
//SymSetParentWindow(
//    HWND hwnd
//    );

//
// options that are set/returned by SymSetOptions() & SymGetOptions()
// these are used as a mask
//

const
  SYMOPT_CASE_INSENSITIVE  = $00000001;
  {$EXTERNALSYM SYMOPT_CASE_INSENSITIVE}
  SYMOPT_UNDNAME           = $00000002;
  {$EXTERNALSYM SYMOPT_UNDNAME}
  SYMOPT_DEFERRED_LOADS    = $00000004;
  {$EXTERNALSYM SYMOPT_DEFERRED_LOADS}
  SYMOPT_NO_CPP            = $00000008;
  {$EXTERNALSYM SYMOPT_NO_CPP}
  SYMOPT_LOAD_LINES        = $00000010;
  {$EXTERNALSYM SYMOPT_LOAD_LINES}
  SYMOPT_OMAP_FIND_NEAREST = $00000020;
  {$EXTERNALSYM SYMOPT_OMAP_FIND_NEAREST}
  SYMOPT_LOAD_ANYTHING         = $00000040;
  {$EXTERNALSYM SYMOPT_LOAD_ANYTHING}
  SYMOPT_IGNORE_CVREC          = $00000080;
  {$EXTERNALSYM SYMOPT_IGNORE_CVREC}
  SYMOPT_NO_UNQUALIFIED_LOADS  = $00000100;
  {$EXTERNALSYM SYMOPT_NO_UNQUALIFIED_LOADS}
  SYMOPT_FAIL_CRITICAL_ERRORS  = $00000200;
  {$EXTERNALSYM SYMOPT_FAIL_CRITICAL_ERRORS}
  SYMOPT_EXACT_SYMBOLS         = $00000400;
  {$EXTERNALSYM SYMOPT_EXACT_SYMBOLS}
  SYMOPT_ALLOW_ABSOLUTE_SYMBOLS = $00000800;
  {$EXTERNALSYM SYMOPT_ALLOW_ABSOLUTE_SYMBOLS}
  SYMOPT_IGNORE_NT_SYMPATH      = $00001000;
  {$EXTERNALSYM SYMOPT_IGNORE_NT_SYMPATH}
  SYMOPT_INCLUDE_32BIT_MODULES = $00002000;
  {$EXTERNALSYM SYMOPT_INCLUDE_32BIT_MODULES}
  SYMOPT_PUBLICS_ONLY          = $00004000;
  {$EXTERNALSYM SYMOPT_PUBLICS_ONLY}
  SYMOPT_NO_PUBLICS            = $00008000;
  {$EXTERNALSYM SYMOPT_NO_PUBLICS}
  SYMOPT_AUTO_PUBLICS          = $00010000;
  {$EXTERNALSYM SYMOPT_AUTO_PUBLICS}
  SYMOPT_NO_IMAGE_SEARCH       = $00020000;
  {$EXTERNALSYM SYMOPT_NO_IMAGE_SEARCH}
  SYMOPT_SECURE                = $00040000;
  {$EXTERNALSYM SYMOPT_SECURE}

  SYMOPT_DEBUG             = DWORD($80000000);
  {$EXTERNALSYM SYMOPT_DEBUG}

function SymSetOptions(SymOptions: DWORD): DWORD; stdcall;
{$EXTERNALSYM SymSetOptions}

function SymGetOptions: DWORD; stdcall;
{$EXTERNALSYM SymGetOptions}

function SymCleanup(hProcess: HANDLE): BOOL; stdcall;
{$EXTERNALSYM SymCleanup}

function SymMatchString(string_, expression: LPSTR; fCase: BOOL): BOOL; stdcall;
{$EXTERNALSYM SymMatchString}

type
  PSYM_ENUMSOURCFILES_CALLBACK = function (pSourceFile: PSOURCEFILE; UserContext: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PSYM_ENUMSOURCFILES_CALLBACK}
  PSymEnumSourceFilesCallback = PSYM_ENUMSOURCFILES_CALLBACK;

function SymEnumSourceFiles(hProcess: HANDLE; ModBase: ULONG64; Mask: LPSTR;
  cbSrcFiles: PSYM_ENUMSOURCFILES_CALLBACK; UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymEnumSourceFiles}

function SymEnumerateModules64(hProcess: HANDLE; EnumModulesCallback: PSYM_ENUMMODULES_CALLBACK64;
  UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymEnumerateModules64}

function SymEnumerateModules(hProcess: HANDLE; EnumModulesCallback: PSYM_ENUMMODULES_CALLBACK;
  UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymEnumerateModules}

function SymEnumerateSymbols64(hProcess: HANDLE; BaseOfDll: DWORD64;
  EnumSymbolsCallback: PSYM_ENUMSYMBOLS_CALLBACK64; UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymEnumerateSymbols64}

function SymEnumerateSymbolsW64(hProcess: HANDLE; BaseOfDll: DWORD64;
  EnumSymbolsCallback: PSYM_ENUMSYMBOLS_CALLBACK64W; UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymEnumerateSymbolsW64}

function SymEnumerateSymbols(hProcess: HANDLE; BaseOfDll: DWORD;
  EnumSymbolsCallback: PSYM_ENUMSYMBOLS_CALLBACK; UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymEnumerateSymbols}

function SymEnumerateSymbolsW(hProcess: HANDLE; BaseOfDll: DWORD;
  EnumSymbolsCallback: PSYM_ENUMSYMBOLS_CALLBACKW; UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymEnumerateSymbolsW}

function EnumerateLoadedModules64(hProcess: HANDLE; EnumLoadedModulesCallback: PENUMLOADED_MODULES_CALLBACK64;
  UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM EnumerateLoadedModules64}

function EnumerateLoadedModules(hProcess: HANDLE; EnumLoadedModulesCallback: PENUMLOADED_MODULES_CALLBACK;
  UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM EnumerateLoadedModules}

function SymFunctionTableAccess64(hProcess: HANDLE; AddrBase: DWORD64): PVOID; stdcall;
{$EXTERNALSYM SymFunctionTableAccess64}

function SymFunctionTableAccess(hProcess: HANDLE; AddrBase: DWORD): PVOID; stdcall;
{$EXTERNALSYM SymFunctionTableAccess}

function SymGetModuleInfo64(hProcess: HANDLE; qwAddr: DWORD64;
  var ModuleInfo: IMAGEHLP_MODULE64): BOOL; stdcall;
{$EXTERNALSYM SymGetModuleInfo64}

function SymGetModuleInfoW64(hProcess: HANDLE; qwAddr: DWORD64;
  var ModuleInfo: IMAGEHLP_MODULEW64): BOOL; stdcall;
{$EXTERNALSYM SymGetModuleInfoW64}

function SymGetModuleInfo(hProcess: HANDLE; dwAddr: DWORD;
  var ModuleInfo: IMAGEHLP_MODULE): BOOL; stdcall;
{$EXTERNALSYM SymGetModuleInfo}

function SymGetModuleInfoW(hProcess: HANDLE; dwAddr: DWORD;
  var ModuleInfo: IMAGEHLP_MODULEW): BOOL; stdcall;
{$EXTERNALSYM SymGetModuleInfoW}

function SymGetModuleBase64(hProcess: HANDLE; qwAddr: DWORD64): DWORD64; stdcall;
{$EXTERNALSYM SymGetModuleBase64}

function SymGetModuleBase(hProcess: HANDLE; dwAddr: DWORD): DWORD; stdcall;
{$EXTERNALSYM SymGetModuleBase}

function SymGetSymNext64(hProcess: HANDLE; var Symbol: IMAGEHLP_SYMBOL64): BOOL; stdcall;
{$EXTERNALSYM SymGetSymNext64}

function SymGetSymNext(hProcess: HANDLE; var Symbol: IMAGEHLP_SYMBOL): BOOL; stdcall;
{$EXTERNALSYM SymGetSymNext}

function SymGetSymPrev64(hProcess: HANDLE; var Symbol: IMAGEHLP_SYMBOL64): BOOL; stdcall;
{$EXTERNALSYM SymGetSymPrev64}

function SymGetSymPrev(hProcess: HANDLE; var Symbol: IMAGEHLP_SYMBOL): BOOL; stdcall;
{$EXTERNALSYM SymGetSymPrev}

function SymGetLineFromAddr64(hProcess: HANDLE; qwAddr: DWORD64;
  var pdwDisplacement: DWORD; var Line64: IMAGEHLP_LINE64): BOOL; stdcall;
{$EXTERNALSYM SymGetLineFromAddr64}

function SymGetLineFromAddr(hProcess: HANDLE; dwAddr: DWORD;
  var pdwDisplacement: DWORD; var Line: IMAGEHLP_LINE): BOOL; stdcall;
{$EXTERNALSYM SymGetLineFromAddr}

function SymGetLineFromName64(hProcess: HANDLE; ModuleName: PSTR; FileName: PSTR;
  dwLineNumber: DWORD; var plDisplacement: LONG; var Line: IMAGEHLP_LINE64): BOOL; stdcall;
{$EXTERNALSYM SymGetLineFromName64}

function SymGetLineFromName(hProcess: HANDLE; ModuleName: PSTR; FileName: PSTR;
  dwLineNumber: DWORD; var plDisplacement: LONG; var Line: IMAGEHLP_LINE): BOOL; stdcall;
{$EXTERNALSYM SymGetLineFromName}

function SymGetLineNext64(hProcess: HANDLE; var Line: IMAGEHLP_LINE64): BOOL; stdcall;
{$EXTERNALSYM SymGetLineNext64}

function SymGetLineNext(hProcess: HANDLE; var Line: IMAGEHLP_LINE): BOOL; stdcall;
{$EXTERNALSYM SymGetLineNext}

function SymGetLinePrev64(hProcess: HANDLE; var Line: IMAGEHLP_LINE64): BOOL; stdcall;
{$EXTERNALSYM SymGetLinePrev64}

function SymGetLinePrev(hProcess: HANDLE; var Line: IMAGEHLP_LINE): BOOL; stdcall;
{$EXTERNALSYM SymGetLinePrev}

function SymMatchFileName(FileName, Match: PSTR; var FileNameStop, MatchStop: PSTR): BOOL; stdcall;
{$EXTERNALSYM SymMatchFileName}

function SymInitialize(hProcess: HANDLE; UserSearchPath: PSTR; fInvadeProcess: BOOL): BOOL; stdcall;
{$EXTERNALSYM SymInitialize}

function SymGetSearchPath(hProcess: HANDLE; SearchPath: PSTR; SearchPathLength: DWORD): BOOL; stdcall;
{$EXTERNALSYM SymGetSearchPath}

function SymSetSearchPath(hProcess: HANDLE; SearchPath: PSTR): BOOL; stdcall;
{$EXTERNALSYM SymSetSearchPath}

function SymLoadModule64(hProcess, hFile: HANDLE; ImageName, ModuleName: PSTR;
  BaseOfDll: DWORD64; SizeOfDll: DWORD): DWORD64; stdcall;
{$EXTERNALSYM SymLoadModule64}

const
  SLMFLAG_VIRTUAL = $1;
  {$EXTERNALSYM SLMFLAG_VIRTUAL}

function SymLoadModuleEx(hProcess, hFile: HANDLE; ImageName, ModuleName: PSTR; BaseOfDll: DWORD64;
  DllSize: DWORD; Data: PMODLOAD_DATA; Flag: DWORD): DWORD64; stdcall;
{$EXTERNALSYM SymLoadModuleEx}

function SymLoadModule(hProcess, hFile: HANDLE; ImageName, ModuleName: PSTR;
  BaseOfDll: DWORD; SizeOfDll: DWORD): DWORD; stdcall;
{$EXTERNALSYM SymLoadModule}

function SymUnloadModule64(hProcess: HANDLE; BaseOfDll: DWORD64): BOOL; stdcall;
{$EXTERNALSYM SymUnloadModule64}

function SymUnloadModule(hProcess: HANDLE; BaseOfDll: DWORD): BOOL; stdcall;
{$EXTERNALSYM SymUnloadModule}

function SymUnDName64(const sym: IMAGEHLP_SYMBOL64; UnDecName: PSTR;
  UnDecNameLength: DWORD): BOOL; stdcall;
{$EXTERNALSYM SymUnDName64}

function SymUnDName(const sym: IMAGEHLP_SYMBOL; UnDecName: PSTR;
  UnDecNameLength: DWORD): BOOL; stdcall;
{$EXTERNALSYM SymUnDName}

function SymRegisterCallback64(hProcess: HANDLE; CallbackFunction: PSYMBOL_REGISTERED_CALLBACK64;
  UserContext: ULONG64): BOOL; stdcall;
{$EXTERNALSYM SymRegisterCallback64}

function SymRegisterFunctionEntryCallback64(hProcess: HANDLE; CallbackFunction: PSYMBOL_FUNCENTRY_CALLBACK64;
  UserContext: ULONG64): BOOL; stdcall;
{$EXTERNALSYM SymRegisterFunctionEntryCallback64}

function SymRegisterCallback(hProcess: HANDLE; CallbackFunction: PSYMBOL_REGISTERED_CALLBACK;
  UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymRegisterCallback}

function SymRegisterFunctionEntryCallback(hProcess: HANDLE; CallbackFunction: PSYMBOL_FUNCENTRY_CALLBACK;
  UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymRegisterFunctionEntryCallback}

type
  PIMAGEHLP_SYMBOL_SRC = ^IMAGEHLP_SYMBOL_SRC;
  {$EXTERNALSYM PIMAGEHLP_SYMBOL_SRC}
  _IMAGEHLP_SYMBOL_SRC = record
    sizeofstruct: DWORD;
    type_: DWORD;
    file_: array [0..MAX_PATH - 1] of Char;
  end;
  {$EXTERNALSYM _IMAGEHLP_SYMBOL_SRC}
  IMAGEHLP_SYMBOL_SRC = _IMAGEHLP_SYMBOL_SRC;
  {$EXTERNALSYM IMAGEHLP_SYMBOL_SRC}
  TImageHlpSymbolSrc = IMAGEHLP_SYMBOL_SRC;
  PImageHlpSymbolSrc = PIMAGEHLP_SYMBOL_SRC;

  PMODULE_TYPE_INFO = ^MODULE_TYPE_INFO;
  {$EXTERNALSYM PMODULE_TYPE_INFO}
  _MODULE_TYPE_INFO = record
    dataLength: USHORT;
    leaf: USHORT;
    data: array [0..0] of BYTE;
  end;
  {$EXTERNALSYM _MODULE_TYPE_INFO}
  MODULE_TYPE_INFO = _MODULE_TYPE_INFO;
  {$EXTERNALSYM MODULE_TYPE_INFO}
  TModuleTypeInfo = MODULE_TYPE_INFO;
  PModuleTypeInfo = PMODULE_TYPE_INFO;

type
  PSYMBOL_INFO = ^SYMBOL_INFO;
  {$EXTERNALSYM PSYMBOL_INFO}
  _SYMBOL_INFO = record
    SizeOfStruct: ULONG;
    TypeIndex: ULONG; // Type Index of symbol
    Reserved: array [0..1] of ULONG64;
    Info: ULONG;
    Size: ULONG;
    ModBase: ULONG64; // Base Address of module comtaining this symbol
    Flags: ULONG;
    Value: ULONG64; // Value of symbol, ValuePresent should be 1
    Address: ULONG64; // Address of symbol including base address of module
    Register_: ULONG; // register holding value or pointer to value
    Scope: ULONG; // scope of the symbol
    Tag: ULONG; // pdb classification
    NameLen: ULONG; // Actual length of name
    MaxNameLen: ULONG;
    Name: array [0..0] of CHAR; // Name of symbol
  end;
  {$EXTERNALSYM _SYMBOL_INFO}
  SYMBOL_INFO = _SYMBOL_INFO;
  {$EXTERNALSYM SYMBOL_INFO}
  TSymbolInfo = SYMBOL_INFO;
  PSymbolInfo = PSYMBOL_INFO;

  _SYMBOL_INFO_PACKAGE = record
    si: SYMBOL_INFO;
    name: array [0..MAX_SYM_NAME] of CHAR;
  end;
  {$EXTERNALSYM _SYMBOL_INFO_PACKAGE}
  SYMBOL_INFO_PACKAGE = _SYMBOL_INFO_PACKAGE;
  {$EXTERNALSYM SYMBOL_INFO_PACKAGE}
  PSYMBOL_INFO_PACKAGE = ^SYMBOL_INFO_PACKAGE;
  {$EXTERNALSYM PSYMBOL_INFO_PACKAGE}
  TSymbolInfoPackage = SYMBOL_INFO_PACKAGE;
  PSymbolInfoPackage = PSYMBOL_INFO_PACKAGE;

  PIMAGEHLP_STACK_FRAME = ^IMAGEHLP_STACK_FRAME;
  {$EXTERNALSYM PIMAGEHLP_STACK_FRAME}
  _IMAGEHLP_STACK_FRAME = record
    InstructionOffset: ULONG64;
    ReturnOffset: ULONG64;
    FrameOffset: ULONG64;
    StackOffset: ULONG64;
    BackingStoreOffset: ULONG64;
    FuncTableEntry: ULONG64;
    Params: array [0..3] of ULONG64;
    Reserved: array [0..4] of ULONG64;
    Virtual_: BOOL;
    Reserved2: ULONG;
  end;
  {$EXTERNALSYM _IMAGEHLP_STACK_FRAME}
  IMAGEHLP_STACK_FRAME = _IMAGEHLP_STACK_FRAME;
  {$EXTERNALSYM IMAGEHLP_STACK_FRAME}
  TImageHlpStackFrame = IMAGEHLP_STACK_FRAME;
  PImageHlpStackFrame = PIMAGEHLP_STACK_FRAME;

  IMAGEHLP_CONTEXT = LPVOID;
  {$EXTERNALSYM IMAGEHLP_CONTEXT}
  PIMAGEHLP_CONTEXT = ^IMAGEHLP_CONTEXT;
  {$EXTERNALSYM PIMAGEHLP_CONTEXT}
  TImageHlpContext = IMAGEHLP_CONTEXT;
  PImageHlpContext = PIMAGEHLP_CONTEXT;

function SymSetContext(hProcess: HANDLE; StackFrame: PIMAGEHLP_STACK_FRAME; Context: PIMAGEHLP_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM SymSetContext}

function SymFromAddr(hProcess: HANDLE; Address: DWORD64; Displacement: PDWORD64; Symbol: PSYMBOL_INFO): BOOL; stdcall;
{$EXTERNALSYM SymFromAddr}

// While SymFromName will provide a symbol from a name,
// SymEnumSymbols can provide the same matching information
// for ALL symbols with a matching name, even regular
// expressions.  That way you can search across modules
// and differentiate between identically named symbols.

function SymFromName(hProcess: HANDLE; Name: LPSTR; Symbol: PSYMBOL_INFO): BOOL; stdcall;
{$EXTERNALSYM SymFromName}

type
  PSYM_ENUMERATESYMBOLS_CALLBACK = function (pSymInfo: PSYMBOL_INFO; SymbolSize: ULONG; UserContext: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PSYM_ENUMERATESYMBOLS_CALLBACK}
  PSymEnumerateSymbolsCallback = PSYM_ENUMERATESYMBOLS_CALLBACK;

function SymEnumSymbols(hProcess: HANDLE; BaseOfDll: ULONG64; Mask: PCSTR; EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACK; UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymEnumSymbols}

function SymEnumSymbolsForAddr(hProcess: HANDLE; Address: DWORD64;
  EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACK; UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymEnumSymbolsForAddr}

type
  _IMAGEHLP_SYMBOL_TYPE_INFO = (
    TI_GET_SYMTAG,
    TI_GET_SYMNAME,
    TI_GET_LENGTH,
    TI_GET_TYPE,
    TI_GET_TYPEID,
    TI_GET_BASETYPE,
    TI_GET_ARRAYINDEXTYPEID,
    TI_FINDCHILDREN,
    TI_GET_DATAKIND,
    TI_GET_ADDRESSOFFSET,
    TI_GET_OFFSET,
    TI_GET_VALUE,
    TI_GET_COUNT,
    TI_GET_CHILDRENCOUNT,
    TI_GET_BITPOSITION,
    TI_GET_VIRTUALBASECLASS,
    TI_GET_VIRTUALTABLESHAPEID,
    TI_GET_VIRTUALBASEPOINTEROFFSET,
    TI_GET_CLASSPARENTID,
    TI_GET_NESTED,
    TI_GET_SYMINDEX,
    TI_GET_LEXICALPARENT,
    TI_GET_ADDRESS,
    TI_GET_THISADJUST,
    TI_GET_UDTKIND,
    TI_IS_EQUIV_TO,
    TI_GET_CALLING_CONVENTION);
  {$EXTERNALSYM _IMAGEHLP_SYMBOL_TYPE_INFO}
  IMAGEHLP_SYMBOL_TYPE_INFO = _IMAGEHLP_SYMBOL_TYPE_INFO;
  {$EXTERNALSYM IMAGEHLP_SYMBOL_TYPE_INFO}
  TImageHlpSymbolTypeInfo = IMAGEHLP_SYMBOL_TYPE_INFO;

  PTI_FINDCHILDREN_PARAMS = ^TI_FINDCHILDREN_PARAMS;
  {$EXTERNALSYM PTI_FINDCHILDREN_PARAMS}
  _TI_FINDCHILDREN_PARAMS = record
    Count: ULONG;
    Start: ULONG;
    ChildId: array [0..0] of ULONG;
  end;
  {$EXTERNALSYM _TI_FINDCHILDREN_PARAMS}
  TI_FINDCHILDREN_PARAMS = _TI_FINDCHILDREN_PARAMS;
  {$EXTERNALSYM TI_FINDCHILDREN_PARAMS}
  TTiFindChildrenParams = TI_FINDCHILDREN_PARAMS;
  PTiFindChildrenParams = PTI_FINDCHILDREN_PARAMS;

function SymGetTypeInfo(hProcess: HANDLE; ModBase: DWORD64; TypeId: ULONG; GetType: IMAGEHLP_SYMBOL_TYPE_INFO; pInfo: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymGetTypeInfo}

function SymEnumTypes(hProcess: HANDLE; BaseOfDll: ULONG64; EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACK; UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymEnumTypes}

function SymGetTypeFromName(hProcess: HANDLE; BaseOfDll: ULONG64; Name: LPSTR; Symbol: PSYMBOL_INFO): BOOL; stdcall;
{$EXTERNALSYM SymGetTypeFromName}

function SymAddSymbol(hProcess: HANDLE; BaseOfDll: ULONG64; Name: PCSTR; Address: DWORD64; Size, Flags: DWORD): BOOL; stdcall;
{$EXTERNALSYM SymAddSymbol}

function SymDeleteSymbol(hProcess: HANDLE; BaseOfDll: ULONG64; Name: PCSTR; Address: DWORD64; Flags: DWORD): BOOL; stdcall;
{$EXTERNALSYM SymDeleteSymbol}

//
// Full user-mode dump creation.
//

type
  PDBGHELP_CREATE_USER_DUMP_CALLBACK = function (DataType: DWORD; var Data: PVOID; DataLength: LPDWORD; UserData: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PDBGHELP_CREATE_USER_DUMP_CALLBACK}
  PDbgHelpCreateUserDumpCallback = PDBGHELP_CREATE_USER_DUMP_CALLBACK;

function DbgHelpCreateUserDump(FileName: LPSTR; Callback: PDBGHELP_CREATE_USER_DUMP_CALLBACK; UserData: PVOID): BOOL; stdcall;
{$EXTERNALSYM DbgHelpCreateUserDump}

function DbgHelpCreateUserDumpW(FileName: LPWSTR; Callback: PDBGHELP_CREATE_USER_DUMP_CALLBACK; UserData: PVOID): BOOL; stdcall;
{$EXTERNALSYM DbgHelpCreateUserDumpW}

// -----------------------------------------------------------------
// The following 4 legacy APIs are fully supported, but newer
// ones are recommended.  SymFromName and SymFromAddr provide
// much more detailed info on the returned symbol.

function SymGetSymFromAddr64(hProcess: HANDLE; qwAddr: DWORD64; pdwDisplacement: PDWORD64; Symbol: PIMAGEHLP_SYMBOL64): BOOL; stdcall;
{$EXTERNALSYM SymGetSymFromAddr64}

function SymGetSymFromAddr(hProcess: HANDLE; dwAddr: DWORD; pdwDisplacement: PDWORD; Symbol: PIMAGEHLP_SYMBOL): BOOL; stdcall;
{$EXTERNALSYM SymGetSymFromAddr}

// While following two APIs will provide a symbol from a name,
// SymEnumSymbols can provide the same matching information
// for ALL symbols with a matching name, even regular
// expressions.  That way you can search across modules
// and differentiate between identically named symbols.

function SymGetSymFromName64(hProcess: HANDLE; Name: PSTR; Symbol: PIMAGEHLP_SYMBOL64): BOOL; stdcall;
{$EXTERNALSYM SymGetSymFromName64}

function SymGetSymFromName(hProcess: HANDLE; Name: PSTR; Symbol: PIMAGEHLP_SYMBOL): BOOL; stdcall;
{$EXTERNALSYM SymGetSymFromName}

// -----------------------------------------------------------------
// The following APIs exist only for backwards compatibility
// with a pre-release version documented in an MSDN release.

// You should use SymFindFileInPath if you want to maintain
// future compatibility.

function FindFileInPath(hprocess: HANDLE; SearchPath: LPSTR; FileName: LPSTR; id: PVOID; two: DWORD; three: DWORD; flags: DWORD; FilePath: LPSTR): BOOL; stdcall;
{$EXTERNALSYM FindFileInPath}

// You should use SymFindFileInPath if you want to maintain
// future compatibility.

function FindFileInSearchPath(hprocess: HANDLE; SearchPath: LPSTR; FileName: LPSTR; one: DWORD; two: DWORD; three: DWORD; FilePath: LPSTR): BOOL; stdcall;
{$EXTERNALSYM FindFileInSearchPath}

function SymEnumSym(hProcess: HANDLE; BaseOfDll: ULONG64; EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACK; UserContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM SymEnumSym}

// These values should not be used.
// They have been replaced by SYMFLAG_ values.

const
  SYMF_OMAP_GENERATED  = $00000001;
  SYMF_OMAP_MODIFIED   = $00000002;
  SYMF_REGISTER        = $00000008;
  SYMF_REGREL          = $00000010;
  SYMF_FRAMEREL        = $00000020;
  SYMF_PARAMETER       = $00000040;
  SYMF_LOCAL           = $00000080;
  SYMF_CONSTANT        = $00000100;
  SYMF_EXPORT          = $00000200;
  SYMF_FORWARDER       = $00000400;
  SYMF_FUNCTION        = $00000800;
  SYMF_VIRTUAL         = $00001000;
  SYMF_THUNK           = $00002000;
  SYMF_TLSREL          = $00004000;

// These values should also not be used.
// They have been replaced by SYMFLAG_ values.

  IMAGEHLP_SYMBOL_INFO_VALUEPRESENT         = 1;
  IMAGEHLP_SYMBOL_INFO_REGISTER             = SYMF_REGISTER;        // 0x0008
  IMAGEHLP_SYMBOL_INFO_REGRELATIVE          = SYMF_REGREL;          // 0x0010
  IMAGEHLP_SYMBOL_INFO_FRAMERELATIVE        = SYMF_FRAMEREL;        // 0x0020
  IMAGEHLP_SYMBOL_INFO_PARAMETER            = SYMF_PARAMETER;       // 0x0040
  IMAGEHLP_SYMBOL_INFO_LOCAL                = SYMF_LOCAL;           // 0x0080
  IMAGEHLP_SYMBOL_INFO_CONSTANT             = SYMF_CONSTANT;        // 0x0100
  IMAGEHLP_SYMBOL_FUNCTION                  = SYMF_FUNCTION;        // 0x0800
  IMAGEHLP_SYMBOL_VIRTUAL                   = SYMF_VIRTUAL;         // 0x1000
  IMAGEHLP_SYMBOL_THUNK                     = SYMF_THUNK;           // 0x2000
  IMAGEHLP_SYMBOL_INFO_TLSRELATIVE          = SYMF_TLSREL;          // 0x4000

const
  MINIDUMP_SIGNATURE = ('PMDM');
  {$EXTERNALSYM MINIDUMP_SIGNATURE}
  MINIDUMP_VERSION   = (42899);
  {$EXTERNALSYM MINIDUMP_VERSION}

type
  RVA = DWORD;
  {$EXTERNALSYM RVA}
  RVA64 = ULONG64;
  {$EXTERNALSYM RVA64}

  _MINIDUMP_LOCATION_DESCRIPTOR = record
    DataSize: ULONG32;
    Rva: RVA;
  end;
  {$EXTERNALSYM _MINIDUMP_LOCATION_DESCRIPTOR}
  MINIDUMP_LOCATION_DESCRIPTOR = _MINIDUMP_LOCATION_DESCRIPTOR;
  {$EXTERNALSYM MINIDUMP_LOCATION_DESCRIPTOR}
  TMinidumpLocationDescriptor = MINIDUMP_LOCATION_DESCRIPTOR;
  PMinidumpLocationDescriptor = ^MINIDUMP_LOCATION_DESCRIPTOR;

  _MINIDUMP_LOCATION_DESCRIPTOR64 = record
    DataSize: ULONG64;
    Rva: RVA64;
  end;
  {$EXTERNALSYM _MINIDUMP_LOCATION_DESCRIPTOR64}
  MINIDUMP_LOCATION_DESCRIPTOR64 = _MINIDUMP_LOCATION_DESCRIPTOR64;
  {$EXTERNALSYM MINIDUMP_LOCATION_DESCRIPTOR64}
  TMinidumpLocationDescriptor64 = MINIDUMP_LOCATION_DESCRIPTOR64;
  PMinidumpLocationDescriptor64 = ^MINIDUMP_LOCATION_DESCRIPTOR64;

  PMINIDUMP_MEMORY_DESCRIPTOR = ^MINIDUMP_MEMORY_DESCRIPTOR;
  {$EXTERNALSYM PMINIDUMP_MEMORY_DESCRIPTOR}
  _MINIDUMP_MEMORY_DESCRIPTOR = record
    StartOfMemoryRange: ULONG64;
    Memory: MINIDUMP_LOCATION_DESCRIPTOR;
  end;
  {$EXTERNALSYM _MINIDUMP_MEMORY_DESCRIPTOR}
  MINIDUMP_MEMORY_DESCRIPTOR = _MINIDUMP_MEMORY_DESCRIPTOR;
  {$EXTERNALSYM MINIDUMP_MEMORY_DESCRIPTOR}
  TMinidumpMemoryDescriptor = MINIDUMP_MEMORY_DESCRIPTOR;
  PMinidumpMemoryDescriptor = PMINIDUMP_MEMORY_DESCRIPTOR;

// DESCRIPTOR64 is used for full-memory minidumps where
// all of the raw memory is laid out sequentially at the
// end of the dump.  There is no need for individual RVAs
// as the RVA is the base RVA plus the sum of the preceeding
// data blocks.

  PMINIDUMP_MEMORY_DESCRIPTOR64 = ^MINIDUMP_MEMORY_DESCRIPTOR64;
  {$EXTERNALSYM PMINIDUMP_MEMORY_DESCRIPTOR64}
  _MINIDUMP_MEMORY_DESCRIPTOR64 = record
    StartOfMemoryRange: ULONG64;
    DataSize: ULONG64;
  end;
  {$EXTERNALSYM _MINIDUMP_MEMORY_DESCRIPTOR64}
  MINIDUMP_MEMORY_DESCRIPTOR64 = _MINIDUMP_MEMORY_DESCRIPTOR64;
  {$EXTERNALSYM MINIDUMP_MEMORY_DESCRIPTOR64}
  TMinidumpMemoryDescriptor64 = MINIDUMP_MEMORY_DESCRIPTOR64;
  PMinidumpMemoryDescriptor64 = PMINIDUMP_MEMORY_DESCRIPTOR64;

  PMINIDUMP_HEADER = ^MINIDUMP_HEADER;
  {$EXTERNALSYM PMINIDUMP_HEADER}
  _MINIDUMP_HEADER = record
    Signature: ULONG32;
    Version: ULONG32;
    NumberOfStreams: ULONG32;
    StreamDirectoryRva: RVA;
    CheckSum: ULONG32;
    U: record
    case Integer of
      0: (Reserved: ULONG32);
      1: (TimeDateStamp: ULONG32);
    end;
    Flags: ULONG64;
  end;
  {$EXTERNALSYM _MINIDUMP_HEADER}
  MINIDUMP_HEADER = _MINIDUMP_HEADER;
  {$EXTERNALSYM MINIDUMP_HEADER}
  TMinidumpHeader = MINIDUMP_HEADER;
  PMinidumpHeader = PMINIDUMP_HEADER;

//
// The MINIDUMP_HEADER field StreamDirectoryRva points to 
// an array of MINIDUMP_DIRECTORY structures.
//

  PMINIDUMP_DIRECTORY = ^MINIDUMP_DIRECTORY;
  {$EXTERNALSYM PMINIDUMP_DIRECTORY}
  _MINIDUMP_DIRECTORY = record
    StreamType: ULONG32;
    Location: MINIDUMP_LOCATION_DESCRIPTOR;
  end;
  {$EXTERNALSYM _MINIDUMP_DIRECTORY}
  MINIDUMP_DIRECTORY = _MINIDUMP_DIRECTORY;
  {$EXTERNALSYM MINIDUMP_DIRECTORY}
  TMinidumpDirectory = MINIDUMP_DIRECTORY;
  PMinidumpDirectory = PMINIDUMP_DIRECTORY;

  PMINIDUMP_STRING = ^MINIDUMP_STRING;
  {$EXTERNALSYM PMINIDUMP_STRING}
  _MINIDUMP_STRING = record
    Length: ULONG32; // Length in bytes of the string
    Buffer: PWCHAR; // Variable size buffer
  end;
  {$EXTERNALSYM _MINIDUMP_STRING}
  MINIDUMP_STRING = _MINIDUMP_STRING;
  {$EXTERNALSYM MINIDUMP_STRING}
  TMinidumpString = MINIDUMP_STRING;
  PMinidumpString = PMINIDUMP_STRING;

//
// The MINIDUMP_DIRECTORY field StreamType may be one of the following types.
// Types will be added in the future, so if a program reading the minidump
// header encounters a stream type it does not understand it should ignore
// the data altogether. Any tag above LastReservedStream will not be used by
// the system and is reserved for program-specific information.
//

const
  UnusedStream                = 0;
  {$EXTERNALSYM UnusedStream}
  ReservedStream0             = 1;
  {$EXTERNALSYM ReservedStream0}
  ReservedStream1             = 2;
  {$EXTERNALSYM ReservedStream1}
  ThreadListStream            = 3;
  {$EXTERNALSYM ThreadListStream}
  ModuleListStream            = 4;
  {$EXTERNALSYM ModuleListStream}
  MemoryListStream            = 5;
  {$EXTERNALSYM MemoryListStream}
  ExceptionStream             = 6;
  {$EXTERNALSYM ExceptionStream}
  SystemInfoStream            = 7;
  {$EXTERNALSYM SystemInfoStream}
  ThreadExListStream          = 8;
  {$EXTERNALSYM ThreadExListStream}
  Memory64ListStream          = 9;
  {$EXTERNALSYM Memory64ListStream}
  CommentStreamA              = 10;
  {$EXTERNALSYM CommentStreamA}
  CommentStreamW              = 11;
  {$EXTERNALSYM CommentStreamW}
  HandleDataStream            = 12;
  {$EXTERNALSYM HandleDataStream}
  FunctionTableStream         = 13;
  {$EXTERNALSYM FunctionTableStream}
  UnloadedModuleListStream   = 14;
  {$EXTERNALSYM UnloadedModuleListStream}
  MiscInfoStream             = 15;
  {$EXTERNALSYM MiscInfoStream}

  LastReservedStream          = $ffff;
  {$EXTERNALSYM LastReservedStream}

type
  _MINIDUMP_STREAM_TYPE = DWORD;
  {$EXTERNALSYM MINIDUMP_STREAM_TYPE}
  MINIDUMP_STREAM_TYPE = _MINIDUMP_STREAM_TYPE;
  {$EXTERNALSYM _MINIDUMP_STREAM_TYPE}
  TMinidumpStreamType = MINIDUMP_STREAM_TYPE;

//
// The minidump system information contains processor and
// Operating System specific information.
//

type
  _CPU_INFORMATION = record
    case Integer of

        //
        // X86 platforms use CPUID function to obtain processor information.
        //

        0: (

          //
          // CPUID Subfunction 0, register EAX (VendorId [0]),
          // EBX (VendorId [1]) and ECX (VendorId [2]).
          //

          VendorId: array [0..2] of ULONG32;

          //
          // CPUID Subfunction 1, register EAX
          //

          VersionInformation: ULONG32;

          //
          // CPUID Subfunction 1, register EDX
          //

          FeatureInformation: ULONG32;

          //
          // CPUID, Subfunction 80000001, register EBX. This will only
          // be obtained if the vendor id is "AuthenticAMD".
          //

          AMDExtendedCpuFeatures: ULONG32);

        //
        // Non-x86 platforms use processor feature flags.
        //

        1: (
          ProcessorFeatures: array [0..1] of ULONG64);
    end;

  _MINIDUMP_SYSTEM_INFO = record

    //
    // ProcessorArchitecture, ProcessorLevel and ProcessorRevision are all
    // taken from the SYSTEM_INFO structure obtained by GetSystemInfo( ).
    //

    ProcessorArchitecture: USHORT;
    ProcessorLevel: USHORT;
    ProcessorRevision: USHORT;

    U: record
    case Integer of
      0: (Reserved0: USHORT);
      1: (
        NumberOfProcessors: UCHAR;
        ProductType: UCHAR);
    end;

    //
    // MajorVersion, MinorVersion, BuildNumber, PlatformId and
    // CSDVersion are all taken from the OSVERSIONINFO structure
    // returned by GetVersionEx( ).
    //

    MajorVersion: ULONG32;
    MinorVersion: ULONG32;
    BuildNumber: ULONG32;
    PlatformId: ULONG32;

    //
    // RVA to a CSDVersion string in the string table.
    //

    CSDVersionRva: RVA;

    U2: record
    case Integer of
      0: (Reserved1: ULONG32);
      1: (
        SuiteMask: USHORT;
        Reserved2: USHORT);
    end;
    
    //
    // CPU information is obtained from one of two places.
    //
    //  1) On x86 computers, CPU_INFORMATION is obtained from the CPUID
    //     instruction. You must use the X86 portion of the union for X86
    //     computers.
    //
    //  2) On non-x86 architectures, CPU_INFORMATION is obtained by calling
    //     IsProcessorFeatureSupported().
    //

    Cpu: _CPU_INFORMATION;
  end;
  {$EXTERNALSYM _MINIDUMP_SYSTEM_INFO}
  MINIDUMP_SYSTEM_INFO = _MINIDUMP_SYSTEM_INFO;
  {$EXTERNALSYM MINIDUMP_SYSTEM_INFO}
  PMINIDUMP_SYSTEM_INFO = ^MINIDUMP_SYSTEM_INFO;
  {$EXTERNALSYM PMINIDUMP_SYSTEM_INFO}
  TMinidumpSystemInfo = MINIDUMP_SYSTEM_INFO;
  PMinidumpSystemInfo = PMINIDUMP_SYSTEM_INFO;

  CPU_INFORMATION = _CPU_INFORMATION;
  {$EXTERNALSYM CPU_INFORMATION}
  PCPU_INFORMATION = CPU_INFORMATION;
  {$EXTERNALSYM PCPU_INFORMATION}

//
// The minidump thread contains standard thread
// information plus an RVA to the memory for this 
// thread and an RVA to the CONTEXT structure for
// this thread.
//


//
// ThreadId must be 4 bytes on all architectures.
//

// C_ASSERT (sizeof ( ((PPROCESS_INFORMATION)0)->dwThreadId ) == 4);

type
  PMINIDUMP_THREAD = ^MINIDUMP_THREAD;
  {$EXTERNALSYM PMINIDUMP_THREAD}
  _MINIDUMP_THREAD = record
    ThreadId: ULONG32;
    SuspendCount: ULONG32;
    PriorityClass: ULONG32;
    Priority: ULONG32;
    Teb: ULONG64;
    Stack: MINIDUMP_MEMORY_DESCRIPTOR;
    ThreadContext: MINIDUMP_LOCATION_DESCRIPTOR;
  end;
  {$EXTERNALSYM _MINIDUMP_THREAD}
  MINIDUMP_THREAD = _MINIDUMP_THREAD;
  {$EXTERNALSYM MINIDUMP_THREAD}
  TMinidumpThread = MINIDUMP_THREAD;
  PMinidumpThread = PMINIDUMP_THREAD;

//
// The thread list is a container of threads.
//

  PMINIDUMP_THREAD_LIST = ^MINIDUMP_THREAD_LIST;
  {$EXTERNALSYM PMINIDUMP_THREAD_LIST}
  _MINIDUMP_THREAD_LIST = record
    NumberOfThreads: ULONG32;
    Threads: array [0..0] of MINIDUMP_THREAD;
  end;
  {$EXTERNALSYM _MINIDUMP_THREAD_LIST}
  MINIDUMP_THREAD_LIST = _MINIDUMP_THREAD_LIST;
  {$EXTERNALSYM MINIDUMP_THREAD_LIST}
  TMinidumpThreadList = MINIDUMP_THREAD_LIST;
  PMinidumpThreadList = PMINIDUMP_THREAD_LIST;

  PMINIDUMP_THREAD_EX = ^MINIDUMP_THREAD_EX;
  {$EXTERNALSYM PMINIDUMP_THREAD_EX}
  _MINIDUMP_THREAD_EX = record
    ThreadId: ULONG32;
    SuspendCount: ULONG32;
    PriorityClass: ULONG32;
    Priority: ULONG32;
    Teb: ULONG64;
    Stack: MINIDUMP_MEMORY_DESCRIPTOR;
    ThreadContext: MINIDUMP_LOCATION_DESCRIPTOR;
    BackingStore: MINIDUMP_MEMORY_DESCRIPTOR;
  end;
  {$EXTERNALSYM _MINIDUMP_THREAD_EX}
  MINIDUMP_THREAD_EX = _MINIDUMP_THREAD_EX;
  {$EXTERNALSYM MINIDUMP_THREAD_EX}
  TMinidumpThreadEx = MINIDUMP_THREAD_EX;
  PMinidumpThreadEx = PMINIDUMP_THREAD_EX;

//
// The thread list is a container of threads.
//

  PMINIDUMP_THREAD_EX_LIST = ^MINIDUMP_THREAD_EX_LIST;
  {$EXTERNALSYM PMINIDUMP_THREAD_EX_LIST}
  _MINIDUMP_THREAD_EX_LIST = record
    NumberOfThreads: ULONG32;
    Threads: array [0..0] of MINIDUMP_THREAD_EX;
  end;
  {$EXTERNALSYM _MINIDUMP_THREAD_EX_LIST}
  MINIDUMP_THREAD_EX_LIST = _MINIDUMP_THREAD_EX_LIST;
  {$EXTERNALSYM MINIDUMP_THREAD_EX_LIST}
  TMinidumpThreadExList = MINIDUMP_THREAD_EX_LIST;
  PMinidumpThreadExList = PMINIDUMP_THREAD_EX_LIST;


//
// The MINIDUMP_EXCEPTION is the same as EXCEPTION on Win64.
//

  PMINIDUMP_EXCEPTION = ^MINIDUMP_EXCEPTION;
  {$EXTERNALSYM PMINIDUMP_EXCEPTION}
  _MINIDUMP_EXCEPTION = record
    ExceptionCode: ULONG32;
    ExceptionFlags: ULONG32;
    ExceptionRecord: ULONG64;
    ExceptionAddress: ULONG64;
    NumberParameters: ULONG32;
    __unusedAlignment: ULONG32;
    ExceptionInformation: array [0..EXCEPTION_MAXIMUM_PARAMETERS - 1] of ULONG64;
  end;
  {$EXTERNALSYM _MINIDUMP_EXCEPTION}
  MINIDUMP_EXCEPTION = _MINIDUMP_EXCEPTION;
  {$EXTERNALSYM MINIDUMP_EXCEPTION}
  TMinidumpException = MINIDUMP_EXCEPTION;
  PMinidumpException = PMINIDUMP_EXCEPTION;

//
// The exception information stream contains the id of the thread that caused
// the exception (ThreadId), the exception record for the exception
// (ExceptionRecord) and an RVA to the thread context where the exception
// occured.
//

  PMINIDUMP_EXCEPTION_STREAM = ^MINIDUMP_EXCEPTION_STREAM;
  {$EXTERNALSYM PMINIDUMP_EXCEPTION_STREAM}
  _MINIDUMP_EXCEPTION_STREAM = record
    ThreadId: ULONG32;
    __alignment: ULONG32;
    ExceptionRecord: MINIDUMP_EXCEPTION;
    ThreadContext: MINIDUMP_LOCATION_DESCRIPTOR;
  end;
  {$EXTERNALSYM _MINIDUMP_EXCEPTION_STREAM}
  MINIDUMP_EXCEPTION_STREAM = _MINIDUMP_EXCEPTION_STREAM;
  {$EXTERNALSYM MINIDUMP_EXCEPTION_STREAM}
  TMinidumpExceptionStream = MINIDUMP_EXCEPTION_STREAM;
  PMinidumpExceptionStream = PMINIDUMP_EXCEPTION_STREAM;

//
// The MINIDUMP_MODULE contains information about a
// a specific module. It includes the CheckSum and
// the TimeDateStamp for the module so the module
// can be reloaded during the analysis phase.
//

  PMINIDUMP_MODULE = ^MINIDUMP_MODULE;
  {$EXTERNALSYM PMINIDUMP_MODULE}
  _MINIDUMP_MODULE = record
    BaseOfImage: ULONG64;
    SizeOfImage: ULONG32;
    CheckSum: ULONG32;
    TimeDateStamp: ULONG32;
    ModuleNameRva: RVA;
    VersionInfo: VS_FIXEDFILEINFO;
    CvRecord: MINIDUMP_LOCATION_DESCRIPTOR;
    MiscRecord: MINIDUMP_LOCATION_DESCRIPTOR;
    Reserved0: ULONG64; // Reserved for future use.
    Reserved1: ULONG64; // Reserved for future use.
  end;
  {$EXTERNALSYM _MINIDUMP_MODULE}
  MINIDUMP_MODULE = _MINIDUMP_MODULE;
  {$EXTERNALSYM MINIDUMP_MODULE}
  TMinidumpModule = MINIDUMP_MODULE;
  PMinidumpModule = PMINIDUMP_MODULE;

//
// The minidump module list is a container for modules.
//

  PMINIDUMP_MODULE_LIST = ^MINIDUMP_MODULE_LIST;
  {$EXTERNALSYM PMINIDUMP_MODULE_LIST}
  _MINIDUMP_MODULE_LIST = record
    NumberOfModules: ULONG32;
    Modules: array [0..0] of MINIDUMP_MODULE;
  end;
  {$EXTERNALSYM _MINIDUMP_MODULE_LIST}
  MINIDUMP_MODULE_LIST = _MINIDUMP_MODULE_LIST;
  {$EXTERNALSYM MINIDUMP_MODULE_LIST}
  TMinidumpModuleList = MINIDUMP_MODULE_LIST;
  PMinidumpModuleList = PMINIDUMP_MODULE_LIST;

//
// Memory Ranges
//

  PMINIDUMP_MEMORY_LIST = ^MINIDUMP_MEMORY_LIST;
  {$EXTERNALSYM PMINIDUMP_MEMORY_LIST}
  _MINIDUMP_MEMORY_LIST = record
    NumberOfMemoryRanges: ULONG32;
    MemoryRanges: array [0..0] of MINIDUMP_MEMORY_DESCRIPTOR;
  end;
  {$EXTERNALSYM _MINIDUMP_MEMORY_LIST}
  MINIDUMP_MEMORY_LIST = _MINIDUMP_MEMORY_LIST;
  {$EXTERNALSYM MINIDUMP_MEMORY_LIST}
  TMinidumpMemoryList = MINIDUMP_MEMORY_LIST;
  PMinidumpMemoryList = PMINIDUMP_MEMORY_LIST;

  PMINIDUMP_MEMORY64_LIST = ^MINIDUMP_MEMORY64_LIST;
  {$EXTERNALSYM PMINIDUMP_MEMORY64_LIST}
  _MINIDUMP_MEMORY64_LIST = record
    NumberOfMemoryRanges: ULONG64;
    BaseRva: RVA64;
    MemoryRanges: array [0..0] of MINIDUMP_MEMORY_DESCRIPTOR64;
  end;
  {$EXTERNALSYM _MINIDUMP_MEMORY64_LIST}
  MINIDUMP_MEMORY64_LIST = _MINIDUMP_MEMORY64_LIST;
  {$EXTERNALSYM MINIDUMP_MEMORY64_LIST}
  TMinidumpMemory64List = MINIDUMP_MEMORY64_LIST;
  PMinidumpMemory64List = PMINIDUMP_MEMORY64_LIST;

//
// Support for user supplied exception information.
//

  PMINIDUMP_EXCEPTION_INFORMATION = ^MINIDUMP_EXCEPTION_INFORMATION;
  {$EXTERNALSYM PMINIDUMP_EXCEPTION_INFORMATION}
  _MINIDUMP_EXCEPTION_INFORMATION = record
    ThreadId: DWORD;
    ExceptionPointers: PEXCEPTION_POINTERS;
    ClientPointers: BOOL;
  end;
  {$EXTERNALSYM _MINIDUMP_EXCEPTION_INFORMATION}
  MINIDUMP_EXCEPTION_INFORMATION = _MINIDUMP_EXCEPTION_INFORMATION;
  {$EXTERNALSYM MINIDUMP_EXCEPTION_INFORMATION}
  TMinidumpExceptionInformation = MINIDUMP_EXCEPTION_INFORMATION;
  PMinidumpExceptionInformation = PMINIDUMP_EXCEPTION_INFORMATION;

//
// Support for capturing system handle state at the time of the dump.
//

  PMINIDUMP_HANDLE_DESCRIPTOR = ^MINIDUMP_HANDLE_DESCRIPTOR;
  {$EXTERNALSYM PMINIDUMP_HANDLE_DESCRIPTOR}
  _MINIDUMP_HANDLE_DESCRIPTOR = record
    Handle: ULONG64;
    TypeNameRva: RVA;
    ObjectNameRva: RVA;
    Attributes: ULONG32;
    GrantedAccess: ULONG32;
    HandleCount: ULONG32;
    PointerCount: ULONG32;
  end;
  {$EXTERNALSYM _MINIDUMP_HANDLE_DESCRIPTOR}
  MINIDUMP_HANDLE_DESCRIPTOR = _MINIDUMP_HANDLE_DESCRIPTOR;
  {$EXTERNALSYM MINIDUMP_HANDLE_DESCRIPTOR}
  TMinidumpHandleDescriptor = MINIDUMP_HANDLE_DESCRIPTOR;
  PMinidumpHandleDescriptor = PMINIDUMP_HANDLE_DESCRIPTOR;

  PMINIDUMP_HANDLE_DATA_STREAM = ^MINIDUMP_HANDLE_DATA_STREAM;
  {$EXTERNALSYM PMINIDUMP_HANDLE_DATA_STREAM}
  _MINIDUMP_HANDLE_DATA_STREAM = record
    SizeOfHeader: ULONG32;
    SizeOfDescriptor: ULONG32;
    NumberOfDescriptors: ULONG32;
    Reserved: ULONG32;
  end;
  {$EXTERNALSYM _MINIDUMP_HANDLE_DATA_STREAM}
  MINIDUMP_HANDLE_DATA_STREAM = _MINIDUMP_HANDLE_DATA_STREAM;
  {$EXTERNALSYM MINIDUMP_HANDLE_DATA_STREAM}
  TMinidumpHandleDataStream = MINIDUMP_HANDLE_DATA_STREAM;
  PMinidumpHandleDataStream = PMINIDUMP_HANDLE_DATA_STREAM;

//
// Support for capturing dynamic function table state at the time of the dump.
//

  PMINIDUMP_FUNCTION_TABLE_DESCRIPTOR = ^MINIDUMP_FUNCTION_TABLE_DESCRIPTOR;
  {$EXTERNALSYM PMINIDUMP_FUNCTION_TABLE_DESCRIPTOR}
  _MINIDUMP_FUNCTION_TABLE_DESCRIPTOR = record
    MinimumAddress: ULONG64;
    MaximumAddress: ULONG64;
    BaseAddress: ULONG64;
    EntryCount: ULONG32;
    SizeOfAlignPad: ULONG32;
  end;
  {$EXTERNALSYM _MINIDUMP_FUNCTION_TABLE_DESCRIPTOR}
  MINIDUMP_FUNCTION_TABLE_DESCRIPTOR = _MINIDUMP_FUNCTION_TABLE_DESCRIPTOR;
  {$EXTERNALSYM MINIDUMP_FUNCTION_TABLE_DESCRIPTOR}
  TMinidumpFunctionTableDescriptor = MINIDUMP_FUNCTION_TABLE_DESCRIPTOR;
  PMinidumpFunctionTableDescriptor = PMINIDUMP_FUNCTION_TABLE_DESCRIPTOR;

  PMINIDUMP_FUNCTION_TABLE_STREAM = ^MINIDUMP_FUNCTION_TABLE_STREAM;
  {$EXTERNALSYM PMINIDUMP_FUNCTION_TABLE_STREAM}
  _MINIDUMP_FUNCTION_TABLE_STREAM = record
    SizeOfHeader: ULONG32;
    SizeOfDescriptor: ULONG32;
    SizeOfNativeDescriptor: ULONG32;
    SizeOfFunctionEntry: ULONG32;
    NumberOfDescriptors: ULONG32;
    SizeOfAlignPad: ULONG32;
  end;
  {$EXTERNALSYM _MINIDUMP_FUNCTION_TABLE_STREAM}
  MINIDUMP_FUNCTION_TABLE_STREAM = _MINIDUMP_FUNCTION_TABLE_STREAM;
  {$EXTERNALSYM MINIDUMP_FUNCTION_TABLE_STREAM}
  TMinidumpFunctionTableStream = MINIDUMP_FUNCTION_TABLE_STREAM;
  PMinidumpFunctionTableStream = PMINIDUMP_FUNCTION_TABLE_STREAM;

//
// The MINIDUMP_UNLOADED_MODULE contains information about a
// a specific module that was previously loaded but no
// longer is.  This can help with diagnosing problems where
// callers attempt to call code that is no longer loaded.
//

  _MINIDUMP_UNLOADED_MODULE = record
    BaseOfImage: ULONG64;
    SizeOfImage: ULONG32;
    CheckSum: ULONG32;
    TimeDateStamp: ULONG32;
    ModuleNameRva: RVA;
  end;
  {$EXTERNALSYM _MINIDUMP_UNLOADED_MODULE}
  MINIDUMP_UNLOADED_MODULE = _MINIDUMP_UNLOADED_MODULE;
  {$EXTERNALSYM MINIDUMP_UNLOADED_MODULE}
  PMINIDUMP_UNLOADED_MODULE = ^MINIDUMP_UNLOADED_MODULE;
  {$EXTERNALSYM PMINIDUMP_UNLOADED_MODULE}
  TMiniDumpUnloadedModule = MINIDUMP_UNLOADED_MODULE;
  PMiniDumpUnloadedModule = PMINIDUMP_UNLOADED_MODULE;

//
// The minidump unloaded module list is a container for unloaded modules.
//

  _MINIDUMP_UNLOADED_MODULE_LIST = record
    SizeOfHeader: ULONG32;
    SizeOfEntry: ULONG32;
    NumberOfEntries: ULONG32;
  end;
  {$EXTERNALSYM _MINIDUMP_UNLOADED_MODULE_LIST}
  MINIDUMP_UNLOADED_MODULE_LIST = _MINIDUMP_UNLOADED_MODULE_LIST;
  {$EXTERNALSYM MINIDUMP_UNLOADED_MODULE_LIST}
  PMINIDUMP_UNLOADED_MODULE_LIST = ^MINIDUMP_UNLOADED_MODULE_LIST;
  {$EXTERNALSYM PMINIDUMP_UNLOADED_MODULE_LIST}
  TMiniDumpUnloadedModuleList = MINIDUMP_UNLOADED_MODULE_LIST;
  PMiniDumpUnloadedModuleList = PMINIDUMP_UNLOADED_MODULE_LIST;

//
// The miscellaneous information stream contains a variety
// of small pieces of information.  A member is valid if
// it's within the available size and its corresponding
// bit is set.
//

const
  MINIDUMP_MISC1_PROCESS_ID    = $00000001;
  {$EXTERNALSYM MINIDUMP_MISC1_PROCESS_ID}
  MINIDUMP_MISC1_PROCESS_TIMES = $00000002;
  {$EXTERNALSYM MINIDUMP_MISC1_PROCESS_TIMES}

type
  _MINIDUMP_MISC_INFO = record
    SizeOfInfo: ULONG32;
    Flags1: ULONG32;
    ProcessId: ULONG32;
    ProcessCreateTime: ULONG32;
    ProcessUserTime: ULONG32;
    ProcessKernelTime: ULONG32;
  end;
  {$EXTERNALSYM _MINIDUMP_MISC_INFO}
  MINIDUMP_MISC_INFO = _MINIDUMP_MISC_INFO;
  {$EXTERNALSYM MINIDUMP_MISC_INFO}
  PMINIDUMP_MISC_INFO = ^MINIDUMP_MISC_INFO;
  {$EXTERNALSYM PMINIDUMP_MISC_INFO}
  TMiniDumpMiscInfo = MINIDUMP_MISC_INFO;
  PMiniDumpMiscInfo = PMINIDUMP_MISC_INFO;

//
// Support for arbitrary user-defined information.
//

  PMINIDUMP_USER_RECORD = ^MINIDUMP_USER_RECORD;
  {$EXTERNALSYM PMINIDUMP_USER_RECORD}
  _MINIDUMP_USER_RECORD = record
    Type_: ULONG32;
    Memory: MINIDUMP_LOCATION_DESCRIPTOR;
  end;
  {$EXTERNALSYM _MINIDUMP_USER_RECORD}
  MINIDUMP_USER_RECORD = _MINIDUMP_USER_RECORD;
  {$EXTERNALSYM MINIDUMP_USER_RECORD}
  TMinidumpUserRecord = MINIDUMP_USER_RECORD;
  PMinidumpUserRecord = PMINIDUMP_USER_RECORD;

  PMINIDUMP_USER_STREAM = ^MINIDUMP_USER_STREAM;
  {$EXTERNALSYM PMINIDUMP_USER_STREAM}
  _MINIDUMP_USER_STREAM = record
    Type_: ULONG32;
    BufferSize: ULONG;
    Buffer: PVOID;
  end;
  {$EXTERNALSYM _MINIDUMP_USER_STREAM}
  MINIDUMP_USER_STREAM = _MINIDUMP_USER_STREAM;
  {$EXTERNALSYM MINIDUMP_USER_STREAM}
  TMinidumpUserStream = MINIDUMP_USER_STREAM;
  PMinidumpUserStream = PMINIDUMP_USER_STREAM;

  PMINIDUMP_USER_STREAM_INFORMATION = ^MINIDUMP_USER_STREAM_INFORMATION;
  {$EXTERNALSYM PMINIDUMP_USER_STREAM_INFORMATION}
  _MINIDUMP_USER_STREAM_INFORMATION = record
    UserStreamCount: ULONG;
    UserStreamArray: PMINIDUMP_USER_STREAM;
  end;
  {$EXTERNALSYM _MINIDUMP_USER_STREAM_INFORMATION}
  MINIDUMP_USER_STREAM_INFORMATION = _MINIDUMP_USER_STREAM_INFORMATION;
  {$EXTERNALSYM MINIDUMP_USER_STREAM_INFORMATION}
  TMinidumpUserStreamInformation = MINIDUMP_USER_STREAM_INFORMATION;
  PMinidumpUserStreamInformation = PMINIDUMP_USER_STREAM_INFORMATION;

//
// Callback support.
//

  _MINIDUMP_CALLBACK_TYPE = (
    ModuleCallback,
    ThreadCallback,
    ThreadExCallback,
    IncludeThreadCallback,
    IncludeModuleCallback);
  {$EXTERNALSYM _MINIDUMP_CALLBACK_TYPE}
  MINIDUMP_CALLBACK_TYPE = _MINIDUMP_CALLBACK_TYPE;
  {$EXTERNALSYM MINIDUMP_CALLBACK_TYPE}
  TMinidumpCallbackType = MINIDUMP_CALLBACK_TYPE;

  PMINIDUMP_THREAD_CALLBACK = ^MINIDUMP_THREAD_CALLBACK;
  {$EXTERNALSYM PMINIDUMP_THREAD_CALLBACK}
  _MINIDUMP_THREAD_CALLBACK = record
    ThreadId: ULONG;
    ThreadHandle: HANDLE;
    Context: CONTEXT;
    SizeOfContext: ULONG;
    StackBase: ULONG64;
    StackEnd: ULONG64;
  end;
  {$EXTERNALSYM _MINIDUMP_THREAD_CALLBACK}
  MINIDUMP_THREAD_CALLBACK = _MINIDUMP_THREAD_CALLBACK;
  {$EXTERNALSYM MINIDUMP_THREAD_CALLBACK}
  TMinidumpThreadCallback = MINIDUMP_THREAD_CALLBACK;
  PMinidumpThreadCallback = PMINIDUMP_THREAD_CALLBACK;

  PMINIDUMP_THREAD_EX_CALLBACK = ^MINIDUMP_THREAD_EX_CALLBACK;
  {$EXTERNALSYM PMINIDUMP_THREAD_EX_CALLBACK}
  _MINIDUMP_THREAD_EX_CALLBACK = record
    ThreadId: ULONG;
    ThreadHandle: HANDLE;
    Context: CONTEXT;
    SizeOfContext: ULONG;
    StackBase: ULONG64;
    StackEnd: ULONG64;
    BackingStoreBase: ULONG64;
    BackingStoreEnd: ULONG64;
  end;
  {$EXTERNALSYM _MINIDUMP_THREAD_EX_CALLBACK}
  MINIDUMP_THREAD_EX_CALLBACK = _MINIDUMP_THREAD_EX_CALLBACK;
  {$EXTERNALSYM MINIDUMP_THREAD_EX_CALLBACK}
  TMinidumpThreadExCallback = MINIDUMP_THREAD_EX_CALLBACK;
  PMinidumpThreadExCallback = PMINIDUMP_THREAD_EX_CALLBACK;

  PMINIDUMP_INCLUDE_THREAD_CALLBACK = ^MINIDUMP_INCLUDE_THREAD_CALLBACK;
  {$EXTERNALSYM PMINIDUMP_INCLUDE_THREAD_CALLBACK}
  _MINIDUMP_INCLUDE_THREAD_CALLBACK = record
    ThreadId: ULONG;
  end;
  {$EXTERNALSYM _MINIDUMP_INCLUDE_THREAD_CALLBACK}
  MINIDUMP_INCLUDE_THREAD_CALLBACK = _MINIDUMP_INCLUDE_THREAD_CALLBACK;
  {$EXTERNALSYM MINIDUMP_INCLUDE_THREAD_CALLBACK}
  TMinidumpIncludeThreadCallback = MINIDUMP_INCLUDE_THREAD_CALLBACK;
  PMinidumpIncludeThreadCallback = PMINIDUMP_INCLUDE_THREAD_CALLBACK;

const
  ThreadWriteThread            = $0001;
  {$EXTERNALSYM ThreadWriteThread}
  ThreadWriteStack             = $0002;
  {$EXTERNALSYM ThreadWriteStack}
  ThreadWriteContext           = $0004;
  {$EXTERNALSYM ThreadWriteContext}
  ThreadWriteBackingStore      = $0008;
  {$EXTERNALSYM ThreadWriteBackingStore}
  ThreadWriteInstructionWindow = $0010;
  {$EXTERNALSYM ThreadWriteInstructionWindow}
  ThreadWriteThreadData        = $0020;
  {$EXTERNALSYM ThreadWriteThreadData}

type
  _THREAD_WRITE_FLAGS = DWORD;
  {$EXTERNALSYM _THREAD_WRITE_FLAGS}
  THREAD_WRITE_FLAGS = _THREAD_WRITE_FLAGS;
  {$EXTERNALSYM THREAD_WRITE_FLAGS}
  TThreadWriteFlags = THREAD_WRITE_FLAGS;

type
  PMINIDUMP_MODULE_CALLBACK = ^MINIDUMP_MODULE_CALLBACK;
  {$EXTERNALSYM PMINIDUMP_MODULE_CALLBACK}
  _MINIDUMP_MODULE_CALLBACK = record
    FullPath: PWCHAR;
    BaseOfImage: ULONG64;
    SizeOfImage: ULONG;
    CheckSum: ULONG;
    TimeDateStamp: ULONG;
    VersionInfo: VS_FIXEDFILEINFO;
    CvRecord: PVOID;
    SizeOfCvRecord: ULONG;
    MiscRecord: PVOID;
    SizeOfMiscRecord: ULONG;
  end;
  {$EXTERNALSYM _MINIDUMP_MODULE_CALLBACK}
  MINIDUMP_MODULE_CALLBACK = _MINIDUMP_MODULE_CALLBACK;
  {$EXTERNALSYM MINIDUMP_MODULE_CALLBACK}
  TMinidumpModuleCallback = MINIDUMP_MODULE_CALLBACK;
  PMinidumpModuleCallback = PMINIDUMP_MODULE_CALLBACK;

  PMINIDUMP_INCLUDE_MODULE_CALLBACK = ^MINIDUMP_INCLUDE_MODULE_CALLBACK;
  {$EXTERNALSYM PMINIDUMP_INCLUDE_MODULE_CALLBACK}
  _MINIDUMP_INCLUDE_MODULE_CALLBACK = record
    BaseOfImage: ULONG64;
  end;
  {$EXTERNALSYM _MINIDUMP_INCLUDE_MODULE_CALLBACK}
  MINIDUMP_INCLUDE_MODULE_CALLBACK = _MINIDUMP_INCLUDE_MODULE_CALLBACK;
  {$EXTERNALSYM MINIDUMP_INCLUDE_MODULE_CALLBACK}
  TMinidumpIncludeModuleCallback = MINIDUMP_INCLUDE_MODULE_CALLBACK;
  PMinidumpIncludeModuleCallback = PMINIDUMP_INCLUDE_MODULE_CALLBACK;

const
  ModuleWriteModule        = $0001;
  {$EXTERNALSYM ModuleWriteModule}
  ModuleWriteDataSeg       = $0002;
  {$EXTERNALSYM ModuleWriteDataSeg}
  ModuleWriteMiscRecord    = $0004;
  {$EXTERNALSYM ModuleWriteMiscRecord}
  ModuleWriteCvRecord      = $0008;
  {$EXTERNALSYM ModuleWriteCvRecord}
  ModuleReferencedByMemory = $0010;
  {$EXTERNALSYM ModuleReferencedByMemory}

type
  _MODULE_WRITE_FLAGS = DWORD;
  {$EXTERNALSYM _MODULE_WRITE_FLAGS}
  MODULE_WRITE_FLAGS = _MODULE_WRITE_FLAGS;
  {$EXTERNALSYM MODULE_WRITE_FLAGS}
  TModuleWriteFlags = MODULE_WRITE_FLAGS;

  _MINIDUMP_CALLBACK_INPUT = record
    ProcessId: ULONG;
    ProcessHandle: HANDLE;
    CallbackType: ULONG;
    case Integer of
      0: (Thread: MINIDUMP_THREAD_CALLBACK);
      1: (ThreadEx: MINIDUMP_THREAD_EX_CALLBACK);
      2: (Module: MINIDUMP_MODULE_CALLBACK);
      3: (IncludeThread: MINIDUMP_INCLUDE_THREAD_CALLBACK);
      4: (IncludeModule: MINIDUMP_INCLUDE_MODULE_CALLBACK);
  end;
  {$EXTERNALSYM _MINIDUMP_CALLBACK_INPUT}
  MINIDUMP_CALLBACK_INPUT = _MINIDUMP_CALLBACK_INPUT;
  {$EXTERNALSYM MINIDUMP_CALLBACK_INPUT}
  PMINIDUMP_CALLBACK_INPUT = ^MINIDUMP_CALLBACK_INPUT;
  {$EXTERNALSYM PMINIDUMP_CALLBACK_INPUT}
  TminidumpCallbackInput = MINIDUMP_CALLBACK_INPUT;

  PMINIDUMP_CALLBACK_OUTPUT = ^MINIDUMP_CALLBACK_OUTPUT;
  {$EXTERNALSYM PMINIDUMP_CALLBACK_OUTPUT}
  _MINIDUMP_CALLBACK_OUTPUT = record
    case Integer of
      0: (ModuleWriteFlags: ULONG);
      1: (ThreadWriteFlags: ULONG);
  end;
  {$EXTERNALSYM _MINIDUMP_CALLBACK_OUTPUT}
  MINIDUMP_CALLBACK_OUTPUT = _MINIDUMP_CALLBACK_OUTPUT;
  {$EXTERNALSYM MINIDUMP_CALLBACK_OUTPUT}
  TMinidumpCallbackOutput = MINIDUMP_CALLBACK_OUTPUT;
  PMinidumpCallbackOutput = PMINIDUMP_CALLBACK_OUTPUT;

//
// A normal minidump contains just the information
// necessary to capture stack traces for all of the
// existing threads in a process.
//
// A minidump with data segments includes all of the data
// sections from loaded modules in order to capture
// global variable contents.  This can make the dump much
// larger if many modules have global data.
//
// A minidump with full memory includes all of the accessible
// memory in the process and can be very large.  A minidump
// with full memory always has the raw memory data at the end
// of the dump so that the initial structures in the dump can
// be mapped directly without having to include the raw
// memory information.
//
// Stack and backing store memory can be filtered to remove
// data unnecessary for stack walking.  This can improve
// compression of stacks and also deletes data that may
// be private and should not be stored in a dump.
// Memory can also be scanned to see what modules are
// referenced by stack and backing store memory to allow
// omission of other modules to reduce dump size.
// In either of these modes the ModuleReferencedByMemory flag
// is set for all modules referenced before the base
// module callbacks occur.
//
// On some operating systems a list of modules that were
// recently unloaded is kept in addition to the currently
// loaded module list.  This information can be saved in
// the dump if desired.
//
// Stack and backing store memory can be scanned for referenced
// pages in order to pick up data referenced by locals or other
// stack memory.  This can increase the size of a dump significantly.
//
// Module paths may contain undesired information such as user names
// or other important directory names so they can be stripped.  This
// option reduces the ability to locate the proper image later
// and should only be used in certain situations.
//
// Complete operating system per-process and per-thread information can
// be gathered and stored in the dump.
//
// The virtual address space can be scanned for various types
// of memory to be included in the dump.
//

const
  MiniDumpNormal         = $0000;
  {$EXTERNALSYM MiniDumpNormal}
  MiniDumpWithDataSegs   = $0001;
  {$EXTERNALSYM MiniDumpWithDataSegs}
  MiniDumpWithFullMemory = $0002;
  {$EXTERNALSYM MiniDumpWithFullMemory}
  MiniDumpWithHandleData = $0004;
  {$EXTERNALSYM MiniDumpWithHandleData}
  MiniDumpFilterMemory   = $0008;
  {$EXTERNALSYM MiniDumpFilterMemory}
  MiniDumpScanMemory     = $0010;
  {$EXTERNALSYM MiniDumpScanMemory}
  MiniDumpWithUnloadedModules            = $0020;
  {$EXTERNALSYM MiniDumpWithUnloadedModules}
  MiniDumpWithIndirectlyReferencedMemory = $0040;
  {$EXTERNALSYM MiniDumpWithIndirectlyReferencedMemory}
  MiniDumpFilterModulePaths              = $0080;
  {$EXTERNALSYM MiniDumpFilterModulePaths}
  MiniDumpWithProcessThreadData          = $0100;
  {$EXTERNALSYM MiniDumpWithProcessThreadData}
  MiniDumpWithPrivateReadWriteMemory     = $0200;
  {$EXTERNALSYM MiniDumpWithPrivateReadWriteMemory}

type
  _MINIDUMP_TYPE = DWORD;
  {$EXTERNALSYM _MINIDUMP_TYPE}
  MINIDUMP_TYPE = _MINIDUMP_TYPE;
  {$EXTERNALSYM MINIDUMP_TYPE}
  TMinidumpType = MINIDUMP_TYPE;

//
// The minidump callback should modify the FieldsToWrite parameter to reflect
// what portions of the specified thread or module should be written to the
// file.
//

  MINIDUMP_CALLBACK_ROUTINE = function (CallbackParam: PVOID; CallbackInput: PMINIDUMP_CALLBACK_INPUT;
    CallbackOutput: PMINIDUMP_CALLBACK_OUTPUT): BOOL; stdcall;
  {$EXTERNALSYM MINIDUMP_CALLBACK_ROUTINE}
  TMinidumpCallbackRoutine = MINIDUMP_CALLBACK_ROUTINE;

  PMINIDUMP_CALLBACK_INFORMATION = ^MINIDUMP_CALLBACK_INFORMATION;
  {$EXTERNALSYM PMINIDUMP_CALLBACK_INFORMATION}
  _MINIDUMP_CALLBACK_INFORMATION = record
    CallbackRoutine: MINIDUMP_CALLBACK_ROUTINE;
    CallbackParam: PVOID;
  end;
  {$EXTERNALSYM _MINIDUMP_CALLBACK_INFORMATION}
  MINIDUMP_CALLBACK_INFORMATION = _MINIDUMP_CALLBACK_INFORMATION;
  {$EXTERNALSYM MINIDUMP_CALLBACK_INFORMATION}
  TMinidumpCallbackInformation = MINIDUMP_CALLBACK_INFORMATION;
  PMinidumpCallbackInformation = PMINIDUMP_CALLBACK_INFORMATION;

//++
//
// PVOID
// RVA_TO_ADDR(
//     PVOID Mapping,
//     ULONG Rva
//     )
//
// Routine Description:
//
//     Map an RVA that is contained within a mapped file to it's associated
//     flat address.
//
// Arguments:
//
//     Mapping - Base address of mapped file containing the RVA.
//
//     Rva - An Rva to fixup.
//
// Return Values:
//
//     A pointer to the desired data.
//
//--

function RVA_TO_ADDR(Mapping, Rva: Pointer): Pointer;
{$EXTERNALSYM RVA_TO_ADDR}

function MiniDumpWriteDump(hProcess: HANDLE; ProcessId: DWORD; hFile: HANDLE; DumpType: MINIDUMP_TYPE; ExceptionParam: PMINIDUMP_EXCEPTION_INFORMATION; UserStreamParam: PMINIDUMP_USER_STREAM_INFORMATION; CallbackParam: PMINIDUMP_CALLBACK_INFORMATION): BOOL; stdcall;
{$EXTERNALSYM MiniDumpWriteDump}

function MiniDumpReadDumpStream(BaseOfDump: PVOID; StreamNumber: ULONG; var Dir: PMINIDUMP_DIRECTORY; var StreamPointer: PVOID; var StreamSize: ULONG): BOOL; stdcall;
{$EXTERNALSYM MiniDumpReadDumpStream}

implementation

procedure Address32To64(a32: LPADDRESS; a64: LPADDRESS64);
begin
  a64^.Offset := {ULONG64(LONG64(LONG(}a32^.Offset{)))};
  a64^.Segment := a32^.Segment;
  a64^.Mode := a32^.Mode;
end;

procedure Address64To32(a64: LPADDRESS64; a32: LPADDRESS);
begin
  a32^.Offset := ULONG(a64^.Offset);
  a32^.Segment := a64^.Segment;
  a32^.Mode := a64^.Mode;
end;

procedure KdHelp32To64(p32: PKDHELP; p64: PKDHELP64);
begin
  p64^.Thread := p32^.Thread;
  p64^.ThCallbackStack := p32^.ThCallbackStack;
  p64^.NextCallback := p32^.NextCallback;
  p64^.FramePointer := p32^.FramePointer;
  p64^.KiCallUserMode := p32^.KiCallUserMode;
  p64^.KeUserCallbackDispatcher := p32^.KeUserCallbackDispatcher;
  p64^.SystemRangeStart := p32^.SystemRangeStart;
end;

const
  ImageHlpLib = 'imagehlp.dll';


{$IFDEF DYNAMIC_LINK}
var
  _BindImage: Pointer;

function BindImage;
begin
  GetProcedureAddress(_BindImage, ImageHlpLib, 'BindImage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BindImage]
  end;
end;
{$ELSE}
function BindImage; external ImageHlpLib name 'BindImage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _BindImageEx: Pointer;

function BindImageEx;
begin
  GetProcedureAddress(_BindImageEx, ImageHlpLib, 'BindImageEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BindImageEx]
  end;
end;
{$ELSE}
function BindImageEx; external ImageHlpLib name 'BindImageEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ReBaseImage: Pointer;

function ReBaseImage;
begin
  GetProcedureAddress(_ReBaseImage, ImageHlpLib, 'ReBaseImage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ReBaseImage]
  end;
end;
{$ELSE}
function ReBaseImage; external ImageHlpLib name 'ReBaseImage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ReBaseImage64: Pointer;

function ReBaseImage64;
begin
  GetProcedureAddress(_ReBaseImage64, ImageHlpLib, 'ReBaseImage64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ReBaseImage64]
  end;
end;
{$ELSE}
function ReBaseImage64; external ImageHlpLib name 'ReBaseImage64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CheckSumMappedFile: Pointer;

function CheckSumMappedFile;
begin
  GetProcedureAddress(_CheckSumMappedFile, ImageHlpLib, 'CheckSumMappedFile');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CheckSumMappedFile]
  end;
end;
{$ELSE}
function CheckSumMappedFile; external ImageHlpLib name 'CheckSumMappedFile';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MapFileAndCheckSumA: Pointer;

function MapFileAndCheckSumA;
begin
  GetProcedureAddress(_MapFileAndCheckSumA, ImageHlpLib, 'MapFileAndCheckSumA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MapFileAndCheckSumA]
  end;
end;
{$ELSE}
function MapFileAndCheckSumA; external ImageHlpLib name 'MapFileAndCheckSumA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MapFileAndCheckSumW: Pointer;

function MapFileAndCheckSumW;
begin
  GetProcedureAddress(_MapFileAndCheckSumW, ImageHlpLib, 'MapFileAndCheckSumW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MapFileAndCheckSumW]
  end;
end;
{$ELSE}
function MapFileAndCheckSumW; external ImageHlpLib name 'MapFileAndCheckSumW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MapFileAndCheckSum: Pointer;

function MapFileAndCheckSum;
begin
  GetProcedureAddress(_MapFileAndCheckSum, ImageHlpLib, 'MapFileAndCheckSumW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MapFileAndCheckSum]
  end;
end;
{$ELSE}
function MapFileAndCheckSum; external ImageHlpLib name 'MapFileAndCheckSumW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MapFileAndCheckSum: Pointer;

function MapFileAndCheckSum;
begin
  GetProcedureAddress(_MapFileAndCheckSum, ImageHlpLib, 'MapFileAndCheckSumA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MapFileAndCheckSum]
  end;
end;
{$ELSE}
function MapFileAndCheckSum; external ImageHlpLib name 'MapFileAndCheckSumA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetImageConfigInformation: Pointer;

function GetImageConfigInformation;
begin
  GetProcedureAddress(_GetImageConfigInformation, ImageHlpLib, 'GetImageConfigInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetImageConfigInformation]
  end;
end;
{$ELSE}
function GetImageConfigInformation; external ImageHlpLib name 'GetImageConfigInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetImageUnusedHeaderBytes: Pointer;

function GetImageUnusedHeaderBytes;
begin
  GetProcedureAddress(_GetImageUnusedHeaderBytes, ImageHlpLib, 'GetImageUnusedHeaderBytes');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetImageUnusedHeaderBytes]
  end;
end;
{$ELSE}
function GetImageUnusedHeaderBytes; external ImageHlpLib name 'GetImageUnusedHeaderBytes';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetImageConfigInformation: Pointer;

function SetImageConfigInformation;
begin
  GetProcedureAddress(_SetImageConfigInformation, ImageHlpLib, 'SetImageConfigInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetImageConfigInformation]
  end;
end;
{$ELSE}
function SetImageConfigInformation; external ImageHlpLib name 'SetImageConfigInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImageGetDigestStream: Pointer;

function ImageGetDigestStream;
begin
  GetProcedureAddress(_ImageGetDigestStream, ImageHlpLib, 'ImageGetDigestStream');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImageGetDigestStream]
  end;
end;
{$ELSE}
function ImageGetDigestStream; external ImageHlpLib name 'ImageGetDigestStream';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImageAddCertificate: Pointer;

function ImageAddCertificate;
begin
  GetProcedureAddress(_ImageAddCertificate, ImageHlpLib, 'ImageAddCertificate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImageAddCertificate]
  end;
end;
{$ELSE}
function ImageAddCertificate; external ImageHlpLib name 'ImageAddCertificate';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImageRemoveCertificate: Pointer;

function ImageRemoveCertificate;
begin
  GetProcedureAddress(_ImageRemoveCertificate, ImageHlpLib, 'ImageRemoveCertificate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImageRemoveCertificate]
  end;
end;
{$ELSE}
function ImageRemoveCertificate; external ImageHlpLib name 'ImageRemoveCertificate';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImageEnumerateCertificates: Pointer;

function ImageEnumerateCertificates;
begin
  GetProcedureAddress(_ImageEnumerateCertificates, ImageHlpLib, 'ImageEnumerateCertificates');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImageEnumerateCertificates]
  end;
end;
{$ELSE}
function ImageEnumerateCertificates; external ImageHlpLib name 'ImageEnumerateCertificates';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImageGetCertificateData: Pointer;

function ImageGetCertificateData;
begin
  GetProcedureAddress(_ImageGetCertificateData, ImageHlpLib, 'ImageGetCertificateData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImageGetCertificateData]
  end;
end;
{$ELSE}
function ImageGetCertificateData; external ImageHlpLib name 'ImageGetCertificateData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImageGetCertificateHeader: Pointer;

function ImageGetCertificateHeader;
begin
  GetProcedureAddress(_ImageGetCertificateHeader, ImageHlpLib, 'ImageGetCertificateHeader');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImageGetCertificateHeader]
  end;
end;
{$ELSE}
function ImageGetCertificateHeader; external ImageHlpLib name 'ImageGetCertificateHeader';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImageLoad: Pointer;

function ImageLoad;
begin
  GetProcedureAddress(_ImageLoad, ImageHlpLib, 'ImageLoad');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImageLoad]
  end;
end;
{$ELSE}
function ImageLoad; external ImageHlpLib name 'ImageLoad';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImageUnload: Pointer;

function ImageUnload;
begin
  GetProcedureAddress(_ImageUnload, ImageHlpLib, 'ImageUnload');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImageUnload]
  end;
end;
{$ELSE}
function ImageUnload; external ImageHlpLib name 'ImageUnload';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MapAndLoad: Pointer;

function MapAndLoad;
begin
  GetProcedureAddress(_MapAndLoad, ImageHlpLib, 'MapAndLoad');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MapAndLoad]
  end;
end;
{$ELSE}
function MapAndLoad; external ImageHlpLib name 'MapAndLoad';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UnMapAndLoad: Pointer;

function UnMapAndLoad;
begin
  GetProcedureAddress(_UnMapAndLoad, ImageHlpLib, 'UnMapAndLoad');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UnMapAndLoad]
  end;
end;
{$ELSE}
function UnMapAndLoad; external ImageHlpLib name 'UnMapAndLoad';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TouchFileTimes: Pointer;

function TouchFileTimes;
begin
  GetProcedureAddress(_TouchFileTimes, ImageHlpLib, 'TouchFileTimes');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TouchFileTimes]
  end;
end;
{$ELSE}
function TouchFileTimes; external ImageHlpLib name 'TouchFileTimes';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SplitSymbols: Pointer;

function SplitSymbols;
begin
  GetProcedureAddress(_SplitSymbols, ImageHlpLib, 'SplitSymbols');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SplitSymbols]
  end;
end;
{$ELSE}
function SplitSymbols; external ImageHlpLib name 'SplitSymbols';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UpdateDebugInfoFile: Pointer;

function UpdateDebugInfoFile;
begin
  GetProcedureAddress(_UpdateDebugInfoFile, ImageHlpLib, 'UpdateDebugInfoFile');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UpdateDebugInfoFile]
  end;
end;
{$ELSE}
function UpdateDebugInfoFile; external ImageHlpLib name 'UpdateDebugInfoFile';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UpdateDebugInfoFileEx: Pointer;

function UpdateDebugInfoFileEx;
begin
  GetProcedureAddress(_UpdateDebugInfoFileEx, ImageHlpLib, 'UpdateDebugInfoFileEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UpdateDebugInfoFileEx]
  end;
end;
{$ELSE}
function UpdateDebugInfoFileEx; external ImageHlpLib name 'UpdateDebugInfoFileEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _FindDebugInfoFile: Pointer;

function FindDebugInfoFile;
begin
  GetProcedureAddress(_FindDebugInfoFile, ImageHlpLib, 'FindDebugInfoFile');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FindDebugInfoFile]
  end;
end;
{$ELSE}
function FindDebugInfoFile; external ImageHlpLib name 'FindDebugInfoFile';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _FindDebugInfoFileEx: Pointer;

function FindDebugInfoFileEx;
begin
  GetProcedureAddress(_FindDebugInfoFileEx, ImageHlpLib, 'FindDebugInfoFileEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FindDebugInfoFileEx]
  end;
end;
{$ELSE}
function FindDebugInfoFileEx; external ImageHlpLib name 'FindDebugInfoFileEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymFindFileInPath: Pointer;

function SymFindFileInPath;
begin
  GetProcedureAddress(_SymFindFileInPath, ImageHlpLib, 'SymFindFileInPath');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymFindFileInPath]
  end;
end;
{$ELSE}
function SymFindFileInPath; external ImageHlpLib name 'SymFindFileInPath';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _FindExecutableImage: Pointer;

function FindExecutableImage;
begin
  GetProcedureAddress(_FindExecutableImage, ImageHlpLib, 'FindExecutableImage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FindExecutableImage]
  end;
end;
{$ELSE}
function FindExecutableImage; external ImageHlpLib name 'FindExecutableImage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _FindExecutableImageEx: Pointer;

function FindExecutableImageEx;
begin
  GetProcedureAddress(_FindExecutableImageEx, ImageHlpLib, 'FindExecutableImageEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FindExecutableImageEx]
  end;
end;
{$ELSE}
function FindExecutableImageEx; external ImageHlpLib name 'FindExecutableImageEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImageNtHeader: Pointer;

function ImageNtHeader;
begin
  GetProcedureAddress(_ImageNtHeader, ImageHlpLib, 'ImageNtHeader');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImageNtHeader]
  end;
end;
{$ELSE}
function ImageNtHeader; external ImageHlpLib name 'ImageNtHeader';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImageDirectoryEntryToDataEx: Pointer;

function ImageDirectoryEntryToDataEx;
begin
  GetProcedureAddress(_ImageDirectoryEntryToDataEx, ImageHlpLib, 'ImageDirectoryEntryToDataEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImageDirectoryEntryToDataEx]
  end;
end;
{$ELSE}
function ImageDirectoryEntryToDataEx; external ImageHlpLib name 'ImageDirectoryEntryToDataEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImageDirectoryEntryToData: Pointer;

function ImageDirectoryEntryToData;
begin
  GetProcedureAddress(_ImageDirectoryEntryToData, ImageHlpLib, 'ImageDirectoryEntryToData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImageDirectoryEntryToData]
  end;
end;
{$ELSE}
function ImageDirectoryEntryToData; external ImageHlpLib name 'ImageDirectoryEntryToData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImageRvaToSection: Pointer;

function ImageRvaToSection;
begin
  GetProcedureAddress(_ImageRvaToSection, ImageHlpLib, 'ImageRvaToSection');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImageRvaToSection]
  end;
end;
{$ELSE}
function ImageRvaToSection; external ImageHlpLib name 'ImageRvaToSection';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImageRvaToVa: Pointer;

function ImageRvaToVa;
begin
  GetProcedureAddress(_ImageRvaToVa, ImageHlpLib, 'ImageRvaToVa');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImageRvaToVa]
  end;
end;
{$ELSE}
function ImageRvaToVa; external ImageHlpLib name 'ImageRvaToVa';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MapDebugInformation: Pointer;

function MapDebugInformation;
begin
  GetProcedureAddress(_MapDebugInformation, ImageHlpLib, 'MapDebugInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MapDebugInformation]
  end;
end;
{$ELSE}
function MapDebugInformation; external ImageHlpLib name 'MapDebugInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UnmapDebugInformation: Pointer;

function UnmapDebugInformation;
begin
  GetProcedureAddress(_UnmapDebugInformation, ImageHlpLib, 'UnmapDebugInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UnmapDebugInformation]
  end;
end;
{$ELSE}
function UnmapDebugInformation; external ImageHlpLib name 'UnmapDebugInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SearchTreeForFile: Pointer;

function SearchTreeForFile;
begin
  GetProcedureAddress(_SearchTreeForFile, ImageHlpLib, 'SearchTreeForFile');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SearchTreeForFile]
  end;
end;
{$ELSE}
function SearchTreeForFile; external ImageHlpLib name 'SearchTreeForFile';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnumDirTree: Pointer;

function EnumDirTree;
begin
  GetProcedureAddress(_EnumDirTree, ImageHlpLib, 'EnumDirTree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumDirTree]
  end;
end;
{$ELSE}
function EnumDirTree; external ImageHlpLib name 'EnumDirTree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MakeSureDirectoryPathExists: Pointer;

function MakeSureDirectoryPathExists;
begin
  GetProcedureAddress(_MakeSureDirectoryPathExists, ImageHlpLib, 'MakeSureDirectoryPathExists');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MakeSureDirectoryPathExists]
  end;
end;
{$ELSE}
function MakeSureDirectoryPathExists; external ImageHlpLib name 'MakeSureDirectoryPathExists';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UnDecorateSymbolName: Pointer;

function UnDecorateSymbolName;
begin
  GetProcedureAddress(_UnDecorateSymbolName, ImageHlpLib, 'UnDecorateSymbolName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UnDecorateSymbolName]
  end;
end;
{$ELSE}
function UnDecorateSymbolName; external ImageHlpLib name 'UnDecorateSymbolName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _StackWalk64: Pointer;

function StackWalk64;
begin
  GetProcedureAddress(_StackWalk64, ImageHlpLib, 'StackWalk64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_StackWalk64]
  end;
end;
{$ELSE}
function StackWalk64; external ImageHlpLib name 'StackWalk64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _StackWalk: Pointer;

function StackWalk;
begin
  GetProcedureAddress(_StackWalk, ImageHlpLib, 'StackWalk');
  asm
    mov esp, ebp
    pop ebp
    jmp [_StackWalk]
  end;
end;
{$ELSE}
function StackWalk; external ImageHlpLib name 'StackWalk';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImagehlpApiVersion: Pointer;

function ImagehlpApiVersion;
begin
  GetProcedureAddress(_ImagehlpApiVersion, ImageHlpLib, 'ImagehlpApiVersion');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImagehlpApiVersion]
  end;
end;
{$ELSE}
function ImagehlpApiVersion; external ImageHlpLib name 'ImagehlpApiVersion';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImagehlpApiVersionEx: Pointer;

function ImagehlpApiVersionEx;
begin
  GetProcedureAddress(_ImagehlpApiVersionEx, ImageHlpLib, 'ImagehlpApiVersionEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImagehlpApiVersionEx]
  end;
end;
{$ELSE}
function ImagehlpApiVersionEx; external ImageHlpLib name 'ImagehlpApiVersionEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetTimestampForLoadedLibrary: Pointer;

function GetTimestampForLoadedLibrary;
begin
  GetProcedureAddress(_GetTimestampForLoadedLibrary, ImageHlpLib, 'GetTimestampForLoadedLibrary');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTimestampForLoadedLibrary]
  end;
end;
{$ELSE}
function GetTimestampForLoadedLibrary; external ImageHlpLib name 'GetTimestampForLoadedLibrary';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymSetOptions: Pointer;

function SymSetOptions;
begin
  GetProcedureAddress(_SymSetOptions, ImageHlpLib, 'SymSetOptions');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymSetOptions]
  end;
end;
{$ELSE}
function SymSetOptions; external ImageHlpLib name 'SymSetOptions';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetOptions: Pointer;

function SymGetOptions;
begin
  GetProcedureAddress(_SymGetOptions, ImageHlpLib, 'SymGetOptions');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetOptions]
  end;
end;
{$ELSE}
function SymGetOptions; external ImageHlpLib name 'SymGetOptions';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymCleanup: Pointer;

function SymCleanup;
begin
  GetProcedureAddress(_SymCleanup, ImageHlpLib, 'SymCleanup');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymCleanup]
  end;
end;
{$ELSE}
function SymCleanup; external ImageHlpLib name 'SymCleanup';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymMatchString: Pointer;

function SymMatchString;
begin
  GetProcedureAddress(_SymMatchString, ImageHlpLib, 'SymMatchString');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymMatchString]
  end;
end;
{$ELSE}
function SymMatchString; external ImageHlpLib name 'SymMatchString';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymEnumSourceFiles: Pointer;

function SymEnumSourceFiles;
begin
  GetProcedureAddress(_SymEnumSourceFiles, ImageHlpLib, 'SymEnumSourceFiles');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymEnumSourceFiles]
  end;
end;
{$ELSE}
function SymEnumSourceFiles; external ImageHlpLib name 'SymEnumSourceFiles';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymEnumerateModules64: Pointer;

function SymEnumerateModules64;
begin
  GetProcedureAddress(_SymEnumerateModules64, ImageHlpLib, 'SymEnumerateModules64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymEnumerateModules64]
  end;
end;
{$ELSE}
function SymEnumerateModules64; external ImageHlpLib name 'SymEnumerateModules64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymEnumerateModules: Pointer;

function SymEnumerateModules;
begin
  GetProcedureAddress(_SymEnumerateModules, ImageHlpLib, 'SymEnumerateModules');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymEnumerateModules]
  end;
end;
{$ELSE}
function SymEnumerateModules; external ImageHlpLib name 'SymEnumerateModules';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymEnumerateSymbols64: Pointer;

function SymEnumerateSymbols64;
begin
  GetProcedureAddress(_SymEnumerateSymbols64, ImageHlpLib, 'SymEnumerateSymbols64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymEnumerateSymbols64]
  end;
end;
{$ELSE}
function SymEnumerateSymbols64; external ImageHlpLib name 'SymEnumerateSymbols64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymEnumerateSymbolsW64: Pointer;

function SymEnumerateSymbolsW64;
begin
  GetProcedureAddress(_SymEnumerateSymbolsW64, ImageHlpLib, 'SymEnumerateSymbolsW64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymEnumerateSymbolsW64]
  end;
end;
{$ELSE}
function SymEnumerateSymbolsW64; external ImageHlpLib name 'SymEnumerateSymbolsW64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymEnumerateSymbols: Pointer;

function SymEnumerateSymbols;
begin
  GetProcedureAddress(_SymEnumerateSymbols, ImageHlpLib, 'SymEnumerateSymbols');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymEnumerateSymbols]
  end;
end;
{$ELSE}
function SymEnumerateSymbols; external ImageHlpLib name 'SymEnumerateSymbols';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymEnumerateSymbolsW: Pointer;

function SymEnumerateSymbolsW;
begin
  GetProcedureAddress(_SymEnumerateSymbolsW, ImageHlpLib, 'SymEnumerateSymbolsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymEnumerateSymbolsW]
  end;
end;
{$ELSE}
function SymEnumerateSymbolsW; external ImageHlpLib name 'SymEnumerateSymbolsW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnumerateLoadedModules64: Pointer;

function EnumerateLoadedModules64;
begin
  GetProcedureAddress(_EnumerateLoadedModules64, ImageHlpLib, 'EnumerateLoadedModules64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumerateLoadedModules64]
  end;
end;
{$ELSE}
function EnumerateLoadedModules64; external ImageHlpLib name 'EnumerateLoadedModules64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnumerateLoadedModules: Pointer;

function EnumerateLoadedModules;
begin
  GetProcedureAddress(_EnumerateLoadedModules, ImageHlpLib, 'EnumerateLoadedModules');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumerateLoadedModules]
  end;
end;
{$ELSE}
function EnumerateLoadedModules; external ImageHlpLib name 'EnumerateLoadedModules';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymFunctionTableAccess64: Pointer;

function SymFunctionTableAccess64;
begin
  GetProcedureAddress(_SymFunctionTableAccess64, ImageHlpLib, 'SymFunctionTableAccess64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymFunctionTableAccess64]
  end;
end;
{$ELSE}
function SymFunctionTableAccess64; external ImageHlpLib name 'SymFunctionTableAccess64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymFunctionTableAccess: Pointer;

function SymFunctionTableAccess;
begin
  GetProcedureAddress(_SymFunctionTableAccess, ImageHlpLib, 'SymFunctionTableAccess');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymFunctionTableAccess]
  end;
end;
{$ELSE}
function SymFunctionTableAccess; external ImageHlpLib name 'SymFunctionTableAccess';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetModuleInfo64: Pointer;

function SymGetModuleInfo64;
begin
  GetProcedureAddress(_SymGetModuleInfo64, ImageHlpLib, 'SymGetModuleInfo64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetModuleInfo64]
  end;
end;
{$ELSE}
function SymGetModuleInfo64; external ImageHlpLib name 'SymGetModuleInfo64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetModuleInfoW64: Pointer;

function SymGetModuleInfoW64;
begin
  GetProcedureAddress(_SymGetModuleInfoW64, ImageHlpLib, 'SymGetModuleInfoW64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetModuleInfoW64]
  end;
end;
{$ELSE}
function SymGetModuleInfoW64; external ImageHlpLib name 'SymGetModuleInfoW64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetModuleInfo: Pointer;

function SymGetModuleInfo;
begin
  GetProcedureAddress(_SymGetModuleInfo, ImageHlpLib, 'SymGetModuleInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetModuleInfo]
  end;
end;
{$ELSE}
function SymGetModuleInfo; external ImageHlpLib name 'SymGetModuleInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetModuleInfoW: Pointer;

function SymGetModuleInfoW;
begin
  GetProcedureAddress(_SymGetModuleInfoW, ImageHlpLib, 'SymGetModuleInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetModuleInfoW]
  end;
end;
{$ELSE}
function SymGetModuleInfoW; external ImageHlpLib name 'SymGetModuleInfoW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetModuleBase64: Pointer;

function SymGetModuleBase64;
begin
  GetProcedureAddress(_SymGetModuleBase64, ImageHlpLib, 'SymGetModuleBase64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetModuleBase64]
  end;
end;
{$ELSE}
function SymGetModuleBase64; external ImageHlpLib name 'SymGetModuleBase64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetModuleBase: Pointer;

function SymGetModuleBase;
begin
  GetProcedureAddress(_SymGetModuleBase, ImageHlpLib, 'SymGetModuleBase');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetModuleBase]
  end;
end;
{$ELSE}
function SymGetModuleBase; external ImageHlpLib name 'SymGetModuleBase';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetSymNext64: Pointer;

function SymGetSymNext64;
begin
  GetProcedureAddress(_SymGetSymNext64, ImageHlpLib, 'SymGetSymNext64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetSymNext64]
  end;
end;
{$ELSE}
function SymGetSymNext64; external ImageHlpLib name 'SymGetSymNext64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetSymNext: Pointer;

function SymGetSymNext;
begin
  GetProcedureAddress(_SymGetSymNext, ImageHlpLib, 'SymGetSymNext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetSymNext]
  end;
end;
{$ELSE}
function SymGetSymNext; external ImageHlpLib name 'SymGetSymNext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetSymPrev64: Pointer;

function SymGetSymPrev64;
begin
  GetProcedureAddress(_SymGetSymPrev64, ImageHlpLib, 'SymGetSymPrev64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetSymPrev64]
  end;
end;
{$ELSE}
function SymGetSymPrev64; external ImageHlpLib name 'SymGetSymPrev64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetSymPrev: Pointer;

function SymGetSymPrev;
begin
  GetProcedureAddress(_SymGetSymPrev, ImageHlpLib, 'SymGetSymPrev');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetSymPrev]
  end;
end;
{$ELSE}
function SymGetSymPrev; external ImageHlpLib name 'SymGetSymPrev';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetLineFromAddr64: Pointer;

function SymGetLineFromAddr64;
begin
  GetProcedureAddress(_SymGetLineFromAddr64, ImageHlpLib, 'SymGetLineFromAddr64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetLineFromAddr64]
  end;
end;
{$ELSE}
function SymGetLineFromAddr64; external ImageHlpLib name 'SymGetLineFromAddr64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetLineFromAddr: Pointer;

function SymGetLineFromAddr;
begin
  GetProcedureAddress(_SymGetLineFromAddr, ImageHlpLib, 'SymGetLineFromAddr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetLineFromAddr]
  end;
end;
{$ELSE}
function SymGetLineFromAddr; external ImageHlpLib name 'SymGetLineFromAddr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetLineFromName64: Pointer;

function SymGetLineFromName64;
begin
  GetProcedureAddress(_SymGetLineFromName64, ImageHlpLib, 'SymGetLineFromName64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetLineFromName64]
  end;
end;
{$ELSE}
function SymGetLineFromName64; external ImageHlpLib name 'SymGetLineFromName64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetLineFromName: Pointer;

function SymGetLineFromName;
begin
  GetProcedureAddress(_SymGetLineFromName, ImageHlpLib, 'SymGetLineFromName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetLineFromName]
  end;
end;
{$ELSE}
function SymGetLineFromName; external ImageHlpLib name 'SymGetLineFromName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetLineNext64: Pointer;

function SymGetLineNext64;
begin
  GetProcedureAddress(_SymGetLineNext64, ImageHlpLib, 'SymGetLineNext64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetLineNext64]
  end;
end;
{$ELSE}
function SymGetLineNext64; external ImageHlpLib name 'SymGetLineNext64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetLineNext: Pointer;

function SymGetLineNext;
begin
  GetProcedureAddress(_SymGetLineNext, ImageHlpLib, 'SymGetLineNext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetLineNext]
  end;
end;
{$ELSE}
function SymGetLineNext; external ImageHlpLib name 'SymGetLineNext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetLinePrev64: Pointer;

function SymGetLinePrev64;
begin
  GetProcedureAddress(_SymGetLinePrev64, ImageHlpLib, 'SymGetLinePrev64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetLinePrev64]
  end;
end;
{$ELSE}
function SymGetLinePrev64; external ImageHlpLib name 'SymGetLinePrev64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetLinePrev: Pointer;

function SymGetLinePrev;
begin
  GetProcedureAddress(_SymGetLinePrev, ImageHlpLib, 'SymGetLinePrev');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetLinePrev]
  end;
end;
{$ELSE}
function SymGetLinePrev; external ImageHlpLib name 'SymGetLinePrev';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymMatchFileName: Pointer;

function SymMatchFileName;
begin
  GetProcedureAddress(_SymMatchFileName, ImageHlpLib, 'SymMatchFileName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymMatchFileName]
  end;
end;
{$ELSE}
function SymMatchFileName; external ImageHlpLib name 'SymMatchFileName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymInitialize: Pointer;

function SymInitialize;
begin
  GetProcedureAddress(_SymInitialize, ImageHlpLib, 'SymInitialize');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymInitialize]
  end;
end;
{$ELSE}
function SymInitialize; external ImageHlpLib name 'SymInitialize';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetSearchPath: Pointer;

function SymGetSearchPath;
begin
  GetProcedureAddress(_SymGetSearchPath, ImageHlpLib, 'SymGetSearchPath');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetSearchPath]
  end;
end;
{$ELSE}
function SymGetSearchPath; external ImageHlpLib name 'SymGetSearchPath';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymSetSearchPath: Pointer;

function SymSetSearchPath;
begin
  GetProcedureAddress(_SymSetSearchPath, ImageHlpLib, 'SymSetSearchPath');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymSetSearchPath]
  end;
end;
{$ELSE}
function SymSetSearchPath; external ImageHlpLib name 'SymSetSearchPath';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymLoadModuleEx: Pointer;

function SymLoadModuleEx;
begin
  GetProcedureAddress(_SymLoadModuleEx, ImageHlpLib, 'SymLoadModuleEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymLoadModuleEx]
  end;
end;
{$ELSE}
function SymLoadModuleEx; external ImageHlpLib name 'SymLoadModuleEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymLoadModule64: Pointer;

function SymLoadModule64;
begin
  GetProcedureAddress(_SymLoadModule64, ImageHlpLib, 'SymLoadModule64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymLoadModule64]
  end;
end;
{$ELSE}
function SymLoadModule64; external ImageHlpLib name 'SymLoadModule64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymLoadModule: Pointer;

function SymLoadModule;
begin
  GetProcedureAddress(_SymLoadModule, ImageHlpLib, 'SymLoadModule');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymLoadModule]
  end;
end;
{$ELSE}
function SymLoadModule; external ImageHlpLib name 'SymLoadModule';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymUnloadModule64: Pointer;

function SymUnloadModule64;
begin
  GetProcedureAddress(_SymUnloadModule64, ImageHlpLib, 'SymUnloadModule64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymUnloadModule64]
  end;
end;
{$ELSE}
function SymUnloadModule64; external ImageHlpLib name 'SymUnloadModule64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymUnloadModule: Pointer;

function SymUnloadModule;
begin
  GetProcedureAddress(_SymUnloadModule, ImageHlpLib, 'SymUnloadModule');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymUnloadModule]
  end;
end;
{$ELSE}
function SymUnloadModule; external ImageHlpLib name 'SymUnloadModule';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymUnDName64: Pointer;

function SymUnDName64;
begin
  GetProcedureAddress(_SymUnDName64, ImageHlpLib, 'SymUnDName64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymUnDName64]
  end;
end;
{$ELSE}
function SymUnDName64; external ImageHlpLib name 'SymUnDName64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymUnDName: Pointer;

function SymUnDName;
begin
  GetProcedureAddress(_SymUnDName, ImageHlpLib, 'SymUnDName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymUnDName]
  end;
end;
{$ELSE}
function SymUnDName; external ImageHlpLib name 'SymUnDName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymRegisterCallback64: Pointer;

function SymRegisterCallback64;
begin
  GetProcedureAddress(_SymRegisterCallback64, ImageHlpLib, 'SymRegisterCallback64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymRegisterCallback64]
  end;
end;
{$ELSE}
function SymRegisterCallback64; external ImageHlpLib name 'SymRegisterCallback64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymRegFuncEntryCallback64: Pointer;

function SymRegisterFunctionEntryCallback64;
begin
  GetProcedureAddress(_SymRegFuncEntryCallback64, ImageHlpLib, 'SymRegisterFunctionEntryCallback64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymRegFuncEntryCallback64]
  end;
end;
{$ELSE}
function SymRegisterFunctionEntryCallback64; external ImageHlpLib name 'SymRegisterFunctionEntryCallback64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymRegisterCallback: Pointer;

function SymRegisterCallback;
begin
  GetProcedureAddress(_SymRegisterCallback, ImageHlpLib, 'SymRegisterCallback');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymRegisterCallback]
  end;
end;
{$ELSE}
function SymRegisterCallback; external ImageHlpLib name 'SymRegisterCallback';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymRegisterFuncEntryCallback: Pointer;

function SymRegisterFunctionEntryCallback;
begin
  GetProcedureAddress(_SymRegisterFuncEntryCallback, ImageHlpLib, 'SymRegisterFunctionEntryCallback');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymRegisterFuncEntryCallback]
  end;
end;
{$ELSE}
function SymRegisterFunctionEntryCallback; external ImageHlpLib name 'SymRegisterFunctionEntryCallback';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _SymSetContext: Pointer;

function SymSetContext;
begin
  GetProcedureAddress(_SymSetContext, ImageHlpLib, 'SymSetContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymSetContext]
  end;
end;
{$ELSE}
function SymSetContext; external ImageHlpLib name 'SymSetContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymFromAddr: Pointer;

function SymFromAddr;
begin
  GetProcedureAddress(_SymFromAddr, ImageHlpLib, 'SymFromAddr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymFromAddr]
  end;
end;
{$ELSE}
function SymFromAddr; external ImageHlpLib name 'SymFromAddr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymFromName: Pointer;

function SymFromName;
begin
  GetProcedureAddress(_SymFromName, ImageHlpLib, 'SymFromName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymFromName]
  end;
end;
{$ELSE}
function SymFromName; external ImageHlpLib name 'SymFromName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymEnumSymbolsForAddr: Pointer;

function SymEnumSymbolsForAddr;
begin
  GetProcedureAddress(_SymEnumSymbolsForAddr, ImageHlpLib, 'SymEnumSymbolsForAddr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymEnumSymbolsForAddr]
  end;
end;
{$ELSE}
function SymEnumSymbolsForAddr; external ImageHlpLib name 'SymEnumSymbolsForAddr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymEnumSymbols: Pointer;

function SymEnumSymbols;
begin
  GetProcedureAddress(_SymEnumSymbols, ImageHlpLib, 'SymEnumSymbols');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymEnumSymbols]
  end;
end;
{$ELSE}
function SymEnumSymbols; external ImageHlpLib name 'SymEnumSymbols';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetTypeInfo: Pointer;

function SymGetTypeInfo;
begin
  GetProcedureAddress(_SymGetTypeInfo, ImageHlpLib, 'SymGetTypeInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetTypeInfo]
  end;
end;
{$ELSE}
function SymGetTypeInfo; external ImageHlpLib name 'SymGetTypeInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymEnumTypes: Pointer;

function SymEnumTypes;
begin
  GetProcedureAddress(_SymEnumTypes, ImageHlpLib, 'SymEnumTypes');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymEnumTypes]
  end;
end;
{$ELSE}
function SymEnumTypes; external ImageHlpLib name 'SymEnumTypes';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetTypeFromName: Pointer;

function SymGetTypeFromName;
begin
  GetProcedureAddress(_SymGetTypeFromName, ImageHlpLib, 'SymGetTypeFromName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetTypeFromName]
  end;
end;
{$ELSE}
function SymGetTypeFromName; external ImageHlpLib name 'SymGetTypeFromName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymAddSymbol: Pointer;

function SymAddSymbol;
begin
  GetProcedureAddress(_SymAddSymbol, ImageHlpLib, 'SymAddSymbol');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymAddSymbol]
  end;
end;
{$ELSE}
function SymAddSymbol; external ImageHlpLib name 'SymAddSymbol';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymDeleteSymbol: Pointer;

function SymDeleteSymbol;
begin
  GetProcedureAddress(_SymDeleteSymbol, ImageHlpLib, 'SymDeleteSymbol');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymDeleteSymbol]
  end;
end;
{$ELSE}
function SymDeleteSymbol; external ImageHlpLib name 'SymDeleteSymbol';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DbgHelpCreateUserDump: Pointer;

function DbgHelpCreateUserDump;
begin
  GetProcedureAddress(_DbgHelpCreateUserDump, ImageHlpLib, 'DbgHelpCreateUserDump');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DbgHelpCreateUserDump]
  end;
end;
{$ELSE}
function DbgHelpCreateUserDump; external ImageHlpLib name 'DbgHelpCreateUserDump';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DbgHelpCreateUserDumpW: Pointer;

function DbgHelpCreateUserDumpW;
begin
  GetProcedureAddress(_DbgHelpCreateUserDumpW, ImageHlpLib, 'DbgHelpCreateUserDumpW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DbgHelpCreateUserDumpW]
  end;
end;
{$ELSE}
function DbgHelpCreateUserDumpW; external ImageHlpLib name 'DbgHelpCreateUserDumpW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetSymFromAddr64: Pointer;

function SymGetSymFromAddr64;
begin
  GetProcedureAddress(_SymGetSymFromAddr64, ImageHlpLib, 'SymGetSymFromAddr64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetSymFromAddr64]
  end;
end;
{$ELSE}
function SymGetSymFromAddr64; external ImageHlpLib name 'SymGetSymFromAddr64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetSymFromAddr: Pointer;

function SymGetSymFromAddr;
begin
  GetProcedureAddress(_SymGetSymFromAddr, ImageHlpLib, 'SymGetSymFromAddr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetSymFromAddr]
  end;
end;
{$ELSE}
function SymGetSymFromAddr; external ImageHlpLib name 'SymGetSymFromAddr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetSymFromName64: Pointer;

function SymGetSymFromName64;
begin
  GetProcedureAddress(_SymGetSymFromName64, ImageHlpLib, 'SymGetSymFromName64');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetSymFromName64]
  end;
end;
{$ELSE}
function SymGetSymFromName64; external ImageHlpLib name 'SymGetSymFromName64';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymGetSymFromName: Pointer;

function SymGetSymFromName;
begin
  GetProcedureAddress(_SymGetSymFromName, ImageHlpLib, 'SymGetSymFromName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymGetSymFromName]
  end;
end;
{$ELSE}
function SymGetSymFromName; external ImageHlpLib name 'SymGetSymFromName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _FindFileInPath: Pointer;

function FindFileInPath;
begin
  GetProcedureAddress(_FindFileInPath, ImageHlpLib, 'FindFileInPath');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FindFileInPath]
  end;
end;
{$ELSE}
function FindFileInPath; external ImageHlpLib name 'FindFileInPath';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _FindFileInSearchPath: Pointer;

function FindFileInSearchPath;
begin
  GetProcedureAddress(_FindFileInSearchPath, ImageHlpLib, 'FindFileInSearchPath');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FindFileInSearchPath]
  end;
end;
{$ELSE}
function FindFileInSearchPath; external ImageHlpLib name 'FindFileInSearchPath';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SymEnumSym: Pointer;

function SymEnumSym;
begin
  GetProcedureAddress(_SymEnumSym, ImageHlpLib, 'SymEnumSym');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SymEnumSym]
  end;
end;
{$ELSE}
function SymEnumSym; external ImageHlpLib name 'SymEnumSym';
{$ENDIF DYNAMIC_LINK}

function RVA_TO_ADDR(Mapping, Rva: Pointer): Pointer;
begin
  Result := Pointer(Cardinal(Mapping) + Cardinal(Rva));
end;


{$IFDEF DYNAMIC_LINK}
var
  _MiniDumpWriteDump: Pointer;

function MiniDumpWriteDump;
begin
  GetProcedureAddress(_MiniDumpWriteDump, ImageHlpLib, 'MiniDumpWriteDump');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MiniDumpWriteDump]
  end;
end;
{$ELSE}
function MiniDumpWriteDump; external ImageHlpLib name 'MiniDumpWriteDump';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MiniDumpReadDumpStream: Pointer;

function MiniDumpReadDumpStream;
begin
  GetProcedureAddress(_MiniDumpReadDumpStream, ImageHlpLib, 'MiniDumpReadDumpStream');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MiniDumpReadDumpStream]
  end;
end;
{$ELSE}
function MiniDumpReadDumpStream; external ImageHlpLib name 'MiniDumpReadDumpStream';
{$ENDIF DYNAMIC_LINK}

end.



