/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 09.06.2022
 */

#include "ShapeGroup.h"
#include "SuperShape.h"
#include "Helper.h"
#include "messages.h"
#include "Export.h"

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
    std::string out = "Group (" + std::to_string(id) + "): \n";
    for(const auto & child : children){
        out += Helper::ToString(Helper::Indent("   ", std::vector<std::string>({child->Print()})));
    }
    return out;
}

ShapeGroup::ShapeGroup(int id,
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

// todo &&
void ShapeGroup::Add(std::shared_ptr<SuperShape> superShape){
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

void ShapeGroup::NewId( const std::function<int(void)> IdGenerator){
    id = IdGenerator();
    for(auto item: children){
        item->NewId(IdGenerator);
    }
}

void ShapeGroup::Draw(Export & exporter) {
    exporter.Process(GROUP_BEGIN, {
            {GROUP_ID, std::to_string(id)}
    });
    for(const auto & child: children){
        child->Draw(exporter);
    }
    exporter.Process(GROUP_END, {});
}


//std::shared_ptr<SuperShape> ShapeGroup::Clone(std::function<int(void)> IdGenerator){
//    std::vector<std::shared_ptr<SuperShape>> childrenCopy;
//    for(const auto & child: childrenCopy){
//        childrenCopy.push_back(child->Clone(IdGenerator));
//    }
//    return std::make_shared<ShapeGroup>(IdGenerator(), name, childrenCopy);
//}
//
