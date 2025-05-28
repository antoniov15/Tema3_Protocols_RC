#pragma once

#include <cstdint>

struct Frame {
	uint32_t sequenceNumber; // Sequence number of the frame
	bool isCorrupted; // Flag indicating if the frame is corrupted
};

Frame createFrame(uint32_t sequenceNumber);
bool isFrameValid(const Frame& frame);