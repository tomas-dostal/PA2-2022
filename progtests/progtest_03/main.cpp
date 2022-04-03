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
    CDate(const CDate & d);
    explicit CDate(int days);
    CDate(int year, int month, int day);

    bool is_valid(int day, int month, int year);

    friend std::ostream &operator << (std::ostream &os, const CDate &d);
    friend std::istream & operator >> (std::istream &is, CDate &d);

    CDate operator+(const int &d) const;

    CDate & operator++(); // { ++i; }
    CDate operator++(const int);  // { i++; }
                                        //     Check temp;
                                        // temp.i = i++;
                                        // return temp

    CDate operator-(const int &d){return *this + (-1 * d);};
    friend int operator - (const CDate & a, const CDate & b );


    CDate & operator--();
    CDate operator--(const int);

    CDate & operator =  ( const CDate & x );

    bool operator == (const CDate & b) const ;
    bool operator != (const CDate & b) const ;
    bool operator < (const CDate & b) const ;
    bool operator > (const CDate & b) const ;
    bool operator <= (const CDate & b) const ;
    bool operator >= (const CDate & b) const ;

private:
    int to_days() const;

    bool _is_leap_year(int year) const;

    bool _is_valid_day(const int & day, const int & month, const int & year) const;

    static bool _is_valid_month(const int & month) { return month > 0 && month <= 12; };

    static bool _is_valid_year(const int & year) { return year >= 2000 && year <= 2030; };

    int _how_many_days(const int & month, const int & year) const;

    CDate days_to_date(int days);

    int day, month, year;

};

bool CDate::_is_valid_day(const int & day, const int & month, const int & year) const{
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

int CDate::_how_many_days(const int & month, const int & year) const {
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
                return 31;
            case 2:
                if (_is_leap_year(year))
                    return 29;
                return 28;
            case 3:
                return 31;
            case 4:
                return 30;
            case 5:
                return 31;
            case 6:
                return 30;
            case 7:
                return 31;
            case 8:
                return 31;
            case 9:
                return 30;
            case 10:
                return 31;
            case 11:
                return 30;
            case 12:
                return 31;
            default:
                return 0;
        }
    }

    bool CDate::is_valid(int day, int month, int year) {

        return (1 <= day && day <= 31) && (1 <= month && month <= 12) && (1900 <= year && year <= 2199) &&
               _is_valid_day(day, month, year);

    }


std::ostream &operator<<(std::ostream &os, const CDate &md) {
    return os << std::setfill('0') << std::setw(4) << md.year << "-"
              << std::setfill('0') << std::setw(2) << md.month << "-"
              << std::setfill('0') << std::setw(2) << md.day;
     }


std::istream & operator >>(std::istream &is, CDate &d) {
    // operátorem >> lze přečíst instanci CDate ze zadaného streamu.
    // V povinných testech je na vstupu očekáváno datum v ISO formátu %Y-%m-%d.
    // Pokud se nepodaří datum načíst (formát, neplatné datum, ...),
    // operátor zajistí nastavení fail bitu a ponechá původní obsah instance CDate.
    // Stejně jako výstupní operátor, i vstup lze řídit pomocí manipulátoru date_format,
    // tato možnost je požadovaná v bonusovém testu.

    if (!is) {
        std::cerr << "Error opening istream";
        is.setstate(std::ios::failbit);
        return is;
    }

    char y1, y2, y3, y4, m1, m2, d1, d2;
    char del1, del2;
    std::string tmp;
    is >> tmp;
    std::istringstream iss(tmp);
    std::istringstream iss2(tmp);

    iss >> skipws >> y1 >> y2 >> y3 >> y4 >> del1 >> m1 >> m2 >> del2 >> d1 >> d2;

    if (!((del1 == '-'
          && del2 == '-')
          && (m1 == '0' || m1 == '1')
          && (d1 == '0' || d1 == '1' || d1 == '2' || d1 == '3')
          && (y1 == '2' && y2 == '0'))
          ) {
        is.setstate(std::ios::failbit);
        return is;
    }

    int year, month, day;
    iss2 >> skipws >> year >> del1 >> month >> del2 >> day;

    if (!d._is_valid_day(day, month, year)) {
        std::cerr << "_is_valid_day: " << year << "-" << month << "-" << day << std::endl;
        is.setstate(std::ios::failbit);
        return is;
    }
    d.year = year;
    d.month = month;
    d.day = day;
    return is;
}


int CDate::to_days() const {

    int days = 0; // 1.1.2020
    days = this->day - 1;

    // 24.02.2020
    for (int m = this->month - 1; m >= 1; m -= 1) {
        days += _how_many_days(m, year);
    }
    for (int i = year - 1; i >= 2000; i--) {
        if (_is_leap_year(i))
            days += 366;
        else days += 365;
    }

    return days;
}

CDate CDate::days_to_date(int days){
    int y = 2000;
    int m = 1;
    int d = 1;

    while(days >= (_is_leap_year(y) ? 366:365)){
        days -= _is_leap_year(y) ? 366:365;
        y++;
    }
    // the rest, try to do some magic with months
    while(days >= _how_many_days(m, y)){
        days -= _how_many_days(m, y);
        m++;
    }
    // days
    d += days;
    days = 0;
    CDate tmp = CDate(y, m, d);
    return tmp;

}

bool CDate::_is_leap_year(int year) const {
    // Při řešení úlohy narazíte na problematiku přestupných roků.
    // Rok je považován za přestupný, pokud je dělitelný 4 (např. 2020, 2024, ...).

    // Výjimku mají roky dělitelné 100, které nejsou přestupné (např. roky 1900 a 2100 nebyly/nebudou přestupné).
    // Výjimku z této výjimky mají roky dělitelné 400, které naopak jsou přestupné (např. rok 2000 byl přestupný).
    // Úlohu však zjednodušuje to, že jsou zadávané roky pouze z omezeného rozmezí 2000 - 2030.

    if(year % 400 == 0)
        return true;
    else if(year % 100 == 0)
        return false;
    else if(year % 4 == 0)
        return true;
    return false;
}

////////////////// Constructors //////////////////

CDate::CDate(int days) {
    *this = this->days_to_date(days++);
}

CDate::CDate(const CDate & d) {
    this->day = d.day;
    this->month = d.month;
    this->year = d.year;
}


CDate::CDate(int year, int month, int day) {
    if (is_valid(day, month, year)) {
        this->day = day;
        this->month = month;
        this->year = year;
    } else {
        std::cerr << "InvalidDateException year: " + to_string(year) + "month: " + to_string(month) + "day: " +
                     to_string(day) + " Is invalid";
        throw InvalidDateException();
    }

}


////////////////// Comparison operators //////////////////

bool CDate::operator>=(const CDate &b) const {
    return !(*this < b);
}
bool CDate::operator<=(const CDate &b) const {
    return *this == b || *this < b;
}

bool CDate::operator < (const CDate &b) const {
    return std::tie(this->year, this->month, this->day) < std::tie(b.year, b.month, b.day);
}

bool CDate::operator != (const CDate & b) const {
    return !(*this == b);
}

bool CDate::operator == (const CDate & b) const {
    return std::tie(this->year, this->month, this->day) == std::tie(b.year, b.month, b.day);
}

bool CDate::operator>(const CDate &b) const {
    return !(*this < b) && (*this != b);
}

////////////////// +- operators //////////////////

// post-increment, return unmodified copy by value
CDate CDate::operator++(const int) {
    CDate original = CDate(*this);
    *this = *this + 1;
    return original;
}

// post-increment, return unmodified copy by value
CDate CDate::operator--(const int) {
    CDate original = CDate(*this);
    *this = *this - 1;
    return original;
}


CDate & CDate::operator++() {
    *this = *this + 1;
    return *this;
}

CDate & CDate::operator--() {
    *this = *this - 1;
    return *this;
}

CDate CDate::operator+(const int &d) const {
    return CDate(this->to_days() + d);
}

int operator - (const CDate & a, const CDate & b ){
    return a.to_days() - b.to_days();
}

CDate &CDate::operator=(const CDate &x) = default;


#ifndef __PROGTEST__

int main(void) {
    ostringstream oss;
    istringstream iss;

    CDate my1(2000, 1, 1);
    my1++;
    oss.str("");
    oss << my1;
    assert (oss.str() == "2000-01-02");
    ++my1;
    oss.str("");
    oss << my1;
    assert (oss.str() == "2000-01-03");
    CDate my2(2000, 1, 1);
    my2 = my2 + 366;
    oss.str("");
    oss << my2;
    std::cerr << my2;
    assert (oss.str() == "2001-01-01");

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
    std::cerr << oss.str() << std::endl;
    assert (oss.str() == "2004-02-10");
    b = b - 2000;
    oss.str("");
    oss << b;
    assert (oss.str() == "2004-08-13");
    std::cerr<< b - a << std::endl;
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
