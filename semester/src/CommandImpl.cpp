/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 19.05.2022
  */


#include "messages.h"
//*    set color <id>;
//    set color <r> <g> <b>;
//
//    set fill <id>;
//    set fill <r> <g> <b>;
//
//    set thickness <int>;
//
//    draw line <pos_start> <pos_end>
//    draw polyline <pos_start> [<pos_i>...]
//
//    draw circle <pos_center> <diameter>
//    draw elipsis todo
//
//    draw rectangle <pos_left_bottom>  <pos_right_top>
//
//    draw square <pos_left_bottom> <pos_right_top>
//
//    draw pa2 <pos_left_bottom> <pos_right_top>
//
//    draw group <group_id> <pos_left_bottom>
//
//    hide shape <id>
//    hide group <id>
//
//    delete group <id>; // force delete group, so it will stop exist
//
//    new group <name> <id> [id...];
//
//    show all // get all ids of objects including their type
//    show <id>

#include "CommandImpl.h"
#include "messages.h"
#include "map"
#include "functional"
#include "any"
#include "Helper.h"
#include "constants.h"


//    set color <id>;
//    set color <r> <g> <b>;
//
//    set fill <id>;
//    set fill <r> <g> <b>;
//
//    set thickness <int>;

std::vector<std::string> setOptions = {"color", "background"};

Command SetCommand() {
    return Command{
            COMMAND_SET,
            HELP_SET,
            [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {

                // inspired by https://stackoverflow.com/questions/61969316/is-it-possible-to-put-lambda-expressions-into-a-map-or-list-in-c

                auto setColor = [&interface, &tspaint]() {
                    tspaint->color = interface->PromptColor(tspaint->colorPalette);
                };
                auto setFill = [&interface, &tspaint]() {
                    tspaint->fill = interface->PromptColor(tspaint->colorPalette);
                };
                auto setThickness = [&interface, &tspaint]() {
                    tspaint->thickness = (size_t) interface->PromptInteger(
                            interface->formatter->FillPlaceholder(SET_ENTER_THICKNESS, FormatterParams{THICKENSS_MIN, THICKENSS_MAX}),
                            INVALID_INPUT,
                            [](const size_t value){
                                return Helper::_isInRange(value, THICKENSS_MIN, THICKENSS_MAX);
                            });
                };

                std::map<std::string, std::function<void(void)>> setOptions{
                        {"color", setColor},
                        {"fill", setFill},
                        {"thickness", setThickness}
                };

                std::vector<std::string> setOptionKeys;
                for (const auto &[key, _]: setOptions) {
                    setOptionKeys.push_back(key);
                }

                std::string commandName = interface->PromptOption(
                        setOptionKeys, [&setOptionKeys](const std::string &commandName) {
                            return std::find(setOptionKeys.begin(), setOptionKeys.end(), commandName) !=
                                   setOptionKeys.end();
                        }
                );

                std::any_cast<std::function<void(void)>>(setOptions[commandName])();

                return true;
            }
    };
}

Command HelpCommand(const std::shared_ptr<std::vector<Command>> commands) {
    return Command{
            COMMAND_HELP,
            HELP_HELP,
            [commands](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {

                interface->ClearScreen();
                interface->PrintHelp(TSPAINT_INFO);
                std::cerr << "Commands are " << commands.get()->size();
                for (const auto &c: *commands) {
                    //if ( c.second.IsActive( game ) )
                    std::cerr << c.Name() << " " << c.Help() << std::endl;
                    interface->PrintHelp(c.Help());
                }
                return true;
            }
    };
}

Command QuitCommand() {
    return Command{
            COMMAND_QUIT,
            HELP_QUIT,
            [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {
                std::cout << "hello" << std::endl;
                return false;
            }
    };
}

