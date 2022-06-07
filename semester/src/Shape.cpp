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