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


class Command {
private:
    std::string name;
    std::string help;
    std::string example;
    bool availableInHeadless;
    std::function<void(std::shared_ptr<Tspaint>,
                       std::shared_ptr<Interface>)> execute;

public:

    /**
     * Command
     * @param name Name of the command
     * @param help Explanation how to use the command
     * @param execute  Lambda of what to execute
     * @param availableInHeadless True if command should be available in import from file. Syscontrol commands should be set to false.
     */
    Command(std::string name, std::string help, bool availableInHeadless,
            const std::function<void(std::shared_ptr<Tspaint>,
                                     std::shared_ptr<Interface>)> &execute);

    void Execute(std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface);

    const std::string &Name() const { return name; };

    const std::string &Help() const { return help; };

    const std::string &Example() const { return example; };

    const bool &IsAllowedHeadless() const { return availableInHeadless; };

};

