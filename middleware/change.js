$(document).ready(function () {
    $("#change").click(function () {
        var password = $("#password").val();
        var cid=$("#cid").val();
        var passpattern = /^[0-9a-zA-Z\s]{5,8}$/g;
        if (password == "") {
            Swal.fire({
                icon: 'error',
                title: 'Oops...',
                text: 'Enter new Password',
                footer: 'Marked As Mandatory'
            })
        }
        else if (passpattern.test(password) == false) {
            Swal.fire({
                icon: 'error',
                title: 'Oops...',
                text: 'Password name must contain 5-10 Characters / digits',
            })
        }
        else {
            $.ajax({
                url: "../backend/cpass.php",
                type: "post",
                async: false,
                data: {
                   "cid":cid,
                   "password":password
                },
                success:function(data)
                {
                    if(data==='Success')
                    {
                        Swal.fire({
                            icon: 'success',
                            title: 'Generation Success',
                            text: 'Password Generated Successfully',
                        })
                        document.getElementById("form").reset();
                        location.reload();
                    }
                    else{
                        Swal.fire({
                            icon: 'error',
                            title: 'Generation Failed',
                            text: 'Password Generation Failed',
                        })
                    }
                }
            });
        }
    });
});