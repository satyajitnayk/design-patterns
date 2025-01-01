#ifndef DELLDESKTOP_BUILDER_HPP
#define DELLDESKTOP_BUILDER_HPP

#include "desktop_builder.hpp"

class DellDesktopBuilder : public DesktopBuilder {
  void buildMonitor();
  void buildKeyboard();
  void buildMouse();
  void buildSpeaker();
  void buildRam();
  void buildProcessor();
  void buildMotherBoard();
};

#endif