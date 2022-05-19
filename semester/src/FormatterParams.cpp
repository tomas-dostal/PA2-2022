/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 19.05.2022
  */

#pragma once


#include "FormatterParams.h"
#include "vector"
#include "string"
#include "set"

FormatterParams::FormatterParams() {
    params = std::vector<std::string>();
}

FormatterParams::FormatterParams(const std::initializer_list<std::string> &initializerList) {
    for (auto it = initializerList.begin(); it != initializerList.end(); ++it) {
        params.emplace_back(static_cast<std::string>(*it))
    }
}

FormatterParams &FormatterParams::Add(const std::string &param) {
    params.emplace_back(param);
    return *this;
}

std::string FormatterParams::operator[](size_t idx) const {
    if (idx > params.size())
        throw std::out_of_range("FormatterParams[" + std::to_string(idx) + "] out of range");
    return params.at(idx);
}
