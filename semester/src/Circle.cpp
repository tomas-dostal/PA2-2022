/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include "Circle.h"
#include "messages.h"
#include "Export.h"

Circle::Circle(int id, std::string name, std::shared_ptr<Pos> center, size_t diameter, size_t thickness,
               std::shared_ptr<Color> color, std::shared_ptr<Color> fill)
        : Shape(id, name, center, 2 * diameter, 2 * diameter, thickness, color, fill), diameter(diameter) {
    {

    }
}

void Circle::Draw(Export & exporter) {
    exporter.Process(SHAPE_CIRCLE, {
            {CENTER_X,   std::to_string(this->center->x)},
            {CENTER_Y,   std::to_string(this->center->x)},
            {DIAMETER_X, std::to_string(this->diameter)},
            {COLOR_R,    std::to_string(this->color->R())},
            {COLOR_G,    std::to_string(this->color->G())},
            {COLOR_B,    std::to_string(this->color->B())},
            {FILL_R,     std::to_string(this->fill->R())},
            {FILL_G,     std::to_string(this->fill->G())},
            {FILL_B,     std::to_string(this->fill->B())},
            {THICKNESS,  std::to_string(this->thickness)}
    });
}

bool Circle::operator==(const SuperShape &s) {
    const Circle *ptr = dynamic_cast<const Circle *>( &s );
    return ptr != nullptr
           && this->diameter == ptr->diameter
           && this->fill == ptr->fill
           && this->color == ptr->color
           && this->center == ptr->center;
    // that's enough
}


std::pair<size_t, size_t> Circle::CalcMaxDimensions(){
    return std::make_pair(((int) width/2) + center->x + thickness,((int) height/2) + center->y + thickness);
}
