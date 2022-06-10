/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include "Circle.h"

Circle::Circle(unsigned int id, std::string name, std::shared_ptr<Pos> center, size_t diameter, size_t thickness,  std::shared_ptr<Color> color, std::shared_ptr<Color> fill)
        : Shape(id, name, center, 2 * diameter, 2 * diameter, thickness, color, fill), diameter(diameter) {
    {

    }
}

void Circle::Draw(std::shared_ptr<Interface> interface, std::string format) {
    interface->PrintInfo("I'm a circle");
}

bool Circle::operator==(const SuperShape &s) {
    const Circle *ptr = dynamic_cast<const Circle *>( &s );
    return ptr != nullptr
           && this->diameter == ptr->diameter
           && this->fill == ptr->fill
           && this->color == ptr->color
           && this->center == ptr->center;
    // that's enough
}

std::string Circle::Print() const{
    return name;
}
