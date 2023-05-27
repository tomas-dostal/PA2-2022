/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 27.05.2023
 */

#pragma once


#include "PolyLine.h"

class Star: public PolyLine {
public:

    /**
     * Star shape
     * @param id
     * @param name
     * @param std::vector<Pos> center
     * @param diameter
     * @param thickness
     * @param color
     * @param fill
     */
    Star(int id, std::string name, std::shared_ptr<Pos> center, size_t diameter, size_t thickness, std::shared_ptr<Color> color, std::shared_ptr<Color> fill);

    // Delete copy constructor
    Star(const Star&) = delete;

    //void MoveRelative(int x, int y) override;

    std::shared_ptr<SuperShape> Clone(const std::function<int(void)>& IdGenerator) override;

    bool operator==(const SuperShape &s) override;

    // std::pair<size_t, size_t> CalcMaxDimensions() override;

    std::vector<Pos> generateStarPositions(const std::shared_ptr<Pos>center, int diameter);
private:
    size_t diameter;
};