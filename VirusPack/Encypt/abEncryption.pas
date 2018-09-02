unit abEncryption;

interface
  uses Windows;

function Decrypt(const InStr: String): String;

implementation

function Decrypt(const InStr: String): String;
var
  C1, C2: Integer;
  Ch1, Ch2: Byte;
  OutStr, Key: String;
begin
  Key := '####';
  C1 := 0;
  C2 := 0;
  OutStr := '';
  while (C1 < Length(InStr)) do
  begin
    Inc(C1);
    Inc(C2);
    if (C2 > Length(Key)) then C2 := 1;
    Ch1 := Ord(InStr[C1]);
    Ch2 := Ord(Key[C2]) + 128;
    OutStr := OutStr + Chr(Ch1 xor Ch2);
  end;
  Result := OutStr;
end;

end.
