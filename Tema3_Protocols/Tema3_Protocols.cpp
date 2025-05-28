#include "SelectiveRepeatProtocol.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
	//SelectiveRepeatProtocol protocol(4); // window size of 4

	//protocol.simulateSpecificScenario();

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "Selective Repeat Protocol Simulation\n";
    std::cout << "====================================\n\n";

    std::cout << "Choose simulation type:\n";
    std::cout << "1. Fixed scenario (Frame 3 corrupted)\n";
    std::cout << "2. Random corruption\n";
    //std::cout << "3. Realistic simulation with retries\n";
    std::cout << "Choice: ";

    int choice;
    std::cin >> choice;

    SelectiveRepeatProtocol protocol(4); // window size of 4

    switch (choice) {
    case 1:
        protocol.simulateSpecificScenario();
        break;

    case 2: {
        int numFrames;
        double corruptionRate;

        std::cout << "\nEnter number of frames to send: ";
        std::cin >> numFrames;

        std::cout << "Enter corruption probability (0.0 to 1.0): ";
        std::cin >> corruptionRate;

        protocol.simulateWithRandomCorruption(numFrames, corruptionRate);
        break;
    }
    default:
        std::cout << "Invalid choice!\n";
        return 1;
    }

    return 0;

	return 0;
}
// This code simulates a selective repeat protocol for reliable data transfer.