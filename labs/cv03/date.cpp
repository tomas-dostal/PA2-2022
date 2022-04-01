//
// Created by Tomas Dostal on 04.03.2022.
//

#include <tuple>
#include "date.h"

bool Date::operator<=(const Date &date) const {
    return std::tie(this->year, this->month, this->day) <=  std::tie(date.year, date.month, date.day);
}

bool Date::operator+(const int days_to_add) {
    // todo
    this->day += day;
}

Date & Date::operator=(const Date &date) = default;
