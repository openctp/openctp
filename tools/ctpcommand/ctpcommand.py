# -*- coding: utf-8 -*-

"""
author: krenx@openctp.
last modify: 2024/7/13
"""

import sys
import threading
from openctp_ctp import tdapi
# import thosttraderapi as tdapi

class CTPCommand(tdapi.CThostFtdcTraderSpi):
    def __init__(self, host, broker, user, password, appid, authcode):
        self.broker = broker
        self.user = user
        self.password = password
        self.appid = appid
        self.authcode = authcode

        self.TradingDay = ""
        self.FrontID = 0
        self.SessionID = 0
        self.OrderRef = 0

        self.Accountregister = tdapi.CThostFtdcAccountregisterField()

        tdapi.CThostFtdcTraderSpi.__init__(self)
        self.api: tdapi.CThostFtdcTraderApi = tdapi.CThostFtdcTraderApi.CreateFtdcTraderApi()
        self.api.RegisterSpi(self)
        self.api.RegisterFront(host)
        self.api.SubscribePrivateTopic(tdapi.THOST_TERT_QUICK)
        self.api.SubscribePublicTopic(tdapi.THOST_TERT_QUICK)

    def Run(self):
        self.api.Init()

    def QryInstrument(self, exchangeid, productid, instrumentid):
        req = tdapi.CThostFtdcQryInstrumentField()
        req.ExchangeID = exchangeid
        req.ProductID = productid
        req.InstrumentID = instrumentid
        self.api.ReqQryInstrument(req, 0)

    def QryExchange(self):
        req = tdapi.CThostFtdcQryExchangeField()
        self.api.ReqQryExchange(req, 0)

    def QryProduct(self, ExchangeID, ProductID):
        req = tdapi.CThostFtdcQryProductField()
        req.ExchangeID = ExchangeID
        req.ProductID = ProductID
        self.api.ReqQryProduct(req, 0)

    def QryPrice(self, ExchangeID, InstrumentID):
        req = tdapi.CThostFtdcQryDepthMarketDataField()
        req.ExchangeID = ExchangeID
        req.InstrumentID = InstrumentID
        self.api.ReqQryDepthMarketData(req, 0)

    def QryInvestor(self):
        req = tdapi.CThostFtdcQryInvestorField()
        req.BrokerID = self.broker
        self.api.ReqQryInvestor(req, 0)

    def QryAccount(self):
        req = tdapi.CThostFtdcQryTradingAccountField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        self.api.ReqQryTradingAccount(req, 0)

    def QryPosition(self, InstrumentID):
        req = tdapi.CThostFtdcQryInvestorPositionField()
        req.InvestorID = self.user
        req.BrokerID = self.broker
        req.InstrumentID = InstrumentID
        self.api.ReqQryInvestorPosition(req, 0)

    def QryPositionDetail(self, InstrumentID):
        req = tdapi.CThostFtdcQryInvestorPositionDetailField()
        req.InvestorID = self.user
        req.BrokerID = self.broker
        req.InstrumentID = InstrumentID
        self.api.ReqQryInvestorPositionDetail(req, 0)

    def QryOrder(self, InstrumentID):
        req = tdapi.CThostFtdcQryOrderField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        req.InstrumentID = InstrumentID
        self.api.ReqQryOrder(req, 0)

    def QryTrade(self, InstrumentID):
        req = tdapi.CThostFtdcQryTradeField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        req.InstrumentID = InstrumentID
        self.api.ReqQryTrade(req, 0)

    def QryCommissionRate(self, ExchangeID, InstrumentID):
        req = tdapi.CThostFtdcQryInstrumentCommissionRateField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        req.ExchangeID = ExchangeID
        req.InstrumentID = InstrumentID
        self.api.ReqQryInstrumentCommissionRate(req, 0)

    def QryMarginRate(self, ExchangeID, InstrumentID, HedgeFlag):
        req = tdapi.CThostFtdcQryInstrumentMarginRateField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        req.ExchangeID = ExchangeID
        req.InstrumentID = InstrumentID
        req.HedgeFlag = HedgeFlag
        self.api.ReqQryInstrumentMarginRate(req, 0)

    def QryOrderCommRate(self, InstrumentID):
        req = tdapi.CThostFtdcQryInstrumentOrderCommRateField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        req.InstrumentID = InstrumentID
        self.api.ReqQryInstrumentOrderCommRate(req, 0)

    def QryOptionInstrCommRate(self, ExchangeID, InstrumentID):
        req = tdapi.CThostFtdcQryOptionInstrCommRateField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        req.ExchangeID = ExchangeID
        req.InstrumentID = InstrumentID
        self.api.ReqQryOptionInstrCommRate(req, 0)

    def QryTradingCode(self):
        req = tdapi.CThostFtdcQryTradingCodeField()
        self.api.ReqQryTradingCode(req, 0)

    def QrySettlementInfo(self, TradingDay):
        req = tdapi.CThostFtdcQrySettlementInfoField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        req.TradingDay = TradingDay
        self.api.ReqQrySettlementInfo(req, 0)

    def ConfirmSettlementInfo(self):
        req = tdapi.CThostFtdcSettlementInfoConfirmField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        self.api.ReqSettlementInfoConfirm(req, 0)

    def OrderInsert(self, ExchangeID, InstrumentID, Direction, Offset, PriceType, Price, Volume, TimeCondition, VolumeCondition, MinVolume):
        req = tdapi.CThostFtdcInputOrderField()
        req.BrokerID = self.broker
        req.UserID = self.user
        req.InvestorID = self.user
        req.ExchangeID = ExchangeID
        req.InstrumentID = InstrumentID
        req.Direction = Direction
        req.CombOffsetFlag = Offset
        req.CombHedgeFlag = tdapi.THOST_FTDC_HF_Speculation
        req.OrderPriceType = PriceType
        if Price != "":
            req.LimitPrice = float(Price)
        if Volume != "":
            req.VolumeTotalOriginal = int(Volume)
        req.TimeCondition = TimeCondition
        req.VolumeCondition = VolumeCondition
        if MinVolume != "":
            req.MinVolume = int(MinVolume)
        req.OrderRef = str(self.OrderRef)
        self.OrderRef = self.OrderRef + 1
        req.ForceCloseReason = tdapi.THOST_FTDC_FCC_NotForceClose
        req.ContingentCondition = tdapi.THOST_FTDC_CC_Immediately
        self.api.ReqOrderInsert(req, 0)

    def OrderCancel(self, ExchangeID, InstrumentID, OrderSysID, FrontID, SessionID, OrderRef):
        req = tdapi.CThostFtdcInputOrderActionField()
        req.BrokerID = self.broker
        req.UserID = self.user
        req.InvestorID = self.user
        req.ExchangeID = ExchangeID
        req.InstrumentID = InstrumentID
        req.OrderSysID = OrderSysID
        if FrontID != "":
            req.FrontID = int(FrontID)
        if SessionID != "":
            req.SessionID = int(SessionID)
        req.OrderRef = OrderRef
        req.ActionFlag = tdapi.THOST_FTDC_AF_Delete
        self.api.ReqOrderAction(req, 0)

    def QryContractBank(self):
        req = tdapi.CThostFtdcQryContractBankField()
        self.api.ReqQryContractBank(req, 0)

    def QryTransferSerial(self):
        req = tdapi.CThostFtdcQryTransferSerialField()
        self.api.ReqQryTransferSerial(req, 0)

    def QryAccountRegister(self):
        req = tdapi.CThostFtdcQryAccountregisterField()
        self.api.ReqQryAccountregister(req, 0)

    def QueryBankAccount(self, Password):
        if self.Accountregister.AccountID == "":
            print("please Query AccountRegister first.")
            return

        req = tdapi.CThostFtdcReqQueryAccountField()
        req.TradeCode = "204002"
        req.AccountID = self.Accountregister.AccountID
        req.BankID = self.Accountregister.BankID
        req.BankBranchID = self.Accountregister.BankBranchID
        req.BankAccount = self.Accountregister.BankAccount
        req.BankAccType = self.Accountregister.BankAccType
        req.BrokerID = self.Accountregister.BrokerID
        req.BrokerBranchID = self.Accountregister.BrokerBranchID
        req.IdCardType = self.Accountregister.IdCardType
        req.IdentifiedCardNo = self.Accountregister.IdentifiedCardNo
        req.CurrencyID = self.Accountregister.CurrencyID
        req.Password = Password
        self.api.ReqQueryBankAccountMoneyByFuture(req, 0)

    def MoneyTransferToCTP(self, Amount, Password):
        req = tdapi.CThostFtdcReqTransferField()
        req.TradeCode = "202001"
        req.AccountID = self.Accountregister.AccountID
        req.BankID = self.Accountregister.BankID
        req.BankBranchID = self.Accountregister.BankBranchID
        req.BankAccount = self.Accountregister.BankAccount
        req.BankAccType = self.Accountregister.BankAccType
        req.BrokerID = self.Accountregister.BrokerID
        req.BrokerBranchID = self.Accountregister.BrokerBranchID
        req.IdCardType = self.Accountregister.IdCardType
        req.IdentifiedCardNo = self.Accountregister.IdentifiedCardNo
        req.CustType = self.Accountregister.CustType
        req.VerifyCertNoFlag = tdapi.THOST_FTDC_YNI_No
        req.SecuPwdFlag = tdapi.THOST_FTDC_BPWDF_BlankCheck
        req.TradeAmount = Amount
        req.CurrencyID = self.Accountregister.CurrencyID
        req.Password = Password
        self.api.ReqFromBankToFutureByFuture(req, 0)

    def MoneyTransferToBank(self, Amount, Password):
        req = tdapi.CThostFtdcReqTransferField()
        req.TradeCode = "202002"
        req.AccountID = self.Accountregister.AccountID
        req.BankID = self.Accountregister.BankID
        req.BankBranchID = self.Accountregister.BankBranchID
        req.BankAccount = self.Accountregister.BankAccount
        req.BankAccType = self.Accountregister.BankAccType
        req.BrokerID = self.Accountregister.BrokerID
        req.BrokerBranchID = self.Accountregister.BrokerBranchID
        req.IdCardType = self.Accountregister.IdCardType
        req.IdentifiedCardNo = self.Accountregister.IdentifiedCardNo
        req.CustType = self.Accountregister.CustType
        req.VerifyCertNoFlag = tdapi.THOST_FTDC_YNI_No
        req.SecuPwdFlag = tdapi.THOST_FTDC_BPWDF_BlankCheck
        req.TradeAmount = Amount
        req.CurrencyID = self.Accountregister.CurrencyID
        req.Password = Password
        self.api.ReqFromFutureToBankByFuture(req, 0)

    def OnFrontConnected(self) -> "void":
        print("OnFrontConnected")

        req = tdapi.CThostFtdcReqAuthenticateField()
        req.BrokerID = self.broker
        req.UserID = self.user
        req.AppID = self.appid
        req.AuthCode = self.authcode
        self.api.ReqAuthenticate(req, 0)

    def OnFrontDisconnected(self, nReason: int) -> "void":
        print(f"OnFrontDisconnected.[nReason={nReason}]")

    def OnRspAuthenticate(
            self,
            pRspAuthenticateField: tdapi.CThostFtdcRspAuthenticateField,
            pRspInfo: tdapi.CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
    ):
        """客户端认证响应"""
        if pRspInfo and pRspInfo.ErrorID != 0:
            print("认证失败：{}".format(pRspInfo.ErrorMsg))
            exit(-1)
        print("Authenticate succeed.")

        # 登录
        req = tdapi.CThostFtdcReqUserLoginField()
        req.BrokerID = self.broker
        req.UserID = self.user
        req.Password = self.password
        req.UserProductInfo = "openctp"
        self.api.ReqUserLogin(req, 0)

    def OnRspUserLogin(self, pRspUserLogin: 'CThostFtdcRspUserLoginField', pRspInfo: 'CThostFtdcRspInfoField',
                       nRequestID: 'int', bIsLast: 'bool') -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"Login failed. {pRspInfo.ErrorMsg}")
            exit(-1)
        print(f"Login succeed. TradingDay: {pRspUserLogin.TradingDay}, MaxOrderRef: {pRspUserLogin.MaxOrderRef}, SystemName: {pRspUserLogin.SystemName}")
        self.TradingDay = pRspUserLogin.TradingDay
        self.FrontID = pRspUserLogin.FrontID
        self.SessionID = pRspUserLogin.SessionID
        self.OrderRef = 1

        semaphore.release()

    def OnRspSettlementInfoConfirm(self, pSettlementInfoConfirm: "CThostFtdcSettlementInfoConfirmField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspSettlementInfoConfirm failed. {pRspInfo.ErrorMsg}")
            exit(-1)
        print(f"OnRspSettlementInfoConfirm: BrokerID:{pSettlementInfoConfirm.BrokerID}, InvestorID:{pSettlementInfoConfirm.InvestorID}, ConfirmDate:{pSettlementInfoConfirm.ConfirmDate}, ConfirmTime:{pSettlementInfoConfirm.ConfirmTime}, CurrencyID:{pSettlementInfoConfirm.CurrencyID}")

    def OnRspOrderInsert(self, pInputOrder: "CThostFtdcInputOrderField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspOrderInsert failed: {pRspInfo.ErrorMsg}")

        if pInputOrder is not None:
            print(f"OnRspOrderInsert:"
                  f"UserID={pInputOrder.UserID} "
                  f"BrokerID={pInputOrder.BrokerID} "
                  f"InvestorID={pInputOrder.InvestorID} "
                  f"ExchangeID={pInputOrder.ExchangeID} "
                  f"InstrumentID={pInputOrder.InstrumentID} "
                  f"Direction={pInputOrder.Direction} "
                  f"CombOffsetFlag={pInputOrder.CombOffsetFlag} "
                  f"CombHedgeFlag={pInputOrder.CombHedgeFlag} "
                  f"OrderPriceType={pInputOrder.OrderPriceType} "
                  f"LimitPrice={pInputOrder.LimitPrice} "
                  f"VolumeTotalOriginal={pInputOrder.VolumeTotalOriginal} "
                  f"OrderRef={pInputOrder.OrderRef} "
                  f"TimeCondition={pInputOrder.TimeCondition} "
                  f"GTDDate={pInputOrder.GTDDate} "
                  f"VolumeCondition={pInputOrder.VolumeCondition} "
                  f"MinVolume={pInputOrder.MinVolume} "
                  f"RequestID={pInputOrder.RequestID} "
                  f"InvestUnitID={pInputOrder.InvestUnitID} "
                  f"CurrencyID={pInputOrder.CurrencyID} "
                  f"AccountID={pInputOrder.AccountID} "
                  f"ClientID={pInputOrder.ClientID} "
                  f"IPAddress={pInputOrder.IPAddress} "
                  f"MacAddress={pInputOrder.MacAddress} "
                  )

    def OnRspOrderAction(self, pInputOrderAction: "CThostFtdcInputOrderActionField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspOrderAction failed: {pRspInfo.ErrorMsg}")

        if pInputOrderAction is not None:
            print(f"OnRspOrderAction:"
                  f"UserID={pInputOrderAction.UserID} "
                  f"ActionFlag={pInputOrderAction.ActionFlag} "
                  f"OrderActionRef={pInputOrderAction.OrderActionRef} "
                  f"BrokerID={pInputOrderAction.BrokerID} "
                  f"InvestorID={pInputOrderAction.InvestorID} "
                  f"ExchangeID={pInputOrderAction.ExchangeID} "
                  f"InstrumentID={pInputOrderAction.InstrumentID} "
                  f"FrontID={pInputOrderAction.FrontID} "
                  f"SessionID={pInputOrderAction.SessionID} "
                  f"OrderRef={pInputOrderAction.OrderRef} "
                  f"OrderSysID={pInputOrderAction.OrderSysID} "
                  f"InvestUnitID={pInputOrderAction.InvestUnitID} "
                  f"IPAddress={pInputOrderAction.IPAddress} "
                  f"MacAddress={pInputOrderAction.MacAddress} "
                  )

    def OnErrRtnOrderInsert(self, pInputOrder: "CThostFtdcInputOrderField", pRspInfo: "CThostFtdcRspInfoField") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnErrRtnOrderInsert failed: {pRspInfo.ErrorMsg}")

        if pInputOrder is not None:
            print(f"OnErrRtnOrderInsert:"
                  f"UserID={pInputOrder.UserID} "
                  f"BrokerID={pInputOrder.BrokerID} "
                  f"InvestorID={pInputOrder.InvestorID} "
                  f"ExchangeID={pInputOrder.ExchangeID} "
                  f"InstrumentID={pInputOrder.InstrumentID} "
                  f"Direction={pInputOrder.Direction} "
                  f"CombOffsetFlag={pInputOrder.CombOffsetFlag} "
                  f"CombHedgeFlag={pInputOrder.CombHedgeFlag} "
                  f"OrderPriceType={pInputOrder.OrderPriceType} "
                  f"LimitPrice={pInputOrder.LimitPrice} "
                  f"VolumeTotalOriginal={pInputOrder.VolumeTotalOriginal} "
                  f"OrderRef={pInputOrder.OrderRef} "
                  f"TimeCondition={pInputOrder.TimeCondition} "
                  f"GTDDate={pInputOrder.GTDDate} "
                  f"VolumeCondition={pInputOrder.VolumeCondition} "
                  f"MinVolume={pInputOrder.MinVolume} "
                  f"RequestID={pInputOrder.RequestID} "
                  f"InvestUnitID={pInputOrder.InvestUnitID} "
                  f"CurrencyID={pInputOrder.CurrencyID} "
                  f"AccountID={pInputOrder.AccountID} "
                  f"ClientID={pInputOrder.ClientID} "
                  f"IPAddress={pInputOrder.IPAddress} "
                  f"MacAddress={pInputOrder.MacAddress} "
                  )

    def OnErrRtnOrderAction(self, pOrderAction: "CThostFtdcOrderActionField", pRspInfo: "CThostFtdcRspInfoField") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnErrRtnOrderAction failed: {pRspInfo.ErrorMsg}")

        if pOrderAction is not None:
            print(f"OnErrRtnOrderAction:"
                  f"UserID={pOrderAction.UserID} "
                  f"ActionFlag={pOrderAction.ActionFlag} "
                  f"OrderActionRef={pOrderAction.OrderActionRef} "
                  f"BrokerID={pOrderAction.BrokerID} "
                  f"InvestorID={pOrderAction.InvestorID} "
                  f"ExchangeID={pOrderAction.ExchangeID} "
                  f"InstrumentID={pOrderAction.InstrumentID} "
                  f"FrontID={pOrderAction.FrontID} "
                  f"SessionID={pOrderAction.SessionID} "
                  f"OrderRef={pOrderAction.OrderRef} "
                  f"OrderSysID={pOrderAction.OrderSysID} "
                  f"InvestUnitID={pOrderAction.InvestUnitID} "
                  f"IPAddress={pOrderAction.IPAddress} "
                  f"MacAddress={pOrderAction.MacAddress} "
                  )

    def OnRspQryInstrument(self, pInstrument: tdapi.CThostFtdcInstrumentField, pRspInfo: "CThostFtdcRspInfoField",
                           nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryInstrument failed: {pRspInfo.ErrorMsg}")
            return

        if pInstrument is not None:
            print(
                f"OnRspQryInstrument:"
                f"InstrumentID={pInstrument.InstrumentID} "
                f"InstrumentName={pInstrument.InstrumentName} "
                f"ExchangeID={pInstrument.ExchangeID} "
                f"ProductClass={pInstrument.ProductClass} "
                f"ProductID={pInstrument.ProductID} "
                f"VolumeMultiple={pInstrument.VolumeMultiple} "
                f"PriceTick={pInstrument.PriceTick} "
                f"OptionsType={pInstrument.OptionsType} "
                f"StrikePrice={pInstrument.StrikePrice} "
                f"UnderlyingInstrID={pInstrument.UnderlyingInstrID} "
                f"UnderlyingMultiple={pInstrument.UnderlyingMultiple} "
                f"PositionType={pInstrument.PositionType} "
                f"PositionDateType={pInstrument.PositionDateType} "
                f"OpenDate={pInstrument.OpenDate} "
                f"ExpireDate={pInstrument.ExpireDate} "
                f"MinLimitOrderVolume={pInstrument.MinLimitOrderVolume} "
                f"MaxLimitOrderVolume={pInstrument.MaxLimitOrderVolume} "
                f"MinMarketOrderVolume={pInstrument.MinMarketOrderVolume} "
                f"MaxMarketOrderVolume={pInstrument.MaxMarketOrderVolume} "
                f"LongMarginRatio={pInstrument.LongMarginRatio} "
                f"ShortMarginRatio={pInstrument.ShortMarginRatio} "
                f"DeliveryYear={pInstrument.DeliveryYear} "
                f"DeliveryMonth={pInstrument.DeliveryMonth} "
                f"StartDelivDate={pInstrument.StartDelivDate} "
                f"EndDelivDate={pInstrument.EndDelivDate} "
                f"InstLifePhase={pInstrument.InstLifePhase} "
                f"IsTrading={pInstrument.IsTrading} "
                f"MaxMarginSideAlgorithm={pInstrument.MaxMarginSideAlgorithm} "
                f"CombinationType={pInstrument.CombinationType} "
                f"CreateDate={pInstrument.CreateDate} "
            )
        if bIsLast == True:
            print("Completed.")

    def OnRspQryExchange(self, pExchange: "CThostFtdcExchangeField", pRspInfo: "CThostFtdcRspInfoField",
                         nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryExchange failed: {pRspInfo.ErrorMsg}")
            return
        print(f"OnRspQryExchange:"
              f"ExchangeID={pExchange.ExchangeID} "
              f"ExchangeName={pExchange.ExchangeName} "
              )
        if bIsLast == True:
            print("Completed.")

    def OnRspQryProduct(self, pProduct: "CThostFtdcProductField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int",
                        bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryProduct failed: {pRspInfo.ErrorMsg}")
            return
        print(f"OnRspQryProduct:{pProduct.ProductID} "
              f"ProductName={pProduct.ProductName} "
              f"ExchangeID={pProduct.ExchangeID} "
              f"ProductClass={pProduct.ProductClass} "
              f"VolumeMultiple={pProduct.VolumeMultiple} "
              f"PriceTick={pProduct.PriceTick} "
              f"PositionType={pProduct.PositionType} "
              f"PositionDateType={pProduct.PositionDateType} "
              f"TradeCurrencyID={pProduct.TradeCurrencyID} "
              f"UnderlyingMultiple={pProduct.UnderlyingMultiple} "
              )
        if bIsLast == True:
            print("Completed.")

    def OnRtnOrder(self, pOrder):
        print(f"OnRtnOrder:"
              f"UserID={pOrder.UserID} "
              f"BrokerID={pOrder.BrokerID} "
              f"InvestorID={pOrder.InvestorID} "
              f"ExchangeID={pOrder.ExchangeID} "
              f"InstrumentID={pOrder.InstrumentID} "
              f"Direction={pOrder.Direction} "
              f"CombOffsetFlag={pOrder.CombOffsetFlag} "
              f"CombHedgeFlag={pOrder.CombHedgeFlag} "
              f"OrderPriceType={pOrder.OrderPriceType} "
              f"LimitPrice={pOrder.LimitPrice} "
              f"VolumeTotalOriginal={pOrder.VolumeTotalOriginal} "
              f"FrontID={pOrder.FrontID} "
              f"SessionID={pOrder.SessionID} "
              f"OrderRef={pOrder.OrderRef} "
              f"TimeCondition={pOrder.TimeCondition} "
              f"GTDDate={pOrder.GTDDate} "
              f"VolumeCondition={pOrder.VolumeCondition} "
              f"MinVolume={pOrder.MinVolume} "
              f"RequestID={pOrder.RequestID} "
              f"InvestUnitID={pOrder.InvestUnitID} "
              f"CurrencyID={pOrder.CurrencyID} "
              f"AccountID={pOrder.AccountID} "
              f"ClientID={pOrder.ClientID} "
              f"IPAddress={pOrder.IPAddress} "
              f"MacAddress={pOrder.MacAddress} "
              f"OrderSysID={pOrder.OrderSysID} "
              f"OrderStatus={pOrder.OrderStatus} "
              f"StatusMsg={pOrder.StatusMsg} "
              f"VolumeTotal={pOrder.VolumeTotal} "
              f"VolumeTraded={pOrder.VolumeTraded} "
              f"OrderSubmitStatus={pOrder.OrderSubmitStatus} "
              f"TradingDay={pOrder.TradingDay} "
              f"InsertDate={pOrder.InsertDate} "
              f"InsertTime={pOrder.InsertTime} "
              f"UpdateTime={pOrder.UpdateTime} "
              f"CancelTime={pOrder.CancelTime} "
              f"UserProductInfo={pOrder.UserProductInfo} "
              f"ActiveUserID={pOrder.ActiveUserID} "
              f"BrokerOrderSeq={pOrder.BrokerOrderSeq} "
              f"TraderID={pOrder.TraderID} "
              f"ClientID={pOrder.ClientID} "
              f"ParticipantID={pOrder.ParticipantID} "
              f"OrderLocalID={pOrder.OrderLocalID} "
              )

    def OnRtnTrade(self, pTrade):
        print(f"OnRtnTrade:"
              f"BrokerID={pTrade.BrokerID} "
              f"InvestorID={pTrade.InvestorID} "
              f"ExchangeID={pTrade.ExchangeID} "
              f"InstrumentID={pTrade.InstrumentID} "
              f"Direction={pTrade.Direction} "
              f"OffsetFlag={pTrade.OffsetFlag} "
              f"HedgeFlag={pTrade.HedgeFlag} "
              f"Price={pTrade.Price}  "
              f"Volume={pTrade.Volume} "
              f"OrderSysID={pTrade.OrderSysID} "
              f"OrderRef={pTrade.OrderRef} "
              f'TradeID={pTrade.TradeID} '
              f'TradeDate={pTrade.TradeDate} '
              f'TradeTime={pTrade.TradeTime} '
              f'ClientID={pTrade.ClientID} '
              f'TradingDay={pTrade.TradingDay} '
              f'OrderLocalID={pTrade.OrderLocalID} '
              f'BrokerOrderSeq={pTrade.BrokerOrderSeq} '
              f'InvestUnitID={pTrade.InvestUnitID} '
              f'ParticipantID={pTrade.ParticipantID} '
              )

    def OnRspQryInvestorPosition(self, pInvestorPosition: tdapi.CThostFtdcInvestorPositionField,
                                 pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryInvestorPosition failed: {pRspInfo.ErrorMsg}")
            return

        if pInvestorPosition is not None:
            print(f"OnRspInvestorPosition:{pInvestorPosition.InstrumentID} "
                  f"ExchangeID={pInvestorPosition.ExchangeID} "
                  f"InstrumentID={pInvestorPosition.InstrumentID} "
                  f"HedgeFlag={pInvestorPosition.HedgeFlag} "
                  f"PositionDate={pInvestorPosition.PositionDate} "
                  f"PosiDirection={pInvestorPosition.PosiDirection} "
                  f"Position={pInvestorPosition.Position} "
                  f"YdPosition={pInvestorPosition.YdPosition} "
                  f"TodayPosition={pInvestorPosition.TodayPosition} "
                  f"UseMargin={pInvestorPosition.UseMargin} "
                  f"PreMargin={pInvestorPosition.PreMargin} "
                  f"FrozenMargin={pInvestorPosition.FrozenMargin} "
                  f"Commission={pInvestorPosition.Commission} "
                  f"FrozenCommission={pInvestorPosition.FrozenCommission} "
                  f"CloseProfit={pInvestorPosition.CloseProfit} "
                  f"LongFrozen={pInvestorPosition.LongFrozen} "
                  f"ShortFrozen={pInvestorPosition.ShortFrozen} "
                  f"PositionCost={pInvestorPosition.PositionCost} "
                  f"OpenCost={pInvestorPosition.OpenCost} "
                  f"SettlementPrice={pInvestorPosition.SettlementPrice} "
                  )

        if bIsLast == True:
            print("Completed.")

    def OnRspQryInvestorPositionDetail(self, pInvestorPositionDetail: tdapi.CThostFtdcInvestorPositionDetailField,
                                       pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int",
                                       bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryInvestorPositionDetail failed: {pRspInfo.ErrorMsg}")
            return

        if pInvestorPositionDetail is not None:
            print(f"OnRspQryInvestorPositionDetail:{pInvestorPositionDetail.InstrumentID} "
                  f"Direction={pInvestorPositionDetail.Direction} "
                  f"HedgeFlag={pInvestorPositionDetail.HedgeFlag} "
                  f"Volume={pInvestorPositionDetail.Volume} "
                  f"OpenPrice={pInvestorPositionDetail.OpenPrice} "
                  f"Margin={pInvestorPositionDetail.Margin} "
                  f"CloseVolume={pInvestorPositionDetail.CloseVolume} "
                  f"CloseAmount={pInvestorPositionDetail.CloseAmount} "
                  f"OpenDate={pInvestorPositionDetail.OpenDate} "
                  f"TradingDay={pInvestorPositionDetail.TradingDay} "
                  )

        if bIsLast == True:
            print("Completed.")

    def OnRspQryOrder(self, pOrder: tdapi.CThostFtdcOrderField, pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int",
                      bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryOrder failed: {pRspInfo.ErrorMsg}")
            return

        if pOrder is not None:
            print(f"OnRspQryOrder:"
                  f"UserID={pOrder.UserID} "
                  f"BrokerID={pOrder.BrokerID} "
                  f"InvestorID={pOrder.InvestorID} "
                  f"ExchangeID={pOrder.ExchangeID} "
                  f"InstrumentID={pOrder.InstrumentID} "
                  f"Direction={pOrder.Direction} "
                  f"CombOffsetFlag={pOrder.CombOffsetFlag} "
                  f"CombHedgeFlag={pOrder.CombHedgeFlag} "
                  f"OrderPriceType={pOrder.OrderPriceType} "
                  f"LimitPrice={pOrder.LimitPrice} "
                  f"VolumeTotalOriginal={pOrder.VolumeTotalOriginal} "
                  f"FrontID={pOrder.FrontID} "
                  f"SessionID={pOrder.SessionID} "
                  f"OrderRef={pOrder.OrderRef} "
                  f"TimeCondition={pOrder.TimeCondition} "
                  f"GTDDate={pOrder.GTDDate} "
                  f"VolumeCondition={pOrder.VolumeCondition} "
                  f"MinVolume={pOrder.MinVolume} "
                  f"RequestID={pOrder.RequestID} "
                  f"InvestUnitID={pOrder.InvestUnitID} "
                  f"CurrencyID={pOrder.CurrencyID} "
                  f"AccountID={pOrder.AccountID} "
                  f"ClientID={pOrder.ClientID} "
                  f"IPAddress={pOrder.IPAddress} "
                  f"MacAddress={pOrder.MacAddress} "
                  f"OrderSysID={pOrder.OrderSysID} "
                  f"OrderStatus={pOrder.OrderStatus} "
                  f"StatusMsg={pOrder.StatusMsg} "
                  f"VolumeTotal={pOrder.VolumeTotal} "
                  f"VolumeTraded={pOrder.VolumeTraded} "
                  f"OrderSubmitStatus={pOrder.OrderSubmitStatus} "
                  f"TradingDay={pOrder.TradingDay} "
                  f"InsertDate={pOrder.InsertDate} "
                  f"InsertTime={pOrder.InsertTime} "
                  f"UpdateTime={pOrder.UpdateTime} "
                  f"CancelTime={pOrder.CancelTime} "
                  f"UserProductInfo={pOrder.UserProductInfo} "
                  f"ActiveUserID={pOrder.ActiveUserID} "
                  f"BrokerOrderSeq={pOrder.BrokerOrderSeq} "
                  f"TraderID={pOrder.TraderID} "
                  f"ClientID={pOrder.ClientID} "
                  f"ParticipantID={pOrder.ParticipantID} "
                  f"OrderLocalID={pOrder.OrderLocalID} "
                  )

        if bIsLast == True:
            print("Completed.")

    def OnRspQryTrade(self, pTrade: tdapi.CThostFtdcTradeField, pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int",
                      bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryTrade failed: {pRspInfo.ErrorMsg}")
            return

        if pTrade is not None:
            print(f"OnRspQryTrade:"
                  f"BrokerID={pTrade.BrokerID} "
                  f"InvestorID={pTrade.InvestorID} "
                  f"ExchangeID={pTrade.ExchangeID} "
                  f"InstrumentID={pTrade.InstrumentID} "
                  f"Direction={pTrade.Direction} "
                  f"OffsetFlag={pTrade.OffsetFlag} "
                  f"HedgeFlag={pTrade.HedgeFlag} "
                  f"Price={pTrade.Price}  "
                  f"Volume={pTrade.Volume} "
                  f"OrderSysID={pTrade.OrderSysID} "
                  f"OrderRef={pTrade.OrderRef} "
                  f'TradeID={pTrade.TradeID} '
                  f'TradeDate={pTrade.TradeDate} '
                  f'TradeTime={pTrade.TradeTime} '
                  f'ClientID={pTrade.ClientID} '
                  f'TradingDay={pTrade.TradingDay} '
                  f'OrderLocalID={pTrade.OrderLocalID} '
                  f'BrokerOrderSeq={pTrade.BrokerOrderSeq} '
                  f'InvestUnitID={pTrade.InvestUnitID} '
                  f'ParticipantID={pTrade.ParticipantID} '
                  )

        if bIsLast == True:
            print("Completed.")

    def OnRspQryTradingAccount(self, pTradingAccount: tdapi.CThostFtdcTradingAccountField,
                               pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryTradingAccount failed: {pRspInfo.ErrorMsg}")
            return

        if pTradingAccount is not None:
            print(f"OnRspQryTradingAccount: "
                  f"PreBalance={pTradingAccount.PreBalance} "
                  f"PreMargin={pTradingAccount.PreMargin} "
                  f"FrozenMargin={pTradingAccount.FrozenMargin} "
                  f"CurrMargin={pTradingAccount.CurrMargin} "
                  f"Commission={pTradingAccount.Commission} "
                  f"FrozenCommission={pTradingAccount.FrozenCommission} "
                  f"Available={pTradingAccount.Available} "
                  f"Balance={pTradingAccount.Balance} "
                  f"CloseProfit={pTradingAccount.CloseProfit} "
                  f"CurrencyID={pTradingAccount.CurrencyID} "
                  )

        if bIsLast == True:
            print("Completed.")

    def OnRspQryInvestor(self, pInvestor: "CThostFtdcInvestorField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryDepthMarketData failed: {pRspInfo.ErrorMsg}")
            return

        if pInvestor is not None:
            print(f"OnRspQryInvestor: "
                  f"InvestorID={pInvestor.InvestorID} "
                  f"InvestorName={pInvestor.InvestorName} "
                  f"Telephone={pInvestor.Telephone} "
                  )

        if bIsLast == True:
            print("Completed.")
    def OnRspQryDepthMarketData(self, pDepthMarketData: tdapi.CThostFtdcDepthMarketDataField,
                                pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryDepthMarketData failed: {pRspInfo.ErrorMsg}")
            return

        if pDepthMarketData is not None:
            print(f"OnRspQryDepthMarketData: "
                  f"InstrumentID={pDepthMarketData.InstrumentID}"
                  f"LastPrice={pDepthMarketData.LastPrice} "
                  f"Volume={pDepthMarketData.Volume} "
                  f"OpenPrice={pDepthMarketData.OpenPrice} "
                  f"HighestPrice={pDepthMarketData.HighestPrice} "
                  f"LowestPrice={pDepthMarketData.LowestPrice} "
                  f"ClosePrice={pDepthMarketData.ClosePrice} "
                  f"OpenInterest={pDepthMarketData.OpenInterest} "
                  f"UpperLimitPrice={pDepthMarketData.UpperLimitPrice} "
                  f"LowerLimitPrice={pDepthMarketData.LowerLimitPrice} "
                  f"SettlementPrice={pDepthMarketData.SettlementPrice} "
                  f"PreSettlementPrice={pDepthMarketData.PreSettlementPrice} "
                  f"PreClosePrice={pDepthMarketData.PreClosePrice} "
                  f"PreOpenInterest={pDepthMarketData.PreOpenInterest} "
                  f"BidPrice1={pDepthMarketData.BidPrice1} "
                  f"BidVolume1={pDepthMarketData.BidVolume1} "
                  f"AskPrice1={pDepthMarketData.AskPrice1} "
                  f"AskVolume1={pDepthMarketData.AskVolume1} "
                  f"UpdateTime={pDepthMarketData.UpdateTime} "
                  f"UpdateMillisec={pDepthMarketData.UpdateMillisec} "
                  f"ActionDay={pDepthMarketData.ActionDay} "
                  f"TradingDay={pDepthMarketData.TradingDay} "
                  )

        if bIsLast == True:
            print("Completed.")

    def OnRspQryInstrumentCommissionRate(self, pInstrumentCommissionRate: tdapi.CThostFtdcInstrumentCommissionRateField,
                                         pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryInstrumentCommissionRate failed: {pRspInfo.ErrorMsg}')
            return
        if pInstrumentCommissionRate is not None:
            print(f"OnRspQryInstrumentCommissionRate:"
                  f"ExchangeID={pInstrumentCommissionRate.ExchangeID} "
                  f"InstrumentID={pInstrumentCommissionRate.InstrumentID} "
                  f"InvestorRange={pInstrumentCommissionRate.InvestorRange} "
                  f"InvestorID={pInstrumentCommissionRate.InvestorID} "
                  f"OpenRatioByMoney={pInstrumentCommissionRate.OpenRatioByMoney} "
                  f"OpenRatioByVolume={pInstrumentCommissionRate.OpenRatioByVolume} "
                  f"CloseRatioByMoney={pInstrumentCommissionRate.CloseRatioByMoney} "
                  f"CloseRatioByVolume={pInstrumentCommissionRate.CloseRatioByVolume} "
                  f"CloseTodayRatioByMoney={pInstrumentCommissionRate.CloseTodayRatioByMoney} "
                  f"CloseTodayRatioByVolume={pInstrumentCommissionRate.CloseTodayRatioByVolume} "
                  )
        if bIsLast == True:
            print("Completed.")

    def OnRspQryInstrumentMarginRate(self, pInstrumentMarginRate: tdapi.CThostFtdcInstrumentMarginRateField,
                                     pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryInstrumentMarginRate failed: {pRspInfo.ErrorMsg}')
            return
        if pInstrumentMarginRate is not None:
            print(f"OnRspQryInstrumentMarginRate:"
                  f"ExchangeID={pInstrumentMarginRate.ExchangeID} "
                  f"InstrumentID={pInstrumentMarginRate.InstrumentID} "
                  f"InvestorRange={pInstrumentMarginRate.InvestorRange} "
                  f"InvestorID={pInstrumentMarginRate.InvestorID} "
                  f"HedgeFlag={pInstrumentMarginRate.HedgeFlag} "
                  f"LongMarginRatioByMoney={pInstrumentMarginRate.LongMarginRatioByMoney} "
                  f"LongMarginRatioByVolume={pInstrumentMarginRate.LongMarginRatioByVolume} "
                  f"ShortMarginRatioByMoney={pInstrumentMarginRate.ShortMarginRatioByMoney} "
                  f"ShortMarginRatioByVolume={pInstrumentMarginRate.ShortMarginRatioByVolume} "
                  f"IsRelative={pInstrumentMarginRate.IsRelative} "
                  )
        if bIsLast == True:
            print("Completed.")

    def OnRspQryInstrumentOrderCommRate(self, pInstrumentOrderCommRate: tdapi.CThostFtdcInstrumentOrderCommRateField,
                                        pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryInstrumentOrderCommRate failed: {pRspInfo.ErrorMsg}')
            return
        if pInstrumentOrderCommRate is not None:
            print(f"OnRspQryInstrumentOrderCommRate:"
                  f"ExchangeID={pInstrumentOrderCommRate.ExchangeID} "
                  f"InstrumentID={pInstrumentOrderCommRate.InstrumentID} "
                  f"InvestorRange={pInstrumentOrderCommRate.InvestorRange} "
                  f"InvestorID={pInstrumentOrderCommRate.InvestorID} "
                  f"HedgeFlag={pInstrumentOrderCommRate.HedgeFlag} "
                  f"OrderCommByVolume={pInstrumentOrderCommRate.OrderCommByVolume} "
                  f"OrderActionCommByVolume={pInstrumentOrderCommRate.OrderActionCommByVolume} "
                  )
        if bIsLast == True:
            print("Completed.")

    def OnRspQryOptionInstrCommRate(self, pOptionInstrCommRate: "CThostFtdcOptionInstrCommRateField",
                                         pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryOptionInstrCommRate failed: {pRspInfo.ErrorMsg}')
            return
        if pOptionInstrCommRate is not None:
            print(f"OnRspQryOptionInstrCommRate:"
                  f"ExchangeID={pOptionInstrCommRate.ExchangeID} "
                  f"InstrumentID={pOptionInstrCommRate.InstrumentID} "
                  f"InvestorRange={pOptionInstrCommRate.InvestorRange} "
                  f"InvestorID={pOptionInstrCommRate.InvestorID} "
                  f"OpenRatioByMoney={pOptionInstrCommRate.OpenRatioByMoney} "
                  f"OpenRatioByVolume={pOptionInstrCommRate.OpenRatioByVolume} "
                  f"CloseRatioByMoney={pOptionInstrCommRate.CloseRatioByMoney} "
                  f"CloseRatioByVolume={pOptionInstrCommRate.CloseRatioByVolume} "
                  f"CloseTodayRatioByMoney={pOptionInstrCommRate.CloseTodayRatioByMoney} "
                  f"CloseTodayRatioByVolume={pOptionInstrCommRate.CloseTodayRatioByVolume} "
                  f"StrikeRatioByMoney={pOptionInstrCommRate.StrikeRatioByMoney} "
                  f"StrikeRatioByVolume={pOptionInstrCommRate.StrikeRatioByVolume} "
                  )
        if bIsLast == True:
            print("Completed.")

    def OnRspQryTradingCode(self, pTradingCode: "CThostFtdcTradingCodeField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryTradingCode failed: {pRspInfo.ErrorMsg}')
            return
        if pTradingCode is not None:
            print(f"OnRspQryTradingCode:"
                  f"BrokerID={pTradingCode.BrokerID} "
                  f"InvestorID={pTradingCode.InvestorID} "
                  f"ExchangeID={pTradingCode.ExchangeID} "
                  f"ClientID={pTradingCode.ClientID} "
                  )
        if bIsLast == True:
            print("Completed.")
    def OnRspQrySettlementInfo(self, pSettlementInfo: "CThostFtdcSettlementInfoField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQrySettlementInfo failed: {pRspInfo.ErrorMsg}')
            return
        if pSettlementInfo is not None:
            # print(f"OnRspQrySettlementInfo:TradingDay={pSettlementInfo.TradingDay},InvestorID={pSettlementInfo.InvestorID},CurrencyID={pSettlementInfo.CurrencyID},Content={pSettlementInfo.Content}")
            print(pSettlementInfo.Content)
        if bIsLast == True:
            print("Completed.")

    def OnRtnInstrumentStatus(self, pInstrumentStatus: "CThostFtdcInstrumentStatusField") -> "void":
        print(f"OnRtnInstrumentStatus:"
              f"ExchangeID={pInstrumentStatus.ExchangeID} "
              f"InstrumentID={pInstrumentStatus.InstrumentID} "
              f"InstrumentStatus={pInstrumentStatus.InstrumentStatus}  "
              f"TradingSegmentSN={pInstrumentStatus.TradingSegmentSN} "
              f'EnterTime={pInstrumentStatus.EnterTime} '
              f"EnterReason={pInstrumentStatus.EnterReason} "
              )

    def OnRspQryTransferSerial(self, pTransferSerial: "CThostFtdcTransferSerialField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        r"""请求查询转帐流水响应"""
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryTransferSerial failed: {pRspInfo.ErrorMsg}')
            return
        if pTransferSerial is not None:
            print(f"OnRspQryTransferSerial:"
                  f"TradeCode={pTransferSerial.TradeCode} "
                  f"AccountID={pTransferSerial.AccountID} "
                  f"BankID={pTransferSerial.BankID} "
                  f"BankAccount={pTransferSerial.BankAccount} "
                  f"CurrencyID={pTransferSerial.CurrencyID} "
                  f"TradeAmount={pTransferSerial.TradeAmount} "
                  f"PlateSerial={pTransferSerial.PlateSerial} "
                  f"TradeDate={pTransferSerial.TradeDate} "
                  f"TradeTime={pTransferSerial.TradeTime} "
                  f"ErrorMsg={pTransferSerial.ErrorMsg} "
                  )
        if bIsLast == True:
            print("Completed.")

    def OnRspQryAccountregister(self, pAccountregister: "CThostFtdcAccountregisterField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        r"""请求查询银期签约关系响应"""
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryAccountregister failed: {pRspInfo.ErrorMsg}')
            return
        if pAccountregister is not None:
            print(f"OnRspQryAccountregister:"
                  f"AccountID={pAccountregister.AccountID} "
                  f"BankID={pAccountregister.BankID} "
                  f"BankAccount={pAccountregister.BankAccount} "
                  f"CustomerName={pAccountregister.CustomerName} "
                  f"CurrencyID={pAccountregister.CurrencyID} "
                  f"RegDate={pAccountregister.RegDate} "
                  )
            self.Accountregister.TradeDay = pAccountregister.TradeDay
            self.Accountregister.BankID = pAccountregister.BankID
            self.Accountregister.BankBranchID = pAccountregister.BankBranchID
            self.Accountregister.BankAccount = pAccountregister.BankAccount
            self.Accountregister.BrokerID = pAccountregister.BrokerID
            self.Accountregister.BrokerBranchID = pAccountregister.BrokerBranchID
            self.Accountregister.AccountID = pAccountregister.AccountID
            self.Accountregister.IdCardType = pAccountregister.IdCardType
            self.Accountregister.IdentifiedCardNo = pAccountregister.IdentifiedCardNo
            self.Accountregister.CustomerName = pAccountregister.CustomerName
            self.Accountregister.CurrencyID = pAccountregister.CurrencyID
            self.Accountregister.OpenOrDestroy = pAccountregister.OpenOrDestroy
            self.Accountregister.RegDate = pAccountregister.RegDate
            self.Accountregister.OutDate = pAccountregister.OutDate
            self.Accountregister.TID = pAccountregister.TID
            self.Accountregister.CustType = pAccountregister.CustType
            self.Accountregister.BankAccType = pAccountregister.BankAccType
            self.Accountregister.LongCustomerName = pAccountregister.LongCustomerName

        if bIsLast == True:
            print("Completed.")

    def OnRspQryContractBank(self, pContractBank: "CThostFtdcContractBankField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        r"""请求查询签约银行响应"""
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryContractBank failed: {pRspInfo.ErrorMsg}')
            return
        if pContractBank is not None:
            print(f"OnRspQryContractBank:"
                  f"BankID={pContractBank.BankID} "
                  f"BankBrchID={pContractBank.BankBrchID} "
                  f"BankName={pContractBank.BankName} "
                  )
        if bIsLast == True:
            print("Completed.")

    def OnRtnFromBankToFutureByBank(self, pRspTransfer: "CThostFtdcRspTransferField") -> "void":
        r"""银行发起银行资金转期货通知"""
        print(f"OnRtnFromBankToFutureByBank:"
              f"TradeCode={pRspTransfer.TradeCode} "
              f"AccountID={pRspTransfer.AccountID} "
              f"BankID={pRspTransfer.BankID} "
              f"BankAccount={pRspTransfer.BankAccount} "
              f"CurrencyID={pRspTransfer.CurrencyID} "
              f"TradeAmount={pRspTransfer.TradeAmount} "
              f"PlateSerial={pRspTransfer.PlateSerial} "
              f"TradeDate={pRspTransfer.TradeDate} "
              f"TradeTime={pRspTransfer.TradeTime} "
              f"ErrorMsg={pRspTransfer.ErrorMsg} "
              )

    def OnRtnFromFutureToBankByBank(self, pRspTransfer: "CThostFtdcRspTransferField") -> "void":
        r"""银行发起期货资金转银行通知"""
        print(f"OnRtnFromFutureToBankByBank:"
              f"TradeCode={pRspTransfer.TradeCode} "
              f"AccountID={pRspTransfer.AccountID} "
              f"BankID={pRspTransfer.BankID} "
              f"BankAccount={pRspTransfer.BankAccount} "
              f"CurrencyID={pRspTransfer.CurrencyID} "
              f"TradeAmount={pRspTransfer.TradeAmount} "
              f"PlateSerial={pRspTransfer.PlateSerial} "
              f"TradeDate={pRspTransfer.TradeDate} "
              f"TradeTime={pRspTransfer.TradeTime} "
              f"ErrorMsg={pRspTransfer.ErrorMsg} "
              )

    def OnRtnRepealFromBankToFutureByBank(self, pRspRepeal: "CThostFtdcRspRepealField") -> "void":
        r"""银行发起冲正银行转期货通知"""
        print(f"OnRtnRepealFromBankToFutureByBank:")

    def OnRtnRepealFromFutureToBankByBank(self, pRspRepeal: "CThostFtdcRspRepealField") -> "void":
        r"""银行发起冲正期货转银行通知"""
        print(f"OnRtnRepealFromFutureToBankByBank:")

    def OnRtnFromBankToFutureByFuture(self, pRspTransfer: "CThostFtdcRspTransferField") -> "void":
        r"""期货发起银行资金转期货通知"""
        print(f"OnRtnFromBankToFutureByFuture:"
              f"TradeCode={pRspTransfer.TradeCode} "
              f"AccountID={pRspTransfer.AccountID} "
              f"BankID={pRspTransfer.BankID} "
              f"BankAccount={pRspTransfer.BankAccount} "
              f"CurrencyID={pRspTransfer.CurrencyID} "
              f"TradeAmount={pRspTransfer.TradeAmount} "
              f"PlateSerial={pRspTransfer.PlateSerial} "
              f"TradeDate={pRspTransfer.TradeDate} "
              f"TradeTime={pRspTransfer.TradeTime} "
              f"ErrorMsg={pRspTransfer.ErrorMsg} "
              )

    def OnRtnFromFutureToBankByFuture(self, pRspTransfer: "CThostFtdcRspTransferField") -> "void":
        r"""期货发起期货资金转银行通知"""
        print(f"OnRtnFromFutureToBankByFuture:"
              f"TradeCode={pRspTransfer.TradeCode} "
              f"AccountID={pRspTransfer.AccountID} "
              f"BankID={pRspTransfer.BankID} "
              f"BankAccount={pRspTransfer.BankAccount} "
              f"CurrencyID={pRspTransfer.CurrencyID} "
              f"TradeAmount={pRspTransfer.TradeAmount} "
              f"PlateSerial={pRspTransfer.PlateSerial} "
              f"TradeDate={pRspTransfer.TradeDate} "
              f"TradeTime={pRspTransfer.TradeTime} "
              f"ErrorMsg={pRspTransfer.ErrorMsg} "
              )

    def OnRtnRepealFromBankToFutureByFutureManual(self, pRspRepeal: "CThostFtdcRspRepealField") -> "void":
        r"""系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知"""
        print(f"OnRtnRepealFromBankToFutureByFutureManual:")

    def OnRtnRepealFromFutureToBankByFutureManual(self, pRspRepeal: "CThostFtdcRspRepealField") -> "void":
        r"""系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知"""
        print(f"OnRtnRepealFromFutureToBankByFutureManual:")

    def OnRtnQueryBankBalanceByFuture(self, pNotifyQueryAccount: "CThostFtdcNotifyQueryAccountField") -> "void":
        r"""期货发起查询银行余额通知"""
        print(f"OnRtnQueryBankBalanceByFuture:"
              f"TradeCode={pNotifyQueryAccount.TradeCode} "
              f"AccountID={pNotifyQueryAccount.AccountID} "
              f"BankID={pNotifyQueryAccount.BankID} "
              f"BankAccount={pNotifyQueryAccount.BankAccount} "
              f"CurrencyID={pNotifyQueryAccount.CurrencyID} "
              f"BankFetchAmount={pNotifyQueryAccount.BankFetchAmount} "
              f"PlateSerial={pNotifyQueryAccount.PlateSerial} "
              f"TradeDate={pNotifyQueryAccount.TradeDate} "
              f"TradeTime={pNotifyQueryAccount.TradeTime} "
              f"ErrorMsg={pNotifyQueryAccount.ErrorMsg} "
              )

    def OnErrRtnBankToFutureByFuture(self, pReqTransfer: "CThostFtdcReqTransferField", pRspInfo: "CThostFtdcRspInfoField") -> "void":
        r"""期货发起银行资金转期货错误回报"""
        print(f"OnErrRtnBankToFutureByFuture:")

    def OnErrRtnFutureToBankByFuture(self, pReqTransfer: "CThostFtdcReqTransferField", pRspInfo: "CThostFtdcRspInfoField") -> "void":
        r"""期货发起期货资金转银行错误回报"""
        print(f"OnErrRtnFutureToBankByFuture:")

    def OnErrRtnRepealBankToFutureByFutureManual(self, pReqRepeal: "CThostFtdcReqRepealField", pRspInfo: "CThostFtdcRspInfoField") -> "void":
        r"""系统运行时期货端手工发起冲正银行转期货错误回报"""
        print(f"OnErrRtnRepealBankToFutureByFutureManual:")

    def OnErrRtnRepealFutureToBankByFutureManual(self, pReqRepeal: "CThostFtdcReqRepealField", pRspInfo: "CThostFtdcRspInfoField") -> "void":
        r"""系统运行时期货端手工发起冲正期货转银行错误回报"""
        print(f"OnErrRtnRepealFutureToBankByFutureManual:")

    def OnErrRtnQueryBankBalanceByFuture(self, pReqQueryAccount: "CThostFtdcReqQueryAccountField", pRspInfo: "CThostFtdcRspInfoField") -> "void":
        r"""期货发起查询银行余额错误回报"""
        print(f"OnErrRtnQueryBankBalanceByFuture:")

    def OnRtnRepealFromBankToFutureByFuture(self, pRspRepeal: "CThostFtdcRspRepealField") -> "void":
        r"""期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知"""
        print(f"OnRtnRepealFromBankToFutureByFuture:")

    def OnRtnRepealFromFutureToBankByFuture(self, pRspRepeal: "CThostFtdcRspRepealField") -> "void":
        r"""期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知"""
        print(f"OnRtnRepealFromFutureToBankByFuture:")

    def OnRspFromBankToFutureByFuture(self, pReqTransfer: "CThostFtdcReqTransferField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        r"""期货发起银行资金转期货应答"""
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspFromBankToFutureByFuture failed: {pRspInfo.ErrorMsg}')
            return
        if pReqTransfer is not None:
            print(f"OnRspFromBankToFutureByFuture:"
                  f"TradeCode={pReqTransfer.TradeCode} "
                  f"AccountID={pReqTransfer.AccountID} "
                  f"BankID={pReqTransfer.BankID} "
                  f"BankAccount={pReqTransfer.BankAccount} "
                  f"CurrencyID={pReqTransfer.CurrencyID} "
                  f"TradeAmount={pReqTransfer.TradeAmount} "
                  f"PlateSerial={pReqTransfer.PlateSerial} "
                  f"TradeDate={pReqTransfer.TradeDate} "
                  f"TradeTime={pReqTransfer.TradeTime} "
                  f"ErrorMsg={pReqTransfer.ErrorMsg} "
                  )
        if bIsLast == True:
            print("Completed.")

    def OnRspFromFutureToBankByFuture(self, pReqTransfer: "CThostFtdcReqTransferField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        r"""期货发起期货资金转银行应答"""
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspFromFutureToBankByFuture failed: {pRspInfo.ErrorMsg}')
            return
        if pReqTransfer is not None:
            print(f"OnRspFromFutureToBankByFuture:"
                  f"TradeCode={pReqTransfer.TradeCode} "
                  f"AccountID={pReqTransfer.AccountID} "
                  f"BankID={pReqTransfer.BankID} "
                  f"BankAccount={pReqTransfer.BankAccount} "
                  f"CurrencyID={pReqTransfer.CurrencyID} "
                  f"TradeAmount={pReqTransfer.TradeAmount} "
                  f"PlateSerial={pReqTransfer.PlateSerial} "
                  f"TradeDate={pReqTransfer.TradeDate} "
                  f"TradeTime={pReqTransfer.TradeTime} "
                  f"ErrorMsg={pReqTransfer.ErrorMsg} "
                  )
        if bIsLast == True:
            print("Completed.")

    def OnRspQueryBankAccountMoneyByFuture(self, pReqQueryAccount: "CThostFtdcReqQueryAccountField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        r"""期货发起查询银行余额应答"""
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQueryBankAccountMoneyByFuture failed: {pRspInfo.ErrorMsg}')
            return
        if pReqQueryAccount is not None:
            print(f"OnRspQueryBankAccountMoneyByFuture:"
                  f"TradeCode={pReqQueryAccount.TradeCode} "
                  f"AccountID={pReqQueryAccount.AccountID} "
                  f"BankID={pReqQueryAccount.BankID} "
                  f"BankAccount={pReqQueryAccount.BankAccount} "
                  f"CurrencyID={pReqQueryAccount.CurrencyID} "
                  f"PlateSerial={pReqQueryAccount.PlateSerial} "
                  f"TradeDate={pReqQueryAccount.TradeDate} "
                  f"TradeTime={pReqQueryAccount.TradeTime} "
                  )
        if bIsLast == True:
            print("Completed.")

def print_commands():
    print("Commands:")

    print("{}: query instrument".format(command_query_instrument))
    print("{}: query exchange".format(command_query_exchange))
    print("{}: query product".format(command_query_product))
    print("{}: query price".format(command_query_price))
    print("{}: query account".format(command_query_account))
    print("{}: query position".format(command_query_position))
    print("{}: query position detail".format(command_query_position_detail))
    print("{}: query order".format(command_query_order))
    print("{}: query trade".format(command_query_trade))
    print("{}: query CommissionRate".format(command_query_CommissionRate))
    print("{}: query MarginRate".format(command_query_MarginRate))
    print("{}: query OrderCommRate".format(command_query_OrderCommRate))
    print("{}: query OptionInstrCommRate".format(command_query_OptionInstrCommRate))
    print("{}: query investor".format(command_query_investor))
    print("{}: query tradingcode".format(command_query_tradingcode))
    print("{}: query settlement".format(command_query_settlement))
    print("{}: confirm settlement".format(command_SettlementInfoConfirm))
    print("{}: order insert".format(command_order_insert))
    print("{}: order cancel".format(command_order_cancel))
    print("{}: money transfer to ctp".format(command_money_transfer_to_ctp))
    print("{}: money transfer to bank".format(command_money_transfer_to_bank))
    print("{}: query money transfer detail".format(command_query_money_transfer_detail))
    print("{}: query bank account".format(command_query_bank_account))
    print("{}: query account register".format(command_query_account_register))
    print("{}: query contract bank".format(command_query_contract_bank))
    print("{}: quit".format(command_quit))

    print("please enter a command number.")


if __name__ == '__main__':
    if len(sys.argv) != 7:
        print("Usage: {} host broker user password appid authcode".format(sys.argv[0]))
        print("example: {} tcp://180.168.146.187:10130 9999 000001 888888 simnow_client_test 0000000000000000".format(
            sys.argv[0]))
        exit(0)

    semaphore = threading.Semaphore(0)

    host = sys.argv[1]
    broker = sys.argv[2]
    user = sys.argv[3]
    password = sys.argv[4]
    appid = sys.argv[5]
    authcode = sys.argv[6]
    ctpcommand = CTPCommand(host, broker, user, password, appid, authcode)
    ctpcommand.Run()

    # wait for login ok.
    semaphore.acquire()

    i = 1
    command_query_instrument = str(i)
    i = i + 1
    command_query_exchange = str(i)
    i = i + 1
    command_query_product = str(i)
    i = i + 1
    command_query_price = str(i)
    i = i + 1
    command_query_account = str(i)
    i = i + 1
    command_query_position = str(i)
    i = i + 1
    command_query_position_detail = str(i)
    i = i + 1
    command_query_order = str(i)
    i = i + 1
    command_query_trade = str(i)
    i = i + 1
    command_query_CommissionRate = str(i)
    i = i + 1
    command_query_MarginRate = str(i)
    i = i + 1
    command_query_OrderCommRate = str(i)
    i = i + 1
    command_query_OptionInstrCommRate = str(i)
    i = i + 1
    command_query_investor = str(i)
    i = i + 1
    command_query_tradingcode = str(i)
    i = i + 1
    command_query_settlement = str(i)
    i = i + 1
    command_SettlementInfoConfirm = str(i)
    i = i + 1
    command_order_insert = str(i)
    i = i + 1
    command_order_cancel = str(i)
    i = i + 1
    command_money_transfer_to_ctp = str(i)
    i = i + 1
    command_money_transfer_to_bank = str(i)
    i = i + 1
    command_query_money_transfer_detail = str(i)
    i = i + 1
    command_query_bank_account = str(i)
    i = i + 1
    command_query_account_register = str(i)
    i = i + 1
    command_query_contract_bank = str(i)

    command_quit = 'q'

    while True:
        print_commands()
        command = input("")
        if command == command_query_instrument:
            ExchangeID = input("ExchangeID: (Default:All)")
            ProductID = input("ProductID: (Default:All)")
            InstrumentID = input("InstrumentID: (Default:All)")
            ctpcommand.QryInstrument(ExchangeID, ProductID, InstrumentID)
        elif command == command_query_exchange:
            ctpcommand.QryExchange()
        elif command == command_query_product:
            ExchangeID = input("ExchangeID: (Default:All)")
            ProductID = input("ProductID: (Default:All)")
            ctpcommand.QryProduct(ExchangeID, ProductID)
        elif command == command_query_position:
            InstrumentID = input("InstrumentID:(Default:All)")
            ctpcommand.QryPosition(InstrumentID)
        elif command == command_query_position_detail:
            InstrumentID = input("InstrumentID:(Default:All)")
            ctpcommand.QryPositionDetail(InstrumentID)
        elif command == command_query_order:
            InstrumentID = input("InstrumentID:(Default:All)")
            ctpcommand.QryOrder(InstrumentID)
        elif command == command_query_trade:
            InstrumentID = input("InstrumentID:(Default:All)")
            ctpcommand.QryTrade(InstrumentID)
        elif command == command_query_price:
            ExchangeID = input("ExchangeID: (Default:All)")
            InstrumentID = input("InstrumentID:(Default:All)")
            ctpcommand.QryPrice(ExchangeID, InstrumentID)
        elif command == command_query_account:
            ctpcommand.QryAccount()
        elif command == command_query_CommissionRate:
            ExchangeID = input("ExchangeID: (Default:All)")
            InstrumentID = input("InstrumentID:(Default:All)")
            ctpcommand.QryCommissionRate(ExchangeID, InstrumentID)
        elif command == command_query_MarginRate:
            ExchangeID = input("ExchangeID: (Default:All)")
            InstrumentID = input("InstrumentID:(Default:All)")
            HedgeFlag = input("HedgeFlag:1,投机;2,套利;3,套保;4,做市商(Default:1)")
            if HedgeFlag == "":
                HedgeFlag = "1"
            ctpcommand.QryMarginRate(ExchangeID, InstrumentID, HedgeFlag)
        elif command == command_query_OrderCommRate:
            InstrumentID = input("InstrumentID:(Default:All)")
            ctpcommand.QryOrderCommRate(InstrumentID)
        elif command == command_query_OptionInstrCommRate:
            ExchangeID = input("ExchangeID: (Default:All)")
            InstrumentID = input("InstrumentID:(Default:All)")
            ctpcommand.QryOptionInstrCommRate(ExchangeID, InstrumentID)
        elif command == command_query_investor:
            ctpcommand.QryInvestor()
        elif command == command_query_tradingcode:
            ctpcommand.QryTradingCode()
        elif command == command_query_settlement:
            TradingDay = input("TradingDay:(Default:All)")
            ctpcommand.QrySettlementInfo(TradingDay)
        elif command == command_SettlementInfoConfirm:
            ctpcommand.ConfirmSettlementInfo()
        elif command == command_order_insert:
            ExchangeID = input("ExchangeID:")
            InstrumentID = input("InstrumentID:")
            Direction = input("Direction:0,买入;1,卖出")
            Offset = input("Offset:0,开仓;1,平仓;2,强平;3,平今;4,平昨;5,强减")
            PriceType = input("PriceType:1,任意价;2,限价(Default:2)")
            if PriceType == "":
                PriceType = "2"
            Price = input("Price:")
            Volume = input("Volume:")
            TimeCondition = input("TimeCondition:1,IOC立即完成否则撤销;3,GFD当日有效(Default:3)")
            if TimeCondition == "":
                TimeCondition = "3"
            VolumeCondition = input("VolumeCondition:1,任何数量;2,最小数量;3,全部数量(Default:1)")
            if VolumeCondition == "":
                VolumeCondition = "1"
            MinVolume = input("MinVolume: (Default:1)")
            if MinVolume == "":
                MinVolume = "1"
            ctpcommand.OrderInsert(ExchangeID, InstrumentID, Direction, Offset, PriceType, Price, Volume, TimeCondition, VolumeCondition, MinVolume)
        elif command == command_order_cancel:
            ExchangeID = input("ExchangeID:")
            InstrumentID = input("InstrumentID:")
            OrderSysID = input("OrderSysID:")
            FrontID = input("FrontID:")
            SessionID = input("SessionID:")
            OrderRef = input("OrderRef:")
            ctpcommand.OrderCancel(ExchangeID, InstrumentID, OrderSysID, FrontID, SessionID, OrderRef)
        elif command == command_query_money_transfer_detail:
            ctpcommand.QryTransferSerial()
        elif command == command_query_bank_account:
            Password = input("Password:")
            ctpcommand.QueryBankAccount(Password)
        elif command == command_query_account_register:
            ctpcommand.QryAccountRegister()
        elif command == command_query_contract_bank:
            ctpcommand.QryContractBank()
        elif command == command_money_transfer_to_ctp:
            Password = input("Password:")
            Amount = input("Amount:")
            if Amount == "":
                print("Invalid Amount.")
                continue
            ctpcommand.MoneyTransferToCTP(float(Amount), Password)
        elif command == command_money_transfer_to_bank:
            Password = input("Password:")
            Amount = input("Amount:")
            if Amount == "":
                print("Invalid Amount.")
                continue
            ctpcommand.MoneyTransferToBank(float(Amount), Password)
        elif command == command_quit:
            break
