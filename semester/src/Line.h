/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include "Shape.h"
#include "SuperShape.h"
#include "Export.h"
#include "PolyLine.h"

class Line : public Shape {
public:

    /**
     * Simple line between two points
     * @param id
     * @param name
     * @param Pos a
     * @param Pos b
     * @param thickness
     * @param color
     * @param fill
     */
    Line(int id, std::string name, Pos &a, Pos &b, size_t thickness, std::shared_ptr<Color> color, std::shared_ptr<Color> fill);

    void Draw(Export & exporter) override;

    void MoveRelative(int x, int y) override;

    bool operator==(const SuperShape &s) override;

    std::pair<size_t, size_t> CalcMaxDimensions() override;

    bool isParalel(Line &other);

    bool isPerpendicular(Line &other);

    std::shared_ptr<SuperShape> Clone(const std::function<int(void)>& IdGenerator) override;

    std::shared_ptr<PolyLine> ToPolyline();
private:

    Pos a, b;

    std::shared_ptr<SuperShape> Clone();
};
