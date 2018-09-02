unit ident;

{$include def.mor}

interface

procedure ident_run;
procedure ident_kill;

implementation

Uses sysutils,winsock,main{$ifdef debug},logger{$endif},sockets;

type
  TIdentHandler = class
  public
    class procedure DoAccept(Sender: TObject; ClientSocket: TCustomIpClient);
  end;

var sIdent:TTcpServer=nil;

class procedure TIdentHandler.DoAccept;
var s:string;
begin
s := ClientSocket.RemotePort+', '+inttostr(ClientSocket.LookupPort(inttostr(sock1))) + ' : USERID : ';    {Do not Localize}
s := s + 'UNIX';
s := s + ','+'76';    {Do not Localize}
s := s + ' : '+'IriNi';  {Do not Localize}  // Random Ident For No Detection ?
{$ifdef Debug}
  AddToMessageLog('[DEBUG] IDENT: ['+S+']');
{$endif}
ClientSocket.sendln(s);
// end thread here
{$ifdef Debug}
  AddToMessageLog('[DEBUG] IDENT STOP (OK)');
{$endif}
freeandnil(sIdent);
end;

procedure TIdent;
begin
  Try
    sIdent:=TTcpServer.Create(nil);
    sIdent.LocalPort:='113';
    sIdent.OnAccept:=TIdentHandler.Doaccept;
    sIdent.Active:=true;
  Finally
  {$ifdef debug}
    if sident.Listening Then
      AddToMessageLog('[DEBUG] IDENT START (OK).')
  {$endif}
  end;
  if not sident.Listening then
    begin
      {$ifdef debug}
        AddToMessageLog('[DEBUG] IDENT START (NOT OK).');
      {$endif}
      freeandnil(sIdent);
    end;
end;

Procedure ident_run;
begin
if sIdent = nil then
  Tident;
end;

procedure ident_kill;
begin
if sIdent <> nil then
  begin
    freeandnil(sident);
    {$ifdef debug}
      logger.AddToMessageLog('[DEBUG] IDENT STOP (OK)');
    {$endif}
  end;
end;

end.
