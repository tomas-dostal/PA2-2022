/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once


class Application {
    Application() = default;
    Application(const Application & c) = delete;
    Application & operator = (const Application & c) = delete;

public:
    ~Application() = default;

    int Run();
};
