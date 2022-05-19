/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 13.05.2022
  */

#pragma once


#include <string>

class CommandParameters {
    template<typename ... Args>
    CommandParameters(Args &&... args);
};

