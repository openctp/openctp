/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_ETRANSPORT_H
#define TWS_API_CLIENT_ETRANSPORT_H

class EMessage;

struct ETransport
{
    virtual int send(EMessage *pMsg) = 0;
    //virtual int sendBufferedData() = 0;
    //virtual bool isOutBufferEmpty() const = 0;
    virtual ~ETransport() {}
};

#endif