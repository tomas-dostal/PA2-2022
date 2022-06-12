/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 11.06.2022
 */

#include "SuperShape.h"

SuperShape::SuperShape( int id,
            std::string name,
            std::shared_ptr<Pos> center,
            size_t width,
            size_t height): id(id),
                           name(name),
                           center(center),
                           width(width),
                           height(height)

{

};

std::string SuperShape::Name(){
    return name;
}

int SuperShape::Id(){
    return id;
}

size_t SuperShape::Width() {
    return width;
}

size_t SuperShape::Height() {
    return height;
}

void SuperShape::NewId( const std::function<int(void)> IdGenerator){
    this->id = IdGenerator();
}
