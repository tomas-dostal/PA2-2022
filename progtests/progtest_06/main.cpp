#ifndef __PROGTEST__

#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stdexcept>
#include <algorithm>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */

class CTypeBasic {
public:

    //virtual ~CTypeBasic() = default;

    virtual size_t getSize() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const CTypeBasic &c);

    virtual void print(ostream &os) const = 0;

    [[nodiscard]] virtual bool equal(const CTypeBasic &other) const = 0;

    [[nodiscard]] virtual shared_ptr<CTypeBasic> clone() const = 0;

    bool operator!=(const CTypeBasic &other) const {
        return !this->equal(other);
    };

    bool operator==(const CTypeBasic &other) const {
        return this->equal(other);
    }
};

std::ostream &operator<<(ostream &os, const CTypeBasic &c) {
    c.print(os);
    return os;
}

class CDataTypeInt : public CTypeBasic {
public:
    explicit CDataTypeInt(int data) : CTypeBasic(), data(data) {};

    CDataTypeInt() : CTypeBasic() { data = 0; };

    //virtual ~CDataTypeInt() override = default;

    virtual size_t getSize() const { return 4; };

    virtual void print(ostream &os) const override {
        os << "int";
    }

    virtual bool equal(const CTypeBasic &other) const override {
        const CDataTypeInt *ptr = dynamic_cast<const CDataTypeInt *>( &other );
        return !(ptr == nullptr);
    }

    [[nodiscard]] shared_ptr<CTypeBasic>clone() const override {
        return make_shared<CDataTypeInt>(CDataTypeInt(*this));
    };
private:
    int data;
};

class CDataTypeDouble : public CTypeBasic {
public:
    explicit CDataTypeDouble(double data) : data(data) {};

    //virtual ~CDataTypeDouble() override = default;

    virtual size_t getSize() const { return 8; };

    CDataTypeDouble() : CTypeBasic() { data = 0.0; };

    virtual void print(ostream &os) const override {
        os << "double";
    };

    shared_ptr<CTypeBasic> clone() const override {
        return make_shared<CDataTypeDouble>(CDataTypeDouble(*this));
    };

    virtual bool equal(const CTypeBasic &other) const override {
        const CDataTypeDouble *ptr = dynamic_cast<const CDataTypeDouble *>( &other );
        return !(ptr == nullptr);
    }

private:
    double data;
};


class CDataTypeEnum : public CTypeBasic {
public:
    CDataTypeEnum() : CTypeBasic() {};

    //virtual ~CDataTypeEnum() override = default;

    virtual size_t getSize() const { return 4; };

    CDataTypeEnum &add(const std::string &value) {

        for(auto item: data)
            if(item == value)
                throw invalid_argument("Duplicate enum value: " + value);

        data.push_back(value);

        return *this;
    }

    virtual void print(ostream &os) const {
        os << "enum" << std::endl;
        os << "{" << std::endl;
        for (long unsigned int i = 0; i < data.size(); i++)
            if(i == data.size() - 1)
                os <<  "  " << data[i] << std::endl;
            else
                os << "  " << data[i] << "," << std::endl;

        os << "}" << std::endl;

    }

    [[nodiscard]] shared_ptr<CTypeBasic> clone() const override {
        return make_shared<CDataTypeEnum>(CDataTypeEnum(*this));
    };

    virtual bool equal_value(const CTypeBasic &other) const {
        const CDataTypeEnum *ptr = dynamic_cast<const CDataTypeEnum *>( &other );
        return ptr != nullptr;
    }

    virtual bool equal(const CTypeBasic &other) const {
        const CDataTypeEnum *ptr = dynamic_cast<const CDataTypeEnum *>( &other );
        if (ptr == nullptr)
            return false;
        return data == ptr->data;
    }
private:

    std::vector<std::string> data;
};

class CDataTypeStruct : public CTypeBasic {
public:
    CDataTypeStruct() : CTypeBasic() {};

    /*virtual ~CDataTypeStruct() override {
        for(auto item: data){
            delete item.second;
        }
    };*/

    virtual size_t getSize() const {
        size_t result = 0;
        for (auto item: data) {
            result += item.second->getSize();
        }
        return result;
    };

    CDataTypeStruct &addField(const std::string &name, const CTypeBasic &c) {
        for(auto item: data){
            if(name == item.first)
                throw invalid_argument("Duplicate field: "+ name);
        }
        data.emplace_back(name, c.clone());

        return *this;
    }

    virtual void print(ostream &os) const override {
        os << "struct" << std::endl;
        os << "{" << std::endl;
        for (const auto& item: data) {

            stringstream ss;
            ss << *item.second;

            std::string tmp;

            long unsigned int i = 0;
            while(std::getline(ss,tmp,'\n')){
                os << "  " << tmp;
                if(i > 0)
                    os << std::endl;
                i++;
            }

            if(i > 0)
                os << " ";
            os << " " << item.first << ";" << std::endl;


        }
        os << "}" << std::endl;
    }

    virtual bool equal(const CTypeBasic &other) const {
        // porovná tento typ s jiným typem, vrátí true, pokud jsou oba typy shodné (oba typy jsou struktury,
        // mají stejný počet složek, složky na každé pozici mají stejný typ, jména složek se ale mohou lišit),
        const CDataTypeStruct *ptr = dynamic_cast<const CDataTypeStruct *>( &other );
        if (ptr == nullptr)
            return false;
        if(ptr->data.size() != this->data.size())
            return false;
        for(long unsigned int i = 0; i < this->data.size(); i++){
            if(*(this->data[i].second) != *(ptr->data[i].second))
                return false;
        }
        return true;
    }

    shared_ptr<CTypeBasic> clone() const {
        return make_shared<CDataTypeStruct>(CDataTypeStruct(*this));
    };

    const CTypeBasic &field(const string &s) const {

        for (auto item: data) {
            if (item.first == s) {
                return *(item.second);
            }
        }
        throw invalid_argument("Unknown field: " + s);
    }

private:
    vector<std::pair<std::string, shared_ptr<CTypeBasic>>> data;
    // todo remove the clone it

};

#ifndef __PROGTEST__

static bool whitespaceMatch(const string &a,
                            const string &b) {

    std::string::const_iterator it1 = a.begin();
    std::string::const_iterator it2 = b.begin();

    while (!(it1 == a.end() && it2 == b.end()))
    {
        while(isspace(*it1) && it1 != a.end())
            it1++;
        while(isspace(*it2) && it2 != b.end())
            it2++;

        if((*it1) != (*it2))
            return false;
        else {
            if(it1 != a.end())
                it1++;
            if(it2 != b.end())
                it2++;
        }
    }
    return true;

}

template<typename T_>
static bool whitespaceMatch(const T_ &x,
                            const string &ref) {
    ostringstream oss;
    oss << x;

    std::cout << "whitespaceMatch" << std::endl << std::endl << x <<  std::endl <<  std::endl;
    std::cout << "REF" <<  std::endl << std::endl << ref << std::endl;
    return whitespaceMatch(oss.str(), ref);
}

int main(void) {

    CDataTypeStruct a = CDataTypeStruct().
            addField("m_Length", CDataTypeInt()).
            addField("m_Status", CDataTypeEnum().
            add("NEW").
            add("FIXED").
            add("BROKEN").
            add("DEAD")).
            addField("m_Ratio", CDataTypeDouble());

    CDataTypeStruct b = CDataTypeStruct().
            addField("m_Length", CDataTypeInt()).
            addField("m_Status", CDataTypeEnum().
            add("NEW").
            add("FIXED").
            add("BROKEN").
            add("READY")).
            addField("m_Ratio", CDataTypeDouble());

    CDataTypeStruct c = CDataTypeStruct().
            addField("m_First", CDataTypeInt()).
            addField("m_Second", CDataTypeEnum().
            add("NEW").
            add("FIXED").
            add("BROKEN").
            add("DEAD")).
            addField("m_Third", CDataTypeDouble());

    CDataTypeStruct d = CDataTypeStruct().
            addField("m_Length", CDataTypeInt()).
            addField("m_Status", CDataTypeEnum().
            add("NEW").
            add("FIXED").
            add("BROKEN").
            add("DEAD")).
            addField("m_Ratio", CDataTypeInt());
    //    CDataTypeStruct a = CDataTypeStruct().
    //            addField("m_Length", CDataTypeInt()).
    //            addField("m_Status", CDataTypeEnum().
    //            add("NEW").
    //            add("FIXED").
    //            add("BROKEN").
    //            add("DEAD")).
    //            addField("m_Ratio", CDataTypeDouble());
    assert (whitespaceMatch(a, "struct\n"
                               "{\n"
                               "  int m_Length;\n"
                               "  enum\n"
                               "  {\n"
                               "    NEW,\n"
                               "    FIXED,\n"
                               "    BROKEN,\n"
                               "    DEAD\n"
                               "  } m_Status;\n"
                               "  double m_Ratio;\n"
                               "}"));

    assert (whitespaceMatch(b, "struct\n"
                               "{\n"
                               "  int m_Length;\n"
                               "  enum\n"
                               "  {\n"
                               "    NEW,\n"
                               "    FIXED,\n"
                               "    BROKEN,\n"
                               "    READY\n"
                               "  } m_Status;\n"
                               "  double m_Ratio;\n"
                               "}"));

    assert (whitespaceMatch(c, "struct\n"
                               "{\n"
                               "  int m_First;\n"
                               "  enum\n"
                               "  {\n"
                               "    NEW,\n"
                               "    FIXED,\n"
                               "    BROKEN,\n"
                               "    DEAD\n"
                               "  } m_Second;\n"
                               "  double m_Third;\n"
                               "}"));

    assert (whitespaceMatch(d, "struct\n"
                               "{\n"
                               "  int m_Length;\n"
                               "  enum\n"
                               "  {\n"
                               "    NEW,\n"
                               "    FIXED,\n"
                               "    BROKEN,\n"
                               "    DEAD\n"
                               "  } m_Status;\n"
                               "  int m_Ratio;\n"
                               "}"));

    assert (a != b);
    assert (a == c);
    assert (a != d);
    assert (a.field("m_Status") == CDataTypeEnum().add("NEW").add("FIXED").add("BROKEN").add("DEAD"));
    assert (a.field("m_Status") != CDataTypeEnum().add("NEW").add("BROKEN").add("FIXED").add("DEAD"));
    assert (a != CDataTypeInt());
    assert (whitespaceMatch(a.field("m_Status"), "enum\n"
                                                 "{\n"
                                                 "  NEW,\n"
                                                 "  FIXED,\n"
                                                 "  BROKEN,\n"
                                                 "  DEAD\n"
                                                 "}"));

    CDataTypeStruct aOld = a;
    b.addField("m_Other", CDataTypeDouble());

    a.addField("m_Sum", CDataTypeInt());

    assert (a != aOld);
    assert (a != c);
    assert (aOld == c);
    assert (whitespaceMatch(a, "struct\n"
                               "{\n"
                               "  int m_Length;\n"
                               "  enum\n"
                               "  {\n"
                               "    NEW,\n"
                               "    FIXED,\n"
                               "    BROKEN,\n"
                               "    DEAD\n"
                               "  } m_Status;\n"
                               "  double m_Ratio;\n"
                               "  int m_Sum;\n"
                               "}"));

    assert (whitespaceMatch(b, "struct\n"
                               "{\n"
                               "  int m_Length;\n"
                               "  enum\n"
                               "  {\n"
                               "    NEW,\n"
                               "    FIXED,\n"
                               "    BROKEN,\n"
                               "    READY\n"
                               "  } m_Status;\n"
                               "  double m_Ratio;\n"
                               "  double m_Other;\n"
                               "}"));

    c.addField("m_Another", a.field("m_Status"));

    assert (whitespaceMatch(c, "struct\n"
                               "{\n"
                               "  int m_First;\n"
                               "  enum\n"
                               "  {\n"
                               "    NEW,\n"
                               "    FIXED,\n"
                               "    BROKEN,\n"
                               "    DEAD\n"
                               "  } m_Second;\n"
                               "  double m_Third;\n"
                               "  enum\n"
                               "  {\n"
                               "    NEW,\n"
                               "    FIXED,\n"
                               "    BROKEN,\n"
                               "    DEAD\n"
                               "  } m_Another;\n"
                               "}"));

    d.addField("m_Another", a.field("m_Ratio"));

    assert (whitespaceMatch(d, "struct\n"
                               "{\n"
                               "  int m_Length;\n"
                               "  enum\n"
                               "  {\n"
                               "    NEW,\n"
                               "    FIXED,\n"
                               "    BROKEN,\n"
                               "    DEAD\n"
                               "  } m_Status;\n"
                               "  int m_Ratio;\n"
                               "  double m_Another;\n"
                               "}"));

    assert (a.getSize() == 20);
    assert (b.getSize() == 24);
    try {
        a.addField("m_Status", CDataTypeInt());
        assert ("addField: missing exception!" == nullptr);
    }
    catch (const invalid_argument &e) {
        assert (e.what() == "Duplicate field: m_Status"sv);
    }

    try {
        cout << a.field("m_Fail") << endl;
        assert ("field: missing exception!" == nullptr);
    }
    catch (const invalid_argument &e) {
        assert (e.what() == "Unknown field: m_Fail"sv);
    }

    try {
        CDataTypeEnum en;
        en.add("FIRST").
                add("SECOND").
                add("FIRST");
        assert ("add: missing exception!" == nullptr);
    }
    catch (const invalid_argument &e) {
        assert (e.what() == "Duplicate enum value: FIRST"sv);
    }

    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
