/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 09.06.2022
 */

#include "ShapeGroup.h"
#include "Helper.h"
#include "constants.h"

template<class T>
std::vector<T> ShapeGroup<T>::List() const {
    return children;
}

template<class T>
std::ostream & operator<<(std::ostream & os, const ShapeGroup<T> & shapeGroup) {
    for(T shapeOrGroup: shapeGroup){
        const Shape *ptr = dynamic_cast<const Shape *>( &shapeOrGroup );
        // group
        if(!ptr){
            std::vector<std::string> vs;
            for(auto item: shapeOrGroup ){
                vs.push_back(item.Print());
            }
            // std::accumulate could be used for that, but it is cpp20
            auto shapeOrGroupVector = Helper::Indent(SEP_SPACE, vs);
            for(std::string str: shapeOrGroupVector)
                os << str << std::endl;
        }
        else{
            os << shapeOrGroup.Print() << std::endl;
        }

    }
    return os;
}

template<class T>
std::string ShapeGroup<T>::Print() const {
    std::string out = "";
    for(auto child : children){
        out += child.Print() + "\n";
    }
    return out;
}

template<class T>
ShapeGroup<T>::ShapeGroup(unsigned int id, std::vector<T> children): children(children), id(id){
}

template<class T>
void ShapeGroup<T>::Add(std::shared_ptr<T> shapeOrGroup){
    this->children.push_back(shapeOrGroup);
}

template<class T>
std::shared_ptr<ShapeGroup<T>> ShapeGroup<T>::Clone(unsigned int newId) const {
    auto res = std::shared_ptr<ShapeGroup>(*this);
    res->id = newId;
    return res;
}


