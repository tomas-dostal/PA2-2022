
/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 08.05.2022
  */

#include "Line.h"
#include "Formatter.h"
#include "Export.h"
#include "messages.h"

Line::Line(int id, std::string name, Pos &a, Pos &b, size_t thickness, std::shared_ptr<Color> color,
           std::shared_ptr<Color> fill)
        : Shape(id,
                name,
                std::make_shared<Pos>(Pos(abs(a.x - b.x) / 2, abs(a.y - b.y) / 2)),
                abs(a.x - b.x),
                abs(a.y - b.y),
                thickness,
                color,
                fill),
          a(a),
          b(b){


}

bool Line::operator==(const SuperShape &s) {
    const Line *ptr = dynamic_cast<const Line *>( &s );
    return ptr != nullptr
           && this->a == ptr->a
           && this->b == ptr->b
           && this->center == ptr->center
           && this->fill == ptr->fill
           && this->color == ptr->color;
}


void Line::Draw(Export & exporter) {
    exporter.Process(SHAPE_LINE, {
            {START_X,   std::to_string(a.x)},
            {START_Y,   std::to_string(a.y)},
            {END_X,   std::to_string(b.x)},
            {END_Y,   std::to_string(b.y)},
            {CENTER_Y,   std::to_string(this->center->x)},
            {CENTER_X,   std::to_string(this->center->x)},
            {CENTER_Y,   std::to_string(this->center->x)},
            {COLOR_R,    std::to_string(this->color->R())},
            {COLOR_G,    std::to_string(this->color->G())},
            {COLOR_B,    std::to_string(this->color->B())},
            {FILL_R,     std::to_string(this->fill->R())},
            {FILL_G,     std::to_string(this->fill->G())},
            {FILL_B,     std::to_string(this->fill->B())},
            {THICKNESS,  std::to_string(this->thickness)}
    });

}

std::string Line::Print() const {
    // todo finish formatting
    return "" + name + " (" + std::to_string(id) + ")";

}

std::pair<size_t, size_t> Line::CalcMaxDimensions(){
    return std::make_pair(thickness * 2 + std::max(a.x, b.x), thickness * 2 + std::max(a.y, b.y));
}
