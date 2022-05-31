/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 08.05.2022
  */

#pragma once

#include <string>
#include <map>
#include "Color.h"

class ColorPalette {
public:
    ColorPalette() = default;

    void addIfNotExists(const std::string &name, const std::shared_ptr<Color> c);

    std::shared_ptr<Color> getColorByName(const std::string &name) const;

    std::shared_ptr<Color> getColorIndex(const size_t index) const;

    std::map<std::string, std::shared_ptr<Color>> colors;

};

