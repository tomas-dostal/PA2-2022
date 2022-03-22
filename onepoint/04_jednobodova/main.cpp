#ifndef __PROGTEST__
#include <cstring>
using namespace std;

class CLinkedSetTester;
#endif /* __PROGTEST__ */


class CLinkedSet
{
private:
    struct CNode
    {
        CNode * m_Next;

        const char * Value () const;

        const char * str;
    };

    CNode * m_Begin;
    CNode * m_Temp;
    size_t size = 0;

public:
    // default constructor
    CLinkedSet();

    // copy constructor
    CLinkedSet(const CLinkedSet &cLinkedSet);

    // operator=
    CLinkedSet & operator = ( const CLinkedSet & src );

    // destructor
    ~CLinkedSet();

    bool Insert ( const char * value );
    
    bool Remove ( const char * value );

    void Erase ( );

    bool Empty () const;

    size_t Size () const;

    bool Contains ( const char * value ) const;

    friend class ::CLinkedSetTester;

};



const char *CLinkedSet::CNode::Value() const {
    return nullptr;
}


CLinkedSet::CLinkedSet() {
    m_Begin = nullptr;
    m_Temp = nullptr;
}

CLinkedSet::CLinkedSet(const CLinkedSet &cLinkedSet) {
    CLinkedSet c = CLinkedSet();
    CNode * element = cLinkedSet.m_Begin;
    if(this->size != 0)
        this->Erase();
    while(element){
        char * string  = new char[strlen(element->str) + 1];
        strcpy(string, element->str);

        c.Insert(string);
        delete [] string;
        element = element->m_Next;

    }
    c.m_Temp = element;
    *this = c;
}

CLinkedSet &CLinkedSet::operator=(const CLinkedSet &src) {

    if ( &src != this ){
        this->Erase();
        CNode * c = src.m_Begin;
        while(c){
            char * string  = new char[strlen(c->str) + 1];
            strcpy(string, c->str);

            this->Insert(string);
            delete [] string;

            c = c->m_Next;
        }

    }
    return *this;
}

void CLinkedSet::Erase() {
    // first remove all the data and nodes
    CNode * current = this->m_Begin;
    if(!this->size)
        return;
    this->m_Temp = nullptr;
    this->size = 0;

    while(current) {
        CNode *tmp = current->m_Next;
        delete[] current->str;
        delete current;
        //this->m_Begin = tmp;

        current = tmp;
    }
    this->m_Temp = nullptr;
    this->m_Begin = nullptr;
}

CLinkedSet::~CLinkedSet() {
    // first remove all the data and nodes
    this->Erase();
    this->m_Begin = nullptr;

    //delete this;
}

bool CLinkedSet::Insert(const char *value) {

    CNode * n = new CNode;
    char * string  = new char[strlen(value) + 1];
    strcpy(string, value);
    n->str = string;
    n->m_Next = nullptr;
    // completely empty list
    if(this->size == 0 || !this->m_Begin){

        this->m_Begin = n;
        this->m_Temp = n;
        this->size = 1;
    }
    else {
        // find location for new node

        CNode * current = this->m_Begin;

        while(current){
            // reached the end, just append
           //if(current->m_Next == nullptr){
           //    current->m_Next = &n;
           //    this->m_Temp = &n;
           //    break;
           //}
           //else {
               // alredy exists
               if(strcmp(current->str, n->str) == 0){
                   return false;
               }
               else if (!current->m_Next || strcmp(n->str, current->str)  < 0)
                   if(!current->m_Next ||  strcmp(n->str, current->m_Next->str) > 0){
                       if(!current->m_Next) // if I am in the end, I should set tmp pointer to this
                       {
                           n->m_Next = nullptr;
                           this->m_Temp = n;
                       }
                           // position OK, append
                        // now I want to insert node n between nodes current and current.next
                        CNode * after = current->m_Next;

                        current->m_Next = n;
                        n->m_Next = after;
                        this->size++;
                        return true;
                   }
           //}
           // go to another string
            current = current->m_Next;
        }

    }
    return true;
}


bool CLinkedSet::Remove(const char *value) {
    CNode * previous = nullptr;
    CNode * current = this->m_Begin;

    while(current){
        if(strcmp(current->str, value) == 0){

            // found
        // if in the beginning
            if(!previous){
                CNode * following = current->m_Next;
                delete [] current->str;
                current->m_Next = nullptr;
                delete current;
                this->m_Begin = following;
            }
            // if in the end
            else if(current == this->m_Temp){
                delete [] current->str;
                current->m_Next = nullptr;
                delete current;
                previous->m_Next = nullptr;
                this->m_Temp = previous;
            }
            // somewhere in the middle
            else {
                CNode * following = current->m_Next;
                delete [] current->str;
                current->m_Next = nullptr;
                delete current;
                previous->m_Next = following;
            }

            // I should remove c string
            // I should remove allocated CNode
            this->size--;
            return true;

        }

        previous = current;
        current = current->m_Next;
    }
    return false;

}

bool CLinkedSet::Empty() const {
    return this->m_Begin == nullptr;
}

size_t CLinkedSet::Size() const {
    return this->size;
}

bool CLinkedSet::Contains(const char *value) const {
    CNode * current = this->m_Begin;

    while(current){
        if(strcmp(current->str, value) == 0)
            return true;
        current = current->m_Next;
    }
    return false;

}



#ifndef __PROGTEST__
#include <cassert>

struct CLinkedSetTester
{
    static void test0()
    {
        CLinkedSet x0;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        assert( !x0 . Empty() );
    }

    static void test1()
    {
        CLinkedSet x0;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        CLinkedSet x1 ( x0 );
        assert( x0 . Insert( "Vodickova Saskie" ) );
        assert( x1 . Insert( "Kadlecova Kvetslava" ) );
        assert( x0 . Size() == 3 );
        assert( x1 . Size() == 3 );
        assert( x0 . Contains( "Vodickova Saskie" ) );
        assert( !x1 . Contains( "Vodickova Saskie" ) );
        assert( !x0 . Contains( "Kadlecova Kvetslava" ) );
        assert( x1 . Contains( "Kadlecova Kvetslava" ) );
    }

    static void test2()
    {
        CLinkedSet x0;
        CLinkedSet x1;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        x1 = x0;
        assert( x0 . Insert( "Vodickova Saskie" ) );
        assert( x1 . Insert( "Kadlecova Kvetslava" ) );
        assert( x0 . Size() == 3 );
        assert( x1 . Size() == 3 );
        assert( x0 . Contains( "Vodickova Saskie" ) );
        assert( !x1 . Contains( "Vodickova Saskie" ) );
        assert( !x0 . Contains( "Kadlecova Kvetslava" ) );
        assert( x1 . Contains( "Kadlecova Kvetslava" ) );
    }

};

int main ()
{
    CLinkedSetTester::test0();
    CLinkedSetTester::test1();
    CLinkedSetTester::test2();
    return 0;
}
#endif /* __PROGTEST__ */
