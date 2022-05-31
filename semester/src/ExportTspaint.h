/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 31.05.2022
 */

#pragma once


#include "ExportHelper.h"

class ExportTspaint: public ExportHelper {
public:

    ExportTspaint(const std::string &fileName, std::shared_ptr<Tspaint> tspaint);

    bool Export() override;

    const std::shared_ptr<Tspaint> tspaint;
};
