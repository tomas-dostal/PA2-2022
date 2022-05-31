/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 13.05.2022
  */

#include "ColorPalette.h"

std::shared_ptr<Color> ColorPalette::getColorByName(const std::string &name) const {

    auto i = colors.find(name);

    if (i == colors.end()) {
        throw std::invalid_argument("getColorByName: " + name + "not found. ");
    }
    return i->second;
}


void ColorPalette::addIfNotExists(const std::string &name, const std::shared_ptr<Color> c) {
    std::map<std::string, std::shared_ptr<Color>>::iterator i = colors.find(name);
    if (i == this->colors.end()) {
        colors.insert({name, c});
    }
}
