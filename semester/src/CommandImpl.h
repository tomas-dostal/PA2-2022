/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 19.05.2022
  *
  * @basedon https://gitlab.fit.cvut.cz/bernhdav/pa2-minesweeper/tree/master
  * @basedon https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/tree/1.1.0
  */

#pragma once

#include "FormatterParams.h"
#include "Command.h"
#include "SysCommand.h"

Command SetCommand();

Command DrawCommand();

Command ListCommand();

SysCommand SaveCommand();

SysCommand
LoadCommand(const std::function<void(std::shared_ptr<Interface>, std::shared_ptr<Tspaint> targetTspaint)> loadFunction);

SysCommand HelpCommand(const std::shared_ptr<std::vector<Command>> &commands);

SysCommand QuitCommand(const std::function<void(void)> stopApplication);