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
    std::vector<std::shared_ptr<SuperShape>> res;
    for(const auto & [id, child]: children)
        res.push_back(child);
    return res;
}

std::ostream & operator<<(std::ostream & os, const ShapeGroup & shapeGroup) {
    for(const auto& [id, child]: shapeGroup.children)
        os << child->Print(0) << std::endl;
    return os;
}

std::string ShapeGroup::Print(int indent) const {
    std::string out = std::string(indent, ' ') + "Group (" + std::to_string(id) + "): \n";
    for(const auto & [id, child] : children){
        out += child->Print(indent + 2);
    }
    return out;
}

ShapeGroup::ShapeGroup( int id,
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
                           ){
        for(const auto & child: children)
            this->children.insert({child->Id(), child});
}

// todo &&
void ShapeGroup::Add(std::shared_ptr<SuperShape> superShape){
    this->children.insert({superShape->Id(), superShape});
}
bool ShapeGroup::operator==(const SuperShape &s) {
    // todo
    const ShapeGroup *ptr = dynamic_cast<const ShapeGroup *>( &s );
    if(ptr)
        return id == ptr->id && children.size() == ptr->children.size();
    return false;
}

void ShapeGroup::NewId( const std::function<int(void)> IdGenerator){
    std::map<int, std::shared_ptr<SuperShape>> tmp;

    for(auto & [id, child]: children){
        tmp.insert({IdGenerator(), child});
    }
    children = tmp;
}

void ShapeGroup::Draw(Export & exporter) {
    exporter.Process(SHAPE_GROUP_BEGIN, {
            {GROUP_ID, std::to_string(id)}
    });
    for(const auto &[id, child]: children){
        child->Draw(exporter);
    }
    exporter.Process(SHAPE_GROUP_END, {});
}

std::pair<size_t, size_t> ShapeGroup::CalcMaxDimensions() {
    size_t max_width = 0;
    size_t max_height = 0;
    for(auto const& [id, shape] : this->children){
        std::pair<size_t, size_t> tmp = shape->CalcMaxDimensions();
        if(tmp.first > max_width)
            max_width = tmp.first;
        if(tmp.second > max_height)
            max_height = tmp.second;
    }
    // update it for current ShapeGroup
    width = max_width;
    height = max_height;

    return std::pair<size_t, size_t>{max_width, max_height};
}

void ShapeGroup::RemoveIfExists(int id){
    auto it = children.find(id);
    if(it != children.end()){
        children.erase(it);
    }
}

void ShapeGroup::MoveRelative(int x, int y) {
    for(auto & child: children){
        child.second->MoveRelative(x, y);
    }
    center->x += x;
    center->y += y;
}

std::shared_ptr<SuperShape> ShapeGroup::Clone( const std::function<int(void)>& IdGenerator){

    std::vector<std::shared_ptr<SuperShape>> childrenCloneVector(0);
    for(const auto & child: children) {
        childrenCloneVector.emplace_back(child.second->Clone(IdGenerator));
    }

        return std::make_shared<ShapeGroup>(  IdGenerator(),
                                              this->name,
                                              childrenCloneVector);

}
