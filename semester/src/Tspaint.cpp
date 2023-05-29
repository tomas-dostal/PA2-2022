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
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(130, 130, 114, "GRAY__OUT_OF_SIGHT")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(0, 0, 0, "BLACK__INSIDE_OF_MY_SOUL")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(255, 0, 255, "MAGENTA__BRAIN_OVERFLOW")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(0, 255, 0, "GREEN__PROGTEST_HOME")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(192, 64, 0, "RED__COMPILED_WITH_ERRORS")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(0, 153, 203, "BLUE__FUN_FOR_A_WEEKEND")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(128, 192, 0, "GREEN__ALMOST_THERE")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(0, 192, 0, "GREEN__IM_DONE")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(255, 255, 255, "WHITE__LOADING")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(240, 171, 0, "YELLOW__FIT")));
    colorPalette.addIfNotExists(std::make_shared<Color>(Color(255, 87, 51, "ORANGE__PAIN")));

    // todo load from file
    color = colorPalette.getColorByName("YELLOW__FIT");
    fill = colorPalette.getColorByName("GRAY__PROGTEST");
    background = colorPalette.getColorByName("BLACK__INSIDE_OF_MY_SOUL");
    thickness = THICKNESS_DEFAULT;
    root = currentGroup = NewGroup();
}

std::shared_ptr<ShapeGroup> Tspaint::NewGroup() {
    auto group = std::make_shared<ShapeGroup>(GenerateId(),
            "group",
            std::vector<std::shared_ptr<SuperShape>>()
            );
    if(currentGroup)
        currentGroup->Add(group);
    superShapesById.insert({group->Id(), group});
    return group;
}


std::shared_ptr<ShapeGroup> Tspaint::AddExistingGroup(std::shared_ptr<ShapeGroup> group) {
    currentGroup->Add(group);
    superShapesById.insert({group->Id(), group});
    for(const auto & item: group->List()){
        auto ptr = std::dynamic_pointer_cast<ShapeGroup>(item);
        if(ptr)
            AddExistingGroup(ptr);
        else
            superShapesById.insert({item->Id(), item});
    }
    return group;
}


std::shared_ptr<ShapeGroup> Tspaint::AddGroup(std::vector<std::shared_ptr<SuperShape>> superShapes) {
    auto group = std::make_shared<ShapeGroup>(GenerateId(), "Group", superShapes);

    superShapesById.insert({group->Id(), group});
    currentGroup->Add(group);
    for(const auto & item: group->List()){
        auto ptr = std::dynamic_pointer_cast<ShapeGroup>(item);
        if(ptr)
            AddExistingGroup(ptr);
        else
            superShapesById.insert({item->Id(), item});
    }
    return group;
}

void Tspaint::AddShape(std::shared_ptr<SuperShape> superShape){
    currentGroup->Add(superShape);
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
