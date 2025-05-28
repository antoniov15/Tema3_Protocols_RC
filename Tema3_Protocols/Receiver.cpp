#include "Receiver.h"
#include <iostream>
#include <algorithm>

Receiver::Receiver(uint32_t windowSize) : windowSize(windowSize) {
	expectedSeqNum = 0;
	receivedFrames.clear();
	buffer.clear();
}

/// Main methods
void Receiver::receiveFrame(const Frame& frame) {
	std::cout << "Received frame with sequence number: " << frame.sequenceNumber << "\n";

	if (frame.isCorrrupted) {
		std::cout << "Frame " << frame.sequenceNumber << " is corrupted. Discarding.\n";
		return;
	}

	if (!isInWindow(frame.sequenceNumber)) {
		std::cout << "Frame " << frame.sequenceNumber << " is out of window. Discarding.\n";
		return;
	}

	if (frame.sequenceNumber == expectedSeqNum) {
		std::cout << "Frame " << frame.sequenceNumber << " is the expexted frame.\n";

		receivedFrames.push_back(frame); // adauga frame-ul in lista de frame-uri primite
		expectedSeqNum++; // incrementeaza numarul de secventa asteptat

		while (buffer.find(expectedSeqNum) != buffer.end()) {
			std::cout << "Found buffered frame " << expectedSeqNum << ". Processing.\n";

			receivedFrames.push_back(buffer[expectedSeqNum]); // adauga frame-ul din buffer in lista de frame-uri primite
			buffer.erase(expectedSeqNum); // sterge frame-ul din buffer
			expectedSeqNum++; // incrementeaza numarul de secventa asteptat
		}
	}
	else {
		std::cout << "Frame " << frame.sequenceNumber << " is out of order. Buffering.\n";
		buffer[frame.sequenceNumber] = frame; // adauga frame-ul in buffer
	}

	std::cout << "Expected sequence number: " << expectedSeqNum << "\n";
}

std::vector<Frame> Receiver::getSortedFrames() {
	std::vector<Frame> sortedFrames = receivedFrames; // adauga frame-urile primite in vectorul de frame-uri sortate

	std::sort(sortedFrames.begin(), sortedFrames.end(), 
				[](const Frame& a, const Frame& b) {
					return a.sequenceNumber < b.sequenceNumber; // sorteaza frame-urile in functie de numarul de secventa
				});

	return sortedFrames; // returneaza vectorul de frame-uri sortate
}

/// Helper methods
bool Receiver::isInWindow(uint32_t seqNum) {
	return (seqNum >= expectedSeqNum && seqNum < expectedSeqNum + windowSize); // verifica daca numarul de secventa este in fereastra
}

bool Receiver::printBufferStatus() {
	std::cout << "Buffer Status:\n";
	std::cout << "Expected Sequence Number: " << expectedSeqNum << '\n';
	std::cout << "Window Size: " << windowSize << '\n';

	std::cout << "Received Frames:\n";
	if (receivedFrames.empty()) {
		std::cout << "No frames received yet.\n";
	}
	else {
		for (const auto& frame : receivedFrames) {
			std::cout << "Frame " << frame.sequenceNumber;
			if (frame.isCorrrupted) {
				std::cout << " (corrupted)";
			}
			std::cout << '\n';
		}
	}

	std::cout << "Buffered Frames:\n";
	if (buffer.empty()) {
		std::cout << "No frames in buffer.\n";
	}
	else {
		for (const auto& pair : buffer) {
			std::cout << "  Frame " << pair.first;
			if (pair.second.isCorrrupted) {
				std::cout << " (corrupted)";
			}
			std::cout << '\n';
		}
	}
	return true;
}