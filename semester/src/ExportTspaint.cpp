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

bool ExportTspaint::Start(int width, int height) {
    std::cout << " ExporTspaint::Export" << width << ", " << height << std::endl;
    return false;
}

bool ExportTspaint::Process(std::string superShapeName, std::map<std::string, std::string> dict){
    std::cout << " ExporTspaint::Process" << superShapeName <<  dict.size();
    return false;
}
bool ExportTspaint::End(){
    std::cout << "tspaint end " << std::endl;
    fileOut.close();
    return false;
}
