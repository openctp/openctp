/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_ORDERSTATE_H
#define TWS_API_CLIENT_ORDERSTATE_H

#include "Order.h"

struct OrderState {

	explicit OrderState()
		:
		commission(UNSET_DOUBLE),
		minCommission(UNSET_DOUBLE),
		maxCommission(UNSET_DOUBLE)
	{}

	std::string status;

	std::string initMarginBefore;
	std::string maintMarginBefore;
	std::string equityWithLoanBefore;
	std::string initMarginChange;
	std::string maintMarginChange;
	std::string equityWithLoanChange;
	std::string initMarginAfter;
	std::string maintMarginAfter;
	std::string equityWithLoanAfter;

	double  commission;
	double  minCommission;
	double  maxCommission;
	std::string commissionCurrency;

	std::string warningText;

	std::string completedTime;
	std::string completedStatus;
};

#endif
