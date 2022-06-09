/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 13.05.2022
  */

#include "Tspaint.h"
#include "constants.h"

Tspaint::Tspaint() : colorPalette(ColorPalette()) {
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(170, 170, 170, "GRAY__PROGTEST")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(255, 87, 51, "GRAY__OUT_OF_SIGHT")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(0, 0, 0, "BLACK__INSIDE_OF_MY_SOUL")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(255, 0, 255, "MAGENTA__BRAIN_OVERFLOW")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(0, 255, 0, "GREEN__PROGTEST_HOME")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(192, 64, 0, "RED__COMPILED_WITH_ERRORS")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(0, 153, 203, "BLUE__FUN_FOR_A_WEEKEND")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(128, 192, 0, "GREEN__ALMOST_THERE")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(0, 192, 0, "GREEN__IM_DONE")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(255, 255, 255, "WHITE__LOADING")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(240, 171, 0, "YELLOW__FIT")));

    // todo load from file
    color = colorPalette.getColorByName("YELLOW__FIT");
    fill = colorPalette.getColorByName("GRAY__PROGTEST");
    thickness = THICKNESS_DEFAULT;
}

void Tspaint::AddShape(std::shared_ptr<Shape> &&shape) {
    this->shapes.push_back(std::move(shape));
}

std::vector<std::shared_ptr<Shape>> Tspaint::GetShapes() {
    return this->shapes;
}

unsigned long Tspaint::GenerateId() {
    return ++idGenerator;
}

Tspaint::Tspaint(std::shared_ptr<Tspaint> src) {
    if (this != src.get()) {
        this->colorPalette = src->colorPalette;
        this->shapes = src->shapes; // todo maybe merge?
        this->fill = src->fill;
        this->color = src->color;
        this->thickness = src->thickness;
        this->idGenerator = src->idGenerator;
    }

}
