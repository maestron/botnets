<?
//Author: Esrun - http://www.onlinehoster.com
//About: http://www.esrun.co.uk/blog/gmail-account-creator-gac/
//
//Use and abuse this script as you wish but a little link love wouldn't go a miss :)
//
//This script is in development and you should check my blog now and then to look for updates
?>

<style type='text/css'>
body {
font-family: verdana;	
}

.gmail {
width: 500px;	
border: 2px solid blue;
}

</style>

<?
@$submitted = $_POST['submitted'];
@$params = $_POST['params'];
@$FirstName = $_POST['FirstName'];
@$LastName = $_POST['LastName'];
@$Email = $_POST['Email'];
@$Password = $_POST['Password'];
@$FormLocation = $_POST['FormLocation'];
@$captchacode = $_POST['captchacode'];

if(!$submitted){
//@unlink("cookies.txt"); //Clear our cookies file

$signuppage = "http://mail.google.com/mail/signup";

$socket = curl_init();
CURL_SETOPT($socket, CURLOPT_URL, $signuppage);
CURL_SETOPT($socket, CURLOPT_REFERER, "http://www.google.com");
CURL_SETOPT($socket, CURLOPT_FOLLOWLOCATION, 1);
CURL_SETOPT($socket, CURLOPT_RETURNTRANSFER, 1);
CURL_SETOPT($socket, CURLOPT_POST, 1);
CURL_SETOPT($socket, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)");
//CURL_SETOPT($socket, CURLOPT_COOKIEJAR, "cookies.txt");
//CURL_SETOPT($socket, CURLOPT_COOKIEFILE, "cookies.txt");
$data = curl_exec($socket);

//Grab form location
preg_match("/<form action=\"(.+?)\" (.+?) id=\"createaccount\"/", $data, $output);
$FormLocation = $output[1];

//Grab the captcha image
preg_match("/Captcha\?ctoken=(.+?)\"/", $data, $output);
$token = $output[1];

//Grab hidden DSH code
preg_match("/name=\"dsh\" value=\"(.+?)\"/", $data, $output);
$dsh = $output[1];

//Grab new account token
preg_match("/id=\"newaccounttoken\" value=\"(.+?)\"/", $data, $output);
$NewAccountToken = $output[1];

//Grab EDK such as gmail.com or googlemail.com
preg_match("/id=\"edk\" value=\"(.+?)\"/", $data, $output);
$edk = $output[1];

//Grab names list
$firstnames = explode("\n", file_get_contents("firstnames.txt"));
$surnames = explode("\n", file_get_contents("surnames.txt"));

//Randomise signup name
$FirstName = trim(ucfirst(strtolower($firstnames[array_rand($firstnames)])));
$LastName = trim(ucfirst(strtolower($surnames[array_rand($surnames)])));

//Assin some random arrays
$letterrand = array("A","b","C","a","D","s","T","t");
$arrayrand = array("A","a","B","b","C","c","D","d","1","0","2","3","4","5","q","Q");

//Randomise email selection
$rand = rand(0,5);
if($rand == "0"){
$Email = $FirstName.".".$LastName;	
}
if($rand == "1"){
$Email = $FirstName.".".$LastName."19".rand(65,86);	
}
if($rand == "2"){
$Email = $FirstName.".".$LastName.rand(65,86);	
}
if($rand == "3"){
$Email = $FirstName."19".rand(65,86);	
}
if($rand == "4"){
$Email = $FirstName.$LastName;
}
if($rand == "5"){
$Email = $FirstName.substr($LastName, 0,1).rand(65,86);
}

//Make sure email is long enough
if(count($Email)<6){
$Email .= "19".rand(60,80);	
}


//Force email into lowercase
$Email = strtolower($Email);

//Generate random password
$Password = $letterrand[array_rand($letterrand)];
$passwordlength = rand(8,10);
for($i=0;$i<$passwordlength;$i++){
$Password .= $arrayrand[array_rand($arrayrand)];
}

$params[] = "continue=http%3A%2F%2Fmail.google.com%2Fmail";
$params[] = "service=mail";
$params[] = "dsh=".$dsh;
$params[] = "type=2";
$params[] = "t=null";
$params[] = "FirstName=".$FirstName;
$params[] = "LastName=".$LastName;
$params[] = "UsernameSelector=header";
$params[] = "Email=".$Email;
$params[] = "edk=".$edk;
$params[] = "Passwd=".$Password;
$params[] = "PasswdAgain=".$Password;
$params[] = "rmShown=1";
$params[] = "smhhk=1";
$params[] = "nshk=1";
$params[] = "selection=What+is+your+library+card+number";
$params[] = "IdentityAnswer=".rand(0,9).rand(0,9).rand(0,9).rand(0,9).rand(0,9).rand(0,9).rand(0,9).rand(0,9).rand(0,9).rand(0,9); //Randomise
$params[] = "hl=en";
$params[] = "gd=1";
$params[] = "loc=US";
$params[] = "newaccounttoken=".$NewAccountToken;
$params[] = "program_policy_url=http%3A%2F%2Fmail.google.com%2Fmail%2Fhelp%2Fprogram_policies.html";
$params[] = "privacy_policy_url=http%3A%2F%2Fwww.google.com%2Fintl%2Fen%2Fprivacy.html";
$params[] = "requested_tos_location=US";
$params[] = "requested_tos_language=en";
$params[] = "served_tos_location=US";
$params[] = "served_tos_language=en";
$params[] = "submitbutton=I+accept.+Create+my+account.";


echo "<form method='post' action='".$PHP_SELF."'>";

foreach($params as $param){
echo "<input type='hidden' name='params[]' value='$param'>";	
}

echo "<input type='hidden' name='submitted' value='1'>";	
echo "<input type='hidden' name='FirstName' value='".$FirstName."'>";	
echo "<input type='hidden' name='LastName' value='".$LastName."'>";	
echo "<input type='hidden' name='Email' value='".$Email."@".$edk."'>";	
echo "<input type='hidden' name='Password' value='".$Password."'>";	
echo "<input type='hidden' name='FormLocation' value='".$FormLocation."'>";	

echo "<div class='gmail'>
<table>
<tr><td>Image:</td><td><img src='https://www.google.com/accounts/Captcha?ctoken=".$token."'>
<tr><td>Name:</td><td>".$FirstName." ".$LastName."</td></tr>
<tr><td>Email:</td><td>".$Email."@".$edk."</td></tr>
<tr><td>Password:</td><td>".$Password."</td></tr>
<tr><td>Captcha:</td><td><input type='text' name='captchacode'></td></tr>
<tr><td>&nbsp;</td><td><input type='submit' value='Create account'></td></tr>
</div>";

} else {
$params[] = "newaccountcaptcha=".$captchacode;

$signuppage = $FormLocation;

//Set parameters
$paramlist="x=1";
foreach($params as $param){
$paramlist.= "&$param";	
}

$socket = curl_init();
CURL_SETOPT($socket, CURLOPT_URL, $signuppage);
CURL_SETOPT($socket, CURLOPT_REFERER, str_replace("CreateAccount", "NewAccount", $FormLocation));
CURL_SETOPT($socket, CURLOPT_FOLLOWLOCATION, 1);
CURL_SETOPT($socket, CURLOPT_RETURNTRANSFER, 1);
CURL_SETOPT($socket, CURLOPT_POST, 1);
CURL_SETOPT($socket, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)");
//CURL_SETOPT($socket, CURLOPT_COOKIEJAR, "cookies.txt");
//CURL_SETOPT($socket, CURLOPT_COOKIEFILE, "cookies.txt");
CURL_SETOPT($socket, CURLOPT_POSTFIELDS, $paramlist);
$data = curl_exec($socket);

//Check if the account creation was a success
if(eregi("Create an Account",$data)){
$status = "Account creation failed";	
} else {
$status = "Account creation was successful<br />
<table>
<tr><td>Name:</td><td>".$FirstName." ".$LastName."</td></tr>
<tr><td>Email:</td><td>".$Email."</td></tr>
<tr><td>Password:</td><td>".$Password."</td></tr>
</div>
";		
}

echo $status;
	
	
}

?>