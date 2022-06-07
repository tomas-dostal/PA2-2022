/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include "Pos.h"
#include "Color.h"
#include "Interface.h"
#include "any"

class Shape {
public:

    Shape( unsigned int id, std::string name, Pos center, size_t height, size_t width, std::shared_ptr<Color> color, std::shared_ptr<Color> fill):
    id(id), name(std::move(name)), center(center), height(height), width(width), color(color), fill(fill)
    {

    };

  Shape() = default;

    virtual ~Shape() noexcept = default; // choose destructors to match class to be sure all the memory is freed

    virtual void Draw(Interface &interface) = 0; // layers are solved by order of drawings, from rear (first drawn) to front (last drawn)

    virtual bool operator==(const Shape &s) = 0;

    virtual std::string ShapeId() = 0;

    virtual std::string ShapeName() = 0;

    virtual std::shared_ptr<Color> ShapeColor() = 0;

    virtual std::shared_ptr<Color> ShapeFill() = 0;

    //virtual std::vector<std::pair<std::string, std::any>> ShapeNamedCoords();

protected:
    unsigned int id{};
    std::string name;

    Pos center;

    size_t height{};
    size_t width{};

    std::shared_ptr<Color> color;
    std::shared_ptr<Color> fill;

};

//std::vector<std::pair<std::string, std::any>> Shape::ShapeNamedCoords() {
//    return std::vector<std::pair<std::string, std::any>>({
//          {"center", this->center,
//           "height", this->height,
//           "width", this->width}
//    });
//}
