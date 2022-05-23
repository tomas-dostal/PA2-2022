/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 13.05.2022
  */

#pragma once

#include "ColorPalette.h"

class Tspaint {
public:
    Tspaint();

    bool IsRunning();

private:
    std::unique_ptr<ColorPalette> colorPalette;
    bool isRunning;
};
