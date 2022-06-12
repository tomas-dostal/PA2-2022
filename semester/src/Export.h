/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 31.05.2022
 */

#pragma once

class Export;
#include <string>
#include <map>
#include <fstream>
#include "SuperShape.h"

class Export {
public:

    explicit Export(const std::string &fileName);

    virtual bool Start() = 0;

    virtual bool Process(std::string SuperShapeName, std::map<std::string, std::string> dict) = 0;

protected:

    std::string fileName;
    std::ofstream fileOut;
};
