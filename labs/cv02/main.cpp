#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ostream>
#include <tuple>

class MyDate
{
private:
    int _day, _month, _year;
    static bool _is_leap_year(int year){
        return false; // todo
    }
    static bool _is_valid_day(int day, int month, int year){
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
                return (_is_leap_year(year) and day <= 29) or (!_is_leap_year(year) and day <= 28) ;
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

        static bool _is_valid(int day, int month, int year){

        return (1 <= day && day <= 31) && (1 <= month && month <= 12) && (1900 <= year && year <= 2199) &&
                _is_valid_day(day, month, year);

    };

    MyDate(int day, int month, int year){
        if (_is_valid(day, month, year)) {
            this->_day = day;
            this->_month = month;
            this->_year = year;
        }
    };
    friend std::ostream & operator<<(std::ostream &os, const MyDate& md) {
        return os << md._year << "-" << md._month << "-" << md._day;
    }

public:
    explicit MyDate(const std::string& in) {

        std::istringstream sstream(in);

        // try to parse
        int yyyy, mm, dd; // , h, m, s;
        char d1, d2; // , d3, d4, d5;
        char dash = '-';
        // char colon = ':';
        std::string zone;

        // YYYY-MM-DD'T'hh:mm:ss'Z'
        if ((sstream >> yyyy >> d1 >> mm >> d2 >> dd)      // read all data //  >> d3 >> h >> d4 >> m >> d5 >> s >> zone
            && d1 == dash && d2 == dash)   // && d3 == 'T' && d4 == colon && d5 == colon &&  // verify that separators are correct
        {
            if (MyDate::_is_valid(dd, mm, yyyy)) {
                this->_day = dd;
                this->_month = mm;
                this->_year = yyyy;
            }
            else  throw std::invalid_argument("Invalid date " + in);

        } else throw std::invalid_argument("Invalid format " + in);

    };
    bool compare (const MyDate & date) const{
        return std::tie(this->_year, this->_month, this->_day) ==  std::tie(date._year, date._month, date._day);
    }
};



class DateManager{
private:
    std::vector<MyDate> dates;

public:
    bool load_from_file(const std::string& file);
    void print_all(){
        for (auto entity : dates) {
            std::cout << entity << std::endl;
        }
    }
};

bool DateManager::load_from_file(const std::string& file) {

    std::ifstream ifs;
    ifs.open ("dateList.txt", std::ifstream::in);
    // pridame kontrolu jestli mam stale pristup k souboru
    if (ifs.is_open())
    {
        std::string line;
        while (getline(ifs, line))
        {
            try {
                MyDate d = MyDate(line);
                dates.push_back(d);
            }
            catch (const std::invalid_argument& ia) {
                std::cerr << ia.what() << std::endl;
            }
        }
        ifs.close();
    }
    else {
        std::cerr << "Unable to read file" << std::endl;
        return false;
    }
    return true;
}

int main() {
    DateManager dm = DateManager();
    dm.load_from_file("dateString.txt");
    dm.print_all();
}
