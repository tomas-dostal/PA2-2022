/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 08.06.2022
 */

#pragma once

#include <functional>

#include "Command.h"


class SysCommand : public Command {
public:

/**
 * SysCommand - subclass of Command which should be used for system calls (file import/export/app close etc), aka
 * what should not be invoked by an imported file.
 *
 * @param name Name of the command
 * @param help Explanation how to use the command
 * @param example Example usage
 * @param execute  Lambda of what to execute
 * @param availableInHeadless True if command should be available in import from file. SysCommands are always false.
 */
    SysCommand(std::string name, std::string help, std::string example,
               const std::function<void(std::shared_ptr<Tspaint>, std::shared_ptr<Interface>)> &execute);
};
