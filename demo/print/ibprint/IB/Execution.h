/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_EXECUTION_H
#define TWS_API_CLIENT_EXECUTION_H

#include <string>

struct Execution
{
	Execution()
	{
		shares = 0;
		price = 0;
		permId = 0;
		clientId = 0;
		orderId = 0;
		cumQty = 0;
		avgPrice = 0;
		evMultiplier = 0;
        lastLiquidity = 0;
	}

	std::string	execId;
	std::string	time;
	std::string	acctNumber;
	std::string	exchange;
	std::string	side;
	double		shares;
	double		price;
	int			permId;
	long		clientId;
	long		orderId;
	int			liquidation;
	double			cumQty;
	double		avgPrice;
	std::string	orderRef;
	std::string	evRule;
	double		evMultiplier;
	std::string modelCode;
    int         lastLiquidity;
};

struct ExecutionFilter
{
	ExecutionFilter()
		: m_clientId(0)
	{
	}

	// Filter fields
	long		m_clientId;
	std::string	m_acctCode;
	std::string	m_time;
	std::string	m_symbol;
	std::string	m_secType;
	std::string	m_exchange;
	std::string	m_side;
};

#endif // execution_def
