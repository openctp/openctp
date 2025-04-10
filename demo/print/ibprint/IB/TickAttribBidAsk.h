/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_TICKATTRIBBIDASK_H
#define TWS_API_CLIENT_TICKATTRIBBIDASK_H

struct TickAttribBidAsk
{
	bool bidPastLow;
	bool askPastHigh;
};

#endif
