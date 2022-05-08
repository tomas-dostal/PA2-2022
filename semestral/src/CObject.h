//
// Created by tomas on 5/4/22.
//

#ifndef SEMESTRAL_COBJECT_H
#define SEMESTRAL_COBJECT_H


class CObject {
    virtual bool is_visible();

    CColor color;
    bool visible;
    CPosition cPosition;
};


#endif //SEMESTRAL_COBJECT_H
