/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 09.06.2022
 */

#include "ShapeGroup.h"
#include "Helper.h"
#include "constants.h"


std::vector<std::shared_ptr<SuperShape>> ShapeGroup::List() const {
    return children;
}

std::ostream & operator<<(std::ostream & os, const ShapeGroup & shapeGroup) {
    for(const auto & shapeOrGroup: shapeGroup.children){
        os << shapeOrGroup->Print() << std::endl;
    }
    return os;
}

std::string ShapeGroup::Print() const {
    std::string out = "Group: ";
    for(const auto & child : children){
        out += "  "+ child->Print() + "\n";
    }
    return out;
}

ShapeGroup::ShapeGroup(unsigned int id,
                       std::string name,
                       std::vector<std::shared_ptr<SuperShape>> children):
    SuperShape(id,
               name,
               std::make_shared<Pos>(0,0),
               [&children]() {
                   size_t max = 0;
                   for (auto child: children) {
                       if (child->Height() > max)
                           max = child->Height();
                   }
                   return max;
               }(),
               [&children]() {
                   size_t max = 0;
                   for (auto child: children) {
                       if (child->Width() > max)
                           max = child->Width();
                   }
                   return max;
               }()
               ), children(children){

}

void ShapeGroup::Add(std::shared_ptr<SuperShape> && superShape){
    this->children.push_back(superShape);
}

//std::shared_ptr<ShapeGroup> ShapeGroup::Clone(unsigned int newId) const {
//    auto res = std::make_shared<ShapeGroup>(*this);
//    res->id = newId;
//    return res;
//}

bool ShapeGroup::operator==(const SuperShape &s) {
    // todo
    const ShapeGroup *ptr = dynamic_cast<const ShapeGroup *>( &s );
    if(ptr)
        return id == ptr->id && children.size() == ptr->children.size();
    return false;
}

ShapeGroup::ShapeGroup(const ShapeGroup &shapeGroup) : SuperShape(shapeGroup.id, shapeGroup.name, shapeGroup.center, shapeGroup.width, shapeGroup.height) {
    // todo
    if(!(*this == shapeGroup)){
        children = std::vector<std::shared_ptr<SuperShape>>(shapeGroup.children);
        id = shapeGroup.id;
        height = shapeGroup.height;
        width = shapeGroup.width;
        name = shapeGroup.name;
        center = shapeGroup.center;
    }
}

void ShapeGroup::Draw(std::shared_ptr<Interface> interface, std::string format) {
    // todo
    for(auto superShape: children){
        superShape->Draw(interface, format);
    }
}
