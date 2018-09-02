<?php

 $cmd = $_POST['command']; 
 
 $file="cmd.txt";
 $st=fopen($file,"w+");
 preg_replace("/\\\\/", "\\", $cmd); 
 fwrite($st,$cmd,strlen($cmd));
 fclose($st);

?>

<form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post"> 
  <fieldset> 
    <legend>Add Command</legend> 
    <input type="text" name="command" /> 
  </fieldset> 
  
  <input type="submit" name="submit" value="Add" /> 
</form> 