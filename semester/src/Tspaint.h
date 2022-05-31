/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 13.05.2022
  */

#pragma once

#include "ColorPalette.h"
#include "Shape.h"
#include "ShapeBuilder.h"

class Tspaint {
public:
    void AddShape(std::shared_ptr<Shape> shape);
    Tspaint();
    //virtual void Build(ShapeBuilder & shapeBuilder) = 0;

    ColorPalette colorPalette;
    std::shared_ptr<Color> color;
    std::shared_ptr<Color> fill;
    size_t thickness;

private:
    std::vector<std::shared_ptr<Shape>> shapes;

};
