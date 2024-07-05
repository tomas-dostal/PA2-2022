/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include <memory>

class Pos {
public:
    Pos() : x(0), y(0) {};

    /**
     * Position
     * @param x
     * @param y
     */
    Pos(int x, int y) : x(x), y(y) {};

    Pos(const Pos &p) = default;

    Pos &operator=(const Pos &p) = default;

    bool operator==(const Pos &p) const { return this->x == p.x && this->y == p.y; };

    bool operator!=(const Pos &p) const { return !(*this == p); };

    /**
     * Clones position
     * @return std::shared_ptr<Pos>(*this)
     */
    std::shared_ptr<Pos> Clone();

    int x, y;
};
