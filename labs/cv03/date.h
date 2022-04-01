//
// Created by Tomas Dostal on 04.03.2022.
//

#ifndef CV03_DATE_H
#define CV03_DATE_H


class Date {
public:
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
    bool operator <= (const Date & date) const;
    bool operator + (const int days_to_add);
    Date & operator = (const Date & date);

protected:
    int day;
    int month;
    int year;

    friend class Vaccine;

};


#endif //CV03_DATE_H
