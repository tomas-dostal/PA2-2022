/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include <string>
#include <utility>

class Color {
public:
    Color() : r(255),
              g(255),
              b(255),
              name("WHITE") {};

    // todo: alpha channel
    Color(unsigned char r, unsigned char g, unsigned char b, std::string name) : r(r),
                                                                                 g(g),
                                                                                 b(b),
                                                                                 name(std::move(name)) {};

    [[nodiscard]] int R() const { return r; }

    [[nodiscard]]  int G() const { return g; }

    [[nodiscard]]  int B() const { return b; }

    bool operator==(const Color &other) const;

    friend class Formatter;


    const std::string &Name() { return name; };
protected:
    int r, g, b;
    std::string name;
};
