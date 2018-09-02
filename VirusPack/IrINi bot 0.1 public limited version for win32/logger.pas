unit logger;

interface
{$ifndef debug}
procedure AddToMessageLog(Msg:string);
{$endif}
implementation
{$ifndef debug}
uses sysutils,classes;

var Lala:text;

procedure AddToMessageLog;
begin
   msg:='['+timetostr(time)+'] '+msg + #13#10;
   Append(lala);
   Write(Lala, msg);
   closefile(Lala);
end;

begin
AssignFile(Lala, 'log.txt');
rewrite(Lala);
{$endif}
end.
