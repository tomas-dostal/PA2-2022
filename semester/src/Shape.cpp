/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include "Shape.h"
#include "SuperShape.h"

Shape::Shape(unsigned int id, std::string name, std::shared_ptr<Pos> center, size_t height, size_t width, size_t thickness,
      std::shared_ptr<Color> color, std::shared_ptr<Color> fill):
      SuperShape(id, name, center, width, height), thickness(thickness), color(color), fill(fill){

}

std::shared_ptr<Color> Shape::ShapeColor() {
    return color;
}

std::shared_ptr<Color> Shape::ShapeFill() {
    return fill;
}

size_t Shape::Thickness() const{
    return thickness;
}