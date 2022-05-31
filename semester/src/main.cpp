/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include <iostream>
#include "Application.h"
#include "Interface.h"
#include "Command.h"

int main(void) {


    std::shared_ptr<Interface> interface = std::make_shared<Interface>(Interface(std::cin, std::cout));
    Application app(interface, std::make_unique<Tspaint>(Tspaint()));
    app.Run();

    /*app.RegisterCommand(Command::New(app))
            .RegisterCommand()
            .RegisterCommand();

    app.RegisterCommand("set", nullptr).RegisterOption("color", CommandParameters({"id", int}))
            .RegisterOption("color", CommandParameters({"r", int}, {"g", int}, {"b", int})
                    .RegisterOption("fill", CommandParameters({"id", int}))
                    .RegisterOption("fill", CommandParameters({"r", int}, {"g", int}, {"b", int})
                            .RegisterOption("thickness", CommandParameters({"thickness", int});
*/
    // from these I will always try to parse.
    // First the main command, then the option,
    // then the arguments

/*
    set color <id>;
    set color <r> <g> <b>;

    set fill <id>;
    set fill <r> <g> <b>;

    set thickness <int>;

    draw line <pos_start> <pos_end>
    draw polyline <pos_start> [<pos_i>...]

    draw circle <pos_center> <diameter>
    draw elipsis todo

    draw rectangle <pos_left_bottom>  <pos_right_top>

    draw square <pos_left_bottom> <pos_right_top>

    draw pa2 <pos_left_bottom> <pos_right_top>

    draw group <group_id> <pos_left_bottom>

    hide shape <id>
    hide group <id>

    delete group <id>; // force delete group, so it will stop exist

    new group <name> <id> [id...];

    show all // get all ids of objects including their type
    show <id>


    )
    */
}