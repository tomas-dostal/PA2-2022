/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include "Color.h"


bool Color::operator==(const Color &other) const {
    return this->r == other.r && this->g == other.g && this->b == other.b && this->name == other.name;
}

std::shared_ptr<Pixel> Color::GetPixel() const {
    return std::make_shared<Pixel>(r, g, b);
}

std::shared_ptr<Color> Color::Clone() {
    return std::make_shared<Color>(r, g, b, name);
}
