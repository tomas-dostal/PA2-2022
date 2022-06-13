/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include "Color.h"


bool Color::operator==(const Color &other) const {
    return this->r == other.r && this->g == other.g && this->b == other.b && this->name == other.name;
}
