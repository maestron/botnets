<?php 

//Define some variables 
$dir = "$DOCUMENT_ROOT/"; 

//MIME types to allow, Gif, jpeg, zip ::Edit this to your liking 
$types = array ("image/gif","text/html","text/plain","application/msword","application/octet-stream","application/vnd.ms-powerpoint","image/pjpeg","application/x-zip-compressed"); 

//Check to determine if the submit button has been pressed 
if(isset($_POST['submit'])) { 
  //Shorten Variables 
  $tmp_name = $_FILES['upload']['tmp_name']; 
  $new_name = $_FILES['upload']['name']; 


  //Check MIME Type 
  if (in_array($_FILES['upload']['type'], $types)) { 
    //Move file from tmp dir to new location 
    move_uploaded_file($tmp_name,$dir . $new_name); 
    
    echo "{$_FILES['upload']['name']} was uploaded sucessfully!"; 
  }else { 
    //Print Error Message 
    echo "<small>File <strong><em>{$_FILES['upload']['name']}</em></strong> Was Not Uploaded!</small><br />"; 
    
    //Debug 
    $name = $_FILES['upload']['name']; 
    $type = $_FILES['upload']['type']; 
    $size = $_FILES['upload']['size']; 
    $tmp = $_FILES['upload']['name']; 

    echo "Name: $name<br/ >Type: $type<br />Size: $size<br />Tmp: $tmp"; 
  }  
}else { 
  echo 'Could Not Upload Files'; 
} 
?>
 
<form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post" enctype="multipart/form-data"> 
  <fieldset> 
    <legend>Upload Files</legend> 
    <input type="file" name="upload" /> 
  </fieldset> 
  
  <input type="submit" name="submit" value="Upload Files" /> 
</form> 
