/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 31.05.2022
 */

#pragma once

#include <fstream>

#include "Export.h"

class ExportTspaint : public Export {
public:

    ExportTspaint(const std::function<std::shared_ptr<std::fstream>(std::ios_base::openmode)>& openFile);

    bool Start(int width, int height)  override;

    bool End() override;

    bool Process(std::string SuperShapeName, std::map<std::string, std::string> dict) override;

    std::map<std::string, std::string> tspaintDict;
private:
    std::ofstream file;

};
