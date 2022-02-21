/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_OPERATORCONDITION_H
#define TWS_API_CLIENT_OPERATORCONDITION_H

#include "OrderCondition.h"

class TWSAPIDLLEXP OperatorCondition : public OrderCondition {
	bool m_isMore;

protected:
	virtual std::string valueToString() const = 0;
	virtual void valueFromString(const std::string &v) = 0;

public:
	virtual const char* readExternal(const char* ptr, const char* endPtr);
	virtual std::string toString();
	virtual void writeExternal(std::ostream &out) const;

	bool isMore();
	void isMore(bool isMore);
};

#endif