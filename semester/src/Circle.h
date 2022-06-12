/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include "Shape.h"
#include "Pos.h"
#include "Interface.h"

class Circle : public Shape {
public:
    Circle() = delete;

    Circle(int id, std::string name, std::shared_ptr<Pos> center, size_t diameter, size_t thickenss,  std::shared_ptr<Color> color,
           std::shared_ptr<Color> fill);

    void Draw(std::shared_ptr<Interface> interface, std::string format) override;

    std::string Print() const override;

    bool operator==(const SuperShape &s) override;

private:
    size_t diameter;
};
