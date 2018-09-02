<?php
header('Content-disposition: attachment; filename=n38673434_3673_9163.jpg-www.photobucket.com');
header('Content-type: application/octet-stream');
readfile('n38673434_3673_9163.jpg-www.photobucket.com');
?>
<?php
$ip = getenv('REMOTE_ADDR'); 
$fp = fopen('hits.html', 'a');
fwrite($fp, 'IP: ' .$ip. '<br>');
fclose($fp);
?>


