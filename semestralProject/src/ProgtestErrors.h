/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 28.05.2022
 */

#pragma once

#include <string>

#include "Interface.h"


class ProgtestErrors {
public:
    ProgtestErrors(std::shared_ptr<Interface> interface, float probability, const std::string &fileName);

    void PrintRandomErrorMessageBecauseWhyNot();

private:
    float probability;
    std::shared_ptr<Interface> interface;
    std::vector<std::string> messages;
};

