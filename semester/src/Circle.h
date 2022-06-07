/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include "Shape.h"
#include "Pos.h"
#include "Interface.h"

class Circle : public Shape {
public:
    Circle() = delete;

    Circle(unsigned int id, std::string name, Pos &center, size_t diameter, size_t thickenss,  std::shared_ptr<Color> color,
           std::shared_ptr<Color> fill);

    void Draw(Interface &interface);

    bool operator==(const Shape &s);

    std::string ShapeId() { return std::to_string(this->id); }

    std::string ShapeName() { return this->name; }

    std::shared_ptr<Color> ShapeColor() { return this->color; };

    std::shared_ptr<Color> ShapeFill() { return this->fill; };

private:
    size_t diameter;
};
