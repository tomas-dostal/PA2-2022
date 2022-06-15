/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include <any>
#include <memory>
#include <string>

#include "SuperShape.h"
#include "Pos.h"
#include "Color.h"
#include "Interface.h"

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
    Shape(int id, std::string name, std::shared_ptr<Pos> center, size_t height, size_t width, size_t thickness,
          std::shared_ptr<Color> color, std::shared_ptr<Color> fill);

    Shape() = delete;

    virtual ~Shape() noexcept = default; // choose destructors to match class to be sure all the memory is freed

    std::shared_ptr<Color> ShapeColor();

    std::shared_ptr<Color> ShapeFill();

    [[nodiscard]] size_t Thickness() const;

    std::string Print(int indent) const override;

protected:

    size_t thickness;
    std::shared_ptr<Color> color;

    std::shared_ptr<Color> fill;

};
