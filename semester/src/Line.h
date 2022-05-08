/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include "Shape.h"

class Line: Shape {
public:
    Line(Pos & a, Pos & b): a(a), b(b){
        this->center = Pos(abs(a.x - b.x)/2, abs(a.y - b.y)/2);
    };
    is_paralel(Line & other);
    is_perpendicular(Line & other);

private:
    Pos a, b;

};
