<?
session_start();
   if(!@$_SESSION['logged']){
  echo '<script language=JavaScript>location.href="getglobal.php"</script>';
  exit;
  };
  
  header("location: getglobal.php");

?>