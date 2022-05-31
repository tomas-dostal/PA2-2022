/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 13.05.2022
  */

#pragma once

#include "ColorPalette.h"

class Tspaint {
public:
    Tspaint();
    ColorPalette colorPalette;
    std::shared_ptr<Color> color;
    std::shared_ptr<Color> fill;
    size_t thickness;

};
