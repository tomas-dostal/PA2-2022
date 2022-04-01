#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;
#endif /* __PROGTEST__ */

//=================================================================================================
// a dummy exception class, keep this implementation
class InvalidDateException : public invalid_argument {
public:
    InvalidDateException()
            : invalid_argument("invalid date or format") {
    }
};

//=================================================================================================
// date_format manipulator - a dummy implementation. Keep this code unless you implement your
// own working manipulator.
ios_base &( *date_format(const char *fmt))(ios_base &x) {
    return [](ios_base &ios) -> ios_base & { return ios; };
}

//=================================================================================================
class CDate {
public:
    CDate(int year, int month, int day, bool make_valid);

    CDate(int year, int month, int day);

    bool is_valid(int day, int month, int year);
    friend std::ostream &operator<<(std::ostream &os, const CDate &md);
    CDate operator + (const int & d);
private:
    bool _is_leap_year(int year);
    bool _is_valid_day(int day, int month, int year);
    bool _is_valid_month(int month){return month > 0 && month <= 12; };
    bool _is_valid_year(int year){return year >= 2000 && year <= 2030; };

    int day, month, year;

    int _get_extra_days_for_month(int day, int month, int year);
};


int CDate::_get_extra_days_for_month(int day, int month, int year) {
    //January – 31 days
    //February – 28 days in a common year and 29 days in leap years
    //March – 31 days
    //April – 30 days
    //May – 31 days
    //June – 30 days
    //July – 31 days
    //August – 31 days
    //September – 30 days
    //October – 31 days
    //November – 30 days
    //December – 31 days
    switch (month) {
        case 1:
            return day - 31;
        case 2:
            if(_is_leap_year(year))
                return day - 29;
            return day - 28;
        case 3:
            return day - 31;
        case 4:
            return day - 30;
        case 5:
            return day - 31;
        case 6:
            return day - 30;
        case 7:
            return day - 31;
        case 8:
            return day - 31;
        case 9:
            return day - 30;
        case 10:
            return day - 31;
        case 11:
            return day - 30;
        case 12:
            return day - 31;
        default:
            return 0;
}

bool CDate::_is_valid_day(int day, int month, int year) {
    //January – 31 days
    //February – 28 days in a common year and 29 days in leap years
    //March – 31 days
    //April – 30 days
    //May – 31 days
    //June – 30 days
    //July – 31 days
    //August – 31 days
    //September – 30 days
    //October – 31 days
    //November – 30 days
    //December – 31 days

    switch (month) {
        case 1:
            return day <= 31;
        case 2:
            return (_is_leap_year(year) and day <= 29) or (!_is_leap_year(year) and day <= 28);
        case 3:
            return day <= 31;
        case 4:
            return day <= 30;
        case 5:
            return day <= 31;
        case 6:
            return day <= 30;
        case 7:
            return day <= 31;
        case 8:
            return day <= 31;
        case 9:
            return day <= 30;
        case 10:
            return day <= 31;
        case 11:
            return day <= 30;
        case 12:
            return day <= 31;
        default:
            return false;
    }
}

bool CDate::is_valid(int day, int month, int year) {

    return (1 <= day && day <= 31) && (1 <= month && month <= 12) && (1900 <= year && year <= 2199) &&
           _is_valid_day(day, month, year);

}

CDate::CDate(int year, int month, int day) {
    if (is_valid(day, month, year)) {
        this->day = day;
        this->month = month;
        this->year = year;
    }
    else {
        std::cerr << "InvalidDateException year: " + to_string(year) + "month: " + to_string(month) + "day: " + to_string(day) + " Is invalid";
        throw InvalidDateException();
    }

}

std::ostream & operator<<(std::ostream &os, const CDate &md) {
    std::cout << std::format("{:04}", year) <<  "-" << std::format("{:02}", month) << "-" <<  std::format("{:02}", day);
    return os << md.year << "-" << md.month << "-" << md.day;
}

CDate CDate::operator+(const int &d) {
    return CDate(0, 0, 0);
}

CDate::CDate(int year, int month, int day, bool make_valid) {

    while(!is_valid(day, month, year)){
        if(!_is_valid_year(year)){
            std::cerr << "CDate: try to fix: Year " << year << " is out of range";
            throw InvalidDateException();
        }
        if(!_is_valid_month(month)){
            // month = 24
            if(month % 12 == 0 && (month / 12 > 1)){
                // year += 2-1
                // month = 12
                year += (month /12) - 1;
                month = 12;
            }
            else if(month % 12 != 0 && month > 12){
                // se zbytkem 25
                // rok += 2
                // mesic = month % 12;

                // (25-1)/12=2
                // 2 - 1
                year += ((month - month % 12) /12);
                month = month % 12;
            }
        }
        if(!_is_valid_day(day, month, year)){
            // 31.02.2021
            //January – 31 days
            //February – 28 days in a common year and 29 days in leap years
            //March – 31 days
            //April – 30 days
            //May – 31 days
            //June – 30 days
            //July – 31 days
            //August – 31 days
            //September – 30 days
            //October – 31 days
            //November – 30 days
            //December – 31 days

            int extra = _get_extra_days_for_month(day, month, year);
            if(extra > 0){
                month += 1;
                day - extra + 1;
            }
        }
            month += 1;
        }



    }
        if(!_is_valid_day(day, month, year)){
            if(!_is_valid_day(year, month + 1, 1){

        }
    }
}


#ifndef __PROGTEST__

int main(void) {
    ostringstream oss;
    istringstream iss;

    CDate a(2000, 1, 2);
    CDate b(2010, 2, 3);
    CDate c(2004, 2, 10);
    oss.str("");
    oss << a;
    assert (oss.str() == "2000-01-02");
    oss.str("");
    oss << b;
    assert (oss.str() == "2010-02-03");
    oss.str("");
    oss << c;
    assert (oss.str() == "2004-02-10");
    a = a + 1500;
    oss.str("");
    oss << a;
    assert (oss.str() == "2004-02-10");
    b = b - 2000;
    oss.str("");
    oss << b;
    assert (oss.str() == "2004-08-13");
    assert (b - a == 185);
    assert ((b == a) == false);
    assert ((b != a) == true);
    assert ((b <= a) == false);
    assert ((b < a) == false);
    assert ((b >= a) == true);
    assert ((b > a) == true);
    assert ((c == a) == true);
    assert ((c != a) == false);
    assert ((c <= a) == true);
    assert ((c < a) == false);
    assert ((c >= a) == true);
    assert ((c > a) == false);
    a = ++c;
    oss.str("");
    oss << a << " " << c;
    assert (oss.str() == "2004-02-11 2004-02-11");
    a = --c;
    oss.str("");
    oss << a << " " << c;
    assert (oss.str() == "2004-02-10 2004-02-10");
    a = c++;
    oss.str("");
    oss << a << " " << c;
    assert (oss.str() == "2004-02-10 2004-02-11");
    a = c--;
    oss.str("");
    oss << a << " " << c;
    assert (oss.str() == "2004-02-11 2004-02-10");
    iss.clear();
    iss.str("2015-09-03");
    assert ((iss >> a));
    oss.str("");
    oss << a;
    assert (oss.str() == "2015-09-03");
    a = a + 70;
    oss.str("");
    oss << a;
    assert (oss.str() == "2015-11-12");

    CDate d(2000, 1, 1);
    try {
        CDate e(2000, 32, 1);
        assert ("No exception thrown!" == nullptr);
    }
    catch (...) {
    }
    iss.clear();
    iss.str("2000-12-33");
    assert (!(iss >> d));
    oss.str("");
    oss << d;
    assert (oss.str() == "2000-01-01");
    iss.clear();
    iss.str("2000-11-31");
    assert (!(iss >> d));
    oss.str("");
    oss << d;
    assert (oss.str() == "2000-01-01");
    iss.clear();
    iss.str("2000-02-29");
    assert ((iss >> d));
    oss.str("");
    oss << d;
    assert (oss.str() == "2000-02-29");
    iss.clear();
    iss.str("2001-02-29");
    assert (!(iss >> d));
    oss.str("");
    oss << d;
    assert (oss.str() == "2000-02-29");

    //-----------------------------------------------------------------------------
    // bonus test examples
    //-----------------------------------------------------------------------------
    CDate f(2000, 5, 12);
    oss.str("");
    oss << f;
    assert (oss.str() == "2000-05-12");
    oss.str("");
    oss << date_format("%Y/%m/%d") << f;
    assert (oss.str() == "2000/05/12");
    oss.str("");
    oss << date_format("%d.%m.%Y") << f;
    assert (oss.str() == "12.05.2000");
    oss.str("");
    oss << date_format("%m/%d/%Y") << f;
    assert (oss.str() == "05/12/2000");
    oss.str("");
    oss << date_format("%Y%m%d") << f;
    assert (oss.str() == "20000512");
    oss.str("");
    oss << date_format("hello kitty") << f;
    assert (oss.str() == "hello kitty");
    oss.str("");
    oss << date_format("%d%d%d%d%d%d%m%m%m%Y%Y%Y%%%%%%%%%%") << f;
    assert (oss.str() == "121212121212050505200020002000%%%%%");
    oss.str("");
    oss << date_format("%Y-%m-%d") << f;
    assert (oss.str() == "2000-05-12");
    iss.clear();
    iss.str("2001-01-1");
    assert (!(iss >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2000-05-12");
    iss.clear();
    iss.str("2001-1-01");
    assert (!(iss >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2000-05-12");
    iss.clear();
    iss.str("2001-001-01");
    assert (!(iss >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2000-05-12");
    iss.clear();
    iss.str("2001-01-02");
    assert ((iss >> date_format("%Y-%m-%d") >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2001-01-02");
    iss.clear();
    iss.str("05.06.2003");
    assert ((iss >> date_format("%d.%m.%Y") >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2003-06-05");
    iss.clear();
    iss.str("07/08/2004");
    assert ((iss >> date_format("%m/%d/%Y") >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2004-07-08");
    iss.clear();
    iss.str("2002*03*04");
    assert ((iss >> date_format("%Y*%m*%d") >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2002-03-04");
    iss.clear();
    iss.str("C++09format10PA22006rulez");
    assert ((iss >> date_format("C++%mformat%dPA2%Yrulez") >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2006-09-10");
    iss.clear();
    iss.str("%12%13%2010%");
    assert ((iss >> date_format("%%%m%%%d%%%Y%%") >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2010-12-13");

    CDate g(2000, 6, 8);
    iss.clear();
    iss.str("2001-11-33");
    assert (!(iss >> date_format("%Y-%m-%d") >> g));
    oss.str("");
    oss << g;
    assert (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("29.02.2003");
    assert (!(iss >> date_format("%d.%m.%Y") >> g));
    oss.str("");
    oss << g;
    assert (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("14/02/2004");
    assert (!(iss >> date_format("%m/%d/%Y") >> g));
    oss.str("");
    oss << g;
    assert (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("2002-03");
    assert (!(iss >> date_format("%Y-%m") >> g));
    oss.str("");
    oss << g;
    assert (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("hello kitty");
    assert (!(iss >> date_format("hello kitty") >> g));
    oss.str("");
    oss << g;
    assert (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("2005-07-12-07");
    assert (!(iss >> date_format("%Y-%m-%d-%m") >> g));
    oss.str("");
    oss << g;
    assert (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("20000101");
    assert ((iss >> date_format("%Y%m%d") >> g));
    oss.str("");
    oss << g;
    assert (oss.str() == "2000-01-01");

    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
