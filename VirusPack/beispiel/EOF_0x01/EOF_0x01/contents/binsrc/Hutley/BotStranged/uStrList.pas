UNIT uStrList;

INTERFACE

TYPE
  TStrList = CLASS(TObject)
  PRIVATE
    vList  : ARRAY OF STRING;
  PUBLIC
    Count : Integer;
    CONSTRUCTOR Create;
    PROCEDURE   Clear;
    PROCEDURE   Add(Text:STRING);
    PROCEDURE   Replace(Index: Integer; Input: String);
    FUNCTION    Strings(Index:Integer) : STRING;
  END;

IMPLEMENTATION

PROCEDURE TStrList.Replace(Index: Integer; Input: String);
BEGIN
  vList[Index] := Input;
END;

CONSTRUCTOR TStrList.Create;
BEGIN
  Count:=0;
  SetLength(vList,Count+1);
END;

procedure TStrList.Clear;
var
  i: Integer;
begin
  For i := 0 to Count-1 do
    vList[i] := '';
  Count := 0;
end;

PROCEDURE TStrList.Add(Text:STRING);
BEGIN
  SetLength(vList,Count+1);
  vList[Count]:=Text;
  Inc(Count);
END;

FUNCTION TStrList.Strings(Index:Integer) : STRING;
BEGIN
  Result:=vList[Index];
END;

END.
