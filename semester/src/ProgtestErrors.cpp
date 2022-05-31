/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 28.05.2022
 */

#include "ProgtestErrors.h"

#include <utility>
#include "messages.h"
#include "iostream"
#include "string"

/*
ProgtestErrors::ProgtestErrors(std::shared_ptr<Interface> interface, float probability, const std::string & fileName):
                                                                                        probability(probability),
                                                                                        interface(std::move(interface)) {
    std::ifstream f;
    f.open(fileName, std::ios::in);
    if (f.is_open()){
        std::string line;
        while (getline(f, line)){
            messages.emplace_back(line);
        }
    }
    else {
        messages.emplace_back(PROGTEST_ERROR_LOADING);
    }
}

void ProgtestErrors::PrintRandomErrorMessageBecauseWhyNot() {
    if ((std::rand() % 42) > this->probability * 10)
        interface->ProgtestGreetings(messages[(int) (std::rand() % (messages.size() - 1))]);
    return;
}
*/