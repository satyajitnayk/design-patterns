#ifndef DESKTOP_DIRECTOR_HPP
#define DESKTOP_DIRECTOR_HPP

#include "desktop_builder.hpp"

class DesktopDirector {
private:
  DesktopBuilder *desktopBuilder;

public:
  DesktopDirector(DesktopBuilder *pDesktopBuilder) {
    desktopBuilder = pDesktopBuilder;
  }

  Desktop *getDesktop() { return desktopBuilder->getDesktop(); }

  Desktop *BuildDesktop() {
    desktopBuilder->buildMonitor();
    desktopBuilder->buildKeyboard();
    desktopBuilder->buildMotherBoard();
    desktopBuilder->buildMouse();
    desktopBuilder->buildProcessor();
    desktopBuilder->buildRam();
    desktopBuilder->buildSpeaker();
    return desktopBuilder->getDesktop();
  }
};

#endif