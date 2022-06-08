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
#include "cctype"


// todo!!!! Fix unexpected input by clearing the rest of buffer

Pos Interface::PromptPos() const {
    return PromptPos("", "", nullptr);
}

Pos Interface::PromptPos(const std::string &msg) const {
    return PromptPos(msg, "", nullptr);
}

Pos Interface::PromptPos(const std::string &msg = "", const std::string &msgInvalid = "",
                         const std::function<bool(const int &)> &valid = nullptr) const {
    std::vector<int> pos = PromptMultipleIntegers(2,
                                                  {
                                                          {Helper::PrintOrDefault(msg, formatter->FillPlaceholder(
                                                                  {PROMPT_POSITION}))}
                                                  },
                                                  {
                                                          {Helper::PrintOrDefault(msgInvalid,
                                                                                  formatter->FillPlaceholder(
                                                                                          ENTER_VALUE_IN_RANGE,
                                                                                          {POS_X_MIN, POS_X_MAX}))},
                                                          {Helper::PrintOrDefault(msgInvalid,
                                                                                  formatter->FillPlaceholder(
                                                                                          ENTER_VALUE_IN_RANGE,
                                                                                          {POS_Y_MIN, POS_Y_MAX}))},
                                                  },
                                                  std::vector<std::function<bool(const int &a)>>{
                                                          {
                                                                  [](const int &a) {
                                                                      return Helper::_isInRange(a, POS_X_MIN,
                                                                                                POS_X_MAX);
                                                                  }
                                                          },
                                                          {
                                                                  [](const int &a) {
                                                                      return Helper::_isInRange(a, POS_Y_MIN,
                                                                                                POS_Y_MAX);
                                                                  }
                                                          }
                                                  }
    );
    return Pos(pos[0], pos[1]);
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
    for (auto &color: colorPalette.colors) {
        colorOptionsStringStream << i << ") " << color.first << std::endl;
        colors.push_back(color.second);
        i++;
    }

    this->os << "Select input of color: {id,rgb} ";
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
        return any_of(name.begin(), name.end(), [](const char &c) -> bool {
            return !isalpha(c);
        });
    });

    auto color = std::make_shared<Color>(Color(res[0], res[1], res[2], name));
    colorPalette.addIfNotExists(color);

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

        if (!(is >> command) || !valid(command)) {
            os << formatter->FillPlaceholder(UNKNOWN_COMMAND, FormatterParams({command, COMMAND_HELP})) << std::endl;
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (isHeadless())
                throw std::runtime_error(FILE_LOADING_ERROR);
            if (is.eof())
                throw std::runtime_error("EOF");
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

        if (!(is >> option) || (!valid(option))) {
            os << formatter->FillPlaceholder(UNKNOWN_OPTION, FormatterParams({option, COMMAND_HELP})) << std::endl;
            os << formatter->FillPlaceholder(AVAILABLE_OPTION,
                                             FormatterParams{Helper::Concat(options, ", ", "\n")});
            if (isHeadless())
                throw std::runtime_error(FILE_LOADING_ERROR);
            if (is.eof())
                throw std::runtime_error("EOF");
        } else {
            return option;
        }
    }
}

Interface::Interface(std::istream &is, std::ostream &os) : is(is), os(os) {
    this->formatter = std::make_unique<Formatter>(Formatter(std::map<std::string, std::string>()));
    attempts = 5;
    headless = false;
}

void Interface::PrintHelp(const std::string &help) {
    os << help << std::endl;
}

void Interface::PrintInfo(const std::string &info) {
    os << info << std::endl;
}

void Interface::PrintCommandName(const std::string &name) {
    os << name << std::endl << "------------" << std::endl;
}

void Interface::PrintCommandExample(const std::string &example) {
    os << "Example: " << std::endl << example << std::endl;
}

void Interface::ClearScreen() {
    os.clear();
}


int Interface::PromptInteger(const std::string &msg,
                             const std::string &msgInvalid,
                             const std::function<bool(const size_t &)> &valid) const {

    int integer;
    while (true) {
        os << formatter->FillPlaceholder({Helper::PrintOrDefault(msg, PROMPT_INTEGER)}) << std::endl;

        if (!(is >> integer) || !valid(integer)) {
            os << formatter->FillPlaceholder({Helper::PrintOrDefault(msgInvalid, INVALID_INPUT)}) << std::endl;
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (isHeadless())
                throw std::runtime_error(FILE_LOADING_ERROR);
            if (is.eof())
                throw std::runtime_error("EOF");
        } else {
            return integer;
        }
    }

}

int Interface::PromptInteger(const std::function<bool(const size_t &)> &valid) const {

    return PromptInteger("", "", valid);
}


void Interface::ProgtestGreetings(const std::string &beautifulError) {
    os << beautifulError << std::endl;
}

std::string Interface::PromptName(const std::function<bool(const std::string &)> &valid) const {
    return PromptBasic("Enter name: ",
                       INVALID_INPUT,
                       [](const std::string &name) { return true; }
    );
}

std::string Interface::PromptBasic(const std::string &msg, const std::string &msgInvalid,
                                   const std::function<bool(const std::string &)> &valid) const {
    std::string word;
    while (true) {
        os << formatter->FillPlaceholder({msg}) << std::endl;

        if (!(is >> word) || !valid(word)) {
            os << formatter->FillPlaceholder({msgInvalid}) << std::endl;
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (isHeadless())
                throw std::runtime_error(FILE_LOADING_ERROR);
            if (is.eof())
                throw std::runtime_error("EOF");
        } else {
            return word;
        }
    }
}


bool Interface::isHeadless() const {
    return this->headless;
}

void Interface::setHeadless(bool val) {
    this->headless = val;
}

bool Interface::End() const {
    return this->is.eof();
}
