<?php
include './db.php';
include './mail.php';
if (isset($_POST["empname"]) || isset($_POST["empemail"]) || isset($_POST["empmobile"])) {
    $empname = $_POST["empname"];
    $empemail = $_POST["empemail"];
    $empmobile = $_POST["empmobile"];
    $c_id = "WI" . uniqid();
    $dup_check = "select *from employeedetails where Empemail='$empemail'";
    $dup_email = mysqli_query($connection, $dup_check);
    $email_count = mysqli_num_rows($dup_email);
    $dup_checks = "select *from employeedetails where Empphno='$empmobile'";
    $dup_mobile = mysqli_query($connection, $dup_checks);
    $mobile_count = mysqli_num_rows($dup_mobile);
    if ($email_count > 0) {
        echo "DE";
    }
    else if ($mobile_count > 0) {
        echo "DM";
    } else {
        $sql = "insert into employeedetails(EmpID,Empname,Empemail,Empphno,Password,Status)values('$c_id','$empname','$empemail','$empmobile','Hello@123','Decline')";
        $execute = mysqli_query($connection, $sql);
        if ($execute) {
            email($empname,$empemail,$c_id);

        } else {
            echo "Failed";
        }
    }
}
