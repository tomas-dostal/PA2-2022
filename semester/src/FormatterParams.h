/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 19.05.2022
  *
  *
  */

#pragma once

#include <set>
#include "string"

class FormatterParams {
public:
    FormatterParams();

    //template<typename T>
    FormatterParams(const std::initializer_list<std::string> &initializerList);

    FormatterParams &Add(const std::string &param);

    [[nodiscard]] size_t Size() const { return params.size(); }

    std::string operator[](size_t idx) const;

private:
    std::vector<std::string> params;
};

