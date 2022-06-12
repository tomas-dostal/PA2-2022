/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include "Line.h"
#include "Helper.h"
#include "Formatter.h"

Line::Line(int id, std::string name, Pos &a, Pos &b, size_t thickness, std::shared_ptr<Color> color,
           std::shared_ptr<Color> fill)
        : Shape(id,
                name,
                std::make_shared<Pos>(Pos(abs(a.x - b.x) / 2, abs(a.y - b.y) / 2)),
                abs(a.x - b.x),
                abs(a.y - b.y),
                thickness,
                color,
                fill) {


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

void Line::Draw(std::shared_ptr<Interface> interface, std::string format) {
    interface->PrintInfo("Line.");

}

std::string Line::Print() const {
    // todo finish formatting
    return "" + name + " (" + std::to_string(id) + ")";

}
