/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include "Shape.h"

class Line : public Shape {
public:

    /**
     * Simple line between two points
     * @param id
     * @param name
     * @param Pos a
     * @param Pos b
     * @param thickness
     * @param color
     * @param fill
     */
    Line(unsigned long id, std::string name, Pos &a, Pos &b, size_t thickness, std::shared_ptr<Color> color, std::shared_ptr<Color> fill);

    void Draw(Interface &interface);

    bool operator==(const Shape &s);

    std::string ShapeId() { return std::to_string(this->id); }

    std::string ShapeName() { return this->name; }

    std::shared_ptr<Color> ShapeColor() { return this->color; };

    std::shared_ptr<Color> ShapeFill() { return this->fill; };

    bool isParalel(Line &other);

    bool isPerpendicular(Line &other);

private:
    Pos a, b;
};
