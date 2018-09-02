unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, polyengine;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Button1: TButton;
    Button2: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  mylist: TStringList;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
begin
mylist := TStringList.Create;
Edit2.Text := polyengine.Cryptstring(Edit1.Text, StrToInt(Edit3.Text));
mylist.Add(Edit2.Text);
mylist.SaveToFile('file.txt');
end;                                       

procedure TForm1.Button2Click(Sender: TObject);
begin
Edit1.Text := polyengine.DeCryptstring(Edit2.TExt, StrToInt(Edit3.TExt));
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
ShowMessage(polyengine.XorCrypt('test', 123123123));
end;

end.
