/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 13.05.2022
  */

#pragma once

#include "ColorPalette.h"
#include "Shape.h"
#include "ShapeGroup.h"


class Tspaint {
public:
    void AddShape(const std::shared_ptr<SuperShape> superShape) const;

    void AddGroup();

    unsigned long GenerateId();

    unsigned long GenerateGroupId();

    Tspaint();

    explicit Tspaint(const std::shared_ptr<Tspaint>& src);

    ColorPalette colorPalette;
    std::shared_ptr<Color> color;
    std::shared_ptr<Color> fill;
    size_t thickness;

    std::shared_ptr<ShapeGroup> root;

    std::shared_ptr<ShapeGroup> currentGroup;

    unsigned long idGenerator = 0;
    unsigned long groupIdGenerator = 0;

    void AddShape(SuperShape superShape) const;
};
