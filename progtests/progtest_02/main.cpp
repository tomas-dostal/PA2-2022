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
        invoices = vector<Invoice>();
    };

    bool operator == (const Company & c);
    bool operator < (const Company & c);
    bool  deactivate(){
        if(active) {
            active = !active;
            return true;
        }
        return false;
    }
    friend class CompanyByIdComparator;
    friend class CompanyByNameComparator;
    unsigned int total_money = 0;
    vector<Invoice> invoices;
    void add_invoice(Invoice & invoice);

private:
    std::string name , address, tax_id;
    bool active = true;
};

class Invoice {
public:
    Invoice(const Company & company, const unsigned int amount):company(company), amount(amount){};
    const bool operator < (const Invoice & i);
private:
    const Company & company;
    unsigned int amount;
};

const bool Invoice::operator<(const Invoice & i) {
    return this->amount < i.amount && this->company < i.company;
}

class CompanyByIdComparator {
public:
    bool operator()(const Company& a,
                    const Company& b)
    {
        // The member function returns 0 if all the characters in the compared
        // contents compare equal, a negative value if the first character that
        // does not match compares to less in the object than in the comparing string,
        // and a positive value in the opposite case.
        if (a.tax_id.compare(b.tax_id) == -1) {
            return true;
        }
        return false;
    }
};

class CompanyByNameComparator {
public:
    bool operator()(const Company& a,
                    const Company& b)
    {
        if (a.name.compare(b.name) == -1) {
            return true;
        }
        else if (a.name.compare(b.name) == 0) {
            return a.address.compare(b.address) == -1;
        }
        return false;
    }
};

bool Company::operator==(const Company & c) {
    return this->name == c.name && this->address == c.address && this->tax_id == c.tax_id;
}

bool Company::operator<(const Company &c) {
    return c.tax_id.compare(c.tax_id) == -1;
}

void Company::add_invoice(Invoice & invoice) {
    this->invoices.push_back(invoice);
}

class CVATRegister {
public:
    CVATRegister() = default;

    ~CVATRegister() = default;

    bool newCompany(const string &name,
                    const string &addr,
                    const string &taxID);

                    const string &addr);

    Company & getCompanyById(const string &id);

    bool companyExists(const string &name,
                       const string &addr);

    bool companyExists(const string &id);

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

    unsigned int medianInvoice(void) const;

private:
    vector<Company> companies_by_id, companies_by_name;
    vector<Invoice> ordered_invoices;
};

bool CVATRegister::newCompany(const string &name, const string &addr, const string &taxID) {
    // try to find the company in register
    if(companyExists(name, addr) || companyExists(taxID))
        return false;

    // create a new company
    Company c = Company(name, addr, taxID);

    companies_by_id.insert(std::lower_bound(companies_by_id.begin(), companies_by_id.end(), c, CompanyByIdComparator()), c);
    companies_by_name.insert(std::lower_bound(companies_by_name.begin(), companies_by_name.end(), c,  CompanyByNameComparator()), c);

    return true;
}

bool CVATRegister::invoice(const string &taxID, unsigned int amount) {
    // maybe just keep the sum of invoices inside company
    // and store invoices ordered by amount inside company?
    try{
        Company & c = getCompanyById(taxID);
        c.total_money += amount;
        c.invoices.push_back(Invoice(c, amount));

        // todo lower bound
        this->ordered_invoices.push_back(Invoice(c, amount));

        return true;
    }
    catch (std::runtime_error){
        return false;
    }
}

bool CVATRegister::cancelCompany(const string &taxID) {
    // as the inovices should be available even after the company is removed, just set flag removed=true.
    // whatever.

    try {
        Company & c = getCompanyById(taxID);
        return c.deactivate();
    }
    catch(std::runtime_error){
        return false;
    }
}

bool CVATRegister::cancelCompany(const string &name, const string &addr) {
    // call get_company_id, then delegate it
    try {
        Company & c = getCompanyByName(name, addr);
        return c.deactivate();
    }
    catch(std::runtime_error){
        return false;
    }
}

bool CVATRegister::invoice(const string &name, const string &addr, unsigned int amount) {
    // find_company_by_name().add_invoice() // inserts inside vector for comany,
    // insert it as well to the register, this one needs to be ordered.
    // -> binary search

    try{
        Company & c = getCompanyByName(name, addr);
        Invoice i = Invoice(c, amount);
        c.add_invoice(i);

        return true;
    }
    catch (std::runtime_error){
        return false;
    }
}

bool CVATRegister::audit(const string &name, const string &addr, unsigned int &sumIncome) const {
    // find company by id, then delegate it

    try{
        Company & c = getCompanyByName(name, addr);
        Invoice i = Invoice(c, amount);
        c.add_invoice(i);

        return true;
    }
    catch (std::runtime_error){
        return false;
    }
}

bool CVATRegister::audit(const string &taxID, unsigned int &sumIncome) const {
    // return sum stored in company.total

    return false;
}

bool CVATRegister::firstCompany(string &name, string &addr) const {
    // some iterator stuff
    return false;
}

bool CVATRegister::nextCompany(string &name, string &addr) const {
    // another iterator stuff
    return false;
}

unsigned int CVATRegister::medianInvoice(void) const {
    // this one will be tricky. Maybe store ordered in register.
    return 0;
}

bool CVATRegister::companyExists(const string &name, const string &addr) {
    try{
        Company c = this->getCompanyByName(name, addr);
    } catch (std::runtime_error) {
        return false;
    }
    return true;
}

bool CVATRegister::companyExists(const std::string & id) {
    try{
        Company c = this->getCompanyById(id);
    } catch (std::runtime_error) {
        return false;
    }
    return true;
}

Company &CVATRegister::getCompanyByName(const string &name, const string &addr) {
    Company tmp = Company(name, addr, "");
    std::vector<Company>::iterator it = std::lower_bound(companies_by_name.begin(), companies_by_name.end(), tmp, CompanyByNameComparator());
    if (it != companies_by_name.end() && (*it) == tmp){
        return *it;
    }
    throw std::runtime_error("getCompanyByName " + name + ", address: " + addr + " not found. ");

}

Company &CVATRegister::]getCompanyById(const string &id) {
    Company tmp = Company("", "", id);
    auto it = std::lower_bound(companies_by_id.begin(), companies_by_id.end(), tmp, CompanyByIdComparator());
    if (it != companies_by_id.end() && (*it) == tmp){
        return *it;
    }
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
    assert (b1.medianInvoice() == 4000);
    assert (b1.cancelCompany("666/666"));
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
