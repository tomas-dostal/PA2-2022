/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 13.05.2022
  */

#include "Tspaint.h"

Tspaint::Tspaint() {

    isRunning = true;

    colorPalette = std::make_unique<ColorPalette>(ColorPalette());

    colorPalette->addIfNotExists("GRAY__PROGTEST", std::make_shared<Color>(Color(170, 170, 170)));
    colorPalette->addIfNotExists("GRAY__OUT_OF_SIGHT", std::make_shared<Color>(Color(255, 87, 51)));
    colorPalette->addIfNotExists("BLACK__INSIDE_OF_MY_SOUL", std::make_shared<Color>(Color(0, 0, 0)));
    colorPalette->addIfNotExists("MAGENTA__BRAIN_OVERFLOW", std::make_shared<Color>(Color(255, 0, 255)));
    colorPalette->addIfNotExists("GREEN__PROGTEST_HOME", std::make_shared<Color>(Color(0, 255, 0)));
    colorPalette->addIfNotExists("RED__COMPILED_WITH_ERRORS", std::make_shared<Color>(Color(192, 64, 0)));
    colorPalette->addIfNotExists("BLUE__FUN_FOR_A_WEEKEND", std::make_shared<Color>(Color(0, 153, 203)));
    colorPalette->addIfNotExists("GREEN__ALMOST_THERE", std::make_shared<Color>(Color(128, 192, 0)));
    colorPalette->addIfNotExists("GREEN__IM_DONE", std::make_shared<Color>(Color(0, 192, 0)));
    colorPalette->addIfNotExists("WHITE__LOADING", std::make_shared<Color>(Color(255, 255, 255)));
    colorPalette->addIfNotExists("YELLOW__FIT", std::make_shared<Color>(Color(240, 171, 0)));

}

bool Tspaint::IsRunning() {
    return this->isRunning;

}
