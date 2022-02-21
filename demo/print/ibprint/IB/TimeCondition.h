/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_TIMECONDITION_H
#define TWS_API_CLIENT_TIMECONDITION_H

#include "OperatorCondition.h"

class TWSAPIDLLEXP TimeCondition : public OperatorCondition {
	friend OrderCondition;

	std::string m_time;

protected:
	TimeCondition() { }

	virtual std::string valueToString() const;
	virtual void valueFromString(const std::string &v);

public:
	static const OrderConditionType conditionType = OrderConditionType::Time;

	virtual std::string toString();

	std::string time();
	void time(const std::string &time);
};

#endif