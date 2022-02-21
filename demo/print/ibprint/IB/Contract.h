/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_CONTRACT_H
#define TWS_API_CLIENT_CONTRACT_H

#include "TagValue.h"

/*
	SAME_POS    = open/close leg value is same as combo
	OPEN_POS    = open
	CLOSE_POS   = close
	UNKNOWN_POS = unknown
*/
enum LegOpenClose { SAME_POS, OPEN_POS, CLOSE_POS, UNKNOWN_POS };

struct ComboLeg
{
	ComboLeg()
		: conId(0)
		, ratio(0)
		, openClose(0)
		, shortSaleSlot(0)
		, exemptCode(-1)
	{
	}

	long		conId;
	long		ratio;
	std::string	action; //BUY/SELL/SSHORT

	std::string	exchange;
	long		openClose; // LegOpenClose enum values

	// for stock legs when doing short sale
	long		shortSaleSlot; // 1 = clearing broker, 2 = third party
	std::string	designatedLocation;
	int			exemptCode;

	bool operator==( const ComboLeg& other) const
	{
		return (conId == other.conId &&
			ratio == other.ratio &&
			openClose == other.openClose &&
			shortSaleSlot == other.shortSaleSlot &&
			exemptCode == other.exemptCode &&
			action == other.action &&
			exchange == other.exchange &&
			designatedLocation == other.designatedLocation);
	}
};

struct DeltaNeutralContract
{
	DeltaNeutralContract()
		: conId(0)
		, delta(0)
		, price(0)
	{}

	long	conId;
	double	delta;
	double	price;
};

typedef std::shared_ptr<ComboLeg> ComboLegSPtr;

struct Contract
{
	Contract()
		: conId(0)
		, strike(0)
		, includeExpired(false)
		, comboLegs(NULL)
		, deltaNeutralContract(NULL)
	{
	}

	long		conId;
	std::string	symbol;
	std::string	secType;
	std::string	lastTradeDateOrContractMonth;
	double		strike;
	std::string	right;
	std::string	multiplier;
	std::string	exchange;
	std::string	primaryExchange; // pick an actual (ie non-aggregate) exchange that the contract trades on.  DO NOT SET TO SMART.
	std::string	currency;
	std::string	localSymbol;
	std::string	tradingClass;
	bool		includeExpired;
	std::string	secIdType;		// CUSIP;SEDOL;ISIN;RIC
	std::string	secId;

	// COMBOS
	std::string comboLegsDescrip; // received in open order 14 and up for all combos

	// combo legs
	typedef std::vector<ComboLegSPtr> ComboLegList;
	typedef std::shared_ptr<ComboLegList> ComboLegListSPtr;

	ComboLegListSPtr comboLegs;

	// delta neutral contract
	DeltaNeutralContract* deltaNeutralContract;

public:

	// Helpers
	static void CloneComboLegs(ComboLegListSPtr& dst, const ComboLegListSPtr& src);
};

struct ContractDetails
{
	ContractDetails()
		: minTick(0)
		, priceMagnifier(0)
		, underConId(0)
		, evMultiplier(0)
		, callable(false)
		, putable(false)
		, coupon(0)
		, convertible(false)
		, nextOptionPartial(false)
	{
	}

	Contract	contract;
	std::string	marketName;
	double		minTick;
	std::string	orderTypes;
	std::string	validExchanges;
	long		priceMagnifier;
	int			underConId;
	std::string	longName;
	std::string	contractMonth;
	std::string	industry;
	std::string	category;
	std::string	subcategory;
	std::string	timeZoneId;
	std::string	tradingHours;
	std::string	liquidHours;
	std::string	evRule;
	double		evMultiplier;
	int			mdSizeMultiplier;
	int			aggGroup;
	std::string	underSymbol;
	std::string	underSecType;
	std::string marketRuleIds;
	std::string realExpirationDate;
	std::string lastTradeTime;

	TagValueListSPtr secIdList;

	// BOND values
	std::string	cusip;
	std::string	ratings;
	std::string	descAppend;
	std::string	bondType;
	std::string	couponType;
	bool		callable;
	bool		putable;
	double		coupon;
	bool		convertible;
	std::string	maturity;
	std::string	issueDate;
	std::string	nextOptionDate;
	std::string	nextOptionType;
	bool		nextOptionPartial;
	std::string	notes;
};

struct ContractDescription
{
	Contract contract;
	typedef std::vector<std::string> DerivativeSecTypesList;
	DerivativeSecTypesList derivativeSecTypes;
};

inline void
Contract::CloneComboLegs(ComboLegListSPtr& dst, const ComboLegListSPtr& src)
{
	if (!src.get())
		return;

	dst->reserve(src->size());

	ComboLegList::const_iterator iter = src->begin();
	const ComboLegList::const_iterator iterEnd = src->end();

	for (; iter != iterEnd; ++iter) {
		const ComboLeg* leg = iter->get();
		if (!leg)
			continue;
		dst->push_back(ComboLegSPtr(new ComboLeg(*leg)));
	}
}


#endif
