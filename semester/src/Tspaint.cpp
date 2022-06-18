/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 13.05.2022
  */

#include "Tspaint.h"
#include "ShapeGroup.h"
#include "constants.h"
#include "messages.h"

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
    background = colorPalette.getColorByName("BLACK__INSIDE_OF_MY_SOUL");
    thickness = THICKNESS_DEFAULT;
    root = currentGroup = AddGroup();
}

std::shared_ptr<ShapeGroup> Tspaint::AddGroup() {
    auto group = std::make_shared<ShapeGroup>(GenerateId(),
            "group",
            std::vector<std::shared_ptr<SuperShape>>()
            );
    if(currentGroup)
        currentGroup->Add(group);
    this->superShapesById.insert({group->Id(), group});
    return group;
}


void Tspaint::AddGroup(std::vector<std::shared_ptr<SuperShape>> superShapes) {

//    std::vector<std::shared_ptr<SuperShape>> shapeClones;
//    for(const auto & ss: superShapes){
//        std::shared_ptr<SuperShape> clone = ss->Clone([this](){
//            return GenerateId();
//        });


    auto group = std::make_shared<ShapeGroup>(GenerateId(), "Group", superShapes);
    this->currentGroup->Add(group);
    this->superShapesById.insert({group->Id(), group});
}

void Tspaint::AddShape(std::shared_ptr<SuperShape> superShape){
    this->currentGroup->Add(superShape);
    superShapesById.insert({superShape->Id(), superShape});
}

std::string Tspaint::Print() const {
    return root->Print(0);
}



int Tspaint::GenerateId() {
    return idGenerator++;
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

bool Tspaint::UseGroup(int id) {
    auto ss = superShapesById.find(id);
    if(ss != superShapesById.end())
    {
        std::shared_ptr<ShapeGroup> ptr = std::dynamic_pointer_cast<ShapeGroup>( ss->second );
        if(ptr){
            currentGroup = ptr;
            return true;
        }
    }
    return false;
}

bool Tspaint::IsValidIndex(int index) const {
    return !(superShapesById.find(index) == superShapesById.end());
}

std::shared_ptr<SuperShape> Tspaint::GetSuperShape(int index){
    auto shape = superShapesById.find(index);
    if(shape != superShapesById.end())
        return shape->second;
    return nullptr;
}

std::pair<size_t, size_t> Tspaint::MaxDimensions() const {
    return root->CalcMaxDimensions();
}

void Tspaint::RemoveSuperShapeFromRootGroup(int shapeId) {
    currentGroup->RemoveIfExists(shapeId);
}
