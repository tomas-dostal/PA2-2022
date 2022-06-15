/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 08.05.2022
  */

#include <vector>
#include <string>

#include "Helper.h"

bool Helper::_isInRange(int val, int min, int max) {
    return (val >= min && val <= max);
}

bool Helper::_getIntFromStringStream(std::stringstream &ss, int &res) {
    if (!ss.eof() && !ss.bad()) {
        ss >> res;
        if (ss.fail()) {
            return false;
        }
        return true;
    }
    return false;
}

std::string Helper::Concat(std::vector<std::string> words, const std::string &separator, const std::string &end) {
    std::string result;
    for (size_t i = 0; i < words.size(); i++) {
        result += words[i];
        result += (i < (words.size() - 1)) ? separator : end;
    }
    return result;
}

std::string Helper::PrintOrDefault(const std::string &text, const std::string &def) {
    if (!text.empty())
        return text;
    return def;
}

int Helper::Extreme(const std::initializer_list<int> &values, std::function<bool(int, int)> & comp) {
    int max = 0;
    for (int value : values) {
        if(comp(value,max))
            max = value;
    }
    return max;
}
std::string Helper::ToString(const std::vector<std::string> & in){
    std::string out = "";
    for(auto line: in){
        out += line + "\n";
    }
    return out;

}
std::vector<std::string> Helper::Indent(const std::string & sep, const std::vector<std::string> & in){

    std::vector<std::string> out;
    for(auto & line: in){
        out.emplace_back(sep + line);
    }
    return out;
}


