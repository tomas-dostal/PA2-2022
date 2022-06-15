/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include "Shape.h"
#include "Pos.h"
#include "Export.h"

class Circle : public Shape {
public:
    Circle() = delete;

    Circle(int id, std::string name, std::shared_ptr<Pos> center, size_t diameter, size_t thickenss,  std::shared_ptr<Color> color,
           std::shared_ptr<Color> fill);

    void Draw(Export & exporter) override;

    bool operator==(const SuperShape &s) override;

    std::pair<size_t, size_t> CalcMaxDimensions() override;

private:
    size_t diameter;

};
