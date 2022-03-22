#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdint>
#include <cctype>
#include <cassert>
using namespace std;
#endif /* __PROGTEST__ */

// This code works, it is tested and evaluated 1.0/1.0 points, although it is slow (unsorted linkedlist),
// binary tree would be much faster

template < class T >
class Node {
public:

    explicit Node(const T & x):
            next(nullptr),
            value(x) {};

    ~Node() {
        delete next;
    };

    Node * Clone() const {
        Node * n;
        n = new Node(value);
        if (next)
            n -> next = next -> Clone();
        return n;
    };

    bool isEqual(const T & x) {
        return !(this -> value < x) && !(x < this -> value);
    }

    Node * next;
    T value;
};

template < class T >
class CSet {
public:

    // konstruktor bez parametrů
    // Inicializuje prázdnou množinu.
    CSet() {
        root = nullptr;
        count = 0;
    };

    // kopírující konstruktor
    // Vytvoří hlubokou kopii.
    CSet(const CSet < T > & src) {
        if (src.root) // could be empty if there was no insert
            root = src.root -> Clone();
        else
            root = nullptr;

        count = src.count;
    };

    // operátor přiřazení
    // Odstraní aktuální množinu a vytvoří hlubokou kopii předané.
    CSet < T > & operator = (const CSet < T > & src) {
        // can not assign to self, I would modify it and delete data
        if (this == & src)
            return *this;
        delete root;
        // if there is a linked list to copy
        if (src.root)
            root = src.root -> Clone();
        else // no linked list to copy
            root = nullptr;
        count = src.count;
        return *this;

    };
    // destruktor
    // Uvolní alokované prostředky.
    ~CSet() {
        // works "recursivlely", if there is a child of root, once destructor of root is called a descructor
        // of Node (which deletes right and left node if exists) and so on till the end
        delete root;
    };

    // bool Insert ( Type )
    // Vloží do množiny objekt typu Type, vrací true pokud se vložení povede.
    // Pokud již v množině objekt je, vrátí funkce false a množinu nemění.
    bool Insert(const T & x);

    // bool Contains ( Type )
    // Vrací true pokud se objekt typu Type nachází v množině, jinak false.
    bool Contains(const T & x) const;

    // bool Remove ( Type )
    // Odstraní z množiny objekt typu Type, vrací true pokud se smazání povede.
    // Pokud v množině objekt není, vrátí funkce false a množinu nemění.
    bool Remove(const T & x);

    // funkce false a množinu nemění.
    // size_t Size () const
    // Vrací počet prvků v množině.
    size_t Size() const {
        return count;
    };

private:

    Node < T > * root;
    size_t count;

};

template < class T >
bool CSet < T > ::Insert(const T & x) {

    if (Contains(x))
        return false;

    Node < T > * node = root;

    if (!node) {
        auto newNode = new Node < T > (x);
        root = newNode;
        count++;
        return true;
    }
    // find the end
    while (node) {
        // reached the end, add new node to the end and return true
        if (!node -> next) {
            auto newNode = new Node < T > (x);
            node -> next = newNode;
            count++;
            return true;
        } else {
            node = node -> next;
        }
    }
    return false;
}

// Třída Type, parametr šablony, má garantované následující funkcionality:
//
// kopírující konstruktor,
// operátor přiřazení,
// operator< pro porovnání dvou prvků.
template < typename T >
bool isEqual(T & a, T & b) {
    return !(a < b) && !(b < a);
}
template < class T >
bool CSet < T > ::Contains(const T & x) const {
    Node < T > * node = root;

    // iterate through the tree
    while (node) {
        // there are three possibilities
        if (node -> isEqual(x))
            return true;
        node = node -> next;
    }
    return false;
}

template < class T >
bool CSet < T > ::Remove(const T & x) {

    Node < T > * node = root;
    Node < T > * previous = nullptr;

    // iterate through the tree
    while (node) {
        // there are three possibilities
        if (node -> isEqual(x)) { // node value == x
            // I am somewhere in the middle, need do skip node
            if (previous) {
                previous -> next = node -> next;
            } else {
                root = node -> next;
            }
            count--;
            node -> next = nullptr;
            delete node; // because there is no next, it will delete just itself

            return true;
        }
        previous = node;
        node = node -> next;
    }
    return false;

}

#ifndef __PROGTEST__

struct CSetTester {
    static void test0() {
        CSet < string > x0;
        assert(x0.Insert("Jerabek Michal"));
        assert(x0.Insert("Pavlik Ales"));
        assert(x0.Insert("Dusek Zikmund"));
        assert(x0.Size() == 3);
        assert(x0.Contains("Dusek Zikmund"));
        assert(!x0.Contains("Pavlik Jan"));
        assert(x0.Remove("Jerabek Michal"));
        assert(!x0.Remove("Pavlik Jan"));
    }

    static void test1() {
        CSet < string > x0;
        assert(x0.Insert("Jerabek Michal"));
        assert(x0.Insert("Pavlik Ales"));
        assert(x0.Insert("Dusek Zikmund"));
        assert(x0.Size() == 3);
        assert(x0.Contains("Dusek Zikmund"));
        assert(!x0.Contains("Pavlik Jan"));
        assert(x0.Remove("Jerabek Michal"));
        assert(!x0.Remove("Pavlik Jan"));
        CSet < string > x1(x0);
        assert(x0.Insert("Vodickova Saskie"));
        assert(x1.Insert("Kadlecova Kvetslava"));
        assert(x0.Size() == 3);
        assert(x1.Size() == 3);
        assert(x0.Contains("Vodickova Saskie"));
        assert(!x1.Contains("Vodickova Saskie"));
        assert(!x0.Contains("Kadlecova Kvetslava"));
        assert(x1.Contains("Kadlecova Kvetslava"));
    }

    static void test2() {
        CSet < string > x0;
        CSet < string > x1;
        assert(x0.Insert("Jerabek Michal"));
        assert(x0.Insert("Pavlik Ales"));
        assert(x0.Insert("Dusek Zikmund"));
        assert(x0.Size() == 3);
        assert(x0.Contains("Dusek Zikmund"));
        assert(!x0.Contains("Pavlik Jan"));
        assert(x0.Remove("Jerabek Michal"));
        assert(!x0.Remove("Pavlik Jan"));
        x1 = x0;
        assert(x0.Insert("Vodickova Saskie"));
        assert(x1.Insert("Kadlecova Kvetslava"));
        assert(x0.Size() == 3);
        assert(x1.Size() == 3);
        assert(x0.Contains("Vodickova Saskie"));
        assert(!x1.Contains("Vodickova Saskie"));
        assert(!x0.Contains("Kadlecova Kvetslava"));
        assert(x1.Contains("Kadlecova Kvetslava"));
    }

    static void test4() {
        CSet < int > x0;
        assert(x0.Insert(4));
        assert(x0.Insert(8));
        assert(x0.Insert(1));
        assert(x0.Size() == 3);
        assert(x0.Contains(4));
        assert(!x0.Contains(5));
        assert(!x0.Remove(5));
        assert(x0.Remove(4));
    }

};

int main() {
    CSetTester::test0();
    CSetTester::test1();
    CSetTester::test2();
    CSetTester::test4();
    return 0;
}
#endif /* __PROGTEST__ */