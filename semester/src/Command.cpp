/**
 * @author David Bernhauer <bernhdav@fit.cvut.cz>
 * @date 28.04.2021
 * // this is an original file I will deeply inspire and modify to fulfill my project's needs.
 * @basedon example semester work available on https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/tree/1.1.0
 */

#include "Command.h"
#include "Tspaint.h"

#include <utility>

Command::Command(std::string name, std::string help,
                 const function<void(std::unique_ptr<Tspaint> &, std::shared_ptr<Interface> &)> &execute)
        : name(move(name)), help(move(help)), execute(execute), options(options) {}

void Command::Execute(std::unique_ptr<Tspaint> &tspaint, std::shared_ptr<Interface> &interface) {
    execute(tspaint, interface);
}

void Command::Exit(Application application) {

}

Command::Command(const std::vector<std::shared_ptr<Command>> &options) : options(options) {}




