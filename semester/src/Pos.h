/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once


class Pos {
public:
    Pos(): x(0), y(0){};
    Pos(int x, int y): x(x), y(y){};
    Pos(const Pos & p): x(p.x), y(p.y){};
    Pos & operator = (const Pos & p){this->x = p.x; this->y = p.y};

    bool operator == (const Pos & p){return this->x == p.x && this->y == p.y};
    bool operator != (const Pos & p){return !(*this == p);};

    int x, y;
};
