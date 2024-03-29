/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 13.05.2022
  */

#pragma once

#include "SuperShape.h"
#include "ColorPalette.h"
#include "ShapeGroup.h"

class Tspaint {
public:
    Tspaint();

    void AddShape(std::shared_ptr<SuperShape> superShape);

    std::shared_ptr<ShapeGroup> NewGroup();

    std::shared_ptr<ShapeGroup> AddGroup(std::vector<std::shared_ptr<SuperShape>> superShapes);

    bool UseGroup(int id);

    void RemoveSuperShapeFromRootGroup(int shapeId);

    int GenerateId();

    std::string Print() const;

    explicit Tspaint(const std::shared_ptr<Tspaint>& src);

    bool IsValidIndex(int) const;

    std::pair<size_t, size_t> MaxDimensions() const;

    std::shared_ptr<SuperShape> GetSuperShape(int index);

    ColorPalette colorPalette;
    std::shared_ptr<Color> color;
    std::shared_ptr<Color> fill;
    std::shared_ptr<Color> background;
    size_t thickness;

    std::shared_ptr<ShapeGroup> root;
    std::shared_ptr<ShapeGroup> currentGroup;
    std::map<int, std::shared_ptr<SuperShape>> superShapesById;

    std::shared_ptr<ShapeGroup> AddExistingGroup(std::shared_ptr<ShapeGroup> group);

private:
    int idGenerator = 1;


    bool IsValidGroupIndex(int index) const;

};
