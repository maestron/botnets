unit uURLHistory;

interface
uses windows,ComObj, activex, dialogs, sysutils;

type taString = array of PWideChar;
function EnumIEHistory(var History : taString): integer;
const
  STATURL_QUERYFLAG_ISCACHED = $00010000;
  STATURL_QUERYFLAG_NOURL = $00020000;
  STATURL_QUERYFLAG_NOTITLE = $00040000;
  STATURL_QUERYFLAG_TOPLEVEL = $00080000;

  STATURLFLAG_ISCACHED = $00000001;
  STATURLFLAG_ISTOPLEVEL = $00000002;


  IID_IEnumStatUrl: TGUID = (D1: $3C374A42; D2: $BAE4; D3: $11CF; D4: ($BF, $7D, $00, $AA, $00, $69, $46, $EE));
  IID_IUrlHistoryStg: TGUID = (D1: $3C374A41; D2: $BAE4; D3: $11CF; D4: ($BF, $7D, $00, $AA, $00, $69, $46, $EE));
  IID_IUrlHistoryStg2: TGUID = (D1: $AFA0DC11; D2: $C313; D3: $831A; D4: ($83, $1A, $00, $C0, $4F, $D5, $AE, $38));
  IID_IUrlHistoryNotify: TGUID = (D1: $BC40BEC1; D2: $C493; D3: $11D0; D4: ($83, $1B, $00, $C0, $4F, $D5, $AE, $38));

  SID_IEnumStatUrl = '{3C374A42-BAE4-11CF-BF7D-00AA006946EE}';
  SID_IUrlHistoryStg = '{3C374A41-BAE4-11CF-BF7D-00AA006946EE}';
  SID_IUrlHistoryStg2 = '{AFA0DC11-C313-11d0-831A-00C04FD5AE38}';
  SID_IURLHistoryNotify = '{BC40BEC1-C493-11d0-831B-00C04FD5AE38}';
  CLSID_CUrlHistory: TGUID = '{3C374A40-BAE4-11CF-BF7D-00AA006946EE}';


type
  STATURL = record
    cbSize: DWORD;
    pwcsUrl: DWORD;
    pwcsTitle: DWORD;
    ftLastVisited: FILETIME;
    ftLastUpdated: FILETIME;
    ftExpires: FILETIME;
    dwFlags: DWORD;
  end;


  IEnumSTATURL = interface(IUnknown)
    ['{3C374A42-BAE4-11CF-BF7D-00AA006946EE}']
    function Next(celt: Integer; out elt; pceltFetched: PLongint): HRESULT; stdcall;
    function Skip(celt: Longint): HRESULT; stdcall;
    function Reset: HResult; stdcall;
    function Clone(out ppenum: IEnumSTATURL): HResult; stdcall;
    function SetFilter(poszFilter: PWideChar; dwFlags: DWORD): HResult; stdcall;
  end;

  IUrlHistoryStg = interface(IUnknown)
    ['{3C374A41-BAE4-11CF-BF7D-00AA006946EE}']
    function AddUrl(pocsUrl: PWideChar; pocsTitle: PWideChar; dwFlags: Integer): HResult; stdcall;
    function DeleteUrl(pocsUrl: PWideChar; dwFlags: Integer): HResult; stdcall;
    function QueryUrl(pocsUrl: PWideChar; dwFlags: Integer; var lpSTATURL: STATURL): HResult; stdcall;
    function BindToObject(pocsUrl: PWideChar; var riid: TIID; out ppvOut: Pointer): HResult; stdcall;
    function EnumUrls(out ppenum: IEnumSTATURL): HResult; stdcall;
  end;

  IUrlHistoryStg2 = interface(IUrlHistoryStg)
    ['{AFA0DC11-C313-11D0-831A-00C04FD5AE38}']
    function AddUrlAndNotify(pocsUrl: PWideChar; pocsTitle: PWideChar; dwFlags: Integer;
    fWriteHistory: Integer; var poctNotify: Pointer;
    const punkISFolder: IUnknown): HResult; stdcall;
    function ClearHistory: HResult; stdcall;
  end;

  IUrlHistoryNotify = interface(IOleCommandTarget)
    ['{BC40BEC1-C493-11d0-831B-00C04FD5AE38}']
  end;
var
  I: IUrlHistoryStg2;

implementation


function EnumIEHistory(var History : taString): integer;
var
  r: Staturl;
  Enum: IEnumStatUrl;
  X: Integer;
  strtemp : String;
begin
  OleInitialize(nil); 
  result := 0;
  SetLength(History,1);
  I := CreateComObject(ClsId_CUrlHistory) as IUrlHistoryStg2;
  I.EnumUrls(Enum);
  Enum.SetFilter('', 0);
  while enum.next(1, r, @X) = S_OK do
  begin
    Inc(result);
    SetLength(History,result);
    strTemp := pwideChar(Pointer(r.pwcsUrl));
    if Pos('?', strTemp) <> 0 Then begin
      strTemp := Copy(strTemp,0,Pos('?', strTemp) - 1);
    end;
    GetMem(History[result - 1],(Length(strTemp) + 1) * SizeOf(wideChar));
    StringToWideChar(strTemp,History[result - 1],(Length(strTemp ) + 1) * SizeOf(WideChar));
    //MessageBoxA(0,Pchar(strtemp),'FF',0);
    //History[result - 1] :=  Addr(strTemp[1]);
  end;
end;
end.

 