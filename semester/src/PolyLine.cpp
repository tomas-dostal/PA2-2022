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
                std::invoke([&positions, &thickness](){
                    int sumWidth = 2*thickness;
                    int sumHeight = 2*thickness;
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
                })).x + 2 * thickness,
                (*std::max_element(positions.begin(), positions.end(), [](const Pos & a, const Pos & b){
                    return a.y > b.y;
                })).y + 2 * thickness,
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

std::pair<size_t, size_t> PolyLine::CalcMaxDimensions(){
    // tmp hotfix copy from Star
    int maxX, maxY = 0;
    int minX, minY = std::numeric_limits<int>::max();;
    for (const auto& pos : positions) {
        maxX = std::max(maxX, pos.x);
        minX = std::min(minX, pos.x);
        maxY = std::max(maxY, pos.y);
        minY = std::min(minY, pos.y);
    }
    return std::make_pair<size_t, size_t>(maxX-minX + center->x, maxY-minY + center->y);
}

void PolyLine::MoveRelative(int x, int y) {
    for(auto & point: positions){
        point.x += x;
        point.y += y;
    }
    center->x += x;
    center->y += y;
}

std::shared_ptr<SuperShape> PolyLine::Clone(const std::function<int(void)>& IdGenerator) {
    std::vector<Pos> clonePositions(0);
    for(const auto & position: positions)
        clonePositions.emplace_back(Pos(position));
    return std::make_shared<PolyLine>(IdGenerator(), name, clonePositions, thickness, color->Clone(), fill->Clone());
}

std::shared_ptr<PolyLine> PolyLine::ToPolyLine(){
    return std::make_shared<PolyLine>(*this);
}
