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

    CDate(int year, int month, int day);

    bool is_valid(int day, int month, int year);

    friend std::ostream &operator<<(std::ostream &os, const CDate &d);

    bool operator==(const CDate &b) const;

    bool operator!=(const CDate &b) const;

    bool operator<(const CDate &b) const;

    bool operator>(const CDate &b) const;

    bool operator<=(const CDate &b) const;

    bool operator>=(const CDate &b) const;

private:

    bool _is_leap_year(int year) const;

    bool _is_valid_day(const int &day, const int &month, const int &year) const;

    static bool _is_valid_month(const int &month) { return month > 0 && month <= 12; };

    static bool _is_valid_year(const int &year) { return true; };

    int _how_many_days(const int &month, const int &year) const;

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

bool CDate::is_valid(int day, int month, int year) {
    return true;
    //return (1 <= day && day <= 31) && (1 <= month && month <= 12) && /*(1900 <= year && year <= 2199) &&*/
    //       _is_valid_day(day, month, year);

}


std::ostream &operator<<(std::ostream &os, const CDate &md) {
    return os << std::setfill('0') << std::setw(4) << md.year << "-"
              << std::setfill('0') << std::setw(2) << md.month << "-"
              << std::setfill('0') << std::setw(2) << md.day;
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
        // request not fulfilled
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
    this->avail += quantity;
    auto it = std::lower_bound(item_versions.begin(), item_versions.end(), tmp, cmp);
    if (!item_versions.empty() && it != item_versions.end() && it->get()->first == expiration) {
        it->get()->second += quantity;
    } else {
        item_versions.insert(it, tmp);
    }

}

Item::Item(const CDate &expiration, int quantity, const std::string &name) : name(name) {
    add_new(expiration, quantity);
}

int Item::how_many_expired(const CDate &at) {
    CDatePairComparatorLower cmp;
    auto it = std::lower_bound(item_versions.begin(), item_versions.end(),
                               make_shared<pair<CDate, int>>(make_pair(at, 0)), cmp);

    int ret = 0;
    for (int i = 0; i <= (it - item_versions.begin() - 1); i++) {
        ret += item_versions[i].get()->second;
    }
    return ret;
}

std::ostream &operator<<(std::ostream &os, const Item &i) {
    for (auto x: i.item_versions) {
        os << " item " << i.name << "  " << x.get()->first << " : " << x.get()->second << std::endl;
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

    map<std::string, std::shared_ptr<Item>> stored_items;

};


CSupermarket &CSupermarket::store(std::string name, CDate expiryDate, int count) {
    if (count <= 0)
        return *this;

    auto it = stored_items.find(name);

    if (it == stored_items.end()) {
        stored_items.insert({name, make_shared<Item>(Item(expiryDate, count, name))});
    } else {
        (*it).second->add_new(expiryDate, count);
    }
    return *this;

}

void CSupermarket::sell(list<pair<string, int>> &shopping_list) {
    // std::cout << "----------------------------------------------" << std::endl;
    // std::cout << "Selling from list of size " << shopping_list.size() << std::endl;
    vector<shared_ptr<Item>> found;
    for (auto item: shopping_list) {
        // pokud se nepodaří nalézt (tedy neexistuje žádné zboží lišící se právě v jednom znaku, nebo existuje
        // více různých zboží lišících se v jednom znaku, nebude se vydávat žádné zboží.

        // pokud neexistuje zboží přesně stejného jména, hledá se zboží, kde se název liší v jednom znaku
        // - překlepu (stále rozlišujeme malá/velká písmena). Pokud se podaří najít právě jedno takové zboží,
        // bude vybráno,

        shared_ptr<Item> tmp = findItemByName(item.first);
        if (tmp == nullptr)
            tmp = findItemByMisspelledName(item.first);
        found.push_back(tmp);
    }
    std::vector<shared_ptr<Item>>::iterator found_iterator = std::begin(found);


    // now process what was
    for (auto shopping_list_item = shopping_list.begin(); shopping_list_item != shopping_list.end();) {
        if (!(*found_iterator)) {
            ++shopping_list_item;

        } else {
            int sold = (*found_iterator)->get(shopping_list_item->second);

            if (sold == shopping_list_item->second)
                shopping_list.erase(shopping_list_item++);
            else {
                shopping_list_item->second -= sold;
                ++shopping_list_item;
            }

            // remove item from store if zero on stock
            if ((*found_iterator)->available() == 0) {
                this->stored_items.erase((*found_iterator)->get_name());
            }
        }
        ++found_iterator;

    }
}

shared_ptr<Item> CSupermarket::findItemByName(const std::string &name) {
    auto it = this->stored_items.find(name);
    if (it == stored_items.end())
        return nullptr;
    return (*it).second;
}

bool CSupermarket::compare_string(const std::string &target, const std::string &x, int allowed_errors) {
    if (target.size() != x.size())
        return false;

    auto it_target = target.begin();
    auto it_x = x.begin();

    int errors = 0;
    for (long unsigned int i = 0; i < max(target.size(), x.size()); i++) {
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
    vector<shared_ptr<Item>> results;
    for (auto item: this->stored_items) {
        if (compare_string(name, item.first, 1))
            results.push_back(item.second);
    }
    if (results.size() > 1 || results.empty())
        return nullptr;
    return *results.begin();
}

list<pair<string, int>> CSupermarket::expired(const CDate &at) const {
    list<pair<string, int>> result;

    for (auto item: this->stored_items) {
        int expired = item.second->how_many_expired(at);
        if (expired > 0)
            result.emplace_back(pair<string, int>(item.first, expired));
    }

    CPairStringIntComparatorHigher cmp2;
    result.sort(cmp2);

    return result;

}

std::ostream &operator<<(std::ostream &os, CSupermarket &s) {
    for (auto const &key_value: s.stored_items) {
        os << key_value.first << " : " << std::endl;
        os << *(key_value.second);
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
    assert (l1.size() == 2);
    l0 = s.expired(CDate(2018, 4, 30));
    assert ((l0 == list<pair<string, int> >{{"bread", 198},
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

    l0 = s.expired(CDate(2030, 4, 30));
    assert ((l0 == list<pair<string, int> >{{"bread", 93},
                                            {"beer",  50},
                                            {"Coke",  10},
                                            {"okey",  5}}));
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

    l0 = s.expired(CDate(2030, 4, 30));
    assert ((l0 == list<pair<string, int> >{{"bread", 93},
                                            {"beer",  50},
                                            {"Coke",  7},
                                            {"okey",  5}}));


    list<pair<string, int> > l7 = s.expired(CDate(2017, 1, 1));
    assert (l7.size() == 4);
    assert ((l7 == list<pair<string, int> >{{"bread", 93},
                                            {"beer",  50},
                                            {"Coke",  7},
                                            {"okey",  5}}));

    s.store("cake", CDate(2016, 11, 1), 5);
    l0 = s.expired(CDate(2030, 4, 30));
    assert ((l0 == list<pair<string, int> >{{"bread", 93},
                                            {"beer",  50},
                                            {"Coke",  7},
                                            {"okey",  5},
                                            {"cake",  5}})
            ||
            (l0 == list<pair<string, int> >{{"bread", 93},
                                            {"beer",  50},
                                            {"Coke",  7},
                                            {"cake",  5},
                                            {"okey",  5}}));

    list<pair<string, int> > l8{{"Cake", 1}, //
                                {"Coke", 1},
                                {"cake", 1},
                                {"coke", 1}, //
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


    CSupermarket s2;
    s2.store("heroin", CDate(2020, 1, 1), 2);
    list<pair<string, int> > ls2_1{{"herOin", 20},
    };
    s2.sell(ls2_1);
    s2.sell(ls2_1);
    assert (ls2_1.size() == 1);
    assert ((ls2_1 == list<pair<string, int> >{{"herOin", 18}}));

    s2.store("heroin", CDate(2020, 1, 1), 2);
    s2.store("heroin", CDate(2019, 1, 1), 8);


    list<pair<string, int> > ls2_2{{"heroin", 11},
    };
    s2.sell(ls2_2);
    assert (ls2_2.size() == 1);
    assert ((ls2_2 == list<pair<string, int> >{{"heroin", 1}}));

    s2.store("heroin", CDate(2020, 1, 1), 0);

    s2.sell(ls2_2);
    assert (ls2_2.size() == 1);
    assert ((ls2_2 == list<pair<string, int> >{{"heroin", 1}}));

    s2.store("cannabis", CDate(1942, 1, 1), 0);
    list<pair<string, int> > ls2_3 = s2.expired(CDate(2400, 2, 29));
    assert (ls2_3.size() == 0);
    assert ((ls2_3 == list<pair<string, int> >{}));

    /////////////////////////////////////////////////////////////

    s2.store("fit", CDate(2020, 2, 1), 2);
    s2.store("fafit", CDate(2020, 5, 1), 1);
    s2.store("fail", CDate(2020, 1, 1), 10);

    list<pair<string, int> > ls2_expired = s2.expired(CDate(2400, 2, 29));
    assert (ls2_expired.size() == 3);
    assert ((ls2_expired == list<pair<string, int> >{{"fail",  10},
                                                     {"fit",   2},
                                                     {"fafit", 1}}));

    // erase last item of the shopping list
    list<pair<string, int> > ls2_5{{"fit",  1},
                                   {"fail", 1}};
    s2.sell(ls2_5);
    assert (ls2_5.size() == 0);
    assert ((ls2_5 == list<pair<string, int> >{}));

    ls2_expired = s2.expired(CDate(2400, 2, 29));
    assert (ls2_expired.size() == 3);
    assert ((ls2_expired == list<pair<string, int> >{{"fail",  9},
                                                     {"fafit", 1},
                                                     {"fit",   1}}));
    // erase first item of the shopping list

    list<pair<string, int> > ls2_6{{"fit", 1}};
    s2.sell(ls2_6);
    assert (ls2_6.size() == 0);
    assert ((ls2_6 == list<pair<string, int> >{}));

    ls2_expired = s2.expired(CDate(2400, 2, 29));
    assert (ls2_expired.size() == 2);
    assert ((ls2_expired == list<pair<string, int> >{{"fail",  9},
                                                     {"fafit", 1}}));

    s2.store("fit", CDate(2020, 5, 4), 2);

    // erase mid item of the shopping list

    list<pair<string, int> > ls2_7{{"fafit", 2}};
    s2.sell(ls2_7);
    assert (ls2_7.size() == 1);
    assert ((ls2_7 == list<pair<string, int> >{{"fafit", 1}}));

    s2.store("fafit", CDate(2020, 12, 4), 1);
    s2.sell(ls2_7);
    assert (ls2_7.size() == 0);
    assert ((ls2_7 == list<pair<string, int> >{}));


    //////////////////////// edge cases ///////////////////
    CSupermarket s3;
    list<pair<string, int> > ls3_1{{"fail", 20}};
    s3.sell(ls3_1);
    assert (ls3_1.size() == 1);
    assert ((ls3_1 == list<pair<string, int> >{{"fail", 20}}));

    ls3_1 = {{"fail", -20}};
    s3.sell(ls3_1);
    assert (ls3_1.size() == 1);
    assert ((ls3_1 == list<pair<string, int> >{{"fail", -20}}));

    s3.store("fail", CDate(2020, 5, 4), 123);
    ls3_1 = {{"fail", -20}};
    s3.sell(ls3_1);
    assert (ls3_1.size() == 1);
    assert ((ls3_1 == list<pair<string, int> >{{"fail", -20}}));

    ls3_1 = {{"", 1}};
    s3.sell(ls3_1);
    assert (ls3_1.size() == 1);
    assert ((ls3_1 == list<pair<string, int> >{{"", 1}}));

    ls3_1 = {{"", 0}};
    s3.sell(ls3_1);
    assert (ls3_1.size() == 1);
    assert ((ls3_1 == list<pair<string, int> >{{"", 0}}));

    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
