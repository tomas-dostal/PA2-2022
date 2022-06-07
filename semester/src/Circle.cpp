/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include "Circle.h"

Circle::Circle(unsigned int id, std::string name, Pos &center, size_t diameter, std::shared_ptr<Color> color, std::shared_ptr<Color> fill)
        : Shape(id, name, center, 2 * diameter, 2 * diameter, color, fill), diameter(diameter) {
    {

    }
}

void Circle::Draw(Interface &interface) {
    interface.PrintInfo("I'm a circle");
}

bool Circle::operator==(const Shape &s) {
    const Circle *ptr = dynamic_cast<const Circle *>( &s );
    return ptr != nullptr
           && this->diameter == ptr->diameter
           && this->fill == ptr->fill
           && this->color == ptr->color
           && this->center == ptr->center;
    // that's enough
}
