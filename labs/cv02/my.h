//
// Created by Tomas Dostal on 20.03.2022.
//

#ifndef CV02_MY_H
#define CV02_MY_H

#include "iostream"
class my {

};
int * a = new int [57];



int main(){
    std::cout << *a;
    delete [] a;

    return 0;
}


#endif //CV02_MY_H
