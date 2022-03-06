<?php
include '../backend/db.php';
include '../backend/details.php';
$sqld="select *from employeedetails where EmpID='$get_cid'";
$executed=mysqli_query($connection,$sqld);
@$fetchd=mysqli_fetch_array($executed);
$status=$fetchd[5];
?>