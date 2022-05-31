/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 08.05.2022
  */

#pragma once

#include <sstream>

class Helper {

public:
    static bool _isInRange(int val, int min, int max);
    static std::string Concat(std::vector<std::string> words, const std::string & separator, const std::string & end);
    static bool _getIntFromStringStream(std::stringstream &ss, int &res);
    static std::string PrintOrDefault(const std::string & text, const std::string & def);
};

