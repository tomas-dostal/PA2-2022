/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 08.05.2022
  */

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
