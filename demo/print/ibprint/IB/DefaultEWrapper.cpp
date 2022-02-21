/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"
#include "DefaultEWrapper.h"

void DefaultEWrapper::tickPrice( TickerId tickerId, TickType field, double price, const TickAttrib& attribs) { }
void DefaultEWrapper::tickSize( TickerId tickerId, TickType field, int size) { }
void DefaultEWrapper::tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
	   double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) { }
void DefaultEWrapper::tickGeneric(TickerId tickerId, TickType tickType, double value) { }
void DefaultEWrapper::tickString(TickerId tickerId, TickType tickType, const std::string& value) { }
void DefaultEWrapper::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints,
	   double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate) { }
void DefaultEWrapper::orderStatus( OrderId orderId, const std::string& status, double filled,
	   double remaining, double avgFillPrice, int permId, int parentId,
	   double lastFillPrice, int clientId, const std::string& whyHeld, double mktCapPrice) { }
void DefaultEWrapper::openOrder( OrderId orderId, const Contract&, const Order&, const OrderState&) { }
void DefaultEWrapper::openOrderEnd() { }
void DefaultEWrapper::winError( const std::string& str, int lastError) { }
void DefaultEWrapper::connectionClosed() { }
void DefaultEWrapper::updateAccountValue(const std::string& key, const std::string& val,
   const std::string& currency, const std::string& accountName) { }
void DefaultEWrapper::updatePortfolio( const Contract& contract, double position,
      double marketPrice, double marketValue, double averageCost,
      double unrealizedPNL, double realizedPNL, const std::string& accountName) { }
void DefaultEWrapper::updateAccountTime(const std::string& timeStamp) { }
void DefaultEWrapper::accountDownloadEnd(const std::string& accountName) { }
void DefaultEWrapper::nextValidId( OrderId orderId) { }
void DefaultEWrapper::contractDetails( int reqId, const ContractDetails& contractDetails) { }
void DefaultEWrapper::bondContractDetails( int reqId, const ContractDetails& contractDetails) { }
void DefaultEWrapper::contractDetailsEnd( int reqId) { }
void DefaultEWrapper::execDetails( int reqId, const Contract& contract, const Execution& execution) { }
void DefaultEWrapper::execDetailsEnd( int reqId) { }
void DefaultEWrapper::error(int id, int errorCode, const std::string& errorString) { }
void DefaultEWrapper::updateMktDepth(TickerId id, int position, int operation, int side,
      double price, int size) { }
void DefaultEWrapper::updateMktDepthL2(TickerId id, int position, const std::string& marketMaker, int operation,
      int side, double price, int size, bool isSmartDepth) { }
void DefaultEWrapper::updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch) { }
void DefaultEWrapper::managedAccounts( const std::string& accountsList) { }
void DefaultEWrapper::receiveFA(faDataType pFaDataType, const std::string& cxml) { }
void DefaultEWrapper::historicalData(TickerId reqId, const Bar& bar) { }
void DefaultEWrapper::historicalDataEnd(int reqId, const std::string& startDateStr, const std::string& endDateStr) { }
void DefaultEWrapper::scannerParameters(const std::string& xml) { }
void DefaultEWrapper::scannerData(int reqId, int rank, const ContractDetails& contractDetails,
	   const std::string& distance, const std::string& benchmark, const std::string& projection,
	   const std::string& legsStr) { }
void DefaultEWrapper::scannerDataEnd(int reqId) { }
void DefaultEWrapper::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
	   long volume, double wap, int count) { }
void DefaultEWrapper::currentTime(long time) { }
void DefaultEWrapper::fundamentalData(TickerId reqId, const std::string& data) { }
void DefaultEWrapper::deltaNeutralValidation(int reqId, const DeltaNeutralContract& deltaNeutralContract) { }
void DefaultEWrapper::tickSnapshotEnd( int reqId) { }
void DefaultEWrapper::marketDataType( TickerId reqId, int marketDataType) { }
void DefaultEWrapper::commissionReport( const CommissionReport& commissionReport) { }
void DefaultEWrapper::position( const std::string& account, const Contract& contract, double position, double avgCost) { }
void DefaultEWrapper::positionEnd() { }
void DefaultEWrapper::accountSummary( int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& curency) { }
void DefaultEWrapper::accountSummaryEnd( int reqId) { }
void DefaultEWrapper::verifyMessageAPI( const std::string& apiData) { }
void DefaultEWrapper::verifyCompleted( bool isSuccessful, const std::string& errorText) { }
void DefaultEWrapper::displayGroupList( int reqId, const std::string& groups) { }
void DefaultEWrapper::displayGroupUpdated( int reqId, const std::string& contractInfo) { }
void DefaultEWrapper::verifyAndAuthMessageAPI( const std::string& apiData, const std::string& xyzChallange) { }
void DefaultEWrapper::verifyAndAuthCompleted( bool isSuccessful, const std::string& errorText) { }
void DefaultEWrapper::connectAck() { }
void DefaultEWrapper::positionMulti( int reqId, const std::string& account,const std::string& modelCode, const Contract& contract, double pos, double avgCost) { }
void DefaultEWrapper::positionMultiEnd( int reqId) { }
void DefaultEWrapper::accountUpdateMulti( int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency) { }
void DefaultEWrapper::accountUpdateMultiEnd( int reqId) { }
void DefaultEWrapper::securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass,
	const std::string& multiplier, const std::set<std::string>& expirations, const std::set<double>& strikes) { }
void DefaultEWrapper::securityDefinitionOptionalParameterEnd(int reqId) { }
void DefaultEWrapper::softDollarTiers(int reqId, const std::vector<SoftDollarTier> &tiers) { }
void DefaultEWrapper::familyCodes(const std::vector<FamilyCode> &familyCodes) { }
void DefaultEWrapper::symbolSamples(int reqId, const std::vector<ContractDescription> &contractDescriptions) { }
void DefaultEWrapper::mktDepthExchanges(const std::vector<DepthMktDataDescription> &depthMktDataDescriptions) { }
void DefaultEWrapper::tickNews(int tickerId, time_t timeStamp, const std::string& providerCode, const std::string& articleId, const std::string& headline, const std::string& extraData) { }
void DefaultEWrapper::smartComponents(int reqId, const SmartComponentsMap& theMap) { }
void DefaultEWrapper::tickReqParams(int tickerId, double minTick, const std::string& bboExchange, int snapshotPermissions) { }
void DefaultEWrapper::newsProviders(const std::vector<NewsProvider> &newsProviders) { }
void DefaultEWrapper::newsArticle(int requestId, int articleType, const std::string& articleText) { }
void DefaultEWrapper::historicalNews(int requestId, const std::string& time, const std::string& providerCode, const std::string& articleId, const std::string& headline) { }
void DefaultEWrapper::historicalNewsEnd(int requestId, bool hasMore) { }
void DefaultEWrapper::headTimestamp(int reqId, const std::string& headTimestamp) { }
void DefaultEWrapper::histogramData(int reqId, const HistogramDataVector& data) { }
void DefaultEWrapper::historicalDataUpdate(TickerId reqId, const Bar& bar) { }
void DefaultEWrapper::rerouteMktDataReq(int reqId, int conid, const std::string& exchange) { }
void DefaultEWrapper::rerouteMktDepthReq(int reqId, int conid, const std::string& exchange) { }
void DefaultEWrapper::marketRule(int marketRuleId, const std::vector<PriceIncrement> &priceIncrements) { }
void DefaultEWrapper::pnl(int reqId, double dailyPnL, double unrealizedPnL, double realizedPnL) { }
void DefaultEWrapper::pnlSingle(int reqId, int pos, double dailyPnL, double unrealizedPnL, double realizedPnL, double value) { }
void DefaultEWrapper::historicalTicks(int reqId, const std::vector<HistoricalTick>& ticks, bool done) { }
void DefaultEWrapper::historicalTicksBidAsk(int reqId, const std::vector<HistoricalTickBidAsk>& ticks, bool done) { }
void DefaultEWrapper::historicalTicksLast(int reqId, const std::vector<HistoricalTickLast>& ticks, bool done) { }
void DefaultEWrapper::tickByTickAllLast(int reqId, int tickType, time_t time, double price, int size, const TickAttribLast& tickAttribLast, const std::string& exchange, const std::string& specialConditions) { }
void DefaultEWrapper::tickByTickBidAsk(int reqId, time_t time, double bidPrice, double askPrice, int bidSize, int askSize, const TickAttribBidAsk& tickAttribBidAsk) { }
void DefaultEWrapper::tickByTickMidPoint(int reqId, time_t time, double midPoint) { }
void DefaultEWrapper::orderBound(long long orderId, int apiClientId, int apiOrderId) { }
void DefaultEWrapper::completedOrder(const Contract& contract, const Order& order, const OrderState& orderState) { }
void DefaultEWrapper::completedOrdersEnd() { }
