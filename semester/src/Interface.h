/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include <iostream>
#include "string"
#include "Color.h"
#include "Pos.h"
#include "Formatter.h"
#include "ColorPalette.h"

class Interface {
public:
    Interface(std::istream &is, std::ostream &os);

    std::string PromptCommand(const std::function<bool(const std::string &)> &valid) const;

    std::string PromptOption(const std::vector<std::string> & options,
                             const std::function<size_t(const std::string &)> &valid) const;

    int PromptInteger(const std::string & msg, const std::string & msgInvalid, const std::function<bool(const size_t &)> &valid) const;

    std::vector<int> PromptMultipleIntegers(size_t howMany, const std::vector<std::string>& messages, const std::vector<std::string>& messagesInvalid, const  std::vector<std::function<bool(const int &)>> &validators) const;

    std::shared_ptr<Color> PromptColor(ColorPalette & colorPalette) const;

    std::string PromptName(const std::function<bool(const std::string &)> &valid) const;

    void PrintHelp(const std::string & help);

    void ProgtestGreetings(const std::string & beautifulError);

    void ClearScreen();

    Pos PromptPos();

    Pos PromptPos(const std::string &msg);

    std::unique_ptr<Formatter> formatter;
private:
    std::istream &is;
    std::ostream &os;


    std::string PromptOption(const std::vector<std::string> &options) const;
};
