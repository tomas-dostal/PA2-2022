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

// This code is (deeply) inspired by bst4.cpp Šablony tříd
// https://courses.fit.cvut.cz/BI-PA2/media/seminars/p04-src.tgz
// it works (should work), but not tested and not evaluated
// It is much faster (binary search, sorted)

template < class T >
class Node {
public:

    explicit Node(const T & x):
            leftNode(nullptr),
            rightNode(nullptr),
            value(x) {};

    ~Node() {
        delete leftNode;
        delete rightNode;
    };

    Node * Clone() const {
        Node * n;
        n = new Node(value);
        // clone left node and all childs of the node
        if (leftNode)
            n -> leftNode = leftNode -> Clone();
        // clone right node and all childs of the node
        if (rightNode)
            n -> rightNode = rightNode -> Clone();
        return n;
    };

    Node * rightNode;
    Node * leftNode;
    T value;
};

template < class T >
class CSet {
public:

    CSet() {
        root = nullptr;
        count = 0;
    };

    // copy constructor
    CSet(const CSet < T > & src) {
        if (src.root) // could be empty if there was no insert
            root = src.root -> Clone();
        else
            root = nullptr;

        count = src.count;
    };

    ~CSet() {
        // works "recursivlely", if there is a child of root, once destructor of root is called a descructor
        // of Node (which deletes right and left node if exists) and so on till the end
        delete root;
    };

    CSet < T > & operator = (const CSet < T > & src) {
        // can not assign to self, I would modify it and delete data
        if (this == & src)
            return *this;
        // delete recursively existing nodes (right node, left node), data of root
        delete root;
        // if there is a tree to copy
        if (src.root)
            root = src.root -> Clone();
        else // no tree to copy
            root = nullptr;
        count = src.count;
        return *this;

    };

    int Size() const {
        return count;
    };

    bool Insert(const T & x);
    bool Contains(const T & x) const;
    bool Remove(const T & x);

private:

    Node < T > * root;
    int count;
    template < class X > friend ostream & operator << (ostream & os,
                                                       const CSet < X > & x);
};

template < class T >
bool CSet < T > ::Insert(const T & x) {
    Node < T > * node = root;
    Node < T > * parent = nullptr;
    bool left;

    while (node) {
        // if already in set
        if (!(x < node -> value) && !(node -> value < x)) // (x == node -> value) // only < operator is available for T
            return false;

        if (x < node -> value) {
            parent = node;
            node = node -> leftNode;
            left = true;
        } else {
            parent = node;
            node = node -> rightNode;
            left = false;
        }
    }
    node = new Node < T > (x);
    /* distinguish the three cases
     */
    if (parent) {
        if (left)
            parent -> leftNode = node;
        else
            parent -> rightNode = node;
    } else
        root = node;
    count++;
    return true;
}

template < class T >
bool CSet < T > ::Contains(const T & x) const {
    Node < T > * node = root;

    // iterate through the tree
    while (node) {
        // there are three possibilities
        if (!(x < node -> value) && !(node -> value < x)) //  (x == node -> value) // only < operator is available for T
            return true;
        if (x > node -> value)
            node = node -> rightNode;
        else
            node = node -> leftNode;

    }
    return false;
}

template < class T >
bool CSet < T > ::Remove(const T & x) {
    Node < T > * node = root;
    Node < T > * parent = nullptr;
    Node < T > * toDel;

    bool left;

    while (node) {
        if (x == node -> value) {
            toDel = node;
            if (node -> leftNode && node -> rightNode) {
                parent = node;
                left = true;
                node = node -> leftNode;
                while (node -> rightNode) {
                    parent = node;
                    node = node -> rightNode;
                    left = false;
                }

                toDel -> value = node -> value;
                toDel = node;
            }

            if (toDel -> leftNode)
                node = toDel -> leftNode;
            else node = toDel -> rightNode;

            /* and again distunguish three possible parents
             */
            if (parent) {
                if (left)
                    parent -> leftNode = node;
                else
                    parent -> rightNode = node;
            } else
                root = node;

            toDel -> leftNode = toDel -> rightNode = nullptr;
            delete toDel;
            count--;
            return true;
        }
        if (x < node -> value) {
            parent = node;
            node = node -> leftNode;
            left = true;
        } else {
            parent = node;
            node = node -> rightNode;
            left = false;
        }
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