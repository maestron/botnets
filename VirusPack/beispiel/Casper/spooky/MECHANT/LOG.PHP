<?php
 // Update main file
 $file = "log.txt";
 $st = fopen($file, "a+");

 $date = date("d/m/y - H:i:s"); 
 $ip   = $_SERVER['REMOTE_ADDR'];

 $ref  = $_GET["ref"]; 
  
 $format = "[$date] - $ip - $ref\n";
   
 fwrite($st, $format, strlen($format));
 fclose($st);

 echo "OK";
?>