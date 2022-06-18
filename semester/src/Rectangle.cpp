/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 12.06.2022
 */

#include "Rectangle.h"
#include "messages.h"

Rectangle::Rectangle(int id, std::string name, Pos &start, size_t width, size_t height, size_t thickness,
                     std::shared_ptr<Color> color, std::shared_ptr<Color> fill) :
        Shape(id,
              name,
              std::make_shared<Pos>(
                      Pos(abs((int) (start.x +
                                     width) / 2),
                          abs((int) (start.y +
                                     height) / 2))),
              width,
              height,
              thickness,
              color,
              fill),
        start(start) {

}


bool Rectangle::operator==(const SuperShape &s) {
    const Rectangle *ptr = dynamic_cast<const Rectangle *>( &s );
    return ptr != nullptr
           && this->start == ptr->start
           && this->height == ptr->height
           && this->width == ptr->width
           && this->center == ptr->center
           && this->fill == ptr->fill
           && this->color == ptr->color;
}


void Rectangle::Draw(Export &exporter) {
    exporter.Process(SHAPE_RECTANGLE, {
            {START_X,   std::to_string(start.x)},
            {START_Y,   std::to_string(start.y)},
            {WIDTH,     std::to_string(width)},
            {HEIGHT,    std::to_string(height)},
            {CENTER_X,  std::to_string(this->center->x)},
            {CENTER_Y,  std::to_string(this->center->y)},
            {COLOR_R,   std::to_string(this->color->R())},
            {COLOR_G,   std::to_string(this->color->G())},
            {COLOR_B,   std::to_string(this->color->B())},
            {FILL_R,    std::to_string(this->fill->R())},
            {FILL_G,    std::to_string(this->fill->G())},
            {FILL_B,    std::to_string(this->fill->B())},
            {THICKNESS, std::to_string(this->thickness)}
    });

}

std::pair<size_t, size_t> Rectangle::CalcMaxDimensions(){
    return std::make_pair(width + start.x + thickness * 2, height + start.y + thickness * 2);
}

