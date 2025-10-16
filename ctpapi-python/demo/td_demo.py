"""
author: krenx@openctp.
last modify: 2024/12/12
"""

import sys
import time
import os
import threading
from openctp_ctp import thosttraderapi as tdapi # pip install mode
# import thosttraderapi as tdapi # local mode


class TdImpl(tdapi.CThostFtdcTraderSpi):
    def __init__(self, host, broker, user, password, appid, authcode):
        super().__init__()

        self.broker = broker
        self.user = user
        self.password = password
        self.appid = appid
        self.authcode = authcode

        self.TradingDay = ""
        self.FrontID = 0
        self.SessionID = 0
        self.OrderRef = 0

        self.api: tdapi.CThostFtdcTraderApi = tdapi.CThostFtdcTraderApi.CreateFtdcTraderApi()
        self.api.RegisterSpi(self)
        self.api.RegisterFront(host)
        self.api.SubscribePrivateTopic(tdapi.THOST_TERT_QUICK)
        self.api.SubscribePublicTopic(tdapi.THOST_TERT_QUICK)

    def Run(self):
        self.api.Init()

    def OnFrontConnected(self):
        print("OnFrontConnected")

        req = tdapi.CThostFtdcReqAuthenticateField()
        req.BrokerID = self.broker
        req.UserID = self.user
        req.AppID = self.appid
        req.AuthCode = self.authcode
        self.api.ReqAuthenticate(req, 0)

    def OnFrontDisconnected(self, nReason: int):
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
        req.UserProductInfo = "demo"
        self.api.ReqUserLogin(req, 0)

    def OnRspUserLogin(
            self,
            pRspUserLogin: tdapi.CThostFtdcRspUserLoginField,
            pRspInfo: tdapi.CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
    ):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"Login failed. {pRspInfo.ErrorMsg}")
            exit(-1)
        print(f"Login succeed. TradingDay: {pRspUserLogin.TradingDay}, MaxOrderRef: {pRspUserLogin.MaxOrderRef}, SystemName: {pRspUserLogin.SystemName}")
        self.TradingDay = pRspUserLogin.TradingDay
        self.FrontID = pRspUserLogin.FrontID
        self.SessionID = pRspUserLogin.SessionID
        self.OrderRef = 1

        if bIsLast == True:
            semaphore.release()

    def OnRspSettlementInfoConfirm(self, pSettlementInfoConfirm: "CThostFtdcSettlementInfoConfirmField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspSettlementInfoConfirm failed. {pRspInfo.ErrorMsg}")
            exit(-1)
        print(f"OnRspSettlementInfoConfirm: BrokerID:{pSettlementInfoConfirm.BrokerID}, InvestorID:{pSettlementInfoConfirm.InvestorID}, ConfirmDate:{pSettlementInfoConfirm.ConfirmDate}, ConfirmTime:{pSettlementInfoConfirm.ConfirmTime}, CurrencyID:{pSettlementInfoConfirm.CurrencyID}")

        if bIsLast == True:
            semaphore.release()

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
                f"PositionType={pInstrument.PositionType} "
                f"PositionDateType={pInstrument.PositionDateType} "
                f"PriceTick={pInstrument.PriceTick} "
                f"ExpireDate={pInstrument.ExpireDate} "
                f"UnderlyingInstrID={pInstrument.UnderlyingInstrID} "
                f"StrikePrice={pInstrument.StrikePrice} "
                f"OptionsType={pInstrument.OptionsType} "
                f"MinLimitOrderVolume={pInstrument.MinLimitOrderVolume} "
                f"MaxLimitOrderVolume={pInstrument.MaxLimitOrderVolume} "
            )
        if bIsLast == True:
           semaphore.release()

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
            semaphore.release()

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
            semaphore.release()

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
            semaphore.release()

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
            semaphore.release()

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
            semaphore.release()

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
            semaphore.release()

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
            semaphore.release()

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
            semaphore.release()

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
            semaphore.release()

    def OnRspQryInstrumentCommissionRate(self, pInstrumentCommissionRate: tdapi.CThostFtdcInstrumentCommissionRateField,
                                         pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryInstrumentCommissionRate failed: {pRspInfo.ErrorMsg}')
            exit(-1)
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
            semaphore.release()

    def OnRspQryInstrumentMarginRate(self, pInstrumentMarginRate: tdapi.CThostFtdcInstrumentMarginRateField,
                                     pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryInstrumentMarginRate failed: {pRspInfo.ErrorMsg}')
            exit(-1)
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
            semaphore.release()

    def OnRspQryInstrumentOrderCommRate(self, pInstrumentOrderCommRate: tdapi.CThostFtdcInstrumentOrderCommRateField,
                                        pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryInstrumentOrderCommRate failed: {pRspInfo.ErrorMsg}')
            exit(-1)
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
            semaphore.release()

    def OnRspQryTradingCode(self, pTradingCode: "CThostFtdcTradingCodeField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryTradingCode failed: {pRspInfo.ErrorMsg}')
            exit(-1)
        if pTradingCode is not None:
            print(f"OnRspQryTradingCode:"
                  f"BrokerID={pTradingCode.BrokerID} "
                  f"InvestorID={pTradingCode.InvestorID} "
                  f"ExchangeID={pTradingCode.ExchangeID} "
                  f"ClientID={pTradingCode.ClientID} "
                  )
        if bIsLast == True:
            semaphore.release()

    def OnRspQrySettlementInfo(self, pSettlementInfo: "CThostFtdcSettlementInfoField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQrySettlementInfo failed: {pRspInfo.ErrorMsg}')
            exit(-1)
        if pSettlementInfo is not None:
            # print(f"OnRspQrySettlementInfo:TradingDay={pSettlementInfo.TradingDay},InvestorID={pSettlementInfo.InvestorID},CurrencyID={pSettlementInfo.CurrencyID},Content={pSettlementInfo.Content}")
            print(pSettlementInfo.Content.decode('gbk'))
        if bIsLast == True:
            semaphore.release()

    def OnRtnInstrumentStatus(self, pInstrumentStatus: "CThostFtdcInstrumentStatusField") -> "void":
        print(f"OnRtnInstrumentStatus:"
              f"ExchangeID={pInstrumentStatus.ExchangeID} "
              f"InstrumentID={pInstrumentStatus.InstrumentID} "
              f"InstrumentStatus={pInstrumentStatus.InstrumentStatus}  "
              f"TradingSegmentSN={pInstrumentStatus.TradingSegmentSN} "
              f'EnterTime={pInstrumentStatus.EnterTime} '
              f"EnterReason={pInstrumentStatus.EnterReason} "
              )

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

    def QryCommissionRate(self, InstrumentID):
        req = tdapi.CThostFtdcQryInstrumentCommissionRateField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        req.InstrumentID = InstrumentID
        self.api.ReqQryInstrumentCommissionRate(req, 0)

    def QryMarginRate(self, ExchangeID, InstrumentID):
        req = tdapi.CThostFtdcQryInstrumentMarginRateField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        req.ExchangeID = ExchangeID
        req.InstrumentID = InstrumentID
        self.api.ReqQryInstrumentMarginRate(req, 0)

    def QryOrderCommRate(self, InstrumentID):
        req = tdapi.CThostFtdcQryInstrumentOrderCommRateField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        req.InstrumentID = InstrumentID
        self.api.ReqQryInstrumentOrderCommRate(req, 0)

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

if __name__ == "__main__":
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
    tdImpl = TdImpl(host, broker, user, password, appid, authcode)
    tdImpl.Run()

    # wait for login ok.
    semaphore.acquire()

    tdImpl.QrySettlementInfo("")

    tdImpl.ConfirmSettlementInfo()

    time.sleep(1)
    tdImpl.QryInstrument("SHFE", "au", "")
    semaphore.acquire()

    time.sleep(1)
    tdImpl.QryExchange()
    semaphore.acquire()

    time.sleep(1)
    tdImpl.QryProduct("","")
    semaphore.acquire()

    time.sleep(1)
    tdImpl.QryPosition("")
    semaphore.acquire()

    time.sleep(1)
    tdImpl.QryPositionDetail("")
    semaphore.acquire()

    tdImpl.QryOrder("")
    time.sleep(1)

    time.sleep(1)
    tdImpl.QryTrade("")
    semaphore.acquire()

    time.sleep(1)
    tdImpl.QryPrice("", "")
    semaphore.acquire()

    time.sleep(1)
    tdImpl.QryAccount()
    semaphore.acquire()

    time.sleep(1)
    tdImpl.QryCommissionRate("")
    semaphore.acquire()

    time.sleep(1)
    tdImpl.QryMarginRate("", "")
    semaphore.acquire()

    time.sleep(1)
    tdImpl.QryOrderCommRate("")
    semaphore.acquire()

    time.sleep(1)
    tdImpl.QryInvestor()
    semaphore.acquire()

    time.sleep(1)
    tdImpl.QryTradingCode()
    semaphore.acquire()

    # insert order
    print("New order ...")
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
    tdImpl.OrderInsert(ExchangeID, InstrumentID, Direction, Offset, PriceType, Price, Volume, TimeCondition,
                       VolumeCondition, MinVolume)

    # cancel order
    print("Cancel order ...")
    ExchangeID = input("ExchangeID:")
    InstrumentID = input("InstrumentID:")
    OrderSysID = input("OrderSysID:")
    FrontID = input("FrontID:")
    SessionID = input("SessionID:")
    OrderRef = input("OrderRef:")
    tdImpl.OrderCancel(ExchangeID, InstrumentID, OrderSysID, FrontID, SessionID, OrderRef)

    input("################# 按任意键退出 \n")
