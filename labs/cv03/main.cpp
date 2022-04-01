#include <iostream>
#include <functional>
#include <cstdio>
#include <string>
#include <set>
#include "child.h"
#include "vaccine.h"
using namespace std;


int main() {
    Child roman("roman"), franta("franta"), david("david");
    roman.AddVaccine({"diphtheria", 2022, 0.0000003});
    roman.AddVaccine({"tetanus", 2025, 0.00054});
    roman.AddVaccine({"polio", 2084, 0.0001});
    roman.print();

    vector<Vaccine> vaccines;
    for (int i = 0; i < 10; i++) {
        vaccines.push_back({"vaccine" + to_string(i), 2043, 0.000001 + i * 0.000001});
    }
    for (const auto& vaccine : vaccines) {
        franta.AddVaccine(vaccine);
    }
    cout << endl << endl << "====================================" << endl;
    franta.print();



    vector<Vaccine> vaccines2;
    for (int i = 0; i < 10; i++) {
        vaccines2.push_back({"vaccine", 2021, 0.000001});
    }
    for (const auto& vaccine : vaccines2) {
        david.AddVaccine(vaccine);
    }
    cout << endl << endl << "====================================" << endl;
    david.print();

    cout << endl << endl << "====================================" << endl;
    cout << "Can be accepted to Child care:" << endl;
    cout << "roman: " << roman.CanBeAcceptedToChildCare(2021) << endl;
    cout << "franta: " << franta.CanBeAcceptedToChildCare(2021) << endl;
    cout << "david: " << david.CanBeAcceptedToChildCare(2021) << endl;


    cout << endl << endl << "====================================" << endl;
    cout << "Probability that at least one of the siblings will be autistic: " << ProbabilityOfAutismOfSiblings(roman, franta, david) << endl;
    return 0;
}
