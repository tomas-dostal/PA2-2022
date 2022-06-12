/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 31.05.2022
 */

#include <ostream>
#include <utility>
#include <iostream>

#include "ExportTspaint.h"
#include "messages.h"

ExportTspaint::ExportTspaint(const std::string &fileName):
        Export(fileName){
    this->fileOut.open(fileName, std::ofstream::out);
    if (!fileOut) {
        throw std::runtime_error(ERROR_FILE_IO);
    }
}

bool ExportTspaint::Start(){
    std::cout << " ExporTspaint::Export I'm alive" << std::endl;
    return false;
}

bool ExportTspaint::Process(std::string SuperShapeName, std::map<std::string, std::string> dict){
    return false;
}