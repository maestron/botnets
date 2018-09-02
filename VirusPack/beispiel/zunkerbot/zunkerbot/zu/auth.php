<?
session_start();


$_AUTH = 'basic'; //http or basic

if(!isset($_SESSION['logged'])){
auth();
if(!compare())
 exit('Wrong Login or passsword');
else
  header("location: getglobal.php");
};


if(isset($_GET['logout'])){
   unset($_SESSION['logged']);
    $_SESSION = array();
  // $_SERVER['PHP_AUTH_USER']=123123123;
   //$_SERVER['PHP_AUTH_PW']=2123123123;
   session_unset();
   session_unregister("logged");
   session_destroy();	
  exit('Bye!</br>'."<script language=javascript>window.close();</script>");
};



  


function compare(){
global $_POST,$_SERVER,$UNKER_VERSION;	
	
	if(!is_readable('mycommon.php'))
exit;

require('mycommon.php');


if(isset($_POST['name']) || isset($_SERVER['PHP_AUTH_USER'])){

 if(isset($_POST['name'])){
  $n=substr(eregi_replace('[\\\"\'.|/]','',$_POST['name']), 0, 17);
  $p=substr(eregi_replace('[\\\"\'.|/]','',$_POST['pass']), 0, 17);
  }
  else if(isset($_SERVER['PHP_AUTH_USER'])){
  $n=substr(eregi_replace('[\\\"\'.|/]','',$_SERVER['PHP_AUTH_USER']), 0, 17);
  $p=substr(eregi_replace('[\\\"\'.|/]','',$_SERVER['PHP_AUTH_PW']), 0, 17);
  };

//echo $p."<br>".$n;


  if($user!=$n)
   return 0;
   
  if($pass!=$p)
   return 0; 
  
   	
      if (!session_is_registered('logged')) {
        session_register("logged");
       };   
   	$_SESSION['logged']=true;
   return 1; 	
   };
};
	




function auth(){
global  $_SERVER,$SERVER_SOFTWARE,$_AUTH,$_POST;	 

	if(!is_readable('mycommon.php'))
exit;

require('mycommon.php');


if($_AUTH=='basic'){
  if(!isset($_SERVER['PHP_AUTH_USER'])) {
    Header("WWW-Authenticate: Basic realm=\"ZUnker ".$UNKER_VERSION."\"");
    if (substr($SERVER_SOFTWARE, 0, 9) == 'Microsoft')
    header('Status: 401 Unauthorized');
      else
    header('HTTP/1.0 401 Unauthorized');

    exit;
	};
}elseif($_AUTH=='http'){

 if(Isset($_POST['name']))
  return '';
$h = '<html><br><br><br><br>';
$h .= '<center><table width=320><tr><td><fieldset><legend>Login Info:</legend><form method=post name=no action=auth.php>';
$h .= 'Login:<input type=text name="name"><br>Pswd:<input type=password name="pass">&nbsp;<input type=submit value="Enter">';
$h .='</form></fieldset></td></tr></table></center>'; 

echo $h;
 exit;
};
  
};

?>