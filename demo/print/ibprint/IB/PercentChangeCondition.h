/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_PERCENTCHANGECONDITION_H
#define TWS_API_CLIENT_PERCENTCHANGECONDITION_H

#include "ContractCondition.h"
#include "Order.h"

class TWSAPIDLLEXP PercentChangeCondition : public ContractCondition {
	friend OrderCondition;

	double m_changePercent;

protected:
	PercentChangeCondition()
	: m_changePercent(UNSET_DOUBLE)
	{ }

	virtual std::string valueToString() const;
	virtual void valueFromString(const std::string &v);

public:
	static const OrderConditionType conditionType = OrderConditionType::PercentChange;

	double changePercent();
	void changePercent(double changePercent);
};

#endif