/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 13.05.2022
  */

#pragma once

#include "ColorPalette.h"
#include "Shape.h"

class Tspaint {
public:
    void AddShape(std::shared_ptr<Shape> shape);

    Tspaint();

    //virtual void Build(ShapeBuilder & shapeBuilder) = 0;
    std::vector<std::shared_ptr<Shape>> GetShapes();

    ColorPalette colorPalette;
    std::shared_ptr<Color> color;
    std::shared_ptr<Color> fill;
    size_t thickness;

    std::vector<std::shared_ptr<Shape>> shapes;

};
