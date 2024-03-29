/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 31.05.2022
 */

#pragma once

#include <string>
#include <map>
#include <fstream>
#include <functional>
#include "Pos.h"

class Export {
public:

    Export(const std::function<std::shared_ptr<std::fstream>(std::ios_base::openmode)>& openFile, std::ios_base::openmode mode);

    ~Export();

    virtual bool Start(int width, int height) = 0;

    virtual bool Process(std::string SuperShapeName, std::map<std::string, std::string> dict) = 0;

    virtual bool End() = 0;

protected:
    std::shared_ptr<std::fstream> file;
};
