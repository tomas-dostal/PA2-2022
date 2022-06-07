/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 19.05.2022
  */


#include <utility>
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
//    draw ellipse <pos_center> <radius_x>, <radius_y>,
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
#include "map"
#include "functional"
#include "any"
#include "Helper.h"
#include "constants.h"
#include "ExportSVG.h"
#include "ExportTspaint.h"
#include "Command.h"

#include "Circle.h"

//    set color <id>;
//    set color <r> <g> <b>;
//
//    set fill <id>;
//    set fill <r> <g> <b>;
//
//    set thickness <int>;

std::vector<std::string> saveFormats = {"svg", "tspaint"};

// source: https://stackoverflow.com/questions/41980888/how-to-convert-from-stdvector-to-args
template<std::size_t... S, typename T>
void unpack_vector(const std::vector<T> &vec, std::index_sequence<S...>) {
    test2(vec[S]...);
}

template<std::size_t size, typename T>
void unpack_vector(const std::vector<T> &vec) {
    if (vec.size() != size) throw /* choose your error */;
    unpack_vector(vec, std::make_index_sequence<size>());
}


Command DrawCommand() {
    return Command{
            COMMAND_DRAW,
            HELP_DRAW,
            [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {

// this would be pretty cool, but requires cpp20 templates in lambda and a lot of template stuff, so maybe later
//                std::vector<std::pair<std::string, std::function<std::any(void)>>> circleBuilder  = {
//                    {"center", [&interface](){ return interface->PromptPos(); }},
//                    {"diameter", [&interface](){ return interface->PromptInteger([](int x){ return x > 0; }); }},
//                    {"color", [&tspaint](){ return tspaint->color.get(); }},
//                    {"fill", [&tspaint](){ return tspaint->fill.get(); }}
//                };

                auto newCircle = [&interface, &tspaint]() {

                    Pos center = std::invoke([&interface]() {
                        return interface->PromptPos(
                                interface->formatter->FillPlaceholder(PROMPT_POSITION_FOR, FormatterParams({"center"}))
                        );
                    });
                    size_t diameter = std::invoke([&interface]() {
                        return interface->PromptInteger(
                                interface->formatter->FillPlaceholder(PROMPT_INTEGER_FOR,
                                                                      FormatterParams({"diameter"})),
                                "",
                                [](int x) { return x > 0; });
                    });
                    std::shared_ptr<Color> color = std::invoke([&tspaint]() { return tspaint->color; });
                    std::shared_ptr<Color> fill = std::invoke([&tspaint]() { return tspaint->fill; });

                    tspaint->AddShape(
                            std::make_shared<Circle>(tspaint->GenerateId(), "Circle", center, diameter, color, fill)
                                    );
                };

                    // todo redo storing
                    tspaint->shapes.emplace_back(std::make_shared<Circle>(circle));
                };

                std::map<std::string, std::function<void(void)>> shapes{
                        {"circle", newCircle},
                };

                std::vector<std::string> setOptionKeys;
                for (const auto &[key, _]: shapes) {
                    setOptionKeys.push_back(key);
                }

                std::string commandName = interface->PromptOption(
                        setOptionKeys, [&setOptionKeys](const std::string &commandName) {
                            return std::find(setOptionKeys.begin(), setOptionKeys.end(), commandName) !=
                                   setOptionKeys.end();
                        }
                );

                return std::any_cast<std::function<void(void)>>(shapes[commandName])();
            }
    };
}

Command ListCommand() {
    return Command{
            COMMAND_LIST,
            HELP_LIST,
            [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {
                return std::invoke([&interface, &tspaint]() {
                    for (const auto &shape: tspaint->GetShapes()) {
                        interface->PrintHelp(
                                interface->formatter->FillPlaceholder(
                                        PRINT_SHAPE,
                                        FormatterParams({
                                                                shape->ShapeId(),
                                                                shape->ShapeName(),
                                                                interface->formatter->FormatColor(shape->ShapeColor()),
                                                                interface->formatter->FormatColor(shape->ShapeFill()),
                                                                //formatter.FormatNamedCoords(shape->ShapeNamedCoords())
                                                        })
                                )
                        );
                    }
                });
            }
    };
}

Command SaveCommand() {
    return Command{
            COMMAND_SAVE,
            HELP_SAVE,
            [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {

                std::string format = interface->PromptOption(saveFormats);
                std::string fileName = interface->PromptBasic("Enter filename: ",
                                                              "Error writing to file",
                                                              [](const std::string &fileName) {
                                                                  std::ofstream file{fileName};
                                                                  if (!file.is_open()) {
                                                                      file.close();
                                                                      return false;
                                                                  }
                                                                  file.close();
                                                                  return true;
                                                              });

                auto svgSave = [&fileName, &tspaint]() {
                    ExportSVG(fileName, tspaint).Export();
                };
                auto tspaintSave = [&fileName, &tspaint]() {
                    ExportTspaint(fileName, tspaint).Export();
                };


                std::map<std::string, std::function<void(void)>> exportOptions{
                        {"svg",     svgSave},
                        {"tspaint", tspaintSave}
                };

                std::vector<std::string> exportOptionKeys;
                for (const auto &[key, _]: exportOptions) {
                    exportOptionKeys.push_back(key);
                }

                std::string commandName = interface->PromptOption(
                        exportOptionKeys, [&exportOptionKeys](const std::string &commandName) {
                            return std::find(exportOptionKeys.begin(), exportOptionKeys.end(), commandName) !=
                                   exportOptionKeys.end();
                        }
                );

                return std::any_cast<std::function<void(void)>>(exportOptions[commandName])();
            }
    };
}


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
                            interface->formatter->FillPlaceholder(SET_ENTER_THICKNESS,
                                                                  FormatterParams{THICKENSS_MIN, THICKENSS_MAX}),
                            INVALID_INPUT,
                            [](const size_t value) {
                                return Helper::_isInRange(value, THICKENSS_MIN, THICKENSS_MAX);
                            });
                };

                std::map<std::string, std::function<void(void)>> setOptions{
                        {"color",     setColor},
                        {"fill",      setFill},
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

Command HelpCommand(const std::shared_ptr<std::vector<Command>> &commands) {
    return Command{
            COMMAND_HELP,
            HELP_HELP,
            [commands](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {

                interface->ClearScreen();
                interface->PrintHelp(TSPAINT_INFO);

                for (const auto &c: *commands) {
                    interface->PrintCommandName(c.Name());
                    interface->PrintHelp(c.Help());
                    interface->PrintCommandExample(c.Example());
                }
                return true;
            }
    };
}

Command QuitCommand(const std::function<void(void)> stopApplication) {
    return Command{
            COMMAND_QUIT,
            HELP_QUIT,
            [stopApplication](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {
                interface->PrintHelp(QUIT_MESSAGE);
                stopApplication();
            }
    };
}

