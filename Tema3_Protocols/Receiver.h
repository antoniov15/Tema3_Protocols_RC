#pragma once

#include "Frame.h"
#include <vector>
#include <map>

class Receiver {
private:
	std::vector<Frame> receivedFrames;	// frames primite
	std::map<uint32_t, Frame> buffer;	// buffer pentru frame-urile in asteptare
	uint32_t expectedSeqNum;			// numarul de secventa asteptat
	uint32_t windowSize;				// dimensiunea ferestrei

public:
	Receiver(uint32_t windowSize);
	/// Main methods
	void receiveFrame(const Frame& frame);
	std::vector<Frame> getSortedFrames();
	/// Helper methods
	bool isInWindow(uint32_t seqNum);
	bool printBufferStatus();
};