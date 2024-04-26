<?php 
	header('Content-type:text/html; charset=utf-8');
	session_start();
	if (isset($_GET['login'])) 
	{
		echo "<script>window.alert('net work error 418')</script>";
	}
	if (isset($_POST['login'])) 
	{
		$username = trim($_POST['username']);
		$password = trim($_POST['password']);
		$allof=2;//在此处添加用户数量
		$usrnm[$allof]={'your username 1','your username 2'};//添加用户名
		$paswrd[$allof]={'your password 1','your password2'};//添加密码
		if (($username == '') || ($password == ''))
		 {
			header('refresh:0; url=login.php');
			echo "<script> window.alert('密码或账号为空，请检查！')</script>";
			exit;
		} 
		else
		{
			for($i=0;$i<$allof;$i++)
			{
				if (($username = $usrnm[$i]) && ($password = $paswrd[$i])) 
				{
					$_SESSION['username'] = $username;
					$_SESSION['islogin'] = 114514;
					if ($_POST['remember'] == "yes") 
					{
						setcookie('username', $username, time()+7*24*60*60);
						setcookie('code', md5($username.md5($password)), time()+7*24*60*60);
					} 
					else
					 {
						setcookie('username', '', time()-999);
						setcookie('code', '', time()-999);
					}
					header('location:index.php');
				}
			}
		}
		header('refresh:0; url=login.php');
		echo "<script> window.alert('密码或账号存在问题，请检查！')</script>";
		exit;
		}
	}
 ?>
 <head>
    <meta charset="utf-8">
     <title>验证</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />    
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0, user-scalable=no minimal-ui">
	<link rel="stylesheet" type="text/css" href="/gx/page/css/bootstrap.min.css">
	<link rel="stylesheet" type="text/css" href="gx/page/css/font-awesome.min.css">
	<link rel="stylesheet" type="text/css" href="gx/page/css/material-design-iconic-font.min.css">
	<link rel="stylesheet" type="text/css" href="gx/page/css/util.css">
	<link rel="icon" href="tx2.png">
	<link rel="stylesheet" type="text/css" href="gx/page/css/main2.css">
	<body>
	<script type="text/javascript">
	function displayAlert(type, data, time){

    var lunbo=document.createElement("div");
    
      if(type == "success") {
          lunbo.style.backgroundColor = "#009900";
      } else if(type == "error") {
          lunbo.style.backgroundColor = "#990000";
      } else if(type == "info") {
          lunbo.style.backgroundColor = " #e6b800";
      } else {
          console.log("入参type错误");
          return;
      }

      lunbo.id="lunbo";
      lunbo.style.position = "absolute";
      lunbo.style.width = "200px";
      lunbo.style.height = "60px";
      lunbo.style.marginLeft = "-100px";
      lunbo.style.marginTop = "-30px";
      lunbo.style.left = "50%";
      lunbo.style.top = "20%";
      lunbo.style.color = "white";
      lunbo.style.fontSize = "25px";
      lunbo.style.borderRadius = "20px";
      lunbo.style.textAlign="center";
      lunbo.style.lineHeight="60px";

      if(document.getElementById("lunbo")==null){
          document.body.appendChild(lunbo);
          lunbo.innerHTML=data;
          setTimeout(function(){
              document.body.removeChild(lunbo);
          } ,time);
      }
    }
    function t3() {
        displayAlert("error", "禁用ctrl+u", 1500);
    }
    function t4() {
        displayAlert("error", "禁用ctrl+s", 1500);
    }
    function test1() {
        displayAlert("error", "禁用F12", 1500);
    }
    function test2() {
        displayAlert("error", "禁用ctrl+shift+i", 1500);
    }
    
        window.onload=function(){
        document.onkeydown=function(){
        var e = window.event||arguments[0];
        if(e.keyCode==123){
            //F12
            test1();
            return false;
        }else if((e.ctrlKey)&&(e.shiftKey)&&(e.keyCode==73)){
            //ctrl + shift + i
            test2();
            return false;
        }else if((e.ctrlKey)&&(e.keyCode==85)){
            //ctrl + U
            t3();
            return false;
        }else if((e.ctrlKey)&&(e.keyCode==83)){
            //ctrl + U
            t4();
            return false;
        }
    }
    document.oncontextmenu=function(){
        return false;
    }
}
    window.addEventListener("contextmenu", ev => ev.preventDefault())
    window.addEventListener("keydown", ev => ev.key === "F12" && ev.preventDefault())
    
setInterval(function() {
    check()
}, 4000);

if(window.location.href.indexOf('#debug')==-1){
  setInterval(function(){
    (function (a) {return (function (a) {return (Function('Function(arguments[0]+"' + a + '")()'))})(a)})('bugger')('de', 0, 0, (0, 0));
  }, 100);
}
        </script>
    </body>
    <body onselectstart = "return false" ></body>
    <body oncontextmenu = "return false" ></body>
    <style>
		.div_show
        {
		display:block;
    	text-align: left;
		}
		.div_hide{
		display:none;
		}

	</style>
</head>
<div class="limiter">
		<div class="container-login100">
			<div class="wrap-login100 p-l-55 p-r-55 p-t-65 p-b-54">
                <form method="post" class="login100-form validate-form" action="login.php" >
                    <span class="login100-form-title p-b-10">验证</span>
                    <span  style="text-align: center;display:block;">输入账号密码以验证</span>
                    <div class="wrap-input100 validate-input" data-validate="账号">
						    <span class="label-input100"></span>
						    <input class="input100" type="text" name="username"  placeholder="账号">
					</div>
					<div class="wrap-input100 validate-input" data-validate="请键入密码">
						<span class="label-input100"></span>

						<input class="input100" type="password" name="password" placeholder="请输入密码">
						<span class="focus-input100" data-symbol=""></span>
					</div>
					<span class="label-input100"></span>
				<div class="container-login100-form-btn">
					<div class="wrap-login100-form-btn">
						<div class="login100-form-bgbtn"></div>
						<button type="submit" name="login" class="login100-form-btn">立即进入</button>
					</div>
					
				</div>
				
	        </form>
	        
	       </div>
	       </div>
	       </div>
        
</div>