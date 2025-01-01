// concrete builder
#include "delldesktop_builder.hpp"

void DellDesktopBuilder::buildMonitor() { desktop->setMonitor("Dell Monitor"); }
void DellDesktopBuilder::buildKeyboard() {
  desktop->setKeyboard("Dell Keyboard");
}
void DellDesktopBuilder::buildMotherBoard() {
  desktop->setMotherBoard("Dell Motherboard");
}
void DellDesktopBuilder::buildMouse() { desktop->setMouse("Dell Mouse"); }
void DellDesktopBuilder::buildProcessor() {
  desktop->setProcessor("Dell Processor");
}
void DellDesktopBuilder::buildRam() { desktop->setRam("Dell Ram"); }
void DellDesktopBuilder::buildSpeaker() { desktop->setSpeaker("Dell Speaker"); }