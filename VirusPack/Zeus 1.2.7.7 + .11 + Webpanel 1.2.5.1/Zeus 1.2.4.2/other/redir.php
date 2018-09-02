<?php
//URL оригинального сервера.
$url = "http://localhost/s.php";

@error_reporting(0); @set_time_limit(0);

//Коннектимся к оригинальному серверу.
$url = @parse_url($url);
if(!isset($url['port']))$url['port'] = 80; 
if(($real_server = @fsockopen($url['host'], $url['port'])) === false)die('E1');

//Получаем данные для пересылки.
if(($data = @file_get_contents('php://input')) === false)$data = '';

//Формируем запрос.
$request  = "POST {$url['path']}?ip=".urlencode($_SERVER['REMOTE_ADDR'])." HTTP/1.1\r\n";
$request .= "Host: {$url['host']}\r\n";

if(!empty($_SERVER['HTTP_USER_AGENT']))$request .= "User-Agent: {$_SERVER['HTTP_USER_AGENT']}\r\n";

//$request .= "Content-Type: application/x-www-form-urlencoded\r\n";
$request .= "Content-Length: ".strlen($data)."\r\n";
$request .= "Connection: Close\r\n";

//Отправляем.
fwrite($real_server, $request."\r\n".$data);

//Получаем ответ.
$result = '';
while(!feof($real_server))$result .= fread($real_server, 1024);
fclose($real_server);

//Выводим ответ.
echo substr($result, strpos($result, "\r\n\r\n") + 4);
?>