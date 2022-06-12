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
#include "fstream"

Application::Application() noexcept:
        isRunning(true),
        progtestErrors(
                std::make_shared<ProgtestErrors>(
                        ProgtestErrors(std::make_shared<Interface>(std::cin, std::cout), CHANCES_FOR_PASSING_PA2,
                                       PROGTEST_ERROR_FILENAME))) {

    auto quit = [this]() { this->Stop(); };
    auto load = [this](std::shared_ptr<Interface> interface, std::shared_ptr<Interface> fileInterface, std::shared_ptr<Tspaint> & targetTspaint) {
        interface->PrintInfo(
                interface->formatter->FillPlaceholder(
                        YES_OR_NO_WITH_MESSAGE,
                        FormatterParams({LOAD_WILL_OVERWRITE})
                        )
                );
        if(std::count(YES.begin(), YES.end(), interface->PromptOption(YES_NO)))
            this->Load(interface, fileInterface, targetTspaint);
        else
            interface->PrintInfo(IMPORT_ABORTED);

    };
    commands.emplace_back(SetCommand());
    commands.emplace_back(DrawCommand());
    commands.emplace_back(GroupCommand());
    commands.emplace_back(ListCommand());
    commands.emplace_back(SaveCommand());
    commands.emplace_back(LoadCommand(load));
    commands.emplace_back(QuitCommand(quit));
    commands.emplace_back(HelpCommand(std::make_shared<std::vector<Command>>(commands)));

}

void Application::Load(const std::shared_ptr<Interface> & interface, const std::shared_ptr<Interface>&  fileInterface, std::shared_ptr<Tspaint> & targetTspaint) {

    std::shared_ptr<Tspaint> tspaintCopy = std::make_shared<Tspaint>(*targetTspaint);
    if (!this->Run(fileInterface,
                  tspaintCopy,
                  [&fileInterface]() { return !fileInterface->End(); },
                  [](Command *command) { return command->IsAllowedHeadless(); }
        )){
        interface->PrintInfo(FILE_LOADING_ERROR);
        return;
    }

    interface->PrintInfo(IMPORT_SUCCESSFUL);
    *targetTspaint = *tspaintCopy;
}

bool Application::Run(const std::shared_ptr<Interface> & interface,
                      std::shared_ptr<Tspaint> & tspaint,
                      std::function<bool(void)> Continue,
                      std::function<bool(Command *)> IsCommandAllowed) {

    while (Continue() && !interface->End()) {

        auto tellgLast = interface->is.tellg();
        std::shared_ptr<Command> command = nullptr;
        try {
            command = this->getCommandByName(interface->PromptCommand([this](const std::string &name) {
                return std::any_of(commands.begin(), commands.end(),
                                   [&name](Command &command) { return name == command.Name(); });
            }));
        }
        catch (std::ifstream::failure e) {
            interface->PrintInfo(interface->formatter->FillPlaceholder(FormatterParams({END_OF_INPUT_REACHED})));
            break;
        }
        try {
            if (command) {
                if (IsCommandAllowed(command.get())) {
                    command->Execute(tspaint, interface);
                } else {
                    interface->PrintInfo(
                            interface->formatter->FillPlaceholder(COMMAND_NOT_ALLOWED_IN_HEADLESS,
                                                                  FormatterParams({command->Name()})
                            )
                    );
                    std::cout << interface->is.tellg() << std::endl;
                    return false;
                }
            }
        }
        catch( std::runtime_error e){
            interface->PrintInfo(e.what());
            interface->is.clear();
            interface->is.seekg(tellgLast);
            for(int x = 0; x < 3; x++) {
                std::string errorLine;
                std::getline(interface->is, errorLine);
                std::cerr << "error occured around line: " << errorLine << std::endl;
            }
            std::cerr << "near to char " << tellgLast << std::endl;
            return false;
        }
    }
    return true;
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
