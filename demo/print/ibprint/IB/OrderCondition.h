/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_ORDERCONDITION_H
#define TWS_API_CLIENT_ORDERCONDITION_H

#include "IExternalizable.h"
#include <string>
#include "platformspecific.h"


class TWSAPIDLLEXP OrderCondition : public IExternalizable {
public:
	enum OrderConditionType {
		Price = 1,
		Time = 3,
		Margin = 4,
		Execution = 5,
		Volume = 6,
		PercentChange = 7
	};

private:
	OrderConditionType m_type;
	bool m_isConjunctionConnection;

public:
	virtual ~OrderCondition() {}
	virtual const char* readExternal(const char* ptr, const char* endPtr);
	virtual void writeExternal(std::ostream &out) const;

	std::string toString();
	bool conjunctionConnection() const;
	void conjunctionConnection(bool isConjunctionConnection);	
	OrderConditionType type();
	
	static OrderCondition *create(OrderConditionType type);
};

#endif