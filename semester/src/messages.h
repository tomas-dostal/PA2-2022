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
const char *const COMMAND_GROUP = "group";


const char *const SHAPE_LINE = "line";
const char *const SHAPE_POLYLINE = "polyline";
const char *const SHAPE_RECTANGLE = "rectangle";
const char *const SHAPE_TRIANGLE = "triangle";
const char *const SHAPE_SQUARE = "square";
const char *const SHAPE_CIRCLE = "circle";
const char *const SHAPE_ELLIPSE = "ellipse";
const char *const SHAPE_STAR = "star";

const char *const SHAPE_GROUP_BEGIN = "groupBegin";
const char *const SHAPE_GROUP_END = "groupEnd";


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
const char *const END_OF_INPUT_REACHED = "Reached end of input";
const char *const IMPORT_SUCCESSFUL = "Import successful";

const char *const PROMPT_OPTION = "Enter an option: ";
const char *const ENTER_VALUE_IN_RANGE = "Enter value in range [$-$]";
const char *const SET_ENTER_THICKNESS = "Enter value for thickness [$-$]";
const char *const SET_ENTER_COLOR_RGB = "Entering color by rgb: <$> ";
const char *const SET_ENTER_COLOR_RGB_INVALID = "Entered color part is invalid ";
const char *const SET_ENTER_COLOR_RGB_NAME = "Enter name: ";
const char *const SET_ENTER_COLOR_ID = "Enter color <id> \noptions: \n$";
const char *const SET_ENTER_COLOR_ID_INVALID = "Entered color id is invalid";
const char *const SET_ENTER_GROUP_ID= "Set group. To list all groups use command 'list'. Enter id: ";
const char *const SET_ENTER_GROUP_ID_INVALID= "Can not find group by provided id. Is it really a group? ";

const char *const PRINT_SHAPE = "id: $, name: $, color: $, fill: $, pos: $, detail: $ ";
const char *const INVALID_INPUT = "Invalid input";
const char *const INVALID_ID = "Invalid id.";
const char *const UNKNOWN_COMMAND = "Unknown command '$'. For help type '$'";
const char *const UNKNOWN_OPTION = "Unknown option '$'. For help type '$'";
const char *const ERROR_FILE_IO = "Unable to read/write file '$'";
const char *const ERROR_FILE_DUPLICATE_OR_ERROR = "File already exists or can't open it";
const char *const FILE_LOADING_ERROR = "Loading error. Correct the input data and try again.";
const char *const IMPORT_ABORTED = "Import aborted. ";
const char *const COMMAND_NOT_ALLOWED_IN_HEADLESS = "Command $ is unavailable in headless mode. ";
const char *const LOAD_WILL_OVERWRITE = "Loading from file will overwrite current instance of tspaint, which might cause you a lot of pain. \nAre you sure you want to do that? \nYour progress will be lost unless saved. \n Do you want to proceed? ";
const char *const YES_OR_NO_WITH_MESSAGE = "$ [y/n]";
const char *const PRINTING_GROUP = "Printing group details";


const char *const AVAILABLE_OPTION = "Options available: $";

const char *const HELP_HELP = "Prints this help";
const char *const HELP_QUIT = "Ends this pain";

const char *const HELP_SAVE = "Saves output of this pain to file";
const char *const HELP_GROUP = "Used to create group from Shapes/groups by their ID.\ngroup <number_of_entered_ids> [id...]";
const char *const HELP_SET = "Modify color/fill/thickness etc of created objects. Similar to standard mspaint where you first select a color and then draw. ";
const char *const HELP_DRAW = "Draw a shape circle/line/polyline/ellipse/rectangle/square/star/triangle. ";
const char *const HELP_LOAD = "Load instance of tspaint from file. ";
const char *const HELP_HIDE = "HELP_HIDE";
const char *const HELP_SHOW = "HELP_SHOW";
const char *const HELP_NEW = "HELP_NEW";
const char *const HELP_DELETE = "HELP_DELETE";
const char *const HELP_LIST = "List all objects in tspaint";
const char *const TSPAINT_INFO = "ThisIsPain.T\n-----------------------------------------------\nSimple drawing tool for experienced FIT students.\n";


const char *const EXAMPLE_SAVE = "save <format> <outfile> \nSupported formats: bmp, svg";
const char *const EXAMPLE_GROUP = "Assuming we have two circles with ids: 2, 3 and we want to create a group out from them. \ngroup objects <number_of_ids> [id,...]\ngroup objects 2 2 3";
const char *const EXAMPLE_GROUP_OBJECTS = "group objects: Assuming we have two circles with ids: 1, 2. \ngroup objects <number_of_ids> [id,...]\ngroup 2 1 2";
const char *const EXAMPLE_GROUP_CLONE = "group clone: Assuming we have group id: 1 circles with ids: 2, 3. \ngroup clone <group_id> creates a deep copy of group <group_id>. Result is placed in the root group.";
const char *const EXAMPLE_GROUP_LIST = "group list: List all children of current group. If not set, root group is used (everything is printed). Default group can be switched by 'set group' command. ";

const char *const EXAMPLE_SET = "set color byname BLACK__INSIDE_OF_MY_SOUL\nset color id 3\nset color rgb 255 255 255 myNewColor";
const char *const EXAMPLE_SET_COLOR = "set color {byname,id,rgb} \nexample: \nset color byname BLACK__INSIDE_OF_MY_SOUL\nset color id 3\nset color rgb 255 255 255 myNewColor";
const char *const EXAMPLE_SET_FILL = "set fill {byname,id,rgb} \nexample: \nset fill byname BLACK__INSIDE_OF_MY_SOUL\nset fill id 3\nset fill rgb 255 255 255 myNewColor";
const char *const EXAMPLE_SET_THICKNESS = "set thickness <int> \nUsed to chenge thicknes of new created shapes. Example:\nset thickness 3";
const char *const EXAMPLE_SET_GROUP = "set group <id> \nUsed for switching between groups. Default is root (id=1). Example:\nset thickness 3";

const char *const EXAMPLE_DRAW = "draw circle <center_x> <center_y> <diameter>\ndraw circle 50 50 10";
const char *const EXAMPLE_DRAW_CIRCLE = "draw circle <center_x> <center_y> <diameter>\ndraw circle 50 50 10";
const char *const EXAMPLE_DRAW_RECTANGLE = "draw rectangle <start_x> <start_y> <width> <height>\ndraw rectangle 10 10 100 50";
const char *const EXAMPLE_DRAW_STAR = "draw star <start_x> <start_y> <diameter> \ndraw star 100 100 50";
const char *const EXAMPLE_DRAW_TRIANGLE = "draw triangle <pos1> <pos2> <pos2> \ndraw triangle 10 10 50 50 10 30";
const char *const EXAMPLE_DRAW_ELLIPSE = "draw ellipse <center_x> <center_y> <width> <height>\ndraw ellipse 10 10 100 50";
const char *const EXAMPLE_DRAW_POLYLINE = "draw polyline <number_of_points> <p1x> <p1y> ... \ndraw polyline 3 1 1 2 2 3 3";
const char *const EXAMPLE_DRAW_LINE = "draw line <start_x> <start_y> <end_x> <end_y> \ndraw line 10 10 100 100";
const char *const EXAMPLE_LOAD = "load examples/house.tspaint";
const char *const EXAMPLE_HIDE = "EXAMPLE_HIDE";
const char *const EXAMPLE_SHOW = "EXAMPLE_HIDE";
const char *const EXAMPLE_NEW = "EXAMPLE_NEW";
const char *const EXAMPLE_DELETE = "EXAMPLE_DELETE";
const char *const EXAMPLE_LIST = "list";
const char *const EXAMPLE_HELP = "help";
const char *const EXAMPLE_QUIT = "quit";

const char *const ROOT_GROUP = "Root";

const char *const PROGTEST_ERROR_LOADING = "Error in basic compilation - source file not accessible [Access help (934 B)] (2 hits available, 4 with penalisation -10%";
const char *const QUIT_MESSAGE = "Error in basic logic. On behalf of This Is Pain(t), LTD, we would like to thank you for using our services and wish you a nice day. ";




const char *const CENTER_X = "CENTER_X";
const char *const CENTER_Y = "CENTER_Y";
const char *const DIAMETER_X = "DIAMETER_X";
const char *const DIAMETER_Y = "DIAMETER_Y";
const char *const COLOR_R = "COLOR_R";
const char *const COLOR_G = "COLOR_G";
const char *const COLOR_B = "COLOR_B";
const char *const FILL_R = "FILL_R";
const char *const FILL_G = "FILL_G";
const char *const FILL_B = "FILL_B";
const char *const THICKNESS = "THICKNESS";
const char *const COLOR_RGB = "COLOR_RGB";
const char *const FILL_RGBA = "FILL_RGBA";
const char *const WIDTH = "WIDTH";
const char *const HEIGHT = "HEIGHT";

const char *const SVG_INIT = "<svg width='MAX_WIDTH' height='MAX_HEIGHT' xmlns='http://www.w3.org/2000/svg'>";
const char *const SVG_END = "</svg>";
const char *const SVG_GROUP_BEGIN = "<g id='GROUP_ID'>";
const char *const SVG_GROUP_END= "</g>";
const char *const SVG_CIRCLE = "<circle cx='CENTER_X' cy='CENTER_Y' r='DIAMETER_X' style=\"stroke:COLOR_RGB;stroke-width:THICKNESS;fill:FILL_RGBA;\"/>";
const char *const SVG_ELLIPSE = "<ellipse cx='CENTER_X' cy='CENTER_Y' rx='DIAMETER_X' ry='DIAMETER_Y' style=\"stroke:COLOR_RGB;stroke-width:THICKNESS;fill:FILL_RGBA;\"/>";
const char *const SVG_RECTANGLE = "<rect x='START_X' y='START_Y' width='WIDTH' height='HEIGHT' style=\"stroke:COLOR_RGB;stroke-width:THICKNESS;fill:FILL_RGBA;\"/>";
const char *const SVG_LINE = "<line x1='START_X' y1='START_Y' x2='END_X' y2='END_Y' style=\"stroke:COLOR_RGB;stroke-width:THICKNESS;\"/>";
const char *const SVG_COLOR_RGB = "rgb(COLOR_R,COLOR_G,COLOR_B)";
const char *const SVG_FILL_RGB = "rgb(FILL_R,FILL_G,FILL_B)";

const char *const MAX_WIDTH = "MAX_WIDTH";
const char *const MAX_HEIGHT = "MAX_HEIGHT";
const char *const CONTENT = "CONTENT";
const char *const GROUP_ID = "GROUP_ID";
const char *const GROUP_BEGIN = "GROUP_BEGIN";
const char *const GROUP_END = "GROUP_END";
const char *const START_X = "START_X";
const char *const START_Y = "START_Y";
const char *const END_X = "END_X";
const char *const END_Y = "END_Y";
