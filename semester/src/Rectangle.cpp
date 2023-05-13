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
    // After feedback from last year I decided to solve Draw more universally,
    // aka casting to PolyLine and drawing it instead of drawing rectangle directly.
    // This allows me to reuse the code from PolyLine, which is more advanced shape that theoretically
    // can be used for drawing any shape.
    this->ToPolyLine()->Draw(exporter);
}

void Rectangle::MoveRelative(int x, int y) {
    start.x += x;
    start.y += y;
    center->x += x;
    center->y += y;
}

std::pair<size_t, size_t> Rectangle::CalcMaxDimensions(){
    return std::make_pair(width + start.x + thickness * 2, height + start.y + thickness * 2);
}

std::shared_ptr<SuperShape> Rectangle::Clone(const std::function<int(void)>& IdGenerator) {
    Pos start2 = Pos(start.x, start.y);
    return std::make_shared<Rectangle>(IdGenerator(), name, start2, width, height, thickness, color->Clone(), fill->Clone());
}

std::shared_ptr<SuperShape> Rectangle::ToPolyLine() {
    return std::make_shared<PolyLine>(this->id, name, std::vector<Pos>{
            Pos(start.x, start.y),
            Pos(start.x + (int) width, start.y),
            Pos(start.x + (int) width, start.y + (int) height),
            Pos(start.x, start.y + (int) height),
            Pos(start.x, start.y)
    }, thickness, color, fill);
}
