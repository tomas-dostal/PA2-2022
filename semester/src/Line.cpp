
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
    this->ToPolyLine()->Draw(exporter);
}

std::pair<size_t, size_t> Line::CalcMaxDimensions(){
    return std::make_pair(thickness * 2 + std::max(a.x, b.x), thickness * 2 + std::max(a.y, b.y));
}

void Line::MoveRelative(int x, int y) {
    a.x += x;
    a.y += y;
    b.x += x;
    b.y += y;
    center->x += x;
    center->y += y;
}

std::shared_ptr<SuperShape> Line::Clone(const std::function<int(void)> &IdGenerator) {
    Pos startClone = Pos(a.x, a.y);
    Pos endClone = Pos(b.x, b.y);
    return std::make_shared<Line>(IdGenerator(), name, startClone, endClone, thickness, color->Clone(), fill->Clone());
}

std::shared_ptr<SuperShape> Line::ToPolyLine() {
    return std::make_shared<PolyLine>(this->id, name, std::vector<Pos>{a, b}, thickness, color, fill);
}

