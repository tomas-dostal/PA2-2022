/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include "Circle.h"
#include "messages.h"
#include "Export.h"

Circle::Circle(int id, std::string name, std::shared_ptr<Pos> center, size_t diameter, size_t thickness,
               std::shared_ptr<Color> color, std::shared_ptr<Color> fill)
        : Ellipse(id, name, center, diameter, diameter, thickness, color, fill), diameter(diameter) {
    {

    }
}

// Todo maybe pass Draw method to Circle?
void Circle::Draw(Export & exporter) {
    this->ToPolyLine()->Draw(exporter);
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
    return std::make_pair(((int) width/2) + center->x + thickness * 2,((int) height/2) + center->y + thickness * 2);
}

void Circle::MoveRelative(int x, int y) {
    center->x += x;
    center->y += y;
}

std::shared_ptr<SuperShape> Circle::Clone(const std::function<int(void)> &IdGenerator) {
    return std::make_shared<Circle>(IdGenerator(), name, center->Clone(), diameter, thickness, color->Clone(), fill->Clone());
}


//std::shared_ptr<PolyLine> Circle::ToPolyLine() {
//    std::vector<Pos> positions;
//    const double angleIncrement = 360.0 / CIRCLE_PRECISION;
//
//    for (size_t i = 0; i < CIRCLE_PRECISION; i++) {
//        double angle = i * angleIncrement;
//        double x = this->center->x + this->width / 2 * cos(angle * M_PI / 180.0);
//        double y = this->center->y + this->height / 2 * sin(angle * M_PI / 180.0);
//        positions.emplace_back(x, y);
//    }
//
//    std::shared_ptr<PolyLine> polyLine = std::make_shared<PolyLine>(this->id, this->name, positions,
//                                                                    this->thickness, this->color,
//                                                                    this->fill);
//
//    return polyLine;
//}