#pragma once

#include "Sender.h"
#include "Receiver.h"

class SelectiveRepeatProtocol {
private:
	Sender sender; // Sender object
	Receiver receiver; // Receiver object
public:
	SelectiveRepeatProtocol(uint32_t windowSize);

	//simuleaza scenariul specific
	void simulateSpecificScenario();

	//simuleaza functionarea generala
	void simulate(int numFrames);

	// corupere random
	void simulateWithRandomCorruption(int numFrames, double corruptionRate);
};