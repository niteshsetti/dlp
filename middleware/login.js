$(document).ready(function () {
    $("#login").click(function () {
        var password = $("#epass").val();
        var emid = $("#eid").val();
        if (password == "") {
            Swal.fire({
                icon: 'warning',
                title: 'Oops...',
                text: 'Enter Your Password'
            })
        }
        else {
            $.ajax({
                url: '../backend/login.php',
                type: "post",
                async: false,
                data: {
                    "emid": emid,
                    "pass": password
                },
                success: function (data) {
                    if (data === 'Success') {
                        let timerInterval
                        Swal.fire({
                            title: 'Login Success Redirecting !! ',
                            html: 'I will close in <b></b> milliseconds.',
                            timer: 2000,
                            timerProgressBar: true,
                            didOpen: () => {
                                Swal.showLoading()
                                const b = Swal.getHtmlContainer().querySelector('b')
                                timerInterval = setInterval(() => {
                                    b.textContent = Swal.getTimerLeft()
                                }, 100)
                            },
                            willClose: () => {
                                clearInterval(timerInterval)
                                window.location.replace('../Dashboard/template/index.html');
                            }
                        }).then((result) => {
                            /* Read more about handling dismissals below */
                            if (result.dismiss === Swal.DismissReason.timer) {
                                console.log('I was closed by the timer')
                            }
                        })
                    }
                    else{
                        Swal.fire({
                            icon: 'error',
                            title: 'Wrong Password',
                            text: 'Login Failed'
                        }) 
                    }
                }
            });
        }
    });
});