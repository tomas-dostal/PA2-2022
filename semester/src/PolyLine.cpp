/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 12.06.2022
 */
#include "PolyLine.h"


#include <numeric>
#include <functional>
#include <memory>

#include "Line.h"
#include "Formatter.h"
#include "Export.h"
#include "Helper.h"
#include "messages.h"




PolyLine::PolyLine(int id, std::string name, std::vector<Pos> positions, size_t thickness, std::shared_ptr<Color> color,
                    std::shared_ptr<Color> fill)
        : Shape(id,
                name,
                std::invoke([&positions](){
                    int sumWidth = 0;
                    int sumHeight = 0;
                    for(const auto & p: positions){
                        sumWidth += p.x;
                        sumHeight += p.y;
                    }
                    return std::make_shared<Pos>(
                            (int) (sumWidth / positions.size()),
                            (int) (sumHeight / positions.size())
                            );
                }),
                (*std::max_element(positions.begin(), positions.end(), [](const Pos & a, const Pos & b){
                    return a.x > b.x;
                })).x,
                (*std::max_element(positions.begin(), positions.end(), [](const Pos & a, const Pos & b){
                    return a.y > b.y;
                })).y,
                thickness,
                color,
                fill),
          positions(positions){


}

bool PolyLine::operator==(const SuperShape &s) {
    const PolyLine *ptr = dynamic_cast<const PolyLine *>( &s );
    return ptr != nullptr
           && this->positions == ptr->positions
           && this->center == ptr->center
           && this->fill == ptr->fill
           && this->color == ptr->color;
}


void PolyLine::Draw(Export & exporter) {

    exporter.Process(SHAPE_GROUP_BEGIN, {
            {GROUP_ID, std::to_string(id)}
    });
    for(size_t i = 0; i < this->positions.size() - 1; i++) {
        exporter.Process(SHAPE_LINE, {
                {START_X,   std::to_string(positions[i].x)},
                {START_Y,   std::to_string(positions[i].y)},
                {END_X,     std::to_string(positions[i + 1].x)},
                {END_Y,     std::to_string(positions[i + 1].y)},
                {CENTER_Y,  std::to_string(this->center->x)},
                {CENTER_X,  std::to_string(this->center->x)},
                {CENTER_Y,  std::to_string(this->center->x)},
                {COLOR_R,   std::to_string(this->color->R())},
                {COLOR_G,   std::to_string(this->color->G())},
                {COLOR_B,   std::to_string(this->color->B())},
                {FILL_R,    std::to_string(this->fill->R())},
                {FILL_G,    std::to_string(this->fill->G())},
                {FILL_B,    std::to_string(this->fill->B())},
                {THICKNESS, std::to_string(this->thickness)}
        });
    }
    exporter.Process(SHAPE_GROUP_END, {});
}

std::string PolyLine::Print() const {
    return "" + name + " (" + std::to_string(id) + ")";

}

std::pair<size_t, size_t> PolyLine::CalcMaxDimensions(){
    return std::make_pair(width, height);
}
