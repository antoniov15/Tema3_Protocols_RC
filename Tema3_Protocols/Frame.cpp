#include "Frame.h"

// Constructor for the Frame struct
Frame createFrame(uint32_t sequenceNumber) {
	Frame frame;
	frame.sequenceNumber = sequenceNumber;
	frame.isCorrupted = false;
	//frame.isCorrupted = (rand() % 2 == 0); // Randomly set the corruption flag
	
	return frame;
}

bool isFrameValid(const Frame& frame) {
	return !frame.isCorrupted; // Check if the frame is not corrupted
}