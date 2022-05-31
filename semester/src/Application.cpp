/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  * @basedon example semester work available on https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/tree/1.1.0
  */

#include "Application.h"
#include "ProgtestErrors.h"
#include "constants.h"


Application &Application::RegisterCommand(const Command &command) {
    this->commands.push_back(command);
    return *this;
}

/*
Application &Application::RegisterOption(const std::string name, const CommandParameters &commandParameters) {

    commands.end().options.push_back({name, commandParameters});
    return *this;
}
*/

Application::Application(std::shared_ptr<Interface> interface, std::shared_ptr<Tspaint> tspaint): interface(interface), tspaint(tspaint), isRunning(true) {

    commands.emplace_back(SetCommand());
    commands.emplace_back(QuitCommand());
    commands.emplace_back(HelpCommand(std::make_shared<std::vector<Command>>(commands)));
}

void Application::Run() {

    //ProgtestErrors progtestErrors = ProgtestErrors (interface, CHANCES_FOR_PASSING_PA2, PROGTEST_ERROR_FILENAME);

    while (isRunning) {
        std::string commandName = interface->PromptCommand([this](const std::string &name) {
            for (size_t i = 0; i < commands.size(); ++i)
                if (name == commands[i].Name())
                    return true;
            return false;
        });
        auto command = this->getCommandByName(commandName);
        if(command)
            command->Execute(this->tspaint, interface);

        //progtestErrors.PrintRandomErrorMessageBecauseWhyNot();

    }
}

std::shared_ptr<Command> Application::getCommandByName(const std::string name) {
    for(auto c: commands)
        if(c.Name() == name)
            return std::make_shared<Command>(c);
    return nullptr;
}
