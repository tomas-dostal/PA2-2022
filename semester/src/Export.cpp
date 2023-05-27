/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 31.05.2022
 */

#include <memory>
#include <iostream>
#include "Export.h"
#include "messages.h"

Export::Export(const std::function<std::shared_ptr<std::fstream>(std::ios_base::openmode)> & openFile, std::ios_base::openmode mode){
    file = openFile(mode);
    if (!file) {
        std::cerr << "Error: Cannot open file." << std::endl;
        file->close();
        throw std::runtime_error(ERROR_FILE_IO);
    }
}

Export::~Export() {
    if (file->is_open()) {
        file->close();
    }
}
