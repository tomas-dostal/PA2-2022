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

class Company {
public:
    Company(std::string name, std::string address, std::string tax_id) :
            name(std::move(name)), address(std::move(address)), tax_id(std::move(tax_id)) {
    };

    friend class CompanyByIdComparatorLower;

    friend class CompanyByNameComparatorLower;

    friend class CompanyByNameComparatorEqual;

    unsigned int total_money = 0;

    const std::string &get_tax_id() const { return this->tax_id; };

    const string &get_address() const;

    const string &get_name() const;

private:
    std::string name, address, tax_id;
};

class Invoice {
public:
    explicit Invoice(const unsigned int amount) : amount(amount) {};

    bool operator<(const Invoice &i) const;

    unsigned int get_amount() const { return this->amount; };
private:
    unsigned int amount;
};

bool Invoice::operator<(const Invoice &i) const {
    return this->amount < i.amount;
}

class CompanyByIdComparatorLower {
public:
    bool operator()(const shared_ptr<Company> &a,
                    const shared_ptr<Company> &b) const {
        return a->tax_id.compare(b->tax_id) < 0;
    }
};

class CompanyByNameComparatorLower {
public:
    bool operator()(const shared_ptr<Company> &a,
                    const shared_ptr<Company> &b) const {
        // Name + address comparison is case-insensitive
        if (strcasecmp(a->name.c_str(), b->name.c_str()) < 0) {
            return true;
        } else if (strcasecmp(a->name.c_str(), b->name.c_str()) == 0) {
            return strcasecmp(a->address.c_str(), b->address.c_str()) < 0;
        }
        return false;
    }
};

class CompanyByNameComparatorEqual {
public:
    bool operator()(const std::shared_ptr<Company> &a,
                    const std::shared_ptr<Company> &b) const {
        // Name + address comparison is case-insensitive
        return strcasecmp(a->get_name().c_str(), b->get_name().c_str()) == 0
               && strcasecmp(a->get_address().c_str(), b->get_address().c_str()) == 0;
    }
};

const string &Company::get_name() const {
    return this->name;
}

const string &Company::get_address() const {
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

    shared_ptr<Company> getCompanyByNameConst(const string &name, const string &addr) const;

    shared_ptr<Company> getCompanyByName(const string &name, const string &addr);


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

///////////////////  Helper methods  ////////////////////

shared_ptr<Company> CVATRegister::getCompanyByName(const string &name, const string &addr) {
    shared_ptr<Company> tmp = make_shared<Company>(Company(name, addr, ""));

    // Company tmp = Company(name, addr, "");
    CompanyByNameComparatorLower comparatorLower = CompanyByNameComparatorLower();
    CompanyByNameComparatorEqual comparatorEqual = CompanyByNameComparatorEqual();

    auto it = std::lower_bound(companies_by_name.begin(), companies_by_name.end(), tmp, comparatorLower);
    if (it != companies_by_name.end() && comparatorEqual((*it), tmp)) {
        return getCompanyById((*it)->get_tax_id()); // aaah, crap it. Money is stored just in the ID one
    }
    std::cerr << "getCompanyByName " + name + ", address: " + addr + " not found. " << std::endl;
    return {nullptr};
    // throw std::runtime_error("getCompanyByName " + name + ", address: " + addr + " not found. ");
}

shared_ptr<Company> CVATRegister::getCompanyByNameConst(const string &name, const string &addr) const {
    shared_ptr<Company> tmp = make_shared<Company>(Company(name, addr, ""));

    //Company tmp = Company(name, addr, "");
    CompanyByNameComparatorLower comparatorLower = CompanyByNameComparatorLower();
    CompanyByNameComparatorEqual comparatorEqual = CompanyByNameComparatorEqual();

    auto it = std::lower_bound(companies_by_name.begin(), companies_by_name.end(), tmp, comparatorLower);
    if (it != companies_by_name.end() && comparatorEqual((*it), tmp)) {
        return getCompanyByIdConst((*it)->get_tax_id()); // aaah, crap it. Money is stored just in the ID one
    }
    std::cerr << "getCompanyByName " + name + ", address: " + addr + " not found. " << std::endl;
    return shared_ptr<Company>(nullptr);
    //throw std::runtime_error("getCompanyByName " + name + ", address: " + addr + " not found. ");
}

shared_ptr<Company> CVATRegister::getCompanyById(const string &id) {
    shared_ptr<Company> tmp = make_shared<Company>(Company("", "", id));
    //Company tmp = Company("", "", id);
    CompanyByIdComparatorLower comparatorLower = CompanyByIdComparatorLower();

    auto it = std::lower_bound(companies_by_id.begin(), companies_by_id.end(), tmp, comparatorLower);
    if (it != companies_by_id.end() && (*it)->get_tax_id() == tmp->get_tax_id()) {
        return (*it);

    }
    std::cerr << "getCompanyById " + id + " not found. " << std::endl;
    //throw std::runtime_error ("getCompanyById " + id + " not found. ");
    return shared_ptr<Company>(nullptr);

}

shared_ptr<Company> CVATRegister::getCompanyByIdConst(const string &id) const {
    auto tmp = make_shared<Company>(Company("", "", id));

    CompanyByIdComparatorLower cmp = CompanyByIdComparatorLower();

    auto it = std::lower_bound(companies_by_id.begin(), companies_by_id.end(), tmp, cmp);
    if (it != companies_by_id.end() && (*it)->get_tax_id() == tmp->get_tax_id()) {
        return (*it);
    }
    std::cerr << "getCompanyById " + id + " not found. " << std::endl;
    return shared_ptr<Company>(nullptr);
    // throw std::runtime_error("getCompanyById " + id + " not found. ");
}

//////////////////////// Required interface /////////////////////////

bool CVATRegister::newCompany(const string &name, const string &addr, const string &taxID) {
    /// Creates a new company if not exist. Combination of case-insensitive name and address
    /// has to be unique.
    /// @param name: Name of company, case insensitive
    /// @param addr: Address of the company, case insensitive
    /// @param taxID: Tax ID, case sensitive
    /// @return true if created, otherwise false.

    shared_ptr<Company> c1 = this->getCompanyByNameConst(name, addr);
    shared_ptr<Company> c2 = this->getCompanyByIdConst(taxID);
    if (!(c1 == nullptr && c2 == nullptr))
        return false; // already exists

    shared_ptr<Company> company = make_shared<Company>(Company(name, addr, taxID));
    // create a new company

    companies_by_id.insert(
            std::lower_bound(companies_by_id.begin(), companies_by_id.end(), company, CompanyByIdComparatorLower()),
            company);
    companies_by_name.insert(
            std::lower_bound(companies_by_name.begin(), companies_by_name.end(), company,
                             CompanyByNameComparatorLower()),
            company);

    return true;
}

bool CVATRegister::invoice(const string &taxID, unsigned int amount) {
    /// Create invoice for a company (searched by name and addr)
    /// @param name: Name of company
    /// @param address: Address of the company
    /// @param amount: How much
    /// @returns true if company found and invoice created, otherwise false;

    shared_ptr<Company> c = getCompanyById(taxID);
    if (!c)
        return false;

    c->total_money += amount;
    Invoice i = Invoice(amount);
    ordered_invoices.insert(std::lower_bound(ordered_invoices.begin(), ordered_invoices.end(), i), i);

    return true;
}

bool CVATRegister::invoice(const string &name, const string &addr, unsigned int amount) {
    /// Create invoice for a company (searched by name and addr)
    /// @param name: Name of company
    /// @param address: Address of the company
    /// @param amount: How much
    /// @returns true if company found and invoice created, otherwise false;

    // find_company_by_name().add_invoice() // inserts inside vector for comany,
    // insert it as well to the register, this one needs to be ordered.
    // -> binary search

    shared_ptr<Company> c = getCompanyByName(name, addr);
    if (!c)
        return false;
    return invoice(c->get_tax_id(), amount);

}


bool CVATRegister::cancelCompany(const string &taxID) {
    /// Erase company from companies_by_name and companies_by_id if exists.
    /// Keep all the invoices associated with this company.
    /// @param taxID: company unique  identification
    /// @return true if success, false if company does not exist or already canceled

    shared_ptr<Company> c = (getCompanyById(taxID));
    if (!c)
        return false;
    shared_ptr<Company> c2 = (getCompanyByName(c->get_name(), c->get_address()));

    this->companies_by_name.erase(std::remove(this->companies_by_name.begin(), this->companies_by_name.end(), c),
                                  this->companies_by_name.end());
    this->companies_by_id.erase(std::remove(this->companies_by_id.begin(), this->companies_by_id.end(), c2),
                                this->companies_by_id.end());

    return true;
}

bool CVATRegister::cancelCompany(const string &name, const string &addr) {
    /// Erase company from companies_by_name and companies_by_id if exists.
    /// Keep all the invoices associated with this company.
    /// @param name: name, case insensitive, name+addr needs to be unique
    /// @param addr: address, case insensitive, name+addr needs to be unique
    /// @return true if success, false if company does not exist or already canceled

    shared_ptr<Company> c = (getCompanyByName(name, addr));
    if (!c)
        return false;
    shared_ptr<Company> c2 = (getCompanyById(c->get_tax_id()));


    this->companies_by_name.erase(std::remove(this->companies_by_name.begin(), this->companies_by_name.end(), c),
                                  this->companies_by_name.end());
    this->companies_by_id.erase(std::remove(this->companies_by_id.begin(), this->companies_by_id.end(), c2),
                                this->companies_by_id.end());

    return true;
}


bool CVATRegister::audit(const string &name, const string &addr, unsigned int &sumIncome) const {
    /// return sum stored in company total
    /// @param name Company name
    /// @param addr Company address
    /// @param sumIncome Return parameter - sum of all invoices issued by this company
    /// @return true if company found, otherwise false
    shared_ptr<Company> c = getCompanyByNameConst(name, addr);
    if (!c)
        return false;
    sumIncome = c->total_money;
    return true;

}

bool CVATRegister::audit(const string &taxID, unsigned int &sumIncome) const {
    /// return sum stored in company total
    /// @param taxID Make audit for this company
    /// @param sumIncome Return parameter - sum of all invoices issued by this company
    /// @return true if company found, otherwise false

    shared_ptr<Company> c = getCompanyByIdConst(taxID);
    if (!c)
        return false;
    sumIncome = c->total_money;
    return true;
}

bool CVATRegister::nextCompany(string &name, string &addr) const {
    /// Find first company matching by name and address. Return next to this one.
    /// Use return parameters name and addr.

    auto tmp = make_shared<Company>(Company(name, addr, ""));
    CompanyByNameComparatorLower comparatorLower = CompanyByNameComparatorLower();

    auto it = std::upper_bound(companies_by_name.begin(), companies_by_name.end(), tmp, comparatorLower);

    if (it != companies_by_name.end()) {
        name = (*it)->get_name();
        addr = (*it)->get_address();
        return true;
    }
    return false;
}

bool CVATRegister::firstCompany(string &name, string &addr) const {
    /// @return name and addr of the alphabetically first company in the parameters.
    /// @return true if find, otherwise false;

    if (!companies_by_name.empty()) {
        addr = this->companies_by_name.front()->get_address();
        name = this->companies_by_name.front()->get_name();
        return true;
    }
    return false;
}

unsigned int CVATRegister::medianInvoice() const {
    /// Return median of the invoice
    ///
    /// If there is an odd number of invoices, return the upper mid
    /// If there is an even number of invoices, return the mid one.
    /// If there is no invoice, return 0
    /// only registered invoices (search did not fail) are in game.

    // ideally this method is not const, so I can sort the ordered invoices here
    // and not waste my time doing it in the invoice method. Unfortunately,
    // const stuff is there.

    if (this->ordered_invoices.empty())
        return 0;

    unsigned int size = this->ordered_invoices.size();
    return ordered_invoices.at((size - size % 2) / 2).get_amount();
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
