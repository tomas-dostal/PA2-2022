/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  * @basedon example semester work available on https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/tree/1.1.0
  */

#include "Application.h"
#include "Command.h"
#include "CommandParameters.h"
#include "messages.h"

Application &Application::RegisterCommand(const Command &command) {
    this->commands.push_back(command);
    return *this;
}


Application &Application::RegisterOption(const std::string name, const CommandParameters &commandParameters) {

    commands.last().options.push_back({name, commandParameters});
    return *this;
}


Application::Application(Interface &interface) {
    this->interface = std::make_shared<Interface>(interface);

    commands.emplace(COMMAND_NEW, CNewCommand(m_Builders));
    commands.emplace(COMMAND_LOAD, LoadCommand());
    commands.emplace(COMMAND_SAVE, SaveCommand());

    commands.emplace(COMMAND_HELP, HelpCommand(commands));
    commands.emplace(COMMAND_QUIT, QuitCommand());
}

void Application::Run() {
    while (isRunning) {
        size_t idx = interface->PromptCommand([this](const std::string &name) {
            for (size_t i = 0; i < commands.size(); ++i)
                if (name == commands[i].Name())
                    return i;
            return commands.size();
        }, commands.size());
        commands[idx].Execute(tspaint, interface);
    }
}

Application::Application(Interface &interface) {
    this->interface = std::make_shared<Interface>(interface);
    isRunning = true;
}
