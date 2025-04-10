/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"
#include "Contract.h"
#include "EDecoder.h"
#include "EMutex.h"
#include "EReader.h"
#include "EClientSocket.h"
#include "EPosixClientSocketPlatform.h"
#include "EReaderSignal.h"
#include "EMessage.h"
#include "DefaultEWrapper.h"

#define IN_BUF_SIZE_DEFAULT 8192

static DefaultEWrapper defaultWrapper;

EReader::EReader(EClientSocket *clientSocket, EReaderSignal *signal)
	: processMsgsDecoder_(clientSocket->EClient::serverVersion(), clientSocket->getWrapper(), clientSocket)
#if defined(IB_POSIX)
    , m_hReadThread(pthread_self())
#elif defined(IB_WIN32)
    , m_hReadThread(0)
#endif
{
		m_isAlive = true;
        m_pClientSocket = clientSocket;       
		m_pEReaderSignal = signal;
		m_nMaxBufSize = IN_BUF_SIZE_DEFAULT;
		m_buf.reserve(IN_BUF_SIZE_DEFAULT);
}

EReader::~EReader(void) {
#if defined(IB_POSIX)
    if (!pthread_equal(pthread_self(), m_hReadThread)) {
        m_isAlive = false;
        m_pClientSocket->eDisconnect();
	pthread_join(m_hReadThread, NULL);
    }
#elif defined(IB_WIN32)
    if (m_hReadThread) {
        m_isAlive = false;
        m_pClientSocket->eDisconnect();
        WaitForSingleObject(m_hReadThread, INFINITE);
    }
#endif
}

void EReader::start() {
#if defined(IB_POSIX)
    pthread_create( &m_hReadThread, NULL, readToQueueThread, this );
#elif defined(IB_WIN32)
    m_hReadThread = CreateThread(0, 0, readToQueueThread, this, 0, 0);
#else
#   error "Not implemented on this platform"
#endif
}

#if defined(IB_POSIX)
void * EReader::readToQueueThread(void * lpParam)
#elif defined(IB_WIN32)
DWORD WINAPI EReader::readToQueueThread(LPVOID lpParam)
#else
#   error "Not implemented on this platform"
#endif
{
	EReader *pThis = reinterpret_cast<EReader *>(lpParam);

	pThis->readToQueue();
	return 0;
}

void EReader::readToQueue() {
	//EMessage *msg = 0;

	while (m_isAlive) {
		if (m_buf.size() == 0 && !processNonBlockingSelect() && m_pClientSocket->isSocketOK())
			continue;

        if (!putMessageToQueue())
			break;
	}

	m_pClientSocket->handleSocketError();
	m_pEReaderSignal->issueSignal(); //letting client know that socket was closed
}

bool EReader::putMessageToQueue() {
	EMessage *msg = 0;

	if (m_pClientSocket->isSocketOK())
		msg = readSingleMsg();

	if (msg == 0)
		return false;

	{
		EMutexGuard lock(m_csMsgQueue);
		m_msgQueue.push_back(std::shared_ptr<EMessage>(msg));
	}

	m_pEReaderSignal->issueSignal();

	return true;
}

bool EReader::processNonBlockingSelect() {
	fd_set readSet, writeSet, errorSet;
	struct timeval tval;

	tval.tv_usec = 100 * 1000; //100 ms
	tval.tv_sec = 0;

	if( m_pClientSocket->fd() >= 0 ) {

		FD_ZERO( &readSet);
		FD_ZERO( &writeSet);
		FD_ZERO( &errorSet);

		FD_SET( m_pClientSocket->fd(), &readSet);
		if (!m_pClientSocket->getTransport()->isOutBufferEmpty())
			FD_SET( m_pClientSocket->fd(), &writeSet);
		FD_SET( m_pClientSocket->fd(), &errorSet);

		int ret = select( m_pClientSocket->fd() + 1, &readSet, &writeSet, &errorSet, &tval);

		if( ret == 0) { // timeout
			return false;
		}

		if( ret < 0) {	// error
			m_pClientSocket->eDisconnect();
			return false;
		}

		if( m_pClientSocket->fd() < 0)
			return false;

		if( FD_ISSET( m_pClientSocket->fd(), &errorSet)) {
			// error on socket
			m_pClientSocket->onError();
		}

		if( m_pClientSocket->fd() < 0)
			return false;

		if( FD_ISSET( m_pClientSocket->fd(), &writeSet)) {
			// socket is ready for writing
			onSend();
		}

		if( m_pClientSocket->fd() < 0)
			return false;

		if( FD_ISSET( m_pClientSocket->fd(), &readSet)) {
			// socket is ready for reading
			onReceive();
		}

		return true;
	}

	return false;
}

void EReader::onSend() {
	m_pEReaderSignal->issueSignal();
}

void EReader::onReceive() {
	int nOffset = m_buf.size();

	m_buf.resize(m_nMaxBufSize);
	
	int nRes = m_pClientSocket->receive(m_buf.data() + nOffset, m_buf.size() - nOffset);

	if (nRes <= 0)
		return;

 	m_buf.resize(nRes + nOffset);	
}

bool EReader::bufferedRead(char *buf, unsigned int size) {
	while (size > 0) {
		while (m_buf.size() < size && m_buf.size() < m_nMaxBufSize) {
			if (!processNonBlockingSelect() && !m_pClientSocket->isSocketOK())
				return false;
		}

		int nBytes = (std::min<unsigned int>)(m_nMaxBufSize, size);

		std::copy(m_buf.begin(), m_buf.begin() + nBytes, buf);
		std::copy(m_buf.begin() + nBytes, m_buf.end(), m_buf.begin());
		m_buf.resize(m_buf.size() - nBytes);

		size -= nBytes;
		buf += nBytes;
	}

	return true;
}

EMessage * EReader::readSingleMsg() {
	if (m_pClientSocket->usingV100Plus()) {
		int msgSize;

		if (!bufferedRead((char *)&msgSize, sizeof(msgSize)))
			return 0;

		msgSize = ntohl(msgSize);

		if (msgSize <= 0 || msgSize > MAX_MSG_LEN)
			return 0;

		std::vector<char> buf = std::vector<char>(msgSize);

		if (!bufferedRead(buf.data(), buf.size()))
			return 0;

		return new EMessage(buf);
	}
	else {
		const char *pBegin = 0;
		const char *pEnd = 0;
		int msgSize = 0;

		while (msgSize == 0)
		{
			if (m_buf.size() >= m_nMaxBufSize * 3/4) 
				m_nMaxBufSize *= 2;

			if (!processNonBlockingSelect() && !m_pClientSocket->isSocketOK())
				return 0;
		
			pBegin = m_buf.data();
			pEnd = pBegin + m_buf.size();
			msgSize = EDecoder(m_pClientSocket->EClient::serverVersion(), &defaultWrapper).parseAndProcessMsg(pBegin, pEnd);
		}
	
		std::vector<char> msgData(msgSize);

		if (!bufferedRead(msgData.data(), msgSize))
			return 0;

		if (m_buf.size() < IN_BUF_SIZE_DEFAULT && m_buf.capacity() > IN_BUF_SIZE_DEFAULT)
		{
			m_buf.resize(m_nMaxBufSize = IN_BUF_SIZE_DEFAULT);
			m_buf.shrink_to_fit();
		}

		EMessage * msg = new EMessage(msgData);

		return msg;
	}
}

std::shared_ptr<EMessage> EReader::getMsg(void) {
	EMutexGuard lock(m_csMsgQueue);

	if (m_msgQueue.size() == 0) {
		return std::shared_ptr<EMessage>();
	}

	std::shared_ptr<EMessage> msg = m_msgQueue.front();
	m_msgQueue.pop_front();

	return msg;
}


void EReader::processMsgs(void) {
	m_pClientSocket->onSend();

	std::shared_ptr<EMessage> msg = getMsg();

	if (!msg.get())
		return;

	const char *pBegin = msg->begin();

	while (processMsgsDecoder_.parseAndProcessMsg(pBegin, msg->end()) > 0) {
		msg = getMsg();

		if (!msg.get())
			break;

		pBegin = msg->begin();
	} 
}
