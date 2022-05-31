/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include <sstream>
#include "Interface.h"
#include "Color.h"
#include "Helper.h"
#include "ColorPalette.h"
#include "Pos.h"
#include "messages.h"
#include "FormatterParams.h"
#include "Formatter.h"
#include "constants.h"

Pos Interface::PromptPos(const std::string &msg) {
    this->os << msg << std::endl;

    std::string input;
    std::getline(is, input);

    std::stringstream ss(input);

    int a, b;

    if (Helper::_getIntFromStringStream(ss, a) && Helper::_getIntFromStringStream(ss, b)) {
        return {a, b};
    }
    os << "Unahle to fetch input. Try again.";
    return PromptPos(msg);
}


std::vector<int> Interface::PromptMultipleIntegers(size_t howMany, const std::vector<std::string> &messages,
                                                   const std::vector<std::string> &messagesInvalid,
                                                   const std::vector<std::function<bool(
                                                           const int &)>> &validators) const {

    assert(validators.size() > 0);
    assert(howMany > 0);

    std::vector<int> res(howMany);

    for (size_t index = 0; index < howMany; index++) {
        res.push_back(this->PromptInteger((messages.size() > index) ? messages[index] : "",
                                          (messagesInvalid.size() > index) ? messagesInvalid[index] : "",
                                          (validators.size() > index) ? validators[index] : validators[0])
        );
    }
    return res;
}


std::shared_ptr<Color> Interface::PromptColor(ColorPalette &colorPalette) const {

    std::stringstream colorOptionsStringStream;
    int i = 0;
    std::vector<std::shared_ptr<Color>> colors;
    for (auto & color : colorPalette.colors) {
        colorOptionsStringStream << i << ") " << color.first << std::endl;
        colors.push_back(color.second);
        i++;
    }

    this->os << "Select input od color: {id,rgb}";
    std::string option = this->PromptOption({"id", "rgb"});
    if (option == "id") {
        size_t index = this->PromptInteger(
                formatter->FillPlaceholder(SET_ENTER_COLOR_ID, FormatterParams{colorOptionsStringStream.str()}),
                formatter->FillPlaceholder(SET_ENTER_COLOR_ID_INVALID, {}),
                [&colors](const int &result) {
                    return Helper::_isInRange(result, 0, colors.size() - 1);
                });
        return colors[index];
    }

    // else
    std::vector<int> res = this->PromptMultipleIntegers(
            3,
            {
                    formatter->FillPlaceholder(SET_ENTER_COLOR_RGB, {"r"}),
                    formatter->FillPlaceholder(SET_ENTER_COLOR_RGB, {"g"}),
                    formatter->FillPlaceholder(SET_ENTER_COLOR_RGB, {"b"})
            },
            {
                    formatter->FillPlaceholder(SET_ENTER_COLOR_RGB_INVALID, {}),
            },
            std::vector<std::function<bool(const int &)>>{[](const int &result) {
                return Helper::_isInRange(result, RGB_MIN, RGB_MAX);
            }
            }
    );
    std::string name = this->PromptName([](const std::string &name) {
        return std::count_if(name.begin(), name.end(), [](unsigned char c) { return !std::isalnum(c); }
        ) > 0;
    });
    auto color = std::make_shared<Color>(Color(res[0], res[1], res[2]));
    colorPalette.addIfNotExists(name, color);
    return color;
}

/**
 *
 * @param valid
 * @return
 *
 *
 * @inspiredby https://gitlab.fit.cvut.cz/bernhdav/pa2-minesweeper/tree/master
 */
std::string Interface::PromptCommand(const std::function<bool(const std::string &)> &valid) const {
    std::string command;
    while (true) {
        os << formatter->FillPlaceholder({PROMPT_COMMAND}) << std::endl;

        if (!(is >> command)) {
            os << formatter->FillPlaceholder({INVALID_INPUT}) << std::endl;
        } else if (!valid(command)) {
            //std::string tmp = COMMAND_HELP;
            os << formatter->FillPlaceholder(UNKNOWN_COMMAND, FormatterParams({command, COMMAND_HELP})) << std::endl;
        } else {
            return command;
        }
    }
}

std::string Interface::PromptOption(const std::vector<std::string> &options) const {
    return PromptOption(options, [&options](const std::string &commandName) {
                            return std::find(options.begin(), options.end(), commandName) !=
                                   options.end();
                        }
    );
}


std::string Interface::PromptOption(const std::vector<std::string> &options,
                                    const std::function<size_t(const std::string &)> &valid) const {
    std::string option;
    while (true) {
        os << formatter->FillPlaceholder({PROMPT_OPTION}) << std::endl;

        if (!(is >> option)) {
            os << formatter->FillPlaceholder({INVALID_INPUT}) << std::endl;
        } else if (!valid(option)) {
            os << formatter->FillPlaceholder(UNKNOWN_OPTION, FormatterParams({option, COMMAND_HELP})) << std::endl;
            os << formatter->FillPlaceholder(AVAILABLE_OPTION,
                                             FormatterParams{Helper::Concat(options, ", ", "\n")});
        } else {
            return option;
        }
    }
}

Interface::Interface(std::istream &is, std::ostream &os) : is(is), os(os) {
    this->formatter = std::make_unique<Formatter>(Formatter(std::map<std::string, std::string>()));
}

void Interface::PrintHelp(const std::string &help) {
    os << "HELP: " << help << std::endl;
}

void Interface::ClearScreen() {
    os.clear();
}

int Interface::PromptInteger(const std::string &msg,
                             const std::string &msgInvalid,
                             const std::function<bool(const size_t &)> &valid) const {

    size_t integer;
    while (true) {
        os << formatter->FillPlaceholder({Helper::PrintOrDefault(msg, PROMPT_INTEGER)}) << std::endl;

        if (!(is >> integer) || !valid(integer)) {
            os << formatter->FillPlaceholder({Helper::PrintOrDefault(msgInvalid, INVALID_INPUT)}) << std::endl;
            is.clear();
        } else {
            return integer;
        }
    }
}


void Interface::ProgtestGreetings(const std::string &beautifulError) {
    os << beautifulError << std::endl;
}

std::string Interface::PromptName(const std::function<bool(const std::string &)> &valid) const {
    std::string name;
    while (true) {
        os << formatter->FillPlaceholder({SET_ENTER_COLOR_RGB_NAME}) << std::endl;

        if (!(is >> name) || !valid(name)) {
            os << formatter->FillPlaceholder({INVALID_INPUT}) << std::endl;
        } else {
            return name;
        }
    }
}

