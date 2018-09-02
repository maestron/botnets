unit polyengine;

interface

var
  CKey:  Integer = 0;
  XKey:  Integer = 0;
  intdefkey:  Integer = 0;
  cryptcount: Integer = 0;
  RCKey: String = '';
  Caesar: Boolean = FAlSE;
  X: Boolean = FAlSE;
  RC4: Boolean = FAlSE;
  Base64: Boolean = FAlSE;
  simplecrypt: Boolean = FAlSE;
    
  Codes64: String = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/';


function CryptString(PlainText, pass :string):String;
function DecryptString(CipherText, pass :string):String;
function XorCrypt(const strText: string; const intKey: longint): string;
function XorDecrypt(const strText: string; const intKey: longint): string;

implementation

function RandomString(PLen: Integer): string;
var
  str: string;
begin
  Randomize;
  str    := 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890';
  Result := '';
  repeat
    Result := Result + str[Random(Length(str)) + 1];
  until (Length(Result) = PLen)
end;


function EasyDecrypt(const InStr: String): String;
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

function XorCrypt(const strText: string; const intKey: longint): string;
var
  i: integer;
  strResult: string;
begin
  strResult := strText;
  // sync RandSeed key to generate Random chars
  RandSeed := intKey;
  // cipher
  for i := 1 to Length(strText) do
    strResult[i] := Chr(Ord(strResult[i]) xor Random(255));
  // set results
  Result := strResult;
end;

function XorDecrypt(const strText: string; const intKey: longint): string;
begin
  // deciphers the string
  Result := XorCrypt(strText, intKey);
end;

function Encode64(S: string): string;
var
  i: Integer;
  a: Integer;
  x: Integer;
  b: Integer;
begin
  Result := '';
  a := 0;
  b := 0;
  for i := 1 to Length(s) do
  begin
    x := Ord(s[i]);
    b := b * 256 + x;
    a := a + 8;
    while a >= 6 do
    begin
      a := a - 6;
      x := b div (1 shl a);
      b := b mod (1 shl a);
      Result := Result + Codes64[x + 1];
    end;
  end;
  if a > 0 then
  begin
    x := b shl (6 - a);
    Result := Result + Codes64[x + 1];
  end;
end;

function Decode64(S: string): string;
var
  i: Integer;
  a: Integer;
  x: Integer;
  b: Integer;
begin
  Result := '';
  a := 0;
  b := 0;
  for i := 1 to Length(s) do
  begin
    x := Pos(s[i], codes64) - 1;
    if x >= 0 then
    begin
      b := b * 64 + x;
      a := a + 6;
      if a >= 8 then
      begin
        a := a - 8;
        x := b shr a;
        b := b mod (1 shl a);
        x := x mod 256;
        Result := Result + chr(x);
      end;
    end
    else
      Exit;
  end;
end;




function RC4CR(Expression, Password: string): string;
var
  RB : array[0..255] of Integer;
  X, Y, Z: longint;
  Key : array of byte;
  ByteArray : array of byte;
  Temp: byte;
  Counter: integer;
begin
  If (Length(Expression) = 0) then Exit;
  If (Length(Password) = 0) then Exit;
  If (Length(Password) > 256) then begin
    Password := Copy(Password, 1, 256);
  end;
  SetLength(Key, Length(Password));
  for Counter := 0 to Length(Password) - 1 do
  begin
    Key[Counter] := ord(Password[Counter + 1]);
  end;
  for X := 0 to 255 do
  begin
    RB[X] := X;
  end;
  X := 0;
  Y := 0;
  Z := 0;
  for X := 0 to 255 do
  begin
    Y := (Y + RB[X] + Key[X mod Length(Password)]) mod 256;
    Temp := RB[X];
    RB[X] := RB[Y];
    RB[Y] := Temp;
  end;
  X := 0;
  Y := 0;
  Z := 0;
  SetLength(ByteArray, Length(Expression));
  for Counter := 0 to Length(Expression) - 1 do
  begin
    ByteArray[Counter] := ord(Expression[Counter + 1]);
  end;
  for X := 0 to Length(Expression) do
  begin
    Y := (Y + 1) mod 256;
    Z := (Z + RB[Y]) mod 256;
    Temp := RB[Y];
    RB[Y] := RB[Z];
    RB[Z] := Temp;
    ByteArray[X] := ByteArray[X] xor (RB[(RB[Y] + RB[Z]) mod 256]);
  end;
  for Counter := 0 to Length(Expression) - 1  do
  begin
    Result := Result + chr(ord(ByteArray[Counter]));
  end;
end;

function DecryptString(CipherText, pass :string):String;
var Workbuffer2 ,WorkBuffer: String;
begin
  WorkBuffer := CipherText;
  WorkBuffer := RC4CR(Workbuffer, pass);
  WorkBuffer := EasyDeCrypt(WorkBuffer);
  WorkBuffer := Decode64(Workbuffer);

 // if X = TRUE then WorkBuffer := XorDecrypt(WorkBuffer, intdefkey);

 REsult := WOrkbuffer;
end;

function CryptString(PlainText, pass :string):String;
var
  WorkBuffer: String;
  Countme   : Integer;
begin
  WorkBuffer := PlainText;
  ////////////////////////////////////////////
  Randomize;
  Countme := Random(2);
  Base64 := TRUE;
  Randomize;
  Countme := Random(2);
  SimpleCrypt := TRUE;
  RC4 := TRUE;
  ////////////////////////////////////////////

  ////////////////////////////////////////////

  ////////////////////////////////////////////
  If Base64 = TRUE then
  begin
    WorkBuffer := Encode64(Workbuffer);
  end;
  ////////////////////////////////////////////
  If SimpleCrypt = TRUE then
  begin
    WorkBuffer := EasydeCrypt(WorkBuffer);
  end;
  ////////////////////////////////////////////

  ////////////////////////////////////////////
  if RC4 = TRUE then
  begin

    Workbuffer := RC4CR(WorkBuffer, pass);
  end;
  REsult := Workbuffer;
end;

end.
