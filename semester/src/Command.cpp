/**
 * @author David Bernhauer <bernhdav@fit.cvut.cz>
 * @date 28.04.2021
 * // this is an original file I will deeply inspire and modify to fulfill my project's needs.
 * @basedon example semester work available on https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/tree/1.1.0
 */

#include "Command.h"
#include "Tspaint.h"


Command::Command(std::string name,
                 std::string help,
                 const std::function<void(
                         std::shared_ptr<Tspaint>,
                         std::shared_ptr<Interface>)> &execute)
        : name(move(name)), help(move(help)), execute(execute) {

}

void Command::Execute(std::shared_ptr<Tspaint> tspaint,
                      std::shared_ptr<Interface> interface) {
    execute(tspaint, interface);
}




