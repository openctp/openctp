/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"
#include "EMutex.h"

EMutex::EMutex() {
#if defined(IB_POSIX)
# if !defined(IBAPI_STD_MUTEX)
    pthread_mutex_init(&cs, NULL);
# endif
#elif defined(IB_WIN32)
    InitializeCriticalSection(&cs);
#else
#   error "Not implemented on this platform"
#endif
}

EMutex::~EMutex(void) {
#if defined(IB_POSIX)
# if !defined(IBAPI_STD_MUTEX)
    pthread_mutex_destroy(&cs);
# endif
#elif defined(IB_WIN32)
    DeleteCriticalSection(&cs);
#else
#   error "Not implemented on this platform"
#endif
}

bool EMutex::TryEnter() {
#if defined(IB_POSIX)
# if !defined(IBAPI_STD_MUTEX)
    return pthread_mutex_trylock(&cs) == 0;
# else
    return cs.try_lock();
# endif
#elif defined(IB_WIN32)
    return TryEnterCriticalSection(&cs);
#else
#   error "Not implemented on this platform"
#endif
}

void EMutex::Enter() {
#if defined(IB_POSIX)
# if !defined(IBAPI_STD_MUTEX)
    pthread_mutex_lock(&cs);
# else
    cs.lock();  
# endif
#elif defined(IB_WIN32)
    EnterCriticalSection(&cs);
#else
#   error "Not implemented on this platform"
#endif
}

void EMutex::Leave() {
#if defined(IB_POSIX)
# if !defined(IBAPI_STD_MUTEX)
    pthread_mutex_unlock(&cs);
# else
    cs.unlock();  
# endif
#elif defined(IB_WIN32)
    LeaveCriticalSection(&cs);
#else
#   error "Not implemented on this platform"
#endif
}


EMutexGuard::EMutexGuard(EMutex& m) : m_mutex(m) {
    m_mutex.Enter();
}

EMutexGuard::~EMutexGuard() {
    m_mutex.Leave();
}

