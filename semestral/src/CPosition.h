//
// Created by tomas on 5/4/22.
//

#ifndef SEMESTRAL_CPOSITION_H
#define SEMESTRAL_CPOSITION_H


class CPosition {
public:
    CPosition(int x, int y);
    std::pair<int, int> get();
    void set(std::pair<int, int> pos);
private:
    int x, y;
};


#endif //SEMESTRAL_CPOSITION_H
