//
// Created by Tomas Dostal on 04.03.2022.
//

#include "vaccine.h"
#include <string>
#include <iostream>
#include <iostream>
#include <functional>
#include <cstdio>
#include <string>
#include <set>

using namespace std;

std::ostream &operator<<(ostream &os, const Vaccine &vac) {
    return os << "Vaccine " << vac.name << " valid until: " << vac.valid_till << " causes autism with probability " << vac.autism_probability;
}

size_t Vaccine::code() {
    size_t hash_name = std::hash<std::string> {}(name);
    size_t hash_validity= this->hash();
    size_t hash = hash_name ^ (hash_validity << 1);
    return hash;
}

void Vaccine::make_vaccine_look_better() {
    valid_till = valid_till + 10;
    while (autism_probability > 0.000001) {
        autism_probability *= 0.026;
    }
}

bool Vaccine::is_safe() {
    return autism_probability < 0.000001;
}

bool Vaccine::is_certified() {
    return this->name != "Russia Sputnik V";
}

bool Vaccine::can_be_applied(Date &date) {
    return this->valid_till <= date;
}

size_t Vaccine::hash() const {
    uint8_t var = this->valid_till.year * 1000 * 100 + this->valid_till.month * 100 + this->valid_till.day;
    return std::hash<uint8_t> {}(var);
}