<?php
include '../backend/db.php';
if(isset($_POST["cid"]) || isset($_POST["password"]))
{
    $cid=$_POST["cid"];
    $password=$_POST["password"];
    $enc_password=$password;
    $sql="update employeedetails set Password='$enc_password',Status='Approved' where EmpID='$cid'";
    $execute=mysqli_query($connection,$sql);
    if($execute)
    {
        echo "Success";
    }
    else{
        echo "Failed";
    }
}
