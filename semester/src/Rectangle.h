/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include "Shape.h"
#include "SuperShape.h"
#include "Export.h"

class Rectangle : public Shape {
public:

    /**
     * Simple line between two points
     * @param id
     * @param name
     * @param Pos start
     * @param size_t width
     * @param size_t height
     * @param thickness
     * @param color
     * @param fill
     */
    Rectangle(int id, std::string name, Pos &start, size_t width, size_t height, size_t thickness, std::shared_ptr<Color> color, std::shared_ptr<Color> fill);

    void Draw(Export & exporter) override;

    [[nodiscard]] std::string Print() const override;

    std::pair<size_t, size_t> CalcMaxDimensions() override;

    bool operator==(const SuperShape &s) override;
private:

    Pos start;
};
