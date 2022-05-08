/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include "Pos.h"
#include "Color.h"
#include "Interface.h"

class Shape {
public:
    virtual void Draw(Interface & interface) = 0; // layers are solved by order of drawings, from rear (first drawn) to front (last drawn)
    virtual bool operator == (const Shape & s) = 0;

protected:
    Pos center;

    Color color;
    Color fill;
    size_t height;
    size_t width;
    std::string name;

    unsigned int id;
};
