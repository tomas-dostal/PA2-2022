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
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
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
    bool operator < (const CTimeStamp &other) const;
    bool operator == (const CTimeStamp &other) const;
    bool operator <= (const CTimeStamp &other) const;

};
bool CTimeStamp::operator <= (const CTimeStamp &other) const {
    return *this < other || *this == other;
}
bool CTimeStamp::operator == (const CTimeStamp &other) const {
    return tie( this->year,
                this->month,
                this->day,
                this->hour,
                this->minute,
                this->second
    )
           == tie( other.year,
                   other.month,
                   other.day,
                   other.hour,
                   other.minute,
                   other.second
    );
}

bool CTimeStamp::operator < (const CTimeStamp &other) const {
    return tie( this->year,
                this->month,
                this->day,
                this->hour,
                this->minute,
                this->second
    )
           < tie( other.year,
                  other.month,
                  other.day,
                  other.hour,
                  other.minute,
                  other.second
    );
}
class CContact
{
private:
    CTimeStamp timeStamp;
    int phone1;
    int phone2;

public:
    CContact(CTimeStamp _timeStamp, int _phone1, int _phone2):
            timeStamp(_timeStamp),
            phone1(_phone1),
            phone2(_phone2){

    };
    
    int returnPeerPhone(int myPhone);

    // okay, progtest throws compilation error on this, let's to it by Java way and create getters
    // instead of friend class ::CEFaceMask;
    int getPhone1() const;
    int getPhone2() const;
    CTimeStamp getTimeStamp() const;
    
    bool operator < (const CContact &other) const;
    bool operator < (const CTimeStamp &other) const;
};

int CContact::getPhone1() const{
    return this->phone1;
}
int CContact::getPhone2() const {
    return this->phone2;
}

CTimeStamp CContact::getTimeStamp() const {
    return this->timeStamp;
}

int CContact::returnPeerPhone(int myPhone){
        if(myPhone == this->phone1)
            return this->phone2;
        else return  this->phone1;
}
bool CContact::operator<(const CContact &other) const {
    return this->timeStamp < other.timeStamp;
}
bool CContact::operator<(const CTimeStamp &other) const {
    return this->timeStamp < timeStamp;
}

class CSpreader{
public:
    int phone;
    int numberOfContacts;

    explicit CSpreader(int phone);
    bool operator < (const int &phone2) const;                // for comparing CSpreader < const int
    friend bool operator < (const int &phone, CSpreader & x); // for comparing const int < CSpreader
       
    void incrementNumberOfContacts();
};

bool CSpreader::operator<(const int &phone2) const {
    return this->phone < phone2;
}

CSpreader::CSpreader(int phone): phone(phone) {
    numberOfContacts = 1;
}

void CSpreader::incrementNumberOfContacts() {
    this->numberOfContacts++;
}

bool operator<(const int &phone, CSpreader &x) {
    return phone < x.phone;
}


class CEFaceMask
{
private:
    vector<CContact> contacts;
    vector<CSpreader> spreaders;

public:
    CEFaceMask();
    CEFaceMask &addContact(CContact newContact) {
        // according to the assignment I should ignore this input
        if(newContact.getPhone1() == newContact.getPhone2())
            return *this;

        auto it = std::lower_bound( contacts.begin(), contacts.end(), newContact); // lower_bound proper position in descending order
        contacts.insert( it, newContact ); // insert before iterator it
        
        // this is really not a elegant way to do that, but whatever, it is just a 1 point.
        if(!std::binary_search( spreaders.begin(), spreaders.end(),  newContact.getPhone1())) {

            auto it2 = std::lower_bound(spreaders.begin(), spreaders.end(), newContact.getPhone1());
            CSpreader c = CSpreader(newContact.getPhone1());
            spreaders.insert(it2, c);
        }
        else {
            auto it2 = std::lower_bound(spreaders.begin(), spreaders.end(), newContact.getPhone1());
            (*it2).incrementNumberOfContacts();
        }
        if(newContact.getPhone1() != newContact.getPhone2()){
            if(!std::binary_search( spreaders.begin(), spreaders.end(),  newContact.getPhone2())){
                auto it3 = std::lower_bound( spreaders.begin(), spreaders.end(), newContact.getPhone2());
                CSpreader c = CSpreader(newContact.getPhone2());
                spreaders.insert(it3, c);
            }
            else {
                auto it3 = std::lower_bound( spreaders.begin(), spreaders.end(), newContact.getPhone2());
                (*it3).incrementNumberOfContacts();
            }
        }
        return *this;
    }

    // default constructor
    // addContact ( contact )
    // getInfectedGroup ( phone, timeStamp )
    // getSuperSpreaders ()

    vector<int> getSuperSpreaders();
    vector<int>  getInfectedGroup ( int phone, CTimeStamp timeStamp);

    bool recursiveSearch(unsigned long position, int numberFrom, vector<int> &found, bool searchBackwards,
                    CTimeStamp hardFrom) const;
};

vector<int> CEFaceMask::getInfectedGroup(int phone, CTimeStamp timeStamp) {

    vector<int> results;

    unsigned long i = 0;
    for (; i < contacts.size(); ++i) {
        if(timeStamp <= contacts.at(i).getTimeStamp()
            && (contacts.at(i).getPhone1() == phone || contacts.at(i).getPhone2() == phone))
        {
            int phone2 = contacts.at(i).returnPeerPhone(phone);


            // now go back (there might be a group countact e.g. of 5 people at the time and I might caught just the
            results.push_back(min(phone, phone2));
            results.push_back(max(phone, phone2));
            recursiveSearch(i, phone, results, true, timeStamp);
            recursiveSearch(i, phone2, results, true, timeStamp);

            recursiveSearch(i + 1, phone, results, false, timeStamp);
            if(phone != phone2)
                recursiveSearch(i + 1, phone2, results, false, timeStamp);
            return results;
        }
    }
    // nothing really left, return just self.phone
    results.push_back(phone);
    return results;
}

bool CEFaceMask::recursiveSearch(unsigned long position, int numberFrom, vector<int> &found, bool searchBackwards, CTimeStamp hardFrom) const {
    while((!searchBackwards && ((position + 1) <= this->contacts.size())) // normal direction
        || (searchBackwards && ((position) >= 1 ))) { // reverse direction

        CContact c = this->contacts.at(position);

        /*cout << "Looking for contacts from infected: " << numberFrom << " from position " << position << " / " <<  this->contacts.size() << endl;
        for( auto f: found)
            cout << f << " " ;
        cout << endl; */

        if((!searchBackwards && (c.getPhone1() == numberFrom)) || (searchBackwards && (c.getPhone1() == numberFrom && c.getTimeStamp() == hardFrom))  ){
            // insert to the right position
            if(!std::binary_search( found.begin(), found.end(), c.getPhone2())) // lclass::CEFaceMaskower_bound proper position in descending order
            {
                auto it = std::lower_bound(found.begin(), found.end(),
                                           c.getPhone2()); // lower_bound proper position in descending order
                found.insert(it, c.getPhone2()); // insert before iterator it

            }
            if(searchBackwards)
                recursiveSearch(position - 1, c.getPhone2(), found, searchBackwards, hardFrom);
            else
                recursiveSearch(position + 1, c.getPhone2(), found, searchBackwards, hardFrom);
        }
        else if((!searchBackwards && (c.getPhone2() == numberFrom)) || (searchBackwards && (c.getPhone2() == numberFrom && c.getTimeStamp() == hardFrom)) ){
            if(!std::binary_search( found.begin(), found.end(), c.getPhone1())) // lower_bound proper position in descending order
            {
                // insert to the right position
                auto it = std::lower_bound(found.begin(), found.end(),
                                           c.getPhone1()); // lower_bound proper position in descending order
                //if(it == found.end())
                found.insert(it, c.getPhone1()); // insert before iterator it

            }
            if(searchBackwards)
                recursiveSearch(position - 1, c.getPhone1(), found, searchBackwards, hardFrom);
            else
                recursiveSearch(position + 1, c.getPhone1(), found, searchBackwards, hardFrom);
        }
        if(searchBackwards)
            position--;
        else position++;
    }
    return false;
}

vector<int> CEFaceMask::getSuperSpreaders() {

    // operator < is already ocupied for CSpreader (compared by phone number), need to do it this way :/
    int max = 0;
    for (CSpreader cSpreader: this->spreaders) {
        if(cSpreader.numberOfContacts > max)
            max = cSpreader.numberOfContacts;
    }

    vector<int> res;
    for (CSpreader cSpreader: this->spreaders) {
        if(cSpreader.numberOfContacts == max){
            auto it = std::lower_bound(res.begin(), res.end(), cSpreader.phone);
            res.insert(it, cSpreader.phone);
            //res.push_back(cSpreader.phone);
        }
    }
    return res;
}

CEFaceMask::CEFaceMask() {
    vector<CContact> c;
    this->contacts = c;
    vector<CSpreader> s;
    this->spreaders = s;
}


#ifndef __PROGTEST__
int main ()
{
   /*
  CEFaceMask test;

  test . addContact ( CContact ( CTimeStamp ( 2021, 1, 10, 12, 40, 10 ), 111111111, 222222222 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 1, 12, 12, 40, 10 ), 333333333, 222222222 ) )
       . addContact ( CContact ( CTimeStamp ( 2021, 2, 14, 15, 30, 28 ), 222222222, 444444444 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 2, 15, 18, 0, 0 ), 555555555, 444444444 ) );
  assert ( test . getSuperSpreaders ( ) == (vector<int> {222222222}) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 3, 20, 18, 0, 0 ), 444444444, 666666666 ) );
  assert ( test . getInfectedGroup ( 222222222, CTimeStamp ( 2021, 1, 11, 17, 17, 17 ) ) == (vector<int> {222222222, 333333333, 444444444, 555555555, 666666666}) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 3, 25, 0, 0, 0 ), 111111111, 666666666 ) );
  assert ( test . getSuperSpreaders ( ) == (vector<int> {222222222, 444444444}) );
  assert ( test . getInfectedGroup ( 111111111, CTimeStamp ( 2021, 1, 1, 0, 0, 0 ) ) == (vector<int> {111111111, 222222222, 333333333, 444444444, 555555555, 666666666}) );
  assert ( test . getInfectedGroup ( 111111111, CTimeStamp ( 2021, 3, 26, 0, 0, 0 ) ) == (vector<int> {111111111}) );
  assert ( test . getInfectedGroup ( 222222222, CTimeStamp ( 2021, 2, 15, 17, 17, 17 ) ) == (vector<int> {222222222}) );
  assert ( test . getInfectedGroup ( 222222222, CTimeStamp ( 2021, 1, 11, 17, 17, 17 ) ) == (vector<int> {111111111, 222222222, 333333333, 444444444, 555555555, 666666666}) );

  CEFaceMask test2;
    assert ( test2 . getInfectedGroup ( 111111111, CTimeStamp ( 2021, 1, 1, 0, 0, 0 ) ) == (vector<int> {111111111}) );

    test2 . addContact ( CContact ( CTimeStamp ( 2021, 1, 10, 12, 40, 10 ), 111111111, 222222222 ) );
    assert ( test2 . getInfectedGroup ( 111111111, CTimeStamp ( 2021, 1, 1, 0, 0, 0 ) ) == (vector<int> {111111111, 222222222}) );
    assert ( test2 . getInfectedGroup ( 111111111, CTimeStamp ( 2021, 1, 10, 12, 40, 10 ) ) == (vector<int> {111111111, 222222222}) );
    assert ( test2 . getInfectedGroup ( 111111111, CTimeStamp ( 2021, 1, 10, 12, 40, 11 ) ) == (vector<int> {111111111}) );
    test2 . addContact ( CContact ( CTimeStamp ( 2021, 1, 11, 12, 40, 10 ), 111111111, 333333333 ) );
    assert ( test2 . getInfectedGroup ( 111111111, CTimeStamp ( 2021, 1, 1, 0, 0, 0 ) ) == (vector<int> {111111111, 222222222, 333333333}) );
    assert ( test2 . getInfectedGroup ( 111111111, CTimeStamp ( 2021, 1, 11, 12, 40, 9 ) ) == (vector<int> {111111111,  333333333}) );
    assert ( test2 . getInfectedGroup ( 111111111, CTimeStamp ( 2021, 1, 12, 12, 40, 9 ) ) == (vector<int> {111111111}) );
    test2 . addContact ( CContact ( CTimeStamp ( 2000, 1, 11, 12, 40, 10 ), 111111111, 333333333 ) );
    assert ( test2 . getInfectedGroup ( 111111111, CTimeStamp ( 2021, 1, 12, 12, 40, 9 ) ) == (vector<int> {111111111}) );
    assert ( test2 . getInfectedGroup ( 111111111, CTimeStamp ( 1900, 1, 11, 12, 40, 9 ) ) == (vector<int> {111111111, 222222222, 333333333}) );
    // does not exists
    assert ( test2 . getInfectedGroup ( 999999999, CTimeStamp ( 1900, 1, 11, 12, 40, 9 ) ) == (vector<int> {999999999}) );


    CEFaceMask test3;
    test3 . addContact ( CContact ( CTimeStamp ( 2000, 1, 1, 0, 0, 1 ) , 111111111, 222222222 ));
    test3 . addContact ( CContact ( CTimeStamp ( 2000, 1, 1, 0, 0, 1 ) , 111111111, 333333333 ));
    test3 . addContact ( CContact ( CTimeStamp ( 2000, 1, 1, 0, 0, 1 ) , 111111111, 444444444 ));
    test3 . addContact ( CContact ( CTimeStamp ( 2000, 1, 1, 0, 0, 1 ) , 111111111, 555555555 ));

    assert ( test3 . getSuperSpreaders ( ) == (vector<int> {111111111}) );

    test3 . addContact ( CContact ( CTimeStamp ( 2000, 1, 1, 0, 0, 1 ) , 999999999, 888888888 ));

    assert ( test3 . getInfectedGroup ( 111111111, CTimeStamp ( 2000, 12, 1, 0, 0, 0 ) ) == (vector<int> {111111111}) );
    assert ( test3 . getInfectedGroup ( 555555555, CTimeStamp ( 2000, 1, 1, 0, 0, 1 ) ) == (vector<int> {111111111, 222222222, 333333333, 444444444, 555555555}) );
    assert ( test3 . getInfectedGroup ( 333333333, CTimeStamp ( 2000, 1, 1, 0, 0, 1 ) ) == (vector<int> {111111111, 222222222, 333333333, 444444444, 555555555}) );

    test3 . addContact ( CContact ( CTimeStamp ( 2000, 1, 1, 0, 0, 2 ) , 111111111, 555555555 ));
    assert ( test3 . getInfectedGroup ( 555555555, CTimeStamp ( 2000, 1, 1, 0, 0, 2 ) ) == (vector<int> {111111111, 555555555}) );

    test3 . addContact ( CContact ( CTimeStamp ( 2000, 1, 1, 0, 0, 3 ) , 333333333, 555555555 ));
*/
    CEFaceMask test4;
    test4 . addContact ( CContact ( CTimeStamp ( 2000, 1, 1, 1, 1, 1 ) , 555555555, 666666666 ));
    test4 . addContact ( CContact ( CTimeStamp ( 2000, 1, 1, 1, 1, 1 ) , 111111111, 222222222 ));
    test4 . addContact ( CContact ( CTimeStamp ( 2000, 1, 1, 1, 1, 1 ) , 333333333, 444444444 ));
    assert ( test4 . getSuperSpreaders ( ) == (vector<int> {111111111, 222222222, 333333333, 444444444, 555555555, 666666666}) );

    test4 . addContact ( CContact ( CTimeStamp ( 2000, 1, 1, 1, 1, 1 ) , 111111111, 555555555 ));
    assert ( test4 . getSuperSpreaders ( ) == (vector<int> {111111111, 555555555}) );

    return 0;
}
#endif /* __PROGTEST__ */
