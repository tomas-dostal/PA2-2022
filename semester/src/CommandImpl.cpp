/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 19.05.2022
  */


#include "map"
#include "any"
#include "memory"
#include "utility"
#include "functional"

#include "Helper.h"
#include "CommandImpl.h"
#include "messages.h"
#include "constants.h"
#include "Command.h"
#include "SysCommand.h"
#include "Circle.h"
#include "Line.h"
#include "Rectangle.h"
#include "PolyLine.h"
#include "Ellipse.h"
#include "ExportBMP.h"
#include "ExportSVG.h"
#include "ExportTspaint.h"


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
    return Command{COMMAND_DRAW, HELP_DRAW, EXAMPLE_DRAW, true,
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
                                                            SHAPE_CIRCLE,
                                                            std::make_shared<Pos>(center),
                                                            diameter,
                                                            tspaint->thickness,
                                                            tspaint->color,
                                                            tspaint->fill)
                           );
                       };
                       auto newEllipse = [&interface, &tspaint]() {

                           Pos center = std::invoke([&interface]() {
                               return interface->PromptPos(
                                       interface->formatter->FillPlaceholder(PROMPT_POSITION_FOR,
                                                                             FormatterParams({"center"}))
                               );
                           });
                           size_t diameter_x = std::invoke([&interface]() {
                               return interface->PromptInteger(
                                       interface->formatter->FillPlaceholder(PROMPT_INTEGER_FOR,
                                                                             FormatterParams({"diameter_x"})),
                                       "",
                                       [](int x) { return x > 0; });
                           });

                           size_t diameter_y = std::invoke([&interface]() {
                               return interface->PromptInteger(
                                       interface->formatter->FillPlaceholder(PROMPT_INTEGER_FOR,
                                                                             FormatterParams({"diameter_y"})),
                                       "",
                                       [](int x) { return x > 0; });
                           });

                           tspaint->AddShape(
                                   std::make_shared<Ellipse>(tspaint->GenerateId(),
                                                             SHAPE_ELLIPSE,
                                                             std::make_shared<Pos>(center),
                                                             diameter_x,
                                                             diameter_y,
                                                             tspaint->thickness,
                                                             tspaint->color,
                                                             tspaint->fill)
                           );
                       };
                       auto newPolyLine = [&interface, &tspaint]() {
                           size_t numberOfPoints = std::invoke([&interface]() {
                               return interface->PromptInteger(
                                       interface->formatter->FillPlaceholder(PROMPT_INTEGER_FOR,
                                                                             FormatterParams({"Number of points"})),
                                       "",
                                       [](int x) { return x > 0; });
                           });
                           std::vector<Pos> res;
                           for (size_t i = 0; i < numberOfPoints; i++) {
                               res.push_back(std::invoke([&interface, &i, &numberOfPoints]() {
                                   return interface->PromptPos(
                                           interface->formatter->FillPlaceholder(PROMPT_POSITION_FOR,
                                                                                 FormatterParams({"Point" +
                                                                                                  std::to_string(
                                                                                                          i + 1) +
                                                                                                  "/ " + std::to_string(
                                                                                         numberOfPoints)}))
                                   );
                               }));
                           }
                           tspaint->AddShape(
                                   std::make_shared<PolyLine>(tspaint->GenerateId(),
                                                              SHAPE_POLYLINE,
                                                              res,
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
                                                          SHAPE_LINE,
                                                          start,
                                                          end,
                                                          tspaint->thickness,
                                                          tspaint->color,
                                                          tspaint->fill)
                           );
                       };
                       auto newRectangle = [&interface, &tspaint]() {

                           Pos start = std::invoke([&interface]() {
                               return interface->PromptPos(
                                       interface->formatter->FillPlaceholder(PROMPT_POSITION_FOR,
                                                                             FormatterParams({"Start point"}))
                               );
                           });
                           size_t width = std::invoke([&interface]() {
                               return interface->PromptInteger(
                                       interface->formatter->FillPlaceholder(PROMPT_INTEGER_FOR,
                                                                             FormatterParams({"Width"})),
                                       "",
                                       [](int x) { return x > 0; });
                           });
                           size_t height = std::invoke([&interface]() {
                               return interface->PromptInteger(
                                       interface->formatter->FillPlaceholder(PROMPT_INTEGER_FOR,
                                                                             FormatterParams({"Height"})),
                                       "",
                                       [](int x) { return x > 0; });
                           });

                           tspaint->AddShape(
                                   std::make_shared<Rectangle>(tspaint->GenerateId(),
                                                               SHAPE_RECTANGLE,
                                                               start,
                                                               width,
                                                               height,
                                                               tspaint->thickness,
                                                               tspaint->color,
                                                               tspaint->fill)
                           );
                       };

                       auto helpDraw = [&interface]() {
                           interface->PrintInfo(EXAMPLE_DRAW_CIRCLE);
                           interface->PrintInfo(EXAMPLE_DRAW_ELLIPSE);
                           interface->PrintInfo(EXAMPLE_DRAW_LINE);
                           interface->PrintInfo(EXAMPLE_DRAW_POLYLINE);
                           interface->PrintInfo(EXAMPLE_DRAW_RECTANGLE);
                       };

                       std::map<std::string, std::function<void(void)>> shapes{
                               {"circle",    newCircle},
                               {"ellipse",   newEllipse},
                               {"line",      newLine},
                               {"polyline",  newPolyLine},
                               {"rectangle", newRectangle},
                               {"help",      helpDraw}
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

Command GroupCommand() {
    return Command{COMMAND_GROUP, HELP_GROUP, EXAMPLE_HELP, true,
                   [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {


                       auto groupObjects = [&interface, &tspaint]() {
                           size_t groupSize = std::invoke([&interface]() {
                               return interface->PromptInteger(
                                       interface->formatter->FillPlaceholder(PROMPT_INTEGER_FOR,
                                                                             FormatterParams({"Group size"})),
                                       "",
                                       [](int x) { return x > 0 && x <= GROUP_MAX_SIZE; });
                           });
                           std::vector<int> ids = std::invoke([&interface, &tspaint, &groupSize]() {
                               return interface->PromptMultipleIntegers(
                                       groupSize,
                                       std::vector<std::string>(
                                               {interface->formatter->FillPlaceholder(PROMPT_INTEGER_FOR,
                                                                                      FormatterParams(
                                                                                              {"Provide IDs of objects to be added to the group"}))}),
                                       std::vector<std::string>({"ID is not valid. "}),
                                       std::vector<std::function<bool(const int &)>>({[&tspaint](int index) {
                                           if (index >= 0)
                                               return tspaint->IsValidIndex(index);
                                           return false;
                                       }})
                               );
                           });
                           std::vector<std::shared_ptr<SuperShape>> ss;
                           for (int id: ids) {
                               // new IDs are generated inside of Tspaint
                               auto shape = tspaint->GetSuperShape(id);
                               ss.emplace_back(shape);
                               tspaint->RemoveSuperShapeFromRootGroup(id);
                           }
                           tspaint->AddGroup(ss);
                       };


                       auto cloneGroup = [&interface, &tspaint]() {
                           int id = interface->PromptInteger(
                                   interface->formatter->FillPlaceholder(PROMPT_INTEGER_FOR,
                                                                         FormatterParams(
                                                                                 {"Provide IDs of group to be clonned"})),
                                   INVALID_ID,
                                   [&tspaint](int index) {
                                       if (index >= 0) {
                                           auto ptr = std::dynamic_pointer_cast<ShapeGroup>(
                                                   tspaint->GetSuperShape(index));
                                           return ptr != nullptr;
                                       }
                                       return false;
                                   }
                           );

                           auto srcGroup = std::dynamic_pointer_cast<ShapeGroup>(tspaint->GetSuperShape(id));
                           auto dimensions = srcGroup->CalcMaxDimensions();
                           tspaint->currentGroup = tspaint->root;
                           auto clone = srcGroup->Clone([tspaint]() { return tspaint->GenerateId(); });
                           auto dstGroup = tspaint->AddExistingGroup(std::dynamic_pointer_cast<ShapeGroup>(clone));
                           dstGroup->MoveRelative((int) dimensions.first, 0);

                           return true;

                       };

                       auto listGroup = [&interface, &tspaint]() {
                           interface->PrintInfo(PRINTING_GROUP);
                           interface->PrintInfo(tspaint->currentGroup->Print(0));
                       };

                       auto helpGroup = [&interface]() {
                           interface->PrintInfo(EXAMPLE_GROUP_OBJECTS);
                           interface->PrintInfo(EXAMPLE_GROUP_CLONE);
                           interface->PrintInfo(EXAMPLE_GROUP_LIST);
                       };

                       std::map<std::string, std::function<void(void)>> shapes{
                               {"objects", groupObjects},
                               {"clone",   cloneGroup},
                               {"list",    listGroup},
                               {"help",    helpGroup}
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
    return Command{COMMAND_LIST, HELP_LIST, EXAMPLE_LIST, true,
                   [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {
                       return std::invoke([&interface, &tspaint]() {
                           interface->PrintInfo(tspaint->Print());
                       });
                   }
    };
}

/**
 * SaveCommand 'save' is used to save/export tspaint to a file.
 * @example save {svg, bmp} <filename>
 * @return save command implementation
 */
SysCommand SaveCommand() {
    return SysCommand{COMMAND_SAVE, HELP_SAVE, EXAMPLE_SAVE,
                      [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {

                          // Following lambdas use different openmodes which are specified in
                          // each instance of Export's children. To achieve some easy functionality
                          // for getting file to Exporter child instance AND to be able to get
                          // set file mode there I created following approach to pass a lambda
                          // which prompts the user and creates a filestream, so in the end it's called
                          // inside of Exporter child instance.
                          auto getFile = [&interface](std::ios_base::openmode mode) {
                              return interface->PromptFile("Select output file: ",
                                                           mode);
                          };
                          // pre-define all possible save lambdas

                          // all i/o errors are handled inside of Export* class, throws exception on error
                          auto svgSave = [&getFile, &tspaint]() {
                              auto exporter = ExportSVG(getFile);
                              auto maxDim = tspaint->MaxDimensions();
                              exporter.Start(maxDim.first, maxDim.second);
                              tspaint->root->Draw(exporter);
                              exporter.End();
                          };
                          // all i/o errors are handled inside of Export* class, throws exception on error
                          auto bmpSave = [&getFile, &tspaint]() {
                              auto exporter = ExportBMP(getFile);
                              auto maxDim = tspaint->MaxDimensions();
                              exporter.SetBackground(tspaint->background);
                              exporter.Start(maxDim.first, maxDim.second);
                              tspaint->root->Draw(exporter);
                              exporter.End();

                          };
                          auto tspaintSave = [&getFile, &tspaint]() {
                              ExportTspaint(getFile).Start(tspaint->root->Width(), tspaint->root->Height());
                          };
                          auto helpSave = [&interface]() {
                              interface->PrintInfo(EXAMPLE_SAVE);
                          };

                          std::map<std::string, std::function<void(void)>> exportOptions{
                                  {"svg",     svgSave},
                                  {"bmp",     bmpSave},
                                  {"tspaint", tspaintSave},
                                  {"help",    helpSave}
                          };
                          std::vector<std::string> exportOptionKeys;
                          for (const auto &[key, _]: exportOptions) {
                              exportOptionKeys.push_back(key);
                          }

                          std::string optionName = interface->PromptOption(
                                  exportOptionKeys, [&exportOptionKeys](const std::string &commandName) {
                                      return std::find(exportOptionKeys.begin(), exportOptionKeys.end(),
                                                       commandName) !=
                                             exportOptionKeys.end();
                                  }
                          );

                          return std::any_cast<std::function<void(void)>>(exportOptions[optionName])();
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
LoadCommand(const std::function<void(std::shared_ptr<Interface>, std::shared_ptr<Interface>,
                                     std::shared_ptr<Tspaint> &targetTspaint)> loadFn) {
    return SysCommand{COMMAND_LOAD, HELP_LOAD, EXAMPLE_LOAD,
                      [loadFn](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {
                          std::shared_ptr<std::fstream> fileIn = interface->PromptFile("Enter filename: ",
                                                                                       OPEN_FILE_READ_STR);
                          std::stringstream ss;
                          // this is probably not a good idea
                          auto fileInterface = std::make_shared<Interface>(*fileIn, ss);
                          fileInterface->setHeadless(true);
                          loadFn(interface, fileInterface, tspaint);
                      }
    };
}

// todo status command showing tspaint config

/**
 * SetCommand is a modifier of tspaint options. It is similar to mspaint when you are selecting color and then
 * applying it to the shape you want to draw.
 *
 * @example set color id <id>
 * @example set color rgb <r> <g> <b> <name>
 * @example set color byname <name>
 * @example set fill id <id>
 * @example set fill rgb <r> <g> <b>
 * @example set thickness <int>
 * @return set command implementation
 */
Command SetCommand() {
    return Command{COMMAND_SET, HELP_SET, EXAMPLE_SET, true,
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
                                                                         FormatterParams{THICKNESS_MIN, THICKNESS_MAX}),
                                   INVALID_INPUT,
                                   [](const size_t value) {
                                       return Helper::_isInRange(value, THICKNESS_MIN, THICKNESS_MAX);
                                   });
                       };
                       auto setGroup = [&interface, &tspaint]() {
                           int id = interface->PromptInteger(
                                   interface->formatter->FillPlaceholder(SET_ENTER_GROUP_ID,
                                                                         FormatterParams{}),
                                   SET_ENTER_GROUP_ID_INVALID,
                                   [&tspaint](const int value) {
                                       if (tspaint->IsValidIndex(value)) {
                                           std::shared_ptr<ShapeGroup> ptr = std::dynamic_pointer_cast<ShapeGroup>(
                                                   tspaint->GetSuperShape(value));
                                           if (ptr)
                                               return true;
                                       }
                                       return false;
                                   });
                           std::shared_ptr<ShapeGroup> ptr = std::dynamic_pointer_cast<ShapeGroup>(
                                   tspaint->GetSuperShape(id));
                           tspaint->currentGroup = ptr;

                       };


                       auto helpSet = [&interface]() {
                           interface->PrintInfo(EXAMPLE_SET_COLOR);
                           interface->PrintInfo(EXAMPLE_SET_FILL);
                           interface->PrintInfo(EXAMPLE_SET_THICKNESS);
                           interface->PrintInfo(EXAMPLE_SET_GROUP);
                           interface->PrintInfo(EXAMPLE_DRAW_RECTANGLE);
                       };

                       std::map<std::string, std::function<void(void)>> setOptions{
                               {"color",     setColor},
                               {"fill",      setFill},
                               {"thickness", setThickness},
                               {"group",     setGroup},
                               {"help",      helpSet}
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
    return SysCommand{COMMAND_HELP, HELP_HELP, EXAMPLE_HELP,
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
    return SysCommand{COMMAND_QUIT, HELP_QUIT, EXAMPLE_QUIT,
                      [stopApplication](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {
                          interface->PrintHelp(QUIT_MESSAGE);
                          stopApplication();
                      }
    };
}

