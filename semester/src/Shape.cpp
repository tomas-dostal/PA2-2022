/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include "Shape.h"

Shape::Shape(unsigned int id, std::string name, Pos center, size_t height, size_t width, size_t thickness, std::shared_ptr<Color> color,
             std::shared_ptr<Color> fill):
        id(id), name(std::move(name)), center(center), height(height), width(width), thickness(thickness), color(color), fill(fill)
{

}

std::string Shape::Print() {
    return this->ShapeId() + " "  + this->ShapeName();
}

std::string Shape::ShapeId() {
    return std::to_string(this->id);
}

std::string Shape::ShapeName() {
    return this->name;
}

std::shared_ptr<Color> Shape::ShapeColor() {
    return this->color;
}

std::shared_ptr<Color> Shape::ShapeFill() {
    return this->fill;
}
