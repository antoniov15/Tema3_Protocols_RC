#pragma once

#include "Frame.h"
#include <vector>

class Sender {
private:
	std::vector<Frame> window; // fereastra
	uint32_t base; // inceputul ferestrei
	uint32_t nextSeqNum; // urmatorul numar de secventa de trimis
	uint32_t windowSize; // dimensiunea ferestrei

public:
	Sender(uint32_t windowSize);
	
	/// Main methods
	bool canSendFrame();
	Frame sendFrame();
	void receiveAck(uint32_t ackNum);
	void checkForTimeouts();

	/// Helper methods
	bool isInWindow(uint32_t seqNum);
	bool printWndowStatus();
};