#include "Frame.h"

// Constructor for the Frame struct
Frame createFrame(uint32_t sequenceNumber) {
	Frame frame;
	frame.sequenceNumber = sequenceNumber;
	frame.isCorrrupted = false;
	//frame.isCorrrupted = (rand() % 2 == 0); // Randomly set the corruption flag
	
	return frame;
}

bool isFrameValid(const Frame& frame) {
	return !frame.isCorrrupted; // Check if the frame is not corrupted
}