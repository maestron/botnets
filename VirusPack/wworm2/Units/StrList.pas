unit StrList;

interface

type
  TStrList = Class(TObject)
  private
    vList: Array of String;
    ListLn: Integer;
  public
    constructor Create;

    procedure Add(Text: String);
    function Text: String;
    function Strings(Index: Integer): String;
    procedure NewVar(Index: Integer; newtext: String);
    procedure Clear;
    function Count: Integer;
  end;

implementation

constructor TStrList.Create;
begin
  ListLn := 0;
  SetLength(vList, ListLn + 1);
end;

procedure TStrList.Add(Text: String);
begin
  SetLength(vList, ListLn + 1);
  vList[Listln] := Text;
  Inc(Listln);
end;

procedure TStrList.Clear;
var
  i: Integer;
begin
  For i := 0 to ListLn-1 do
    vList[i] := '';
  Listln := 0;
end;

function TStrList.Text: String;
var
  i: Integer;
  Txt: String;
begin
  For i := 0 to ListLn-1 do
    Txt := Txt + vList[i] + #13;

  Txt := Copy(Txt, 1, Length(Txt)-1);
  Result := Txt;
end;

function TStrList.Strings(Index: Integer): String;
begin
  Result := vList[Index];
end;

procedure TStrList.NewVar(Index: Integer; newtext: String);
begin
  vList[Index] := newtext;
end;

function TStrList.Count: Integer;
begin
  Result := ListLn;
end;

end.
