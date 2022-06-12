/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 19.05.2022
  * @basedon example semester work available on https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/tree/1.1.0
  */

#pragma once

#include <string>
#include <map>
#include <memory>

#include "FormatterParams.h"
#include "Color.h"
#include "ColorPalette.h"
#include "Pos.h"

class Formatter {
public:
    explicit Formatter(std::map<std::string, std::string> dict);

    explicit Formatter();

    std::string FormatColor(std::shared_ptr<Color> color);

    std::string FormatNamedCoords(std::vector<std::pair<std::string, Pos>> namedCoords);

    std::string FillPlaceholder(const FormatterParams &formaterParams);

    std::string FillNamedPlaceholders(const std::string & text, const std::map<std::string, std::string> & dict);

    bool Replace(std::string & text, const std::string & from, const std::string &to);

    std::string FillPlaceholder(const std::string &text, const FormatterParams &formaterParams);

private:
    const std::string PLACEHOLDER = "$";
    std::map<std::string, std::string> dict;
};


