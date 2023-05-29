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

    // This class is just an extra fun. The goal is to from time to time
    // print some error message, it's not really important which one.

    std::ifstream f(fileName);
    if (!f) {
        messages.emplace_back(PROGTEST_ERROR_LOADING);
        return;
    }

    std::string line;
    while (getline(f, line)) {
        messages.emplace_back(line);
    }

    if (!f.eof()) {
        messages.emplace_back(PROGTEST_ERROR_LOADING);
    }
}

void ProgtestErrors::PrintRandomErrorMessageBecauseWhyNot() {
    if (std::rand() % 42 > 24) {
        int index = std::rand() % messages.size();
        interface->ProgtestGreetings(messages[index]);

    }
}
