// author: krenx@openctp
// last modify: 2024/5/10

#include <stdio.h>
#include <string>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>
#include "ThostFtdcTraderApi.h"


///TThostFtdcTradeCodeType	TradeCode;  银期转账业务功能码说明，更多功能码见文档“综合交易平台API开发常见问题列表”。
/*
常用功能码：
102001 银行发起银行资金转期货
102002 银行发起期货资金转银行
202001 期货发起银行资金转期货
202002 期货发起期货资金转银行
*/

class semaphore
{
public:
	semaphore(int value = 1) :count(value) {}

	void wait()
	{
		std::unique_lock<std::mutex> lck(mt);
		if (--count < 0)//资源不足挂起线程
			cv.wait(lck);
	}

	void signal()
	{
		std::unique_lock<std::mutex> lck(mt);
		if (++count <= 0)//有线程挂起，唤醒一个
			cv.notify_one();
	}

private:
	int count;
	std::mutex mt;
	std::condition_variable cv;
};

semaphore _semaphore(0);

class CApplication : public CThostFtdcTraderSpi
{
public:
	CApplication(std::string host, std::string broker, std::string user, std::string password, std::string appid, std::string authcode) :
		m_host(host),
		m_broker(broker),
		m_user(user),
		m_password(password),
		m_appid(appid),
		m_authcode(authcode)
	{
		memset(&m_Accountregister, 0x00, sizeof(m_Accountregister));
		m_pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
		m_pUserApi->RegisterSpi(this);
	}

	~CApplication()
	{
	}

	const std::string direction_to_string(TThostFtdcDirectionType Direction)
	{
		std::string str = Direction == THOST_FTDC_D_Buy ? "买" : "卖";
		return std::move(str);
	}

	const std::string posidirection_to_string(TThostFtdcPosiDirectionType Direction)
	{
		std::string str = Direction == THOST_FTDC_PD_Long ? "买" : "卖";
		return std::move(str);
	}

	double double_format(double value)
	{
		return value==DBL_MAX?0.0:value;
	}

	int Run()
	{
		m_pUserApi->RegisterFront((char*)m_host.c_str());
		m_pUserApi->SubscribePrivateTopic(THOST_TERT_QUICK);
		m_pUserApi->SubscribePublicTopic(THOST_TERT_QUICK);
		m_pUserApi->Init();

		return 0;
	}

	// 下单
	int OrderInsert(const char* ExchangeID, const char* InstrumentID, TThostFtdcDirectionType Direction, TThostFtdcOffsetFlagType OffsetFlag, double Price, unsigned int Qty)
	{
		CThostFtdcInputOrderField Req;

		memset(&Req, 0x00, sizeof(Req));
		strncpy_s(Req.BrokerID, m_broker.c_str(), sizeof(Req.BrokerID) - 1);
		strncpy_s(Req.InvestorID, m_user.c_str(), sizeof(Req.InvestorID) - 1);
		strncpy_s(Req.InstrumentID, InstrumentID, sizeof(Req.InstrumentID) - 1);
		strncpy_s(Req.ExchangeID, ExchangeID, sizeof(Req.ExchangeID) - 1);
		Req.Direction = Direction;
		Req.CombOffsetFlag[0] = OffsetFlag;
		Req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
		Req.VolumeTotalOriginal = Qty;
		Req.LimitPrice = Price;
		Req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
		sprintf_s(Req.OrderRef, "%d", m_nOrderRef++);
		Req.TimeCondition = THOST_FTDC_TC_GFD;
		if (Req.OrderPriceType == THOST_FTDC_OPT_AnyPrice)
			Req.TimeCondition = THOST_FTDC_TC_IOC;
		Req.VolumeCondition = THOST_FTDC_VC_AV;
		Req.MinVolume = 1;
		Req.ContingentCondition = THOST_FTDC_CC_Immediately;
		Req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
		Req.IsAutoSuspend = 0;
		Req.UserForceClose = 0;
		Req.RequestID = 1; // Only used by User
		strncpy_s(Req.InvestUnitID, "XXXX", sizeof(Req.InvestUnitID) - 1); // Only used by User

		return m_pUserApi->ReqOrderInsert(&Req, 0);
	}

	// 撤单
	int OrderCancel(const char* ExchangeID, const char* InstrumentID, const char* OrderSysID)
	{
		CThostFtdcInputOrderActionField Req;

		memset(&Req, 0x00, sizeof(Req));
		strncpy_s(Req.BrokerID, m_broker.c_str(), sizeof(Req.BrokerID) - 1);
		strncpy_s(Req.InvestorID, m_user.c_str(), sizeof(Req.InvestorID) - 1);
		strncpy_s(Req.InstrumentID, InstrumentID, sizeof(Req.InstrumentID) - 1);
		strncpy_s(Req.ExchangeID, ExchangeID, sizeof(Req.ExchangeID) - 1);
		strncpy_s(Req.OrderSysID, OrderSysID, sizeof(Req.OrderSysID) - 1);
		//Req.FrontID = 100;
		//Req.SessionID = 1;
		//strncpy_s(Req.OrderRef, "111", sizeof(Req.OrderRef) - 1);
		Req.ActionFlag = THOST_FTDC_AF_Delete;

		return m_pUserApi->ReqOrderAction(&Req, 0);
	}

	// 入金（银行资金转CTP柜台，密码为资金密码）
	int MoneyTransferToCTP(double Amount, const char* AccountPassword)
	{
		CThostFtdcReqTransferField ReqTransfer = { 0 };

		strncpy(ReqTransfer.TradeCode, "202001", sizeof(ReqTransfer.TradeCode) - 1);
		strncpy(ReqTransfer.AccountID, m_Accountregister.AccountID, sizeof(ReqTransfer.AccountID) - 1);
		strncpy(ReqTransfer.Password, AccountPassword, sizeof(ReqTransfer.Password) - 1);
		strncpy(ReqTransfer.BankID, m_Accountregister.BankID, sizeof(ReqTransfer.BankID) - 1);
		strncpy(ReqTransfer.BankBranchID, m_Accountregister.BankBranchID, sizeof(ReqTransfer.BankBranchID) - 1);
		strncpy(ReqTransfer.BankAccount, m_Accountregister.BankAccount, sizeof(ReqTransfer.BankAccount) - 1);
		ReqTransfer.BankAccType = m_Accountregister.BankAccType;
		strncpy(ReqTransfer.BrokerID, m_Accountregister.BrokerID, sizeof(ReqTransfer.BrokerID) - 1);
		strncpy(ReqTransfer.BrokerBranchID, m_Accountregister.BrokerBranchID, sizeof(ReqTransfer.BrokerBranchID) - 1);
		ReqTransfer.IdCardType = m_Accountregister.IdCardType;
		strncpy(ReqTransfer.IdentifiedCardNo, m_Accountregister.IdentifiedCardNo, sizeof(ReqTransfer.IdentifiedCardNo) - 1);
		strncpy(ReqTransfer.CurrencyID, m_Accountregister.CurrencyID, sizeof(ReqTransfer.CurrencyID) - 1);
		ReqTransfer.CustType = m_Accountregister.CustType;
		ReqTransfer.VerifyCertNoFlag = THOST_FTDC_YNI_No;
		ReqTransfer.SecuPwdFlag = THOST_FTDC_BPWDF_BlankCheck;
		ReqTransfer.TradeAmount = Amount;

		return m_pUserApi->ReqFromBankToFutureByFuture(&ReqTransfer, 0);
	}

	// 出金（CTP柜台资金转银行，密码为资金密码）
	int MoneyTransferToBank(double Amount, const char* AccountPassword)
	{
		CThostFtdcReqTransferField ReqTransfer = { 0 };

		strncpy(ReqTransfer.TradeCode, "202002", sizeof(ReqTransfer.TradeCode) - 1);
		strncpy(ReqTransfer.AccountID, m_Accountregister.AccountID, sizeof(ReqTransfer.AccountID) - 1);
		strncpy(ReqTransfer.Password, AccountPassword, sizeof(ReqTransfer.Password) - 1);
		strncpy(ReqTransfer.BankID, m_Accountregister.BankID, sizeof(ReqTransfer.BankID) - 1);
		strncpy(ReqTransfer.BankBranchID, m_Accountregister.BankBranchID, sizeof(ReqTransfer.BankBranchID) - 1);
		strncpy(ReqTransfer.BankAccount, m_Accountregister.BankAccount, sizeof(ReqTransfer.BankAccount) - 1);
		ReqTransfer.BankAccType = m_Accountregister.BankAccType;
		strncpy(ReqTransfer.BrokerID, m_Accountregister.BrokerID, sizeof(ReqTransfer.BrokerID) - 1);
		strncpy(ReqTransfer.BrokerBranchID, m_Accountregister.BrokerBranchID, sizeof(ReqTransfer.BrokerBranchID) - 1);
		ReqTransfer.IdCardType = m_Accountregister.IdCardType;
		strncpy(ReqTransfer.IdentifiedCardNo, m_Accountregister.IdentifiedCardNo, sizeof(ReqTransfer.IdentifiedCardNo) - 1);
		strncpy(ReqTransfer.CurrencyID, m_Accountregister.CurrencyID, sizeof(ReqTransfer.CurrencyID) - 1);
		ReqTransfer.CustType = m_Accountregister.CustType;
		ReqTransfer.VerifyCertNoFlag = THOST_FTDC_YNI_No;
		ReqTransfer.SecuPwdFlag = THOST_FTDC_BPWDF_BlankCheck;
		ReqTransfer.TradeAmount = Amount;

		return m_pUserApi->ReqFromFutureToBankByFuture(&ReqTransfer, 0);
	}

	int QueryBankAccountMoney(const char* Password)
	{
		CThostFtdcReqQueryAccountField ReqQueryAccount = { 0 };
		strcpy(ReqQueryAccount.TradeCode, "204002");
		strncpy(ReqQueryAccount.AccountID, m_Accountregister.AccountID, sizeof(ReqQueryAccount.AccountID) - 1);
		strncpy(ReqQueryAccount.BankID, m_Accountregister.BankID, sizeof(ReqQueryAccount.BankID) - 1);
		strncpy(ReqQueryAccount.BankBranchID, m_Accountregister.BankBranchID, sizeof(ReqQueryAccount.BankBranchID) - 1);
		strncpy(ReqQueryAccount.BankAccount, m_Accountregister.BankAccount, sizeof(ReqQueryAccount.BankAccount) - 1);
		ReqQueryAccount.BankAccType = m_Accountregister.BankAccType;
		strncpy(ReqQueryAccount.BrokerID, m_Accountregister.BrokerID, sizeof(ReqQueryAccount.BrokerID) - 1);
		strncpy(ReqQueryAccount.BrokerBranchID, m_Accountregister.BrokerBranchID, sizeof(ReqQueryAccount.BrokerBranchID) - 1);
		ReqQueryAccount.IdCardType = m_Accountregister.IdCardType;
		strncpy(ReqQueryAccount.IdentifiedCardNo, m_Accountregister.IdentifiedCardNo, sizeof(ReqQueryAccount.IdentifiedCardNo) - 1);
		strncpy(ReqQueryAccount.CurrencyID, m_Accountregister.CurrencyID, sizeof(ReqQueryAccount.CurrencyID) - 1);
		ReqQueryAccount.CustType = m_Accountregister.CustType;
		ReqQueryAccount.VerifyCertNoFlag = THOST_FTDC_YNI_No;
		ReqQueryAccount.SecuPwdFlag = THOST_FTDC_BPWDF_BlankCheck;
		strncpy(ReqQueryAccount.Password, Password, sizeof(ReqQueryAccount.Password) - 1);

		return m_pUserApi->ReqQueryBankAccountMoneyByFuture(&ReqQueryAccount, 0);
	}

	//连接成功
	void OnFrontConnected()
	{
		printf("Connected.\n");
		CThostFtdcReqAuthenticateField Req;
		memset(&Req, 0x00, sizeof(Req));
		strncpy_s(Req.BrokerID, m_broker.c_str(), sizeof(Req.BrokerID) - 1);
		strncpy_s(Req.UserID, m_user.c_str(), sizeof(Req.UserID) - 1);
		strncpy_s(Req.AuthCode, m_authcode.c_str(), sizeof(Req.AuthCode) - 1);
		strncpy_s(Req.AppID, m_appid.c_str(), sizeof(Req.AppID) - 1);
		m_pUserApi->ReqAuthenticate(&Req, 0);
	}

	//连接断开
	void OnFrontDisconnected(int nReason)
	{
		printf("Disconnected.\n");
	}


	///认证响应
	void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo->ErrorID != 0)
			printf("OnRspAuthenticate:%s\n", pRspInfo->ErrorMsg);
		else
			printf("Authenticate succeeded.\n");

		// 登录
		printf("Login ...\n");
		CThostFtdcReqUserLoginField Req;

		memset(&Req, 0x00, sizeof(Req));
		strncpy_s(Req.BrokerID, m_broker.c_str(), sizeof(Req.BrokerID) - 1);
		strncpy_s(Req.UserID, m_user.c_str(), sizeof(Req.UserID) - 1);
		strncpy_s(Req.Password, m_password.c_str(), sizeof(Req.Password) - 1);
		m_pUserApi->ReqUserLogin(&Req, 0);
	}


	//登录应答
	void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("Login failed. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}
		printf("Login succeeded.TradingDay:%s,FrontID=%d,SessionID=%d\n", pRspUserLogin->TradingDay, pRspUserLogin->FrontID, pRspUserLogin->SessionID);
		m_nOrderRef = atol(pRspUserLogin->MaxOrderRef);

		// 确认结算单
		CThostFtdcSettlementInfoConfirmField SettlementInfoConfirmField;

		memset(&SettlementInfoConfirmField, 0x00, sizeof(SettlementInfoConfirmField));
		strncpy_s(SettlementInfoConfirmField.BrokerID, pRspUserLogin->BrokerID, sizeof(SettlementInfoConfirmField.BrokerID) - 1);
		strncpy_s(SettlementInfoConfirmField.InvestorID, pRspUserLogin->UserID, sizeof(SettlementInfoConfirmField.InvestorID) - 1);
		strncpy_s(SettlementInfoConfirmField.ConfirmDate, pRspUserLogin->TradingDay, sizeof(SettlementInfoConfirmField.ConfirmDate) - 1);
		strncpy_s(SettlementInfoConfirmField.ConfirmTime, pRspUserLogin->LoginTime, sizeof(SettlementInfoConfirmField.ConfirmTime) - 1);
		m_pUserApi->ReqSettlementInfoConfirm(&SettlementInfoConfirmField, 0);

		_semaphore.signal();
	}

	// 下单应答
	void OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspOrderInsert. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}
		printf("OnRspOrderInsert:InstrumentID:%s,ExchangeID:%s,VolumeTotalOriginal:%d,LimitPrice:%lf,RequestID:%d,InvestUnitID:%s\n", pInputOrder->InstrumentID, pInputOrder->ExchangeID, pInputOrder->VolumeTotalOriginal, pInputOrder->LimitPrice, pInputOrder->RequestID, pInputOrder->InvestUnitID);
	}

	// 撤单应答
	void OnRspOrderAction(CThostFtdcInputOrderActionField* pInputOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspOrderAction. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}
		printf("OnRspOrderAction:InstrumentID:%s,ExchangeID:%s,OrderSysID:%s,FrontID:%d,SessionID:%d,OrderRef:%s,RequestID:%d,InvestUnitID:%s\n",pInputOrderAction->InstrumentID,pInputOrderAction->ExchangeID,pInputOrderAction->OrderSysID, pInputOrderAction->FrontID, pInputOrderAction->SessionID, pInputOrderAction->OrderRef,pInputOrderAction->RequestID,pInputOrderAction->InvestUnitID);
	}

	/*产品查询应答*/
	void OnRspQryProduct(CThostFtdcProductField* pProduct, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pProduct)
			printf("OnRspQryProduct:ProductID:%s,ProductName:%s,ProductClass:%c,ExchangeID:%s\n", pProduct->ProductID, pProduct->ProductName, pProduct->ProductClass, pProduct->ExchangeID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	/*交易所查询应答*/
	void OnRspQryExchange(CThostFtdcExchangeField* pExchange, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pExchange)
			printf("OnRspQryExchange:ExchangeID:%s,ExchangeName:%s\n", pExchange->ExchangeID, pExchange->ExchangeName);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	/*投资者手续费率查询应答*/
	void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField* pInstrumentCommissionRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pInstrumentCommissionRate)
			printf("OnRspQryInstrumentCommissionRate:BrokerID:%s,InvestorID:%s,InvestorRange:%c,ExchangeID:%s,InstrumentID:%s,OpenRatioByMoney:%lf,CloseRatioByMoney:%lf,CloseTodayRatioByMoney:%lf,OpenRatioByVolume:%lf,CloseRatioByVolume:%lf,CloseTodayRatioByVolume:%lf\n",
				pInstrumentCommissionRate->BrokerID, pInstrumentCommissionRate->InvestorID, pInstrumentCommissionRate->InvestorRange,
				pInstrumentCommissionRate->ExchangeID, pInstrumentCommissionRate->InstrumentID,
				pInstrumentCommissionRate->OpenRatioByMoney, pInstrumentCommissionRate->CloseRatioByMoney, pInstrumentCommissionRate->CloseTodayRatioByMoney,
				pInstrumentCommissionRate->OpenRatioByVolume, pInstrumentCommissionRate->CloseRatioByVolume, pInstrumentCommissionRate->CloseTodayRatioByVolume);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	/*申报手续费率查询应答*/
	void OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField* pInstrumentOrderCommRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pInstrumentOrderCommRate)
			printf("OnRspQryInstrumentOrderCommRate:BrokerID:%s,InvestorID:%s,InvestorRange:%c,ExchangeID:%s,InstrumentID:%s,OrderCommByVolume:%lf,OrderActionCommByVolume:%lf,HedgeFlag:%c\n",
				pInstrumentOrderCommRate->BrokerID, pInstrumentOrderCommRate->InvestorID, pInstrumentOrderCommRate->InvestorRange,
				pInstrumentOrderCommRate->ExchangeID, pInstrumentOrderCommRate->InstrumentID,
				pInstrumentOrderCommRate->OrderCommByVolume, pInstrumentOrderCommRate->OrderActionCommByVolume, pInstrumentOrderCommRate->HedgeFlag);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	/*投资者保证金率查询应答*/
	void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField* pInstrumentMarginRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pInstrumentMarginRate)
			printf("OnRspQryInstrumentMarginRate:BrokerID:%s,InvestorID:%s,InvestorRange:%c,ExchangeID:%s,InstrumentID:%s,LongMarginRatioByMoney:%lf,LongMarginRatioByVolume:%lf,ShortMarginRatioByMoney:%lf,ShortMarginRatioByVolume:%lf,HedgeFlag:%c\n",
				pInstrumentMarginRate->BrokerID, pInstrumentMarginRate->InvestorID, pInstrumentMarginRate->InvestorRange,
				pInstrumentMarginRate->ExchangeID, pInstrumentMarginRate->InstrumentID,
				pInstrumentMarginRate->LongMarginRatioByMoney, pInstrumentMarginRate->LongMarginRatioByVolume, pInstrumentMarginRate->ShortMarginRatioByMoney,
				pInstrumentMarginRate->ShortMarginRatioByVolume,pInstrumentMarginRate->HedgeFlag);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	///请求查询交易所保证金率响应
	void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField* pExchangeMarginRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pExchangeMarginRate)
			printf("OnRspQryExchangeMarginRate:ExchangeID:%s,InstrumentID:%s,LongMarginRatioByMoney:%lf,LongMarginRatioByVolume:%lf,ShortMarginRatioByMoney:%lf,ShortMarginRatioByVolume:%lf,HedgeFlag:%c\n",
				pExchangeMarginRate->ExchangeID, pExchangeMarginRate->InstrumentID,
				pExchangeMarginRate->LongMarginRatioByMoney, pExchangeMarginRate->LongMarginRatioByVolume, pExchangeMarginRate->ShortMarginRatioByMoney,
				pExchangeMarginRate->ShortMarginRatioByVolume,pExchangeMarginRate->HedgeFlag);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	///请求查询交易所调整保证金率响应
	void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField* pExchangeMarginRateAdjust, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pExchangeMarginRateAdjust)
			printf("OnRspQryExchangeMarginRateAdjust:InstrumentID:%s,LongMarginRatioByMoney:%lf,LongMarginRatioByVolume:%lf,ShortMarginRatioByMoney:%lf,ShortMarginRatioByVolume:%lf,ExchLongMarginRatioByMoney:%lf,ExchLongMarginRatioByVolume:%lf,ExchShortMarginRatioByMoney:%lf,ExchShortMarginRatioByVolume:%lf\n",
				pExchangeMarginRateAdjust->InstrumentID,
				pExchangeMarginRateAdjust->LongMarginRatioByMoney, pExchangeMarginRateAdjust->LongMarginRatioByVolume, pExchangeMarginRateAdjust->ShortMarginRatioByMoney,
				pExchangeMarginRateAdjust->ShortMarginRatioByVolume, pExchangeMarginRateAdjust->ExchLongMarginRatioByMoney, pExchangeMarginRateAdjust->ExchLongMarginRatioByVolume,
				pExchangeMarginRateAdjust->ExchShortMarginRatioByMoney, pExchangeMarginRateAdjust->ExchShortMarginRatioByVolume);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	///请求查询投资者品种/跨品种保证金响应
	void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField* pInvestorProductGroupMargin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pInvestorProductGroupMargin)
			printf("OnRspQryInvestorProductGroupMargin:ExchangeID:%s,ProductGroupID:%s,FrozenMargin:%lf,LongFrozenMargin:%lf,ShortFrozenMargin:%lf,UseMargin:%lf,LongUseMargin:%lf,ShortUseMargin:%lf,CloseProfit:%lf,FrozenCommission:%lf,Commission:%lf,FrozenCash:%lf\n",
				pInvestorProductGroupMargin->ExchangeID,
				pInvestorProductGroupMargin->ProductGroupID, pInvestorProductGroupMargin->FrozenMargin, pInvestorProductGroupMargin->LongFrozenMargin,
				pInvestorProductGroupMargin->ShortFrozenMargin, pInvestorProductGroupMargin->UseMargin, pInvestorProductGroupMargin->LongUseMargin, pInvestorProductGroupMargin->ShortUseMargin,
				pInvestorProductGroupMargin->CloseProfit, pInvestorProductGroupMargin->FrozenCommission, pInvestorProductGroupMargin->Commission, pInvestorProductGroupMargin->FrozenCash);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	///请求查询期权合约手续费响应
	void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField* pOptionInstrCommRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pOptionInstrCommRate)
			printf("OnRspQryOptionInstrCommRate:BrokerID:%s,InvestorID:%s,InvestorRange:%c,ExchangeID:%s,InstrumentID:%s,OpenRatioByMoney:%lf,CloseRatioByMoney:%lf,CloseTodayRatioByMoney:%lf,OpenRatioByVolume:%lf,CloseRatioByVolume:%lf,CloseTodayRatioByVolume:%lf,StrikeRatioByMoney:%lf,StrikeRatioByVolume:%lf\n",
				pOptionInstrCommRate->BrokerID, pOptionInstrCommRate->InvestorID, pOptionInstrCommRate->InvestorRange,
				pOptionInstrCommRate->ExchangeID, pOptionInstrCommRate->InstrumentID,
				pOptionInstrCommRate->OpenRatioByMoney, pOptionInstrCommRate->CloseRatioByMoney, pOptionInstrCommRate->CloseTodayRatioByMoney,
				pOptionInstrCommRate->OpenRatioByVolume, pOptionInstrCommRate->CloseRatioByVolume, pOptionInstrCommRate->CloseTodayRatioByVolume,
				pOptionInstrCommRate->StrikeRatioByMoney, pOptionInstrCommRate->StrikeRatioByVolume);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询合约列表
	void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pInstrument)
			printf("OnRspQryInstrument:InstrumentID:%s,InstrumentName:%s,ProductID:%s,PriceTick:%lf,UnderlyingInstrID:%s,StrikePrice:%lf,ExchangeID:%s\n", pInstrument->InstrumentID, pInstrument->InstrumentName, pInstrument->ProductID, pInstrument->PriceTick, pInstrument->UnderlyingInstrID, pInstrument->StrikePrice, pInstrument->ExchangeID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询行情列表
	void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQryDepthMarketData. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if(pDepthMarketData)
			printf("OnRspQryDepthMarketData:InstrumentID:%s,LastPrice:%lf,Volume:%d,Turnover:%lf,OpenPrice:%lf,HighestPrice:%lf,LowestPrice:%lf,UpperLimitPrice:%lf,LowerLimitPrice:%lf,OpenInterest:%lf,PreClosePrice:%lf,PreSettlementPrice:%lf,SettlementPrice:%lf,UpdateTime:%s,ActionDay:%s,TradingDay:%s,ExchangeID:%s\n",
				pDepthMarketData->InstrumentID, double_format(pDepthMarketData->LastPrice), pDepthMarketData->Volume, double_format(pDepthMarketData->Turnover), double_format(pDepthMarketData->OpenPrice),
				double_format(pDepthMarketData->HighestPrice), double_format(pDepthMarketData->LowestPrice), double_format(pDepthMarketData->UpperLimitPrice), double_format(pDepthMarketData->LowerLimitPrice),
				double_format(pDepthMarketData->OpenInterest), double_format(pDepthMarketData->PreClosePrice), double_format(pDepthMarketData->PreSettlementPrice),
				double_format(pDepthMarketData->SettlementPrice), pDepthMarketData->UpdateTime, pDepthMarketData->ActionDay, pDepthMarketData->TradingDay, pDepthMarketData->ExchangeID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询委托列表
	void OnRspQryOrder(CThostFtdcOrderField* pOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQryOrder. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if(pOrder)
			printf("OnRspQryOrder:BrokerID:%s,BrokerOrderSeq:%d,OrderLocalID:%s,InstrumentID:%s,Direction:%s,VolumeTotalOriginal:%d,LimitPrice:%lf,VolumeTraded:%d,VolumeTotal:%d,OrderSysID:%s,FrontID:%d,SessionID:%d,OrderRef:%s,OrderStatus:%c,StatusMsg:%s,ExchangeID:%s,InsertTime:%s,ClientID:%s,RequestID:%d,InvestUnitID:%s\n",
				pOrder->BrokerID,pOrder->BrokerOrderSeq,pOrder->OrderLocalID, pOrder->InstrumentID, direction_to_string(pOrder->Direction).c_str(), pOrder->VolumeTotalOriginal, pOrder->LimitPrice, pOrder->VolumeTraded, pOrder->VolumeTotal, pOrder->OrderSysID, pOrder->FrontID, pOrder->SessionID, pOrder->OrderRef, pOrder->OrderStatus, pOrder->StatusMsg, pOrder->ExchangeID, pOrder->InsertTime,pOrder->ClientID,pOrder->RequestID,pOrder->InvestUnitID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询成交列表
	void OnRspQryTrade(CThostFtdcTradeField* pTrade, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQryTrade. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if(pTrade)
			printf("OnRspQryTrade:BrokerID:%s,BrokerOrderSeq:%d,OrderLocalID:%s,InstrumentID:%s,Direction:%s,Volume:%d,Price:%lf,OrderSysID:%s,TradeID:%s,OrderRef:%s,ExchangeID:%s,TradeTime:%s,ClientID:%s,InvestUnitID:%s\n",
				pTrade->BrokerID, pTrade->BrokerOrderSeq, pTrade->OrderLocalID, pTrade->InstrumentID, direction_to_string(pTrade->Direction).c_str(), pTrade->Volume, pTrade->Price, pTrade->OrderSysID, pTrade->TradeID, pTrade->OrderRef, pTrade->ExchangeID, pTrade->TradeTime,pTrade->ClientID,pTrade->InvestUnitID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询持仓
	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pInvestorPosition, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQryInvestorPosition. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if (pInvestorPosition)
			printf("OnRspQryInvestorPosition:InstrumentID:%s,PosiDirection:%s,HedgeFlag:%c,Position:%d,YdPosition:%d,TodayPosition:%d,PositionCost:%lf,OpenCost:%lf,ExchangeID:%s,PositionDate:%c,TradingDay:%s\n",
				pInvestorPosition->InstrumentID, posidirection_to_string(pInvestorPosition->PosiDirection).c_str(), pInvestorPosition->HedgeFlag, pInvestorPosition->Position, pInvestorPosition->YdPosition, pInvestorPosition->TodayPosition, pInvestorPosition->PositionCost, pInvestorPosition->OpenCost, pInvestorPosition->ExchangeID, pInvestorPosition->PositionDate, pInvestorPosition->TradingDay);

		if (bIsLast) {
			_semaphore.signal();
		}
	}


	// 查询持仓明细
	void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField* pInvestorPositionDetail, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQryInvestorPositionDetail. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if (pInvestorPositionDetail)
			printf("OnRspQryInvestorPositionDetail:InstrumentID:%s,Direction:%s,HedgeFlag:%c,Volume:%d,CloseVolume:%d,OpenDate:%s,OpenPrice:%lf,Margin:%lf,ExchangeID:%s,LastSettlementPrice=%lf,SettlementPrice=%lf\n",
				pInvestorPositionDetail->InstrumentID, direction_to_string(pInvestorPositionDetail->Direction).c_str(), pInvestorPositionDetail->HedgeFlag, pInvestorPositionDetail->Volume, pInvestorPositionDetail->CloseVolume, pInvestorPositionDetail->OpenDate, pInvestorPositionDetail->OpenPrice, pInvestorPositionDetail->Margin, pInvestorPositionDetail->ExchangeID,pInvestorPositionDetail->LastSettlementPrice,pInvestorPositionDetail->SettlementPrice);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	///请求查询资金账户响应
	void OnRspQryTradingAccount(CThostFtdcTradingAccountField* pTradingAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pTradingAccount)
			printf("OnRspQryTradingAccount:AccountID:%s,Available:%lf,FrozenCash:%lf,FrozenCommission:%lf\n",
				pTradingAccount->AccountID, pTradingAccount->Available, pTradingAccount->FrozenCash, pTradingAccount->FrozenCommission);

		if (bIsLast) {
			_semaphore.signal();
		}
	}


	// 委托回报
	void OnRtnOrder(CThostFtdcOrderField* pOrder)
	{
		printf("OnRtnOrder:BrokerID:%s,BrokerOrderSeq:%d,OrderLocalID:%s,InstrumentID:%s,Direction:%s,VolumeTotalOriginal:%d,LimitPrice:%lf,VolumeTraded:%d,VolumeTotal:%d,OrderSysID:%s,FrontID:%d,SessionID:%d,OrderRef:%s,OrderStatus:%c,StatusMsg:%s,ExchangeID:%s,InsertTime:%s,ClientID:%s,RequestID:%d,InvestUnitID:%s\n",
			pOrder->BrokerID, pOrder->BrokerOrderSeq, pOrder->OrderLocalID, pOrder->InstrumentID, direction_to_string(pOrder->Direction).c_str(), pOrder->VolumeTotalOriginal, pOrder->LimitPrice, pOrder->VolumeTraded, pOrder->VolumeTotal, pOrder->OrderSysID, pOrder->FrontID, pOrder->SessionID, pOrder->OrderRef, pOrder->OrderStatus, pOrder->StatusMsg, pOrder->ExchangeID, pOrder->InsertTime,pOrder->ClientID,pOrder->RequestID,pOrder->InvestUnitID);
	}

	// 成交回报
	void OnRtnTrade(CThostFtdcTradeField* pTrade)
	{
		printf("OnRtnTrade:BrokerID:%s,BrokerOrderSeq:%d,OrderLocalID:%s,InstrumentID:%s,Direction:%s,Volume:%d,Price:%lf,OrderSysID:%s,TradeID:%s,OrderRef:%s,ExchangeID:%s,TradeTime:%s,ClientID:%s,InvestUnitID:%s\n",
			pTrade->BrokerID, pTrade->BrokerOrderSeq, pTrade->OrderLocalID, pTrade->InstrumentID, direction_to_string(pTrade->Direction).c_str(), pTrade->Volume, pTrade->Price, pTrade->OrderSysID, pTrade->TradeID, pTrade->OrderRef, pTrade->ExchangeID, pTrade->TradeTime,pTrade->ClientID,pTrade->InvestUnitID);
	}

	// 报单错误
	void OnErrRtnOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0)
			printf("OnErrRtnOrderInsert. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);

		if(pInputOrder)
			printf("OnErrRtnOrderInsert:OrderRef:%s,InstrumentID:%s,Direction:%s,VolumeTotalOriginal:%d,LimitPrice:%lf,ExchangeID:%s,RequestID:%d,InvestUnitID:%s\n",
				pInputOrder->OrderRef, pInputOrder->InstrumentID, direction_to_string(pInputOrder->Direction).c_str(), pInputOrder->VolumeTotalOriginal, pInputOrder->LimitPrice, pInputOrder->ExchangeID, pInputOrder->RequestID, pInputOrder->InvestUnitID);
	}


	// 撤单错误回报
	void OnErrRtnOrderAction(CThostFtdcOrderActionField* pOrderAction, CThostFtdcRspInfoField* pRspInfo)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0)
			printf("OnErrRtnOrderAction. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);

		if (pOrderAction)
			printf("OnErrRtnOrderAction:FrontID:%d,SessionID:%d,OrderRef:%s,InstrumentID:%s,OrderActionRef:%d,OrderSysID:%s,LimitPrice:%lf,ExchangeID:%s,RequestID:%d,InvestUnitID:%s\n",
				pOrderAction->FrontID, pOrderAction->SessionID, pOrderAction->OrderRef, pOrderAction->InstrumentID, pOrderAction->OrderActionRef, pOrderAction->OrderSysID, pOrderAction->LimitPrice, pOrderAction->ExchangeID, pOrderAction->RequestID, pOrderAction->InvestUnitID);
	}

	///请求查询转帐流水响应
	void OnRspQryTransferSerial(CThostFtdcTransferSerialField* pTransferSerial, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pTransferSerial)
			printf("OnRspQryTransferSerial:AccountID:%s,BankAccount:%s,TradeAmount:%lf,FutureSerial:%d\n",
				pTransferSerial->AccountID, pTransferSerial->BankAccount, pTransferSerial->TradeAmount, pTransferSerial->FutureSerial);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	///请求查询银期签约关系响应
	void OnRspQryAccountregister(CThostFtdcAccountregisterField* pAccountregister, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pAccountregister) {
			printf("OnRspQryAccountregister:AccountID:%s,BankID:%s,BankAccount:%s\n",
				pAccountregister->AccountID, pAccountregister->BankID, pAccountregister->BankAccount);
			memcpy(&m_Accountregister, pAccountregister, sizeof(m_Accountregister));
		}

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	///银行发起银行资金转期货通知
	void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField* pRspTransfer)
	{
		printf("OnRtnFromBankToFutureByBank:AccountID:%s,BankAccount:%s,TradeAmount:%lf,BankID:%s,TradeCode:%s,PlateSerial:%d,ErrorMsg:%s\n", pRspTransfer->AccountID, pRspTransfer->BankAccount, pRspTransfer->TradeAmount, pRspTransfer->BankID, pRspTransfer->TradeCode, pRspTransfer->PlateSerial, pRspTransfer->ErrorMsg);
	}

	///银行发起期货资金转银行通知
	void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField* pRspTransfer)
	{
		printf("OnRtnFromFutureToBankByBank:AccountID:%s,BankAccount:%s,TradeAmount:%lf,BankID:%s,TradeCode:%s,PlateSerial:%d,ErrorMsg:%s\n", pRspTransfer->AccountID, pRspTransfer->BankAccount, pRspTransfer->TradeAmount, pRspTransfer->BankID, pRspTransfer->TradeCode, pRspTransfer->PlateSerial, pRspTransfer->ErrorMsg);
	}

	///银行发起冲正银行转期货通知
	void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField* pRspRepeal)
	{
	}

	///银行发起冲正期货转银行通知
	void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField* pRspRepeal)
	{
	}

	///期货发起银行资金转期货通知
	void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField* pRspTransfer)
	{
		printf("OnRtnFromBankToFutureByFuture:AccountID:%s,BankAccount:%s,TradeAmount:%lf,BankID:%s,TradeCode:%s,PlateSerial:%d,ErrorMsg:%s\n", pRspTransfer->AccountID, pRspTransfer->BankAccount, pRspTransfer->TradeAmount, pRspTransfer->BankID, pRspTransfer->TradeCode, pRspTransfer->PlateSerial, pRspTransfer->ErrorMsg);
	}

	///期货发起期货资金转银行通知
	void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField* pRspTransfer)
	{
		printf("OnRtnFromFutureToBankByFuture:AccountID:%s,BankAccount:%s,TradeAmount:%lf,BankID:%s,TradeCode:%s,PlateSerial:%d,ErrorMsg:%s\n", pRspTransfer->AccountID, pRspTransfer->BankAccount, pRspTransfer->TradeAmount, pRspTransfer->BankID, pRspTransfer->TradeCode, pRspTransfer->PlateSerial, pRspTransfer->ErrorMsg);
	}

	///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
	void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField* pRspRepeal)
	{
	}

	///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
	void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField* pRspRepeal)
	{
	}

	///期货发起查询银行余额通知
	void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField* pNotifyQueryAccount)
	{
		printf("OnRtnQueryBankBalanceByFuture:AccountID:%s,BankAccount:%s,BankFetchAmount:%lf,BankID:%s,TradeCode:%s,PlateSerial:%d,ErrorMsg:%s\n", pNotifyQueryAccount->AccountID, pNotifyQueryAccount->BankAccount, pNotifyQueryAccount->BankFetchAmount, pNotifyQueryAccount->BankID, pNotifyQueryAccount->TradeCode, pNotifyQueryAccount->PlateSerial, pNotifyQueryAccount->ErrorMsg);
	}

	///期货发起银行资金转期货错误回报
	void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField* pReqTransfer, CThostFtdcRspInfoField* pRspInfo)
	{
	}

	///期货发起期货资金转银行错误回报
	void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField* pReqTransfer, CThostFtdcRspInfoField* pRspInfo)
	{
	}

	///系统运行时期货端手工发起冲正银行转期货错误回报
	void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField* pReqRepeal, CThostFtdcRspInfoField* pRspInfo)
	{
	}

	///系统运行时期货端手工发起冲正期货转银行错误回报
	void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField* pReqRepeal, CThostFtdcRspInfoField* pRspInfo)
	{
	}

	///期货发起查询银行余额错误回报
	void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField* pReqQueryAccount, CThostFtdcRspInfoField* pRspInfo)
	{
	}

	///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
	void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField* pRspRepeal)
	{
	}

	///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
	void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField* pRspRepeal)
	{
	}

	///期货发起银行资金转期货应答
	void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField* pReqTransfer, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspFromBankToFutureByFuture. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}
		if (pReqTransfer)
			printf("OnRspFromBankToFutureByFuture:AccountID:%s,BankAccount:%s,TradeAmount:%lf,BankID:%s,TradeCode:%s,PlateSerial:%d\n", pReqTransfer->AccountID, pReqTransfer->BankAccount, pReqTransfer->TradeAmount, pReqTransfer->BankID, pReqTransfer->TradeCode, pReqTransfer->PlateSerial);
	}

	///期货发起期货资金转银行应答
	void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField* pReqTransfer, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspFromFutureToBankByFuture. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}
		if (pReqTransfer)
			printf("OnRspFromFutureToBankByFuture:AccountID:%s,BankAccount:%s,TradeAmount:%lf,BankID:%s,TradeCode:%s,PlateSerial:%d\n", pReqTransfer->AccountID, pReqTransfer->BankAccount, pReqTransfer->TradeAmount, pReqTransfer->BankID, pReqTransfer->TradeCode, pReqTransfer->PlateSerial);
	}

	///请求查询签约银行响应
	void OnRspQryContractBank(CThostFtdcContractBankField* pContractBank, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQryContractBank. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if (pContractBank)
			printf("OnRspQryContractBank:BankID:%s,BankBrchID:%s,BankName:%s\n",
				pContractBank->BankID, pContractBank->BankBrchID, pContractBank->BankName);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	///期货发起查询银行余额应答
	void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField* pReqQueryAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQueryBankAccountMoneyByFuture. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if (pReqQueryAccount)
			printf("OnRspQueryBankAccountMoneyByFuture:AccountID:%s,BankAccount:%s,BankID:%s,TradeCode:%s,PlateSerial:%d\n", pReqQueryAccount->AccountID, pReqQueryAccount->BankAccount, pReqQueryAccount->BankID, pReqQueryAccount->TradeCode, pReqQueryAccount->PlateSerial);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

public:
	std::string m_host;
	std::string m_broker;
	std::string m_user;
	std::string m_password;
	std::string m_appid;
	std::string m_authcode;
	unsigned int m_nOrderRef;

	CThostFtdcAccountregisterField m_Accountregister;

	CThostFtdcTraderApi* m_pUserApi;
};


void display_usage()
{
	printf("usage:ctpprint host broker user password appid authcode\n");
	printf("example:ctpprint tcp://180.168.146.187:10130 9999 000001 888888 simnow_client_test 0000000000000000\n");
}


int main(int argc, char* argv[])
{
	if (argc != 7) {
		display_usage();
		return -1;
	}

	std::string host(argv[1]), broker(argv[2]), user(argv[3]), password(argv[4]), appid(argv[5]), authcode(argv[6]);

	CApplication Spi(host, broker, user, password, appid, authcode);

	// 启动
	if (Spi.Run() < 0)
		return -1;

	// 等待登录完成
	_semaphore.wait();

	// 查询交易所
	printf("查询交易所 ...\n");
	CThostFtdcQryExchangeField QryExchange = { 0 };
	Spi.m_pUserApi->ReqQryExchange(&QryExchange, 0);
	_semaphore.wait();

	// 查询品种
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询品种 ...\n");
	CThostFtdcQryProductField QryProduct = { 0 };
	Spi.m_pUserApi->ReqQryProduct(&QryProduct, 0);
	_semaphore.wait();

	// 查询投资者手续费率
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询投资者手续费率 ...\n");
	CThostFtdcQryInstrumentCommissionRateField QryInstrumentCommissionRate = { 0 };
	strncpy(QryInstrumentCommissionRate.BrokerID, broker.c_str(), sizeof(QryInstrumentCommissionRate.BrokerID) - 1);
	strncpy(QryInstrumentCommissionRate.InvestorID, user.c_str(), sizeof(QryInstrumentCommissionRate.InvestorID) - 1);
	strncpy(QryInstrumentCommissionRate.ExchangeID, "SHFE", sizeof(QryInstrumentCommissionRate.ExchangeID) - 1);
	strncpy(QryInstrumentCommissionRate.InstrumentID, "au2512", sizeof(QryInstrumentCommissionRate).InstrumentID - 1);
	Spi.m_pUserApi->ReqQryInstrumentCommissionRate(&QryInstrumentCommissionRate, 0);
	_semaphore.wait();

	// 查询投资者保证金率
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询投资者保证金率 ...\n");
	CThostFtdcQryInstrumentMarginRateField QryInstrumentMarginRate = { 0 };
	strncpy(QryInstrumentMarginRate.BrokerID, broker.c_str(), sizeof(QryInstrumentMarginRate.BrokerID) - 1);
	strncpy(QryInstrumentMarginRate.InvestorID, user.c_str(), sizeof(QryInstrumentMarginRate.InvestorID) - 1);
	strncpy(QryInstrumentMarginRate.ExchangeID, "SHFE", sizeof(QryInstrumentMarginRate.ExchangeID) - 1);
	strncpy(QryInstrumentMarginRate.InstrumentID, "au2512", sizeof(QryInstrumentMarginRate.InstrumentID) - 1);
	QryInstrumentMarginRate.HedgeFlag = THOST_FTDC_HF_Speculation;
	Spi.m_pUserApi->ReqQryInstrumentMarginRate(&QryInstrumentMarginRate, 0);
	_semaphore.wait();

	// 查询交易所保证金率
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询交易所保证金率 ...\n");
	CThostFtdcQryExchangeMarginRateField QryExchangeMarginRate = { 0 };
	strncpy(QryExchangeMarginRate.BrokerID, broker.c_str(), sizeof(QryExchangeMarginRate.BrokerID) - 1);
	strncpy(QryExchangeMarginRate.ExchangeID, "SHFE", sizeof(QryExchangeMarginRate.ExchangeID) - 1);
	strncpy(QryExchangeMarginRate.InstrumentID, "au2512", sizeof(QryExchangeMarginRate.InstrumentID) - 1);
	QryExchangeMarginRate.HedgeFlag = THOST_FTDC_HF_Speculation;
	Spi.m_pUserApi->ReqQryExchangeMarginRate(&QryExchangeMarginRate, 0);
	_semaphore.wait();

	// 查询交易所调整保证金率
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询交易所调整保证金率 ...\n");
	CThostFtdcQryExchangeMarginRateAdjustField QryExchangeMarginRateAdjust = { 0 };
	strncpy(QryExchangeMarginRateAdjust.BrokerID, broker.c_str(), sizeof(QryExchangeMarginRateAdjust.BrokerID) - 1);
	strncpy(QryExchangeMarginRateAdjust.InstrumentID, "au2512", sizeof(QryExchangeMarginRateAdjust.InstrumentID) - 1);
	QryExchangeMarginRateAdjust.HedgeFlag = THOST_FTDC_HF_Speculation;
	Spi.m_pUserApi->ReqQryExchangeMarginRateAdjust(&QryExchangeMarginRateAdjust, 0);
	_semaphore.wait();

	///请求查询投资者品种/跨品种保证金
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询投资者品种/跨品种保证金 ...\n");
	CThostFtdcQryInvestorProductGroupMarginField QryInvestorProductGroupMargin = { 0 };
	strncpy(QryInvestorProductGroupMargin.BrokerID, broker.c_str(), sizeof(QryInvestorProductGroupMargin.BrokerID) - 1);
	strncpy(QryInvestorProductGroupMargin.ExchangeID, "SHFE", sizeof(QryInvestorProductGroupMargin.ExchangeID) - 1);
	QryInvestorProductGroupMargin.HedgeFlag = THOST_FTDC_HF_Speculation;
	Spi.m_pUserApi->ReqQryInvestorProductGroupMargin(&QryInvestorProductGroupMargin, 0);
	_semaphore.wait();

	// 查询合约
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询合约 ...\n");
	CThostFtdcQryInstrumentField QryInstrument = { 0 };
	Spi.m_pUserApi->ReqQryInstrument(&QryInstrument, 0);
	_semaphore.wait();

	// 查询申报手续费率（报撤单费率，主要是中金所有此项费用，大连好像要报撤单笔数达到5000笔之上才收）
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询申报手续费率 ...\n");
	CThostFtdcQryInstrumentOrderCommRateField QryInstrumentOrderCommRate = { 0 };
	strncpy(QryInstrumentOrderCommRate.BrokerID, broker.c_str(), sizeof(QryInstrumentOrderCommRate.BrokerID) - 1);
	strncpy(QryInstrumentOrderCommRate.InvestorID, user.c_str(), sizeof(QryInstrumentOrderCommRate.InvestorID) - 1);
	strncpy(QryInstrumentOrderCommRate.InstrumentID, "IF2509", sizeof(QryInstrumentOrderCommRate.InstrumentID) - 1);
	Spi.m_pUserApi->ReqQryInstrumentOrderCommRate(&QryInstrumentOrderCommRate, 0);
	_semaphore.wait();

	// 查询投资者期权合约手续费率
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询投资者期权合约手续费率 ...\n");
	CThostFtdcQryOptionInstrCommRateField QryOptionInstrCommRate = { 0 };
	strncpy(QryOptionInstrCommRate.BrokerID, broker.c_str(), sizeof(QryOptionInstrCommRate.BrokerID) - 1);
	strncpy(QryOptionInstrCommRate.InvestorID, user.c_str(), sizeof(QryOptionInstrCommRate.InvestorID) - 1);
	strncpy(QryOptionInstrCommRate.ExchangeID, "SHFE", sizeof(QryOptionInstrCommRate.ExchangeID) - 1);
	strncpy(QryOptionInstrCommRate.InstrumentID, "au2510C848", sizeof(QryOptionInstrCommRate.InstrumentID) - 1);
	Spi.m_pUserApi->ReqQryOptionInstrCommRate(&QryOptionInstrCommRate, 0);
	_semaphore.wait();

	// 查询行情
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询行情 ...\n");
	CThostFtdcQryDepthMarketDataField QryDepthMarketData = { 0 };
	Spi.m_pUserApi->ReqQryDepthMarketData(&QryDepthMarketData, 0);
	_semaphore.wait();

	// 查询订单
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询订单 ...\n");
	CThostFtdcQryOrderField QryOrder = { 0 };
	Spi.m_pUserApi->ReqQryOrder(&QryOrder, 0);
	_semaphore.wait();

	// 查询成交
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询成交 ...\n");
	CThostFtdcQryTradeField QryTrade = { 0 };
	Spi.m_pUserApi->ReqQryTrade(&QryTrade, 0);
	_semaphore.wait();

	// 查询持仓
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询持仓 ...\n");
	CThostFtdcQryInvestorPositionField QryInvestorPosition = { 0 };
	Spi.m_pUserApi->ReqQryInvestorPosition(&QryInvestorPosition, 0);
	_semaphore.wait();

	// 持仓明细
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("持仓明细 ...\n");
	CThostFtdcQryInvestorPositionDetailField QryInvestorPositionDetail = { 0 };
	Spi.m_pUserApi->ReqQryInvestorPositionDetail(&QryInvestorPositionDetail, 0);
	_semaphore.wait();

	// 查询资金
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询资金 ...\n");
	CThostFtdcQryTradingAccountField QryTradingAccount = { 0 };
	Spi.m_pUserApi->ReqQryTradingAccount(&QryTradingAccount, 0);
	_semaphore.wait();

	///请求查询转帐流水
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	CThostFtdcQryTransferSerialField QryTransferSerial = { 0 };
	Spi.m_pUserApi->ReqQryTransferSerial(&QryTransferSerial, 0);
	_semaphore.wait();

	///请求查询银期签约关系
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	CThostFtdcQryAccountregisterField QryAccountregister = { 0 };
	Spi.m_pUserApi->ReqQryAccountregister(&QryAccountregister, 0);
	_semaphore.wait();

	///请求查询签约银行
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	CThostFtdcQryContractBankField QryContractBank = { 0 };
	Spi.m_pUserApi->ReqQryContractBank(&QryContractBank, 0);
	_semaphore.wait();

	///请求查询银行余额，若要查询银行余额，放开下面的代码即可
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//Spi.QueryBankAccountMoney("888888");
	//_semaphore.wait();
	
	// 如需出入金，放开下面的代码即可
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//printf("按任意键入金 ...\n");
	//getchar();
	//Spi.MoneyTransferToCTP(100.0, "888888");

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//printf("按任意键出金 ...\n");
	//getchar();
	//Spi.MoneyTransferToBank(100.0, "888888");

	// 如需下单、撤单，放开下面的代码即可
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//printf("按任意键下单 ...\n");
	//getchar();
	//Spi.OrderInsert("SHFE", "au2406", THOST_FTDC_D_Buy, THOST_FTDC_OF_Open, 550.0, 3);

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//printf("按任意键下单 ...\n");
	//getchar();
	//Spi.OrderInsert("CFFEX", "IF2407", THOST_FTDC_D_Sell, THOST_FTDC_OF_Open, 3500.0, 1);

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//printf("按任意键撤单 ...\n");
	//getchar();
	//Spi.OrderCancel("CFFEX", "IF2407", "xxx");

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("按任意键退出 ...\n");
	getchar();

	return 0;
}
