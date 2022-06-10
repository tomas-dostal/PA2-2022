/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 11.06.2022
 */

#include "SuperShape.h"

SuperShape::SuperShape( unsigned int id,
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

unsigned int SuperShape::Id(){
    return id;
}

size_t SuperShape::Width() {
    return width;
}

size_t SuperShape::Height() {
    return height;
}
