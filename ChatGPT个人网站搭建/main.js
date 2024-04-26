const { createApp } = Vue
        createApp({
        data() {
            return {
                api: \'\',
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
                this.sentext = \'请求中\'
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