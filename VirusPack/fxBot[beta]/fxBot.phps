<?

#################################################
#                 fxBot[beta]1.2                #
# 02/14/06                                      #
# Happy Love Day!                 <3r           #
# "A lesson learned is a lesson earned." -Chris #
#################################################

# <settings>
$server = "irc.server.com";
$port = "6667";
$socknick = "BotNick22";
$channel = "#nerds";
$mastern = "bongfu";
$botpass = "password";
$botemail = "e@mail.com";
# </settings>

   $socket = socket_create(AF_INET,SOCK_STREAM,SOL_TCP);
   $connection = socket_connect($socket,$server,$port);
   socket_write($socket,"USER $socknick $socknick $socknick :$socknick \r\n");
   socket_write($socket,"NICK $socknick \r\n");
   socket_write($socket,"PRIVMSG nickserv identify $botpass \r\n");
   socket_write($socket,"JOIN $channel \r\n");

   while($data = socket_read($socket,2046)) {
     if(ereg("PING",$data)) {
       $ping = explode(":",$data);
       $reply = $ping[1];
       socket_write($socket, "PONG $reply\n\r");
       $new = $new . "<br>PONG $reply"; $register = "1";
    }
   if (ereg("!quit",$data)) {
     if (ereg("$mastern",$data)) {
        socket_write($socket,"PRIVMSG $channel :Quit command issued \r\n");
        socket_write($socket,"QUIT :Good day. \r\n");
      }
    }
  if (ereg("!info",$data)) {
     if (ereg("$mastern",$data)) {
        socket_write($socket,"PRIVMSG $channel :fxBot[beta]1.2 by sketch, in PHP , connected to: $server w/ nick: $socknick on channel(s): $channel \r\n");
      }
    }
if (ereg("!register",$data)) {
     if (ereg("$mastern",$data)) {
        socket_write($socket,"PRIVMSG $channel Registering Nickname. \r\n");        
        socket_write($socket,"PRIVMSG nickserv register $botpass $botemail \r\n");
      }
    }
if (ereg("!identify",$data)) {
     if (ereg("$mastern",$data)) {
        socket_write($socket,"PRIVMSG nickserv identify $botpass \r\n");
      }
    }
if (ereg("!boxuptime",$data)) {
     if (ereg("$mastern",$data)) {
      $uptime = system("uptime");
        socket_write($socket,"PRIVMSG $channel :$uptime \r\n");
      }
    }
    echo $data . "<br>";
  }
?> 