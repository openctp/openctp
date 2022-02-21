/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_EREADER_H
#define TWS_API_CLIENT_EREADER_H

#include <atomic>
#include <deque>
#include "platformspecific.h"
#include "EDecoder.h"
#include "EMutex.h"
#include "EReaderOSSignal.h"

class EClientSocket;
struct EReaderSignal;
class EMessage;

class TWSAPIDLLEXP EReader
{  
    EClientSocket *m_pClientSocket;
    EReaderSignal *m_pEReaderSignal;
    EDecoder processMsgsDecoder_;
    std::deque<std::shared_ptr<EMessage>> m_msgQueue;
    EMutex m_csMsgQueue;
    std::vector<char> m_buf;
    std::atomic<bool> m_isAlive;
#if defined(IB_POSIX)
    pthread_t m_hReadThread;
#elif defined(IB_WIN32)
    HANDLE m_hReadThread;
#endif
	unsigned int m_nMaxBufSize;

	void onReceive();
	void onSend();
	bool bufferedRead(char *buf, unsigned int size);

public:
    EReader(EClientSocket *clientSocket, EReaderSignal *signal);
    ~EReader(void);

protected:
	bool processNonBlockingSelect();
    std::shared_ptr<EMessage> getMsg(void);
    void readToQueue();
#if defined(IB_POSIX)
    static void * readToQueueThread(void * lpParam);
#elif defined(IB_WIN32)
    static DWORD WINAPI readToQueueThread(LPVOID lpParam);
#else
#   error "Not implemented on this platform"
#endif
    
    EMessage * readSingleMsg();

public:
    void processMsgs(void);
	bool putMessageToQueue();
	void start();
};

#endif