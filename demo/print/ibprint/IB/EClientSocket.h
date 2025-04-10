/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_ECLIENTSOCKET_H
#define TWS_API_CLIENT_ECLIENTSOCKET_H

#include <atomic>
#include "EClient.h"
#include "EClientMsgSink.h"
#include "ESocket.h"

class EWrapper;
struct EReaderSignal;

class TWSAPIDLLEXP EClientSocket : public EClient, public EClientMsgSink
{
protected:
    virtual void prepareBufferImpl(std::ostream&) const;
	virtual void prepareBuffer(std::ostream&) const;
	virtual bool closeAndSend(std::string msg, unsigned offset = 0);

public:

	explicit EClientSocket(EWrapper *ptr, EReaderSignal *pSignal = 0);
	virtual ~EClientSocket();

	bool eConnect( const char *host, int port, int clientId = 0, bool extraAuth = false);
	// override virtual funcs from EClient
	void eDisconnect(bool resetState = true);

	bool isSocketOK() const;
	int fd() const;
    bool asyncEConnect() const;
    void asyncEConnect(bool val);
    ESocket *getTransport();

    void allowRedirect(bool v);
    bool allowRedirect() const; 

private:

	bool eConnectImpl(int clientId, bool extraAuth, ConnState* stateOutPt);

private:
	void encodeMsgLen(std::string& msg, unsigned offset) const;
public:
	bool handleSocketError();
	int receive( char* buf, size_t sz);

public:
	// callback from socket
	void onSend();
	void onError();

private:

	void onClose();

private:

	std::atomic<int> m_fd;
    bool m_allowRedirect;    
    bool m_asyncEConnect;
    EReaderSignal *m_pSignal;
    int m_redirectCount;

    static const int REDIRECT_COUNT_MAX = 2;

//EClientMsgSink implementation
public:
    void serverVersion(int version, const char *time);
    void redirect(const char *host, int port);    
};

#endif
