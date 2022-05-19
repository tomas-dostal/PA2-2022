/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 19.05.2022
  * @basedon example semester work available on https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/tree/1.1.0
  */

#include "string"
#include "map"
#include "FormatterParams.h"

class Formatter {
public:
    explicit Formatter(std::map<std::string, std::string> dict);

    std::string FillPlaceholder(const std::string &text, const FormatterParams &formaterParams);

private:
    const std::string PLACEHOLDER = "$";
    std::map<std::string, std::string> dict;
};


