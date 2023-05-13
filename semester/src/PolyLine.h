/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include "Shape.h"
#include "SuperShape.h"
#include "Export.h"

class PolyLine : public Shape {
public:

    /**
     * Simple Polyline between mulitple points
     * @param id
     * @param name
     * @param std::vector<Pos> coordinates
     * @param thickness
     * @param color
     * @param fill
     */
    PolyLine(int id, std::string name, std::vector<Pos> positions, size_t thickness, std::shared_ptr<Color> color, std::shared_ptr<Color> fill);

    void Draw(Export & exporter) override;

    void MoveRelative(int x, int y) override;

    std::shared_ptr<SuperShape> Clone(const std::function<int(void)>& IdGenerator) override;

    bool operator==(const SuperShape &s) override;

    std::pair<size_t, size_t> CalcMaxDimensions() override;

    std::shared_ptr<PolyLine> ToPolyLine() override;

private:

    std::vector<Pos> positions;

};
