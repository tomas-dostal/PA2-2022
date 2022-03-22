#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>
#include <cassert>
using namespace std;
#endif /* __PROGTEST__ */

enum States {
    readData,
    readFromList,
    exitSuccess
};

class FinalStateMachine {
    public: 
    int currentState;

    FinalStateMachine(){
        currentState = readData;   
    }
    void next(){
        if(currentState == readData)
            currentState = readFromList;
        else if(currentState == readFromList)
            currentState = exitSuccess;
    }

}; 
class Human {
    public:
        string name, surname;
        int phone;

        Human(string name, string surname, int phone):
            name(name),
            surname(surname),
            phone(phone) {
            //cout << "created human " << name << ", " << surname << " (" << phone << ")" << endl;
        }

        bool is_valid() {
            return name.length() > 0 && surname.length() > 0 && phone >= 100000000 && phone <= 999999999;
        }
        bool isInList(vector<Human> & humanList){
            for (auto const &humanInList: humanList) {
                if (!humanInList.name.compare(this->name)
                    && !humanInList.surname.compare(this->surname)
                    && humanInList.phone == this->phone) {
                    return true;
                }
            }
            return false;
        }
};

bool checkRemainingCharacters(istringstream & iss) {
    char c;

    while (iss >> c) {
        if(!isspace(c))
            return false; // in the rest of the stream there is non-whitespace character
    }
    return true;
}


bool report ( const string & fileName, ostream & out ) {
    fstream myFile (fileName, ios::in); // read-only open
    if (!myFile.is_open()) {
        //throw "Unable to open file " + fileName;
        return false;
    }

    FinalStateMachine machine = FinalStateMachine();
    std::vector<Human> humanList;
    std::string line;


    while (std::getline(myFile, line)) {

        std::istringstream iss(line);
        string name, surname, searchWord;
        int phone;

        if(machine.currentState == readData) {

            if ((iss >> name >> surname >> phone)) {
                Human h = Human(name, surname, phone);
                if (h.is_valid()){
                    //if(!h.isInList(humanList)) // only add if not already here
                        humanList.emplace_back(h);
                }

                else   // invalid input (name/surname/phone not matching requirements
                    return false;
            } else if (line == ""){
                machine.next();
            } else { // unable to finish reading, one or more arguments missing
                return false;
            }

            // non-white characters found in the input line
            if (!checkRemainingCharacters(iss)) {
                //throw "Non-white characters remains on line: " + line;
                return false;
            }
        } else if(machine.currentState == readFromList) {
            if (line == "") {
                //cout << "No more requests";
                return true;
            }
            if (!(iss >> searchWord)) {
                //cout << "Unable to extract searchword";
                return false;
            }
            if (!checkRemainingCharacters(iss)) {
                //throw "Non-white characters remains on line: " + line;
                return false;
            }
            int counter = 0;
            for (auto const &human: humanList) {
                if (!human.name.compare(searchWord) || !human.surname.compare(searchWord)) {
                    out << human.name << " " << human.surname << " " << human.phone << endl;
                    counter++;
                }
            }
            out << "-> " << counter << endl;
        }
    }


    myFile.close();

    return true;
}

#ifndef __PROGTEST__
int main () {
    ostringstream oss;
    oss . str ( "" );
    report( "tests/test10_in.txt", cout );
            assert ( report( "tests/test0_in.txt", oss ) == true );
    assert ( oss . str () ==
             "John Christescu 258452362\n"
             "John Harmson 861647702\n"
             "-> 2\n"
             "-> 0\n"
             "Josh Dakhov 264112084\n"
             "Dakhov Speechley 865216101\n"
             "-> 2\n"
             "John Harmson 861647702\n"
             "-> 1\n" );
    oss . str ( "" );
    assert ( report( "tests/test1_in.txt", oss ) == false );
    assert ( report( "tests/test2_in.txt", oss ) == false ); // test missing argument
    assert ( report( "tests/test3_in.txt", oss ) == true ); // test multiplewhitespaces, but ok
    assert ( report( "tests/test4_in.txt", oss ) == false ); // phone number has more than 9 digits
    assert ( report( "tests/test5_in.txt", oss ) == false ); // missing empty line after list of name:surname:phone
    assert ( report( "tests/test6_in.txt", oss ) == false ); // letters in phone number
    assert ( report( "tests/test7_in.txt", oss ) == false ); // letters in phone number
    assert ( report( "tests/test8_in.txt", oss ) == false ); // unexpected input after phone number
    assert ( report( "tests/test9_in.txt", oss ) == false ); // unexpected input in readFromList
    return 0;
}
#endif /* __PROGTEST__ */