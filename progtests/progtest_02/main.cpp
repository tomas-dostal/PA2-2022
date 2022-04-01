#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */



class Invoice; // declared lated

class Company{
public:
    Company(std::string name, std::string address, std::string tax_id):
                name(std::move(name)), address(std::move(address)), tax_id(std::move(tax_id)){
    };

    bool operator == (const Company & c) const;
    bool operator == (const std::string & id) const;

        bool operator < (const Company & c) const;
    bool  deactivate(){
        if(active) {
            active = !active;
            return true;
        }
        return false;
    }
    const bool is_active() const {return this->active; };

    friend class CompanyByIdComparatorLower;
    friend class CompanyByIdComparatorEqual;
    friend class CompanyByNameComparatorLower;
    friend class CompanyByNameComparatorEqual;

    unsigned int total_money = 0;

    const std::string & get_tax_id() const { return this->tax_id; };
    const string & get_address() const;
    const string & get_name() const;


private:
    std::string name , address, tax_id;
    bool active = true;
};

class Invoice {
public:
    Invoice(const unsigned int amount): amount(amount){};
    bool operator < (const Invoice & i) const;
    unsigned int get_amount() const {return this->amount;};
private:
    unsigned int amount;
};

bool Invoice::operator<(const Invoice & i) const {
    return std::tie(this->amount) < std::tie( i.amount);
}

class CompanyByIdComparatorLower {
public:
    bool operator()(const shared_ptr<Company> a,
                    const shared_ptr<Company> b) const
    {
        // The member function returns 0 if all the characters in the compared
        // contents compare equal, a negative value if the first character that
        // does not match compares to less in the object than in the comparing string,
        // and a positive value in the opposite case.
        return a->tax_id.compare(b->tax_id) < 0;
    }
};

class CompanyByIdComparatorEqual {
public:
    bool operator()(const shared_ptr<Company> a,
                    const shared_ptr<Company> b) const
    {
        // The member function returns 0 if all the characters in the compared
        // contents compare equal, a negative value if the first character that
        // does not match compares to less in the object than in the comparing string,
        // and a positive value in the opposite case.
        if (a->get_tax_id() == b->get_tax_id()) {
            return true;
        }
        return false;
    }
};
class CompanyByNameComparatorLower{
public:
    bool operator()(const shared_ptr<Company>& a,
                    const shared_ptr<Company>& b) const
    {

        if (strcasecmp(a->name.c_str(), b->name.c_str()) < 0) {
            return true;
        }
        else if ( strcasecmp(a->name.c_str(), b->name.c_str()) == 0) {
            return  strcasecmp(a->address.c_str(), b->address.c_str()) < 0;
        }
        return false;
    }
};

class CompanyByNameComparatorEqual{
public:
    bool operator()(const std::shared_ptr<Company>  a,
                    const std::shared_ptr<Company> b) const
    {
        return strcasecmp(a->get_name().c_str(), b->get_name().c_str()) == 0 && strcasecmp(a->get_address().c_str(), b->get_address().c_str()) == 0;
    }
};

const string & Company::get_name() const {
    return this->name;
}

const string & Company::get_address() const {
    return this->address;
}

class CVATRegister {
public:
    CVATRegister() = default;

    ~CVATRegister() = default;

    bool newCompany(const string &name,
                    const string &addr,
                    const string &taxID);

    shared_ptr<Company> getCompanyByIdConst(const string &id) const;
    shared_ptr<Company> getCompanyById(const string &id);

    const shared_ptr<Company> getCompanyByNameConst(const string &name, const string &addr) const;
    shared_ptr<Company> getCompanyByName(const string &name, const string &addr);

    bool companyExists(const string &name,
                       const string &addr) const;

    bool companyExists(const string &id) const;

    bool cancelCompany(const string &name,
                       const string &addr);

    bool cancelCompany(const string &taxID);

    bool invoice(const string &taxID,
                 unsigned int amount);

    bool invoice(const string &name,
                 const string &addr,
                 unsigned int amount);

    bool audit(const string &name,
               const string &addr,
               unsigned int &sumIncome) const;

    bool audit(const string &taxID,
               unsigned int &sumIncome) const;

    bool firstCompany(string &name,
                      string &addr) const;

    bool nextCompany(string &name,
                     string &addr) const;

    unsigned int medianInvoice() const;

private:
    vector<shared_ptr<Company>> companies_by_id;
    std::vector<shared_ptr<Company>> companies_by_name;
    vector<Invoice> ordered_invoices;

};

bool CVATRegister::newCompany(const string &name, const string &addr, const string &taxID) {
    // try to find the company in register
    if(companyExists(name, addr) || companyExists(taxID))
        return false;
    shared_ptr<Company> foo = make_shared<Company>(Company(name, addr, taxID));
    // create a new company

    companies_by_id.insert(std::lower_bound(companies_by_id.begin(), companies_by_id.end(),  foo, CompanyByIdComparatorLower()), foo);
    // this one is just for searching, actual money count is stored in companies_by_id. Because I don't want to use pointers.
    companies_by_name.insert(std::lower_bound(companies_by_name.begin(), companies_by_name.end(), foo,  CompanyByNameComparatorLower()), foo);

    return true;
}

bool CVATRegister::invoice(const string &taxID, unsigned int amount) {
    // maybe just keep the sum of invoices inside company
    // and store invoices ordered by amount inside company?
    try{
        shared_ptr<Company> c = getCompanyById(taxID);
        c->total_money += amount;
        Invoice i = Invoice(amount);
        ordered_invoices.insert(std::lower_bound(ordered_invoices.begin(), ordered_invoices.end(), i), i);
        //ordered_invoices.emplace_back();

        return true;
    }
    catch (std::runtime_error const&){
        return false;
    }
}

bool CVATRegister::cancelCompany(const string &taxID) {
    // as the inovices should be available even after the company is removed, just set flag removed=true.

    try {
        shared_ptr<Company> c = (getCompanyById(taxID));
        shared_ptr<Company> c2 = (getCompanyByName(c->get_name(), c->get_address()));

        this->companies_by_name.erase(std::remove(this->companies_by_name.begin(), this->companies_by_name.end(), c), this->companies_by_name.end());
        this->companies_by_id.erase(std::remove(this->companies_by_id.begin(), this->companies_by_id.end(), c2), this->companies_by_id.end());

        return true;
    }
    catch(std::out_of_range const&){
        return false;
    }
    catch(std::runtime_error const&){
        return false;
    }
}

bool CVATRegister::cancelCompany(const string &name, const string &addr) {
    // call get_company_id, then delegate it
    try {
        shared_ptr<Company> c = (getCompanyByName(name, addr));
        shared_ptr<Company> c2 = (getCompanyById(c->get_tax_id()));

        this->companies_by_name.erase(std::remove(this->companies_by_name.begin(), this->companies_by_name.end(), c), this->companies_by_name.end());
        this->companies_by_id.erase(std::remove(this->companies_by_id.begin(), this->companies_by_id.end(), c2), this->companies_by_id.end());

        return true;
    }
    catch(std::runtime_error const&){
        return false;
    }
    catch(std::out_of_range const&){
        return false;
    }
}

bool CVATRegister::invoice(const string &name, const string &addr, unsigned int amount) {
    // find_company_by_name().add_invoice() // inserts inside vector for comany,
    // insert it as well to the register, this one needs to be ordered.
    // -> binary search

    try{
        shared_ptr<Company> c = getCompanyByName(name, addr);
        return invoice(c->get_tax_id(), amount);
    }
    catch (std::runtime_error const&){
        return false;
    }
}

bool CVATRegister::audit(const string &name, const string &addr, unsigned int &sumIncome) const {
    // find company by id, then delegate it
    try{
        shared_ptr<Company> c = getCompanyByNameConst(name, addr);
        sumIncome = c->total_money;
        return true;
    }
    catch (std::runtime_error const&){
        return false;
    }
}

bool CVATRegister::audit(const string &taxID, unsigned int &sumIncome) const {
    // return sum stored in company.total
    try{
        shared_ptr<Company> c = getCompanyByIdConst(taxID);
        sumIncome = c->total_money;
        return true;
    }
    catch (std::runtime_error const&){
        return false;
    }
}

bool CVATRegister::nextCompany(string &name, string &addr) const {
    // nejdriv vezmi a podle name a addr najdi nejakou formu.
    // Do tech parametru name a addr vrat o jedno vetsi firmu

    auto tmp = make_shared<Company>(Company(name, addr, ""));
    CompanyByNameComparatorLower comparatorLower = CompanyByNameComparatorLower();

    auto it = std::upper_bound(companies_by_name.begin(), companies_by_name.end(), tmp, comparatorLower);

    // tohle mozna nefunguje
    if (it != companies_by_name.end()){
        name = (*it)->get_name();
        addr = (*it)->get_address();
        return true;
    }
    return false;
}

bool CVATRegister::firstCompany(string &name, string &addr) const{
    // uplne prvni prvek pole
    if(!companies_by_name.empty()){
        addr = this->companies_by_name.front()->get_address();
        name = this->companies_by_name.front()->get_name();
        return true;
    }
    return false;
}

unsigned int CVATRegister::medianInvoice() const {
    // this one will be tricky. Maybe store ordered in register.
    // vyhledá medián hodnoty faktury.
    // Do vypočteného mediánu se započtou všechny úspěšně zpracované faktury
    // zadané voláním invoice. Tedy nezapočítávají se faktury, které nešlo přiřadit
    // (volání invoice selhalo), ale započítávají se všechny dosud registrované faktury,
    // tedy při výmazu firmy se neodstraňují její faktury z výpočtu mediánu. Pokud je
    // v systému zadaný sudý počet faktur, vezme se vyšší ze dvou prostředních hodnot.
    // Pokud systém zatím nezpracoval žádnou fakturu, bude vrácena hodnota 0.

    // create a copy, sort it.
    if(this->ordered_invoices.empty())
        return 0;
    //vector<Invoice> tmp =  vector<Invoice>(this->ordered_invoices);
    //std::sort(tmp.begin(), tmp.end());

    unsigned int size = this->ordered_invoices.size();
    return ordered_invoices.at((size - size % 2) / 2).get_amount();
}

bool CVATRegister::companyExists(const string &name, const string &addr) const {
    try{
        shared_ptr<Company> c = this->getCompanyByNameConst(name, addr);
    } catch (std::runtime_error const&) {
        return false;
    }
    return true;
}

bool CVATRegister::companyExists(const std::string & id) const {
    try{
        shared_ptr<Company> c = this->getCompanyByIdConst(id);
    } catch (std::runtime_error const&) {
        return false;
    }
    return true;
}

shared_ptr<Company> CVATRegister::getCompanyByName(const string &name, const string &addr) {
    shared_ptr<Company> tmp = make_shared<Company>(Company(name, addr, ""));

    // Company tmp = Company(name, addr, "");
    CompanyByNameComparatorLower comparatorLower = CompanyByNameComparatorLower();
    CompanyByNameComparatorEqual comparatorEqual = CompanyByNameComparatorEqual();

    auto it = std::lower_bound(companies_by_name.begin(), companies_by_name.end(), tmp, comparatorLower);
    if (it != companies_by_name.end() && comparatorEqual((*it), tmp)){
        return getCompanyById((*it)->get_tax_id()); // aaah, crap it. Money is stored just in the ID one
    }
    std::cerr << "getCompanyByName " + name + ", address: " + addr + " not found. " << std::endl;
    throw std::runtime_error("getCompanyByName " + name + ", address: " + addr + " not found. ");
}

const shared_ptr<Company> CVATRegister::getCompanyByNameConst(const string &name, const string &addr) const {
    shared_ptr<Company> tmp = make_shared<Company>(Company(name, addr, ""));

    //Company tmp = Company(name, addr, "");
    CompanyByNameComparatorLower comparatorLower = CompanyByNameComparatorLower();
    CompanyByNameComparatorEqual comparatorEqual = CompanyByNameComparatorEqual();

    auto it = std::lower_bound(companies_by_name.begin(), companies_by_name.end(), tmp, comparatorLower);
    if (it != companies_by_name.end() && comparatorEqual((*it), tmp)){
        return getCompanyByIdConst((*it)->get_tax_id()); // aaah, crap it. Money is stored just in the ID one
    }
    std::cerr << "getCompanyByName " + name + ", address: " + addr + " not found. " << std::endl;
    throw std::runtime_error("getCompanyByName " + name + ", address: " + addr + " not found. ");
}
shared_ptr<Company> CVATRegister::getCompanyById(const string &id) {
    shared_ptr<Company> tmp = make_shared<Company>(Company("", "", id));
    //Company tmp = Company("", "", id);
    CompanyByIdComparatorLower comparatorLower = CompanyByIdComparatorLower();

    auto it = std::lower_bound(companies_by_id.begin(), companies_by_id.end(), tmp, comparatorLower);
    if (it != companies_by_id.end() && (*it)->get_tax_id() == tmp->get_tax_id()){
        return (*it);

    }
    std::cerr << "getCompanyById " + id + " not found. " << std::endl;
    throw std::runtime_error ("getCompanyById " + id + " not found. ");


}

shared_ptr<Company> CVATRegister::getCompanyByIdConst(const string &id) const {
    auto tmp = make_shared<Company>(Company("", "", id));

    CompanyByIdComparatorLower cmp = CompanyByIdComparatorLower();

    auto it = std::lower_bound(companies_by_id.begin(), companies_by_id.end(), tmp, cmp);
    if (it != companies_by_id.end() && (*it)->get_tax_id() == tmp->get_tax_id()){
        return (*it);
    }
    std::cerr << "getCompanyById " + id + " not found. " << std::endl;
    throw std::runtime_error("getCompanyById " + id + " not found. ");
}


#ifndef __PROGTEST__

int main(void) {
    string name, addr;
    unsigned int sumIncome;

    CVATRegister b1;
    assert (b1.newCompany("ACME", "Thakurova", "666/666"));
    assert (b1.newCompany("ACME", "Kolejni", "666/666/666"));
    assert (b1.newCompany("Dummy", "Thakurova", "123456"));
    assert (b1.invoice("666/666", 2000));
    assert (b1.medianInvoice() == 2000);
    assert (b1.invoice("666/666/666", 3000));
    assert (b1.medianInvoice() == 3000);
    assert (b1.invoice("123456", 4000));
    assert (b1.medianInvoice() == 3000);
    assert (b1.invoice("aCmE", "Kolejni", 5000));
    assert (b1.medianInvoice() == 4000);
    assert (b1.audit("ACME", "Kolejni", sumIncome) && sumIncome == 8000);
    assert (b1.audit("123456", sumIncome) && sumIncome == 4000);
    assert (b1.firstCompany(name, addr) && name == "ACME" && addr == "Kolejni");
    assert (b1.nextCompany(name, addr) && name == "ACME" && addr == "Thakurova");
    assert (b1.nextCompany(name, addr) && name == "Dummy" && addr == "Thakurova");
    assert (!b1.nextCompany(name, addr));
    assert (b1.cancelCompany("ACME", "KoLeJnI"));
    assert (b1.firstCompany(name, addr) && name == "ACME" && addr == "Thakurova");
    assert (b1.nextCompany(name, addr) && name == "Dummy" && addr == "Thakurova");
    assert (!b1.nextCompany(name, addr));
    assert (b1.medianInvoice() == 4000);
    assert (b1.cancelCompany("666/666"));
    assert (b1.firstCompany(name, addr) && name == "Dummy" && addr == "Thakurova");
    assert (!b1.nextCompany(name, addr));
    assert (b1.medianInvoice() == 4000);
    assert (b1.invoice("123456", 100));
    assert (b1.medianInvoice() == 3000);
    assert (b1.invoice("123456", 300));
    assert (b1.medianInvoice() == 3000);
    assert (b1.invoice("123456", 200));
    assert (b1.medianInvoice() == 2000);
    assert (b1.invoice("123456", 230));
    assert (b1.medianInvoice() == 2000);
    assert (b1.invoice("123456", 830));
    assert (b1.medianInvoice() == 830);
    assert (b1.invoice("123456", 1830));
    assert (b1.medianInvoice() == 1830);
    assert (b1.invoice("123456", 2830));
    assert (b1.medianInvoice() == 1830);
    assert (b1.invoice("123456", 2830));
    assert (b1.medianInvoice() == 2000);
    assert (b1.invoice("123456", 3200));
    assert (b1.medianInvoice() == 2000);
    assert (b1.firstCompany(name, addr) && name == "Dummy" && addr == "Thakurova");
    assert (!b1.nextCompany(name, addr));
    assert (b1.cancelCompany("123456"));
    assert (!b1.firstCompany(name, addr));

    CVATRegister b2;
    assert (b2.newCompany("ACME", "Kolejni", "abcdef"));
    assert (b2.newCompany("Dummy", "Kolejni", "123456"));
    assert (!b2.newCompany("AcMe", "kOlEjNi", "1234"));
    assert (b2.newCompany("Dummy", "Thakurova", "ABCDEF"));
    assert (b2.medianInvoice() == 0);
    assert (b2.invoice("ABCDEF", 1000));
    assert (b2.medianInvoice() == 1000);
    assert (b2.invoice("abcdef", 2000));
    assert (b2.medianInvoice() == 2000);
    assert (b2.invoice("aCMe", "kOlEjNi", 3000));
    assert (b2.medianInvoice() == 2000);
    assert (!b2.invoice("1234567", 100));
    assert (!b2.invoice("ACE", "Kolejni", 100));
    assert (!b2.invoice("ACME", "Thakurova", 100));
    assert (!b2.audit("1234567", sumIncome));
    assert (!b2.audit("ACE", "Kolejni", sumIncome));
    assert (!b2.audit("ACME", "Thakurova", sumIncome));
    assert (!b2.cancelCompany("1234567"));
    assert (!b2.cancelCompany("ACE", "Kolejni"));
    assert (!b2.cancelCompany("ACME", "Thakurova"));
    assert (b2.cancelCompany("abcdef"));
    assert (b2.medianInvoice() == 2000);
    assert (!b2.cancelCompany("abcdef"));
    assert (b2.newCompany("ACME", "Kolejni", "abcdef"));
    assert (b2.cancelCompany("ACME", "Kolejni"));
    assert (!b2.cancelCompany("ACME", "Kolejni"));

    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
