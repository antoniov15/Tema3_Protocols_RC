#include "SelectiveRepeatProtocol.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>

/**
 * Constructor for the SelectiveRepeatProtocol class.
 * Initializes the sender and receiver with the specified window size.
 *
 * @param windowSize The size of the sliding window
 */
SelectiveRepeatProtocol::SelectiveRepeatProtocol(uint32_t windowSize)
    : sender(windowSize), receiver(windowSize) {
    Utils::logMessage("Selective Repeat Protocol initialized with window size: " +
        std::to_string(windowSize));
}

/**
 * Simulates a specific scenario as described in the requirements.
 *
 * Example scenario:
 * - Frame 1 is sent and acknowledged
 * - Frame 2 is sent and acknowledged
 * - Frame 3 is sent but corrupted
 * - Frame 4 is sent and acknowledged
 * - Frame 5 is sent and acknowledged
 * - Frame 3 is retransmitted and acknowledged
 * - Frame 6 is sent and acknowledged
 * - Resulting in a vector: 1, 2, 4, 5, 3, 6 which needs to be sorted
 */
void SelectiveRepeatProtocol::simulateSpecificScenario() {
    Utils::printDivider('=', 70);
    Utils::logMessage("Starting Selective Repeat Protocol Specific Scenario Simulation");
    Utils::printDivider('=', 70);

    // Frame 1: Send and receive properly
    Utils::printDivider();
    Utils::logMessage("Step 1: Sending Frame 1");
    Frame frame1 = sender.sendFrame();
    receiver.receiveFrame(frame1);
    sender.receiveAck(frame1.sequenceNumber);

    // Frame 2: Send and receive properly
    Utils::printDivider();
    Utils::logMessage("Step 2: Sending Frame 2");
    Frame frame2 = sender.sendFrame();
    receiver.receiveFrame(frame2);
    sender.receiveAck(frame2.sequenceNumber);

    // Frame 3: Send but corrupt
    Utils::printDivider();
    Utils::logMessage("Step 3: Sending Frame 3 (will be corrupted)");
    Frame frame3 = sender.sendFrame();
    // Corrupt the frame
    frame3.isCorrupted = true;
    Utils::logMessage("Frame 3 corrupted!");
    receiver.receiveFrame(frame3);

    // Frame 4: Send and receive properly
    Utils::printDivider();
    Utils::logMessage("Step 4: Sending Frame 4");
    Frame frame4 = sender.sendFrame();
    receiver.receiveFrame(frame4);
    sender.receiveAck(frame4.sequenceNumber);

    // Frame 5: Send and receive properly
    Utils::printDivider();
    Utils::logMessage("Step 5: Sending Frame 5");
    Frame frame5 = sender.sendFrame();
    receiver.receiveFrame(frame5);
    sender.receiveAck(frame5.sequenceNumber);

    // Frame 3: Retransmit and receive properly
    Utils::printDivider();
    Utils::logMessage("Step 6: Retransmitting Frame 3");
    // Create a new, uncorrupted frame 3
    Frame frame3Retransmit = createFrame(3);
    receiver.receiveFrame(frame3Retransmit);
    sender.receiveAck(frame3Retransmit.sequenceNumber);

    // Frame 6: Send and receive properly
    Utils::printDivider();
    Utils::logMessage("Step 7: Sending Frame 6");
    Frame frame6 = sender.sendFrame();
    receiver.receiveFrame(frame6);
    sender.receiveAck(frame6.sequenceNumber);

    // Print the unsorted frames
    Utils::printDivider();
    Utils::logMessage("Unsorted received frames:");
    std::vector<Frame> receivedFrames = receiver.getSortedFrames();
    for (const auto& frame : receivedFrames) {
        std::cout << frame.sequenceNumber << " ";
    }
    std::cout << std::endl;

    // Sort the frames (just to demonstrate, getSortedFrames already returns sorted frames)
    Utils::logMessage("Sorted received frames:");
    std::sort(receivedFrames.begin(), receivedFrames.end(),
        [](const Frame& a, const Frame& b) {
            return a.sequenceNumber < b.sequenceNumber;
        });

    for (const auto& frame : receivedFrames) {
        std::cout << frame.sequenceNumber << " ";
    }
    std::cout << std::endl;

    Utils::printDivider('=', 70);
    Utils::logMessage("Selective Repeat Protocol Specific Scenario Simulation Complete");
    Utils::printDivider('=', 70);
}

/**
 * Simulates the Selective Repeat Protocol for a general case.
 *
 * @param numFrames The number of frames to simulate
 */
void SelectiveRepeatProtocol::simulate(int numFrames) {
    Utils::printDivider('=', 70);
    Utils::logMessage("Starting Selective Repeat Protocol General Simulation");
    Utils::logMessage("Number of frames: " + std::to_string(numFrames));
    Utils::printDivider('=', 70);

    // Define error rates
    const double corruptionRate = 0.2; // 20% chance of corruption

    // Send frames
    for (int i = 0; i < numFrames; i++) {
        if (sender.canSendFrame()) {
            Utils::printDivider();
            Utils::logMessage("Sending frame " + std::to_string(i));

            // Send the frame
            Frame frame = sender.sendFrame();

            // Simulate potential corruption
            frame = Utils::simulateCorruption(frame, corruptionRate);

            // Receiver processes the frame
            receiver.receiveFrame(frame);

            // If the frame was not corrupted, sender receives ACK
            if (!frame.isCorrupted) {
                sender.receiveAck(frame.sequenceNumber);
            }
        }
        else {
            Utils::logMessage("Cannot send frame, window is full. Checking for timeouts...");
            sender.checkForTimeouts();

            // In a real implementation, this would wait for ACKs or timeouts
            // For the simulation, we'll just retry sending after a "timeout"

            // Retransmit a frame (simplified, just retransmit the first frame in the window)
            if (!sender.printWndowStatus()) {
                Utils::logMessage("Failed to print window status.");
            }
        }
    }

    // Print the status
    Utils::printDivider();
    Utils::logMessage("Final window status:");
    sender.printWndowStatus();

    Utils::printDivider();
    Utils::logMessage("Final buffer status:");
    receiver.printBufferStatus();

    // Get and print the sorted frames
    Utils::printDivider();
    Utils::logMessage("Sorted received frames:");
    std::vector<Frame> sortedFrames = receiver.getSortedFrames();

    for (const auto& frame : sortedFrames) {
        std::cout << frame.sequenceNumber << " ";
    }
    std::cout << std::endl;

    Utils::printDivider('=', 70);
    Utils::logMessage("Selective Repeat Protocol General Simulation Complete");
    Utils::printDivider('=', 70);
}