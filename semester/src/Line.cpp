/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include "Line.h"
#include "Helper.h"

Line::Line(unsigned long id, std::string name, Pos &a, Pos &b, size_t thickness, std::shared_ptr<Color> color,
           std::shared_ptr<Color> fill)
        : Shape(id,
                name,
                Pos(abs(a.x - b.x) / 2, abs(a.y - b.y) / 2),
                abs(a.x - b.x),
                abs(a.y - b.y),
                thickness,
                color,
                fill) {


}

bool Line::operator==(const Shape &s) {
    const Line *ptr = dynamic_cast<const Line *>( &s );
    return ptr != nullptr
           && this->a == ptr->a
           && this->b == ptr->b
           && this->center == ptr->center
           && this->fill == ptr->fill
           && this->color == ptr->color;
}

void Line::Draw(Interface &interface) {
    interface.PrintInfo("Line.");

}
