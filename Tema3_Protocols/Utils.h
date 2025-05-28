#pragma once

#include "Frame.h"
#include <string>

namespace Utils {
	bool simulateChannelError(double errorRate);
	Frame simulateCorruption(const Frame& frame, double errorRate);
	void printDivider(char symbol = '-', int length = 50);
	std::string getCurrentTimestamp();
	void logMessage(const std::string& message, bool includeTimeStamp = true);
}