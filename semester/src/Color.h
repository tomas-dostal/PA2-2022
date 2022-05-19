/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include <string>

class Color {
public:
    Color() {
        r = 255;
        g = 255;
        b = 255;
    }

    Color(unsigned char r, unsigned char g, unsigned char b);

private:
    int r, g, b;
    std::string name;
};
