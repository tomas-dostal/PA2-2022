//
// Created by Tomas Dostal on 04.03.2022.
//

#include "child.h"
#include "vaccine.h"
#include <vector>

class Child {
public:
    std::string name;
    std::vector<Vaccine> vaccines;
    bool add_vaccine(Vaccine & vaccine)
    {
        vaccines.push_back(vaccine); // maybe check if already applied?
        return true;
    }

    int m_vaccines_size;
    Child(string _name = "Unknown_child",
          Vaccine* _vaccines=NULL,
          int _vaccines_count= 0,
          int _vaccines_size = 10):
            vaccines_COUNT(_vaccines_count),
            jmeno_ditete(_name){
        m_vaccines_size = _vaccines_size;
        vaccines = new Vaccine[m_vaccines_size];
    }
    // destructor
    ~Child() {}
    void print() {
        cout << "Child named " << jmeno_ditete << " has " << vaccines_COUNT << " vaccines:" << endl;
        for (int i = 0; i<vaccines_COUNT;++i){

            cout<<static_cast<char>((65)+i)<<") "<<vaccines[i].VaccineCode()<<endl;
            vaccines[i].TellMeMoreInformationAboutTheVaccine();
        }
    }

    // returns true if all vaccines are valid in the current year "a"
    bool HasAllVaccinesValid(int a) {
        for (int i = 0; i < vaccines_COUNT; i++)
        {
            if (a > vaccines[i].validUntil) {
                return 0;
            }
        }
        return 1;
    }

    bool CanBeAcceptedToChildCare(const int& current_year) {
        set<string> valid_vaccines;
        for (int i = 0; i < vaccines_COUNT; i++) {
            if (!vaccines[i].IsValid(current_year)) return false;
            valid_vaccines.insert(vaccines[i].name);
        }
        return valid_vaccines.size() > 9;
    }

};

double ProbabilityOfAutismOfSiblings(Child &child1, Child &child2, Child &child3) {
    double first_autism_probability;
    for (int i = 0; i < child1.vaccines_COUNT; i++) {
        first_autism_probability += child1.vaccines[i].autism_causing_probability;
        if (child1.vaccines[i].VaccineCode() > 666666666) {
            first_autism_probability *= 2;
        }
    }

    double second_autism_probability = 0;
    for (int i = 0; i < child2.vaccines_COUNT; i++) {
        second_autism_probability += child2.vaccines[i].autism_causing_probability;
        if (child2.vaccines[i].VaccineCode() > 666666666) {
            second_autism_probability *= 2;
        }
    }


    double third_autism_probability = 0;
    for (int i = 0; i < child3.vaccines_COUNT; i++) {
        third_autism_probability += child3.vaccines[i].autism_causing_probability;
        if (child3.vaccines[i].VaccineCode() > 666666666) {
            third_autism_probability *= 2;
        }
    }

    return first_autism_probability + second_autism_probability + third_autism_probability;
}