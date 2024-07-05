/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 08.05.2022
  */

#pragma once

#include <sstream>
#include <functional>

class Helper {

public:
    static bool _isInRange(int val, int min, int max);

    static std::string Concat(std::vector<std::string> words, const std::string &separator, const std::string &end);

    static int Extreme(const std::initializer_list<int> &values, std::function<bool(int, int)> & comp);

    static bool _getIntFromStringStream(std::stringstream &ss, int &res);

    static std::string PrintOrDefault(const std::string &text, const std::string &def);

    static std::vector<std::string> Indent(const std::string & sep, const std::vector<std::string> & in) ;

    static std::string ToString(const std::vector<std::string> &in);
};

// predefined modes for file open
static std::ios_base::openmode OPEN_FILE_READ_STR = std::ios_base::in;
static std::ios_base::openmode OPEN_FILE_READ_BINARY = std::ios_base::in | std::ios_base::binary;
static std::ios_base::openmode OPEN_FILE_WRITE_STR = std::ios_base::out;
static std::ios_base::openmode OPEN_FILE_WRITE_BINARY = std::ios_base::out | std::ios_base::binary;
