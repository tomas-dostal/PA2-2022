#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>
#include <cassert>
using namespace std;
#endif /* __PROGTEST__ */

class CTimeStamp
{
    private:
        int year, month, day, hour, minute, second;
    public:
        CTimeStamp(int _year, int _month, int _day, int _hour, int _minute, int _second ):
            year(_year),
            month(_month),
            day(_day),
            hour(_hour),
            minute(_minute),
            second(_second){
        };

    bool operator <= (const CTimeStamp &other) const {
        return tie( this->year,
                this->month,
                this->day,
                this->hour,
                this->minute,
                this->second
                )
                <= tie( other.year,
                        other.month,
                        other.day,
                        other.hour,
                        other.minute,
                        other.second
                );
    };
};
class CContact
{
private:
    CTimeStamp timeStamp;

        int phone1, phone2;

    public:
        CContact(CTimeStamp _timeStamp, int _phone1, int _phone2):
            timeStamp(_timeStamp),
            phone1(_phone1),
            phone2(_phone2){

        };
    bool isMatching(int phone){
        // Later I should ignore printing outputs like phone abc:abc
        if(phone == phone1 && phone == phone2){
            return false;
        }
        return phone == this->phone1 || phone == this->phone2;
    }
    int returnPeerPhone(int myPhone){
        if(myPhone == this->phone1)
            return this->phone2;
        else return  this->phone1;
    }

    bool isWithinInterval(CTimeStamp & from, CTimeStamp & to){
        return from <= this->timeStamp && this->timeStamp <= to;
    }
};

vector<int> addIfNotExists(vector<int> & list, int phone){
    if (std::count(list.begin(), list.end(), phone))
        return list;
    list.push_back(phone);
    return list;

}
class CEFaceMask
{
    private:
        vector<CContact> contacts;

    public:
        CEFaceMask &addContact(CContact newContact){
            this->contacts.push_back(newContact);
            return *this;
        }

        // Návratové hodnoty metod listContacts vrátí seznam telefonních čísel infikovaných kontaktů.
        // Zařídí, aby se ve výsledku čísla neopakovala, tedy ve výsledku potlačte druhý a další výskyt toho stejného čísla. Naví
        // Vyhledávací metodu lze zavolat s jedním parametrem (telefonním číslem nakaženého)
        vector<int> listContacts(int phone) const{
            vector<int> result;
                for(CContact contact: this->contacts) {
                    if(contact.isMatching(phone)){
                        addIfNotExists(result, contact.returnPeerPhone(phone));
                    }
                }
                return result;
        };

        // nebo s trojicí parametrů (telefonním číslem nakaženého, počátek a konec časového intervalu).
       vector<int> listContacts(int phone, CTimeStamp from, CTimeStamp to) const{

            vector<int> result;
            for(CContact contact: this->contacts) {
                if(contact.isMatching(phone) && contact.isWithinInterval(from, to)){
                    addIfNotExists(result, contact.returnPeerPhone(phone));
                }
            }
            return result;
       };

};
#ifndef __PROGTEST__
int main ()
{
    CEFaceMask test;

    test . addContact ( CContact ( CTimeStamp ( 2021, 1, 10, 12, 40, 10 ), 123456789, 999888777 ) );
    test . addContact ( CContact ( CTimeStamp ( 2021, 1, 12, 12, 40, 10 ), 123456789, 111222333 ) )
            . addContact ( CContact ( CTimeStamp ( 2021, 2, 5, 15, 30, 28 ), 999888777, 555000222 ) );
    test . addContact ( CContact ( CTimeStamp ( 2021, 2, 21, 18, 0, 0 ), 123456789, 999888777 ) );
    test . addContact ( CContact ( CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), 123456789, 456456456 ) );
    test . addContact ( CContact ( CTimeStamp ( 2021, 2, 1, 0, 0, 0 ), 123456789, 123456789 ) );
    assert ( test . listContacts ( 123456789 ) == (vector<int> {999888777, 111222333, 456456456}) );
    assert ( test . listContacts ( 999888777 ) == (vector<int> {123456789, 555000222}) );
    assert ( test . listContacts ( 191919191 ) == (vector<int> {}) );
    assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), CTimeStamp ( 2021, 2, 21, 18, 0, 0 ) ) == (vector<int> {999888777, 111222333, 456456456}) );
    assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 1 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) ) == (vector<int> {999888777, 111222333}) );
    assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 10, 12, 41, 9 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) ) == (vector<int> {111222333}) );
    return 0;
}
#endif /* __PROGTEST__ */