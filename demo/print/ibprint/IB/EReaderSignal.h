/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_EREADERSIGNAL_H
#define TWS_API_CLIENT_EREADERSIGNAL_H

struct EReaderSignal
{
    virtual void issueSignal() = 0;
    virtual void waitForSignal() = 0;
    virtual ~EReaderSignal() {}
};

#endif