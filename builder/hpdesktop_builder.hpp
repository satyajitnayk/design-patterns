#ifndef HPDESKTOP_BUILDER_HPP
#define HPDESKTOP_BUILDER_HPP

#include "desktop_builder.hpp"

class HpDesktopBuilder : public DesktopBuilder {
  void buildMonitor();
  void buildKeyboard();
  void buildMouse();
  void buildSpeaker();
  void buildRam();
  void buildProcessor();
  void buildMotherBoard();
};

#endif