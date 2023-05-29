/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 27.05.2023
 */

#include <algorithm>
#include <cmath>

#include "Star.h"
#include "Pos.h"
#include "PolyLine.h"

Star::Star(int id, std::string name, std::shared_ptr<Pos> center, size_t diameter, size_t thickness,
           std::shared_ptr<Color> color,
           std::shared_ptr<Color> fill) : PolyLine(id, name,
                                                   generateStarPositions(center, diameter),
                                                   thickness, color, fill),
                                          diameter(diameter) {}


bool Star::operator==(const SuperShape &s) {
    const Star *ptr = dynamic_cast<const Star *>( &s );
    const PolyLine *ptrPoly = dynamic_cast<const PolyLine *>( &s );
    return ptr != nullptr
           && this->diameter == ptr->diameter
           && ptrPoly != nullptr
           && ptrPoly == dynamic_cast<const PolyLine *>( this );
}


std::vector<Pos> Star::generateStarPositions(const std::shared_ptr<Pos> center, int diameter) {
    std::vector<Pos> positions;

    const int numTops = 6;
    const double angleIncrement = 2 * M_PI / numTops;

    for (int i = 0; i <= numTops; ++i) {
        double outerAngle = i * angleIncrement;
        double innerAngle = outerAngle + angleIncrement / 2.0;

        int outerX = center->x + diameter / 2 * sin(outerAngle);
        int outerY = center->y - diameter / 2 * cos(outerAngle);
        int innerX = center->x + diameter / 4 * sin(innerAngle);
        int innerY = center->y - diameter / 4 * cos(innerAngle);

        positions.push_back(Pos(outerX, outerY));
        positions.push_back(Pos(innerX, innerY));
    }
    return positions;
}

std::shared_ptr<SuperShape> Star::Clone(const std::function<int(void)> &IdGenerator) {
    return std::make_shared<Star>(IdGenerator(), name, center, diameter, thickness, color->Clone(), fill->Clone());
}

std::pair<size_t, size_t> Star::CalcMaxDimensions() {
    int maxX, maxY = 0;
    int minX, minY = std::numeric_limits<int>::max();;
    for (const auto& pos : positions) {
        maxX = std::max(maxX, pos.x);
        minX = std::min(minX, pos.x);
        maxY = std::max(maxY, pos.y);
        minY = std::min(minY, pos.y);
    }
    return std::make_pair<size_t, size_t>(maxX-minX + center->x, maxY-minY + center->y);
}
