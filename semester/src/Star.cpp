/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 27.05.2023
 */

#include "Star.h"
#include "Pos.h"
#include "PolyLine.h"

Star::Star(int id, std::string name, std::shared_ptr<Pos> center, size_t diameter, size_t thickness, std::shared_ptr<Color> color,
                              std::shared_ptr<Color> fill) : PolyLine(id, name,
                                                                      generateStarPositions(center, diameter),
                                                    thickness, color, fill),
                                                    diameter(diameter){}


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

    // Add positions for the points of the star
    positions.push_back(Pos(center->x, center->y - diameter));  // Top point
    positions.push_back(Pos(center->x + diameter / 2, center->y - diameter / 2));  // Top-right point
    positions.push_back(Pos(center->x + diameter, center->y));  // Right point
    positions.push_back(Pos(center->x + diameter / 2, center->y + diameter / 2));  // Bottom-right point
    positions.push_back(Pos(center->x, center->y + diameter));  // Bottom point
    positions.push_back(Pos(center->x - diameter / 2, center->y + diameter / 2));  // Bottom-left point
    positions.push_back(Pos(center->x - diameter, center->y));  // Left point
    positions.push_back(Pos(center->x - diameter / 2, center->y - diameter / 2));  // Top-left point

    // Add the first position again to close the shape
    positions.push_back(positions.front());

    return positions;
}

std::shared_ptr<SuperShape> Star::Clone(const std::function<int(void)>& IdGenerator) {
    return std::make_shared<Star>(IdGenerator(), name, center, diameter, thickness, color->Clone(), fill->Clone());
}
