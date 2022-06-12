/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 19.05.2022
  */

#include <string>
#include <vector>

#include "FormatterParams.h"

FormatterParams::FormatterParams() {
    this->params = std::vector<std::string>();
}

FormatterParams::FormatterParams(const std::initializer_list<int> &initializerList) {
    this->params = std::vector<std::string>();
    for (auto it = initializerList.begin(); it != initializerList.end(); ++it) {
        this->params.emplace_back(std::to_string(*it));
    }
}

FormatterParams::FormatterParams(const std::initializer_list<std::string> &initializerList) {
    this->params = std::vector<std::string>();
    for (auto it = initializerList.begin(); it != initializerList.end(); ++it) {
        this->params.emplace_back(*it);
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
