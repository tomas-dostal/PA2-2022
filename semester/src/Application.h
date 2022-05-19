/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once


#include "Interface.h"
#include "CommandParameters.h"
#include "Command.h"

class Application {


public:
    explicit Application(Interface &interface);

    ~Application() = default;

    Application(const Application &c) = delete;

    Application &operator=(const Application &c) = delete;

    void Run();


private:
    std::vector<Command> commands;
    std::shared_ptr<Interface> interface;

    Application &RegisterCommand(const Command &c);

    bool isRunning;

    Application &RegisterOption(const std::string name, const CommandParameters &commandParameters);
};
