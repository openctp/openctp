# ctpcmd

ctpcmd是openctp开发的一套命令行程序化交易工具链，包括ctporder、ctpprice、ctpoptorder、ctpoptprice等命令，从命令行选项获取参数调用CTPAPI发起请求，将响应信息以Json文本形式输出到命令行，可以通过bat、bash、Python等脚本语言结合基础命令编写出强大的策略或自动化工具。

## [ctporder、ctpoptorder](https://github.com/openctp/openctp/tree/master/tools/ctpcmd/ctpcmd)

CTP及CTP股票期权柜台交易命令，支持查询资金、持仓、订单、合约、行情等数据，也支持自然语言式下单撤单，如：

```shell
ctporder buy open 1 share of SHFE.fu2701 at 3500.0
ctporder sell close 3 shares of CZCE.MA701 at market
ctporder cancel "    157620" of CFFEX.IF2612
```

## [ctpprice、ctpoptprice](https://github.com/openctp/openctp/tree/master/tools/ctpcmd/ctpcmd)

CTP及CTP股票期权柜台报价命令，支持查询行情、订阅行情，支持一次查询/订阅多个合约，如：

```shell
ctpprice query CFFEX.IF2612,SHFE.ag2701,MA701,i2612
ctpprice subscribe fu2701,rb2612,cu2701,AP612
```
