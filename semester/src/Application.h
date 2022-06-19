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

    /**
     * Application constructor.
     * Sets up all commands.
     */
    Application() noexcept;

    ~Application() = default;

    Application(const Application &c) = delete;

    Application &operator=(const Application &c) = delete;

    /**
     * Infinite loop for loading from istream
     * @param interface Interface
     * @param tspaint Tspaint instance
     * @param Continue Function pointer deciding whether the loop should be ended if command not found / invalid input. Usefull in headless mode.
     * @param IsCommandAllowed  Function pointer deciding whether command is allowed (system commands are disabled in headless mode)
     * @return
    */
    bool Run(const std::shared_ptr<Interface>& interface, std::shared_ptr<Tspaint> &tspaint,
             std::function<bool(void)> Continue,
             std::function<bool(Command *)> IsCommandAllowed);

    /**
     * Used for loading from istream in tspaint format
     * @param interface
     * @param fileInterface
     * @param targetTspaint
     */
    void Load(const std::shared_ptr<Interface>& interface, const std::shared_ptr<Interface>&  fileInterface, std::shared_ptr<Tspaint> &targetTspaint);

    /**
     * Sets flag isRunning to false, so the Run() loop will not continue further
     */
    void Stop();

    /**
     *
     * @return bool: true if application is running
     */
    bool IsRunning();

    /**
     * Get command by name
     * @param name command name
     * @return std::shared_ptr<Command> if success, else nullptr
     */
    std::shared_ptr<Command> getCommandByName(const std::string name);

private:
    bool isRunning;
    std::vector<Command> commands;
    std::shared_ptr<ProgtestErrors> progtestErrors;

};
