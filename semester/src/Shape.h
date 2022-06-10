/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include "any"

#include "Pos.h"
#include "Color.h"
#include "Interface.h"
#include "SuperShape.h"

class Shape : public SuperShape {
public:

    /**
     * Shape - basic structure for generic shapes like circle, line etc.
     * @param id
     * @param name
     * @param center
     * @param height
     * @param width
     * @param thickness
     * @param color
     * @param fill
     */
    Shape(unsigned int id, std::string name, std::shared_ptr<Pos> center, size_t height, size_t width, size_t thickness,
          std::shared_ptr<Color> color, std::shared_ptr<Color> fill);

    Shape() = delete;

    virtual ~Shape() noexcept = default; // choose destructors to match class to be sure all the memory is freed

    /**
     * Draw shape into the interface / just print it
     * @param interface
     */
    // virtual void Draw(Interface &interface) = 0; // layers are solved by order of drawings, from rear (first drawn) to front (last drawn)

//    virtual std::string Print();
//
//    virtual bool operator==(const Shape &s) = 0;
//
//    virtual std::string Id();
//
//    virtual std::string Name();

    std::shared_ptr<Color> ShapeColor();

    std::shared_ptr<Color> ShapeFill();


    size_t Thickness() const;

    //virtual std::vector<std::pair<std::string, std::any>> ShapeNamedCoords();
protected:
    size_t height{};
    size_t width{};

    size_t thickness{};
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


