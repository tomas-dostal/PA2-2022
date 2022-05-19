/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include "Shape.h"
#include "Pos.h"
#include "Interface.h"

class Circle : Shape {
public:
    Circle() = delete;

    Circle(Pos &center, size_t diameter) : diameter(diameter) { this->center = center; };

    void Draw(Interface &interface);

private:
    size_t diameter;
};
