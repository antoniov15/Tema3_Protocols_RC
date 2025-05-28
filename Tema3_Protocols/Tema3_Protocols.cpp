#include "SelectiveRepeatProtocol.h"
#include <iostream>

int main()
{
	SelectiveRepeatProtocol protocol(4); // window size of 4

	protocol.simulateSpecificScenario();

	return 0;
}
// This code simulates a selective repeat protocol for reliable data transfer.