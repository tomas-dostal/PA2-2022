/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  * @basedon example semester work available on https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/tree/1.1.0
  */

#include "Application.h"

#include <utility>
#include "ProgtestErrors.h"
#include "constants.h"

Application::Application(std::shared_ptr<Interface> interface,
                         std::shared_ptr<Tspaint> tspaint) :
                            isRunning(true),
                            interface(std::move(
                                   interface)),
                            tspaint(std::move(
                                   tspaint)),
                            progtestErrors(
                                   std::make_shared<ProgtestErrors>(
                                           ProgtestErrors(this->interface, CHANCES_FOR_PASSING_PA2, PROGTEST_ERROR_FILENAME))) {
    auto quit = [this]() { this->Stop(); };
    commands.emplace_back(SetCommand());
    commands.emplace_back(DrawCommand());
    commands.emplace_back(ListCommand());
    commands.emplace_back(SaveCommand());
    commands.emplace_back(QuitCommand(quit));
    commands.emplace_back(HelpCommand(std::make_shared<std::vector<Command>>(commands)));

}

void Application::Run() {

    while (isRunning) {
        auto command = this->getCommandByName(interface->PromptCommand([this](const std::string &name) {
            return std::any_of(commands.begin(), commands.end(),
                               [&name](Command &command) { return name == command.Name(); });
        }));
        if (command)
            command->Execute(this->tspaint, interface);

        progtestErrors->PrintRandomErrorMessageBecauseWhyNot();

    }
}

std::shared_ptr<Command> Application::getCommandByName(const std::string name) {
    for (auto c: commands)
        if (c.Name() == name)
            return std::make_shared<Command>(c);
    return nullptr;
}

void Application::Stop() {
    isRunning = false;
}
