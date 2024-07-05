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
#include "Star.h"


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
                   [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> it) {

//                this would be pretty cool, but requires cpp20 templates in lambda and a lot of template stuff, so maybe later
//                std::vector<std::pair<std::string, std::function<std::any(void)>>> circleBuilder  = {
//                    {"center", [&it](){ return it->PromptPos(); }},
//                    {"diameter", [&it](){ return it->PromptInteger([](int x){ return x > 0; }); }},
//                    {"color", [&tspaint](){ return tspaint->color.get(); }},
//                    {"fill", [&tspaint](){ return tspaint->fill.get(); }}
//                };

                       auto newCircle = [&it, &tspaint]() {
                           Pos center = it->getPos("center");
                           size_t diameter = it->getPositiveNumber("diameter");
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
                       auto newStar = [&it, &tspaint]() {
                           Pos center = it->getPos("center");
                           size_t diameter = it->getPositiveNumber("diameter");
                           tspaint->AddShape(
                                   std::make_shared<Star>(tspaint->GenerateId(),
                                                          SHAPE_STAR,
                                                          std::make_shared<Pos>(center),
                                                          diameter,
                                                          tspaint->thickness,
                                                          tspaint->color,
                                                          tspaint->fill)
                           );
                       };
                       auto newEllipse = [&it, &tspaint]() {
                           Pos center = it->getPos("center");
                           size_t diameter_x = it->getPositiveNumber("diameter_x");
                           size_t diameter_y = it->getPositiveNumber("diameter_y");

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
                       auto newPolyLine = [&it, &tspaint]() {
                           size_t numberOfPoints = it->getPositiveNumber("Number of points");
                           std::vector<Pos> res = it->getPolyLine(numberOfPoints);
                           tspaint->AddShape(
                                   std::make_shared<PolyLine>(tspaint->GenerateId(),
                                                              SHAPE_POLYLINE,
                                                              res,
                                                              tspaint->thickness,
                                                              tspaint->color,
                                                              tspaint->fill)
                           );
                       };
                       auto newTriangle = [&it, &tspaint]() {
                           std::vector<Pos> res = it->getPolyLine(3);
                           res.push_back(res[0]); // add first point to the end to close the triangle
                           tspaint->AddShape(
                                   std::make_shared<PolyLine>(tspaint->GenerateId(),
                                                              SHAPE_TRIANGLE,
                                                              res,
                                                              tspaint->thickness,
                                                              tspaint->color,
                                                              tspaint->fill)
                           );
                       };
                       auto newLine = [&it, &tspaint]() {
                           Pos start = it->getPos("Start point");
                           Pos end = it->getPos("End point");
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
   

                       auto newRectangle = [&it, &tspaint]() {
                           Pos start = it->getPos("Start point");
                           size_t width = it->getPositiveNumber("Width");
                           size_t height = it->getPositiveNumber("Height");
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
                       auto newSquare = [&it, &tspaint]() {
                           Pos start = it->getPos("Start point");
                           size_t width = it->getPositiveNumber("Width");
                           tspaint->AddShape(
                                   std::make_shared<Rectangle>(tspaint->GenerateId(),
                                                               SHAPE_SQUARE,
                                                               start,
                                                               width,
                                                               width,
                                                               tspaint->thickness,
                                                               tspaint->color,
                                                               tspaint->fill)
                           );
                       };

                       auto helpDraw = [&it]() {
                           it->PrintInfo(EXAMPLE_DRAW_CIRCLE);
                           it->PrintInfo(EXAMPLE_DRAW_ELLIPSE);
                           it->PrintInfo(EXAMPLE_DRAW_LINE);
                           it->PrintInfo(EXAMPLE_DRAW_POLYLINE);
                           it->PrintInfo(EXAMPLE_DRAW_RECTANGLE);
                           it->PrintInfo(EXAMPLE_DRAW_STAR);
                           it->PrintInfo(EXAMPLE_DRAW_TRIANGLE);
                       };

                       std::map<std::string, std::function<void(void)>> shapes{
                               {SHAPE_CIRCLE,    newCircle},
                               {SHAPE_ELLIPSE,   newEllipse},
                               {SHAPE_STAR,      newStar},
                               {SHAPE_LINE,      newLine},
                               {SHAPE_POLYLINE,  newPolyLine},
                               {SHAPE_RECTANGLE, newRectangle},
                               {SHAPE_SQUARE,    newSquare},
                               {SHAPE_TRIANGLE,  newTriangle},
                               {COMMAND_HELP,    helpDraw}
                       };

                       std::vector<std::string> setOptionKeys;
                       for (const auto &[key, _]: shapes) {
                           setOptionKeys.push_back(key);
                       }

                       std::string commandName = it->PromptOption(
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
                   [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> it) {


                       auto groupObjects = [&it, &tspaint]() {
                           size_t groupSize = std::invoke([&it]() {
                               return it->PromptInteger(
                                       it->formatter->FillPlaceholder(PROMPT_INTEGER_FOR,
                                                                      FormatterParams({"Group size"})),
                                       "",
                                       [](int x) { return x > 0 && x <= GROUP_MAX_SIZE; });
                           });
                           std::vector<int> ids = std::invoke([&it, &tspaint, &groupSize]() {
                               return it->PromptMultipleIntegers(
                                       groupSize,
                                       std::vector<std::string>(
                                               {it->formatter->FillPlaceholder(PROMPT_INTEGER_FOR,
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
                               // new IDs are generated inside Tspaint
                               auto shape = tspaint->GetSuperShape(id);
                               ss.emplace_back(shape);
                               tspaint->RemoveSuperShapeFromRootGroup(id);
                           }
                           tspaint->AddGroup(ss);
                       };

                       auto cloneGroup = [&it, &tspaint]() {
                           int id = it->PromptInteger(
                                   it->formatter->FillPlaceholder(PROMPT_INTEGER_FOR,
                                                                  FormatterParams(
                                                                          {"Provide IDs of group to be cloned"})),
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
                           // now we're sure that it's a ShapeGroup, so static pointer cast can be used
                           // otherwise it could lead to an undefined behaviour.
                           auto srcGroup = std::static_pointer_cast<ShapeGroup>(tspaint->GetSuperShape(id));
                           auto dimensions = srcGroup->CalcMaxDimensions();
                           tspaint->currentGroup = tspaint->root;
                           auto clone = srcGroup->Clone([&tspaint]() { return tspaint->GenerateId(); });
                           const auto c = std::static_pointer_cast<ShapeGroup>(clone);
                           auto dstGroup = tspaint->AddExistingGroup(c);
                           dstGroup->MoveRelative((int) dimensions.first, 0);

                           return true;

                       };

                       auto listGroup = [&it, &tspaint]() {
                           it->PrintInfo(PRINTING_GROUP);
                           it->PrintInfo(tspaint->currentGroup->Print(0));
                       };

                       auto helpGroup = [&it]() {
                           it->PrintInfo(EXAMPLE_GROUP_OBJECTS);
                           it->PrintInfo(EXAMPLE_GROUP_CLONE);
                           it->PrintInfo(EXAMPLE_GROUP_LIST);
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

                       std::string commandName = it->PromptOption(
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
                   [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> it) {
                       return std::invoke([&it, &tspaint]() {
                           it->PrintInfo(tspaint->Print());
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
                      [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> it) {

                          // Following lambdas use different openmodes which are specified in
                          // each instance of Export's children. To achieve some easy functionality
                          // for getting file to Exporter child instance AND to be able to get
                          // set file mode there I created following approach to pass a lambda
                          // which prompts the user and creates a filestream, so in the end it's called
                          // inside of Exporter child instance.
                          auto getFile = [&it](std::ios_base::openmode mode) {
                              return it->PromptFile("Select output file: ",
                                                    mode);
                          };
                          // pre-define all possible save lambdas

                          // all i/o errors are handled inside of Export* class, returns false on error
                          auto svgSave = [&getFile, &tspaint]() {
                              auto exporter = ExportSVG(getFile);
                              auto maxDim = tspaint->MaxDimensions();
                              exporter.Start(maxDim.first, maxDim.second);
                              tspaint->root->Draw(exporter);
                              return exporter.End();
                          };
                          // all i/o errors are handled inside of Export* class, returns false on error
                          auto bmpSave = [&getFile, &tspaint]() {
                              auto exporter = ExportBMP(getFile);
                              auto maxDim = tspaint->MaxDimensions();
                              exporter.SetBackground(tspaint->background);
                              exporter.Start(maxDim.first, maxDim.second);
                              tspaint->root->Draw(exporter);
                              return exporter.End();
                          };
                          auto tspaintSave = [&getFile, &tspaint]() {
                              ExportTspaint(getFile).Start(tspaint->root->Width(), tspaint->root->Height());
                              return false;
                          };
                          auto helpSave = [&it]() {
                              it->PrintInfo(EXAMPLE_SAVE);
                              return true;
                          };

                          std::map<std::string, std::function<void(void)>> exportOptions{
                                  {"svg",     svgSave},
                                  {"bmp",     bmpSave},
                                  {"help",    helpSave}
                          };
                          std::vector<std::string> exportOptionKeys;
                          for (const auto &[key, _]: exportOptions) {
                              exportOptionKeys.push_back(key);
                          }

                          std::string optionName = it->PromptOption(
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
                      [loadFn](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> it) {
                          std::shared_ptr<std::fstream> fileIn = it->PromptFile("Enter filename: ",
                                                                                OPEN_FILE_READ_STR);
                          std::stringstream ss;
                          // this is probably not a good idea
                          auto fileit = std::make_shared<Interface>(*fileIn, ss);
                          fileit->setHeadless(true);
                          loadFn(it, fileit, tspaint);
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
                   [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> it) {

                       // inspired by https://stackoverflow.com/questions/61969316/is-it-possible-to-put-lambda-expressions-into-a-map-or-list-in-c

                       auto setColor = [&it, &tspaint]() {
                           tspaint->color = it->PromptColor(tspaint->colorPalette);
                       };
                       auto setFill = [&it, &tspaint]() {
                           tspaint->fill = it->PromptColor(tspaint->colorPalette);
                       };
                       auto setThickness = [&it, &tspaint]() {
                           tspaint->thickness = (size_t) it->PromptInteger(
                                   it->formatter->FillPlaceholder(SET_ENTER_THICKNESS,
                                                                  FormatterParams{THICKNESS_MIN, THICKNESS_MAX}),
                                   INVALID_INPUT,
                                   [](const size_t value) {
                                       return Helper::_isInRange(value, THICKNESS_MIN, THICKNESS_MAX);
                                   });
                       };
                       auto setGroup = [&it, &tspaint]() {
                           int id = it->PromptInteger(
                                   it->formatter->FillPlaceholder(SET_ENTER_GROUP_ID,
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
                           // already know that's an instance of ShapeGroup, so I can use static_pointer_cast.
                           std::shared_ptr<ShapeGroup> ptr = std::static_pointer_cast<ShapeGroup>(
                                   tspaint->GetSuperShape(id));
                           tspaint->currentGroup = ptr;

                       };


                       auto helpSet = [&it]() {
                           it->PrintInfo(EXAMPLE_SET_COLOR);
                           it->PrintInfo(EXAMPLE_SET_FILL);
                           it->PrintInfo(EXAMPLE_SET_THICKNESS);
                           it->PrintInfo(EXAMPLE_SET_GROUP);
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

                       std::string commandName = it->PromptOption(
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
                      [commands](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> it) {

                          it->ClearScreen();
                          it->PrintHelp(TSPAINT_INFO);

                          for (const auto &c: *commands) {
                              it->PrintCommandName(c.Name());
                              it->PrintHelp(c.Help());
                              it->PrintCommandExample(c.Example());
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
                      [stopApplication](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> it) {
                          it->PrintHelp(QUIT_MESSAGE);
                          stopApplication();
                      }
    };
}

