#include "Sender.h"
#include <iostream>
#include <algorithm>

Sender::Sender(uint32_t windowSize) : windowSize(windowSize) {
	base = 0;
	nextSeqNum = 0;
	window.clear();
}

/// Main methods
bool Sender::canSendFrame() {
	return(nextSeqNum < base + windowSize); // returneaza true daca mai pot trimite frame-uri
}

Frame Sender::sendFrame() {
	if (canSendFrame()) {
		std::cerr << "Error: Cannot send frame, window is full.\n";

		Frame invalidFrame;
		invalidFrame.sequenceNumber = UINT32_MAX;
		invalidFrame.isCorrrupted = true;
		return invalidFrame; // returneaza un frame invalids
	}

	Frame frame = createFrame(nextSeqNum); // creeaza un frame cu numarul de secventa curent

	window.push_back(frame); // adauga frame-ul in fereastra

	nextSeqNum++; // incrementeaza numarul de secventa pentru urmatorul frame

	std::cout << "Sent frame with sequence number: " << frame.sequenceNumber << "\n";

	return frame; // returneaza frame-ul trimis
}

void Sender::receiveAck(uint32_t ackNum) {
	std::cout << "Received ACK for frame: " << ackNum << '\n';

	auto it = std::find_if(window.begin(), window.end(), 
							[ackNum](const Frame& frame) {
			return frame.sequenceNumber == ackNum;
		});

	if (it != window.end()) {
		window.erase(it); // sterge frame-ul din fereastra
	
		if (ackNum == base) {
			if (!window.empty()) {
				//base = window.front().sequenceNumber; 
				base = window[0].sequenceNumber; // actualizeaza baza ferestrei
				for (const auto& f : window) {
					if (f.sequenceNumber < base) {
						base = f.sequenceNumber; // actualizeaza baza ferestrei
					}
				}
			}
			else {
				base = nextSeqNum; // daca fereastra este goala, actualizeaza baza
			}
		}

		std::cout << "Updated base to: " << base << '\n';
	}
	else {
		std::cout << "Frame " << ackNum << " not found in window or already acknowledged.\n";
	}
}

void Sender::checkForTimeouts() {
	std::cout << "Checking for timeouts in window...\n";

	for (auto& frame : window) {
		std::cout << "Frame " << frame.sequenceNumber << " is still in window.\n";
	}
}

/// Helper methods
bool Sender::isInWindow(uint32_t seqNum) {
	return (seqNum >= base && seqNum < base + windowSize); // verifica daca numarul de secventa este in fereastra
}

bool Sender::printWndowStatus() {
	std::cout << "Window Status:" << std::endl;
	std::cout << "Base: " << base << std::endl;
	std::cout << "Next Sequence Number: " << nextSeqNum << std::endl;
	std::cout << "Window Size: " << windowSize << std::endl;

	std::cout << "Frames in Window:\n";
	if (window.empty()) {
		std::cout << "  Window is empty.\n";
	}
	else {
		for (const auto& frame : window) {
			std::cout << "  Frame " << frame.sequenceNumber;
			if (frame.isCorrrupted) {
				std::cout << " (corrupted)";
			}
			std::cout << std::endl;
		}
	}

	return true;
}