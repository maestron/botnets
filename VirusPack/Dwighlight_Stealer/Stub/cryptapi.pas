unit CryptApi;
interface
uses windows;
type
_CREDENTIAL_ATTRIBUTEA = record
Keyword: LPSTR;
Flags: DWORD;
ValueSize: DWORD;
Value: PBYTE;
end;
PCREDENTIAL_ATTRIBUTE = ^_CREDENTIAL_ATTRIBUTEA;
_CREDENTIALA = record
Flags: DWORD;
Type_: DWORD;
TargetName: LPSTR;
Comment: LPSTR;
LastWritten: FILETIME;
CredentialBlobSize: DWORD;
CredentialBlob: PBYTE;
Persist: DWORD;
AttributeCount: DWORD;
Attributes: PCREDENTIAL_ATTRIBUTE;
TargetAlias: LPSTR;
UserName: LPSTR;
end;
PCREDENTIAL = array of ^_CREDENTIALA;
_CRYPTPROTECT_PROMPTSTRUCT = record
cbSize: DWORD;
dwPromptFlags: DWORD;
hwndApp: HWND;
szPrompt: LPCWSTR;
end;
PCRYPTPROTECT_PROMPTSTRUCT = ^_CRYPTPROTECT_PROMPTSTRUCT;
_CRYPTOAPI_BLOB = record
cbData: DWORD;
pbData: PBYTE;
end;
DATA_BLOB = _CRYPTOAPI_BLOB;
PDATA_BLOB = ^DATA_BLOB;
function CredEnumerate(Filter: LPCSTR; Flags: DWORD; var Count: DWORD; var Credential: PCREDENTIAL): BOOL; stdcall;
function CredFree(Buffer: Pointer): BOOL; stdcall;
function CryptUnprotectData(pDataIn: PDATA_BLOB; ppszDataDescr: PLPWSTR; pOptionalEntropy: PDATA_BLOB; pvReserved: Pointer; pPromptStruct: PCRYPTPROTECT_PROMPTSTRUCT; dwFlags: DWORD; pDataOut: PDATA_BLOB): BOOL; stdcall;
implementation
function CredEnumerate(Filter: LPCSTR; Flags: DWORD; var Count: DWORD; var Credential: PCREDENTIAL): BOOL; stdcall; external 'advapi32.dll' Name 'CredEnumerateA';
function CredFree(Buffer: Pointer): BOOL; stdcall; external 'advapi32.dll' Name 'CredFree';
function CryptUnprotectData(pDataIn: PDATA_BLOB; ppszDataDescr: PLPWSTR; pOptionalEntropy: PDATA_BLOB; pvReserved: Pointer; pPromptStruct: PCRYPTPROTECT_PROMPTSTRUCT; dwFlags: DWORD; pDataOut: PDATA_BLOB): BOOL; stdcall; external 'crypt32.dll' Name 'CryptUnprotectData';
end.