/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_IEXTERNALIZABLE_H
#define TWS_API_CLIENT_IEXTERNALIZABLE_H

#include <ios>

struct IExternalizable
{
	virtual const char* readExternal(const char* ptr, const char* endPtr) = 0;
	virtual void writeExternal(std::ostream &out) const = 0;
};

#endif