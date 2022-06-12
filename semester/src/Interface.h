/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <memory>

#include "Color.h"
#include "Pos.h"
#include "Formatter.h"
#include "ColorPalette.h"

class Interface {
public:
    Interface(std::istream &is, std::ostream &os);

    std::string PromptBasic(const std::string &msg, const std::string &msgInvalid,
                            const std::function<bool(const std::string &)> &valid) const;

    std::string PromptCommand(const std::function<bool(const std::string &)> &valid) const;

    std::string PromptOption(const std::vector<std::string> &options) const;

    std::string PromptOption(const std::vector<std::string> &options,
                             const std::function<size_t(const std::string &)> &valid) const;

    int PromptInteger(const std::string &msg, const std::string &msgInvalid,
                      const std::function<bool(const size_t &)> &valid) const;

    int PromptInteger(const std::function<bool(const size_t &)> &valid) const;

    std::vector<int> PromptMultipleIntegers(size_t howMany, const std::vector<std::string> &messages,
                                            const std::vector<std::string> &messagesInvalid,
                                            const std::vector<std::function<bool(const int &)>> &validators) const;

    std::shared_ptr<Color> PromptColor(ColorPalette &colorPalette) const;

    std::string PromptName(const std::function<bool(const std::string &)> &valid) const;

    void PrintHelp(const std::string &help);

    void PrintInfo(const std::string &help);

    void PrintCommandExample(const std::string &example);

    void PrintCommandName(const std::string &name);

    void ProgtestGreetings(const std::string &beautifulError);

    void ClearScreen();

    Pos PromptPos(const std::string &msg, const std::string &msgInvalid,
                  const std::function<bool(const int &)> &valid) const;

    Pos PromptPos(const std::string &msg) const;

    Pos PromptPos() const;

    bool isHeadless() const;

    void setHeadless(bool val);

    bool End() const;

    friend std::ostream &operator<<(std::ostream &os, const std::string &text);

    std::unique_ptr<Formatter> formatter;
    std::istream &is;
private:
    std::ostream &os;

    int attempts;
    bool headless;

    void ClearOrThrow() const;
};
