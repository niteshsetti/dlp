<?php
include '../backend/db.php';
if(isset($_POST["emid"]) || isset($_POST["pass"]))
{
    $emid=$_POST["emid"];
    $pass=$_POST["pass"];
    $conv=$pass;
    $sql="select *from employeedetails where EmpID='$emid'";
    $execute=mysqli_query($connection,$sql);
    @$fetch=mysqli_fetch_array($execute);
    $password=$fetch['Password'];
    if($password==$conv)
    {
        echo "Success";
    }
    else{
        echo "Failed";
    }
}
?>