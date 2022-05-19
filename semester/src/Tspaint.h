/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 13.05.2022
  */

#pragma once

#include "ColorPalett.h"

class Tspaint {
public:
    void Init();

    bool IsRunning();

private:
    std::unique_ptr<ColorPalett> colorPalette;
    bool isRunning;
};
