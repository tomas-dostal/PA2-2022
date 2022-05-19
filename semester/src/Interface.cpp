/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include <sstream>
#include "Interface.h"
#include "Color.h"
#include "Helper.h"
#include "ColorPalett.h"
#include "Pos.h"
#include "messages.h"
#include "FormatterParams.h"


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


std::shared_ptr<Color> Interface::PromptColor() const {

    this->os << "Enter color <r> <g> <b> <name>  or <id>" << std::to_string(ColorPalett::colors.size() - 1)
             << "] to choose from list: " << std::endl;
    int i = 0;
    for (auto const &[key, value]: ColorPalett::colors) {
        this->os << i << ")" << key << std::endl;
    }

    std::string input;
    std::getline(is, input);

    std::stringstream ss(input);

    int a, b, c;
    std::string name;

    if (Helper::_getIntFromStringStream(ss, a)) {
        // color pick
        if (!Helper::_getIntFromStringStream(ss, b)) {
        } else if (Helper::_getIntFromStringStream(ss, c)) {
            ss >> name;
            if (Helper::_isInRange(a, 0, 255) && Helper::_isInRange(b, 0, 255) && Helper::_isInRange(c, 0, 255)) {
                auto color = std::make_shared<Color>(Color(a, b, c));
                ColorPalett::addIfNotExists(name, color);
                return color;
            } else {
                os << "Unable to create color, acceptable range (0-255) not matching r: " << a << ", g: " << b
                   << ", b: " << c << std::endl;
                return PromptColor();
            }

        }
    }

    os << "Input format incorrect / No input detected" << std::endl;
    return PromptColor();
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
        os << fomatter.FillPlaceholder(PROMPT_COMMAND) << std::endl;

        if (!(is >> command)) {
            os << fomatter.FillPlaceholder(INVALID_INPUT) << std::endl;
        } else if (!valid(command)) {
            std::string tmp = COMMAND_HELP;
            os << fomatter.FillPlaceholder(UNKNOWN_COMMAND, FormatterParams({command, tmp})) << std::endl;
        }
    } else {
        return command;
    }

    ClearLine();
}

std::string Interface::PromptCommandOption(const std::function<size_t(const std::string &)> &valid) const {
    return "color";
}

Interface::Interface(std::istream &is, std::ostream &os) : is(is), os(os) {
    this->formatter = Formatter();


}
