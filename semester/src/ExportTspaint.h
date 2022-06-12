/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 31.05.2022
 */

#pragma once

#include "Export.h"

class ExportTspaint : public Export {
public:

    ExportTspaint(const std::string &fileName);

    bool Start() override;

    bool Process(std::string SuperShapeName, std::map<std::string, std::string> dict) override;

    std::map<std::string, std::string> tspaintDict;

};
