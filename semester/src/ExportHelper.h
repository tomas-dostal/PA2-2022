/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 31.05.2022
 */

#pragma once
#include "string"
#include "Tspaint.h"
#include "fstream"

class ExportHelper {
public:
    //ExportHelper(const std::string & fileName, std::shared_ptr<Tspaint> tspaint);
    virtual bool Export() = 0;
protected:
    std::ofstream fileOut;
    std::shared_ptr<Tspaint> tspaint;
};
