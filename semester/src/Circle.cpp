/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include "Circle.h"

Circle::Circle(Pos &center, size_t diameter, std::shared_ptr<Color> color, std::shared_ptr<Color> fill): Shape(), diameter(diameter) {
    this->center = center;
    this->color = color;
    this->fill = fill;
    this->height = 2*diameter;
    this->width = 2*diameter;
    this->name = "Amazing circle";
    this->id = 2;
}

void Circle::Draw(Interface &interface) {
    interface.PrintInfo("I'm a circle");
}

bool Circle::operator==(const Shape &s) {
    const Circle * ptr = dynamic_cast<const Circle *>( &s );
    return  ptr != nullptr
            && this->diameter == ptr->diameter
            && this->fill == ptr->fill
            && this->color == ptr->color
            && this->center == ptr->center;
    // that's enough
}
