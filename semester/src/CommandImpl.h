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

Command SetCommand();
Command HelpCommand(const std::shared_ptr<std::vector<Command>> commands);
Command QuitCommand();