/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include "Shape.h"
#include "Pos.h"
#include "Export.h"

class Ellipse : public Shape {
public:
    Ellipse() = delete;

    Ellipse(int id, std::string name, std::shared_ptr<Pos> center, size_t diameter_x, size_t diameter_y,
            size_t thickness, std::shared_ptr<Color> color,
            std::shared_ptr<Color> fill);

    void Draw(Export &exporter) override;

    void MoveRelative(int x, int y) override;

    std::shared_ptr<SuperShape> Clone(const std::function<int(void)>& IdGenerator) override;

    bool operator==(const SuperShape &s) override;

    std::pair<size_t, size_t> CalcMaxDimensions() override;

    std::shared_ptr<PolyLine> ToPolyLine() override;

private:
    size_t diameter_x;
    size_t diameter_y;

};
