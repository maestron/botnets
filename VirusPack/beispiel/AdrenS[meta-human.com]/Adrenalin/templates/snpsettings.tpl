<html>

<head>
  <title>S'n'P Installer</title>
</head>

<style>
TD, SELECT, TEXTAREA, INPUT
{
        font-family: Tahoma;
        font-size: 8pt;
}

A:link
{
        color: BLUE;
        text-decoration: none;
}

A:visited
{
        color: BLUE;
        text-decoration: none;
}

A:hover
{
        color: #E14C22;
        text-decoration: underline;
}

A:active
{
        color: BLUE;
        text-decoration: none;
}

</style>

<table border='0'>
<form action='setup.php?do=1' method='POST'>
<tr>
 <td>
  MySQL Server:
 </td>
 <td>
  <input type='text' name='mysqlServer' value='{strServer}'>
 </td>
</tr>
<tr>
 <td>
  MySQL User:
 </td>
 <td>
  <input type='text' name='mysqlUser' value='{strUser}'>
 </td>
</tr>
<tr>
 <td>
  MySQL Password:
 </td>
 <td>
  <input type='text' name='mysqlPassword' value='{strPassword}'>
 </td>
</tr>
<tr>
 <td>
  MySQL Database:
 </td>
 <td>
  <input type='text' name='mysqlDatabase' value='{strDatabase}'>
 </td>
</tr>
<tr>
 <td>
  Create tables:
 </td>
 <td>
  <input type='checkbox' name='createTables' value='yes'>
 </td>
</tr>
<tr>
 <td>
  Admin User:
 </td>
 <td>
  <input type='text' name='firstUser' value='{strFirstUser}'>
 </td>
</tr>
<tr>
 <td>
  Admin Password:
 </td>
 <td>
  <input type='text' name='firstPassword' value='{strFisrtPassword}'>
 </td>
</tr>
<tr>
 <td colspan='2' align='center'>
  <input type='submit' value='Install'>
 </td>
</tr>
</form>
</table>

</html>