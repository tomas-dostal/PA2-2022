/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 13.05.2022
  */

#include "Tspaint.h"
#include "ShapeGroup.h"
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
    root = std::make_shared<ShapeGroup>(GenerateId(), "root", std::vector<std::shared_ptr<SuperShape>>());
    currentGroup = root;
}

void Tspaint::AddGroup() {
    auto group = std::make_shared<ShapeGroup>(GenerateGroupId(),
            "group",
            std::vector<std::shared_ptr<SuperShape>>()
            );

    this->currentGroup->Add(group);
}





unsigned long Tspaint::GenerateId() {
    return ++idGenerator;
}


unsigned long Tspaint::GenerateGroupId() {
    return ++groupIdGenerator;
}


Tspaint::Tspaint(const std::shared_ptr<Tspaint>& src) {
    if (this != src.get()) {
        this->colorPalette = src->colorPalette;// todo
        root = src->root;
        currentGroup = src->currentGroup;
        this->fill = src->fill;
        this->color = src->color;
        this->thickness = src->thickness;
        this->idGenerator = src->idGenerator;
    }

}
