/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_SCANNERSUBSCRIPTION_H
#define TWS_API_CLIENT_SCANNERSUBSCRIPTION_H

#include <float.h>
#include <limits.h>
#include <string>


#define UNSET_DOUBLE DBL_MAX
#define UNSET_INTEGER INT_MAX
#define NO_ROW_NUMBER_SPECIFIED -1;

struct ScannerSubscription {
	ScannerSubscription() {
		numberOfRows = NO_ROW_NUMBER_SPECIFIED;
		abovePrice = DBL_MAX;
		belowPrice = DBL_MAX;
		aboveVolume = INT_MAX;
		marketCapAbove = DBL_MAX;
		marketCapBelow = DBL_MAX;
		couponRateAbove = DBL_MAX;
		couponRateBelow = DBL_MAX;
		excludeConvertible = INT_MAX;
		averageOptionVolumeAbove = INT_MAX;
	}
    int numberOfRows;
    std::string instrument;
    std::string locationCode;
    std::string scanCode;
    double abovePrice;
    double belowPrice;
    int aboveVolume;
    double marketCapAbove;
    double marketCapBelow;
    std::string moodyRatingAbove;
    std::string moodyRatingBelow;
    std::string spRatingAbove;
    std::string spRatingBelow;
    std::string maturityDateAbove;
    std::string maturityDateBelow;
    double couponRateAbove;
    double couponRateBelow;
    int excludeConvertible;
	int averageOptionVolumeAbove;
	std::string scannerSettingPairs;
	std::string stockTypeFilter;
};

#endif
