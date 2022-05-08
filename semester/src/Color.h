/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once
#include <string>


enum PredefinedColor{
    GRAY__PROGTEST,
    GRAY__OUT_OF_SIGHT,
    BLACK__INSIDE_OF_MY_SOUL,
    MAGENTA__BRAIN_OVERFLOW,
    GREEN__PROGTEST_HOME,
    RED__COMPILED_WITH_ERRORS,
    BLUE__FUN_FOR_A_WEEKEND,
    GREEN__ALMOST_THERE,
    GREEN__IM_DONE,
    WHITE__LOADING,
    YELLOW__FIT
};

class Color {
    Color(){
        *this = Color(YELLOW__FIT);
    }
    Color(unsigned char r, unsigned char g, unsigned char b);
    // any recommendation how to do this inside of the enum is welcomed :)

    Color(PredefinedColor predefinedColor){
        switch (predefinedColor) {
            case GRAY__PROGTEST:
                r = 170; g = 170; b = 170;
                break;
            case GRAY__OUT_OF_SIGHT:
                r = 255; g = 87; b = 51;
                break;
            case BLACK__INSIDE_OF_MY_SOUL:
                r = 0; g = 0; b = 0;
                break;
            case MAGENTA__BRAIN_OVERFLOW:
                r = 255; g = 0; b = 255;
                break;
            case GREEN__PROGTEST_HOME:
                r = 0; g = 255; b = 0;
                break;
            case RED__COMPILED_WITH_ERRORS:
                r = 192; g = 64; b = 0;
                break;
            case BLUE__FUN_FOR_A_WEEKEND:
                r = 0; g = 153; b = 203;
                break;
            case GREEN__ALMOST_THERE:
                r = 128; g = 192, b = 0;
                break;
            case GREEN__IM_DONE:
                r = 0; g = 192, b = 0;
                break;
            case WHITE__LOADING:
                r = 255; g = 255, b = 255;
                break;
            case YELLOW__FIT:
                r = 255; g = 255, b = 255;
                break;
            default: // YELLOW__FIT
                r = 240; g = 171; b = 0;
                break;
        }

    };

    std::string hex();

private:
    int r, g, b;
};
