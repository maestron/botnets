<?php
/*
  Этот файл может свободно модифицироваться.
  Файл содержит код для создания архивного файла.
  
  Архиватор ZIP можно загрузить по адресу http://www.info-zip.org/Zip.html.
  
  ВНИМАНИЕ: Файл находиться в UTF-8 кодировке. Файл всегда должен сохраняться без BOM (заголовок UTF-8).
*/

/*
  Создание архива.
  
  IN $archive - string, полный путь по которому должен быть создан архив (без расширения).
  IN $files   - array, список файлов для добавления в архив.
  
  Return      - mixed, имя архива - в случаи успешного создания архива, false - в случаи ошибки.
*/
function arc_Create($archive, $files)
{
  error_reporting(E_ALL);
  if(strcasecmp(substr(php_uname('s'), 0, 7), 'windows') === 0)
  {
    $archive = str_replace('/', '\\', $archive);
    foreach($files as $k => $v)$files[$k] = str_replace('/', '\\', $v);
  }
  
  $archive .= '.zip';
  $cli = 'zip -r -9 -q -S "'.$archive.'" "'.implode('" "', $files).'"';
  exec($cli, $e, $r);
  
  if($r != 0)echo "(error: $r) ".$cli.'<br/>';  
  return $r ? false : $archive;
}
?>