/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 08.05.2022
  */

#pragma once

#include <sstream>

class Helper {

public:
    static bool _isInRange(int val, int min, int max);

    static bool _getIntFromStringStream(std::stringstream &ss, int &res);
};

