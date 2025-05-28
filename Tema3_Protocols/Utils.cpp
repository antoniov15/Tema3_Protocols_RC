#include "Utils.h"
#include "Frame.h"
#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>

// Simulate channel errors (packet loss or corruption) with given probability
bool Utils::simulateChannelError(double errorRate) {
    // Seed the random number generator if it hasn't been seeded yet
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    // Generate a random number between 0 and 1
    double random = static_cast<double>(std::rand()) / RAND_MAX;

    // Return true if random number is less than error rate (indicating an error)
    return (random < errorRate);
}

// Simulate frame corruption with given probability
Frame Utils::simulateCorruption(const Frame& frame, double corruptionRate) {
    Frame result = frame;

    if (simulateChannelError(corruptionRate)) {
        result.isCorrrupted = true;
        logMessage("Frame " + std::to_string(frame.sequenceNumber) + " corrupted during transmission");
    }

    return result;
}

// Print a divider line for better console output formatting
void Utils::printDivider(char symbol, int length) {
    std::cout << std::string(length, symbol) << std::endl;
}

// Get current timestamp for logging
std::string Utils::getCurrentTimestamp() {
    std::time_t now = std::time(nullptr);

    // Use localtime_s instead of localtime for safety
    std::tm tm_buf;
#ifdef _WIN32
    localtime_s(&tm_buf, &now);
#else
    // For non-Windows platforms
    tm_buf = *std::localtime(&now);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm_buf, "[%H:%M:%S] ");
    return oss.str();
}

// Log a message with timestamp
void Utils::logMessage(const std::string& message, bool includeTimestamp) {
    if (includeTimestamp) {
        std::cout << getCurrentTimestamp();
    }

    std::cout << message << std::endl;
}