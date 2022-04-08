#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>

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
    CDate(const CDate &d);

    explicit CDate(int days);

    CDate(int year, int month, int day);

    bool is_valid(int day, int month, int year);

    friend std::ostream &operator<<(std::ostream &os, const CDate &d);

    CDate &operator=(const CDate &x);

    bool operator==(const CDate &b) const;

    bool operator!=(const CDate &b) const;

    bool operator<(const CDate &b) const;

    bool operator>(const CDate &b) const;

    bool operator<=(const CDate &b) const;

    bool operator>=(const CDate &b) const;

private:
    int to_days() const;

    bool _is_leap_year(int year) const;

    bool _is_valid_day(const int &day, const int &month, const int &year) const;

    static bool _is_valid_month(const int &month) { return month > 0 && month <= 12; };

    static bool _is_valid_year(const int &year) { return year >= 2000 && year <= 2030; };

    int _how_many_days(const int &month, const int &year) const;

    CDate days_to_date(int days);

    int day, month, year;

};

bool CDate::_is_valid_day(const int &day, const int &month, const int &year) const {
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

int CDate::_how_many_days(const int &month, const int &year) const {
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
    // tm {
    //	int	tm_sec;		/* seconds after the minute [0-60] */
    //	int	tm_min;		/* minutes after the hour [0-59] */
    //	int	tm_hour;	/* hours since midnight [0-23] */
    //	int	tm_mday;	/* day of the month [1-31] */
    //	int	tm_mon;		/* months since January [0-11] */
    //	int	tm_year;	/* years since 1900 */
    //	int	tm_wday;	/* days since Sunday [0-6] */
    //	int	tm_yday;	/* days since January 1 [0-365] */
    //	int	tm_isdst;	/* Daylight Savings Time flag */
    //	long	tm_gmtoff;	/* offset from UTC in seconds */
    //	char	*tm_zone;	/* timezone abbreviation */
    // 2.1.2000 was sunday

    return os << std::setfill('0') << std::setw(4) << md.year << "-"
              << std::setfill('0') << std::setw(2) << md.month << "-"
              << std::setfill('0') << std::setw(2) << md.day;
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

CDate CDate::days_to_date(int days) {
    int y = 2000;
    int m = 1;
    int d = 1;

    while (days >= (_is_leap_year(y) ? 366 : 365)) {
        days -= _is_leap_year(y) ? 366 : 365;
        y++;
    }
    // the rest, try to do some magic with months
    while (days >= _how_many_days(m, y)) {
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

    if (year % 400 == 0)
        return true;
    else if (year % 100 == 0)
        return false;
    else if (year % 4 == 0)
        return true;
    return false;
}

////////////////// Constructors //////////////////

CDate::CDate(int days) {
    *this = this->days_to_date(days++);
}

CDate::CDate(const CDate &d) {
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

bool CDate::operator<(const CDate &b) const {
    return std::tie(this->year, this->month, this->day) < std::tie(b.year, b.month, b.day);
}

bool CDate::operator!=(const CDate &b) const {
    return !(*this == b);
}

bool CDate::operator==(const CDate &b) const {
    return std::tie(this->year, this->month, this->day) == std::tie(b.year, b.month, b.day);
}

bool CDate::operator>(const CDate &b) const {
    return !(*this < b) && (*this != b);
}

CDate &CDate::operator=(const CDate &x) = default;


////////////////////////////////////////////////////////////////////

class CDatePairComparatorLower {
public:
    bool operator()(const std::shared_ptr<std::pair<CDate, int>> &a,
                    const std::shared_ptr<std::pair<CDate, int>> &b) const {
        return a->first < b->first;
    }
};

class CDatePairComparatorLowerDate {
public:
    bool operator()(const std::shared_ptr<std::pair<CDate, int>> &a,
                    const CDate &b) const {
        return a->first < b;
    }
};

class CDatePairDateStringStuffComparatorLower {
public:
    bool operator()(const pair<CDate, pair<string, int>> &a,
                    const pair<CDate, string> &b) const {
        return std::tie(a.first, a.second.first) < std::tie(b.first, b.second);
    }
};

class CPairStringIntComparatorHigher {
public:
    bool operator()(const pair<string, int> &a,
                    const pair<string, int> &b) const {
        return a.second > b.second;
    }
};


class Item {
public:
    Item(const CDate &expiration, int quantity, const std::string &name);

    void add_new(const CDate &expiration, int quantity);

    int get(int quantity);

    std::string &get_name();

    int how_many_expired(const CDate &at);

    int available() const;

    friend std::ostream &operator<<(std::ostream &os, const Item &i);

private:
    int avail = 0;
    std::string name;
protected:
    deque<shared_ptr<std::pair<CDate, int>>> item_versions;
};

int Item::available() const {
    return this->avail;
}

int Item::get(const int quantity) {
    int requested_remaining = quantity;
    while (requested_remaining > 0) {
        // request not fullfilled
        if (item_versions.empty()) {
            return quantity - requested_remaining;
        }
        auto current = item_versions.begin();
        if (current->get()->second <= requested_remaining) {
            requested_remaining -= current->get()->second;
            this->avail -= current->get()->second;
            current->get()->second = 0;
            item_versions.pop_front();
        } else { // requested_remaining < current->second
            int tmp = requested_remaining;
            current->get()->second -= tmp;
            this->avail -= tmp;
            requested_remaining -= tmp;
        }
    }
    return quantity - requested_remaining;
}

void Item::add_new(const CDate &expiration, const int quantity) {
    int i = quantity;
    std::shared_ptr<std::pair<CDate, int>> tmp = make_shared<std::pair<CDate, int>>(
            std::pair<CDate, int>(expiration, i));
    CDatePairComparatorLower cmp;
    auto it = std::lower_bound(item_versions.begin(), item_versions.end(), tmp, cmp);
    if (!item_versions.empty() && it->get()->first == expiration) {
        it->get()->second += quantity;
    } else {
        item_versions.insert(it, tmp);
    }

}

Item::Item(const CDate &expiration, int quantity, const std::string &name) : name(name) {
    add_new(expiration, quantity);
    avail += quantity;
}

int Item::how_many_expired(const CDate &at) {
    CDatePairComparatorLowerDate cmp;
    auto it = std::lower_bound(item_versions.begin(), item_versions.end(), at, cmp);
    int iters;
    //if (!(!*it) && (*it)->first > at)
    //    iters = (it - item_versions.begin());
    //else
    iters = (it - item_versions.begin() - 1);

    int ret = 0;
    for (int i = 0; i <= iters; i++) {
        ret += item_versions[i].get()->second;
    }
    return ret;
}

std::ostream &operator<<(std::ostream &os, const Item &i) {
    for (auto x: i.item_versions) {
        std::cout << " item " << i.name << "  " << x.get()->first << " : " << x.get()->second << std::endl;
    }
    return os;
}

std::string &Item::get_name() {
    return this->name;
}


class CSupermarket {
public:
    //default constructor
    CSupermarket() = default;

    // store   ( name, expiryDate, count )
    CSupermarket &store(std::string name, CDate expiryDate, int count);

    // this is also a return parameter
    void sell(list<pair<string, int>> &shopping_list);

    // expired ( date ) const
    list<pair<string, int>> expired(const CDate &at) const;

    friend std::ostream &operator<<(std::ostream &os, CSupermarket &s);

private:

    shared_ptr<Item> findItemByName(const std::string &name);

    shared_ptr<Item> findItemByMisspelledName(const std::string &name);

    static bool compare_string(const std::string &target, const std::string &x, int allowed_errors);

    map<std::string, Item> stored_items;

};


CSupermarket &CSupermarket::store(std::string name, CDate expiryDate, int count) {

    auto it = stored_items.find(name);

    // not found
    //      map<std::string, Item> stored_items;
    if (it == stored_items.end()) {
        Item item = Item(expiryDate, count, name);
        stored_items.insert({name, item});
    } else {
        (*it).second.add_new(expiryDate, count);
    }
    return *this;
}

void CSupermarket::sell(list<pair<string, int>> &shopping_list) {
    list<pair<string, int>> res;
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "Selling from list of size " << shopping_list.size() << std::endl;
    for (auto item: shopping_list) {
        std::cout << item.first << ": " << item.second << std::endl;
    }

    for (auto shopping_list_item = shopping_list.begin(); shopping_list_item != shopping_list.end();) {

        shared_ptr<Item> tmp = findItemByName(shopping_list_item->first);
        if (tmp == nullptr) {
            tmp = findItemByMisspelledName(shopping_list_item->first);
            // pokud se nepodaří nalézt (tedy neexistuje žádné zboží lišící se právě v jednom znaku, nebo existuje
            // více různých zboží lišících se v jednom znaku, nebude se vydávat žádné zboží.

            // pokud neexistuje zboží přesně stejného jména, hledá se zboží, kde se název liší v jednom znaku
            // - překlepu (stále rozlišujeme malá/velká písmena). Pokud se podaří najít právě jedno takové zboží,
            // bude vybráno,
        }

        if (!tmp) {
            ++shopping_list_item;

        } else {
            int sold = tmp->get(shopping_list_item->second);

            if (sold == shopping_list_item->second)
                shopping_list.erase(shopping_list_item++);
            else {
                shopping_list_item->second -= sold;
                ++shopping_list_item;
            }

            // remove item from store if zero on stock
            if(tmp->available() == 0){
                this->stored_items.erase(tmp->get_name());
            }
        }

    }
}

shared_ptr<Item> CSupermarket::findItemByName(const std::string &name) {
    auto it = this->stored_items.find(name);
    if (it == stored_items.end())
        return nullptr;
    return make_shared<Item>((*it).second);
}

bool CSupermarket::compare_string(const std::string &target, const std::string &x, int allowed_errors) {
    if (abs((int) target.size() - (int) x.size()) > 0) {
        return false;
    }
    auto it_target = target.begin();
    auto it_x = x.begin();

    int errors = 0;
    for(int i = 0; i < max(target.size(), x.size()); i++){
        if (*it_target != *it_x)
            errors++;

        if (it_target != target.end()) {
            ++it_target;
        }
        if (it_x != x.end()) {
            ++it_x;
        }
        if (errors > allowed_errors)
            return false;
    }
    return true;

}

shared_ptr<Item> CSupermarket::findItemByMisspelledName(const string &name) {
    vector<Item> results;
    vector<string> names;
    for (auto item: this->stored_items) {
        if (compare_string(name, item.first, 1)) {
            results.push_back(item.second);
        }
    }
    if (results.size() > 1 || results.empty())
        return nullptr;
    return make_shared<Item>(*results.begin());
}

list<pair<string, int>> CSupermarket::expired(const CDate &at) const {
    //CDatePairDateStringStuffComparatorLower cmp;
    list<pair<string, int>> result;

    for (auto item: this->stored_items) {
        int expired = item.second.how_many_expired(at);
        if (expired > 0) {
            // todo insert by date
            //auto it = std::lower_bound(result.begin(), result.end(), std::pair<CDate, std::string>(at, item.first), cmp);
            // pair<CDate, pair<string, int>>
            //result.insert(it, pair<CDate, pair<string, int>>(at, pair<string, int>(item.first, expired)));
            result.emplace_back(pair<string, int>(item.first, expired));
        }
    }

    CPairStringIntComparatorHigher cmp2;
    result.sort(cmp2);
    return result;

}

std::ostream &operator<<(std::ostream &os, CSupermarket &s) {
    for (auto const &keyValue: s.stored_items) {
        std::cout << keyValue.first << " : " << std::endl;
        std::cout << keyValue.second; // Value
    }
    return os;
}

#ifndef __PROGTEST__

int main(void) {
    CSupermarket s;
    s.store("bread", CDate(2016, 4, 30), 100)
            .store("butter", CDate(2016, 5, 10), 10)
            .store("beer", CDate(2016, 8, 10), 50)
            .store("bread", CDate(2016, 4, 25), 100)
            .store("okey", CDate(2016, 7, 18), 5);
    std::cout << s << std::endl << std::endl;
    list<pair<string, int> > l0 = s.expired(CDate(2018, 4, 30));
    assert (l0.size() == 4);
    assert ((l0 == list<pair<string, int> >{{"bread",  200},
                                            {"beer",   50},
                                            {"butter", 10},
                                            {"okey",   5}}));
    list<pair<string, int> > l1{{"bread",  2},
                                {"Coke",   5},
                                {"butter", 20}};
    s.sell(l1);
    std::cout << s << std::endl << std::endl;
    assert (l1.size() == 2);
    list<pair<string, int> > l0_again = s.expired(CDate(2018, 4, 30));
    assert ((l0_again == list<pair<string, int> >{{"bread", 198},
                                                  {"beer",  50},
                                                  {"okey",  5}}));


    assert ((l1 == list<pair<string, int> >{{"Coke",   5},
                                            {"butter", 10}}));

    list<pair<string, int> > l2 = s.expired(CDate(2016, 4, 30));
    assert (l2.size() == 1);
    assert ((l2 == list<pair<string, int> >{{"bread", 98}}));

    list<pair<string, int> > l3 = s.expired(CDate(2016, 5, 20));
    assert (l3.size() == 1);
    assert ((l3 == list<pair<string, int> >{{"bread", 198}}));

    list<pair<string, int> > l4{{"bread", 105}};
    s.sell(l4);
    assert (l4.size() == 0);
    assert ((l4 == list<pair<string, int> >{}));

    list<pair<string, int> > l5 = s.expired(CDate(2017, 1, 1));
    assert (l5.size() == 3);
    assert ((l5 == list<pair<string, int> >{{"bread", 93},
                                            {"beer",  50},
                                            {"okey",  5}}));

    s.store("Coke", CDate(2016, 12, 31), 10);

    list<pair<string, int> > l6{{"Cake",  1},
                                {"Coke",  1},
                                {"cake",  1},
                                {"coke",  1},
                                {"cuke",  1},
                                {"Cokes", 1}};
    s.sell(l6);
    assert (l6.size() == 3);
    assert ((l6 == list<pair<string, int> >{{"cake",  1},
                                            {"cuke",  1},
                                            {"Cokes", 1}}));

    list<pair<string, int> > l7 = s.expired(CDate(2017, 1, 1));
    assert (l7.size() == 4);
    assert ((l7 == list<pair<string, int> >{{"bread", 93},
                                            {"beer",  50},
                                            {"Coke",  7},
                                            {"okey",  5}}));

    s.store("cake", CDate(2016, 11, 1), 5);

    list<pair<string, int> > l8{{"Cake", 1},
                                {"Coke", 1},
                                {"cake", 1},
                                {"coke", 1},
                                {"cuke", 1}};
    s.sell(l8);
    assert (l8.size() == 2);
    assert ((l8 == list<pair<string, int> >{{"Cake", 1},
                                            {"coke", 1}}));

    list<pair<string, int> > l9 = s.expired(CDate(2017, 1, 1));
    assert (l9.size() == 5);
    assert ((l9 == list<pair<string, int> >{{"bread", 93},
                                            {"beer",  50},
                                            {"Coke",  6},
                                            {"okey",  5},
                                            {"cake",  3}}));

    list<pair<string, int> > l10{{"cake", 15},
                                 {"Cake", 2}};
    s.sell(l10);
    assert (l10.size() == 2);
    assert ((l10 == list<pair<string, int> >{{"cake", 12},
                                             {"Cake", 2}}));

    list<pair<string, int> > l11 = s.expired(CDate(2017, 1, 1));
    assert (l11.size() == 4);
    assert ((l11 == list<pair<string, int> >{{"bread", 93},
                                             {"beer",  50},
                                             {"Coke",  6},
                                             {"okey",  5}}));

    list<pair<string, int> > l12{{"Cake", 4}};
    s.sell(l12);
    assert (l12.size() == 0);
    assert ((l12 == list<pair<string, int> >{}));

    list<pair<string, int> > l13 = s.expired(CDate(2017, 1, 1));
    assert (l13.size() == 4);
    assert ((l13 == list<pair<string, int> >{{"bread", 93},
                                             {"beer",  50},
                                             {"okey",  5},
                                             {"Coke",  2}}));

    list<pair<string, int> > l14{{"Beer", 20},
                                 {"Coke", 1},
                                 {"bear", 25},
                                 {"beer", 10}};
    s.sell(l14);
    assert (l14.size() == 1);
    assert ((l14 == list<pair<string, int> >{{"beer", 5}}));

    s.store("ccccb", CDate(2019, 3, 11), 100)
            .store("ccccd", CDate(2019, 6, 9), 100)
            .store("dcccc", CDate(2019, 2, 14), 100);

    list<pair<string, int> > l15{{"ccccc", 10}};
    s.sell(l15);
    assert (l15.size() == 1);
    assert ((l15 == list<pair<string, int> >{{"ccccc", 10}}));

    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
