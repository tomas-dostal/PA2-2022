/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 19.05.2022
  */

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

#include "map"
#include "any"
#include "memory"
#include "utility"
#include "functional"

#include "Helper.h"
#include "CommandImpl.h"
#include "messages.h"
#include "constants.h"
#include "ExportSVG.h"
#include "ExportTspaint.h"
#include "Command.h"
#include "SysCommand.h"
#include "Circle.h"
#include "Line.h"


/**
 * DrawCommand 'draw' generates shapes/groups based on the user's input and stores them in the tspaint.
 * It uses predefined color/fill/thickness/etc which can be modified by "set"command.
 *
 * @example draw {circle, ellipse, line, polyline} <coordinates...>
 * @example draw circle <center_x> <center_y> <diameter>
 *
 * @return implementation of 'draw' command
 */
Command DrawCommand() {
    return Command{COMMAND_DRAW, HELP_DRAW, true,
                   [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {

//                this would be pretty cool, but requires cpp20 templates in lambda and a lot of template stuff, so maybe later
//                std::vector<std::pair<std::string, std::function<std::any(void)>>> circleBuilder  = {
//                    {"center", [&interface](){ return interface->PromptPos(); }},
//                    {"diameter", [&interface](){ return interface->PromptInteger([](int x){ return x > 0; }); }},
//                    {"color", [&tspaint](){ return tspaint->color.get(); }},
//                    {"fill", [&tspaint](){ return tspaint->fill.get(); }}
//                };

                       auto newCircle = [&interface, &tspaint]() {

                           Pos center = std::invoke([&interface]() {
                               return interface->PromptPos(
                                       interface->formatter->FillPlaceholder(PROMPT_POSITION_FOR,
                                                                             FormatterParams({"center"}))
                               );
                           });
                           size_t diameter = std::invoke([&interface]() {
                               return interface->PromptInteger(
                                       interface->formatter->FillPlaceholder(PROMPT_INTEGER_FOR,
                                                                             FormatterParams({"diameter"})),
                                       "",
                                       [](int x) { return x > 0; });
                           });

                           tspaint->AddShape(
                                   std::make_shared<Circle>(tspaint->GenerateId(),
                                                            "Circle",
                                                            center,
                                                            diameter,
                                                            tspaint->thickness,
                                                            tspaint->color,
                                                            tspaint->fill)
                           );
                       };
                       auto newLine = [&interface, &tspaint]() {

                           Pos start = std::invoke([&interface]() {
                               return interface->PromptPos(
                                       interface->formatter->FillPlaceholder(PROMPT_POSITION_FOR,
                                                                             FormatterParams({"Start point"}))
                               );
                           });
                           Pos end = std::invoke([&interface]() {
                               return interface->PromptPos(
                                       interface->formatter->FillPlaceholder(PROMPT_POSITION_FOR,
                                                                             FormatterParams({"End point"}))
                               );
                           });

                           tspaint->AddShape(
                                   std::make_shared<Line>(tspaint->GenerateId(),
                                                          "line",
                                                          start,
                                                          end,
                                                          tspaint->thickness,
                                                          tspaint->color,
                                                          tspaint->fill)
                           );
                       };


                       std::map<std::string, std::function<void(void)>> shapes{
                               {"circle", newCircle},
                               {"line",   newLine},
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

/**
 * ListCommand - 'list' all created shapes with colors, thickness, positions, etc.
 * Output format is not matching tspaint specification.
 *
 * @return Implementation of ListCommand
 */
Command ListCommand() {
    return Command{COMMAND_LIST, HELP_LIST, true,
                   [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {
                       return std::invoke([&interface, &tspaint]() {
                           for (const auto &shape: tspaint->GetShapes()) {
                               interface->PrintHelp(
                                       interface->formatter->FillPlaceholder(
                                               PRINT_SHAPE,
                                               FormatterParams({
                                                                       shape->ShapeId(),
                                                                       shape->ShapeName(),
                                                                       interface->formatter->FormatColor(
                                                                               shape->ShapeColor()),
                                                                       interface->formatter->FormatColor(
                                                                               shape->ShapeFill()),
                                                                       //formatter.FormatNamedCoords(shape->ShapeNamedCoords())
                                                               })
                                       )
                               );
                           }
                       });
                   }
    };
}

/**
 * SaveCommand 'save' is used to save/export tspaint to a file.
 * @example save {svg, tspaint} <filename>
 * @return save command implementation
 */
SysCommand SaveCommand() {
    return SysCommand{COMMAND_SAVE, HELP_SAVE,
                      [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {

                          std::string format = interface->PromptOption({"svg", "tspaint"});
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

/**
 * LoadCommand 'load' - load instructions for tspaint from file.
 * Instructions are same as for an interactive command line, aka matching tspaint standard.
 *
 * @param loadFn Application->Load() lambda
 * @return LoadCommand implementation
 */
SysCommand
LoadCommand(const std::function<void(std::shared_ptr<Interface>, std::shared_ptr<Tspaint> targetTspaint)> loadFn) {
    return SysCommand{COMMAND_LOAD, HELP_LOAD,
                      [loadFn](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {

                          std::string fileName = interface->PromptBasic("Enter filename: ",
                                                                        "Error writing to file",
                                                                        [](const std::string &fileName) {
                                                                            std::ifstream file{fileName};
                                                                            if (!file.is_open()) {
                                                                                file.close();
                                                                                return false;
                                                                            }
                                                                            file.close();
                                                                            return true;
                                                                        });
                          std::ifstream fileIn{fileName};
                          std::stringstream ss;
                          auto fileInterface = std::make_shared<Interface>(fileIn, ss);
                          fileInterface->setHeadless(true);

                          loadFn(fileInterface, tspaint);
                      }
    };
}

/**
 * SetCommand is a modifier of tspaint options. It is similar to mspaint when you are selecting color and then
 * applying it to the shape you want to draw.
 *
 * @example set color id <id>
 * @example set color rgb <r> <g> <b>
 * @example set fill id <id>
 * @example set fill rgb <r> <g> <b>
 * @example set thickness <int>
 * @return set command implementation
 */
Command SetCommand() {
    return Command{COMMAND_SET, HELP_SET, true,
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

/**
 * Help
 * @param commands vector of commands
 * @return SysCommand implementation of command "help"
 */
SysCommand HelpCommand(const std::shared_ptr<std::vector<Command>> &commands) {
    return SysCommand{COMMAND_HELP, HELP_HELP,
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

/**
 * Quits the application
 *
 * @param stopApplication Lambda which modifies Application's field isRunning, so in next iteration the
 * "enter command" loop is ended, thus the application ends.
 *
 * @return QuitCommand implementation.
 */
SysCommand QuitCommand(const std::function<void(void)> stopApplication) {
    return SysCommand{COMMAND_QUIT, HELP_QUIT,
                      [stopApplication](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {
                          interface->PrintHelp(QUIT_MESSAGE);
                          stopApplication();
                      }
    };
}

