// concrete builder
#include "hpdesktop_builder.hpp"

void HpDesktopBuilder::buildMonitor() { desktop->setMonitor("Hp Monitor"); }
void HpDesktopBuilder::buildKeyboard() { desktop->setKeyboard("Hp Keyboard"); }
void HpDesktopBuilder::buildMotherBoard() {
  desktop->setMotherBoard("Hp Motherboard");
}
void HpDesktopBuilder::buildMouse() { desktop->setMouse("Hp Mouse"); }
void HpDesktopBuilder::buildProcessor() {
  desktop->setProcessor("Hp Processor");
}
void HpDesktopBuilder::buildRam() { desktop->setRam("Hp Ram"); }
void HpDesktopBuilder::buildSpeaker() { desktop->setSpeaker("Hp Speaker"); }