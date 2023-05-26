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
        Export(fileName, std::ofstream::out){
}

bool ExportTspaint::Start(int width, int height) {
    std::cout << " ExporTspaint::Export" << width << ", " << height << std::endl;
    std::cerr << "ExporTspaint Not implemented" << std::endl;
    return false;
}

bool ExportTspaint::Process(std::string superShapeName, std::map<std::string, std::string> dict){
    std::cout << " ExporTspaint::Process" << superShapeName <<  dict.size();
    std::cerr << "ExporTspaint Not implemented" << std::endl;

    return false;
}
bool ExportTspaint::End(){
    std::cerr << "ExporTspaint Not implemented" << std::endl;
    return false;
}
