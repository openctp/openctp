/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"
#include "TimeCondition.h"

std::string TimeCondition::valueToString() const {
	return m_time;
}

void TimeCondition::valueFromString(const std::string & v) {
	m_time = v;
}

std::string TimeCondition::toString() {
	return "time" + OperatorCondition::toString();
}

std::string TimeCondition::time() {
	return m_time;
}

void TimeCondition::time(const std::string & time) {
	m_time = time;
}
