/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include <string>
#include <utility>

class Color {
public:
    Color() :   r(255),
                g(255),
                b(255),
                name("WHITE") {};

    Color([[maybe_unused]] unsigned char r, [[maybe_unused]] unsigned char g, [[maybe_unused]] unsigned char b, std::string name) : r(255),
                                                                                 g(255),
                                                                                 b(255),
                                                                                 name(std::move(name)) {};

    bool operator==(const Color &other) const;

    friend class Formatter;

    const std::string & Name (){return name;};
protected:
    int r, g, b;
    std::string name;
};
