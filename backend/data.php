<?php
include '../backend/db.php';
include '../backend/details.php';
$sql="select *from employeedetails where EmpID='$get_cid'";
$execute=mysqli_query($connection,$sql);
@$fetch=mysqli_fetch_array($execute);
$get_name=$fetch[1];
?>