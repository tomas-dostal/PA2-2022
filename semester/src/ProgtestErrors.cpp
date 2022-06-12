/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 28.05.2022
 */


#include <utility>
#include <iostream>
#include <string>
#include <fstream>

#include "ProgtestErrors.h"
#include "messages.h"

ProgtestErrors::ProgtestErrors(std::shared_ptr<Interface> interface, float probability, const std::string &fileName) :
        probability(probability),
        interface(interface) {

//    std::cerr << std::filesystem::current_path();

    std::ifstream f;
    f.open(fileName, std::ios::in);
    if (f.is_open()) {
        std::string line;
        while (getline(f, line)) {
            messages.emplace_back(line);
        }
    } else {
        messages.emplace_back(PROGTEST_ERROR_LOADING);
    }
}

void ProgtestErrors::PrintRandomErrorMessageBecauseWhyNot() {
    if (std::rand() % 42 > this->probability * 24) {
        int index = std::rand() % messages.size();
        interface->ProgtestGreetings(messages[index]);

    }
}
