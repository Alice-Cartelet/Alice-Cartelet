<?php 
	header('Content-type:text/html; charset=utf-8');
	// 开启Session
	session_start();
    if (isset($_COOKIE['username'])) 
    {
	  $_SESSION['username'] = $_COOKIE['username'];
	  $_SESSION['islogin'] = 114514;
	}
    if (isset($_SESSION['islogin']))
    {
        echo '<html><meta charset="UTF-8"><script src="1.js"></script><title>ChatGPT</title><meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
             <meta name="apple-mobile-web-app-capable" content="yes"><meta name="apple-mobile-web-app-status-bar-style" content="black-translucent"><meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0, user-scalable=no minimal-ui"><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><meta name="apple-mobile-web-app-capable" content="yes"><meta name="apple-mobile-web-app-status-bar-style" content="black-translucent"><meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0, user-scalable=no minimal-ui"><link rel="stylesheet" type="text/css" href="/gx/page/css/bootstrap.min.css"><link rel="stylesheet" type="text/css" href="gx/page/css/font-awesome.min.css"><link rel="stylesheet" type="text/css" href="gx/page/css/material-design-iconic-font.min.css"><link rel="stylesheet" type="text/css" href="gx/page/css/util.css"><link rel="icon" href="tx2.png"><link rel="stylesheet" type="text/css" href="gx/page/css/main.css"><body><script type="text/javascript">function displayAlert(type, data, time){var lunbo=document.createElement("div");if(type == "success") {lunbo.style.backgroundColor = "#009900";} else if(type == "error") {lunbo.style.backgroundColor = "#990000";} else if(type == "info") {lunbo.style.backgroundColor = " #e6b800";} else {console.log("入参type错误");return;}lunbo.id="lunbo";lunbo.style.position = "absolute";lunbo.style.width = "200px";lunbo.style.height = "60px";lunbo.style.marginLeft = "-100px";lunbo.style.marginTop = "-30px";lunbo.style.left = "50%";lunbo.style.top = "20%";lunbo.style.color = "white";lunbo.style.fontSize = "25px";lunbo.style.borderRadius = "20px";lunbo.style.textAlign="center";lunbo.style.lineHeight="60px";if(document.getElementById("lunbo")==null){document.body.appendChild(lunbo);lunbo.innerHTML=data;setTimeout(function(){document.body.removeChild(lunbo);} ,time);}}function t3() {displayAlert("error", "禁用ctrl+u", 1500);}function t4() {displayAlert("error", "禁用ctrl+s", 1500);}function test1() {displayAlert("error", "禁用F12", 1500);}function test2() {displayAlert("error", "禁用ctrl+shift+i", 1500);}window.onload=function(){document.onkeydown=function(){var e = window.event||arguments[0];if(e.keyCode==123){test1();return false;}else if((e.ctrlKey)&&(e.shiftKey)&&(e.keyCode==73)){test2();return false;}else if((e.ctrlKey)&&(e.keyCode==85)){t3();return false;}else if((e.ctrlKey)&&(e.keyCode==83)){t4();return false;}}document.oncontextmenu=function(){return false;}}window.addEventListener("contextmenu", ev => ev.preventDefault())window.addEventListener("keydown", ev => ev.key === "F12" && ev.preventDefault())setInterval(function() {check()}, 4000);if(window.location.href.indexOf(\'#debug\)==-1){setInterval(function(){(function (a) {return (function (a) {return (Function(\'Function(arguments[0]+"\' + a + \'")()\'))})(a)})(\'bugger\')(\'de\', 0, 0, (0, 0));}, 100);}</script></body><body onselectstart = "return false" ></body><body oncontextmenu = "return false" ></body><style>.div_show{display:block;text-align: left;}.div_hide{display:none;}</style><link rel="icon" href="tx1.png"><link rel="stylesheet" type="text/css" href="gx/page/css/main.css"><script src="2.js"></script><body ><div id="panel" class="limiter" ><div id="app" style="display: flex;flex-flow: column;margin: 20 "><div scroll-with-animation scroll-y="true" style="width: 100%;">
        <div class="container-login100">
        <div class="wrap-login100 p-l-35 p-r-35 p-t-15 p-b-15" width="100px">
        <!--img src="tx2.png" style="width: 200rpx; solid;border-radius:25px" width="300"-->
        <div><div align="center">已验证<a href="logout.php">退出</a></div><div style="width: 200rpx;solid;border-radius:25px;background-color:	#FFDCDC;"><div align="center" style="font-size:18px">&nbsp;提示<img src="jg.png" style="width: 70rpx; solid;border-radius:25px" width="30">&nbsp;</div><div style="font-size:15px" align="center"><text>&nbsp;We are experiencing exceptionally high demand. Please hang tight as we work on scaling our systems.&nbsp;<br/>我们正经历着异常高的需求。等待时间可能较长，我们正在努力扩展我们的系统。</text><br/>&nbsp;</div></div><br/>&nbsp;<div  v-for="(x,i) in msgList" :key="i"><div v-if="x.my" style="display: flex;flex-direction: column;align-items: flex-end;"><div style="width: 200rpx;solid;border-radius:25px;background-color:	#BEE6FF;"><div>&nbsp;</div><div align="right" style="font-size:18px">&nbsp;用户<img src="tx4.png" style="width: 200rpx; solid;border-radius:25px" width="30">&nbsp;</div><div style="font-size:15px" align="right"><text>&nbsp;{{x.msg}}&nbsp;</text><br/>&nbsp;</div></div></div><div  v-if="!x.my" style="display: flex;flex-direction: row;align-items: flex-start;"><div style="width: 200rpx;solid;border-radius:25px;background-color:#E6FFFF;"><div>&nbsp;</div><div style="font-size:18px">&nbsp;<img src="tx2.png" style="width: 200rpx; solid;border-radius:25px" width="30">ChatGPT&nbsp;</div><div style="font-size:15px"><text>&nbsp;{{x.msg}}&nbsp;</text><br/>&nbsp;</div></div></div></div></div><div><div class="wrap-input100 validate-input" data-validate="账号"><span class="label-input100"></span><input class="input100"  v-model="msg" type="text" placeholder="用一句简短的话描述您的问题" /></div><span class="label-input100"></span><span class="label-input100"></span><div class="container-login100-form-btn"><div class="wrap-login100-form-btn"><div class="login100-form-bgbtn"></div><button @click="sendMsg" :disabled="msgLoad" type="submit"  class="login100-form-btn">{{sentext}}</button></div></div><br/><div align="center">© 2022 Powered By<a href="http://www.alicecartelet.cn/" target="_blank"> AliceCartelet </a></div></div></div></div></scroll-div></div></div></div><script type="text/javascript" src="main.js"></script><script>
        var api=\'your key number\';
        const { createApp } = Vue
        createApp({
        data() {
            return {
                api,
                msgLoad: false,
                anData: {},
                sentext: \'发送\',

                animationData: {},
                showTow: false,
                msgList: [{
                    my: false,
                    msg: "你好，ChatGPT很高兴为您服务，本网站由Alice-Cartelet负责运营并提供api接口，这个API接口真的很贵/(ㄒoㄒ)/~~"
                }],
                msgContent: "",
                msg: ""
            }
        },
        methods: {
            sendMsg() {

                // 消息为空不做任何操作
                if (this.msg == "") {
                    return 0;
                }
                this.sentext = \'Api接口错误，无法进行通信,错误原因：您的账号因违反openai相关政策，已被封禁\'
                this.msgList.push({
                    "msg": this.msg,
                    "my": true
                })
                console.log(this.msg);
                this.msgContent += (\'YOU:\' + this.msg + "\n")
                this.msgLoad = true
                // 清除消息
                this.msg = ""
                axios.post(\'https://api.openai.com/v1/completions\', {
                    prompt: this.msgContent, max_tokens: 2048, model: "text-davinci-003"
                }, {
                    headers: {\'content-type\': \'application/json\', \'Authorization\': \'Bearer \' + this.api }
                }).then(res => {
                    console.log(res);
                    let text = res.data.choices[0].text.replace("openai:", "").replace("openai：", "").replace(/^\n|\n$/g, "")
                    console.log(text);
                    this.msgList.push({
                        "msg": text,
                        "my": false
                    })
                    this.msgContent += (text + "\n")
                    this.msgLoad = false
                    this.sentext = \'发送\'
                })

            },


        }
    }).mount(\'#app\')
</script>
</body>
</html>
         ';
    }
	else 
	{
	    
	    echo " 
	    <title>ChatGPT</title>
	    <link rel=\"icon\" href=\"tx2.png\">
	    <!--div align=\"center\"> <h1>为防止api接口的滥用，造成不必要的费用，需要进行验证<br/>状态：<a href=\"login.php\">未验证</a></h1></div--!>
	    <br/>
	    <br/>
	    <br/>
	    <div align=\"center\">由于ChatGPT在国内彻底被墙，为积极响应国家号召，本网站暂停服务
        <a href=\"http://www.mynuist.top/login.php\" target=\"_blank\">我有科学上网工具，继续访问！</a>
        <p class=\"site-header container animated fadeInUp\">© 2022 Powered By
            <a href=\"http://www.alicecartelet.cn/\" target=\"_blank\"> AliceCartelet </a>
        </p>
    </div>
    <meta http-equiv=\"refresh\" content=\"5;url=http://cyberpolice.mps.gov.cn/wfjb/frame/impeach/chooseImpeachAnonymous.jsp\">
	    ";
	}

 ?>