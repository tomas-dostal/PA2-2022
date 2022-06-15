/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 08.06.2022
 */

#include <string>

#include "SysCommand.h"


SysCommand::SysCommand(std::string name, std::string help, std::string example,
                       const std::function<void(std::shared_ptr<Tspaint>, std::shared_ptr<Interface>)> &execute) :
        Command(name, help, example, false, execute) {
}
