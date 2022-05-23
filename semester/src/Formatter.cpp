/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 19.05.2022
  * @basedon example semester work available on https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/tree/1.1.0
  */

#pragma once

#include "Formatter.h"


std::string Formatter::FillPlaceholder(const FormatterParams &formaterParams) {
    return FillPlaceholder(Formatter::PLACEHOLDER, formaterParams);
}
std::string Formatter::FillPlaceholder(const std::string &text, const FormatterParams &formaterParams) {
    std::string result = text;
    size_t start_pos;
    for (size_t i = 0; i < formaterParams.Size(); i++) {
        start_pos = result.find(Formatter::PLACEHOLDER);
        if (start_pos == std::string::npos)
            throw std::runtime_error("Number of FormaterParams does not match placeholders in '" + text + "'.");

        result.replace(start_pos, Formatter::PLACEHOLDER.length(), formaterParams[i]);
    }
    return result;

}

Formatter::Formatter(std::map<std::string, std::string> dict) : dict(std::move(dict)) {
}
