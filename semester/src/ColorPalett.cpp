/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 13.05.2022
  */

#include "ColorPalett.h"

std::shared_ptr<Color> ColorPalett::getColorByName(const std::string & name) const{

    std::map<std::string,std::shared_ptr<Color>>::iterator i = colors.find(name);

    if (i == colors.end()) {
        throw std::invalid_argument("getColorByName: " + name + "not found. ");
    }
    return i->second;
}


void ColorPalett::addIfNotExists(const std::string & name, const std::shared_ptr<Color> c) {
    std::map<std::string,std::shared_ptr<Color>>::iterator i = colors.find(name);
    if (i == colors.end()) {
        colors.insert({name, c});
    }
}

ColorPalett::ColorPalett() {

}
