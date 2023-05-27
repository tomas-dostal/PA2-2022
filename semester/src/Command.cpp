/**
 * @author David Bernhauer <bernhdav@fit.cvut.cz>
 * @modified_by Tomas Dostal <dostato6@fit.cvut.cz>
 * @date 28.04.2021
 * @date 12.06.2022
 * Inspiration level was quite high so I decided to keep the original author.
 * @basedon example semester work available on https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/tree/1.1.0
 *
 */

#include "Command.h"

#include <utility>
#include "Tspaint.h"


Command::Command(std::string name,
                 std::string help,
                 std::string example,
                 bool availableInHeadless,
                 const std::function<void(std::shared_ptr<Tspaint>,
                                          std::shared_ptr<Interface>)> &execute
)
        : name(std::move(name)),
          help(std::move(help)),
          example(std::move(example)),
          availableInHeadless(availableInHeadless),
          execute(execute) {

}


void Command::Execute(std::shared_ptr<Tspaint> tspaint,
                      std::shared_ptr<Interface> interface) {
    execute(std::move(tspaint), std::move(interface));
}




