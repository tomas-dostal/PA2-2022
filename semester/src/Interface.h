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
#include <cassert>

#include "Color.h"
#include "Pos.h"
#include "Formatter.h"
#include "ColorPalette.h"

class Interface {
public:
    Interface(std::istream &is, std::ostream &os);

    /**
     * Prompt for a basic value (text, one word)
     * @param msg Prints this message to @param os to get input from user
     * @param msgInvalid Prints this message to @param os if incorrect input
     * @param valid Input is validated by this function pointer
     * @return std::string user input
     */
    std::string PromptBasic(const std::string &msg, const std::string &msgInvalid,
                            const std::function<bool(const std::string &)> &valid) const;

    /**
     * Prompt for a command (one word)
     * @param valid Input is validated by this function pointer
     * @return std::string command name
     */
    std::string PromptCommand(const std::function<bool(const std::string &)> &valid) const;

    /**
     * Prompt for a option from vector of options. Only options from list are allowed,
     * if non-list one is provided by user, the user is prompted to provide a correct option.
     * @param options: List of possible options
     * @return std::string selected option
     */
    std::string PromptOption(const std::vector<std::string> &options) const;

    /**
     * Prompt for a option from vector of options. Only options from list are allowed,
     * if non-list one is provided by user, the user is prompted to provide a correct option.
     * @param options List of possible options
     * @param valid Custom validator
     * @return std::string selected option
     */
    std::string PromptOption(const std::vector<std::string> &options,
                             const std::function<size_t(const std::string &)> &valid) const;

    /**
     * Prompt for a integer validated by @param valid
     * Custom messages.
     * @param msg Prints this message to @param os to get input from user
     * @param msgInvalid Prints this message to @param os if incorrect input
     * @param valid Custom validator
     * @return int: validated user input
     */
    int PromptInteger(const std::string &msg, const std::string &msgInvalid,
                      const std::function<bool(const size_t &)> &valid) const;

    /**
     * Prompt for a integer validated by @param valid
     * Fefault message
     * @param valid Custom validator
     * @return int: validated user input
     */
    int PromptInteger(const std::function<bool(const size_t &)> &valid) const;

    /**
     * Multiple calls to PromptInteger()
     * @param howMany positive int: number of integers to be loaded
     * @param messages  prints one of there messages to @param os (either matching index, or the first one if not enough of messages)
     * @param messagesInvalid prints one of there messages to @param os if incorrect input (either matching index, or the first one if not enough of messages)
     * @param validators list of custom validators
     * @return  std::vector<int> validated results
     */
    std::vector<int> PromptMultipleIntegers(size_t howMany, const std::vector<std::string> &messages,
                                            const std::vector<std::string> &messagesInvalid,
                                            const std::vector<std::function<bool(const int &)>> &validators) const;

    /**
     * PromptColor gets color by rgb, id or name from user (interactive)
     * @param colorPalette Instance of ColorPallete holding information about colors used
     * @return std::shared_ptr<Color> Smart pointer to selected color
     */
    std::shared_ptr<Color> PromptColor(ColorPalette &colorPalette) const;

    /**
     * Prompts one word from user
     * @param valid Custom validator
     * @return std::string validated name
     */
    std::string PromptName(const std::function<bool(const std::string &)> &valid) const;

    /**
     * Prompt for a Pos (int, int) validated by @param valid
     * Custom messages.
     * @param msg Prints this message to @param os to get input from user
     * @param msgInvalid Prints this message to @param os if incorrect input
     * @return  Pos(x, y) instance
     */
    Pos PromptPos(const std::string &msg, const std::string &msgInvalid,
                  const std::function<bool(const int &)> &valid) const;

    /**
    * Prompt for a Pos (int, int)
    * Custom messages, auto validator.
    * @param msg Prints this message to @param os to get input from user
    * @return  Pos(x, y) instance
    */
    Pos PromptPos(const std::string &msg) const;

    /**
    * Prompt for a Pos (int, int)
    * Default messages, auto validator.
    * @return  Pos(x, y) instance
    */

    Pos PromptPos() const;

    /**
     * Method for printing help to output stream
     * @param help std::string to be printed
     */
    void PrintHelp(const std::string &help);

    /**
    * Method for printing info to output stream
    * @param info std::string info to be printed
    */
    void PrintInfo(const std::string &info);


    void PrintCommandExample(const std::string &example);

    void PrintCommandName(const std::string &name);

    void ProgtestGreetings(const std::string &beautifulError);

    void ClearScreen();

    bool isHeadless() const;

    /**
     * Set headless mode for loading from filestream.
     * Used not to get into the infinite loop of loading e.g. command, because
     * with this once bad input detected, input is canceled and all changes reverted.
     * @param val
     */
    void setHeadless(bool val);

    /**
     * Returns true of input stream is EOF
     * @return if is.eof()
     */
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
