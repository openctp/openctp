<template>
  <div style="padding:5px">
    合约：<vxe-input v-model="inputText" />
    <vxe-button @click="handleCusMarketData">订阅</vxe-button>
    <vxe-button
      v-if="!isLogin"
      @click="websocketonopen"
    >登陆</vxe-button>
  </div>
  <div class="cell-color">
    <!-- <button @click="handleMarketData">订阅行情</button> -->
    <button @click="handleUnMarketData">取消订阅行情</button>
  </div>
  <div
    class="cell-color"
    style="paading-left:5px"
  >行情</div>
  <div>
    <vxe-table
      border
      :data="list"
    >
      <vxe-column
        v-for="item in columns"
        :key="item.key"
        :field="item.key"
        :title="item.title"
        :minWidth="item.minWidth"
        :align="item.align"
      ></vxe-column>
    </vxe-table>
  </div>
</template>

<script>
// const { dialog } = require('electron')
// import { dialog } from 'electron'
import { errMessage } from "../dialog.js"
export default {
  data() {
    return {
      websock: null,
      columns: [
        {
          title: "代码",
          key: "InstrumentID",
          minWidth: 60,
          align: "center"
        },
        {
          title: "交易所",
          key: "ExchangeID",
          minWidth: 60,
          align: "center"
        },
        {
          title: "名称",
          key: "ExchangeInstID",
          minWidth: 60,
          align: "center"
        },
        {
          title: "最新价",
          key: "LastPrice",
          minWidth: 60,
          align: "center"
        },
        {
          title: "成交量",
          key: "Volume",
          minWidth: 60,
          align: "center"
        },
        {
          title: "开盘价",
          key: "OpenPrice",
          minWidth: 60,
          align: "center"
        },
        {
          title: "最高价",
          key: "HighestPrice",
          minWidth: 60,
          align: "center"
        },
        {
          title: "最低价",
          key: "LowestPrice",
          minWidth: 60,
          align: "center"
        },
        {
          title: "买1价",
          key: "BidPrice1",
          minWidth: 60,
          align: "center"
        },
        {
          title: "买1量",
          key: "BidVolume1",
          minWidth: 60,
          align: "center"
        },
        {
          title: "卖1价",
          key: "AskPrice1",
          minWidth: 60,
          align: "center"
        },
        {
          title: "卖1量",
          key: "AskVolume1",
          minWidth: 60,
          align: "center"
        },
        {
          title: "时间",
          key: "UpdateTime",
          minWidth: 60,
          align: "center"
        }
      ],
      inputText: "",
      marketData: [],
      list: [],
      isLogin: false,
    }
  },
  mounted() {
    !this.isLogin && this.initWebSocket();
  },
  onBeforeUnmount() {
    this.websock.close();
  },
  methods: {
    initWebSocket() { //初始化weosocket
      const wsuri = "ws://121.37.86.17:15000/md/";
      this.websock = new WebSocket(wsuri);
      this.websock.onmessage = this.websocketonmessage;
      this.websock.onopen = this.websocketonopen;
      this.websock.onerror = this.websocketonerror;
      this.websock.onclose = this.websocketclose;
    },
    websocketonerror(e) {//连接建立失败重连
      console.log('websocketonerror', e);
      this.isLogin = false;
      let option = {
        title: "登陆失败啦",                            // 通知标题
        body: "登陆失败啦，请重新登陆",                               // 内容
        icon: "../favicon.ico",                                 // 图标
        // href: 'https://www.cnblogs.com/binglicheng/'            // 地址
      };
      // 创建通知并保存
      let hhwNotication = new window.Notification(option.title, option);
      // 当通知被点击时
      hhwNotication.onclick = function () {
        // TODO something...
        this.websocketonopen()
      }

      // this.initWebSocket();
    },
    websocketonmessage(e) { //数据接收
      const redata = JSON.parse(e.data);
      console.log("接受数据啦", redata.MsgType)
      if (redata.MsgType == "OnRtnDepthMarketData") {
        let tempIndex = this.list.findIndex(item => item.InstrumentID == redata.DepthMarketData.InstrumentID)
        if (tempIndex > -1) {
          this.list.map(item => {
            if (item.InstrumentID == redata.DepthMarketData.InstrumentID) {
              for (let key in item) {
                item[key] = redata.DepthMarketData[key]
              }
            }
          })
        } else {
          // this.list = this.list.filter(item => item.InstrumentID != redata.DepthMarketData.InstrumentID)
          this.list.push(redata.DepthMarketData)
        }

        console.log("this.list", this.list)
      }
      if (redata.MsgType == "OnRspUserLogin") {
        console.log("ppppp")
        this.isLogin = true;
      }
    },
    websocketsend(Data) {//数据发送
      this.websock.send(Data);
    },
    websocketclose(e) {  //关闭
      console.log('断开连接', e);
      let option = {
        title: "链接断开啦",
        body: "有可能是服务关闭了，请开启服务哦",
        icon: "../favicon.ico",
        // href: 'https://www.cnblogs.com/binglicheng/'            // 地址
      };
      // 创建通知并保存
      let hhwNotication = new window.Notification(option.title, option);
      // 当通知被点击时
      hhwNotication.onclick = function () {
        // TODO something...
      }
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
    handleMarketData() {
      let actions = {
        "MsgType": "SubscribeMarketData",
        "InstrumentID": ["ag2307", "ag2312", "TA305"]
      }
      this.websocketsend(JSON.stringify(actions));
    },
    handleUnMarketData() {
      let tempArray = [];
      this.list.map(item => {
        tempArray.push(item.InstrumentID)
      })
      let actions = {
        "MsgType": "UnSubscribeMarketData",
        "InstrumentID": tempArray
      }
      this.websocketsend(JSON.stringify(actions));
    },
    handleCusMarketData() {
      if (this.inputText.length == 0) {
        errMessage("请输入合约")
      }
      let actions = {
        "MsgType": "SubscribeMarketData",
        "InstrumentID": [this.inputText]
      }
      this.websocketsend(JSON.stringify(actions));
    },
    handleClose() {
      this.websock.close()
    }
  }
}
</script>

<style >
.cell-color {
  background-color: rgb(68, 82, 102) !important;
  margin-top: 5px;
  padding: 0 5px;
}
.vxe-table--header-wrapper {
  color: white !important;
  background-color: rgb(68, 82, 102) !important;
}
.vxe-header--column {
  padding: 5px 0 !important;
}
.vxe-cell {
  padding: 0 3px !important;
}
.vxe-table--body-wrapper {
  background-color: black !important;
  color: white !important;
}
</style>