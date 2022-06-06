/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 19.05.2022
  * @basedon https://gitlab.fit.cvut.cz/bernhdav/pa2-minesweeper/tree/master
  * @basedon https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/tree/1.1.0
  */

#pragma once

const char *const COMMAND_HELP = "help";
const char *const COMMAND_QUIT = "quit";

const char *const COMMAND_SET = "set";
const char *const COMMAND_DRAW = "draw";
const char *const COMMAND_SAVE = "save";
const char *const COMMAND_LOAD = "load";
const char *const COMMAND_HIDE = "hide";
const char *const COMMAND_SHOW = "show";
const char *const COMMAND_NEW = "new";
const char *const COMMAND_DELETE = "delete";
const char *const COMMAND_LIST = "list";


const char *const SHAPE_LINE = "line";
const char *const SHAPE_POLYLINE = "polyline";
const char *const SHAPE_RECTANGLE = "rectangle";
const char *const SHAPE_SQUARE = "square";
const char *const SHAPE_CIRCLE = "circle";
const char *const SHAPE_ELIPSYS = "elipsys";


const char *const PROMPT_COMMAND = "Enter a command: ";
const char *const PROMPT_INTEGER = "Enter a positive number: ";
const char *const PROMPT_INTEGER_FOR = "$: Enter a positive number: ";
const char *const PROMPT_POSITION = "Enter a position x y: ";
const char *const PROMPT_POSITION_FOR = "$: Enter a position x y: ";
const char *const NAMED_COORDS = "$: $";
const char *const COORDS = "$, $ ";
const char *const COLOR = "$ (r: $, g: $, b: $)";
const char *const UNKNOWN_COLOR_NAME = "Unknown color";

const char *const BUILDING_SHAPE = "Building $: ";

const char *const PROMPT_OPTION = "Enter an option: ";
const char *const ENTER_VALUE_IN_RANGE = "Enter value in range [$-$]";
const char *const SET_ENTER_THICKNESS = "Enter value for thickness [$-$]";
const char *const SET_ENTER_COLOR_RGB = "Entering color by rgb: <$> ";
const char *const SET_ENTER_COLOR_RGB_INVALID = "Entered color part is invalid ";
const char *const SET_ENTER_COLOR_RGB_NAME = "Enter name: ";
const char *const SET_ENTER_COLOR_ID = "Enter color <id> \noptions: \n$";
const char *const SET_ENTER_COLOR_ID_INVALID = "Entered color id is invalid";

const char *const PRINT_SHAPE = "id: $, name: $, color: $, fill: $, pos: $, detail: $ ";
const char *const INVALID_INPUT = "Invalid input";
const char *const UNKNOWN_COMMAND = "Unknown command '$'. For help type '$'";
const char *const UNKNOWN_OPTION = "Unknown option '$'. For help type '$'";
const char *const ERROR_FILE_IO = "Unable to read/write file '$'";

const char *const AVAILABLE_OPTION = "Options available: $";

const char *const HELP_HELP = "Prints this help";
const char *const HELP_QUIT = "Ends this pain";

const char *const HELP_SAVE = "Saves output of this pain to file";

const char *const HELP_SET = "HELP_SET";
const char *const HELP_DRAW = "HELP_DRAW";
const char *const HELP_LOAD = "HELP_LOAD";
const char *const HELP_HIDE = "HELP_HIDE";
const char *const HELP_SHOW = "HELP_SHOW";
const char *const HELP_NEW = "HELP_NEW";
const char *const HELP_DELETE = "HELP_DELETE";
const char *const HELP_LIST = "List all objects in tspaint";
const char *const TSPAINT_INFO = "ThisIsPain.T\n-----------------------------------------------\nSimple drawing tool for experienced FIT students.\n";

const char *const PROGTEST_ERROR_LOADING = "Error in basic compilation - source file not accessible [Access help (934 B)] (2 hits available, 4 with penalisation -10%";
const char *const QUIT_MESSAGE = "Error in basic logic. On behalf of This Is Pain(t), LTD, we would like to thank you for using our services and wish you a nice day. ";


