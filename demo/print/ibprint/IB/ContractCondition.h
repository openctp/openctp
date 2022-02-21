/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_CONTRACTCONDITION_H
#define TWS_API_CLIENT_CONTRACTCONDITION_H

#include "OperatorCondition.h"

class TWSAPIDLLEXP ContractCondition : public OperatorCondition {
	int m_conId;
	std::string m_exchange;

public:
	virtual std::string toString();
	virtual const char* readExternal(const char* ptr, const char* endPtr);
	virtual void writeExternal(std::ostream &out) const;

	int conId();
	void conId(int conId);
	std::string exchange();
	void exchange(const std::string &exchange);
};
#endif
