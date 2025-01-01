#include "desktop.hpp"
#include <iostream>

void Desktop::setMonitor(string pMonitor) { monitor = pMonitor; }
void Desktop::setKeyboard(string pKeyboard) { keyboard = pKeyboard; }
void Desktop::setMotherBoard(string pMotherboard) {
  motherBoard = pMotherboard;
}
void Desktop::setMouse(string pMouse) { mouse = pMouse; }
void Desktop::setProcessor(string pProcessor) { processor = pProcessor; }
void Desktop::setRam(string pRam) { ram = pRam; }
void Desktop::setSpeaker(string pSpeaker) { speaker = pSpeaker; }

void Desktop::showSpecs() {
  cout << "----------------------------\n";
  cout << "Monitor " << monitor << "\n";
  cout << "Keyboard " << keyboard << "\n";
  cout << "Motherboard " << motherBoard << "\n";
  cout << "Mouse " << mouse << "\n";
  cout << "Processor " << processor << "\n";
  cout << "Ram " << ram << "\n";
  cout << "Speaker " << speaker << "\n";
  cout << "-----------------------------\n";
}