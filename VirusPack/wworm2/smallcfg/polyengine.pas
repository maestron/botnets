unit polyengine;

interface

uses Windows;

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

function XorCrypt(strText: string;intKey: longint): string;
function CryptString(PlainText: String; pass :integer):String;
function DecryptString(CipherText: String; pass :integer):String;

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

function XorCrypt(strText: string;intKey: longint): string;
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

function XorDecrypt(strText: string;intKey: longint): string;
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




function DecryptString(CipherText: String; pass :integer):String;
var Workbuffer2 ,WorkBuffer: String;
begin
  WorkBuffer := CipherText;
  WorkBuffer := EasyDeCrypt(WorkBuffer);
  WorkBuffer := Decode64(Workbuffer);
  WorkBuffer := XorDecrypt(WorkBuffer, pass);
  Result := WOrkbuffer;
end;

function CryptString(PlainText: String; pass :Integer):String;
var
  WorkBuffer: String;
begin
  WorkBuffer := PlainText;
  ////////////////////////////////////////////
  WorkBuffer := polyengine.XorCrypt(Workbuffer, pass);
  WorkBuffer := Encode64(Workbuffer);
  WorkBuffer := EasydeCrypt(WorkBuffer);
  ////////////////////////////////////////////
  Result := Workbuffer;
  ////////////////////////////////////////////
end;

end.
