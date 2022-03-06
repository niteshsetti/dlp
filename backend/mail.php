<?php
function email($name,$email,$c_id)
{
$our_email = "nitesh.setti2001@gmail.com";
$to = $email;
$from = $our_email;
$subject = "Reset Your Company password";
$message = 'Hello '.$name.' Your Record is added by Hr Successfully now you need to reset your password through this link
<html>
<body>
<a href="http://localhost/Doorlockproject/frontend/user.php?%20Empid='.$c_id.'">Click Here!!!</a>
</body>
</html>';
$headers  = "From: $from\r\n";
$headers .= "Content-type: text/html\r\n";
$mail = mail($to, $subject, $message, $headers);
if($mail)
{
    echo "Suc";
}
else{
    echo "Fail";
}
}
?>