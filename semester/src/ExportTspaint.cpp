/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 31.05.2022
 */

#include "ExportTspaint.h"

#include <utility>
#include "iostream"
#include "messages.h"
#include "ostream"

ExportTspaint::ExportTspaint(const std::string &fileName, std::shared_ptr<Tspaint> tspaint){
    this->fileOut.open(fileName, std::ofstream::out);
    if (!fileOut) {
        throw std::runtime_error(ERROR_FILE_IO);
    }
}

bool ExportTspaint::Export() {
    std::cout << " ExporTspaint::Export I'm alive" << std::endl;

}
