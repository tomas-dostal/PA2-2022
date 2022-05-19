/**
  * @authors David Bernhauer <bernhdav@fit.cvut.cz>, Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 08.05.2022
  * @basedon example semester work available on https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/tree/1.1.0
  */

#pragma once

#include <string>
#include <memory>
#include <functional>
#include "Tspaint.h"
#include "Interface.h"
#include "Tspaint.h"
#include "Application.h"

class Command {
private:
    std::string name;
    static std::string help;
    std::string example;
    std::function<void(Tspaint &, Interface &)> execute;

public:
    Command(std::string name, std::string help, const std::function<void(Tspaint &, Interface &)> &execute);

    void Execute(Tspaint &tspaint, Interface &interface);

    const std::string &Name() const { return name; };

    const std::string &Help() const { return help; };

    const std::string &Example() const { return example; };

    static void New(Application application);

    static void Exit(Application application);
};


};

