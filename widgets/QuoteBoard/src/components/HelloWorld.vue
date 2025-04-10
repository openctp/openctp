<template>
  <div class="hello">
    <button @click="handleInstrCommRate">查询期权合约手续费</button>
    <button @click="handleInstrTradeCost">查询期权交易成本</button>
    <button @click="handleMarketData">查询行情</button>
    <button @click="handleInstrument">查询合约</button>
    <button @click="handleClose">断开链接</button>
    
  </div>
</template>

<script>
export default {
  name: 'HelloWorld',
  props: {
    msg: String
  },
  data() {
    return {
      websock: null
    }
  },
  mounted() {
    this.initWebSocket();
  },
  methods: {
    initWebSocket() { //初始化weosocket
      const wsuri = "ws://121.37.86.17:15000/td/";
      this.websock = new WebSocket(wsuri);
      this.websock.onmessage = this.websocketonmessage;
      this.websock.onopen = this.websocketonopen;
      this.websock.onerror = this.websocketonerror;
      this.websock.onclose = this.websocketclose;
    },
    websocketonerror(e) {//连接建立失败重连
      console.log('websocketonerror', e);
      // this.initWebSocket();
    },
    websocketonmessage(e) { //数据接收
      const redata = JSON.parse(e.data);
      console.log("接受数据啦", redata)
    },
    websocketsend(Data) {//数据发送
      this.websock.send(Data);
    },
    websocketclose(e) {  //关闭
      console.log('断开连接', e);
    },
    websocketonopen() { //连接建立之后执行send方法发送数据
      let actions = {
        "MsgType": "ReqUserLogin",
        "ReqUserLogin": {
          "UserID": "1014",
          "Password": "123456"
        }
      }
      console.log("111111")
      this.websocketsend(JSON.stringify(actions));
    },
    //查询期权合约手续费
    handleInstrCommRate() {
      let actions = {
        "MsgType": "ReqQryOptionInstrCommRate",
        "QryOptionInstrCommRate": {
          "BrokerID": "9999",
          "InvestorID": "1014",
          "InstrumentID": "m2309-C-3000"
        },
        "RequestID": 0
      }
      console.log("22222")
      this.websocketsend(JSON.stringify(actions));
    },
    handleInstrTradeCost() {
      let actions = {
        "MsgType": "ReqQryOptionInstrTradeCost",
        "QryOptionInstrTradeCost": {
          "BrokerID": "9999",
          "InvestorID": "1014",
          "InstrumentID": "m2309-C-3000",
          "HedgeFlag": "1",
          "InputPrice": 123.2,
          "UnderlyingPrice": 0
        },
        "RequestID": 0
      }
      console.log("333333")
      this.websocketsend(JSON.stringify(actions));
    },
    //查询行情
    handleMarketData() {
      let actions = {
        "MsgType": "ReqQryDepthMarketData",
        "QryDepthMarketData": {
          "InstrumentID": "m2309",
          "ExchangeID": "DCE"
        },
        "RequestID": 0
      }
      console.log("444")
      this.websocketsend(JSON.stringify(actions));
    },
    //查询合约
    handleInstrument() {
      let actions = {
        "MsgType": "ReqQryInstrument",
        "QryInstrument": {
          "ExchangeID": "",
          "ExchangeInstID": "",
          "InstrumentID": "",
          "ProductID": ""
        },
        "RequestID": 0
      }
      this.websocketsend(JSON.stringify(actions));
    },
    handleClose() {
      this.websock.close()
    }
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
</style>
