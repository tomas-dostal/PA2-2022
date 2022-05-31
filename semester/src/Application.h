/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include "Interface.h"
#include "Command.h"
#include "Tspaint.h"
#include "CommandParameters.h"
#include "messages.h"
#include "CommandImpl.h"

class Application {


public:
    Application() = delete;

    Application(std::shared_ptr<Interface> interface, std::shared_ptr<Tspaint> tspaint);

    ~Application() = default;

    Application(const Application &c) = delete;

    Application &operator=(const Application &c) = delete;

    void Run();

protected:
    Application & RegisterCommand(const Command &c);
    std::shared_ptr<Command> getCommandByName(const std::string name);

private:
    bool isRunning;
    std::vector<Command> commands;
    std::shared_ptr<Interface> interface;
    std::shared_ptr<Tspaint> tspaint;

   // Application &RegisterOption(const std::string name, const CommandParameters &commandParameters);
};
