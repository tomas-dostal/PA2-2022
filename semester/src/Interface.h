/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include <iostream>
#include "string"
#include "Color.h"
#include "Pos.h"

class Interface {
public:
    Interface(std::istream &is, std::ostream &os);

    std::string PromptCommand(const std::function<bool(const std::string &)> &valid) const;

    std::string PromptCommandOption(const std::function<size_t(const std::string &)> &valid) const;

    std::shared_ptr<Color> PromptColor() const;


private:
    std::istream &is;
    std::ostream &os;

    Pos PromptPos();

    Pos PromptPos(const std::string &msg);

};
