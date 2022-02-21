/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_ESOCKET_H
#define TWS_API_CLIENT_ESOCKET_H

#include "ETransport.h"
#include <vector>

class ESocket :
    public ETransport
{
    int m_fd;
	std::vector<char> m_outBuffer;

    int bufferedSend(const char* buf, size_t sz);
    int send(const char* buf, size_t sz);
    void CleanupBuffer(std::vector<char>& buffer, int processed);

public:
    ESocket();
    virtual ~ESocket(void);

    int send(EMessage *pMsg);
    bool isOutBufferEmpty() const;
    int sendBufferedData();
    void fd(int fd);
};

#endif