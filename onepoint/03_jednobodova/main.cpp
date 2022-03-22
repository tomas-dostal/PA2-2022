#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
using namespace std;

class CTimeTester;
#endif /* __PROGTEST__ */

class CTime
{

protected:
    int m_Minute{};
    int m_Second{};
    int m_Hour{};
public:
    // constructor, destructor
    CTime(int hour, int minute, int second);
    CTime(int hour, int minute);
    CTime();

    int getHour() const {return m_Hour;};
    int getMinute() const {return m_Minute;};
    int getSecond() const{return m_Second;};

    ~CTime()= default;
    CTime & operator =  ( const CTime & x );

    // comparison operators

    bool operator < (const CTime &other) const;
    bool operator <= (const CTime &other) const;
    bool operator > (const CTime &other) const;
    bool operator >= (const CTime &other) const;
    bool operator == (const CTime &other) const;
    bool operator != (const CTime &other) const;

    // arithmetic operators

    CTime operator + (int seconds) const; // jj, protoze nemuzu upravovat ten objekt, je to obyc plus
    friend CTime operator +  (const int & a, const CTime & b );
    CTime operator - ( int seconds) const;

    CTime & operator +=  (const CTime & x); // treba tohle?
    CTime & operator +=  (const int addSeconds);
    CTime & operator -=  (const int substractSeconds);

    // operator-
    // Umožní odečíst od sebe dva objekty typu CTime. Výsledek je minimální počet
    // sekund, který potřebujeme přičíst k jednomu z předaných časů, abychom získali
    // čas druhý.

    int operator - (const CTime &other) const;
    //friend CTime operator -  (const int & a, const CTime & b );

    // prefix
    CTime& operator++();
    CTime operator++(int);

    CTime& operator--();
    CTime operator--(int);

     // in/out operators
    friend std::ostream & operator << ( std::ostream & os, const CTime & x);
    friend std::istream & operator >> ( std::istream & is, CTime & x);

    friend class ::CTimeTester;

private:
    int toSeconds() const;
};

bool checkIfValid(int hour, int minute, int second) {
    if(!(hour <= 23 && hour >= 0
         && minute <= 59 && minute >= 0
         && second <= 59 && second >= 0 ))
        throw invalid_argument("Hour / minute / second not valid");
    return true;
}

CTime::CTime(int hour, int minute) {
    if(checkIfValid(hour, minute, 0)) {
        m_Hour = hour;
        m_Minute = minute;
        m_Second = 0;
    }
}

CTime::CTime(int hour, int minute, int second) {
    if(checkIfValid(hour, minute, second)) {
        m_Hour = hour;
        m_Minute = minute;
        m_Second = second;
    }
}
CTime::CTime() {
    m_Hour = 0;
    m_Minute = 0;
    m_Second = 0;
}

CTime &CTime::operator += (const CTime &x) {
    *this = (*this + x.toSeconds());
    return *this;
}

CTime &CTime::operator = (const CTime &x) {
    if ( &x != this ){
        this->m_Hour = x.m_Hour;
        this->m_Minute = x.m_Minute;
        this->m_Second = x.m_Second;
    }
    return *this;
}

bool CTime::operator > (const CTime &other) const {
    return !(*this < other) && !(*this == other);
}

bool CTime::operator >= (const CTime &other) const {
    return *this > other || *this == other;
}

bool CTime::operator < (const CTime &other) const {
    return tie( this->m_Hour,
                this->m_Minute,
                this->m_Second
    )
           < tie( other.m_Hour,
                  other.m_Minute,
                  other.m_Second
    );
}

bool CTime::operator == (const CTime &other) const {
    return tie( this->m_Hour,
                this->m_Minute,
                this->m_Second
    )
           == tie( other.m_Hour,
                   other.m_Minute,
                   other.m_Second
    );
}

bool CTime::operator <= (const CTime &other) const {
    return *this < other || *this == other;
}

bool CTime::operator != (const CTime &other) const {
    return !(*this == other);
}

CTime CTime::operator + (const int addSeconds) const {
    //  CTime::operator-(CTime &, int) mismatch r='15:59:07', s='-8:00:-53'
    int seconds = this->toSeconds()
                  + addSeconds;
    seconds = seconds % (60*60*24);
    // time = 0:00:00, add -1 second -> 23:59:59
    if(seconds < 0){
        seconds = ((60*60*24) + seconds) % (60*60*24) ;
    }
    seconds = seconds % (60*60*24);
    int h = (seconds - (seconds % 3600)) / 3600;
    h = h % 24;

    // Jako validní akceptujte hodiny od 0 do 23, minuty a sekundy od 0 do 59.
    // Předchozí bod aplikujte i při výpočtech. Pokud by v rámci výpočtu došlo
    // k přetečení / podtečení času do dalšího / předchozího dne, uvažujte výsledek modulo 24 hodin.

    seconds -= h * 3600;
    int m = (seconds - (seconds % 60)) / 60;
    seconds -= m * 60;
    m = m % 60;

    CTime c = CTime();
    c.m_Second = seconds;
    c.m_Minute = m;
    c.m_Hour = h;


    // CTime result = CTime(h, m, seconds); // tady tohle je legit? takhle to vratit?
    return c; // CTime(h, m, seconds);
} //  Test 'Test aritmetickych operaci': Program provedl neplatnou operaci a byl ukončen (Segmentation fault/Bus error/Memory limit exceeded/Stack limit exceeded)
// jedine nejaky Segmentation fault
// nekde beztak nejaky debilni pointer nebo tak neco
 //  CTime::operator-(CTime &, int) mismatch r='15:59:07', s='-8:00:-53'
CTime CTime::operator-(const int seconds) const {
    return *this + (-seconds);
}

int CTime::toSeconds() const {
    return this->m_Hour * 3600
           + this->m_Minute * 60
           + this->m_Second;
}
std::ostream &operator<<(std::ostream &os, const CTime &x) {
    // format HH:MM:SS, one-digit hours filled with space
    return os   << std::setw(2) << std::setfill(' ') << x.getHour()
                << ":" << std::setw(2) << std::setfill('0') << x.getMinute()
                << ":" << std::setw(2) << std::setfill('0') << x.getSecond();
}

std::istream & operator >> (std::istream &is, CTime &x) {

    // Bude umožňovat načtení ze vstupního C++ streamu, ignorujte počáteční bílé znaky.
    // V případě nevalidního vstupu, nastaví std::ios::failbit a původní objekt nemění.
    int hour, minute, second;
    char dot1, dot2;

    if(!(is >> std::skipws >> hour >> std::noskipws >> dot1 >> minute >> dot2 >> second)){
        is.setstate (ios::failbit);
        //throw std::invalid_argument("Invalid format / inputstream error!\n");
        return is;
    }
    if ( ! is . eof () )
    {
        is.setstate (ios::failbit);
        //throw std::invalid_argument("Something is remaining after input!\n");
        return is;

    }

    // check input format
    if (dot1 != ':' || dot2 != ':' ) {
        is.setstate (ios::failbit);
        //throw std::invalid_argument("Wrong time format!\n");
        return is;

    }

    try {
        if(checkIfValid(hour, minute, second)){
            x.m_Hour = hour;
            x.m_Minute = minute;
            x.m_Second = second;
        }

    }
    catch (std::invalid_argument const&){
        is.setstate (ios::failbit);
    }
    return is;
}

//template<typename A, typename B>
//bool operator==(const A &, const B &) { A == B; }

int CTime::operator-(const CTime &other) const {
    // Výsledek je minimální počet sekund, který potřebujeme přičíst
    // k jednomu z předaných časů, abychom získali čas druhý

    // 00:00:00 - 23:59:59
    int clockWise = abs(this->toSeconds() - other.toSeconds());               // 23:59:59
    int counterClockWise = 24*60*60 - abs(this->toSeconds() - other.toSeconds()); // 1

    if(clockWise < counterClockWise)
        return clockWise;
    return counterClockWise;
}

// pre-increment, return *this by reference
CTime &CTime::operator++() {
    // implement increment logic on this instance, return reference to it.
    *this += CTime(0,0,1);
    return *this;
}

// post-increment, return unmodified copy by value
CTime CTime::operator++(int) {
    CTime copy = CTime(this->m_Hour, this->m_Minute, this->m_Second);
    //CTime copy(*this);
    //CTime tmp(this->m_Hour, this->m_Minute, this->m_Second);
    ++(*this); // prefix-increment this instance
    return copy;   // return value before increment
}

// pre-increment, return *this by reference
CTime &CTime::operator--() {
    *this = *this - 1;
    return *this;
}

// post-increment, return unmodified copy by value
CTime CTime::operator--(int) {
    CTime tmp(this->m_Hour, this->m_Minute, this->m_Second);
    operator--(); // prefix-increment this instance
    return tmp;   // return value before increment
}

CTime &CTime::operator+=(const int addSeconds) {
    return *this = (operator+(addSeconds));
}

CTime &CTime::operator-=(const int substractSeconds) {
    return *this = (operator-(substractSeconds));
}
CTime operator+(const int &a, const CTime &b) {
    return b + a;
}
//CTime operator-(const int &a, const CTime &b) {
//    return b - a;
//}


#ifndef __PROGTEST__
struct CTimeTester
{
    static bool test ( const CTime & time, int hour, int minute, int second )
    {
        return time.m_Hour == hour
               && time.m_Minute == minute
               && time.m_Second == second;
    }
};


#include <cassert>
#include <sstream>

int main ()
{
    CTime atZijeProgtest {0, 59, 00};
    atZijeProgtest -= 8*60*60 + 3*24*60*60;
    assert( CTimeTester::test( atZijeProgtest, 16, 59, 0 ) );
    CTime g;
    std::istringstream validInput { "         \n 3:30:00" };
    assert( static_cast<bool>( validInput >> g ) );
    assert( CTimeTester::test( g, 3, 30, 0 ) );

    CTime e;
    std::istringstream invalidInput { "         \n 13:  30:00" };
    assert( static_cast<bool>(invalidInput >> e) == false);

    //assert(!static_cast<bool>( invalidInput >> e ));
    assert( CTimeTester::test( e, 0, 0, 0 ) );
    CTime f;

    std::istringstream invalidInput2 { "         \n 13:30:00 " };
    assert(static_cast<bool>(invalidInput2 >> f )== false);

    CTime fg;

    std::istringstream invalidInput3 { "         \n 13:30:00\n" };
    assert(static_cast<bool>(invalidInput3 >> fg)== false);
    assert( CTimeTester::test( fg , 0, 0, 0 ) );

    CTime ggg;

    std::istringstream invalidInput4 { " 12 : 45 : 42 " };
    assert(static_cast<bool>( invalidInput4 >> ggg)== false);
    assert( CTimeTester::test( ggg , 0, 0, 0 ) );

    CTime gggg;

    std::istringstream invalidInput5 { "1:   23:\t45 " };
    assert(static_cast<bool>(invalidInput5 >> gggg)== false);
    assert( CTimeTester::test( gggg , 0, 0, 0 ) );

    CTime ggggf;

    std::istringstream invalidInput24 { "5:05:" };
    assert(static_cast<bool>(invalidInput24 >> gggg)== false);
    assert( CTimeTester::test( ggggf , 0, 0, 0 ) );

    CTime ggggg;

    std::istringstream invalidInput6 { "1:23" };
    assert(static_cast<bool>(invalidInput6 >> ggggg)== false);
    assert( CTimeTester::test( ggggg , 0, 0, 0 ) );

    CTime w { 12, 30 };
    CTime q { 0, 30 };
    CTime er = q+=w;
    assert( CTimeTester::test( er, 13, 00, 0 ) );


    CTime a { 12, 30 };
    assert( CTimeTester::test( a, 12, 30, 0 ) );

    CTime b;
    std::istringstream input { "13:30:00" };
    assert( static_cast<bool>( input >> b ) );
    assert( CTimeTester::test( b, 13, 30, 0 ) );

    assert( b - a == 3600 );

    assert( CTimeTester::test( a + 60, 12, 31, 0 ) );
    assert( CTimeTester::test( a - 60, 12, 29, 0 ) );

    assert( a < b );
    assert( a <= b );
    assert( a != b );
    assert( !( a > b ) );
    assert( !( a >= b ) );
    assert( !( a == b ) );

    while ( ++a != b );
    assert( a == b );

    std::ostringstream output;
    assert( static_cast<bool>( output << a ) );
    assert( output.str() == "13:30:00" );

    assert( a++ == b++ );
    assert( a == b );

    assert( --a == --b );
    assert( a == b );

    assert( a-- == b-- );
    assert( a == b );

    CTime c { 12, 00 };
    CTime d { 11, 59 , 59};
    CTime de { 0, 0 , 0};
    c == (d++);
    --d;
    //assert( c == (d + 1) );
    c--;
    assert( c == d );


    CTime almost { 23, 59 , 59};
    CTime midnight { 0, 0 , 0};

    assert(almost - midnight == midnight - almost);
    assert(almost - midnight == 1);

    //almost-=-2;
    //assert(almost == ++midnight);

    CTime fuuuu { 23, 59 , 59};
    CTime progtest { 0, 0 , 0};
    assert((fuuuu - progtest) == 1);

    // Zkus si to rozbít nějakýma mezníma assertama,
    // tzn. podtéct do předchozího dne, přetéct do dalšího, etc

    // podtect do predchoziho dne
    assert(fuuuu == progtest - 1);
    fuuuu += 2;
    progtest += 1;
    assert(fuuuu == progtest);


    CTime progtest2 { 0, 0 , 0};

    CTime fff { 15, 0, 0 };
    cout << (fff + 5) << endl;
    cout << (5 + fff ) << endl;
    cout << (fff - 5) << endl;
    cout << progtest2 - 5 << endl;
    // << 5 - fff << endl;

    cout << "[akjsdfljasd" << endl;
    cout << progtest2-- << endl;
    cout << --progtest2 << endl;
    cout << progtest2++ << endl;
    cout << ++progtest2 << endl;

    //cout << *progtest + *progtest2 << endl;

    return 0;
}
#endif /* __PROGTEST__ */
