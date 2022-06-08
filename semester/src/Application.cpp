/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  * @basedon example semester work available on https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/tree/1.1.0
  */

#include "Application.h"

#include <utility>
#include "ProgtestErrors.h"
#include "constants.h"
#include "sstream"

Application::Application() noexcept:
        isRunning(true),
        progtestErrors(
                std::make_shared<ProgtestErrors>(
                        ProgtestErrors(std::make_shared<Interface>(std::cin, std::cout), CHANCES_FOR_PASSING_PA2,
                                       PROGTEST_ERROR_FILENAME))) {

    auto quit = [this]() { this->Stop(); };
    auto load = [this](std::shared_ptr<Interface> interface, std::shared_ptr<Tspaint> targetTspaint) {
        this->Load(interface, targetTspaint);
    };
    commands.emplace_back(SetCommand());
    commands.emplace_back(DrawCommand());
    commands.emplace_back(ListCommand());
    commands.emplace_back(SaveCommand());
    commands.emplace_back(LoadCommand(load));
    commands.emplace_back(QuitCommand(quit));
    commands.emplace_back(HelpCommand(std::make_shared<std::vector<Command>>(commands)));

}

void Application::Load(std::shared_ptr<Interface> fileInterface, std::shared_ptr<Tspaint> &targetTspaint) {

    Tspaint tspaintCopy(targetTspaint);
    try {
        this->Run(fileInterface,
                  std::make_shared<Tspaint>(tspaintCopy),
                  [&fileInterface]() { return !fileInterface->End(); },
                  [](Command *command) { return command->IsAllowedHeadless(); }
        );
        *targetTspaint = tspaintCopy;
    }
    catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        fileInterface->PrintInfo(FILE_LOADING_ERROR);
    }
}

void Application::Run(std::shared_ptr<Interface> interface, std::shared_ptr<Tspaint> tspaint,
                      std::function<bool(void)> Continue, std::function<bool(Command *)> IsCommandAllowed) {

    while (Continue() && !interface->End()) {
        try {
            auto command = this->getCommandByName(interface->PromptCommand([this](const std::string &name) {
                return std::any_of(commands.begin(), commands.end(),
                                   [&name](Command &command) { return name == command.Name(); });
            }));
            if (command) {
                if (IsCommandAllowed(command.get())) {
                    command->Execute(std::make_shared<Tspaint>(tspaint), interface);
                } else {
                    throw std::runtime_error(
                            interface->formatter->FillPlaceholder(COMMAND_NOT_ALLOWED_IN_HEADLESS,
                                                                  FormatterParams({command->Name()})
                            )
                    );
                }
            }
        }
        catch (std::runtime_error e) {
            std::cerr << e.what() << std::endl;
        }


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

bool Application::IsRunning() {
    return isRunning;
}
