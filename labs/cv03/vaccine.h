//
// Created by Tomas Dostal on 04.03.2022.
//

#ifndef CV03_VACCINE_H
#define CV03_VACCINE_H
#include <string>
#include <iostream>
#include "date.h"

class Vaccine {
public:
    std::string name;
    std::uint16_t id;
    std::string supplier;
    Date valid_till;

    double autism_probability;
    friend std::ostream& operator << (std::ostream &os, const Vaccine& vac);
    size_t code();
    bool is_safe();
    bool can_be_applied(Date & date);
    bool is_certified();

private:
    void make_vaccine_look_better();
    size_t hash() const;
};
