/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 31.05.2022
 */

#include "memory"
#include "Export.h"
#include "messages.h"
#include "iostream"

Export::Export(const std::string &fileName, std::ios_base::openmode mode) : fileName(fileName) {
    file.open(fileName, mode);
    if (!file) {
        std::cerr << "Error: Cannot open file " << fileName << "." << std::endl;
        file.close();
        throw std::runtime_error(ERROR_FILE_IO);
    }
}

Export::~Export() {
    if (file.is_open()) {
        file.close();
    }
}
