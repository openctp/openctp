# -*- coding: utf-8 -*-
import thosttraderapi
import sys

'''
written by krenx on 2023-1-10.
published in openctp@github: https://github.com/krenx1983/openctp/tree/master/ctpapi-python
'''


class CTdSpiImpl(thosttraderapi.CThostFtdcTraderSpi):
	def __init__(self, api):
		thosttraderapi.CThostFtdcTraderSpi.__init__(self)
		self.api = api
		
	def OnFrontConnected(self) -> "void":
		print("OnFrontConnected")
		req = api.CThostFtdcReqAuthenticateField()
		req.BrokerID = brokerid
		req.UserID = user
		req.AppID = appid
		authfield.AuthCode = authcode
		self.api.ReqAuthenticate(req, 0)

	def OnFrontDisconnected(self, nReason: 'int') -> "void":
		print("OnFrontDisconnected")

	def OnRspAuthenticate(self, pRspAuthenticateField: 'CThostFtdcRspAuthenticateField', pRspInfo: 'CThostFtdcRspInfoField', nRequestID: 'int', bIsLast: 'bool') -> "void":
		print(f"OnRspAuthenticate: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}")

		if pRspInfo.ErrorID != 0:
			req = api.CThostFtdcReqUserLoginField()
			req.BrokerID = brokerid
			req.UserID = user
			req.Password = password
			req.UserProductInfo = "openctp"
			self.api.ReqUserLogin(req, 0)
		
	def OnRspUserLogin(self, pRspUserLogin: 'CThostFtdcRspUserLoginField', pRspInfo: 'CThostFtdcRspInfoField', nRequestID: 'int', bIsLast: 'bool') -> "void":
		print(f"OnRspUserLogin: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}, TradingDay={pRspUserLogin.TradingDay}")

		req = api.CThostFtdcSettlementInfoConfirmField()
		req.BrokerID = brokerid
		req.InvestorID = user
		self.api.ReqSettlementInfoConfirm(req, 0)
		
	def OnRspSettlementInfoConfirm(self, pSettlementInfoConfirm: 'CThostFtdcSettlementInfoConfirmField', pRspInfo: 'CThostFtdcRspInfoField', nRequestID: 'int', bIsLast: 'bool') -> "void":
		print(f"OnRspUserLogin: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}")
		req = api.CThostFtdcQryInstrumentField()
		req.BrokerID = brokerid
		req.InvestorID = user
		self.api.ReqQryInstrument(req, 0)

	def OnRtnOrder(self, pOrder: 'CThostFtdcOrderField') -> "void":
		print("OnRtnOrder: InstrumentID={pOrder.InstrumentID}, ExchangeID={pOrder.ExchangeID}, VolumeTotalOriginal={pOrder.VolumeTotalOriginal}, VolumeTraded={pOrder->VolumeTraded}, LimitPrice={pOrder.LimitPrice}, OrderStatus={pOrder.OrderStatus}, OrderSysID={pOrder.OrderSysID}, FrontID={pOrder.FrontID}, SessionID={pOrder.SessionID}, OrderRef={pOrder.OrderRef}")

	def OnRtnTrade(self, pTrade: 'CThostFtdcTradeField') -> "void":
		print("OnRtnTrade: InstrumentID={pTrade.InstrumentID}, ExchangeID={pTrade.ExchangeID}, Volume={pTrade.Volume}, Price={pTrade.Price}, OrderSysID={pTrade.OrderSysID}, OrderRef={pTrade.OrderRef}")

	def OnRspOrderInsert(self, pInputOrder: 'CThostFtdcInputOrderField', pRspInfo: 'CThostFtdcRspInfoField', nRequestID: 'int', bIsLast: 'bool') -> "void":
		print(f"OnRspOrderInsert: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}")

	
if __name__ == '__main__':
	usage = "ctpprint tcp://180.168.146.187:10130 9999 0000000000000000 simnow_client_test 000001 123456 ..."
	if len(sys.argv) != 7:
		print(usage)
		sys.exit(1)

	tdfront = sys.argv[1]
	brokerid = sys.argv[2]
	authcode = sys.argv[3]
	appid = sys.argv[4]
	user = sys.argv[5]
	password = sys.argv[6]
	
	tdapi = thosttraderapi.CThostFtdcTraderApi.CreateFtdcTraderApi(user)
	tdspi = CTdSpiImpl(tdapi)
	tdapi.RegisterSpi(tdspi)
	tdapi.SubscribePrivateTopic(thosttraderapi.THOST_TERT_QUICK)
	tdapi.SubscribePublicTopic(thosttraderapi.THOST_TERT_QUICK)
	tdapi.RegisterFront(tdfront)
	tdapi.Init()
	
	print("press Enter key to exit ...")
	input()

