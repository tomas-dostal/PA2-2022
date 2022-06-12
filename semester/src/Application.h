/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once

#include <functional>
#include <memory>

#include "Interface.h"
#include "Command.h"
#include "Tspaint.h"
#include "messages.h"
#include "CommandImpl.h"
#include "ProgtestErrors.h"


class Application {


public:
    Application() noexcept;

    //Application(std::shared_ptr<Interface> interface, std::shared_ptr<Tspaint> tspaint);

    ~Application() = default;

    Application(const Application &c) = delete;

    Application &operator=(const Application &c) = delete;

    bool Run(const std::shared_ptr<Interface>& interface, std::shared_ptr<Tspaint> &tspaint,
             std::function<bool(void)> Continue,
             std::function<bool(Command *)> IsCommandAllowed);

    void Load(const std::shared_ptr<Interface>& interface, const std::shared_ptr<Interface>&  fileInterface, std::shared_ptr<Tspaint> &targetTspaint);

    void Stop();

    bool IsRunning();

protected:

    std::shared_ptr<Command> getCommandByName(const std::string name);

private:
    bool isRunning;
    std::vector<Command> commands;
    std::shared_ptr<ProgtestErrors> progtestErrors;

};
