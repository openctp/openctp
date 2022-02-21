/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_PLATFORMSPECIFIC_H
#define TWS_API_CLIENT_PLATFORMSPECIFIC_H

#ifdef _MSC_VER

#ifdef TWSAPIDLL
#ifndef TWSAPIDLLEXP
#define TWSAPIDLLEXP __declspec(dllexport)
#endif
#endif

#define assert ASSERT
#if _MSC_VER<=1800
#define snprintf _snprintf
#endif
#include <WinSock2.h>
#include <Windows.h>
#include <time.h>
#define IB_WIN32
#define atoll _atoi64
#else

#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/fcntl.h>
#include <mutex>
#include <unistd.h> // defines _POSIX_THREADS, @see http://bit.ly/1pWJ8KQ#tag_13_80_03_02

#if defined(_POSIX_THREADS) && (_POSIX_THREADS > 0)
#include <pthread.h>
#define IB_POSIX
#if __cplusplus >= 201103L // strict C++11 standard std::mutex is available
#define IBAPI_STD_MUTEX
#endif 
#else
#error "Not supported on this platform"
#endif

#endif // #ifdef _MSC_VER

#ifndef TWSAPIDLLEXP
#define TWSAPIDLLEXP
#endif

#endif