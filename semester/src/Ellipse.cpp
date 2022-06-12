/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 12.06.2022
  */

#include "Ellipse.h"
#include "messages.h"
#include "Export.h"

Ellipse::Ellipse(int id, std::string name, std::shared_ptr<Pos> center, size_t diameter_x, size_t diameter_y,
                 size_t thickenss, std::shared_ptr<Color> color,
                 std::shared_ptr<Color> fill)
        : Shape(id, name, center, 2 * diameter_x, 2 * diameter_y, thickness, color, fill), diameter_x(diameter_x),
          diameter_y(diameter_y) {
}

void Ellipse::Draw(Export &exporter) {
    exporter.Process(SHAPE_ELLIPSE, {
            {CENTER_X,   std::to_string(this->center->x)},
            {CENTER_Y,   std::to_string(this->center->x)},
            {DIAMETER_X, std::to_string(this->diameter_x)},
            {DIAMETER_Y, std::to_string(this->diameter_y)},
            {COLOR_R,    std::to_string(this->color->R())},
            {COLOR_G,    std::to_string(this->color->G())},
            {COLOR_B,    std::to_string(this->color->B())},
            {FILL_R,     std::to_string(this->fill->R())},
            {FILL_G,     std::to_string(this->fill->G())},
            {FILL_B,     std::to_string(this->fill->B())},
            {THICKNESS,  std::to_string(this->thickness)}
    });
}

bool Ellipse::operator==(const SuperShape &s) {
    const Ellipse *ptr = dynamic_cast<const Ellipse *>( &s );
    return ptr != nullptr
           && this->diameter_x == ptr->diameter_x
           && this->diameter_y == ptr->diameter_y
           && this->fill == ptr->fill
           && this->color == ptr->color
           && this->center == ptr->center;
    // that's enough
}

std::string Ellipse::Print() const {
    return "" + name + " (" + std::to_string(id) + ")";
}


std::pair<size_t, size_t> Ellipse::CalcMaxDimensions() {
    return std::make_pair(width, height);
}