/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 28.05.2022
 */

#pragma once
#include <vector>
#include <string>

const float CHANCES_FOR_PASSING_PA2 = 0.5;
const char *const PROGTEST_ERROR_FILENAME = "src/progtesterrors.txt";
const int RGB_MIN = 0;
const int RGB_MAX = 255;
const int THICKNESS_MIN = 1;
const int THICKNESS_MAX = 20;

const int POS_X_MIN = 0;
const int POS_X_MAX = 1920;
const int POS_Y_MIN = 0;
const int POS_Y_MAX = 1080;
const int THICKNESS_DEFAULT = 6;
const int GROUP_MAX_SIZE = 10;
const float SHAPE_NA_CIRCLE = 1.0;
const float SHAPE_NA_RECTANGLE = 0.2;
const float SHAPE_NA_ELLISPE = 1.0;
const float SHAPE_NA_DIAMOND = 2.0;
const float SHAPE_NA_STAR = 5.0;
const float SHAPE_NA_CROSS = 100.0;
const int BMP_THICKNESS = 1;
// How many lines are used to draw a circle with PolyLine
const float ELLIPSE_PRECISION = 1.1;

const std::vector<std::string> YES_NO = {"y", "n"};
const std::vector<std::string> YES = {"y"};
const std::vector<std::string> NO = {"n"};
const std::string SEP_SPACE = "  ";

