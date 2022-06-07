/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 31.05.2022
 */

#include "ExportHelper.h"
#include "messages.h"

ExportHelper::ExportHelper(const std::string & fileName, std::shared_ptr<Tspaint> tspaint): fileName(fileName), tspaint(tspaint){
    this->fileOut.open(fileName, std::ofstream::out);
    if (!fileOut) {
        throw std::runtime_error(ERROR_FILE_IO);
    }
};