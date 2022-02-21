/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"
#include "PercentChangeCondition.h"

#include <sstream>


std::string PercentChangeCondition::valueToString() const {
	std::stringstream tmp;

	tmp << m_changePercent;

	return tmp.str();
}

void PercentChangeCondition::valueFromString(const std::string & v) {
	std::stringstream tmp;
	
	tmp << v;
	tmp >> m_changePercent;
}

double PercentChangeCondition::changePercent() {
	return m_changePercent;
}

void PercentChangeCondition::changePercent(double changePercent) {
	m_changePercent = changePercent;
}
